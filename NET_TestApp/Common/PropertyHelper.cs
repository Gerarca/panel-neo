using System;
using System.Diagnostics;

using DSC.Automation.DataHelpers;
using DSC.Automation.TextHelpers;
using DSC.Automation.CustomProperties;

namespace NET_TestApp
{
    class PropertyHelper
    {
        #region Static Methods
        public static void StoreProperties(
            ParamParser clsParams, IDataCollection<IPropertyData> clsProperties)
        {
            //sanity check
            Debug.Assert(clsParams != null, "[PropertyHelper::StoreProperties] Debug.Assert(clsParams != null)");

            //check if properties collection is present
            if (clsProperties != null)
            {
                //add all properties
                for (int i = 0; i < clsProperties.Count; ++i)
                {
                    //get property data
                    IPropertyData clsData = clsProperties[i];

                    //check if the value should be re-generated during run-time
                    if (clsData.Generator != String.Empty)
                    {
                        //instantiate generator
                        IDataGenerator clsGenerator =
                            clsData.ClassFactory.CreateInstance<IDataGenerator>(clsData.Generator);

                        //generate new value
                        clsData.Value = clsGenerator.GetValue(null);
                    }

                    //sync property value
                    if (clsData.Synchronize())
                    {
                        //add property data
                        clsParams.AddValue(clsData.Name, clsData.Image);
                    }
                }
            }
        }

        public static void FetchProperties(
            ParamParser clsParams, IDataCollection<IPropertyData> clsProperties)
        {
            //sanity check
            Debug.Assert(clsParams != null, "[PropertyHelper::FetchProperties] Debug.Assert(clsParams != null)");

            //check if properties collection is present
            if (clsProperties != null)
            {
                //add all properties
                for (int i = 0; i < clsProperties.Count; ++i)
                {
                    //get property data
                    IPropertyData clsData = clsProperties[i];
                    if (clsParams.Contains(clsData.Name))
                    {
                        ////check if the value should be re-generated during run-time
                        //if (clsData.Generator != String.Empty)
                        //{
                        //    //instantiate generator
                        //    IDataGenerator clsGenerator =
                        //        clsData.ClassFactory.CreateInstance<IDataGenerator>(clsData.Generator);

                        //    //generate new value
                        //    clsData.Value = clsGenerator.GetValue(null);
                        //}
                        //else
                        //{
                        //update property value image
                        clsData.Image = clsParams.GetValue(clsData.Name);
                        //}

                        //sync property value
                        if (!clsData.Synchronize())
                        {
                            //bad data
                            Debug.Assert(false, "[PropertyHelper::FetchProperties] !clsData.Synchronize()");
                        }
                    }
                }
            }
        }
        #endregion Static Methods

        #region Private Members
        private PropertyContainer _clsPropertyContainer = new PropertyContainer();

        //event handlers
        private PropertyEventHandler _ehValidateValue = null;
        private PropertyEventHandler _ehValueChanged = null;
        private PropertyEventHandler _ehLaunchEditor = null;
        #endregion Private Members

        #region Construction
        public PropertyHelper()
        {
            _ehValidateValue = new PropertyEventHandler(OnValidateValue);
            _ehValueChanged = new PropertyEventHandler(OnValueChanged);
            _ehLaunchEditor = new PropertyEventHandler(OnLaunchEditor);
        }
        #endregion Construction

        #region Events
        public event PropertyEventHandler PropertyChangedEvent = null;
        #endregion Events

        #region Properties
        public PropertyContainer Properties
        {
            get { return _clsPropertyContainer; }
        }
        #endregion Properties

        #region Public Methods
        public void Clear()
        {
            //clear all custom properties
            _clsPropertyContainer.Clear();
        }

