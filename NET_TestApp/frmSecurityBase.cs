using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.Diagnostics;
using TSP.DSC_InteractiveSDK;
using TSP.DSC_InteractiveSDK.Security;
using NET_TestApp.Helpers;

namespace NET_TestApp
{
    public partial class frmSecurityBase : Form
    {
        #region Variables
        private ISecurityBase  _securitybase;
        private InteractiveSDK _sdk;
        #endregion

        #region Constructor
        public frmSecurityBase(InteractiveSDK sdk, string name, ISecurityBase securitybase)
        {
            InitializeComponent();

            this._sdk = sdk;
            this.Name = name;
            this.Text = name;
            this._securitybase = securitybase;
        }
        #endregion

        #region Form Events
        private void frmSecurityBase_Load(object sender, EventArgs e)
        {
            CreateTreeView();
        }

        private void frmSecurityBase_FormClosing(object sender, FormClosingEventArgs e)
        {
            // top node is the securitybase node
            if (tvSecurityBase.Nodes.Count > 0)
            {
                CleanUpTreeView(tvSecurityBase.Nodes[0], true);
            }
        }

        private void updateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // this is just an update to the treeview (to re-read the properties - updated in real-time and don't need a refresh)... since the application 
            // was originally written to execute SDK functions which required calling them and checking the return, then updating the treeview display
            // NOTE: requires an initial refresh of PartitionManager or SystemManager to get the max values, then it will update real-time (upon update call) as 
            // zones/access codes/partitions are added/removed from the system
            ToolStripItem item = (sender as ToolStripItem);
            ContextMenuStrip owner = (item.Owner as ContextMenuStrip);
            Control source = owner.SourceControl;
            TreeView view = (source as TreeView);
            TreeNode node = view.SelectedNode;

            UpdateTreeView(node);
        }

        private void SpecialNodeContextMenuItem_Click(object sender, EventArgs e)
        {
            ToolStripItem item = (sender as ToolStripItem);
            ContextMenuStrip owner = (item.Owner as ContextMenuStrip);
            Control source = owner.SourceControl;
            TreeView view = (source as TreeView);
            TreeNode node = view.SelectedNode;

            object methodowner = (node.Tag as clsNode).Object;
            string methodname = item.Text;

            string key = "LifeStyle - " + this.Name.ToString();
            if (FormUtils.IsFormOpen(key) == false)
            {
                frmLifeStyle f = new frmLifeStyle(this._sdk, key, this._securitybase, methodowner);
                f.Show();
            } // if

        }

