#include "Application.h"
#include "Debug.hpp"
#include "TextString.hpp"
#include "HexHelper.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#if defined(WINDOWS)
#include <conio.h>
#include <cstdio>
#elif defined(LINUX)
#include <unistd.h>
#include <cstdio>
#include "LinuxIO.h"
#define Sleep(a) usleep(a * 1000)
#define _snprintf snprintf
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4996)
#elif defined(GCC_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#else
#error "Undefined compiler information!"
#endif  //MS_VS_COMPILER

//---------------------------------------------------------------------------

VOID CApplication::DisplayMainMenu(VOID)
{
	printf("TESTAPP:\n");
	printf("Press '%c' for SystemManager.\n", APP_SYSTEM_MANAGER_CHAR);
	printf("Press '%c' for PartitionManager.\n", APP_PARTITION_MANAGER_CHAR);
	printf("Press '%c' for SpecificFunctions.\n", APP_SPECIFIC_FUNCTIONS_CHAR);
	printf("Press '%c' to  ReadSystemInformation().\n", APP_READ_SYSTEM_INFORMATION_CHAR);
	printf("Press '%c' to  ReadSystemCapabilities().\n", APP_READ_SYSTEM_CAPABILITIES_CHAR);
	printf("Press '%c' to  ReadTroubleInformation().\n", APP_READ_TROUBLE_INFORMATION_CHAR);
	printf("Press '%c' to  Quit.\n", APP_QUIT_CHAR);
}