        public bool AddProperty(IPropertyData clsProperty, bool flgReadOnly)
        {
            if ((clsProperty == null) || !clsProperty.Synchronize())
            {
                //cannot add this property because it is invalid
                return false;
            }

            //add property
            switch (clsProperty.DataType)
            {
                case DataType.ArrayOfBoolean:
                case DataType.ArrayOfByte:
                case DataType.ArrayOfChar:
                case DataType.ArrayOfDateTime:
                case DataType.ArrayOfDecimal:
                case DataType.ArrayOfDouble:
                case DataType.ArrayOfInt16:
                case DataType.ArrayOfInt32:
                case DataType.ArrayOfInt64:
                case DataType.ArrayOfSByte:
                case DataType.ArrayOfSingle:
                case DataType.ArrayOfString:
                case DataType.ArrayOfUInt16:
                case DataType.ArrayOfUInt32:
                case DataType.ArrayOfUInt64:
                    return AddArrayProperty(clsProperty, flgReadOnly);

                case DataType.Boolean:
                case DataType.Byte:
                case DataType.Char:
                case DataType.DateTime:
                case DataType.Decimal:
                case DataType.Double:
                case DataType.Int16:
                case DataType.Int32:
                case DataType.Int64:
                case DataType.SByte:
                case DataType.Single:
                case DataType.String:
                case DataType.UInt16:
                case DataType.UInt32:
                case DataType.UInt64:
                    return AddSimpleProperty(clsProperty, flgReadOnly);

                case DataType.Object:
                    //do not setup such a properties
                    break;
            }
            Debug.Assert(false, "[PropertyHelper::AddProperty] Unsupported property type!");	//it should never come here
            return false;
        }

        public void AddProperties(IDataCollection<IPropertyData> lstProperties, bool flgReadOnly)
        {
            if (lstProperties != null)
            {
                for (int i = 0; i < lstProperties.Count; ++i)
                {
                    IPropertyData clsProp = lstProperties[i];
                    if (clsProp != null)
                    {
                        AddProperty(clsProp, flgReadOnly);
                    }
                }
            }
        }

        public IPropertyData RemoveProperty(IPropertyInfo clsProperty)
        {
            //get the qualified name of the property
            string strName = GetPropertyName(clsProperty);

            //delete custom property
            CustomProperty clsCustom = Properties.Remove(strName);
            if (clsCustom != null)
            {
                //return the property data
                return clsCustom.UserData as IPropertyData;
            }
            //custom property not found
            return null;
        }

        public void RemoveProperties(IDataCollection<IPropertyData> lstProperties)
        {
            if (lstProperties != null)
            {
                for (int i = 0; i < lstProperties.Count; ++i)
                {
                    IPropertyData clsProp = lstProperties[i];
                    if (clsProp != null)
                    {
                        RemoveProperty(clsProp);
                    }
                }
            }
        }

        public void RestoreProperties(IDataCollection<IPropertyData> lstProperties)
        {
            //check all stored properties
            for (int i = Properties.Count - 1; i >= 0; --i)
            {
                //get custom property
                CustomProperty clsCustom = Properties[i];
                if (clsCustom != null)
                {
                    //get user data
                    IPropertyData clsProp = clsCustom.UserData as IPropertyData;
                    if (clsProp != null)
                    {
                        //check if the reference collection contains the property
                        if (lstProperties.Contains(clsProp))
                        {
                            //move to the next property
                            continue;
                        }
                    }
                }

                //delete property
                Properties.RemoveAt(i);
            }
        }
        #endregion Public Methods

        #region Event Handlers
        private void OnValidateValue(object sender, PropertyEventArgs args)
        {
            CustomProperty clsCustom = sender as CustomProperty;
            if (clsCustom != null)
            {
                //synchronize data holder
                if (args.NewData.Synchronize())
                {
                    //treat string properties in a special way
                    if (args.NewData.Type == typeof(string))
                    {
                        //trim the string
                        args.NewData.Image = args.NewData.Image.Trim();
                        args.NewData.Synchronize(); //re-synchronize
                    }

                    //get property data reference
                    IPropertyData clsData = clsCustom.UserData as IPropertyData;
                    Debug.Assert(clsData != null, "[PropertyHelper::OnValidateValue] Debug.Assert(clsData != null)");

                    //check if the new image can be synchronized
                    string strImage = String.Empty;
                    IDataConverter clsConverter =
                        clsData.ClassFactory.CreateInstance<IDataConverter>(clsData.Converter);
                    if (!DataHelper.ToImage(clsData.DataType, args.NewData.Value, clsConverter, out strImage))
                    {
                        //the new value cannot be synced - restore the original value
                        args.NewData.Value = args.OldData.Value;
                    }
                }
                else
                {
                    //restore the original value
                    args.NewData.Value = args.OldData.Value;
                }
            }
        }

