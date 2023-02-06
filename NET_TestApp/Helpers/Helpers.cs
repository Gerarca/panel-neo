using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Windows.Forms;
using TSP.DSC_InteractiveSDK;
using TSP.DSC_InteractiveSDK.Security;

namespace NET_TestApp.Helpers
{
    public class clsNode
    {
        public string Value             = string.Empty;
        public object Object            = null;
        public object Owner             = null;
        public string ItemText          = string.Empty;
        public string ItemName          = string.Empty;
        public bool   IsEditable        = false;
        public bool   IsRefreshed       = false;
        public bool   IsRoot            = false;
        public Action<TreeNode> SubItem = null;

        public clsNode()
        {
        }
    }

    public static class FormUtils
    {
        public static bool IsFormOpen(string formName)
        {
            if (Application.OpenForms[formName] == null)
            {
                return (false);
            } // if
            return (true);
        }

        public static void SetActive(string formName)
        {
            if (Application.OpenForms[formName] != null)
            {
                Application.OpenForms[formName].Activate();
            } // if
            return;
        }

        public static Form GetForm(string formName)
        {
            return (Application.OpenForms[formName]);
        }
    }

    public static class ReflectionHelpers
    {
        #region Properties
        public static PropertyInfo[] GetProperties(object obj)
        {
            PropertyInfo[] properties = new PropertyInfo[0];
            try
            {
                properties = obj.GetType().GetProperties();
            }
            catch (Exception)
            {
            } // try
            return (properties);
        }

        public static PropertyInfo[] GetProperties(object obj, BindingFlags flags)
        {
            PropertyInfo[] properties = new PropertyInfo[0];
            try
            {
                properties = obj.GetType().GetProperties(flags);
            }
            catch (Exception)
            {
            } // try
            return (properties);
        }

        public static Type GetPropertyType(object obj, string property)
        {
            PropertyInfo pi = obj.GetType().GetProperty(property);
            if (pi != null)
            {
                return (pi.PropertyType);
            } // if
            return(default(Type));
        }

        public static string GetPropertyValue(object obj, string property, string dval)
        {
            PropertyInfo pi = obj.GetType().GetProperty(property);
            if (pi != null)
            {
                return ((pi.GetValue(obj, null)).ToString());
            } // if
            return (dval);
        }

        public static bool SetPropertyValue<T>(object obj, string property, T value)
        {
            try
            {
                PropertyInfo pi = obj.GetType().GetProperty(property);
                if (pi != null)
                {
                    pi.SetValue(obj, value, null);
                } // if
                return (true);
            }
            catch (Exception)
            {
            } // try
            return (false);
        }
        #endregion

        #region Methods
        public static MethodInfo[] GetMethods(object obj)
        {
            MethodInfo[] methods = new MethodInfo[0];
            try
            {
                methods = obj.GetType().GetMethods();
            }
            catch (Exception)
            {
            } // try
            return (methods);
        }

        public static MethodInfo[] GetMethods(object obj, BindingFlags flags)
        {
            MethodInfo[] methods = new MethodInfo[0];
            try
            {
                methods = obj.GetType().GetMethods(flags);
            }
            catch (Exception)
            {
            } // try
            return (methods);
        }

        public static IRequestResult ExecuteMethod_RequestResult(object obj, object[] parameters, string method)
        {
            try
            {
                MethodInfo mi = obj.GetType().GetMethod(method);
                if (mi != null)
                {
                    return (mi.Invoke(obj, parameters) as IRequestResult);
                } // if
            }
            catch (TargetInvocationException tie)
            {
                // TargeInvocationException means that the called method fired an exception internally and the InnerException
                // is holding the exception information. In this case, InteractiveSdkException.
                if (tie.InnerException.GetType() == typeof(InteractiveSdkException))
                {
                    return ((tie.InnerException as InteractiveSdkException).SdkRequestResult);
                } // if
            }
            catch (Exception)
            {
            } // try
            return (default(IRequestResult));
        }
        #endregion

        #region Parameters
        public static ParameterInfo[] GetParameters(object obj, string method)
        {
            ParameterInfo[] parameters = new ParameterInfo[0];
            try
            {
                MethodInfo mi = obj.GetType().GetMethod(method);
                if (mi != null)
                {
                    parameters = mi.GetParameters();
                } // if
            }
            catch (Exception)
            {
            } // try
            return (parameters);
        }

        public static bool HasInputParameters(object obj, string method)
        {
            ParameterInfo[] parameters = new ParameterInfo[0];
            int param_count = 0;
            try
            {
                MethodInfo mi = obj.GetType().GetMethod(method);
                if (mi != null)
                {
                    parameters = mi.GetParameters();
                    // check for ByRef && OUT parameters, as these don't count when displaying the parameter entry window
                    foreach (ParameterInfo i in parameters)
                    {
                        if ((i.ParameterType.IsByRef == true) && (i.IsOut == true))
                        {
                            continue;
                        }
                        param_count++;
                    }
                } // if
            }
            catch (Exception)
            {
            } // try
            return (((param_count > 0) ? true : false));
        }
        #endregion
    }

    public class ListViewNF : System.Windows.Forms.ListView
    {
        [DllImport("uxtheme.dll", CharSet = CharSet.Unicode)]
        private extern static int SetWindowTheme(IntPtr hWnd, string pszSubAppName, string pszSubIdList);

        public ListViewNF()
        {
            //Activate double buffering 
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint, true);

            //Enable the OnNotifyMessage event so we get a chance to filter out  
            // Windows messages before they get to the form's WndProc 
            this.SetStyle(ControlStyles.EnableNotifyMessage, true);
        }

        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);

            SetWindowTheme(this.Handle, "explorer", null);
        }

        protected override void OnNotifyMessage(Message m)
        {
            //Filter out the WM_ERASEBKGND message 
            if (m.Msg != 0x14)
            {
                base.OnNotifyMessage(m);
            }
        }
    }

    public class TreeViewEx : System.Windows.Forms.TreeView
    {
        [DllImport("uxtheme.dll", CharSet = CharSet.Unicode)]
        private extern static int SetWindowTheme(IntPtr hWnd, string pszSubAppName, string pszSubIdList);

        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);

            SetWindowTheme(this.Handle, "explorer", null);
        }

        //protected override void OnDrawNode(System.Windows.Forms.DrawTreeNodeEventArgs e)
        //{
        //    base.OnDrawNode(e);
        //}
    }


}