        private void NodeContextMenuItem_Click(object sender, EventArgs e)
        {
            ToolStripItem item = (sender as ToolStripItem);
            ContextMenuStrip owner = (item.Owner as ContextMenuStrip);
            Control source = owner.SourceControl;
            TreeView view = (source as TreeView);
            TreeNode node = view.SelectedNode;

            object methodowner = (node.Tag as clsNode).Object;
            string methodname = item.Text;

            // check if the function has parameters or not
            List<object> values = new List<object>();
            if (ReflectionHelpers.HasInputParameters(methodowner, methodname) == true)
            {
                // create the dialog window for user input of parameter values to send to method execution
                frmParameterValuesEntry f = new frmParameterValuesEntry(methodname, _sdk, ReflectionHelpers.GetParameters(methodowner, methodname), values);
                if (f.ShowDialog(this) != DialogResult.OK)
                {
                    return;
                } // if
            }
            else
            {
                // function may have OUT ByRef parameters ONLY, therefore we need to add a null entry in values to catch the return from the method call
                // This is done in the frmParameterValuesEntry() but in this case, we have no parameters to ask the user for, so why show the form
                ParameterInfo[] parameters = ReflectionHelpers.GetParameters(methodowner, methodname);
                foreach (ParameterInfo i in parameters)
                {
                    if ((i.IsOut == true) && (i.ParameterType.IsByRef == true))
                    {
                        // out reference parameter, add null object to catch the value on method execution
                        values.Add(null);
                    }
                }
            }

            // execute the method with the user supplied values
            object[] methodparameters = values.ToArray();

            MethodInfo mi = methodowner.GetType().GetMethod(methodname);
            if (mi != null)
            {
                // need to check the return type for the method
                if (mi.ReturnType == typeof(IRequestResult))
                {
                    // request result type
                    IRequestResult result = ReflectionHelpers.ExecuteMethod_RequestResult(methodowner, methodparameters, methodname);
                    if (result != null)
                    {
                        if (result.ReadWriteResultCode != RequestResultCode.Common_Success)
                        {
                            MessageBox.Show(Enum.GetName(typeof(RequestResultCode), result.ReadWriteResultCode) + ": " + result.ResultDescription, methodname + "()");
                        }
                        else
                        {
                            // need to check for ByRef parameters so we can cast (eg. ReadAccessCodePartitionAssignment)
                            // return values are ByRef parameters to the function call
                            ParameterInfo[] parameters = ReflectionHelpers.GetParameters(methodowner, methodname);
                            string returnvalue = string.Empty;
                            for (int i = 0; i < parameters.Length; ++i)
                            {
                                if (parameters[i].ParameterType.IsByRef == true)
                                {
                                    if (parameters[i].ParameterType.GetElementType() == typeof(string))
                                    {
                                        returnvalue = (methodparameters[i] as string).ToString();
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(UInt32))
                                    {
                                        returnvalue = (Convert.ToUInt32(methodparameters[i])).ToString();
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(UInt32[]))
                                    {
                                        UInt32[] array = (methodparameters[i] as UInt32[]);
                                        if (array.Length == 0)
                                        {
                                            returnvalue = "[not assigned]";
                                        }
                                        else
                                        {
                                            for (int j = 0; j < array.Length; ++j)
                                            {
                                                returnvalue += string.Format("{0}{1}", array[j].ToString(), ((j == array.Length - 1) ? "" : ","));
                                            } // for
                                        } // if
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(IVirtualKeypad))
                                    {
                                        returnvalue = "Successful";
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(ISystemCapabilities))
                                    {
                                        string astring = string.Empty;
                                        using (methodparameters[i] as ISystemCapabilities)
                                        {
                                            astring += "\r\nPeer Identifier: " + (methodparameters[i] as ISystemCapabilities).PeerIdentifier + "\r\n";
                                            astring += "Supported AccessCodes: " + (methodparameters[i] as ISystemCapabilities).SupportedAccessCodes + "\r\n";
                                            astring += "Supported CommandOutputs: " + (methodparameters[i] as ISystemCapabilities).SupportedCommandOutputs + "\r\n";
                                            astring += "Supported FOBs: " + (methodparameters[i] as ISystemCapabilities).SupportedFOBs + "\r\n";
                                            astring += "Supported Partitions: " + (methodparameters[i] as ISystemCapabilities).SupportedPartitions + "\r\n";
                                            astring += "Supported ProximityTags : " + (methodparameters[i] as ISystemCapabilities).SupportedProximityTags + "\r\n";
                                            astring += "Supported Zones: " + (methodparameters[i] as ISystemCapabilities).SupportedZones + "\r\n";
                                        }
                                        returnvalue = astring;
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(ISystemInformation))
                                    {
                                        string astring = string.Empty;
                                        using (methodparameters[i] as ISystemInformation)
                                        {
                                            astring += "\r\nPeer Identifier: " + (methodparameters[i] as ISystemInformation).PeerIdentifier + "\r\n";
                                            astring += "Software Version: " + (methodparameters[i] as ISystemInformation).SoftwareVersion + "\r\n";
                                            astring += "Protocol Version: " + (methodparameters[i] as ISystemInformation).ProtocolVersion + "\r\n";
                                            astring += "Miscellaneous Info: " + (methodparameters[i] as ISystemInformation).MiscellaneousInfo + "\r\n";
                                        }
                                        returnvalue = astring;
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(LifeStyleNotification[]))
                                    {
                                        string astring = string.Empty;
                                        LifeStyleNotification[] array = (methodparameters[i] as LifeStyleNotification[]);
                                        if (array.Length == 0)
                                        {
                                            astring = "[not assigned]";
                                        }
                                        else
                                        {
                                            for (int j = 0; j < array.Length; ++j)
                                            {
                                                astring += string.Format("{0}{1}", Enum.GetName(typeof(LifeStyleNotification), array[j]).ToString(), ((j == array.Length - 1) ? "" : ","));
                                            }
                                        }
                                        returnvalue = astring;
                                    }
                                    else if (parameters[i].ParameterType.GetElementType() == typeof(ITroubleList))
                                    {
                                        string astring = string.Empty;
                                        using (methodparameters[i] as ITroubleList)
                                        {
                                            for (int j = 0, count = (methodparameters[i] as ITroubleList).Troubles.Length; j < count; ++j)
                                            {
                                                astring += "\r\nTrouble " + (j + 1).ToString() + ":\r\n";
                                                astring += "DeviceModuleType = " + Enum.GetName(typeof(DeviceModuleType), (methodparameters[i] as ITroubleList).Troubles[j].DeviceModuleType).ToString() + "\r\n";
                                                astring += "TroubleType = " + Enum.GetName(typeof(TroubleType), (methodparameters[i] as ITroubleList).Troubles[j].TroubleType).ToString() + "\r\n";
                                                astring += "DeviceModuleNumber = " + (methodparameters[i] as ITroubleList).Troubles[j].DeviceModuleNumber.ToString() + "\r\n";
                                                astring += "TroubleStatus = " + Enum.GetName(typeof(TroubleState), (methodparameters[i] as ITroubleList).Troubles[j].TroubleStatus).ToString() + "\r\n";
                                            }
                                        }
                                        if (astring == string.Empty)
                                        {
                                            astring = "\r\nNo Troubles\r\n";
                                        }
                                        returnvalue = astring;
                                    }
                                    else
                                    {
                                        returnvalue = string.Format("Unknown ParameterType: {0}", parameters[i].ParameterType.ToString());
                                    } // if
                                } // if
                            } // for

                            if (returnvalue != string.Empty)
                            {
                                MessageBox.Show(String.Format("{0}() Result = {1}", methodname, returnvalue));
                            }
                            else
                            {
                                MessageBox.Show("Last Operation Successfull");
                            } // if
                            if ((String.Compare(methodname, "Refresh") == 0) || (String.Compare(methodname, "Configure") == 0))
                            {
                                (node.Tag as clsNode).IsRefreshed = true;
                            } // if
                        } // if
                        result.Dispose();
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    } // if
                }
                else
                {
                    MessageBox.Show("Unknown return type " + mi.ReturnType.ToString());
                } // if
            } // if

            // cleanup interface in/out parameters
            foreach (object o in values)
            {
                if ((o as TSP.DSC_InteractiveSDK.IComponent) != null)
                {
                    (o as TSP.DSC_InteractiveSDK.IComponent).Dispose();
                }
            }

            CleanUpTreeView(node, true);

            UpdateTreeView(node);
        }