        private void OnValueChanged(object sender, PropertyEventArgs args)
        {
            CustomProperty clsCustom = sender as CustomProperty;
            if (clsCustom != null)
            {
                //sync custom property data
                if (clsCustom.Data.Synchronize())
                {
                    //get property data reference
                    IPropertyData clsData = clsCustom.UserData as IPropertyData;
                    Debug.Assert(clsData != null, "[PropertyHelper::OnValueChanged] Debug.Assert(clsData != null)");

                    //update property data
                    clsData.Image = clsCustom.Data.Image;
                    if (clsData.Synchronize())
                    {
                        if (PropertyChangedEvent != null)
                        {
                            //notify about property changes
                            PropertyChangedEvent(clsData, args);
                        }
                    }
                    else
                    {
                        Debug.Assert(false, "[PropertyHelper::OnValueChanged] !clsData.Synchronize()");
                    }
                }
                else
                {
                    //couldn't sync daya
                    Debug.Assert(false, "[PropertyHelper::OnValueChanged] !clsCustom.Data.Synchronize()");
                }
            }
        }

        private void OnLaunchEditor(object sender, PropertyEventArgs args)
        {
            CustomProperty clsCustom = sender as CustomProperty;
            if (clsCustom != null)
            {
                //get property data reference
                IPropertyData clsData = clsCustom.UserData as IPropertyData;
                Debug.Assert(clsData != null, "[PropertyHelper::OnLaunchEditor] Debug.Assert(clsData != null)");
                if (clsData != null)
                {
                    //create copy of the property data - do not edit the original user data!
                    IPropertyData clsTemp = clsData.Clone() as IPropertyData;
                    Debug.Assert(clsTemp != null, "[PropertyHelper::OnLaunchEditor] Debug.Assert(clsTemp != null)");

                    //launch custom property editor
                    if (clsTemp.LaunchEditor())
                    {
                        //synchronize edited data
                        if (clsTemp.Synchronize())
                        {
                            //update custom property data
                            args.NewData.Image = clsTemp.Image;
                            if (!args.NewData.Synchronize())
                            {
                                Debug.Assert(false, "[PropertyHelper::OnLaunchEditor] Debug.Assert(args.NewData.Synchronize())");
                            }

                            //Warning: since the clsTemp.Value and args.NewData.Value data types
                            //may be different, it is safer to use value images for updating data
                            //and then syncing the value with image.
                        }
                        else
                        {
                            Debug.Assert(false, "[PropertyHelper::OnLaunchEditor] Debug.Assert(clsTemp.Synchronize())");
                        }
                    }
                }
            }
        }
        #endregion Event Handlers

        #region Private Methods
        private string GetPropertyName(IPropertyInfo clsProperty)
        {
            //make sure the custom property name is unique within the given category
            return String.Format("{0}\\{1}", clsProperty.Category, clsProperty.Name);
        }

