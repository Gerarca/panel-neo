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
    public partial class frmLifeStyle : Form
    {
        #region Variables
        private ISecurityBase  _securitybase;
        private InteractiveSDK _sdk;
        private object         _methodowner;
        #endregion

        #region Constructor
        public frmLifeStyle(InteractiveSDK sdk, string name, ISecurityBase securitybase, object methodowner)
        {
            InitializeComponent();

            this._sdk = sdk;
            this.Name = name;
            this.Text = name;
            this._securitybase = securitybase;
            this._methodowner = methodowner;
        }
        #endregion

        private void Read_Write_Click(object sender, EventArgs e)
        {
            
            string methodname = (sender as Button).Text;

            UInt32              max_zones = 0;
            ISystemCapabilities system_capabilities = null;
            IRequestResult      iresult = null;
            try
            {
                iresult = _securitybase.ReadSystemCapabilities(out system_capabilities);
                if (null != iresult)
                {
                    if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                    {
                        max_zones = system_capabilities.SupportedZones;
                    }
                    else
                    {
                        MessageBox.Show(
                            Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                            iresult.ResultDescription, methodname + "()");
                        return;
                    }
                }
                else
                {
                    MessageBox.Show("Error Executing Method!", methodname + "()");
                    return;
                }
            }
            catch (InteractiveSdkException sdke)
            {
                iresult = sdke.SdkRequestResult;
                MessageBox.Show(
                    Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                    iresult.ResultDescription, methodname + "()");
                return;
            }
            finally
            {
                if (iresult != null)
                {
                    iresult.Dispose();
                }
                if (system_capabilities != null)
                {
                    system_capabilities.Dispose();
                }
            }

            ISpecificFunctions specific_functions = _securitybase.SpecificFunctions;
            try
            {
                // what operation are we doing?
                if (0 == string.Compare(methodname, "ITV2_ReadLifeStyleNotificationSettings"))
                {
                    LifeStyleNotification[] notifications = new LifeStyleNotification[0];
                    iresult = specific_functions.ITV2_ReadLifeStyleNotificationSettings(out notifications);
                    if (null != iresult)
                    {
                        if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                        {
                            if (null != notifications)
                            {
                                lblOn.Text = "LifeStyle Notifications On";
                                lblOff.Text = "LifeStyle Notifications Off";

                                // update ON notifications
                                lbOn.BeginUpdate();
                                lbOn.Items.Clear();
                                for (int j = 0; j < notifications.Length; ++j)
                                {
                                    lbOn.Items.Add(Enum.GetName(typeof(LifeStyleNotification), notifications[j]).ToString());
                                }
                                lbOn.EndUpdate();

                                // update OFF notifications
                                lbOff.BeginUpdate();
                                lbOff.Items.Clear();
                                LifeStyleNotification[] values = (LifeStyleNotification[])Enum.GetValues(typeof(LifeStyleNotification));
                                int max_values = values.Length;
                                for (int j = 0; j < max_values; ++j)
                                {
                                    if ((values[j] == LifeStyleNotification.Unknown) || (values[j] == LifeStyleNotification.Not_Available))
                                    {
                                        // don't include Unknown or Not_Available
                                        continue;
                                    } // if
                                    string aString = Enum.GetName(typeof(LifeStyleNotification), values[j]).ToString();
                                    if (false == lbOn.Items.Contains(aString))
                                    {
                                        lbOff.Items.Add(aString);
                                    }
                                }
                                lbOff.EndUpdate();
                            }
                            MessageBox.Show("Success", methodname + "()");
                        }
                        else
                        {
                            MessageBox.Show(
                                Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                                iresult.ResultDescription, methodname + "()");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    }

                }
                else if (0 == string.Compare(methodname, "ITV2_WriteLifeStyleNotificationSettings"))
                {
                    // check the data in the lbOn&lbOff to make sure it's notification data FIRST
                    if (0 != lbOn.Items.Count)
                    {
                        LifeStyleNotification result;
                        if (false == Enum.TryParse<LifeStyleNotification>(lbOn.Items[0].ToString(), out result))
                        {
                            // can't parse the first item as a LifeStyleNotifiation type... therefore the user
                            // most likely pressed the ITV2_WriteLifeStyleNotificationSettings button while
                            // there is ZoneNotificationSetting data in there
                            MessageBox.Show(
                                "Cannot execute this method call with ZoneNotification data!", methodname + "()");
                            return;
                        }
                    }
                    if (0 != lbOff.Items.Count)
                    {
                        LifeStyleNotification result;
                        if (false == Enum.TryParse<LifeStyleNotification>(lbOff.Items[0].ToString(), out result))
                        {
                            // can't parse the first item as a LifeStyleNotifiation type... therefore the user
                            // most likely pressed the ITV2_WriteLifeStyleNotificationSettings button while
                            // there is ZoneNotificationSetting data in there
                            MessageBox.Show(
                                "Cannot execute this method call with ZoneNotification data!", methodname + "()");
                            return;
                        }
                    }

                    // create ON notifications list
                    List<LifeStyleNotification> onNotifications = new List<LifeStyleNotification>();
                    foreach (Object i in lbOn.Items)
                    {
                        LifeStyleNotification result;
                        if (true == Enum.TryParse<LifeStyleNotification>(i.ToString(), out result))
                        {
                            onNotifications.Add(result);
                        }
                        else
                        {
                            // error
                        }
                    }

                    // create OFF Notifications list
                    List<LifeStyleNotification> offNotifications = new List<LifeStyleNotification>();
                    foreach (Object i in lbOff.Items)
                    {
                        LifeStyleNotification result;
                        if (true == Enum.TryParse<LifeStyleNotification>(i.ToString(), out result))
                        {
                            offNotifications.Add(result);
                        }
                        else
                        {
                            // error
                        }
                    }

                    iresult = specific_functions.ITV2_WriteLifeStyleNotificationSettings(onNotifications.ToArray(), offNotifications.ToArray());
                    if (null != iresult)
                    {
                        if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                        {
                            MessageBox.Show("Success", methodname + "()");
                        }
                        else
                        {
                            MessageBox.Show(
                                Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                                iresult.ResultDescription, methodname + "()");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    }
                }
                else if (0 == string.Compare(methodname, "ITV2_DefaultLifeStyleNotificationSettings"))
                {
                    iresult = specific_functions.ITV2_DefaultLifeStyleNotificationSettings();
                    if (null != iresult)
                    {
                        if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                        {
                            MessageBox.Show("Success", methodname + "()");
                        }
                        else
                        {
                            MessageBox.Show(
                                Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                                iresult.ResultDescription, methodname + "()");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    }
                }
                else if (0 == string.Compare(methodname, "ITV2_ReadZoneNotificationSettings"))
                {
                    UInt32[] zone_indexes = new UInt32[0];
                    iresult = specific_functions.ITV2_ReadZoneNotificationSettings(out zone_indexes);
                    if (null != iresult)
                    {
                        if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                        {
                            if (null != zone_indexes)
                            {
                                lblOn.Text = "Zone Notifications On";
                                lblOff.Text = "Zone Notifications Off";

                                // update the ON zones
                                lbOn.BeginUpdate();
                                lbOn.Items.Clear();
                                for (int j = 0; j < zone_indexes.Length; ++j)
                                {
                                    lbOn.Items.Add(string.Format("Zone{0}", zone_indexes[j]));
                                }
                                lbOn.EndUpdate();

                                // update the OFF zones
                                lbOff.BeginUpdate();
                                lbOff.Items.Clear();
                                for (int j = 1; j <= max_zones; ++j)
                                {
                                    string aString = string.Format("Zone{0}", j);
                                    if (false == lbOn.Items.Contains(aString))
                                    {
                                        lbOff.Items.Add(aString);
                                    }
                                }
                                lbOff.EndUpdate();
                            }
                            MessageBox.Show("Success", methodname + "()");
                        }
                        else
                        {
                            MessageBox.Show(
                                Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                                iresult.ResultDescription, methodname + "()");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    }
                }
                else if (0 == string.Compare(methodname, "ITV2_WriteZoneNotificationSettings"))
                {
                    // check the data in the lbOn&lbOff to make sure it's zone data FIRST
                    if (0 != lbOn.Items.Count)
                    {
                        LifeStyleNotification result;
                        if (true == Enum.TryParse<LifeStyleNotification>(lbOn.Items[0].ToString(), out result))
                        {
                            // can't parse the first item as a LifeStyleNotifiation type... therefore the user
                            // most likely pressed the ITV2_WriteZoneNotificationSettings button while
                            // there is LifeStyleNotificationSettings data in there
                            MessageBox.Show(
                                "Cannot execute this method call with LifeStyleNotification data!", methodname + "()");
                            return;
                        }
                    }
                    if (0 != lbOff.Items.Count)
                    {
                        LifeStyleNotification result;
                        if (true == Enum.TryParse<LifeStyleNotification>(lbOff.Items[0].ToString(), out result))
                        {
                            // can't parse the first item as a LifeStyleNotifiation type... therefore the user
                            // most likely pressed the ITV2_WriteZoneNotificationSettings button while
                            // there is LifeStyleNotificationSettings data in there
                            MessageBox.Show(
                                "Cannot execute this method call with LifeStyleNotification data!", methodname + "()");
                            return;
                        }
                    }

                    // create ON zone list
                    List<UInt32> onZones = new List<UInt32>();
                    foreach (Object i in lbOn.Items)
                    {
                        if (true == i.ToString().Contains("Zone"))
                        {
                            string zoneNumber = i.ToString().Replace("Zone", "");
                            onZones.Add(Convert.ToUInt32(zoneNumber));
                        }
                    }

                    // create OFF zone list
                    List<UInt32> offZones = new List<UInt32>();
                    foreach (Object i in lbOff.Items)
                    {
                        if (true == i.ToString().Contains("Zone"))
                        {
                            string zoneNumber = i.ToString().Replace("Zone", "");
                            offZones.Add(Convert.ToUInt32(zoneNumber));
                        }
                    }

                    iresult = specific_functions.ITV2_WriteZoneNotificationSettings(onZones.ToArray(), offZones.ToArray());
                    if (null != iresult)
                    {
                        if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                        {
                            MessageBox.Show("Success", methodname + "()");
                        }
                        else
                        {
                            MessageBox.Show(
                                Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                                iresult.ResultDescription, methodname + "()");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    }
                }
                else if (0 == string.Compare(methodname, "ITV2_DefaultZoneNotificationSettings"))
                {
                    iresult = specific_functions.ITV2_DefaultZoneNotificationSettings();
                    if (null != iresult)
                    {
                        if (RequestResultCode.Common_Success == iresult.ReadWriteResultCode)
                        {
                            MessageBox.Show("Success", methodname + "()");
                        }
                        else
                        {
                            MessageBox.Show(
                                Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                                iresult.ResultDescription, methodname + "()");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Error Executing Method!", methodname + "()");
                    }
                }
                else
                {
                    MessageBox.Show("Unknown Function Call!", methodname + "()");
                }
            }
            catch (InteractiveSdkException sdke)
            {
                iresult = sdke.SdkRequestResult;
                MessageBox.Show(
                    Enum.GetName(typeof(RequestResultCode), iresult.ReadWriteResultCode) + ": " +
                    iresult.ResultDescription, methodname + "()");
            }
            finally
            {
                if (iresult != null)
                {
                    iresult.Dispose();
                }
                if (specific_functions != null)
                {
                    specific_functions.Dispose();
                }
            }
        }

        private void Move_To_Click(object sender, EventArgs e)
        {
            Button  aButton      = (sender as Button);
            ListBox aSource      = null;
            ListBox aDestination = null;

            if(true == aButton.Name.Contains("Off"))
            {
                aSource = lbOn;
                aDestination = lbOff;
            }
            else
            {
                aSource = lbOff;
                aDestination = lbOn;
            } // if

            if (0 < aSource.SelectedItems.Count)
            {
                foreach (var i in aSource.SelectedItems)
                {
                    aDestination.Items.Add(i);
                }
                while (0 < aSource.SelectedItems.Count)
                {
                    aSource.Items.Remove(aSource.SelectedItems[0]);
                }
            }

            return;
        }
    }
}