        private void tvSecurityBase_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                // change selected node on right mouse click... the context menu needs the tag property of the 
                // selected node, but on right mouse click the selection isn't changed, hence we'll get the wrong 
                // treenode
                tvSecurityBase.SelectedNode = e.Node;
            } // if
        }

        private void tvSecurityBase_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            // can double click on attributes to change their values
            if (e.Button == MouseButtons.Left)
            {
                if ((e.Node.Tag as clsNode).IsEditable == true)
                {
                    if (FormUtils.IsFormOpen("frmAttributeChange") == false)
                    {
                        frmAttributeChange f = new frmAttributeChange(e.Node);
                        Point point = (sender as Control).PointToScreen(new Point(e.X, e.Y));
                        f.SetDesktopLocation(point.X, point.Y);
                        if (f.ShowDialog(this) == DialogResult.OK)
                        {
                            string new_value = f.AttributeValue;
                            try
                            {
                                PropertyInfo pi = (e.Node.Parent.Tag as clsNode).Object.GetType().GetProperty((e.Node.Tag as clsNode).ItemName);
                                if (pi != null)
                                {
                                    // doing some assembly magic to programatically resolve the ParameterType... avoids having to use a giant if statement
                                    // to process ALL the enums seperately
                                    string assembly = typeof(FAPType).AssemblyQualifiedName.Remove(0, typeof(FAPType).AssemblyQualifiedName.IndexOf(','));
                                    Type aType = Type.GetType(pi.PropertyType.FullName + assembly);
                                    pi.SetValue((e.Node.Parent.Tag as clsNode).Object, Enum.Parse(aType, new_value), null);
                                    (e.Node.Tag as clsNode).Value = new_value;
                                    UpdateNodeText(e.Node);
                                    e.Node.ForeColor = Color.Red;
                                } // if                           
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show(ex.Message);
                            } // try
                        } // if
                    } // if
                } // if
            } // if
        }
        #endregion

        #region Private Methods

        private void CreateTreeView()
        {
            tvSecurityBase.BeginUpdate();

            tvSecurityBase.Nodes.Clear();

            tvSecurityBase.Nodes.Add(CreateNode(null, _securitybase, cmsSecurityBase, new Action<TreeNode>(UpdateSecurityBaseNode), "Security Base", false, true));

            tvSecurityBase.EndUpdate();
        }

        private TreeNode CreateNode(TreeNode parent, object o, ContextMenuStrip cms, Action<TreeNode> subitem, string text, bool editable, bool root)
        {
            // creating a child of the parent
            clsNode  n = new clsNode();
            TreeNode t = new TreeNode();

            // clsNode
            n.Owner       = t;
            n.Object      = o;
            n.Value       = string.Empty;
            n.ItemText    = text;
            n.ItemName    = n.ItemText.Replace(" ", "");
            n.SubItem     = subitem;
            n.IsEditable  = editable;
            n.IsRoot      = root;
            n.IsRefreshed = false;

            // treeNode
            t.Name             = n.ItemName.ToLower();
            t.ContextMenuStrip = cms;
            t.Tag              = n;

            // do color update for added node
            if (t.ContextMenuStrip != null)
            {
                // has context menu, so has refresh most likely but since it is being created, refresh hasn't been called
                t.ToolTipText = String.Format("Right Click For {0} Functionality", n.ItemText);
                t.ForeColor = Color.Red;

                if (o != null)
                {
                    if (n.IsRoot == true)
                    {
                        t.ForeColor = Color.Green;
                        n.IsRefreshed = true;
                    } // if
                } // if
            }
            else
            {
                // doesn't have a context menu, either a property or array (need to check the parent for isRefreshed)
                t.ForeColor = Color.Red;
                if (o != null)
                {
                    // object assigned, so most likely a collection, check
                    if (o.GetType().IsArray == true)
                    {
                        // object collection, parent present and refreshed?
                        if (parent != null)
                        {
                            if ((parent.Tag as clsNode).IsRefreshed == true)
                            {
                                t.ForeColor = Color.Green;
                            } // if
                        } // if
                    }
                    else
                    {
                        // could be the root node, check
                        if (n.IsRoot == true)
                        {
                            t.ForeColor = Color.Green;
                        } // if
                    } // if
                }
                else
                {
                    // no object assigned, so most likely a property
                    if (parent != null)
                    {
                        if ((parent.Tag as clsNode).IsRefreshed == true)
                        {
                            // parent is present and refreshed, we can proceed to GetValue() - NOTE: don't want to call this with reflection while filling in a UI control UNLESS
                            // the parent is refreshed, because if the values aren't filled in, the SDK throws an exception that the value is unknown... this adds a ~100ms delay 
                            // to adding EACH treenode and the Treeview slows to a crawl updating.
                            t.ForeColor = Color.Green;
                            n.Value = GetValue((parent.Tag as clsNode).Object, n.ItemName.ToString());
                        } // if
                    } // if
                } // if
            } // if

            // update the display value
            t.Text = n.ItemText + ((n.Value != string.Empty) ? ": " + n.Value.ToString() : "");

            // do node addition
            if (parent != null)
            {
                parent.Nodes.Add(t);
                //parent.ExpandAll();
                // we have any subitems to do?
                if (n.SubItem != null)
                {
                    n.SubItem(t);
                } // if
            }
            else
            {
                // if parent == null then we are doing the root node
                if (n.SubItem != null)
                {
                    n.SubItem(t);
                }
            }

            return (t);
        }

        private void CleanUpTreeView(TreeNode caller, bool isTopNode)
        {
            if (caller.Nodes.Count > 0)
            {
                // has sub items
                int count = caller.Nodes.Count;
                for (int i = (count - 1); i >= 0; i--)
                {
                    // cleanup from the bottom to the top
                    CleanUpTreeView(caller.Nodes[i], false);
                }
            }

            if ((caller.Tag != null) && (isTopNode == false))
            {
                // no sub items, can clean this one up if it'snot the top node
                clsNode node = (caller.Tag as clsNode);
                if (node.Object != null)
                {
                    if ((node.Object as TSP.DSC_InteractiveSDK.IComponent) != null)
                    {
                        (node.Object as TSP.DSC_InteractiveSDK.IComponent).Dispose();
                    }
                    else if ((node.Object as TSP.DSC_InteractiveSDK.IComponent[]) != null)
                    {
                        node.Object = null;
                    }
                }
            }
        }

        private void UpdateTreeView(TreeNode caller)
        {
            clsNode node = (caller.Tag as clsNode);

            tvSecurityBase.BeginUpdate();

            // update the color of the callers
            caller.ForeColor = Color.Red;
            if (node.IsRefreshed == true)
            {
                caller.ForeColor = Color.Green;
            } // if

            // process any subitems
            if (node.SubItem != null)
            {
                node.SubItem((node.Owner as TreeNode));
            } // if

            tvSecurityBase.EndUpdate();
        }

        private void UpdateNodeText(TreeNode node)
        {
            clsNode n = (node.Tag as clsNode);

            node.Text = n.ItemText + ((n.Value != string.Empty) ? ": " + n.Value.ToString() : "");
        }

        private string GetValue(object obj, string property)
        {
            string value = string.Empty;

            try
            {
                value = ReflectionHelpers.GetPropertyValue(obj, property, string.Empty);
            }
            catch (TargetInvocationException tie)
            {
                // TargeInvocationException means that the called method fired an exception internally and the InnerException
                // is holding the exception information. In this case, InteractiveSdkException.
                if (tie.InnerException.GetType() == typeof(InteractiveSdkException))
                {
                    value = Enum.GetName(typeof(ResultCode), (tie.InnerException as InteractiveSdkException).SdkResult);
                } // if
            }
            catch (Exception)
            {
            } // try

            return (value);
        }

        #region Security Base
        
        private void UpdateSecurityBaseNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, ((parent.Tag as clsNode).Object as ISecurityBase).PartitionManager, cmsPartitionManager, new Action<TreeNode>(UpdatePartitionManagerNode), "Partition Manager", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as ISecurityBase).SystemManager, cmsSystemManager, new Action<TreeNode>(UpdateSystemManagerNode), "System Manager", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as ISecurityBase).Repository, cmsRepository, new Action<TreeNode>(UpdateRepositoryNode), "Repository", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as ISecurityBase).SpecificFunctions, cmsSpecificFunctions, null, "Specific Functions", false, true);
        }
        #endregion

        #region Partition Manager

        private void UpdatePartitionManagerNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            if (((parent.Tag as clsNode).Object as IPartitionManager).Partitions.Length > 0)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IPartitionManager).Partitions, null, new Action<TreeNode>(UpdatePartitionsNode), "Partitions", false, false);
            } // if
        }

        #region Partition
        private void UpdatePartitionsNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            for (int i = 0; i < ((parent.Tag as clsNode).Object as IPartition[]).Length; ++i)
            {
                // try/catch on the enable since the property might not have been set yet
                try
                {
                    // check if the partition is enabled or not... if not, don't display it
                    if (((parent.Tag as clsNode).Object as IPartition[])[i].Enabled == true)
                    {
                        CreateNode(parent, ((parent.Tag as clsNode).Object as IPartition[])[i], cmsPartition, new Action<TreeNode>(UpdatePartitionNode), "Partition " + ((parent.Tag as clsNode).Object as IPartition[])[i].SystemIndex.ToString(), false, false);
                    }
                }
                catch (InteractiveSdkException ie)
                {
                    // sdkresult values are stored in InteractiveSDK_dotNet->Common->Interface->Enums->ResultCodes.hpp
                    if (ie.SdkResult == Convert.ToInt32(ResultCode.Err_Unknown_Value))
                    {
                        // Enabled value is unknown(hasn't been received from the panel yet [Refresh not done])
                        // so we can't use the enabled flag, therefore don't display the partition
                    }
                    else
                    {
                        MessageBox.Show(ie.Message);
                    }
                }
            } // for
        }

        private void UpdatePartitionNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Label", false, false);

            CreateNode(parent, null, null, null, "Enabled", false, false);

            CreateNode(parent, null, null, null, "System Index", false, false);

            CreateNode(parent, null, null, null, "Door Chime Enabled", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as IPartition).PartitionStateData, cmsPartitionStateData, new Action<TreeNode>(UpdatePartitionStateDataNode), "Partition State Data", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as IPartition).ZoneManager, cmsZoneManager, new Action<TreeNode>(UpdateZoneManagerNode), "Zone Manager", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as IPartition).AccessCodeManager, cmsAccessCodeManager, new Action<TreeNode>(UpdateAccessCodeManagerNode), "Access Code Manager", false, false);
        }

        private void UpdatePartitionStateDataNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Partition Buzzer", false, false);

            CreateNode(parent, null, null, null, "Partition Quick Exit", false, false);

            CreateNode(parent, null, null, null, "Partition Ready", false, false);

            CreateNode(parent, null, null, null, "Partition Armed", false, false);

            CreateNode(parent, null, null, null, "Partition Blank", false, false);

            CreateNode(parent, null, null, null, "Partition Trouble", false, false);

            CreateNode(parent, null, null, null, "Partition Exit Delay", false, false);

            CreateNode(parent, null, null, null, "Partition Entry Delay", false, false);

            CreateNode(parent, null, null, null, "Partition Bypass", false, false);

            CreateNode(parent, null, null, null, "Partition Alarm", false, false);

            CreateNode(parent, null, null, null, "Partition Alarm Memory", false, false);

            CreateNode(parent, null, null, null, "Partition Busy", false, false);

            CreateNode(parent, null, null, null, "Partition Audible Bell State", false, false);

            CreateNode(parent, null, null, null, "Partition Audible Bell Type", false, false);
        }
        #endregion

        #region Zone
        private void UpdateZoneManagerNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            if (((parent.Tag as clsNode).Object as IZoneManager).Zones.Length > 0)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IZoneManager).Zones, null, new Action<TreeNode>(UpdateZonesNode), "Zones", false, false);
            } // if
        }

        private void UpdateZonesNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            for (int i = 0; i < ((parent.Tag as clsNode).Object as IZone[]).Length; ++i)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IZone[])[i], cmsZone, new Action<TreeNode>(UpdateZoneNode), "Zone " + ((parent.Tag as clsNode).Object as IZone[])[i].SystemIndex.ToString(), false, false);
            } // for
        }

        private void UpdateZoneNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Label", false, false);

            CreateNode(parent, null, null, null, "System Index", false, false);

            CreateNode(parent, null, null, null, "Alarm In Memory State", false, false);

            CreateNode(parent, null, null, null, "Alarm State", false, false);

            CreateNode(parent, null, null, null, "Bypass State", false, false);

            CreateNode(parent, null, null, null, "Open Close State", false, false);

            CreateNode(parent, null, null, null, "Tamper State", false, false);

            CreateNode(parent, null, null, null, "Low Sensitivity State", false, false);

            CreateNode(parent, null, null, null, "Delinquency State", false, false);

            CreateNode(parent, null, null, null, "Low Battery State", false, false);

            CreateNode(parent, null, null, null, "Fault State", false, false);

            CreateNode(parent, null, null, null, "Masked State", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as IZone).Attributes, cmsZoneAttributes, new Action<TreeNode>(UpdateZoneAttributesNode), "Attributes", false, false);
        }

        private void UpdateZoneAttributesNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Chime Function", true, false);

            CreateNode(parent, null, null, null, "Bypass Enable", true, false);
        }
        #endregion

        #region Access Code
        private void UpdateAccessCodeManagerNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            if (((parent.Tag as clsNode).Object as IAccessCodeManager).AccessCodes.Length > 0)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IAccessCodeManager).AccessCodes, null, new Action<TreeNode>(UpdateAccessCodesNode), "Access Codes", false, false);
            } // if
        }

        private void UpdateAccessCodesNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            for (int i = 0; i < ((parent.Tag as clsNode).Object as IAccessCode[]).Length; ++i)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IAccessCode[])[i], cmsAccessCode, new Action<TreeNode>(UpdateAccessCodeNode), "Access Code " + ((parent.Tag as clsNode).Object as IAccessCode[])[i].SystemIndex.ToString(), false, false);
            } // for
        }

        private void UpdateAccessCodeNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Value", false, false);

            CreateNode(parent, null, null, null, "Label", false, false);

            CreateNode(parent, null, null, null, "System Index", false, false);

            CreateNode(parent, null, null, null, "Access Code Length", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as IAccessCode).Attributes, cmsAccessCodeAttributes, new Action<TreeNode>(UpdateAccessCodeAttributesNode), "Attributes", false, false);
        }

        private void UpdateAccessCodeAttributesNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Can Bypass Zone", true, false);

            CreateNode(parent, null, null, null, "Remote Access Enabled", true, false);

            CreateNode(parent, null, null, null, "One Time Use", true, false);

            CreateNode(parent, null, null, null, "Bell Squawk", true, false);

            CreateNode(parent, null, null, null, "Supervisor", true, false);

            CreateNode(parent, null, null, null, "Duress Code", true, false);
        }
        #endregion

        #endregion

        #region System Manager

        private void UpdateSystemManagerNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Trouble Present", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as ISystemManager).VirtualZoneManager, cmsVirtualZoneManager, new Action<TreeNode>(UpdateVirtualZoneManagerNode), "Virtual Zone Manager", false, false);
        }

        #region Virtual Zone
        private void UpdateVirtualZoneManagerNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            if (((parent.Tag as clsNode).Object as IVirtualZoneManager).VirtualZones.Length > 0)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IVirtualZoneManager).VirtualZones, null, new Action<TreeNode>(UpdateVirtualZonesNode), "Virtual Zones", false, false);
            } // if
        }

        private void UpdateVirtualZonesNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            for (int i = 0; i < ((parent.Tag as clsNode).Object as IVirtualZone[]).Length; ++i)
            {
                CreateNode(parent, ((parent.Tag as clsNode).Object as IVirtualZone[])[i], cmsVirtualZone, new Action<TreeNode>(UpdateVirtualZoneNode), "Virtual Zone " + ((parent.Tag as clsNode).Object as IVirtualZone[])[i].SystemIndex.ToString(), false, false);
            } // for
        }

        private void UpdateVirtualZoneNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "System Index", false, false);

            CreateNode(parent, null, null, null, "Zone Number", false, false);

            CreateNode(parent, ((parent.Tag as clsNode).Object as IVirtualZone).ZoneStatus, cmsVirtualZoneStatus, new Action<TreeNode>(UpdateVirtualZoneStatusNode), "ZoneStatus", false, false);
        }

        private void UpdateVirtualZoneStatusNode(TreeNode parent)
        {
            parent.Nodes.Clear();

            CreateNode(parent, null, null, null, "Open", true, false);

            CreateNode(parent, null, null, null, "Tamper", true, false);

            CreateNode(parent, null, null, null, "Fault", true, false);

            CreateNode(parent, null, null, null, "Low Battery", true, false);

            CreateNode(parent, null, null, null, "AC Trouble", true, false);

            CreateNode(parent, null, null, null, "Masked", true, false);
        }
        #endregion

        #endregion

        #region Repository

        private void UpdateRepositoryNode(TreeNode parent)
        {
            parent.Nodes.Clear();
            (parent.Tag as clsNode).IsRefreshed = true;

            CreateNode(parent, null, null, null, "Peer Identifier", false, false);
            CreateNode(parent, null, null, null, "Software Version", false, false);
            CreateNode(parent, null, null, null, "Protocol Version", false, false);
            CreateNode(parent, null, null, null, "Miscellaneous Info", false, false);
            CreateNode(parent, null, null, null, "Supported AccessCodes", false, false);
            CreateNode(parent, null, null, null, "Supported Partitions", false, false);
            CreateNode(parent, null, null, null, "Supported Zones", false, false);
            CreateNode(parent, null, null, null, "Supported FOBs", false, false);
            CreateNode(parent, null, null, null, "Supported ProximityTags", false, false);
            CreateNode(parent, null, null, null, "Supported CommandOutputs", false, false);
            CreateNode(parent, null, null, null, "Number Of AccessCodes", false, false);
            CreateNode(parent, null, null, null, "Number Of Partitions", false, false);
            CreateNode(parent, null, null, null, "Number Of Zones", false, false);
            CreateNode(parent, null, null, null, "Number Of VirtualZones", false, false);
        }

        #endregion

        #endregion
    }
}