VOID CApplication::DisplaySystemManagerMenu(VOID)
{
	printf("SYSTEM MANAGER:\n");
	printf("Press '%c' to  Refresh().\n", APP_SYSTEM_MANAGER_REFRESH_CHAR);
	printf("Press '%c' to  get_TroubleStatus().\n", APP_SYSTEM_MANAGER_GET_TROUBLE_STATUS_CHAR);
	printf("Press '%c' to  ReadSystemDateTime().\n", APP_SYSTEM_MANAGER_READ_SYSTEM_DATE_TIME_CHAR);
	printf("Press '%c' to  WriteSystemDateTime().\n", APP_SYSTEM_MANAGER_WRITE_SYSTEM_DATE_TIME_CHAR);
	printf("Press '%c' to  get_VirtualZoneManager().\n", APP_SYSTEM_MANAGER_GET_VIRTUAL_ZONE_MANAGER_CHAR);
	printf("Press '%c' to  ReadAccessCodePartitionAssignments().\n", APP_SYSTEM_MANAGER_READ_ACCESS_CODE_ASSIGNMENTS_CHAR);
	printf("Press '%c' to  AddAccessCodeToPartitions().\n", APP_SYSTEM_MANAGER_ADD_ACCESS_CODE_ASSIGNMENTS_CHAR);
	printf("Press '%c' to  RemoveAccessCodeFromPartitions().\n", APP_SYSTEM_MANAGER_REMOVE_ACCESS_CODE_ASSIGNMENTS_CHAR);
	printf("Press '%c' to  get_VirtualKeypadManager().\n", APP_SYSTEM_MANAGER_VIRTUAL_KEYPAD_MANAGER_CHAR);
	printf("Press '%c' to  get_AlarmTypes().\n", APP_SYSTEM_MANAGER_GET_ALARM_TYPES_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayVirtualZoneManagerMenu(VOID)
{
	printf("VIRTUAL ZONE MANAGER:\n");
	printf("Press '%c' to  Refresh().\n", APP_VIRTUAL_ZONE_MANAGER_REFRESH_CHAR);
	printf("Press '%c' to  get_NumberOfVirtualZones().\n", APP_VIRTUAL_ZONE_MANAGER_GET_NUMBER_OF_VIRTUAL_ZONES_CHAR);
	printf("Press '%c' to  get_VirtualZone().\n", APP_VIRTUAL_ZONE_MANAGER_GET_VIRTUAL_ZONE_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayVirtualKeypadManagerMenu(VOID)
{
	printf("VIRTUAL KEYPAD MANAGER:\n");
	printf("Press '%c' to  Refresh().\n", APP_VIRTUAL_KEYPAD_MANAGER_REFRESH_CHAR);
	printf("Press '%c' to  get_NumberOfVirtualKeypads().\n", APP_VIRTUAL_KEYPAD_MANAGER_GET_NUMBER_OF_VIRTUAL_KEYPADS_CHAR);
	printf("Press '%c' to  get_VirtualKeypad().\n", APP_VIRTUAL_KEYPAD_MANAGER_GET_VIRTUAL_KEYPAD);
	printf("Press '%c' to  NumberOfSupportedVirtualKeypads().\n", APP_VIRTUAL_KEYPAD_MANAGER_NUMBER_OF_SUPPORTED_VIRTUAL_KEYPADS_CHAR);
	printf("Press '%c' to  CreateVirtualKeypad().\n", APP_VIRTUAL_KEYPAD_MANAGER_CREATE_VIRTUAL_KEYPAD_CHAR);
	printf("Press '%c' to  DeleteVirtualKeypad().\n", APP_VIRTUAL_KEYPAD_MANAGER_DELETE_VIRTUAL_KEYPAD_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayVirtualKeypadMenu(VOID)
{
	printf("VIRTUAL KEYPAD:\n");
	printf("Press '%c' to  Configure().\n", APP_VIRTUAL_KEYPAD_CONFIG_CHAR);
	printf("Press '%c' to  Keypress 0.\n", APP_VIRTUAL_KEYPAD_0_CHAR);
	printf("Press '%c' to  Keypress 1.\n", APP_VIRTUAL_KEYPAD_1_CHAR);
	printf("Press '%c' to  Keypress 2.\n", APP_VIRTUAL_KEYPAD_2_CHAR);
	printf("Press '%c' to  Keypress 3.\n", APP_VIRTUAL_KEYPAD_3_CHAR);
	printf("Press '%c' to  Keypress 4.\n", APP_VIRTUAL_KEYPAD_4_CHAR);
	printf("Press '%c' to  Keypress 5.\n", APP_VIRTUAL_KEYPAD_5_CHAR);
	printf("Press '%c' to  Keypress 6.\n", APP_VIRTUAL_KEYPAD_6_CHAR);
	printf("Press '%c' to  Keypress 7.\n", APP_VIRTUAL_KEYPAD_7_CHAR);
	printf("Press '%c' to  Keypress 8.\n", APP_VIRTUAL_KEYPAD_8_CHAR);
	printf("Press '%c' to  Keypress 9.\n", APP_VIRTUAL_KEYPAD_9_CHAR);
	printf("Press '%c' to  Keypress *.\n", APP_VIRTUAL_KEYPAD_STAR_CHAR);
	printf("Press '%c' to  Keypress #.\n", APP_VIRTUAL_KEYPAD_POUND_CHAR);
	printf("Press '%c' to  Keypress >.\n", APP_VIRTUAL_KEYPAD_ARROWR_CHAR);
	printf("Press '%c' to  Keypress <.\n", APP_VIRTUAL_KEYPAD_ARROWL_CHAR);
	printf("Press '%c' to  Keypress F.\n", APP_VIRTUAL_KEYPAD_DOUBLE_FIRE_LONG_CHAR);
	printf("Press '%c' to  Keypress A.\n", APP_VIRTUAL_KEYPAD_DOUBLE_AUX_LONG_CHAR);
	printf("Press '%c' to  Keypress P.\n", APP_VIRTUAL_KEYPAD_DOUBLE_PANIC_LONG_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_VIRTUAL_KEYPAD_GET_SYSTEM_INDEX_CHAR);
	printf("Press '%c' to  get_Partition().\n", APP_VIRTUAL_KEYPAD_GET_PARTITION_CHAR);
	printf("Press '%c' to  get_Mode().\n", APP_VIRTUAL_KEYPAD_GET_MODE_CHAR);
	printf("Press '%c' to  get_Type().\n", APP_VIRTUAL_KEYPAD_GET_TYPE_CHAR);
	printf("Press '%c' to  get_Width().\n", APP_VIRTUAL_KEYPAD_GET_WIDTH_CHAR);
	printf("Press '%c' to  get_Height().\n", APP_VIRTUAL_KEYPAD_GET_HEIGHT_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayVirtualZoneMenu(VOID)
{
	printf("VIRTUAL ZONE:\n");
	printf("Press '%c' to  Refresh().\n", APP_VIRTUAL_ZONE_REFRESH_CHAR);
	printf("Press '%c' to  get_ZoneNumber().\n", APP_VIRTUAL_ZONE_GET_ZONE_NUMBER_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_VIRTUAL_ZONE_GET_SYSTEMINDEX_CHAR);
	printf("Press '%c' to  get_VirtualZoneStatus().\n", APP_VIRTUAL_ZONE_GET_VIRTUAL_ZONE_STATUS_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayVirtualZoneStatusMenu(VOID)
{
	printf("VIRTUAL ZONE STATUS:\n");
	printf("Press '%c' to  Refresh().\n", APP_VIRTUAL_ZONE_REFRESH_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_VIRTUAL_ZONE_STATUS_GET_SYSTEMINDEX_CHAR);
	printf("Press '%c' to  WriteVirtualZoneStatus().\n", APP_VIRTUAL_ZONE_STATUS_WRITE_CHAR);
	printf("Press '%c' to  get_Open().\n", APP_VIRTUAL_ZONE_STATUS_GET_OPEN_CHAR);
	printf("Press '%c' to  get_Tamper().\n", APP_VIRTUAL_ZONE_STATUS_GET_TAMPER_CHAR);
	printf("Press '%c' to  get_Fault().\n", APP_VIRTUAL_ZONE_STATUS_GET_FAULT_CHAR);
	printf("Press '%c' to  get_LowBattery().\n", APP_VIRTUAL_ZONE_STATUS_GET_LOW_BATTERY_CHAR);
	printf("Press '%c' to  get_ACTrouble().\n", APP_VIRTUAL_ZONE_STATUS_GET_AC_TROUBLE_CHAR);
	printf("Press '%c' to  get_Masked().\n", APP_VIRTUAL_ZONE_STATUS_GET_MASKED_CHAR);
	printf("Press '%c' to  set_Open().\n", APP_VIRTUAL_ZONE_STATUS_SET_OPEN_CHAR);
	printf("Press '%c' to  set_Tamper().\n", APP_VIRTUAL_ZONE_STATUS_SET_TAMPER_CHAR);
	printf("Press '%c' to  set_Fault().\n", APP_VIRTUAL_ZONE_STATUS_SET_FAULT_CHAR);
	printf("Press '%c' to  set_LowBattery().\n", APP_VIRTUAL_ZONE_STATUS_SET_LOW_BATTERY_CHAR);
	printf("Press '%c' to  set_ACTrouble().\n", APP_VIRTUAL_ZONE_STATUS_SET_AC_TROUBLE_CHAR);
	printf("Press '%c' to  set_Masked().\n", APP_VIRTUAL_ZONE_STATUS_SET_MASKED_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayPartitionManagerMenu(VOID)
{
	printf("PARTITION MANAGER:\n");
	printf("Press '%c' to  Refresh().\n", APP_PARTITION_MANAGER_REFRESH_CHAR);
	printf("Press '%c' to  get_NumberOfPartitions().\n", APP_PARTITION_MANAGER_GET_NUMBER_OF_PARTITIONS_CHAR);
	printf("Press '%c' to  get_Partition().\n", APP_PARTITION_MANAGER_GET_PARTITION_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayPartitionMenu(VOID)
{
	printf("PARTITION:\n");
	printf("Press '%c' to  Refresh().\n", APP_PARTITION_REFRESH_CHAR);
	printf("Press '%c' to  get_Label().\n", APP_PARTITION_GET_LABEL_CHAR);
	printf("Press '%c' to  get_Enabled().\n", APP_PARTITION_GET_ENABLED_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_PARTITION_GET_SYSTEMINDEX_CHAR);
	printf("Press '%c' to  get_PartitionStateData().\n", APP_PARTITION_GET_PARTITION_STATE_DATA_CHAR);
	printf("Press '%c' to  WritePartitionLabel().\n", APP_PARTITION_WRITE_PARTITION_LABEL_CHAR);
	printf("Press '%c' to  ArmPartitionWithAccessCredentials().\n", APP_PARTITION_ARM_PARTITION_WITH_ACCESS_CREDENTIALS_CHAR);
	printf("Press '%c' to  DisarmPartitionWithAccessCredentials().\n", APP_PARTITION_DISARM_PARTITION_WITH_ACCESS_CREDENTIALS_CHAR);
	printf("Press '%c' to  get_ZoneManager().\n", APP_PARTITION_GET_ZONE_MANAGER_CHAR);
	printf("Press '%c' to  get_AccessCodeManager().\n", APP_PARTITION_GET_ACCESSCODE_MANAGER_CHAR);
	printf("Press '%c' to  SilenceTroubleBeepsForThisPartition().\n", APP_PARTITION_SILENCE_TROUBLE_BEEPS_CHAR);
	printf("Press '%c' to  ActivateFAP(Fire).\n", APP_PARTITION_ACTIVATE_FAP_FIRE_CHAR);
	printf("Press '%c' to  ActivateFAP(Aux).\n", APP_PARTITION_ACTIVATE_FAP_AUX_CHAR);
	printf("Press '%c' to  ActivateFAP(Panic).\n", APP_PARTITION_ACTIVATE_FAP_PANIC_CHAR);
	printf("Press '%c' to  WriteDoorChimeEnabledState().\n", APP_PARTITION_WRITE_DOOR_CHIME_STATE_CHAR);
	printf("Press '%c' to  get_DoorChimeEnabledState().\n", APP_PARTITION_GET_DOOR_CHIME_STATE_CHAR);
	printf("Press '%c' to  ActivateCommandOutput().\n", APP_PARTITION_ACTIVATE_COMMAND_OUTPUT_CHAR);
	printf("Press '%c' to  get_AlarmTypes().\n", APP_PARTITION_GET_ALARM_TYPES_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayZoneManagerMenu(VOID)
{
	printf("ZONE:\n");
	printf("Press '%c' to  Refresh().\n", APP_ZONE_MANAGER_REFRESH_CHAR);
	printf("Press '%c' to  get_NumberOfZones().\n", APP_ZONE_MANAGER_GET_NUMBER_OF_ZONES_CHAR);
	printf("Press '%c' to  get_Zone().\n", APP_ZONE_MANAGER_GET_ZONE_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayAccessCodeManagerMenu(VOID)
{
	printf("ACCESS CODE MANAGER:\n");
	printf("Press '%c' to  Refresh().\n", APP_ACCESSCODE_MANAGER_REFRESH_CHAR);
	printf("Press '%c' to  get_NumberOfAccessCodes().\n", APP_ACCESSCODE_MANAGER_GET_NUMBER_OF_ACESSS_CODES_CHAR);
	printf("Press '%c' to  get_AccessCode().\n", APP_ACCESSCODE_MANAGER_GET_ACCESS_CODE_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayZoneMenu(VOID)
{
	printf("ZONE:\n");
	printf("Press '%c' to  Refresh().\n", APP_ZONE_REFRESH_CHAR);
	printf("Press '%c' to  get_Label().\n", APP_ZONE_GET_LABEL_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_ZONE_GET_SYSTEM_INDEX_CHAR);
	printf("Press '%c' to  get_AlarmInMemoryState().\n", APP_ZONE_GET_ALARM_IN_MEMORY_STATE_CHAR);
	printf("Press '%c' to  get_AlarmState().\n", APP_ZONE_GET_ALARM_STATE_CHAR);
	printf("Press '%c' to  get_BypassState().\n", APP_ZONE_GET_BYPASS_STATE_CHAR);
	printf("Press '%c' to  get_OpenCloseState().\n", APP_ZONE_GET_OPEN_CLOSE_STATE_CHAR);
	printf("Press '%c' to  get_TamperState().\n", APP_ZONE_GET_TAMPER_STATE_CHAR);
	printf("Press '%c' to  get_LowSensitivityState().\n", APP_ZONE_GET_LOW_SENSITIVITY_STATE_CHAR);
	printf("Press '%c' to  get_DelinquencyState().\n", APP_ZONE_GET_DELINQUENCY_STATE_CHAR);
	printf("Press '%c' to  get_LowBatteryState().\n", APP_ZONE_GET_LOWBATT_STATE_CHAR);
	printf("Press '%c' to  get_FaultState().\n", APP_ZONE_GET_FAULT_STATE_CHAR);
	printf("Press '%c' to  get_MaskedState().\n", APP_ZONE_GET_MASKED_STATE_CHAR);
	printf("Press '%c' to  get_Attributes().\n", APP_ZONE_GET_ATTRIBUTES_CHAR);
	printf("Press '%c' to  WriteZoneLabel().\n", APP_ZONE_WRITE_ZONE_LABEL_CHAR);
	printf("Press '%c' to  WriteZoneBypass().\n", APP_ZONE_WRITE_ZONE_BYPASS_CHAR);
	printf("Press '%c' to  get_AlarmTypes().\n", APP_ZONE_GET_ALARM_TYPES_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayZoneAttributesMenu(VOID)
{
	printf("ZONE ATTRIBUTES:\n");
	printf("Press '%c' to  Refresh().\n", APP_ZONE_ATTRIBUTES_REFRESH_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_ZONE_ATTRIBUTES_GET_SYSTEM_INDEX_CHAR); 
	printf("Press '%c' to  WriteZoneAttributes().\n", APP_ZONE_ATTRIBUTES_WRITE_CHAR);
	printf("Press '%c' to  get_ChimeFunction().\n", APP_ZONE_ATTRIBUTES_GET_CHIME_CHAR);
	printf("Press '%c' to  get_BypassEnable().\n", APP_ZONE_ATTRIBUTES_GET_BYPASS_CHAR);
	printf("Press '%c' to  set_ChimeFunction().\n", APP_ZONE_ATTRIBUTES_SET_CHIME_CHAR);
	printf("Press '%c' to  set_BypassEnable().\n", APP_ZONE_ATTRIBUTES_SET_BYPASS_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayAccessCodeMenu(VOID)
{
	printf("ACCESS CODE:\n");
	printf("Press '%c' to  Refresh().\n", APP_ACCESSCODE_REFRESH_CHAR);
	printf("Press '%c' to  get_Value().\n", APP_ACCESSCODE_GET_VALUE_CHAR);
	printf("Press '%c' to  get_Label().\n", APP_ACCESSCODE_GET_LABEL_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_ACCESSCODE_GET_SYSTEM_INDEX_CHAR);
	printf("Press '%c' to  get_Attributes().\n", APP_ACCESSCODE_GET_ATTRIBUTES_CHAR);
	printf("Press '%c' to  get_AccessCodeLength().\n", APP_ACCESSCODE_GET_LENGTH_CHAR);
	printf("Press '%c' to  WriteAccessCodeLabel().\n", APP_ACCESSCODE_WRITE_ACCESS_CODE_LABEL_CHAR);
	printf("Press '%c' to  WriteAccessCodeValue().\n", APP_ACCESSCODE_WRITE_ACCESS_CODE_VALUE_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayAccessCodeAttributesMenu(VOID)
{
	printf("ACCESS CODE ATTRIBUTES:\n");
	printf("Press '%c' to  Refresh().\n", APP_ACCESSCODE_ATTRIBUTES_REFRESH_CHAR);
	printf("Press '%c' to  get_SystemIndex().\n", APP_ACCESSCODE_ATTRIBUTES_GET_SYSTEM_INDEX_CHAR);
	printf("Press '%c' to  WriteAccessCodeAttributes().\n", APP_ACCESSCODE_ATTRIBUTES_WRITE_CHAR);
	printf("Press '%c' to  get_CanBypassZone().\n", APP_ACCESSCODE_ATTRIBUTES_GET_CAN_BYPASS_ZONE_CHAR);
	printf("Press '%c' to  get_RemoteAccess().\n", APP_ACCESSCODE_ATTRIBUTES_GET_REMOTE_ACCESS_CHAR);
	printf("Press '%c' to  get_OneTimeUse().\n", APP_ACCESSCODE_ATTRIBUTES_GET_ONE_TIME_USE_CHAR);
	printf("Press '%c' to  get_BellSquawk().\n", APP_ACCESSCODE_ATTRIBUTES_GET_BELL_SQUAWK_CHAR);
	printf("Press '%c' to  get_Supervisor().\n", APP_ACCESSCODE_ATTRIBUTES_GET_SUPERVISOR_CHAR);
	printf("Press '%c' to  get_DuressCode().\n", APP_ACCESSCODE_ATTRIBUTES_GET_DURESS_CODE_CHAR);
	printf("Press '%c' to  set_CanBypassZone().\n", APP_ACCESSCODE_ATTRIBUTES_SET_CAN_BYPASS_ZONE_CHAR);
	printf("Press '%c' to  set_RemoteAccess().\n", APP_ACCESSCODE_ATTRIBUTES_SET_REMOTE_ACCESS_CHAR);
	printf("Press '%c' to  set_OneTimeUse().\n", APP_ACCESSCODE_ATTRIBUTES_SET_ONE_TIME_USE_CHAR);
	printf("Press '%c' to  set_BellSquawk().\n", APP_ACCESSCODE_ATTRIBUTES_SET_BELL_SQUAWK_CHAR);
	printf("Press '%c' to  set_Supervisor().\n", APP_ACCESSCODE_ATTRIBUTES_SET_SUPERVISOR_CHAR);
	printf("Press '%c' to  set_DuressCode().\n", APP_ACCESSCODE_ATTRIBUTES_SET_DURESS_CODE_CHAR);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplaySpecificFunctionsMenu(VOID)
{
	printf("SPECIFIC FUNCIONS:\n");
	printf("Press '%c' to  ITV2_ChangeIntegrationAccessCode(8-1).\n", APP_SPECIFIC_FUNCTIONS_CHANGE_IAC);
	printf("Press '%c' to  ITV2_ChangeIntegrationAccessCode(1-8).\n", APP_SPECIFIC_FUNCTIONS_DEFAULT_IAC);
	printf("Press '%c' to  ITV2_ReadLifeStyleNotificationSettings().\n", APP_SPECIFIC_FUNCTIONS_READ_LIFESTYLE_NOTIFICATION_SETTINGS);
	printf("Press '%c' to  ITV2_WriteLifeStyleNotificationSettings(Access Code Length = OFF, Chime = OFF).\n", APP_SPECIFIC_FUNCTIONS_WRITE_LIFESTYLE_NOTIFICATION_SETTINGS1);
	printf("Press '%c' to  ITV2_WriteLifeStyleNotificationSettings(Access Code Length = ON, Chime = ON).\n", APP_SPECIFIC_FUNCTIONS_WRITE_LIFESTYLE_NOTIFICATION_SETTINGS2);
	printf("Press '%c' to  ITV2_DefaultLifeStyleNotificationSettings().\n", APP_SPECIFIC_FUNCTIONS_DEFAULT_LIFESTYLE_NOTIFICATION_SETTINGS);
	printf("Press '%c' to  ITV2_ReadZoneNotificationSettings().\n", APP_SPECIFIC_FUNCTIONS_READ_ZONE_NOTIFICATION_SETTINGS);
	printf("Press '%c' to  ITV2_WriteZoneNotificationSettings(Zone 1 = OFF, Zone 8 = OFF).\n", APP_SPECIFIC_FUNCTIONS_WRITE_ZONE_NOTIFICATION_SETTINGS1);
	printf("Press '%c' to  ITV2_WriteZoneNotificationSettings(Zone 1 = ON, Zone 8 = ON).\n", APP_SPECIFIC_FUNCTIONS_WRITE_ZONE_NOTIFICATION_SETTINGS2);
	printf("Press '%c' to  ITV2_DefaultZoneNotificationSettings().\n", APP_SPECIFIC_FUNCTIONS_DEFAULT_ZONE_NOTIFICATION_SETTINGS);
	printf("Press '%c' for Previous Menu.\n", APP_PREVIOUS_MENU_CHAR);
	printf("Press '%c' for Main Menu.\n", APP_MAIN_MENU_CHAR);
}

VOID CApplication::DisplayMenu(VOID)
{
	switch (ui_vars.menulevel)
	{
		case APP_MAIN_MENU:
			DisplayMainMenu();
			break;
		case APP_SYSTEM_MANAGER_MENU:
			DisplaySystemManagerMenu();
			break;
		case APP_VIRTUAL_ZONE_MANAGER_MENU:
			DisplayVirtualZoneManagerMenu();
			break;
		case APP_VIRTUAL_ZONE_MENU:
			DisplayVirtualZoneMenu();
			break;
		case APP_VIRTUAL_ZONE_STATUS_MENU:
			DisplayVirtualZoneStatusMenu();
			break;
		case APP_PARTITION_MANAGER_MENU:
			DisplayPartitionManagerMenu();
			break;
		case APP_PARTITION_MENU:
			DisplayPartitionMenu();
			break;
		case APP_ZONE_MANAGER_MENU:
			DisplayZoneManagerMenu();
			break;
		case APP_ACCESSCODE_MANAGER_MENU:
			DisplayAccessCodeManagerMenu();
			break;
		case APP_ZONE_MENU:
			DisplayZoneMenu();
			break;
		case APP_ZONE_ATTRIBUTES_MENU:
			DisplayZoneAttributesMenu();
			break;
		case APP_ACCESSCODE_MENU:
			DisplayAccessCodeMenu();
			break;
		case APP_ACCESSCODE_ATTRIBUTES_MENU:
			DisplayAccessCodeAttributesMenu();
			break;
		case APP_VIRTUAL_KEYPAD_MANAGER_MENU:
			DisplayVirtualKeypadManagerMenu();
			break;
		case APP_VIRTUAL_KEYPAD_MENU:
			DisplayVirtualKeypadMenu();
			break;
		case APP_SPECIFIC_FUNCTIONS_MENU:
			DisplaySpecificFunctionsMenu();
			break;
		case APP_EXIT_MENU:
			break;
		default:
			break;
	}
}

VOID CApplication::doUIMainMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;
		switch (toupper(_getch()))
		{
			case APP_SYSTEM_MANAGER_CHAR:
				retval = ui_vars.instance->get_SystemManager(ui_vars.system_manager);
				printf("get_SystemManager() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_SYSTEM_MANAGER_MENU;
				}
				break;
			case APP_PARTITION_MANAGER_CHAR:
				retval = ui_vars.instance->get_PartitionManager(ui_vars.partition_manager);
				printf("get_PartitionManager() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_PARTITION_MANAGER_MENU;
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_CHAR:
				retval = ui_vars.instance->get_SpecificFunctions(ui_vars.specific_functions);
				printf("get_SpecificFunctions() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_SPECIFIC_FUNCTIONS_MENU;
				}
				break;
			case APP_READ_SYSTEM_INFORMATION_CHAR:
				{
					TComPtr<DSC_ISystemInformation> systemInformation;
					retval = ui_vars.instance->ReadSystemInformation(systemInformation, result);
					printf("ReadSystemInformation() %s\n", RequestResultToString(result).c_str());
					if(IS_SUCCESS(retval))
					{
						TComPtr<DSC_ITextString> strPeerIdentifier;
						retval = systemInformation->get_PeerIdentifier(strPeerIdentifier);
						if(IS_SUCCESS(retval))
						{
							char const* str_string = NULL;
							retval = strPeerIdentifier->get_String(&str_string);
							if (IS_SUCCESS(retval))
							{
								printf("Peer Identifier = %s\n", str_string);
							}
						}
						TComPtr<DSC_ITextString> strProtocolVersion;
						retval = systemInformation->get_ProtocolVersion(strProtocolVersion);
						if(IS_SUCCESS(retval))
						{
							char const* str_string = NULL;
							retval = strProtocolVersion->get_String(&str_string);
							if (IS_SUCCESS(retval))
							{
								printf("Protocol Version = %s\n", str_string);
							}
						}
						TComPtr<DSC_ITextString> strSoftwareVersion;
						retval = systemInformation->get_SoftwareVersion(strSoftwareVersion);
						if(IS_SUCCESS(retval))
						{
							char const* str_string = NULL;
							retval = strSoftwareVersion->get_String(&str_string);
							if (IS_SUCCESS(retval))
							{
								printf("Software Version = %s\n", str_string);
							}
						}
						TComPtr<DSC_ITextString> strMiscellaneousInfo;
						retval = systemInformation->get_MiscellaneousInfo(strMiscellaneousInfo);
						if(IS_SUCCESS(retval))
						{
							char const* str_string = NULL;
							retval = strMiscellaneousInfo->get_String(&str_string);
							if (IS_SUCCESS(retval))
							{
								printf("Miscellaneous Info = %s\n", str_string);
							}
						}
					}
				}
				break;
			case APP_READ_SYSTEM_CAPABILITIES_CHAR:
				{
					TComPtr<DSC_ISystemCapabilities> systemCapabilities;
					retval = ui_vars.instance->ReadSystemCapabilities(systemCapabilities, result);
					printf("ReadSystemCapabilities() %s\n", RequestResultToString(result).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T value;
						retval = systemCapabilities->get_SupportedAccessCodes(&value);
						if(IS_SUCCESS(retval))
						{
							printf("Supported AccessCodes = %d\n", value);
						}
						retval = systemCapabilities->get_SupportedCommandOutputs(&value);
						if(IS_SUCCESS(retval))
						{
							printf("Supported Command Outputs = %d\n", value);
						}
						retval = systemCapabilities->get_SupportedFOBs(&value);
						if(IS_SUCCESS(retval))
						{
							printf("Supported FOBs = %d\n", value);
						}
						retval = systemCapabilities->get_SupportedPartitions(&value);
						if(IS_SUCCESS(retval))
						{
							printf("Supported Partitions = %d\n", value);
						}
						retval = systemCapabilities->get_SupportedProximityTags(&value);
						if(IS_SUCCESS(retval))
						{
							printf("Supported Proximity Tags = %d\n", value);
						}
						retval = systemCapabilities->get_SupportedZones(&value);
						if(IS_SUCCESS(retval))
						{
							printf("Supported Zones = %d\n", value);
						}
					}
				}
				break;
			case APP_READ_TROUBLE_INFORMATION_CHAR:
				{
					TComPtr<DSC_ITroubleList> troubles;
					retval = ui_vars.instance->ReadTroubleInformation(troubles, result);
					printf("ReadTroubleInformation() %s\n", RequestResultToString(result).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T count;
						retval = troubles->get_NumberOfTroubles(&count);
						if(IS_SUCCESS(retval))
						{
							for(DSC_SIZE_T i = 0; i < count; ++i)
							{
								TComPtr<DSC_ITroubleData> trouble;
								if(IS_FAILURE(troubles->get_TroubleData(i, trouble)))
								{
									continue;
								}

								DSC_DeviceModuleType device_type;
								if(IS_FAILURE(trouble->get_DeviceModuleType(&device_type)))
								{
									continue;
								}

								DSC_TroubleType trouble_type;
								if(IS_FAILURE(trouble->get_TroubleType(&trouble_type)))
								{
									continue;
								}

								DSC_SYSTEM_INDEX device_number;
								if(IS_FAILURE(trouble->get_DeviceModuleNumber(&device_number)))
								{
									continue;
								}

								DSC_TroubleState state;
								if(IS_FAILURE(trouble->get_TroubleStatus(&state)))
								{
									continue;
								}

								printf("DeviceType = %d DeviceNumber = %d TroubleType = %d TroubleState = %d\n", device_type, device_number, trouble_type, state);
							}
						}
					}
				}
				break;
			case APP_QUIT_CHAR:
				ui_vars.menulevel = APP_EXIT_MENU;
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUISystemManagerMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_SYSTEM_MANAGER_REFRESH_CHAR:
				retval = ui_vars.system_manager->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_SYSTEM_MANAGER_GET_TROUBLE_STATUS_CHAR:
				BOOL flgPresent;
				retval = ui_vars.system_manager->get_TroublePresent(&flgPresent);
				printf("get_TroublePresent() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Trouble Present = %s\n", ((flgPresent == TRUE) ? "YES" : "NO"));
				}
				break;
			case APP_SYSTEM_MANAGER_READ_SYSTEM_DATE_TIME_CHAR:
				{
					TComPtr<DSC_ITextString> strSystemDateTime;
					retval = ui_vars.system_manager->ReadSystemTimeDate(ui_vars.user_credentials, strSystemDateTime, result);
					printf("ReadSystemTimeData() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						char const* strtimedate = NULL;
						retval = strSystemDateTime->get_String(&strtimedate);
						printf("get_String() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("System Time Date = %s\n", strtimedate);
						}
					}
				}
				break;
			case APP_SYSTEM_MANAGER_WRITE_SYSTEM_DATE_TIME_CHAR:
				retval = ui_vars.system_manager->WriteSystemTimeDate(ui_vars.user_credentials, "2021-01-01T8:30:30", result);
				printf("WriteSystemTimeDate() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_SYSTEM_MANAGER_GET_VIRTUAL_ZONE_MANAGER_CHAR:
				retval = ui_vars.system_manager->get_VirtualZoneManager(ui_vars.virtual_zone_manager);
				printf("get_VirtualZoneManager() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_VIRTUAL_ZONE_MANAGER_MENU;
				}
				break;
			case APP_SYSTEM_MANAGER_READ_ACCESS_CODE_ASSIGNMENTS_CHAR:
				{
					TComPtr<DSC_ISystemIndices> partitionIndexes;
					retval = ui_vars.system_manager->ReadAccessCodePartitionAssignments(ui_vars.user_credentials, 2, partitionIndexes, result);
					printf("ReadAccessCodePartitionAssignments() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Partitions Access Code 2 Is Assigned To:\n");
						DSC_SIZE_T count;
						retval = partitionIndexes->get_Size(&count);
						printf("get_Size() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							for (DSC_SIZE_T i = 0; i < count; ++i)
							{
								DSC_SYSTEM_INDEX partition;
								retval = partitionIndexes->get_Index(i, &partition);
								printf("get_Index() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
								if (IS_SUCCESS(retval))
								{
									printf("Partition %d\n", partition);
								}
							}
						}
					}
				}
				break;
			case APP_SYSTEM_MANAGER_ADD_ACCESS_CODE_ASSIGNMENTS_CHAR:
				{
					DSC_SYSTEM_INDEX partitionIndexes[2];
					partitionIndexes[0] = 2;
					partitionIndexes[1] = 3;
					retval = ui_vars.system_manager->AddAccessCodeToPartitions(ui_vars.user_credentials, 2, partitionIndexes, 2, result);
					printf("AddAccessCodeToPartitions() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Access Code #2 added to Partitions 2&3\n");
					}
				}
				break;
			case APP_SYSTEM_MANAGER_REMOVE_ACCESS_CODE_ASSIGNMENTS_CHAR:
				{
					DSC_SYSTEM_INDEX partitionIndexes[2];
					partitionIndexes[0] = 2;
					partitionIndexes[1] = 3;
					retval = ui_vars.system_manager->RemoveAccessCodeFromPartitions(ui_vars.user_credentials, 2, partitionIndexes, 2, result);
					printf("RemoveAccessCodeFromPartitions() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Access Code #2 removed from Partitions 2&3\n");
					}
				}
				break;
			case APP_SYSTEM_MANAGER_VIRTUAL_KEYPAD_MANAGER_CHAR:
				retval = ui_vars.system_manager->get_VirtualKeypadManager(ui_vars.virtual_keypad_manager);
				printf("get_VirtualKeypadManager() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_VIRTUAL_KEYPAD_MANAGER_MENU;
				}
				break;
			case APP_SYSTEM_MANAGER_GET_ALARM_TYPES_CHAR:
				{
					TComPtr<DSC_IAlarmTypeContainer> alarms;
					retval = ui_vars.system_manager->get_AlarmTypes(alarms);
					printf("get_AlarmTypes() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T count;
						if (IS_SUCCESS(alarms->get_NumberOfAlarmTypes(&count)))
						{
							for (DSC_SIZE_T i = 0; i < count; ++i)
							{
								DSC_AlarmType type;
								if (IS_FAILURE(alarms->get_AlarmType(i, &type)))
								{
									continue;
								}
								printf("SystemManager AlarmType = %d\n", type);
							}
						}
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup system manager
				if (FALSE == ui_vars.system_manager.IsNull())
				{
					ui_vars.system_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIVirtualZoneManagerMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_VIRTUAL_ZONE_MANAGER_REFRESH_CHAR:
				retval = ui_vars.virtual_zone_manager->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_ZONE_MANAGER_GET_NUMBER_OF_VIRTUAL_ZONES_CHAR:
				UINT32 numVirtualZones;
				retval = ui_vars.virtual_zone_manager->get_NumberOfVirtualZones(&numVirtualZones);
				printf("get_NumberOfVirtualZones() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Number Of Virtual Zones = %d\n", numVirtualZones);
				}
				break;
			case APP_VIRTUAL_ZONE_MANAGER_GET_VIRTUAL_ZONE_CHAR:
				retval = ui_vars.virtual_zone_manager->get_VirtualZone(0, ui_vars.virtual_zone);
				printf("get_VirtualZone() For Virtual Zone1 [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_VIRTUAL_ZONE_MENU;
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_SYSTEM_MANAGER_MENU;
				// cleanup virtual zone manager
				if (FALSE == ui_vars.virtual_zone_manager.IsNull())
				{
					ui_vars.virtual_zone_manager.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup virtual zone manager
				if (FALSE == ui_vars.virtual_zone_manager.IsNull())
				{
					ui_vars.virtual_zone_manager.Clear();
				}
				// cleanup system manager
				if (FALSE == ui_vars.system_manager.IsNull())
				{
					ui_vars.system_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIVirtualZoneMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_VIRTUAL_ZONE_REFRESH_CHAR:
				retval = ui_vars.virtual_zone->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_ZONE_GET_ZONE_NUMBER_CHAR:
				UINT32 numZoneNumber;
				retval = ui_vars.virtual_zone->get_ZoneNumber(&numZoneNumber);
				printf("get_ZoneNumber() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone Number = %d\n", numZoneNumber);
				}
				break;
			case APP_VIRTUAL_ZONE_GET_SYSTEMINDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.virtual_zone->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_VIRTUAL_ZONE_GET_VIRTUAL_ZONE_STATUS_CHAR:
				retval = ui_vars.virtual_zone->get_VirtualZoneStatus(ui_vars.virtual_zone_status);
				printf("get_VirtualZoneStatus() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_VIRTUAL_ZONE_STATUS_MENU;
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_VIRTUAL_ZONE_MANAGER_MENU;
				// cleanup virtual zone
				if (FALSE == ui_vars.virtual_zone.IsNull())
				{
					ui_vars.virtual_zone.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup virtual zone
				if (FALSE == ui_vars.virtual_zone.IsNull())
				{
					ui_vars.virtual_zone.Clear();
				}
				// cleanup virtual zone manager
				if (FALSE == ui_vars.virtual_zone_manager.IsNull())
				{
					ui_vars.virtual_zone_manager.Clear();
				}
				// cleanup system manager
				if (FALSE == ui_vars.system_manager.IsNull())
				{
					ui_vars.system_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIVirtualZoneStatusMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_VIRTUAL_ZONE_STATUS_REFRESH_CHAR:
				retval = ui_vars.virtual_zone_status->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_SYSTEMINDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.virtual_zone_status->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_WRITE_CHAR:
				retval = ui_vars.virtual_zone_status->WriteVirtualZoneStatus(result);
				printf("WriteVirtualZoneStatus() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_OPEN_CHAR:
				{
					DSC_VirtualZoneStatusOpenState state;
					retval = ui_vars.virtual_zone_status->get_Open(&state);
					printf("get_Open() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Open: %s\n", ((DSC_VirtualZoneStatusOpenStates::Opened == state) ? "TRUE" : "FALSE"));
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_TAMPER_CHAR:
				{
					DSC_VirtualZoneStatusTamperState state;
					retval = ui_vars.virtual_zone_status->get_Tamper(&state);
					printf("get_Tamper() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Tamper: %s\n", ((DSC_VirtualZoneStatusTamperStates::Tamper == state) ? "TRUE" : "FALSE"));
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_FAULT_CHAR:
				{
					DSC_VirtualZoneStatusFaultState state;
					retval = ui_vars.virtual_zone_status->get_Fault(&state);
					printf("get_Fault() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Fault: %s\n", ((DSC_VirtualZoneStatusFaultStates::Fault == state) ? "TRUE" : "FALSE"));
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_LOW_BATTERY_CHAR:
				{
					DSC_VirtualZoneStatusLowBatteryState state;
					retval = ui_vars.virtual_zone_status->get_LowBattery(&state);
					printf("get_LowBattery() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("LowBattery: %s\n", ((DSC_VirtualZoneStatusLowBatteryStates::Low_Battery == state) ? "TRUE" : "FALSE"));
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_AC_TROUBLE_CHAR:
				{
					DSC_VirtualZoneStatusACTroubleState state;
					retval = ui_vars.virtual_zone_status->get_ACTrouble(&state);
					printf("get_ACTrouble() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("ACTrouble: %s\n", ((DSC_VirtualZoneStatusACTroubleStates::AC_Trouble == state) ? "TRUE" : "FALSE"));
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_GET_MASKED_CHAR:
				{
					DSC_VirtualZoneStatusMaskedState state;
					retval = ui_vars.virtual_zone_status->get_Masked(&state);
					printf("get_Masked() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Masked: %s\n", ((DSC_VirtualZoneStatusMaskedStates::Masked == state) ? "TRUE" : "FALSE"));
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_SET_OPEN_CHAR:
				{
					DSC_VirtualZoneStatusOpenState state;
					retval = ui_vars.virtual_zone_status->get_Open(&state);
					printf("get_Open() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_VirtualZoneStatusOpenState toggle = DSC_VirtualZoneStatusOpenStates::Opened;
						if (DSC_VirtualZoneStatusOpenStates::Opened == state)
						{
							toggle = DSC_VirtualZoneStatusOpenStates::Closed;
						}
						retval = ui_vars.virtual_zone_status->set_Open(toggle);
						printf("set_Open() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("%s\n", ((DSC_VirtualZoneStatusOpenStates::Opened == toggle) ? "Opened" : "Closed"));
						}
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_SET_TAMPER_CHAR:
				{
					DSC_VirtualZoneStatusTamperState state;
					retval = ui_vars.virtual_zone_status->get_Tamper(&state);
					printf("get_Tamper() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_VirtualZoneStatusTamperState toggle = DSC_VirtualZoneStatusTamperStates::Tamper;
						if (DSC_VirtualZoneStatusTamperStates::Tamper == state)
						{
							toggle = DSC_VirtualZoneStatusTamperStates::No_Tamper;
						}
						retval = ui_vars.virtual_zone_status->set_Tamper(toggle);
						printf("set_Tamper() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("%s\n", ((DSC_VirtualZoneStatusTamperStates::Tamper == toggle) ? "Tamper ON" : "Tamper OFF"));
						}
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_SET_FAULT_CHAR:
				{
					DSC_VirtualZoneStatusFaultState state;
					retval = ui_vars.virtual_zone_status->get_Fault(&state);
					printf("get_Fault() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_VirtualZoneStatusFaultState toggle = DSC_VirtualZoneStatusFaultStates::Fault;
						if (DSC_VirtualZoneStatusFaultStates::Fault == state)
						{
							toggle = DSC_VirtualZoneStatusFaultStates::No_Fault;
						}
						retval = ui_vars.virtual_zone_status->set_Fault(toggle);
						printf("set_Fault() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("%s\n", ((DSC_VirtualZoneStatusFaultStates::Fault == toggle) ? "Fault ON" : "Fault OFF"));
						}
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_SET_LOW_BATTERY_CHAR:
				{
					DSC_VirtualZoneStatusLowBatteryState state;
					retval = ui_vars.virtual_zone_status->get_LowBattery(&state);
					printf("get_LowBattery() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_VirtualZoneStatusLowBatteryState toggle = DSC_VirtualZoneStatusLowBatteryStates::Low_Battery;
						if (DSC_VirtualZoneStatusLowBatteryStates::Low_Battery == state)
						{
							toggle = DSC_VirtualZoneStatusLowBatteryStates::No_Low_Battery;
						}
						retval = ui_vars.virtual_zone_status->set_LowBattery(toggle);
						printf("set_LowBattery() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("%s\n", ((DSC_VirtualZoneStatusLowBatteryStates::Low_Battery == toggle) ? "LowBattery ON" : "LowBattery OFF"));
						}
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_SET_AC_TROUBLE_CHAR:
				{
					DSC_VirtualZoneStatusACTroubleState state;
					retval = ui_vars.virtual_zone_status->get_ACTrouble(&state);
					printf("get_ACTrouble() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_VirtualZoneStatusACTroubleState toggle = DSC_VirtualZoneStatusACTroubleStates::AC_Trouble;
						if (DSC_VirtualZoneStatusACTroubleStates::AC_Trouble == state)
						{
							toggle = DSC_VirtualZoneStatusACTroubleStates::No_AC_Trouble;
						}
						retval = ui_vars.virtual_zone_status->set_ACTrouble(toggle);
						printf("set_ACTrouble() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("%s\n", ((DSC_VirtualZoneStatusACTroubleStates::AC_Trouble == toggle) ? "ACTrouble ON" : "ACTrouble OFF"));
						}
					}
				}
				break;
			case APP_VIRTUAL_ZONE_STATUS_SET_MASKED_CHAR:
				{
					DSC_VirtualZoneStatusMaskedState state;
					retval = ui_vars.virtual_zone_status->get_Masked(&state);
					printf("get_Masked() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_VirtualZoneStatusMaskedState toggle = DSC_VirtualZoneStatusMaskedStates::Masked;
						if (DSC_VirtualZoneStatusMaskedStates::Masked == state)
						{
							toggle = DSC_VirtualZoneStatusMaskedStates::Not_Masked;
						}
						retval = ui_vars.virtual_zone_status->set_Masked(toggle);
						printf("get_Masked() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("%s\n", ((DSC_VirtualZoneStatusMaskedStates::Masked == toggle) ? "Masked ON" : "Masked OFF"));
						}
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_VIRTUAL_ZONE_MENU;
				// cleanup virtual zone status
				if (FALSE == ui_vars.virtual_zone_status.IsNull())
				{
					ui_vars.virtual_zone_status.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup virtual zone status
				if (FALSE == ui_vars.virtual_zone_status.IsNull())
				{
					ui_vars.virtual_zone_status.Clear();
				}
				// cleanup virtual zone
				if (FALSE == ui_vars.virtual_zone.IsNull())
				{
					ui_vars.virtual_zone.Clear();
				}
				// cleanup virtual zone manager
				if (FALSE == ui_vars.virtual_zone_manager.IsNull())
				{
					ui_vars.virtual_zone_manager.Clear();
				}
				// cleanup system manager
				if (FALSE == ui_vars.system_manager.IsNull())
				{
					ui_vars.system_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIVirtualKeypadManagerMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_VIRTUAL_KEYPAD_MANAGER_REFRESH_CHAR:
				retval = ui_vars.virtual_keypad_manager->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_MANAGER_GET_NUMBER_OF_VIRTUAL_KEYPADS_CHAR:
				UINT32 numVirtualKeypads;
				retval = ui_vars.virtual_keypad_manager->get_NumberOfVirtualKeypads(&numVirtualKeypads);
				printf("get_NumberOfVirtualKeypads() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Number Of Virtual Keypads = %d\n", numVirtualKeypads);
				}
				break;
			case APP_VIRTUAL_KEYPAD_MANAGER_GET_VIRTUAL_KEYPAD:
				retval = ui_vars.virtual_keypad_manager->get_VirtualKeypad(1, ui_vars.virtual_keypad);
				printf("get_VirtualKeypad() For Virtual Keypad 1 [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_VIRTUAL_KEYPAD_MENU;
				}
				break;
			case APP_VIRTUAL_KEYPAD_MANAGER_NUMBER_OF_SUPPORTED_VIRTUAL_KEYPADS_CHAR:
				{
					UINT32 numSupportedVirtualKeypads;
					retval = ui_vars.virtual_keypad_manager->NumberOfSupportedVirtualKeypads(DSC_VirtualKeypadTypes::Character_Matrix_16x2, &numSupportedVirtualKeypads, result);
					printf("NumberOfSupportedVirtualKeypads() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Number Of Supported [Character_Matrix_16x2] Virtual Keypads = %d\n", numSupportedVirtualKeypads);
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_MANAGER_CREATE_VIRTUAL_KEYPAD_CHAR:
				{
					TComPtr<DSC_IVirtualKeypad> vk;
					retval = ui_vars.virtual_keypad_manager->CreateVirtualKeypad(DSC_VirtualKeypadTypes::Character_Matrix_16x2, vk, result);
					printf("CreateVirtualKeypad() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						ui_vars.virtual_keypad = vk;
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_MANAGER_DELETE_VIRTUAL_KEYPAD_CHAR:
				{
					retval = ui_vars.virtual_keypad_manager->DeleteVirtualKeypad(1, result);
					printf("DeleteVirtualKeypad() For Virtual Keypad 1 %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						if (FALSE == ui_vars.virtual_keypad.IsNull())
						{
							ui_vars.virtual_keypad.Clear();
						}
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_SYSTEM_MANAGER_MENU;
				// cleanup virtual keypad manager
				if (FALSE == ui_vars.virtual_keypad_manager.IsNull())
				{
					ui_vars.virtual_keypad_manager.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup virtual keypad manager
				if (FALSE == ui_vars.virtual_keypad_manager.IsNull())
				{
					ui_vars.virtual_keypad_manager.Clear();
				}
				// cleanup system manager
				if (FALSE == ui_vars.system_manager.IsNull())
				{
					ui_vars.system_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIVirtualKeypadMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_VIRTUAL_KEYPAD_CONFIG_CHAR:
				{
					retval = ui_vars.virtual_keypad->Configure(1, DSC_VirtualKeypadModes::Emulator, result);
					printf("Configure() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_VIRTUAL_KEYPAD_0_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_0_Short, result);
				printf("Keypress(Key_0_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_1_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_1_Short, result);
				printf("Keypress(Key_1_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_2_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_2_Short, result);
				printf("Keypress(Key_2_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_3_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_3_Short, result);
				printf("Keypress(Key_3_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_4_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_4_Short, result);
				printf("Keypress(Key_4_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_5_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_5_Short, result);
				printf("Keypress(Key_5_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_6_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_6_Short, result);
				printf("Keypress(Key_6_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_7_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_7_Short, result);
				printf("Keypress(Key_7_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_8_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_8_Short, result);
				printf("Keypress(Key_8_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_9_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_9_Short, result);
				printf("Keypress(Key_9_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_STAR_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_Star_Short, result);
				printf("Keypress(Key_Star_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_POUND_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_Pound_Short, result);
				printf("Keypress(Key_Pound_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_ARROWR_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_ArrowR_Short, result);
				printf("Keypress(Key_ArrowR_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_ARROWL_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_ArrowL_Short, result);
				printf("Keypress(Key_ArrowL_Short) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_DOUBLE_FIRE_LONG_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_FireD_Long, result);
				printf("Keypress(Key_FireD_Long) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_DOUBLE_AUX_LONG_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_AuxD_Long, result);
				printf("Keypress(Key_AuxD_Long) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_DOUBLE_PANIC_LONG_CHAR:
				retval = ui_vars.virtual_keypad->KeyPress(DSC_VirtualKeypadKeys::Key_PanicD_Long, result);
				printf("Keypress(Key_PanicD_Long) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_VIRTUAL_KEYPAD_GET_SYSTEM_INDEX_CHAR:
				{
					UINT32 systemIndex;
					retval = ui_vars.virtual_keypad->get_SystemIndex(&systemIndex);
					printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("System Index = %d\n", systemIndex);
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_GET_PARTITION_CHAR:
				{
					UINT32 partition;
					retval = ui_vars.virtual_keypad->get_Partition(&partition);
					printf("get_Partition() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Partition = %d\n", partition);
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_GET_MODE_CHAR:
				{
					DSC_VirtualKeypadMode mode;
					retval = ui_vars.virtual_keypad->get_Mode(&mode);
					printf("get_Mode() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Mode = %d\n", mode);
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_GET_TYPE_CHAR:
				{
					DSC_VirtualKeypadType type;
					retval = ui_vars.virtual_keypad->get_Type(&type);
					printf("get_Type() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Type = %d\n", type);
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_GET_WIDTH_CHAR:
				{
					UINT32 width;
					retval = ui_vars.virtual_keypad->get_Width(&width);
					printf("get_Width() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Width = %d\n", width);
					}
				}
				break;
			case APP_VIRTUAL_KEYPAD_GET_HEIGHT_CHAR:
				{
					UINT32 height;
					retval = ui_vars.virtual_keypad->get_Height(&height);
					printf("get_Height() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Height = %d\n", height);
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_VIRTUAL_KEYPAD_MANAGER_MENU;
				// cleanup virtual keypad
				if (FALSE == ui_vars.virtual_keypad.IsNull())
				{
					ui_vars.virtual_keypad.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup virtual keypad
				if (FALSE == ui_vars.virtual_keypad.IsNull())
				{
					ui_vars.virtual_keypad.Clear();
				}
				// cleanup virtual keypad manager
				if (FALSE == ui_vars.virtual_keypad_manager.IsNull())
				{
					ui_vars.virtual_keypad_manager.Clear();
				}
				// cleanup system manager
				if (FALSE == ui_vars.system_manager.IsNull())
				{
					ui_vars.system_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIPartitionManagerMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_PARTITION_MANAGER_REFRESH_CHAR:
				retval = ui_vars.partition_manager->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_MANAGER_GET_NUMBER_OF_PARTITIONS_CHAR:
				UINT32 numPartitions;
				retval = ui_vars.partition_manager->get_NumberOfPartitions(&numPartitions);
				printf("get_NumberOfPartitions() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Number Of Partitions = %d\n", numPartitions);
				}
				break;
			case APP_PARTITION_MANAGER_GET_PARTITION_CHAR:
				retval = ui_vars.partition_manager->get_Partition(0, ui_vars.partition);
				printf("get_Partition() For Partition 1 [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_PARTITION_MENU;
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIPartitionMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_PARTITION_REFRESH_CHAR:
				retval = ui_vars.partition->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_GET_LABEL_CHAR:
				{
					TComPtr<DSC_ITextString> label;
					retval = ui_vars.partition->get_Label(label);
					printf("get_Label() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						char const* text;
						retval = label->get_String(&text);
						printf("get_String() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("Partition1 Label = %s\n", text);
						}
					}
				}
				break;
			case APP_PARTITION_GET_ENABLED_CHAR:
				BOOL flgEnabled;
				retval = ui_vars.partition->get_Enabled(&flgEnabled);
				printf("get_Enabled() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Enabled = %s\n", ((flgEnabled == TRUE) ? "YES" : "NO"));
				}
				break;
			case APP_PARTITION_GET_SYSTEMINDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.partition->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_PARTITION_GET_PARTITION_STATE_DATA_CHAR:
				{
					TComPtr<DSC_IPartitionStateData> partitionStateData;
					retval = ui_vars.partition->get_PartitionStateData(partitionStateData);
					printf("get_PartitionStateData() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						DSC_PartitionAlarmMemoryState partitionAlarmMemoryState;
						retval = partitionStateData->get_PartitionAlarmMemoryState(&partitionAlarmMemoryState);
						printf("get_PartitionAlarmMemoryState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("Partition Alarm Memory State = %d\n", partitionAlarmMemoryState);
						}

						DSC_PartitionTroubleState partitionTroubleState;
						retval = partitionStateData->get_PartitionTroubleState(&partitionTroubleState);
						printf("get_PartitionTroubleState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("Partition Trouble State = %d\n", partitionTroubleState);
						}
					}
				}
				break;
			case APP_PARTITION_WRITE_PARTITION_LABEL_CHAR:
				retval = ui_vars.partition->WritePartitionLabel("Test", result);
				printf("WritePartitionLabel() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_ARM_PARTITION_WITH_ACCESS_CREDENTIALS_CHAR:
				retval = ui_vars.partition->ArmPartitionWithAccessCredentials(ui_vars.user_credentials, DSC_PartitionArmedStates::AwayArmed, result);
				printf("ArmPartitionWithAccessCredentials() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_DISARM_PARTITION_WITH_ACCESS_CREDENTIALS_CHAR:
				retval = ui_vars.partition->DisarmPartitionWithAccessCredentials(ui_vars.user_credentials, result);
				printf("DisarmPartitionWithAccessCredentials() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_GET_ZONE_MANAGER_CHAR:
				retval = ui_vars.partition->get_ZoneManager(ui_vars.zone_manager);
				printf("get_ZoneManager() For Partition 1 [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_ZONE_MANAGER_MENU;
				}
				break;
			case APP_PARTITION_GET_ACCESSCODE_MANAGER_CHAR:
				retval = ui_vars.partition->get_AccessCodeManager(ui_vars.accesscode_manager);
				printf("get_AccessCodeManager() For Partition 1 [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_ACCESSCODE_MANAGER_MENU;
				}
				break;
			case APP_PARTITION_SILENCE_TROUBLE_BEEPS_CHAR:
				retval = ui_vars.partition->SilenceTroubleBeepsForThisPartition(ui_vars.user_credentials, result);
				printf("SilenceTroubleBeepsForThisPartition() %s\n", RequestResultToString(result).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Trouble Beeps Silenced\n");
				}
				break;
			case APP_PARTITION_ACTIVATE_FAP_FIRE_CHAR:
				retval = ui_vars.partition->ActivateFAP(DSC_FAPTypes::Fire, result);
				printf("ActivateFAP(Fire) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_ACTIVATE_FAP_AUX_CHAR:
				retval = ui_vars.partition->ActivateFAP(DSC_FAPTypes::Aux, result);
				printf("ActivateFAP(Aux) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_ACTIVATE_FAP_PANIC_CHAR:
				retval = ui_vars.partition->ActivateFAP(DSC_FAPTypes::Panic, result);
				printf("ActivateFAP(Panic) %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PARTITION_WRITE_DOOR_CHIME_STATE_CHAR:
				retval = ui_vars.partition->WriteDoorChimeEnabledState(ui_vars.user_credentials, DSC_DoorChimeEnabledStates::Chime_Toggle, result);
				printf("WriteDoorChimeEnabledState() %s\n", RequestResultToString(result).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Partition1 Chime Toggled\n");
				}
				break;
			case APP_PARTITION_GET_DOOR_CHIME_STATE_CHAR:
				DSC_DoorChimeEnabledState cstate;
				retval = ui_vars.partition->get_DoorChimeEnabledState(&cstate);
				printf("get_DoorChimeEnabledState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Partition1 Chime: %s\n", ((DSC_DoorChimeEnabledStates::Chime_Enabled == cstate) ? "Enabled" : "Disabled"));
				}
				break;
			case APP_PARTITION_ACTIVATE_COMMAND_OUTPUT_CHAR:
				retval = ui_vars.partition->ActivateCommandOutput(ui_vars.user_credentials, 1, DSC_CommandOutputStates::Output_Toggle, result);
				printf("ActivateCommandOutput() %s\n", RequestResultToString(result).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Command Output 1 Toggled\n");
				}
				break;
			case APP_PARTITION_GET_ALARM_TYPES_CHAR:
				{
					TComPtr<DSC_IAlarmTypeContainer> alarms;
					retval = ui_vars.partition->get_AlarmTypes(alarms);
					printf("get_AlarmTypes() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T count;
						if (IS_SUCCESS(alarms->get_NumberOfAlarmTypes(&count)))
						{
							for (DSC_SIZE_T i = 0; i < count; ++i)
							{
								DSC_AlarmType type;
								if (IS_FAILURE(alarms->get_AlarmType(i, &type)))
								{
									continue;
								}
								printf("Partition1 AlarmType = %d\n", type);
							}
						}
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_PARTITION_MANAGER_MENU;
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIZoneManagerMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_ZONE_MANAGER_REFRESH_CHAR:
				retval = ui_vars.zone_manager->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ZONE_MANAGER_GET_NUMBER_OF_ZONES_CHAR:
				UINT32 numZones;
				retval = ui_vars.zone_manager->get_NumberOfZones(&numZones);
				printf("get_NumberOfZones() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Number Of Zones = %d\n", numZones);
				}
				break;
			case APP_ZONE_MANAGER_GET_ZONE_CHAR:
				retval = ui_vars.zone_manager->get_Zone(0, ui_vars.zone);
				printf("get_Zone() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_ZONE_MENU;
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_PARTITION_MENU;
				// cleanup zone manager
				if (FALSE == ui_vars.zone_manager.IsNull())
				{
					ui_vars.zone_manager.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup zone manager
				if (FALSE == ui_vars.zone_manager.IsNull())
				{
					ui_vars.zone_manager.Clear();
				}
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIAccessCodeManagerMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_ACCESSCODE_MANAGER_REFRESH_CHAR:
				retval = ui_vars.accesscode_manager->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ACCESSCODE_MANAGER_GET_NUMBER_OF_ACESSS_CODES_CHAR:
				UINT32 numAccessCodes;
				retval = ui_vars.accesscode_manager->get_NumberOfAccessCodes(&numAccessCodes);
				printf("get_NumberOfAccessCodes() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Number Of Access Codes = %d\n", numAccessCodes);
				}
				break;
			case APP_ACCESSCODE_MANAGER_GET_ACCESS_CODE_CHAR:
				retval = ui_vars.accesscode_manager->get_AccessCode(1, ui_vars.access_code);
				printf("get_AccessCode() For Access Code 2 [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_ACCESSCODE_MENU;
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_PARTITION_MENU;
				// cleanup access code manager
				if (FALSE == ui_vars.accesscode_manager.IsNull())
				{
					ui_vars.accesscode_manager.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup access code manager
				if (FALSE == ui_vars.accesscode_manager.IsNull())
				{
					ui_vars.accesscode_manager.Clear();
				}
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIZoneMenu(VOID)
{
	string commonResult;
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_ZONE_REFRESH_CHAR:
				retval = ui_vars.zone->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ZONE_GET_LABEL_CHAR:
				{
					TComPtr<DSC_ITextString> label;
					retval = ui_vars.zone->get_Label(label);
					printf("get_Label() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						char const* text;
						retval = label->get_String(&text);
						printf("get_String() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("Zone1 Label = %s\n", text);
						}
					}
				}
				break;
			case APP_ZONE_GET_SYSTEM_INDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.zone->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_ZONE_GET_ALARM_IN_MEMORY_STATE_CHAR:
				DSC_ZoneAlarmInMemoryState mstate;
				retval = ui_vars.zone->get_AlarmInMemoryState(&mstate);
				printf("get_AlarmInMemoryState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Alarm In Memory: %s\n", ((DSC_ZoneAlarmInMemoryStates::Alarm_In_Memory == mstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_ALARM_STATE_CHAR:
				DSC_ZoneAlarmState astate;
				retval = ui_vars.zone->get_AlarmState(&astate);
				printf("get_AlarmState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 InAlarm: %s\n", ((DSC_ZoneAlarmStates::InAlarm == astate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_BYPASS_STATE_CHAR:
				DSC_ZoneBypassState bstate;
				retval = ui_vars.zone->get_BypassState(&bstate);
				printf("get_BypassState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Bypassed: %s\n", ((DSC_ZoneBypassStates::Bypassed == bstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_OPEN_CLOSE_STATE_CHAR:
				DSC_ZoneOpenCloseState ostate;
				retval = ui_vars.zone->get_OpenCloseState(&ostate);
				printf("get_OpenCloseState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Open/Closed: %s\n", ((DSC_ZoneOpenCloseStates::ZoneOpen == ostate) ? "Open" : "Closed"));
				}
				break;
			case APP_ZONE_GET_TAMPER_STATE_CHAR:
				DSC_ZoneTamperState tstate;
				retval = ui_vars.zone->get_TamperState(&tstate);
				printf("get_TamperState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Tampered: %s\n", ((DSC_ZoneTamperStates::TamperPresent == tstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_LOW_SENSITIVITY_STATE_CHAR:
				DSC_ZoneLowSensitivityState lstate;
				retval = ui_vars.zone->get_LowSensitivityState(&lstate);
				printf("get_LowSensitivityState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Low Sensitivity: %s\n", ((DSC_ZoneLowSensitivityStates::LowSensitivityTrouble == lstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_DELINQUENCY_STATE_CHAR:
				DSC_ZoneDelinquencyState dstate;
				retval = ui_vars.zone->get_DelinquencyState(&dstate);
				printf("get_DelinquencyState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Delinquency: %s\n", ((DSC_ZoneDelinquencyStates::Delinquency == dstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_LOWBATT_STATE_CHAR:
				DSC_ZoneLowBatteryState lbstate;
				retval = ui_vars.zone->get_LowBatteryState(&lbstate);
				printf("get_LowBatteryState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 LowBattery: %s\n", ((DSC_ZoneLowBatteryStates::LowBattery == lbstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_FAULT_STATE_CHAR:
				DSC_ZoneFaultState fstate;
				retval = ui_vars.zone->get_FaultState(&fstate);
				printf("get_FaultState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Fault: %s\n", ((DSC_ZoneFaultStates::Fault == fstate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_MASKED_STATE_CHAR:
				DSC_ZoneMaskedState mastate;
				retval = ui_vars.zone->get_MaskedState(&mastate);
				printf("get_MaskedState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Zone1 Masked: %s\n", ((DSC_ZoneMaskedStates::Masked == mastate) ? "YES" : "NO"));
				}
				break;
			case APP_ZONE_GET_ATTRIBUTES_CHAR:
				retval = ui_vars.zone->get_Attributes(ui_vars.zone_attributes);
				printf("get_Attributes() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_ZONE_ATTRIBUTES_MENU;
				}
				break;
			case APP_ZONE_WRITE_ZONE_LABEL_CHAR:
				retval = ui_vars.zone->WriteZoneLabel("Test Zone", result);
				printf("WriteZoneLabel() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ZONE_WRITE_ZONE_BYPASS_CHAR:
				DSC_ZoneBypassState bypassState;
				retval = ui_vars.zone->get_BypassState(&bypassState);
				printf("get_BypassState() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_ZoneBypassState toggle = DSC_ZoneBypassStates::Bypassed;
					if (DSC_ZoneBypassStates::Bypassed == bypassState)
					{
						toggle = DSC_ZoneBypassStates::Not_Bypassed;
					}
					retval = ui_vars.zone->WriteZoneBypass(ui_vars.user_credentials, ((DSC_ZoneBypassStates::Bypassed == toggle) ? TRUE : FALSE), result);
					printf("WriteZoneBypass() %s\n", RequestResultToString(result).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Zone1 %s\n", ((DSC_ZoneBypassStates::Bypassed == toggle) ? "Bypassed" : "UnBypassed"));
					}
				}
				break;
			case APP_ZONE_GET_ALARM_TYPES_CHAR:
				{
					TComPtr<DSC_IAlarmTypeContainer> alarms;
					retval = ui_vars.zone->get_AlarmTypes(alarms);
					printf("get_AlarmTypes() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T count;
						if (IS_SUCCESS(alarms->get_NumberOfAlarmTypes(&count)))
						{
							for (DSC_SIZE_T i = 0; i < count; ++i)
							{
								DSC_AlarmType type;
								if (IS_FAILURE(alarms->get_AlarmType(i, &type)))
								{
									continue;
								}
								printf("Zone1 AlarmType = %d\n", type);
							}
						}
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_ZONE_MANAGER_MENU;
				// cleanup zone
				if (FALSE == ui_vars.zone.IsNull())
				{
					ui_vars.zone.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup zone
				if (FALSE == ui_vars.zone.IsNull())
				{
					ui_vars.zone.Clear();
				}
				// cleanup zone manager
				if (FALSE == ui_vars.zone_manager.IsNull())
				{
					ui_vars.zone_manager.Clear();
				}
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

VOID CApplication::doUIZoneAttributesMenu(VOID)
{
	string commonResult;
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_ZONE_ATTRIBUTES_REFRESH_CHAR:
				retval = ui_vars.zone_attributes->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ZONE_ATTRIBUTES_GET_SYSTEM_INDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.zone_attributes->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_ZONE_ATTRIBUTES_WRITE_CHAR:
				retval = ui_vars.zone_attributes->WriteZoneAttributes(ui_vars.user_credentials, result);
				printf("WriteZoneAttributes() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ZONE_ATTRIBUTES_GET_CHIME_CHAR:
				{
					DSC_ZoneAttributesChimeFunctionState cstate;
					retval = ui_vars.zone_attributes->get_ChimeFunction(&cstate);
					printf("get_ChimeFunction() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Chime Function: %s\n", ((DSC_ZoneAttributesChimeFunctionStates::ChimeFunction_Enabled == cstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ZONE_ATTRIBUTES_GET_BYPASS_CHAR:
				{
					DSC_ZoneAttributesBypassEnableState bstate;
					retval = ui_vars.zone_attributes->get_BypassEnable(&bstate);
					printf("get_BypassEnable() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Bypass Enable: %s\n", ((DSC_ZoneAttributesBypassEnableStates::BypassEnable_Enabled == bstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ZONE_ATTRIBUTES_SET_CHIME_CHAR:
				DSC_ZoneAttributesChimeFunctionState chimeFunctionState;
				retval = ui_vars.zone_attributes->get_ChimeFunction(&chimeFunctionState);
				printf("get_ChimeFunction() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_ZoneAttributesChimeFunctionState toggle = DSC_ZoneAttributesChimeFunctionStates::ChimeFunction_Enabled;
					if (DSC_ZoneAttributesChimeFunctionStates::ChimeFunction_Enabled == chimeFunctionState)
					{
						toggle = DSC_ZoneAttributesChimeFunctionStates::ChimeFunction_Disabled;
					}
					retval = ui_vars.zone_attributes->set_ChimeFunction(toggle);
					printf("set_ChimeFunction() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Chime Function: %s\n", ((DSC_ZoneAttributesChimeFunctionStates::ChimeFunction_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ZONE_ATTRIBUTES_SET_BYPASS_CHAR:
				DSC_ZoneAttributesBypassEnableState bypassEnableState;
				retval = ui_vars.zone_attributes->get_BypassEnable(&bypassEnableState);
				printf("get_BypassEnable() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_ZoneAttributesBypassEnableState toggle = DSC_ZoneAttributesBypassEnableStates::BypassEnable_Enabled;
					if (DSC_ZoneAttributesBypassEnableStates::BypassEnable_Enabled == bypassEnableState)
					{
						toggle = DSC_ZoneAttributesBypassEnableStates::BypassEnable_Disabled;
					}
					retval = ui_vars.zone_attributes->set_BypassEnable(toggle);
					printf("set_BypassEnable() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Bypass Function: %s\n", ((DSC_ZoneAttributesBypassEnableStates::BypassEnable_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_ZONE_MENU;
				// cleanup zone attributes
				if (FALSE == ui_vars.zone_attributes.IsNull())
				{
					ui_vars.zone_attributes.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup zone attributes
				if (FALSE == ui_vars.zone_attributes.IsNull())
				{
					ui_vars.zone_attributes.Clear();
				}
				// cleanup zone
				if (FALSE == ui_vars.zone.IsNull())
				{
					ui_vars.zone.Clear();
				}
				// cleanup zone manager
				if (FALSE == ui_vars.zone_manager.IsNull())
				{
					ui_vars.zone_manager.Clear();
				}
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

//------------------------------------------------------------------------------------------------

VOID CApplication::doUIAccessCodeMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_ACCESSCODE_REFRESH_CHAR:
				retval = ui_vars.access_code->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ACCESSCODE_GET_VALUE_CHAR:
				{
					TComPtr<DSC_ITextString> value;
					retval = ui_vars.access_code->get_Value(value);
					printf("get_Value() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						char const* text;
						retval = value->get_String(&text);
						printf("get_String() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("Access Code 2 Value = %s\n", text);
						}
					}
				}
				break;
			case APP_ACCESSCODE_GET_LABEL_CHAR:
				{
					TComPtr<DSC_ITextString> label;
					retval = ui_vars.access_code->get_Label(label);
					printf("get_Label() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						char const* text;
						retval = label->get_String(&text);
						printf("get_String() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
						if (IS_SUCCESS(retval))
						{
							printf("Access Code 2 Label = %s\n", text);
						}
					}
				}
				break;
			case APP_ACCESSCODE_GET_SYSTEM_INDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.access_code->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_ACCESSCODE_GET_ATTRIBUTES_CHAR:
				retval = ui_vars.access_code->get_Attributes(ui_vars.access_code_attributes);
				printf("get_Attributes() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					ui_vars.menulevel = APP_ACCESSCODE_ATTRIBUTES_MENU;
				}
				break;
			case APP_ACCESSCODE_GET_LENGTH_CHAR:
				UINT32 accessCodeLength;
				retval = ui_vars.access_code->get_AccessCodeLength(&accessCodeLength);
				printf("get_AccessCodeLength() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("Access Code 2 Length = %d\n", accessCodeLength);
				}
				break;
			case APP_ACCESSCODE_WRITE_ACCESS_CODE_LABEL_CHAR:
				retval = ui_vars.access_code->WriteAccessCodeLabel(ui_vars.user_credentials, "Test Code", result);
				printf("WriteAccessCodeLabel() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ACCESSCODE_WRITE_ACCESS_CODE_VALUE_CHAR:
				retval = ui_vars.access_code->WriteAccessCodeValue(ui_vars.user_credentials, "5555", result);
				printf("WriteAccessCodeValue() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_ACCESSCODE_MANAGER_MENU;
				// cleanup access code
				if (FALSE == ui_vars.access_code.IsNull())
				{
					ui_vars.access_code.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup access code
				if (FALSE == ui_vars.access_code.IsNull())
				{
					ui_vars.access_code.Clear();
				}
				// cleanup access code manager
				if (FALSE == ui_vars.accesscode_manager.IsNull())
				{
					ui_vars.accesscode_manager.Clear();
				}
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

//------------------------------------------------------------------------------------------------

VOID CApplication::doUIAccessCodeAttributesMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_ACCESSCODE_ATTRIBUTES_REFRESH_CHAR:
				retval = ui_vars.access_code_attributes->Refresh(ui_vars.user_credentials, result);
				printf("Refresh() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_SYSTEM_INDEX_CHAR:
				UINT32 systemIndex;
				retval = ui_vars.access_code_attributes->get_SystemIndex(&systemIndex);
				printf("get_SystemIndex() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					printf("System Index = %d\n", systemIndex);
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_WRITE_CHAR:
				retval = ui_vars.access_code_attributes->WriteAccessCodeAttributes(ui_vars.user_credentials, result);
				printf("WriteAccessCodeAttributes() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_BELL_SQUAWK_CHAR:
				{
					DSC_AccessCodeAttributesBellSquawkState bstate;
					retval = ui_vars.access_code_attributes->get_BellSquawk(&bstate);
					printf("get_BellSquawk() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Bell Squawk: %s\n", ((DSC_AccessCodeAttributesBellSquawkStates::BellSquawk_Enabled == bstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_CAN_BYPASS_ZONE_CHAR:
				{
					DSC_AccessCodeAttributesCanBypassZoneState cstate;
					retval = ui_vars.access_code_attributes->get_CanBypassZone(&cstate);
					printf("get_CanBypassZone() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Can Bypass: %s\n", ((DSC_AccessCodeAttributesCanBypassZoneStates::CanBypassZone_Enabled == cstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_DURESS_CODE_CHAR:
				{
					DSC_AccessCodeAttributesDuressCodeState dstate;
					retval = ui_vars.access_code_attributes->get_DuressCode(&dstate);
					printf("get_DuressCode() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Duress Code: %s\n", ((DSC_AccessCodeAttributesDuressCodeStates::DuressCode_Enabled == dstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_ONE_TIME_USE_CHAR:
				{
					DSC_AccessCodeAttributesOneTimeUseState ostate;
					retval = ui_vars.access_code_attributes->get_OneTimeUse(&ostate);
					printf("get_OneTimeUse() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("One Time Use: %s\n", ((DSC_AccessCodeAttributesOneTimeUseStates::OneTimeUse_Enabled == ostate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_REMOTE_ACCESS_CHAR:
				{
					DSC_AccessCodeAttributesRemoteAccessState rstate;
					retval = ui_vars.access_code_attributes->get_RemoteAccessEnabled(&rstate);
					printf("get_RemoteAccessEnabled() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Remote Access: %s\n", ((DSC_AccessCodeAttributesRemoteAccessStates::RemoteAccess_Enabled == rstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_GET_SUPERVISOR_CHAR:
				{
					DSC_AccessCodeAttributesSupervisorState sstate;
					retval = ui_vars.access_code_attributes->get_Supervisor(&sstate);
					printf("get_Supervisor() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Supervisor: %s\n", ((DSC_AccessCodeAttributesSupervisorStates::Supervisor_Enabled == sstate) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_SET_BELL_SQUAWK_CHAR:
				DSC_AccessCodeAttributesBellSquawkState bellSquawkState;
				retval = ui_vars.access_code_attributes->get_BellSquawk(&bellSquawkState);
				printf("get_BellSquawk() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_AccessCodeAttributesBellSquawkState toggle = DSC_AccessCodeAttributesBellSquawkStates::BellSquawk_Enabled;
					if (DSC_AccessCodeAttributesBellSquawkStates::BellSquawk_Enabled == bellSquawkState)
					{
						toggle = DSC_AccessCodeAttributesBellSquawkStates::BellSquawk_Disabled;
					}
					retval = ui_vars.access_code_attributes->set_BellSquawk(toggle);
					printf("set_BellSquawk() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Bell Squawk: %s\n", ((DSC_AccessCodeAttributesBellSquawkStates::BellSquawk_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_SET_CAN_BYPASS_ZONE_CHAR:
				DSC_AccessCodeAttributesCanBypassZoneState canBypassZoneState;
				retval = ui_vars.access_code_attributes->get_CanBypassZone(&canBypassZoneState);
				printf("get_CanBypassZone() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_AccessCodeAttributesCanBypassZoneState toggle = DSC_AccessCodeAttributesCanBypassZoneStates::CanBypassZone_Enabled;
					if (DSC_AccessCodeAttributesCanBypassZoneStates::CanBypassZone_Enabled == canBypassZoneState)
					{
						toggle = DSC_AccessCodeAttributesCanBypassZoneStates::CanBypassZone_Disabled;
					}
					retval = ui_vars.access_code_attributes->set_CanBypassZone(toggle);
					printf("set_CanBypassZone() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Can Bypass: %s\n", ((DSC_AccessCodeAttributesCanBypassZoneStates::CanBypassZone_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_SET_DURESS_CODE_CHAR:
				DSC_AccessCodeAttributesDuressCodeState duressCodeState;
				retval = ui_vars.access_code_attributes->get_DuressCode(&duressCodeState);
				printf("get_DuressCode() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_AccessCodeAttributesDuressCodeState toggle = DSC_AccessCodeAttributesDuressCodeStates::DuressCode_Enabled;
					if (DSC_AccessCodeAttributesDuressCodeStates::DuressCode_Enabled == duressCodeState)
					{
						toggle = DSC_AccessCodeAttributesDuressCodeStates::DuressCode_Disabled;
					}
					retval = ui_vars.access_code_attributes->set_DuressCode(toggle);
					printf("set_DuressCode() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Duress Code: %s\n", ((DSC_AccessCodeAttributesDuressCodeStates::DuressCode_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_SET_ONE_TIME_USE_CHAR:
				DSC_AccessCodeAttributesOneTimeUseState oneTimeUseState;
				retval = ui_vars.access_code_attributes->get_OneTimeUse(&oneTimeUseState);
				printf("get_OneTimeUse() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_AccessCodeAttributesOneTimeUseState toggle = DSC_AccessCodeAttributesOneTimeUseStates::OneTimeUse_Enabled;
					if (DSC_AccessCodeAttributesOneTimeUseStates::OneTimeUse_Enabled == oneTimeUseState)
					{
						toggle = DSC_AccessCodeAttributesOneTimeUseStates::OneTimeUse_Disabled;
					}
					retval = ui_vars.access_code_attributes->set_OneTimeUse(toggle);
					printf("set_OneTimeUse() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("One Time Use: %s\n", ((DSC_AccessCodeAttributesOneTimeUseStates::OneTimeUse_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_SET_REMOTE_ACCESS_CHAR:
				DSC_AccessCodeAttributesRemoteAccessState remoteAccessState;
				retval = ui_vars.access_code_attributes->get_RemoteAccessEnabled(&remoteAccessState);
				printf("get_RemoteAccessEnabled() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_AccessCodeAttributesRemoteAccessState toggle = DSC_AccessCodeAttributesRemoteAccessStates::RemoteAccess_Enabled;
					if (DSC_AccessCodeAttributesRemoteAccessStates::RemoteAccess_Enabled == remoteAccessState)
					{
						toggle = DSC_AccessCodeAttributesRemoteAccessStates::RemoteAccess_Disabled;
					}
					retval = ui_vars.access_code_attributes->set_RemoteAccessEnabled(toggle);
					printf("set_RemoteAccessEnabled() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Remote Access: %s\n", ((DSC_AccessCodeAttributesRemoteAccessStates::RemoteAccess_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_ACCESSCODE_ATTRIBUTES_SET_SUPERVISOR_CHAR:
				DSC_AccessCodeAttributesSupervisorState supervisorState;
				retval = ui_vars.access_code_attributes->get_Supervisor(&supervisorState);
				printf("get_Supervisor() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
				if (IS_SUCCESS(retval))
				{
					DSC_AccessCodeAttributesSupervisorState toggle = DSC_AccessCodeAttributesSupervisorStates::Supervisor_Enabled;
					if (DSC_AccessCodeAttributesSupervisorStates::Supervisor_Enabled == supervisorState)
					{
						toggle = DSC_AccessCodeAttributesSupervisorStates::Supervisor_Disabled;
					}
					retval = ui_vars.access_code_attributes->set_Supervisor(toggle);
					printf("set_Supervisor() [0x%08X (%s)]\n", retval, IResultToString(retval).c_str());
					if (IS_SUCCESS(retval))
					{
						printf("Supervisor: %s\n", ((DSC_AccessCodeAttributesSupervisorStates::Supervisor_Enabled == toggle) ? "Enabled" : "Disabled"));
					}
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
				ui_vars.menulevel = APP_ACCESSCODE_MENU;
				// cleanup access code attributes
				if (FALSE == ui_vars.access_code_attributes.IsNull())
				{
					ui_vars.access_code_attributes.Clear();
				}
				break;
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup access code attributes
				if (FALSE == ui_vars.access_code_attributes.IsNull())
				{
					ui_vars.access_code_attributes.Clear();
				}
				// cleanup access code
				if (FALSE == ui_vars.access_code.IsNull())
				{
					ui_vars.access_code.Clear();
				}
				// cleanup access code manager
				if (FALSE == ui_vars.accesscode_manager.IsNull())
				{
					ui_vars.accesscode_manager.Clear();
				}
				// cleanup partition
				if (FALSE == ui_vars.partition.IsNull())
				{
					ui_vars.partition.Clear();
				}
				// cleanup partition manager
				if (FALSE == ui_vars.partition_manager.IsNull())
				{
					ui_vars.partition_manager.Clear();
				}
				break;
			default:
				break;
		}
		DisplayMenu();
	}
}

//------------------------------------------------------------------------------------------------

VOID CApplication::doUISpecificFunctionsMenu(VOID)
{
	if (_kbhit())
	{
		ui_vars.previous_menulevel = ui_vars.menulevel;
		IRESULT retval = IRESULT_S_OK;
		TComPtr<DSC_IRequestResult> result;

		switch (toupper(_getch()))
		{
			case APP_SPECIFIC_FUNCTIONS_CHANGE_IAC:
				retval = ui_vars.specific_functions->ITV2_ChangeIntegrationAccessCode("12345678123456781234567812345678", "87654321876543218765432187654321", "New Session", result);
				printf("ITV2_ChangeIntegrationAccessCode() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_SPECIFIC_FUNCTIONS_DEFAULT_IAC:
				retval = ui_vars.specific_functions->ITV2_ChangeIntegrationAccessCode("87654321876543218765432187654321", "12345678123456781234567812345678", "New Session", result);
				printf("ITV2_ChangeIntegrationAccessCode() %s\n", RequestResultToString(result).c_str());
				break;
			case APP_SPECIFIC_FUNCTIONS_READ_LIFESTYLE_NOTIFICATION_SETTINGS:
				{
					TComPtr<DSC_ILifeStyleSettings> settings;
					retval = ui_vars.specific_functions->ITV2_ReadLifeStyleNotificationSettings(settings, result);
					printf("ITV2_ReadLifeStyleNotificationSettings() %s\n", RequestResultToString(result).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T count;
						retval = settings->get_Size(&count);
						if(IS_SUCCESS(retval))
						{
							for(DSC_SIZE_T i = 0; i < count; ++i)
							{
								DSC_LifeStyleNotification notification;
								retval = settings->get_Setting(i, &notification);
								if(IS_SUCCESS(retval))
								{
									printf("Notification %d ON\n", notification);
								}
							}
						}
					}
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_WRITE_LIFESTYLE_NOTIFICATION_SETTINGS1:
				{
					// turn off Access_Code_Length & Chime
					DSC_LifeStyleNotification off_notifications[2]  = { DSC_LifeStyleNotifications::Access_Code_Length, DSC_LifeStyleNotifications::Chime };
					retval = ui_vars.specific_functions->ITV2_WriteLifeStyleNotificationSettings(NULL, 0, off_notifications, (sizeof(off_notifications) / sizeof(DSC_LifeStyleNotification)), result);
					printf("ITV2_WriteLifeStyleNotificationSettings() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_WRITE_LIFESTYLE_NOTIFICATION_SETTINGS2:
				{
					// turn on Access_Code_Length & Chime
					DSC_LifeStyleNotification on_notifications[2]  = { DSC_LifeStyleNotifications::Access_Code_Length, DSC_LifeStyleNotifications::Chime };
					retval = ui_vars.specific_functions->ITV2_WriteLifeStyleNotificationSettings(on_notifications, (sizeof(on_notifications) / sizeof(DSC_LifeStyleNotification)), NULL, 0, result);
					printf("ITV2_WriteLifeStyleNotificationSettings() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_DEFAULT_LIFESTYLE_NOTIFICATION_SETTINGS:
				{
					TComPtr<DSC_ILifeStyleSettings> settings;
					retval = ui_vars.specific_functions->ITV2_DefaultLifeStyleNotificationSettings(result);
					printf("ITV2_DefaultLifeStyleNotificationSettings() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_READ_ZONE_NOTIFICATION_SETTINGS:
				{
					TComPtr<DSC_ISystemIndices> settings;
					retval = ui_vars.specific_functions->ITV2_ReadZoneNotificationSettings(settings, result);
					printf("ITV2_ReadZoneNotificationSettings() %s\n", RequestResultToString(result).c_str());
					if(IS_SUCCESS(retval))
					{
						DSC_SIZE_T count;
						retval = settings->get_Size(&count);
						if(IS_SUCCESS(retval))
						{
							for(DSC_SIZE_T i = 0; i < count; ++i)
							{
								DSC_SYSTEM_INDEX index;
								retval = settings->get_Index(i, &index);
								if(IS_SUCCESS(retval))
								{
									printf("Zone %d ON\n", index);
								}
							}
						}
					}
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_WRITE_ZONE_NOTIFICATION_SETTINGS1:
				{
					// turn off Zone 1 & Zone 8
					DSC_SYSTEM_INDEX off_zones[2]  = { 1, 8 };
					retval = ui_vars.specific_functions->ITV2_WriteZoneNotificationSettings(NULL, 0, off_zones, (sizeof(off_zones) / sizeof(DSC_SYSTEM_INDEX)), result);
					printf("ITV2_WriteZoneNotificationSettings() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_WRITE_ZONE_NOTIFICATION_SETTINGS2:
				{
					// turn on Zone 1 & Zone 8
					DSC_SYSTEM_INDEX on_zones[2]  = { 1, 8 };
					retval = ui_vars.specific_functions->ITV2_WriteZoneNotificationSettings(on_zones, (sizeof(on_zones) / sizeof(DSC_SYSTEM_INDEX)), NULL, 0, result);
					printf("ITV2_WriteZoneNotificationSettings() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_SPECIFIC_FUNCTIONS_DEFAULT_ZONE_NOTIFICATION_SETTINGS:
				{
					TComPtr<DSC_ILifeStyleSettings> settings;
					retval = ui_vars.specific_functions->ITV2_DefaultZoneNotificationSettings(result);
					printf("ITV2_DefaultZoneNotificationSettings() %s\n", RequestResultToString(result).c_str());
				}
				break;
			case APP_PREVIOUS_MENU_CHAR:
			case APP_MAIN_MENU_CHAR:
				ui_vars.menulevel = APP_MAIN_MENU;
				// cleanup specific functions
				if (FALSE == ui_vars.specific_functions.IsNull())
				{
					ui_vars.specific_functions.Clear();
				}
			default:
				break;
		}
		DisplayMenu();
	}
}

//------------------------------------------------------------------------------------------------

BOOL CApplication::doUserInterface(VOID)
{
	BOOL retval = TRUE;

	switch (ui_vars.menulevel)
	{
		case APP_MAIN_MENU:
			doUIMainMenu();
			break;
		case APP_SYSTEM_MANAGER_MENU:
			doUISystemManagerMenu();
			break;
		case APP_VIRTUAL_ZONE_MANAGER_MENU:
			doUIVirtualZoneManagerMenu();
			break;
		case APP_VIRTUAL_ZONE_MENU:
			doUIVirtualZoneMenu();
			break;
		case APP_VIRTUAL_ZONE_STATUS_MENU:
			doUIVirtualZoneStatusMenu();
			break;
		case APP_PARTITION_MANAGER_MENU:
			doUIPartitionManagerMenu();
			break;
		case APP_PARTITION_MENU:
			doUIPartitionMenu();
			break;
		case APP_ZONE_MANAGER_MENU:
			doUIZoneManagerMenu();
			break;
		case APP_ACCESSCODE_MANAGER_MENU:
			doUIAccessCodeManagerMenu();
			break;
		case APP_ZONE_MENU:
			doUIZoneMenu();
			break;
		case APP_ZONE_ATTRIBUTES_MENU:
			doUIZoneAttributesMenu();
			break;
		case APP_ACCESSCODE_MENU:
			doUIAccessCodeMenu();
			break;
		case APP_ACCESSCODE_ATTRIBUTES_MENU:
			doUIAccessCodeAttributesMenu();
			break;
		case APP_VIRTUAL_KEYPAD_MANAGER_MENU:
			doUIVirtualKeypadManagerMenu();
			break;
		case APP_VIRTUAL_KEYPAD_MENU:
			doUIVirtualKeypadMenu();
			break;
		case APP_SPECIFIC_FUNCTIONS_MENU:
			doUISpecificFunctionsMenu();
			break;
		case APP_EXIT_MENU:
			retval = FALSE;
			break;
		default:
			break;
	}

	return(retval);
}

//---------------------------------------------------------------------------

string CApplication::RequestResultToString(DSC_IRequestResult* result)
{
	string retval;

	retval.assign("");

	if (NULL != result)
	{
		DSC_RequestResultCode code = DSC_RequestResultCodes::Common_NotAvailable;
		if (IS_FAILURE(result->get_ReadWriteResultCode(&code)))
		{
			// error
			retval.assign("[RequestResultToString()->get_ReadWriteResultCode() Failed]");
			return retval;
		}

		TComPtr<DSC_ITextString> text;
		if (IS_FAILURE(result->get_ResultDescription(text)))
		{
			retval.assign("[RequestResultToString()->get_ResultDescription() Failed]");
			return retval;
		}

		char const* str = NULL;
		if (IS_FAILURE(text->get_String(&str)))
		{
			retval.assign("[RequestResultToString()->get_String() Failed]");
			return retval;
		}

		int size;
		if (DSC_RequestResultCodes::Common_Success == code)
		{
			size = _snprintf(NULL, 0, "[%d (%s): %s]", code, ResultCodeToString(code).c_str(), str);
		}
		else
		{
			TComPtr<DSC_IDataBuffer> sent;
			TComPtr<DSC_IDataBuffer> recv;
			(void)result->get_ExtendedData(sent, recv);
			size = _snprintf(NULL, 0, "[%d (%s): %s]\n[Sent: %s]\n[Recv: %s]", code, ResultCodeToString(code).c_str(), str, DataToString(sent).c_str(), DataToString(recv).c_str());
		}
		if (0 <= size)
		{
			//char* text = (char*)malloc(size + sizeof(char));
			char text[500];
			if (NULL != text)
			{
				// malloc successful
				int size2;
				if (DSC_RequestResultCodes::Common_Success == code)
				{
					size2 = _snprintf(text, size + 1, "[%d (%s): %s]", code, ResultCodeToString(code).c_str(), str);
				}
				else
				{
					TComPtr<DSC_IDataBuffer> sent;
					TComPtr<DSC_IDataBuffer> recv;
					(void)result->get_ExtendedData(sent, recv);
					size2 = _snprintf(text, size + 1, "[%d (%s): %s]\n[Sent: %s]\n[Recv: %s]", code, ResultCodeToString(code).c_str(), str, DataToString(sent).c_str(), DataToString(recv).c_str());
				}
				if (size == size2)
				{
					text[size] = '\0'; //terminator
					retval = text;
					//free(text);
				}
				else
				{
					// _snprintf failed
					retval.assign("RequestResultToString()->_snprintf() Failed");
				}
			}
			else
			{
				// malloc failed
				retval.assign("RequestResultToString()->malloc() Failed");
			}
		}
	}

	return retval;
}

//---------------------------------------------------------------------------

string CApplication::DataToString(DSC_IDataBuffer* data)
{
	string retval = string("Not Available");

	DSC_SIZE_T size;
	if (IS_SUCCESS(data->get_Size(&size)))
	{
		if (0 < size)
		{
			BYTE* ptrBuffer = NULL;
			if (IS_SUCCESS(data->get_Buffer(&ptrBuffer)))
			{
				retval = CHexHelper::ToString(ptrBuffer, size, "", "", " ", FALSE);
			}
		}
	}

	return retval;
}

//---------------------------------------------------------------------------

string CApplication::ResultCodeToString(DSC_RequestResultCode code)
{
	string retval;
	retval.assign("");

	switch(code)
	{
		case DSC_RequestResultCodes::Common_NotAvailable:
			retval.assign("Common_NotAvailable");
			break;
		case DSC_RequestResultCodes::Common_Unknown:
			retval.assign("Common_Unknown");
			break;
		case DSC_RequestResultCodes::Common_Success:
			retval.assign("Common_Success");
			break;
		case DSC_RequestResultCodes::Common_InvalidUserCredentials:
			retval.assign("Common_InvalidUserCredentials");
			break;
		case DSC_RequestResultCodes::Common_InvalidInstallerCredentials:
			retval.assign("Common_InvalidInstallerCredentials");
			break;
		case DSC_RequestResultCodes::Common_UserCredentialsRequired:
			retval.assign("Common_UserCredentialsRequired");
			break;
		case DSC_RequestResultCodes::Common_FunctionNotAvailable:
			retval.assign("Common_FunctionNotAvailable");
			break;
		case DSC_RequestResultCodes::Common_UnrecognizedResultCode:
			retval.assign("Common_UnrecognizedResultCode");
			break;
		case DSC_RequestResultCodes::Common_InvalidInstance:
			retval.assign("Common_InvalidInstance");
			break;
		case DSC_RequestResultCodes::Target_SystemIsLockedOut:
			retval.assign("Target_SystemIsLockedOut");
			break;
		case DSC_RequestResultCodes::Target_PowerUpShuntInEffect:
			retval.assign("Target_PowerUpShuntInEffect");
			break;
		case DSC_RequestResultCodes::Target_PanelIsNotResponsive:
			retval.assign("Target_PanelIsNotResponsive");
			break;
		case DSC_RequestResultCodes::Target_SystemIsBusy:
			retval.assign("Target_SystemIsBusy");
			break;
		case DSC_RequestResultCodes::Target_NoActiveSession:
			retval.assign("Target_NoActiveSession");
			break;
		case DSC_RequestResultCodes::Target_WrongSessionId:
			retval.assign("Target_WrongSessionId");
			break;
		case DSC_RequestResultCodes::Target_InternalError:
			retval.assign("Target_InternalError");
			break;
		case DSC_RequestResultCodes::Target_Timeout:
			retval.assign("Target_Timeout");
			break;
		case DSC_RequestResultCodes::Target_RequestMissing:
			retval.assign("Target_RequestMissing");
			break;
		case DSC_RequestResultCodes::Target_RequestError:
			retval.assign("Target_RequestError");
			break;
		case DSC_RequestResultCodes::Target_ResponseMissing:
			retval.assign("Target_ResponseMissing");
			break;
		case DSC_RequestResultCodes::Target_ResponseError:
			retval.assign("Target_ResponseError");
			break;
		case DSC_RequestResultCodes::SDK_InternalError:
			retval.assign("SDK_InternalError");
			break;
		case DSC_RequestResultCodes::AccessCode_InvalidAccessCodeBeingProgrammed:
			retval.assign("AccessCode_InvalidAccessCodeBeingProgrammed");
			break;
		case DSC_RequestResultCodes::AccessCode_CodeDuplicated:
			retval.assign("AccessCode_CodeDuplicated");
			break;
		case DSC_RequestResultCodes::Partition_PartitionFailedToArm:
			retval.assign("Partition_PartitionFailedToArm");
			break;
		case DSC_RequestResultCodes::Partition_InvalidArmingMode:
			retval.assign("Partition_InvalidArmingMode");
			break;
		case DSC_RequestResultCodes::Partition_WalkTestActive:
			retval.assign("Partition_WalkTestActive");
			break;
		case DSC_RequestResultCodes::Partition_SomeOrAllPartitionsFailedToArm:
			retval.assign("Partition_SomeOrAllPartitionsFailedToArm");
			break;
		case DSC_RequestResultCodes::Partition_PartitionIsBusy:
			retval.assign("Partition_PartitionIsBusy");
			break;
		case DSC_RequestResultCodes::Partition_PartitionFailedToDisarm:
			retval.assign("Partition_PartitionFailedToDisarm");
			break;
		case DSC_RequestResultCodes::Partition_SomeOrAllPartitionsFailedToDisarm:
			retval.assign("Partition_SomeOrAllPartitionsFailedToDisarm");
			break;
		case DSC_RequestResultCodes::Partition_InvalidFAPType:
			retval.assign("Partition_InvalidFAPType");
			break;
		case DSC_RequestResultCodes::Partition_FAPRequestDenied:
			retval.assign("Partition_FAPRequestDenied");
			break;
		case DSC_RequestResultCodes::Partition_CannotChangeDoorChimeStatus:
			retval.assign("Partition_CannotChangeDoorChimeStatus");
			break;
		case DSC_RequestResultCodes::Partition_InvalidDoorChimeEnabledState:
			retval.assign("Partition_InvalidDoorChimeEnabledState");
			break;
		case DSC_RequestResultCodes::Partition_CommandOutputNotDefined:
			retval.assign("Partition_CommandOutputNotDefined");
			break;
		case DSC_RequestResultCodes::Partition_InvalidCommandOutputNumber:
			retval.assign("Partition_InvalidCommandOutputNumber");
			break;
		case DSC_RequestResultCodes::Partition_InvalidCommandOutputState:
			retval.assign("Partition_InvalidCommandOutputState");
			break;
		case DSC_RequestResultCodes::System_IncorrectTime:
			retval.assign("System_IncorrectTime");
			break;
		case DSC_RequestResultCodes::VirtualZoneStatus_SystemIsBusy:
			retval.assign("VirtualZoneStatus_SystemIsBusy");
			break;
		case DSC_RequestResultCodes::Zone_ZoneCannotBeBypassed:
			retval.assign("Zone_ZoneCannotBeBypassed");
			break;
		case DSC_RequestResultCodes::Zone_InvalidBypassState:
			retval.assign("Zone_InvalidBypassState");
			break;
		case DSC_RequestResultCodes::VirtualKeypad_NotSupported:
			retval.assign("VirtualKeypad_NotSupported");
			break;
		case DSC_RequestResultCodes::VirtualKeypad_InvalidKeypadNumber:
			retval.assign("VirtualKeypad_InvalidKeypadNumber");
			break;
		case DSC_RequestResultCodes::VirtualKeypad_InvalidKeypadMode:
			retval.assign("VirtualKeypad_InvalidKeypadMode");
			break;
		case DSC_RequestResultCodes::VirtualKeypad_AlreadyActiveOnAnotherSession:
			retval.assign("VirtualKeypad_AlreadyActiveOnAnotherSession");
			break;
		case DSC_RequestResultCodes::VirtualKeypad_MaximumSupportedKeypadsActive:
			retval.assign("VirtualKeypad_MaximumSupportedKeypadsActive");
			break;
		default:
			retval.assign("Unknown DSC_RequestResultCode");
			break;
	}

	return retval;
}

//---------------------------------------------------------------------------

string CApplication::IResultToString(IRESULT result)
{
	string retval;
	retval.assign("");

	switch(result)
	{
		case IRESULT_S_OK:
			retval.assign("IRESULT_S_OK");
			break;
		case IRESULT_S_TRUE:
			retval.assign("IRESULT_S_TRUE");
			break;
		case IRESULT_S_FALSE:
			retval.assign("IRESULT_S_FALSE");
			break;
		case IRESULT_S_NULL:
			retval.assign("IRESULT_S_NULL");
			break;
		case IRESULT_E_FAILURE:
			retval.assign("IRESULT_E_FAILURE");
			break;
		case IRESULT_E_TIMEOUT:
			retval.assign("IRESULT_E_TIMEOUT");
			break;
		case IRESULT_E_NOT_IMPLEMENTED:
			retval.assign("IRESULT_E_NOT_IMPLEMENTED");
			break;
		case IRESULT_E_MEMORY_ALLOC:
			retval.assign("IRESULT_E_MEMORY_ALLOC");
			break;
		case IRESULT_E_SMALL_BUFFER:
			retval.assign("IRESULT_E_SMALL_BUFFER");
			break;
		case IRESULT_E_BAD_ARGUMENTS:
			retval.assign("IRESULT_E_BAD_ARGUMENTS");
			break;
		case IRESULT_E_NOT_AVAILABLE:
			retval.assign("IRESULT_E_NOT_AVAILABLE");
			break;
		case IRESULT_E_UNKNOWN_VALUE:
			retval.assign("IRESULT_E_UNKNOWN_VALUE");
			break;
		case IRESULT_E_INVALID_VALUE:
			retval.assign("IRESULT_E_INVALID_VALUE");
			break;
		case IRESULT_E_INDEX_OUT_OF_RANGE:
			retval.assign("IRESULT_E_INDEX_OUT_OF_RANGE");
			break;
		case IRESULT_E_MISSING_DATA:
			retval.assign("IRESULT_E_MISSING_DATA");
			break;
		case IRESULT_E_MISSING_LICENSE:
			retval.assign("IRESULT_E_MISSING_LICENSE");
			break;
		case IRESULT_E_MISSING_SESSION:
			retval.assign("IRESULT_E_MISSING_SESSION");
			break;
		case IRESULT_E_INVALID_INSTANCE:
			retval.assign("IRESULT_E_INVALID_INSTANCE");
			break;
		case IRESULT_E_TARGET_FAILURE:
			retval.assign("IRESULT_E_TARGET_FAILURE");
			break;
		case IRESULT_E_TARGET_TIMEOUT:
			retval.assign("IRESULT_E_TARGET_TIMEOUT");
			break;
		default:
			retval.assign("Unknown IRESULT");
			break;
	}

	return retval;
}

//---------------------------------------------------------------------------

string CApplication::CommandToString(UINT16 cmd)
{
	string retval;

	retval.assign("");

	switch (cmd)
	{
	case 0x0100:
		retval.assign("0x0100_Get_Event_Buffer_Information");
		break;
	case 0x0101:
		retval.assign("0x0101_Event_Buffer_Read_By_Event_Number");
		break;
	case 0x0102:
		retval.assign("0x0102_Single_Event_Buffer_Read");
		break;
	case 0x0103:
		retval.assign("0x0103_SMS_Preview_Read");
		break;
	case 0x0104:
		retval.assign("0x0104_Single_SMS_Text_Read");
		break;
	case 0x0105:
		retval.assign("0x0105_Delete_SMS");
		break;
	case 0x0106:
		retval.assign("0x0106_Event_Buffer_Read_By_Date_Time_Stamp");
		break;
	case 0x0110:
		retval.assign("0x0110_Panel_Event_Buffer_Notification");
		break;
	case 0x0111:
		retval.assign("0x0111_Unread_SMS_Notification");
		break;
	case 0x0112:
		retval.assign("0x0112_Panel_Communicable_Event_TX_Notification");
		break;
	case 0x0200:
		retval.assign("0x0200_SIA_CID_Messsage");
		break;
	case 0x0201:
		retval.assign("0x0201_Text_Message");
		break;
	case 0x0210:
		retval.assign("0x0210_Lifestyle_Zone_Status");
		break;
	case 0x0220:
		retval.assign("0x0220_Time_Date_Broadcast");
		break;
	case 0x0221:
		retval.assign("0x0221_Temperature_Broadcast");
		break;
	case 0x0222:
		retval.assign("0x0222_Command_Output_Activation");
		break;
	case 0x0223:
		retval.assign("0x0223_Chime_Broadcast");
		break;
	case 0x0224:
		retval.assign("0x0224_Panel_Display_Configuration");
		break;
	case 0x0230:
		retval.assign("0x0230_Exit_Delay");
		break;
	case 0x0231:
		retval.assign("0x0231_Entry_Delay");
		break;
	case 0x0232:
		retval.assign("0x0232_Arming_Disarming");
		break;
	case 0x0233:
		retval.assign("0x0233_Arming_PreAlert");
		break;
	case 0x0234:
		retval.assign("0x0234_Enrollment_Status");
		break;
	case 0x0235:
		retval.assign("0x0235_General_Activity");
		break;
	case 0x0236:
		retval.assign("0x0236_Access_Code_Length");
		break;
	case 0x0237:
		retval.assign("0x0237_Partition_Buzzer_Type");
		break;
	case 0x0238:
		retval.assign("0x0238_Partition_Quick_Exit");
		break;
	case 0x0239:
		retval.assign("0x0239_Partition_Ready_Status");
		break;
	case 0x023A:
		retval.assign("0x023A_System_Test");
		break;
	case 0x023B:
		retval.assign("0x023B_Partition_Audible_Bell");
		break;
	case 0x023C:
		retval.assign("0x023C_Partition_Alarm_Memory");
		break;
	case 0x023D:
		retval.assign("0x023D_Miscellaneous_PreAlert");
		break;
	case 0x023E:
		retval.assign("0x023E_Partition_Blank_Status");
		break;
	case 0x023F:
		retval.assign("0x023F_Partition_Trouble_Status");
		break;
	case 0x0240:
		retval.assign("0x0240_Partition_Bypass_Status");
		break;
	case 0x0241:
		retval.assign("0x0241_Partition_Busy_Status");
		break;
	case 0x0242:
		retval.assign("0x0242_Partition_General_Activity");
		break;
	case 0x0243:
		retval.assign("0x0243_Signal_Strength");
		break;
	case 0x0244:
		retval.assign("0x0244_Command_Output_Activation_Extended");
		break;
	case 0x0245:
		retval.assign("0x0245_Partition_Banner");
		break;
	case 0x0246:
		retval.assign("0x0246_Partition_Buzzer_Type_Extended");
		break;
	case 0x0250:
		retval.assign("0x0250_User_Configuration_Change");
		break;
	case 0x02F0:
		retval.assign("0x02F0_Buffer_Overload");
		break;
	case 0x0300:
		retval.assign("0x0300_Firmware_Available");
		break;
	case 0x0301:
		retval.assign("0x0301_Start_Download");
		break;
	case 0x0302:
		retval.assign("0x0302_Cancel_Download");
		break;
	case 0x0303:
		retval.assign("0x0303_Download_Complete");
		break;
	case 0x0304:
		retval.assign("0x0304_Data_Packet");
		break;
	case 0x0305:
		retval.assign("0x0305_Available_Critical");
		break;
	case 0x0306:
		retval.assign("0x0306_Update_Status");
		break;
	case 0x0400:
		retval.assign("0x0400_Enter_Access_Level");
		break;
	case 0x0401:
		retval.assign("0x0401_Exit_Access_Level");
		break;
	case 0x0402:
		retval.assign("0x0402_Access_Level_Lead_In_Out");
		break;
	case 0x0501:
		retval.assign("0x0501_Command_Error");
		break;
	case 0x0502:
		retval.assign("0x0502_Command_Response");
		break;
	case 0x0600:
		retval.assign("0x0600_Poll");
		break;
	case 0x060A:
		retval.assign("0x060A_Open_Session");
		break;
	case 0x060B:
		retval.assign("0x060B_End_Session");
		break;
	case 0x060C:
		retval.assign("0x060C_Inform_TX_And_RX_Buffer_Sizes");
		break;
	case 0x060D:
		retval.assign("0x060D_Software_Version");
		break;
	case 0x060E:
		retval.assign("0x060E_Request_Access");
		break;
	case 0x0612:
		retval.assign("0x0612_Pass_Through_Command");
		break;
	case 0x0613:
		retval.assign("0x0613_System_Capabilities");
		break;
	case 0x0614:
		retval.assign("0x0614_Panel_Status");
		break;
	case 0x0615:
		retval.assign("0x0615_Device_Enrollment");
		break;
	case 0x0622:
		retval.assign("0x0622_Encapsulated_Command_For_Long_Packets");
		break;
	case 0x0623:
		retval.assign("0x0623_Encapsulated_Command_For_Multiple_Packets");
		break;
	case 0x0631:
		retval.assign("0x0631_Session_Key_Change");
		break;
	case 0x0632:
		retval.assign("0x0632_Integration_Access_Code_Change");
		break;
	case 0x0700:
		retval.assign("0x0700_Enter_Configuration_Mode");
		break;
	case 0x0701:
		retval.assign("0x0701_Exit_Configuration_Mode");
		break;
	case 0x0702:
		retval.assign("0x0702_Panel_Programming_Lead_In_Out");
		break;
	case 0x0703:
		retval.assign("0x0703_Access_Code_Wrapper");
		break;
	case 0x0704:
		retval.assign("0x0704_Enter_Configuration_Mode_Read_Write_Control");
		break;
	case 0x0721:
		retval.assign("0x0721_Section_Read");
		break;
	case 0x0722:
		retval.assign("0x0722_Section_Write");
		break;
	case 0x0731:
		retval.assign("0x0731_Time_And_Date_Read");
		break;
	case 0x0732:
		retval.assign("0x0732_Late_To_Open_Control_Read");
		break;
	case 0x0733:
		retval.assign("0x0733_Late_To_Open_Time_Read");
		break;
	case 0x0734:
		retval.assign("0x0734_Voice_Dialler_Read");
		break;
	case 0x0735:
		retval.assign("0x0735_Bypass_Zones_Read");
		break;
	case 0x0736:
		retval.assign("0x0736_Access_Codes_Read");
		break;
	case 0x0737:
		retval.assign("0x0737_Access_Codes_Attributes_Read");
		break;
	case 0x0738:
		retval.assign("0x0738_Access_Codes_Partition_Assignments_Read");
		break;
	case 0x0739:
		retval.assign("0x0739_Auto_Arm_Time_Read");
		break;
	case 0x073C:
		retval.assign("0x073C_User_Code_Configuration_Read");
		break;
	case 0x073D:
		retval.assign("0x073D_Late_To_Open_Time_Single_Day_Read");
		break;
	case 0x073E:
		retval.assign("0x073E_Auto_Arm_Time_Single_Day_Read");
		break;
	case 0x0741:
		retval.assign("0x0741_Time_And_Date_Write");
		break;
	case 0x0742:
		retval.assign("0x0742_Late_To_Open_Control_Write");
		break;
	case 0x0743:
		retval.assign("0x0743_Late_To_Open_Time_Write");
		break;
	case 0x0744:
		retval.assign("0x0744_Voice_Dialler_Write");
		break;
	case 0x0745:
		retval.assign("0x0745_Bypass_Zones_Write");
		break;
	case 0x0746:
		retval.assign("0x0746_Access_Codes_Write");
		break;
	case 0x0747:
		retval.assign("0x0747_Access_Codes_Attributes_Write");
		break;
	case 0x0748:
		retval.assign("0x0748_Access_Codes_Partition_Assignments_Write");
		break;
	case 0x0749:
		retval.assign("0x0749_Auto_Arm_Time_Write");
		break;
	case 0x074A:
		retval.assign("0x074A_Single_Zone_Bypass_Write");
		break;
	case 0x074B:
		retval.assign("0x074B_Group_Bypass_Write");
		break;
	case 0x074C:
		retval.assign("0x074C_Proximity_Tag_Write");
		break;
	case 0x074D:
		retval.assign("0x074D_Late_To_Open_Time_Single_Day_Write");
		break;
	case 0x074E:
		retval.assign("0x074E_Auto_Arm_Time_Single_Day_Write");
		break;
	case 0x074F:
		retval.assign("0x074F_Factory_Default_Programming");
		break;
	case 0x0750:
		retval.assign("0x0750_Access_Codes_Label_Write");
		break;
	case 0x0761:
		retval.assign("0x0761_Event_Reporting_Configuration_Read");
		break;
	case 0x0762:
		retval.assign("0x0762_Event_Reporting_Configuration_Write");
		break;
	case 0x0770:
		retval.assign("0x0770_Zone_Assignment_Configuration");
		break;
	case 0x0771:
		retval.assign("0x0771_Configuration_Broadcast");
		break;
	case 0x0772:
		retval.assign("0x0772_Partition_Assignment_Configuration");
		break;
	case 0x0773:
		retval.assign("0x0773_Virtual_Zone_To_Zone_Assignment_Configuration");
		break;
	case 0x0774:
		retval.assign("0x0774_Configuration_Broadcast_Extended");
		break;
	case 0x0775:
		retval.assign("0x0775_User_Partition_Assignment_Configuration");
		break;
	case 0x0800:
		retval.assign("0x0800_Command_Request");
		break;
	case 0x0810:
		retval.assign("0x0810_Global_Status");
		break;
	case 0x0811:
		retval.assign("0x0811_Zone_Status");
		break;
	case 0x0812:
		retval.assign("0x0812_Partition_Status");
		break;
	case 0x0813:
		retval.assign("0x0813_Zone_Bypass_Status");
		break;
	case 0x0814:
		retval.assign("0x0814_System_Troubles_Status");
		break;
	case 0x0815:
		retval.assign("0x0815_Alarm_Memory_Information");
		break;
	case 0x0816:
		retval.assign("0x0816_Bus_State");
		break;
	case 0x0817:
		retval.assign("0x0817_Trouble_Detail");
		break;
	case 0x0819:
		retval.assign("0x0819_Door_Chime_Status");
		break;
	case 0x0820:
		retval.assign("0x0820_Single_Zone_Bypass_Status");
		break;
	case 0x0821:
		retval.assign("0x0821_Grouped_Trouble_Status");
		break;
	case 0x0822:
		retval.assign("0x0822_System_Trouble_Status_New");
		break;
	case 0x0823:
		retval.assign("0x0823_Trouble_Detail_Notification");
		break;
	case 0x0840:
		retval.assign("0x0840_Zone_Alarm_Status");
		break;
	case 0x0841:
		retval.assign("0x0841_Miscellaneous_Alarm_Status");
		break;
	case 0x0842:
		retval.assign("0x0842_Diagnostic_Status");
		break;
	case 0x0900:
		retval.assign("0x0900_Partition_Arm_Control");
		break;
	case 0x0901:
		retval.assign("0x0901_Partition_Disarm_Control");
		break;
	case 0x0902:
		retval.assign("0x0902_Command_Output");
		break;
	case 0x0903:
		retval.assign("0x0903_System_Testing");
		break;
	case 0x0904:
		retval.assign("0x0904_Door_Chime_Status_Write");
		break;
	case 0x0905:
		retval.assign("0x0905_Enable_DLS_Window");
		break;
	case 0x0906:
		retval.assign("0x0906_User_Call_Up");
		break;
	case 0x0907:
		retval.assign("0x0907_Auto_Arm_Enable_Disable");
		break;
	case 0x0908:
		retval.assign("0x0908_Activate_FAP");
		break;
	case 0x0909:
		retval.assign("0x0909_Initiate_Label_Broadcast");
		break;
	case 0x0910:
		retval.assign("0x0910_Partition_Quick_Exit");
		break;
	case 0x0911:
		retval.assign("0x0911_Silence_Troubles");
		break;
	case 0x0912:
		retval.assign("0x0912_User_Activity");
		break;
	case 0x0913:
		retval.assign("0x0913_Partition_Banner_Display");
		break;
	case 0x0914:
		retval.assign("0x0914_Partition_Buzzer_Control");
		break;
	case 0x0915:
		retval.assign("0x0915_Virtual_Zone_Control");
		break;
	case 0x0916:
		retval.assign("0x0916_Set_Partition_Mode");
		break;
	case 0x0917:
		retval.assign("0x0917_Door_Chime_Status_Write_Extended");
		break;
	case 0x0C02:
		retval.assign("0x0C02_Image_File_Header_Command");
		break;
	case 0x0C03:
		retval.assign("0x0C03_File_Transfer_Data_Blocks");
		break;
	case 0x0F00:
		retval.assign("0x0F00_Virtual_Keypad_Control");
		break;
	case 0x0F01:
		retval.assign("0x0F01_Key_Pressed_Notification");
		break;
	case 0x0F02:
		retval.assign("0x0F02_LCD_Update_Notification");
		break;
	case 0x0F03:
		retval.assign("0x0F03_LCD_Cursor_Notification");
		break;
	case 0x0F04:
		retval.assign("0x0F04_LED_Status_Notification");
		break;
	case 0x4100:
		retval.assign("0x4100_Event_Buffer_Information_Response");
		break;
	case 0x4101:
		retval.assign("0x4101_Event_Buffer_Read_Response");
		break;
	case 0x4102:
		retval.assign("0x4102_Single_Event_Buffer_Read_Response");
		break;
	case 0x4103:
		retval.assign("0x4103_SMS_Preview_Read_Response");
		break;
	case 0x4104:
		retval.assign("0x4104_Single_SMS_Text_Read_Response");
		break;
	case 0x4721:
		retval.assign("0x4721_Section_Read_Response");
		break;
	case 0x4731:
		retval.assign("0x4731_Time_And_Date_Read_Response");
		break;
	case 0x4732:
		retval.assign("0x4732_Late_To_Open_Control_Read_Response");
		break;
	case 0x4733:
		retval.assign("0x4733_Late_To_Open_Time_Read_Response");
		break;
	case 0x4734:
		retval.assign("0x4734_Voice_Dialler_Read_Response");
		break;
	case 0x4735:
		retval.assign("0x4735_Bypass_Zones_Read_Response");
		break;
	case 0x4736:
		retval.assign("0x4736_Access_Codes_Read_Response");
		break;
	case 0x4737:
		retval.assign("0x4737_Access_Codes_Attributes_Read_Response");
		break;
	case 0x4738:
		retval.assign("0x4738_Access_Codes_Partition_Assignments_Read_Response");
		break;
	case 0x4739:
		retval.assign("0x4739_Auto_Arm_Time_Read_Response");
		break;
	case 0x473C:
		retval.assign("0x473C_User_Code_Configuration_Read_Response");
		break;
	case 0x473D:
		retval.assign("0x473D_Late_To_Open_Time_Single_Day_Read_Response");
		break;
	case 0x473E:
		retval.assign("0x473E_Auto_Arm_Time_Single_Day_Read_Response");
		break;
	case 0x4761:
		retval.assign("0x4761_Event_Reporting_Configuration_Read_Response");
		break;
	default:
		retval.assign("Unknown Command");
		break;
	}

	return retval;
}

//---------------------------------------------------------------------------

string CApplication::CommonEnumResultToString(int commonValue)
{

	//Print -1 / 0 as they are common values
	// else do nothing we can process the state as they are unique per enum

	//E.g.:
	//Default for all enums
	//	Not_Available		= -1,	/**< Reserved value for all enums, indicates Not Available on this product. */	
	//	Unknown				= 0,	/**< Reserved, default value, indicates not yet retrieved from product. */	

	//Valid product values follow

	if (commonValue <= 0)
	{
		switch (commonValue)
		{
			case -1:
				return "Value Is Not_Available\n";
				break;

			case 0:
				return"Value Is Unknown\n";

			default:
				printf("Undefined common (<=0) enum value of %d",commonValue);
				return ("Undefined common (<=0) enum value");
		}		
	}
	else
	{		
		return string();
	}
}

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#pragma GCC diagnostic pop
#else
#error "Undefined compiler information!"
#endif  //MS_VS_COMPILER

//---------------------------------------------------------------------------