        private void SetPropertyData(
            CustomProperty clsCustom, IPropertyData clsProperty, bool flgReadOnly)
        {
            //copy property data
            clsCustom.Order = clsProperty.Ordinal;
            clsCustom.Category = clsProperty.Category;
            clsCustom.DisplayName = clsProperty.Label;
            clsCustom.Description = clsProperty.Description;
            clsCustom.IsBrowsable = clsProperty.IsBrowsable;
            clsCustom.IsReadOnly = (flgReadOnly) ? true : clsProperty.IsReadOnly;   //overwrite ReadOnly if necessary
            clsCustom.IsGuarded = clsProperty.IsGuarded;
            clsCustom.IsPassword = clsProperty.IsPassword;
            clsCustom.EditorEnabled = (flgReadOnly) ? false : clsProperty.EditorEnabled;    //overwrite EditorEnabled if necessary

            //load property icon bitmap if required
            if (clsProperty.IconEnabled &&
                (clsProperty.PropertyIcon != String.Empty))
            {
                //try loading image
                ImageLoader clsImageLoader = new ImageLoader();
                if (clsImageLoader.Load(clsProperty.PropertyIcon))
                {
                    //store image
                    clsCustom.Image = clsImageLoader.Image;
                }
                else
                {
                    //cannot load image
                    //Messages.ShowFailureText("PropertyHelper::SetPropertyData",
                    //    String.Format(Messages.ErrCannotLoadImage, clsProperty.PropertyIcon));
                }
            }

            //cross link the custom property with 
            //the property data container
            clsCustom.UserData = clsProperty;
            clsProperty.Tag = clsCustom;

            //connect the events
            clsCustom.ValidateValueEvent += _ehValidateValue;
            clsCustom.ValueChangedEvent += _ehValueChanged;
            clsCustom.LaunchEditorEvent += _ehLaunchEditor;

            //setup custom property data converter
            clsCustom.Data.Converter =
                clsProperty.ClassFactory.CreateInstance<IPropertyDataConverter>(clsProperty.Converter);
        }

        private bool AddSimpleProperty(IPropertyData clsProperty, bool flgReadOnly)
        {
            //get the qualified name of the property
            string strName = GetPropertyName(clsProperty);

            //create custom property of type string
            CustomProperty clsCustom = (Properties.Contains(strName)) ?
                Properties.GetProperty(strName) : Properties.AddProperty(strName, typeof(string));
            Debug.Assert(clsCustom != null, "[PropertyHelper::AddSimpleProperty] Debug.Assert(clsCustom != null)");
            if (clsCustom == null) return false;

            //setup data
            SetPropertyData(clsCustom, clsProperty, flgReadOnly);

            //determine valid values if necessary
            if (clsProperty.DataCollector != String.Empty)
            {
                //clear current valid values
                clsProperty.ValidValues.Clear();

                //create data collector
                IDataCollector clsCollector =
                    clsProperty.ClassFactory.CreateInstance<IDataCollector>(clsProperty.DataCollector);
                if (clsCollector != null)
                {
                    //collect valid values during runtime
                    IGenericCollection<INamedValue> clsValues = clsCollector.Execute(null);
                    if (clsValues != null)
                    {
                        //update valid values collection
                        clsProperty.ValidValues.AddRange(clsValues);
                    }
                }
            }

            //setup valid values if necessary
            for (int i = 0; i < clsProperty.ValidValues.Count; ++i)
            {
                INamedValue clsValue = clsProperty.ValidValues[i];
                Debug.Assert(clsValue != null, "[PropertyHelper::AddSimpleProperty] Debug.Assert(clsValue != null)");
                if ((clsValue != null) && (clsValue.Value != null))
                {
                    string strImage = String.Empty;
                    IDataConverter clsConverter =
                        clsProperty.ClassFactory.CreateInstance<IDataConverter>(clsProperty.Converter);
                    if (DataHelper.ToImage(clsProperty.DataType, clsValue.Value, clsConverter, out strImage))
                    {
                        clsCustom.AddValidValue(strImage, clsValue.Label);
                    }
                }
            }

            //set the custom property value
            clsCustom.Data.SetImage(clsProperty.Image);
            return clsCustom.Data.Synchronize();
        }

        private bool AddArrayProperty(IPropertyData clsProperty, bool flgReadOnly)
        {
            //get the qualified name of the property
            string strName = GetPropertyName(clsProperty);

            //create custom property of type string
            CustomProperty clsCustom = (Properties.Contains(strName)) ?
                Properties.GetProperty(strName) : Properties.AddProperty(strName, typeof(string));
            Debug.Assert(clsCustom != null, "[PropertyHelper::AddArrayProperty] Debug.Assert(clsCustom != null)");
            if (clsCustom == null) return false;

            //setup data
            SetPropertyData(clsCustom, clsProperty, flgReadOnly);

            //set the custom property value
            clsCustom.Data.SetImage(clsProperty.Image);
            return clsCustom.Data.Synchronize();
        }
        #endregion Private Methods
    }
}
