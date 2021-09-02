#ifndef DYNAMIC_CREATE_H
#define DYNAMIC_CREATE_H

#include <QByteArray>
#include <QVariant>
#include "PF_Common.h"

static QByteArray changeToba(int id, QVariant data, int& len){
    QVariantList list = data.toList();
    QByteArray byteArray;

    switch (id) {
    case MSG_EEPROM_0_ID:
        _c_MSG_EEPROM_0_msgType msg59;
        len = sizeof(msg59);
        msg59.Signals.IPC_BackLightLevelDaytime = list.at(0).toMap().value("value").toUInt();
        msg59.Signals.IPC_BackLightLevelNight = list.at(1).toMap().value("value").toUInt();
        msg59.Signals.IHU_BackLightLevel = list.at(2).toMap().value("value").toUInt();
        msg59.Signals.IPC_BackLightLevel = list.at(3).toMap().value("value").toUInt();
        msg59.Signals.Passenger_BackLightLevel = list.at(4).toMap().value("value").toUInt();
        msg59.Signals.IHU_BackLightLevelDaytime = list.at(5).toMap().value("value").toUInt();
        msg59.Signals.IHU_BackLightLevelNight = list.at(6).toMap().value("value").toUInt();
        msg59.Signals.BackLightingLuminance = list.at(7).toMap().value("value").toUInt();
        msg59.Signals.Diag_flag = list.at(8).toMap().value("value").toUInt();
        msg59.Signals.LanguageSet = list.at(9).toMap().value("value").toUInt();
        msg59.Signals.IPC_DiagAdjustValue = list.at(10).toMap().value("value").toUInt();
        msg59.Signals.IHU_DiagAdjustValue = list.at(11).toMap().value("value").toUInt();
        msg59.Signals.SPDLMTPA_SATUS = list.at(12).toMap().value("value").toUInt();
        msg59.Signals.SPDLMTPA_SETPOINT = list.at(13).toMap().value("value").toUInt();
        msg59.Signals.T1C_M36T_DEFINE = list.at(14).toMap().value("value").toUInt();
        msg59.Signals.CAR_SET_ASSIST_LINE = list.at(15).toMap().value("value").toUInt();
        msg59.Signals.CAR_SET_SIA_SWITCH = list.at(16).toMap().value("value").toUInt();
        msg59.Signals.AudioVolume = list.at(17).toMap().value("value").toUInt();
        msg59.Signals.reserved_bit = list.at(18).toMap().value("value").toUInt();
        msg59.Signals.u8ThemeSwitch = list.at(19).toMap().value("value").toUInt();
        msg59.Signals.u8LastMenu = list.at(20).toMap().value("value").toUInt();
        msg59.Signals.aubDiagOdoClearTimes = list.at(21).toMap().value("value").toUInt();
        msg59.Signals.FatigueSensitivity = list.at(22).toMap().value("value").toUInt();
        msg59.Signals.DistractionSensitivity = list.at(23).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg59, len);
        break;
    case MSG_EEPROM_1_ID:
        _c_MSG_EEPROM_1_msgType msg60;
        len = sizeof(msg60);
        msg60.Signals.CFG_Transmission = list.at(0).toMap().value("value").toUInt();
        msg60.Signals.CFG_EPB = list.at(1).toMap().value("value").toUInt();
        msg60.Signals.CFG_TPMS = list.at(2).toMap().value("value").toUInt();
        msg60.Signals.CFG_Engine = list.at(3).toMap().value("value").toUInt();
        msg60.Signals.CFG_PEPS = list.at(4).toMap().value("value").toUInt();
        msg60.Signals.CFG_ESP = list.at(5).toMap().value("value").toUInt();
        msg60.Signals.CFG_Driver_position = list.at(6).toMap().value("value").toUInt();
        msg60.Signals.CFG_Cruise = list.at(7).toMap().value("value").toUInt();
        msg60.Signals.CFG_Voltage_Display = list.at(8).toMap().value("value").toUInt();
        msg60.Signals.CFG_Multi_media = list.at(9).toMap().value("value").toUInt();
        msg60.Signals.CFG_Glow = list.at(10).toMap().value("value").toUInt();
        msg60.Signals.CFG_Rear_fog = list.at(11).toMap().value("value").toUInt();
        msg60.Signals.CFG_Boot_animation = list.at(12).toMap().value("value").toUInt();
        msg60.Signals.CFG_WaterInfuel = list.at(13).toMap().value("value").toUInt();
        msg60.Signals.CFG_OverspeedEn = list.at(14).toMap().value("value").toUInt();
        msg60.Signals.CFG_Clock = list.at(15).toMap().value("value").toUInt();
        msg60.Signals.CFG_Fuel_tank = list.at(16).toMap().value("value").toUInt();
        msg60.Signals.CFG_AutoLight = list.at(17).toMap().value("value").toUInt();
        msg60.Signals.CFG_Maintenance = list.at(18).toMap().value("value").toUInt();
        msg60.Signals.CFG_EPS = list.at(19).toMap().value("value").toUInt();
        msg60.Signals.CFG_Language = list.at(20).toMap().value("value").toUInt();
        msg60.Signals.CFG_Airbag = list.at(21).toMap().value("value").toUInt();
        msg60.Signals.CFG_FATIGUE_DRIVING = list.at(22).toMap().value("value").toUInt();
        msg60.Signals.CFG_Wheel_Deviation = list.at(23).toMap().value("value").toUInt();
        msg60.Signals.CFG_Overspeed_switch = list.at(24).toMap().value("value").toUInt();
        msg60.Signals.CFG_After_reset_info_display = list.at(25).toMap().value("value").toUInt();
        msg60.Signals.CFG_After_start_info_display = list.at(26).toMap().value("value").toUInt();
        msg60.Signals.CFG_SCR = list.at(27).toMap().value("value").toUInt();
        msg60.Signals.CFG_Mile_unit = list.at(28).toMap().value("value").toUInt();
        msg60.Signals.CFG_OverspeedSet = list.at(29).toMap().value("value").toUInt();
        msg60.Signals.CFG_PDC = list.at(30).toMap().value("value").toUInt();
        msg60.Signals.CFG_LCA = list.at(31).toMap().value("value").toUInt();
        msg60.Signals.CFG_LDW = list.at(32).toMap().value("value").toUInt();
        msg60.Signals.CFG_LKA = list.at(33).toMap().value("value").toUInt();
        msg60.Signals.CFG_FCM = list.at(34).toMap().value("value").toUInt();
        msg60.Signals.CFG_AEB = list.at(35).toMap().value("value").toUInt();
        msg60.Signals.CFG_TSR = list.at(36).toMap().value("value").toUInt();
        msg60.Signals.CFG_Seatbelt = list.at(37).toMap().value("value").toUInt();
        msg60.Signals.CFG_Seat_layout = list.at(38).toMap().value("value").toUInt();
        msg60.Signals.CFG_AWD = list.at(39).toMap().value("value").toUInt();
        msg60.Signals.CFG_Cruise_speed_display = list.at(40).toMap().value("value").toUInt();
        msg60.Signals.CFG_Navi_display = list.at(41).toMap().value("value").toUInt();
        msg60.Signals.CFG_Media_display = list.at(42).toMap().value("value").toUInt();
        msg60.Signals.CFG_Call_display = list.at(43).toMap().value("value").toUInt();
        msg60.Signals.CFG_Outside_Temp = list.at(44).toMap().value("value").toUInt();
        msg60.Signals.CFG_DPF = list.at(45).toMap().value("value").toUInt();
        msg60.Signals.CFG_Theme = list.at(46).toMap().value("value").toUInt();
        msg60.Signals.CFG_IHC = list.at(47).toMap().value("value").toUInt();
        msg60.Signals.CFG_TimeFormat = list.at(48).toMap().value("value").toUInt();
        msg60.Signals.CFG_ESCL = list.at(49).toMap().value("value").toUInt();
        msg60.Signals.Reserved = list.at(50).toMap().value("value").toUInt();
        msg60.Signals.Theme_Setting = list.at(51).toMap().value("value").toUInt();
        msg60.Signals.unused = list.at(52).toMap().value("value").toUInt();
        msg60.Signals.SPEAKERS = list.at(53).toMap().value("value").toUInt();
        msg60.Signals.MICROPHONE = list.at(54).toMap().value("value").toUInt();
        msg60.Signals.VEHICLEBACKUPCAMERA = list.at(55).toMap().value("value").toUInt();
        msg60.Signals.PANORAMICVISION = list.at(56).toMap().value("value").toUInt();
        msg60.Signals.Model = list.at(57).toMap().value("value").toUInt();
        msg60.Signals.PDCObstclWarning = list.at(58).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg60, len);
        break;
    case MSG_EEPROM_2_ID:
        _c_MSG_EEPROM_2_msgType msg61;
        len = sizeof(msg61);
        msg61.Signals.CLS_FUEL_LOW_BAR = list.at(0).toMap().value("value").toUInt();
        msg61.Signals.CLS_FUEL_LOW_RELEASE_BAR = list.at(1).toMap().value("value").toUInt();
        msg61.Signals.CLS_COOLANT_HIGH_BAR = list.at(2).toMap().value("value").toUInt();
        msg61.Signals.CLS_COOLANT_HIGH_RELEASE_BAR = list.at(3).toMap().value("value").toUInt();
        msg61.Signals.CLS_LAST_SOURCE_CURRENT_REQ_BAR = list.at(4).toMap().value("value").toUInt();
        msg61.Signals.CLS_LAST_SOURCE_CARINFO_REQ_BAR2 = list.at(5).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg61, len);
        break;
    case MSG_EEPROM_3_ID:
        _c_MSG_EEPROM_3_msgType msg62;
        len = sizeof(msg62);
        msg62.Signals.CFG_IFE_Range1 = list.at(0).toMap().value("value").toUInt();
        msg62.Signals.CFG_IFE_Range2 = list.at(1).toMap().value("value").toUInt();
        msg62.Signals.CFG_DTE_Fuel_Consumption_Idle = list.at(2).toMap().value("value").toUInt();
        msg62.Signals.CFG_DTE_Display_Direction = list.at(3).toMap().value("value").toUInt();
        msg62.Signals.Reserved0 = list.at(4).toMap().value("value").toUInt();
        msg62.Signals.Reserved1 = list.at(5).toMap().value("value").toUInt();
        msg62.Signals.CFG_AFE_Init = list.at(6).toMap().value("value").toUInt();
        msg62.Signals.CFG_AFE_Range = list.at(7).toMap().value("value").toUInt();
        msg62.Signals.CFG_DTE_Fuel_calculate = list.at(8).toMap().value("value").toUInt();
        msg62.Signals.CFG_Current_Fuel_Consumption_Distance = list.at(9).toMap().value("value").toUInt();
        msg62.Signals.CFG_MaxFuelConsumption = list.at(10).toMap().value("value").toUInt();
        msg62.Signals.CFG_Mainteance_distance = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg62, len);
        break;
    case MSG_EEPROM_4_ID:
        _c_MSG_EEPROM_4_msgType msg63;
        len = sizeof(msg63);
        msg63.Signals.softVersionNum[19] = list.at(0).toMap().value("value").toUInt();
        msg63.Signals.HardVersionNum[6] = list.at(1).toMap().value("value").toUInt();
        msg63.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg63, len);
        break;
    case MSG_DIDCTL_0_ID:
        _c_MSG_DIDCTL_0_msgType msg64;
        len = sizeof(msg64);
        msg64.Signals.DID_NUMBER = list.at(0).toMap().value("value").toUInt();
        msg64.Signals.SUB_FUNCTION_CODE = list.at(1).toMap().value("value").toUInt();
        msg64.Signals.CONTROLE_CODE = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg64, len);
        break;
    case MSG_MCU_0_ID:
        _c_MSG_MCU_0_msgType msg69;
        len = sizeof(msg69);
        msg69.Signals.MCU_VEHICLE_SPEED = list.at(0).toMap().value("value").toUInt();
        msg69.Signals.MCU_ENGINE_SPEED = list.at(1).toMap().value("value").toUInt();
        msg69.Signals.MCU_FUEL_LEVEL = list.at(2).toMap().value("value").toUInt();
        msg69.Signals.MCU_ENGINE_TEMPERATURE = list.at(3).toMap().value("value").toUInt();
        msg69.Signals.MCU_BATT_VAL = list.at(4).toMap().value("value").toUInt();
        msg69.Signals.MCU_Interface_Disp = list.at(5).toMap().value("value").toUInt();
        msg69.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg69, len);
        break;
    case MSG_MCU_1_ID:
        _c_MSG_MCU_1_msgType msg70;
        len = sizeof(msg70);
        msg70.Signals.MCU_RANGE = list.at(0).toMap().value("value").toUInt();
        msg70.Signals.MCU_INSTAT_FC = list.at(1).toMap().value("value").toUInt();
        msg70.Signals.MCU_ODO_SYNC_STATUS = list.at(2).toMap().value("value").toUInt();
        msg70.Signals.MCU_ODO_EEPGET = list.at(3).toMap().value("value").toUInt();
        msg70.Signals.MCU_INSTAT_FC_UNIT = list.at(4).toMap().value("value").toUInt();
        msg70.Signals.MCU_ODO_CLR_ENABLE = list.at(5).toMap().value("value").toUInt();
        msg70.Signals.MCU_ODO = list.at(6).toMap().value("value").toUInt();
        msg70.Signals.MCU_TRIP_A = list.at(7).toMap().value("value").toUInt();
        msg70.Signals.unused0 = list.at(8).toMap().value("value").toUInt();
        msg70.Signals.MCU_TRIP_B = list.at(9).toMap().value("value").toUInt();
        msg70.Signals.unused1 = list.at(10).toMap().value("value").toUInt();
        msg70.Signals.MCU_AVERAGE_SPEED_A = list.at(11).toMap().value("value").toUInt();
        msg70.Signals.MCU_AVERAGE_SPEED_B = list.at(12).toMap().value("value").toUInt();
        msg70.Signals.MCU_DRIVING_TIME_A = list.at(13).toMap().value("value").toUInt();
        msg70.Signals.MCU_DRIVING_TIME_B = list.at(14).toMap().value("value").toUInt();
        msg70.Signals.MCU_AVERAGE_FC_A = list.at(15).toMap().value("value").toUInt();
        msg70.Signals.MCU_AVERAGE_FC_B = list.at(16).toMap().value("value").toUInt();
        msg70.Signals.MCU_REMAINING_MAINTENANCE = list.at(17).toMap().value("value").toUInt();
        msg70.Signals.MCU_AMBIENT_TEMPERATURE = list.at(18).toMap().value("value").toUInt();
        msg70.Signals.BattVoltage = list.at(19).toMap().value("value").toUInt();
        msg70.Signals.TripBApc = list.at(20).toMap().value("value").toUInt();
        msg70.Signals.TripAApc = list.at(21).toMap().value("value").toUInt();
        msg70.Signals.MCU_SinceLastChargeTime = list.at(22).toMap().value("value").toUInt();
        msg70.Signals.MCU_SinceLastChargeOdo = list.at(23).toMap().value("value").toUInt();
        msg70.Signals.MCU_Recent100KmAPC = list.at(24).toMap().value("value").toUInt();
        msg70.Signals.MCU_Recent1KmAPC = list.at(25).toMap().value("value").toUInt();
        msg70.Signals.MCU_Recent100KmAPCSts = list.at(26).toMap().value("value").toUInt();
        msg70.Signals.MCU_Recent1KmAPCSts = list.at(27).toMap().value("value").toUInt();
        msg70.Signals.unused2 = list.at(28).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg70, len);
        break;
    case MSG_MCU_2_ID:
        _c_MSG_MCU_2_msgType msg71;
        len = sizeof(msg71);
        msg71.Signals.MCU_Hand_brake_Pin6 = list.at(0).toMap().value("value").toUInt();
        msg71.Signals.MCU_Brake_fluid_Pin7 = list.at(1).toMap().value("value").toUInt();
        msg71.Signals.MCU_Charge_Indicator_Pin8 = list.at(2).toMap().value("value").toUInt();
        msg71.Signals.reserved = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg71, len);
        break;
    case MSG_MCU_3_ID:
        _c_MSG_MCU_3_msgType msg72;
        len = sizeof(msg72);
        msg72.Signals.MCU_CLOCK_YEAR = list.at(0).toMap().value("value").toUInt();
        msg72.Signals.MCU_CLOCK_MONTH = list.at(1).toMap().value("value").toUInt();
        msg72.Signals.MCU_CLOCK_DAY = list.at(2).toMap().value("value").toUInt();
        msg72.Signals.MCU_CLOCK_HOUR = list.at(3).toMap().value("value").toUInt();
        msg72.Signals.MCU_CLOCK_MINUTE = list.at(4).toMap().value("value").toUInt();
        msg72.Signals.MCU_CLOCK_SECOND = list.at(5).toMap().value("value").toUInt();
        msg72.Signals.MCU_CLOCK_TIME_FORMAT = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg72, len);
        break;
    case MSG_MCU_4_ID:
        _c_MSG_MCU_4_msgType msg73;
        len = sizeof(msg73);
        msg73.Signals.MCU_CLUSTER_HARDL_KEY_NUMBER = list.at(0).toMap().value("value").toUInt();
        msg73.Signals.MCU_CLUSTER_HARDL_KEY_STATUS = list.at(1).toMap().value("value").toUInt();
        msg73.Signals.MCU_CLUSTER_HARDKEY_DRIVER_MODE = list.at(2).toMap().value("value").toUInt();
        msg73.Signals.MCU_CLUSTER_HARDKEY_LDW_LKA_BUTTON = list.at(3).toMap().value("value").toUInt();
        msg73.Signals.MCU_CLUSTER_HARDKEY_POWER = list.at(4).toMap().value("value").toUInt();
        msg73.Signals.reserved = list.at(5).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg73, len);
        break;
    case MSG_MCU_5_ID:
        _c_MSG_MCU_5_msgType msg74;
        len = sizeof(msg74);
        msg74.Signals.FuelLowWaring = list.at(0).toMap().value("value").toUInt();
        msg74.Signals.CoolantTtState = list.at(1).toMap().value("value").toUInt();
        msg74.Signals.CLS_FAD_WARNING = list.at(2).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_STATUS = list.at(3).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_DISTSTATUS = list.at(4).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_DAYSTATUS = list.at(5).toMap().value("value").toUInt();
        msg74.Signals.CoolantPopState = list.at(6).toMap().value("value").toUInt();
        msg74.Signals.CLS_TT_BATT_COLOR = list.at(7).toMap().value("value").toUInt();
        msg74.Signals.reserved = list.at(8).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_LASTODO = list.at(9).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_INVLDAY = list.at(10).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_LASTDATE = list.at(11).toMap().value("value").toUInt();
        msg74.Signals.CLS_SIA_INVLDIST = list.at(12).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg74, len);
        break;
    case MSG_MCU_6_ID:
        _c_MSG_MCU_6_msgType msg75;
        len = sizeof(msg75);
        msg75.Signals.StartLightCnt = list.at(0).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg75, len);
        break;
    case MSG_ESC_HMIInfo_136h_ID:
        _c_136_ESC_HMIInfo_msgType msg76;
        len = sizeof(msg76);
        msg76.Signals.ESC_BrkLiActvnReq = list.at(0).toMap().value("value").toUInt();
        msg76.Signals.ESC_HmiLampReqEpbActv = list.at(1).toMap().value("value").toUInt();
        msg76.Signals.ESC_HmiLampReqEpbFlt = list.at(2).toMap().value("value").toUInt();
        msg76.Signals.ESC_HmiLampReqBrkSys = list.at(3).toMap().value("value").toUInt();
        msg76.Signals.ESC_HMIDrvPrstInAVH = list.at(4).toMap().value("value").toUInt();
        msg76.Signals.ESC_HmiLampReqEsc = list.at(5).toMap().value("value").toUInt();
        msg76.Signals.ESC_AdpvBrkLiActvnReq = list.at(6).toMap().value("value").toUInt();
        msg76.Signals.IsTimeout = list.at(7).toMap().value("value").toUInt();
        msg76.Signals.E2Estatus = list.at(8).toMap().value("value").toUInt();
        msg76.Signals.ESC_HmiTxtReqScm = list.at(9).toMap().value("value").toUInt();
        msg76.Signals.ESC_HmiLampReqHdc = list.at(10).toMap().value("value").toUInt();
        msg76.Signals.unused0 = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg76, len);
        break;
    case MSG_VCU_WarnForHU_148_ID:
        _c_148_VCU_WarnForHU_msgType msg77;
        len = sizeof(msg77);
        msg77.Signals.VCU_CoolantAlarmHMI = list.at(0).toMap().value("value").toUInt();
        msg77.Signals.VCU_BatteryHeatCriticalHMI = list.at(1).toMap().value("value").toUInt();
        msg77.Signals.VCU_SystemFailureHMI = list.at(2).toMap().value("value").toUInt();
        msg77.Signals.VCU_SystemPowerLimitationHMI = list.at(3).toMap().value("value").toUInt();
        msg77.Signals.VCU_EMotorAlarmHMI = list.at(4).toMap().value("value").toUInt();
        msg77.Signals.IsTimeout = list.at(5).toMap().value("value").toUInt();
        msg77.Signals.E2Estatus = list.at(6).toMap().value("value").toUInt();
        msg77.Signals.unused0 = list.at(7).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg77, len);
        break;
    case MSG_BCM_LightReq_151h_ID:
        _c_151_BCM_LightReq_msgType msg78;
        len = sizeof(msg78);
        msg78.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiSideDirIndcrReq = list.at(1).toMap().value("value").toUInt();
        msg78.Signals.BCM_LeDirIndcrTelltlLampReq = list.at(2).toMap().value("value").toUInt();
        msg78.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg78.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg78.Signals.BCM_FrntAxleLvlSnsrRawVal = list.at(5).toMap().value("value").toUInt();
        msg78.Signals.BCM_ReAxleLvlSnsrRawVal = list.at(6).toMap().value("value").toUInt();
        msg78.Signals.BCM_ReFogLiTelltlLampReq = list.at(7).toMap().value("value").toUInt();
        msg78.Signals.BCM_LeSideDirIndcrReq = list.at(8).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiPosnLiReq = list.at(9).toMap().value("value").toUInt();
        msg78.Signals.BCM_LoBeamTelltlLampReq = list.at(10).toMap().value("value").toUInt();
        msg78.Signals.BCM_HiBeamReq = list.at(11).toMap().value("value").toUInt();
        msg78.Signals.BCM_LeWelcomePrjnRotReq = list.at(12).toMap().value("value").toUInt();
        msg78.Signals.BCM_ReFogLiSt = list.at(13).toMap().value("value").toUInt();
        msg78.Signals.BCM_LeDaytiRunngLiReq = list.at(14).toMap().value("value").toUInt();
        msg78.Signals.BCM_PosnLiSt = list.at(15).toMap().value("value").toUInt();
        msg78.Signals.unused1 = list.at(16).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiWelcomePrjnReq = list.at(17).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiWelcomePrjnRotReq = list.at(18).toMap().value("value").toUInt();
        msg78.Signals.BCM_LoBeamReq = list.at(19).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiDirIndcrTelltlLampReq = list.at(20).toMap().value("value").toUInt();
        msg78.Signals.BCM_LePosnLiReq = list.at(21).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiFrntDirIndcrReq = list.at(22).toMap().value("value").toUInt();
        msg78.Signals.BCM_LeFrntDirIndcrReq = list.at(23).toMap().value("value").toUInt();
        msg78.Signals.BCM_PosnLiTelltlLampReq = list.at(24).toMap().value("value").toUInt();
        msg78.Signals.BCM_HiBeamTelltlLampReq = list.at(25).toMap().value("value").toUInt();
        msg78.Signals.BCM_BCMHBAMXBReq = list.at(26).toMap().value("value").toUInt();
        msg78.Signals.unused2 = list.at(27).toMap().value("value").toUInt();
        msg78.Signals.BCM_KeyDetectWarn = list.at(28).toMap().value("value").toUInt();
        msg78.Signals.BCM_LeWelcomePrjnReq = list.at(29).toMap().value("value").toUInt();
        msg78.Signals.BCM_RiDaytiRunngLiReq = list.at(30).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg78, len);
        break;
    case MSG_VCU_AccPosGearSts_97h_ID:
        _c_97_VCU_AccPosGearSts_msgType msg79;
        len = sizeof(msg79);
        msg79.Signals.VCU_AccrPosnAct = list.at(0).toMap().value("value").toUInt();
        msg79.Signals.IsTimeout = list.at(1).toMap().value("value").toUInt();
        msg79.Signals.VCU_AccrPosnActVldy = list.at(2).toMap().value("value").toUInt();
        msg79.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg79.Signals.unused1 = list.at(4).toMap().value("value").toUInt();
        msg79.Signals.VCU_VehSpdLimReqdPtl = list.at(5).toMap().value("value").toUInt();
        msg79.Signals.unused0 = list.at(6).toMap().value("value").toUInt();
        msg79.Signals.VCU_PtSt = list.at(7).toMap().value("value").toUInt();
        msg79.Signals.VCU_LoglGearStsAct = list.at(8).toMap().value("value").toUInt();
        msg79.Signals.VCU_VirtAccrPedlPosnVldy = list.at(9).toMap().value("value").toUInt();
        msg79.Signals.VCU_VirtAccrPedlPosn = list.at(10).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg79, len);
        break;
    case MSG_VCU_HvInfForDrvr_9Ah_ID:
        _c_9A_VCU_HvInfForDrvr_msgType msg80;
        len = sizeof(msg80);
        msg80.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg80.Signals.VCU_CoastLvlAct = list.at(1).toMap().value("value").toUInt();
        msg80.Signals.VCU_InvldCdnToDrvr = list.at(2).toMap().value("value").toUInt();
        msg80.Signals.VCU_ElecPtLimdDecelSts = list.at(3).toMap().value("value").toUInt();
        msg80.Signals.unused0 = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg80, len);
        break;
    case MSG_VCU_HvCoolgModReq_98h_ID:
        _c_98_VCU_HvCoolgModReq_msgType msg81;
        len = sizeof(msg81);
        msg81.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg81.Signals.E2Estatus = list.at(1).toMap().value("value").toUInt();
        msg81.Signals.VCU_LvDegradationDem = list.at(2).toMap().value("value").toUInt();
        msg81.Signals.VCU_AvlDrvMod = list.at(3).toMap().value("value").toUInt();
        msg81.Signals.VCU_ActvdDrvMod = list.at(4).toMap().value("value").toUInt();
        msg81.Signals.VCU_HvCoolgModReq_RollingCounter = list.at(5).toMap().value("value").toUInt();
        msg81.Signals.unused0 = list.at(6).toMap().value("value").toUInt();
        msg81.Signals.VCU_HvCoolgModReq_Checksum = list.at(7).toMap().value("value").toUInt();
        msg81.Signals.VCU_ChrgSts = list.at(8).toMap().value("value").toUInt();
        msg81.Signals.unused1 = list.at(9).toMap().value("value").toUInt();
        msg81.Signals.VCU_DisChrgTarSOCRsp = list.at(10).toMap().value("value").toUInt();
        msg81.Signals.VCU_HvBattSocDrv = list.at(11).toMap().value("value").toUInt();
        msg81.Signals.unused2 = list.at(12).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg81, len);
        break;
    case MSG_EPS_EPSInfo_130h_ID:
        _c_ICGM_EPS_335h_IP_msgType msg82;
        len = sizeof(msg82);
        msg82.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg82.Signals.EPSFail_WL = list.at(1).toMap().value("value").toUInt();
        msg82.Signals.EPSMessageCounter = list.at(2).toMap().value("value").toUInt();
        msg82.Signals.unused0 = list.at(3).toMap().value("value").toUInt();
        msg82.Signals.EPSChecksum = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg82, len);
        break;
    case MSG_ACM_ACMInfo_201h_ID:
        _c_201_ACM_ACMInfo_msgType msg84;
        len = sizeof(msg84);
        msg84.Signals.ACM_CrashOutpSts = list.at(0).toMap().value("value").toUInt();
        msg84.Signals.ACM_CrashSevLvl = list.at(1).toMap().value("value").toUInt();
        msg84.Signals.ACM_FrntCrashOutpSts = list.at(2).toMap().value("value").toUInt();
        msg84.Signals.ACM_PedProtnCrashOutpSts = list.at(3).toMap().value("value").toUInt();
        msg84.Signals.ACM_RiSideCrashOutpSts = list.at(4).toMap().value("value").toUInt();
        msg84.Signals.ACM_RollovrCrashOutpSts = list.at(5).toMap().value("value").toUInt();
        msg84.Signals.ACM_RearCrashOutpSts = list.at(6).toMap().value("value").toUInt();
        msg84.Signals.IsTimeout = list.at(7).toMap().value("value").toUInt();
        msg84.Signals.ACM_LeSideCrashOutpSts = list.at(8).toMap().value("value").toUInt();
        msg84.Signals.ACM_BucSwtSt2ndSeatRowLe = list.at(9).toMap().value("value").toUInt();
        msg84.Signals.ACM_BucSwtStFrntPass = list.at(10).toMap().value("value").toUInt();
        msg84.Signals.ACM_BucSwtStFrntDrvr = list.at(11).toMap().value("value").toUInt();
        msg84.Signals.ACM_EmgyCall = list.at(12).toMap().value("value").toUInt();
        msg84.Signals.ACM_AirbWarnLampSt = list.at(13).toMap().value("value").toUInt();
        msg84.Signals.ACM_BucSwtSt2ndSeatRowRi = list.at(14).toMap().value("value").toUInt();
        msg84.Signals.ACM_BucSwtSt2ndSeatRowCentr = list.at(15).toMap().value("value").toUInt();
        msg84.Signals.E2Estatus = list.at(16).toMap().value("value").toUInt();
        msg84.Signals.unused1 = list.at(17).toMap().value("value").toUInt();
        msg84.Signals.ACM_OccptDetnSt2ndSeatRowRi = list.at(18).toMap().value("value").toUInt();
        msg84.Signals.ACM_OccptDetnSt2ndSeatRowCentr = list.at(19).toMap().value("value").toUInt();
        msg84.Signals.ACM_OccptDetnSt2ndSeatRowLe = list.at(20).toMap().value("value").toUInt();
        msg84.Signals.ACM_OccptDetnStPassSeat = list.at(21).toMap().value("value").toUInt();
        msg84.Signals.ACM_SeatTrkPosnSwtFrntPass = list.at(22).toMap().value("value").toUInt();
        msg84.Signals.ACM_SeatTrkPosnSwtFrntDrvr = list.at(23).toMap().value("value").toUInt();
        msg84.Signals.ACM_ACMInfo_RollingCounter = list.at(24).toMap().value("value").toUInt();
        msg84.Signals.ACM_ACMInfo_Checksum = list.at(25).toMap().value("value").toUInt();
        msg84.Signals.unused0 = list.at(26).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg84, len);
        break;
    case MSG_CCU_AirT_1F7h_ID:
        _c_1F7_CCU_AirT_msgType msg85;
        len = sizeof(msg85);
        msg85.Signals.CCU_AmbAirT = list.at(0).toMap().value("value").toUInt();
        msg85.Signals.IsTimeout = list.at(1).toMap().value("value").toUInt();
        msg85.Signals.E2Estatus = list.at(2).toMap().value("value").toUInt();
        msg85.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg85, len);
        break;
    case MSG_BMS_BatSocU_F9_ID:
        _c_F9_BMS_BatSocU_msgType msg86;
        len = sizeof(msg86);
        msg86.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg86.Signals.BMS_HvBattU = list.at(1).toMap().value("value").toUInt();
        msg86.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg86, len);
        break;
    case MSG_BMS_HVBatterySts_FB_ID:
        _c_FB_BMS_HVBatterySts_msgType msg87;
        len = sizeof(msg87);
        msg87.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg87.Signals.BMS_HvBattI = list.at(1).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg87, len);
        break;
    case MSG_BCM_AlrmWarnIn_245_ID:
        _c_245_BCM_AlrmWarnIn_msgType msg88;
        len = sizeof(msg88);
        msg88.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg88.Signals.BCM_AutHdlampLvlgLtgCdnSt = list.at(1).toMap().value("value").toUInt();
        msg88.Signals.BCM_HoodNotClsdWarnReq = list.at(2).toMap().value("value").toUInt();
        msg88.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg88.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg88.Signals.BCM_ChdLockErrSt = list.at(5).toMap().value("value").toUInt();
        msg88.Signals.BCM_WtrLvlDisp = list.at(6).toMap().value("value").toUInt();
        msg88.Signals.BCM_PasSettingCfgFb = list.at(7).toMap().value("value").toUInt();
        msg88.Signals.BCM_RedGuardCfgFb = list.at(8).toMap().value("value").toUInt();
        msg88.Signals.BCM_PepsKeyFobInVehSt = list.at(9).toMap().value("value").toUInt();
        msg88.Signals.BCM_BrkFldLvlDisp = list.at(10).toMap().value("value").toUInt();
        msg88.Signals.BCM_KeyFobInsVehSt = list.at(11).toMap().value("value").toUInt();
        msg88.Signals.BCM_ChrgnFlapRiNotClsdWarnReq = list.at(12).toMap().value("value").toUInt();
        msg88.Signals.BCM_ChrgnFlapNotClsdWarnReq = list.at(13).toMap().value("value").toUInt();
        msg88.Signals.BCM_PepsAdvKeyFobBattChrgnSt = list.at(14).toMap().value("value").toUInt();
        msg88.Signals.BCM_TrNotClsdWarnReq = list.at(15).toMap().value("value").toUInt();
        msg88.Signals.BCM_DoorRearLeNotClsdWarnReq = list.at(16).toMap().value("value").toUInt();
        msg88.Signals.BCM_DoorRearRiNotClsdWarnReq = list.at(17).toMap().value("value").toUInt();
        msg88.Signals.BCM_DoorPassNotClsdWarnReq = list.at(18).toMap().value("value").toUInt();
        msg88.Signals.BCM_DoorDrvrNotClsdWarnReq = list.at(19).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg88, len);
        break;
    case MSG_AVAS_CurrSts_17F_ID:
        _c_17F_AVAS_CurrSts_msgType msg89;
        len = sizeof(msg89);
        msg89.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg89.Signals.AVAS_AVASShowCurrSoundSeln = list.at(1).toMap().value("value").toUInt();
        msg89.Signals.AVAS_AVASShowCurrSts = list.at(2).toMap().value("value").toUInt();
        msg89.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg89, len);
        break;
    case MSG_BCM_TireWarn_246_ID:
        _c_246_BCM_TireWarn_msgType msg90;
        len = sizeof(msg90);
        msg90.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg90.Signals.unused0 = list.at(1).toMap().value("value").toUInt();
        msg90.Signals.BCM_TireWarnReLe = list.at(2).toMap().value("value").toUInt();
        msg90.Signals.BCM_TireWarnReRi = list.at(3).toMap().value("value").toUInt();
        msg90.Signals.BCM_TireWarnFrntLe = list.at(4).toMap().value("value").toUInt();
        msg90.Signals.BCM_TireWarnFrntRi = list.at(5).toMap().value("value").toUInt();
        msg90.Signals.unused1 = list.at(6).toMap().value("value").toUInt();
        msg90.Signals.BCM_TireWarn_RollgCntr = list.at(7).toMap().value("value").toUInt();
        msg90.Signals.unused2 = list.at(8).toMap().value("value").toUInt();
        msg90.Signals.BCM_TireWarn_Chks = list.at(9).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg90, len);
        break;
    case MSG_BCM_TireP_247_ID:
        _c_247_BCM_TireP_msgType msg91;
        len = sizeof(msg91);
        msg91.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg91.Signals.unused0 = list.at(1).toMap().value("value").toUInt();
        msg91.Signals.BCM_TirePReLe = list.at(2).toMap().value("value").toUInt();
        msg91.Signals.BCM_TirePReRi = list.at(3).toMap().value("value").toUInt();
        msg91.Signals.BCM_TirePFrntLe = list.at(4).toMap().value("value").toUInt();
        msg91.Signals.BCM_TirePFrntRi = list.at(5).toMap().value("value").toUInt();
        msg91.Signals.unused1 = list.at(6).toMap().value("value").toUInt();
        msg91.Signals.BCM_TireP_RollgCntr = list.at(7).toMap().value("value").toUInt();
        msg91.Signals.unused2 = list.at(8).toMap().value("value").toUInt();
        msg91.Signals.BCM_TireP_Chks = list.at(9).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg91, len);
        break;
    case MSG_BCM_TireT_248_ID:
        _c_248_BCM_TireT_msgType msg92;
        len = sizeof(msg92);
        msg92.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireMonTireSts = list.at(1).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireMonSysSts = list.at(2).toMap().value("value").toUInt();
        msg92.Signals.unused0 = list.at(3).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireTReLe = list.at(4).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireTReRi = list.at(5).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireTFrntLe = list.at(6).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireTFrntRi = list.at(7).toMap().value("value").toUInt();
        msg92.Signals.unused1 = list.at(8).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireT_RollgCntr = list.at(9).toMap().value("value").toUInt();
        msg92.Signals.unused2 = list.at(10).toMap().value("value").toUInt();
        msg92.Signals.BCM_TireT_Chks = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg92, len);
        break;
    case MSG_BCM_CANFD_212_ID:
        _c_212_BCM_CANFD_msgType msg93;
        len = sizeof(msg93);
        msg93.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg93.Signals.E2Estatus = list.at(1).toMap().value("value").toUInt();
        msg93.Signals.BCM_HmiLampReqBrkPadWarn = list.at(2).toMap().value("value").toUInt();
        msg93.Signals.BCM_PASSwtPsd = list.at(3).toMap().value("value").toUInt();
        msg93.Signals.BCM_ErrWipr = list.at(4).toMap().value("value").toUInt();
        msg93.Signals.BCM_MidHiBrkLiFailrSts = list.at(5).toMap().value("value").toUInt();
        msg93.Signals.BCM_ImobBkpWarn = list.at(6).toMap().value("value").toUInt();
        msg93.Signals.BCM_LvlBattULoWarn = list.at(7).toMap().value("value").toUInt();
        msg93.Signals.BCM_EgyLvlDegradationWarn = list.at(8).toMap().value("value").toUInt();
        msg93.Signals.BCM_AutoWiprCtrlWarn = list.at(9).toMap().value("value").toUInt();
        msg93.Signals.BCM_KeyInsideWarn = list.at(10).toMap().value("value").toUInt();
        msg93.Signals.BCM_BrkPedlIndcnWarn = list.at(11).toMap().value("value").toUInt();
        msg93.Signals.BCM_PwrRlyErrWarn = list.at(12).toMap().value("value").toUInt();
        msg93.Signals.BCM_AutoLiCtrlWarn = list.at(13).toMap().value("value").toUInt();
        msg93.Signals.BCM_HeadLightOpenWarn = list.at(14).toMap().value("value").toUInt();
        msg93.Signals.BCM_ReLeRvsLiFailrSts = list.at(15).toMap().value("value").toUInt();
        msg93.Signals.BCM_ReRiRvsLiFailrSts = list.at(16).toMap().value("value").toUInt();
        msg93.Signals.BCM_ReLeFogFailrSts = list.at(17).toMap().value("value").toUInt();
        msg93.Signals.BCM_ReLeBrkLiFailrSts = list.at(18).toMap().value("value").toUInt();
        msg93.Signals.BCM_ReRiBrkLiFailrSts = list.at(19).toMap().value("value").toUInt();
        msg93.Signals.BCM_ReRiFogFailrSts = list.at(20).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg93, len);
        break;
    case MSG_ESC_HmiLampReq_138_ID:
        _c_138_ESC_HmiLampReq_msgType msg94;
        len = sizeof(msg94);
        msg94.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReqHHCFlt = list.at(1).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReqEPBMode = list.at(2).toMap().value("value").toUInt();
        msg94.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg94.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReqAVHSts = list.at(5).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReqABS = list.at(6).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReqTCSOff = list.at(7).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReqTCS = list.at(8).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReq_RollgCntr = list.at(9).toMap().value("value").toUInt();
        msg94.Signals.unused5 = list.at(10).toMap().value("value").toUInt();
        msg94.Signals.ESC_HmiLampReq_Chks = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg94, len);
        break;
    case MSG_ESC_FctSt_131_ID:
        _c_131_ESC_FctSt_msgType msg95;
        len = sizeof(msg95);
        msg95.Signals.ESC_VehYawRate = list.at(0).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrAvlTcs = list.at(1).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrAvlAbs = list.at(2).toMap().value("value").toUInt();
        msg95.Signals.IsTimeout = list.at(3).toMap().value("value").toUInt();
        msg95.Signals.ESC_EpbSts = list.at(4).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctAvlHbb = list.at(5).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrAvlEbd = list.at(6).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctActvCdp = list.at(7).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrActvTcs = list.at(8).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrActvDtc = list.at(9).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrActvEbd = list.at(10).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrActvAbs = list.at(11).toMap().value("value").toUInt();
        msg95.Signals.ESC_EscSysSts = list.at(12).toMap().value("value").toUInt();
        msg95.Signals.ESC_BrkPedlStsVldy = list.at(13).toMap().value("value").toUInt();
        msg95.Signals.ESC_BrkPedlSts = list.at(14).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctAvlCdp = list.at(15).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctAvlAvh = list.at(16).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctActvAvh = list.at(17).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctActvHba = list.at(18).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctAvlHba = list.at(19).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrAvlEsc = list.at(20).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctActvHdc = list.at(21).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctActvHbb = list.at(22).toMap().value("value").toUInt();
        msg95.Signals.ESC_VehMovgDir = list.at(23).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctSt_RollingCounter = list.at(24).toMap().value("value").toUInt();
        msg95.Signals.ESC_PrimBrkSysAvl = list.at(25).toMap().value("value").toUInt();
        msg95.Signals.E2Estatus = list.at(26).toMap().value("value").toUInt();
        msg95.Signals.ESC_CtrlrActvEsc = list.at(27).toMap().value("value").toUInt();
        msg95.Signals.ESC_FctSt_Checksum = list.at(28).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg95, len);
        break;
    case MSG_SUM_SuspSts_1BC_ID:
        _c_1BC_SUM_SuspSts_msgType msg96;
        len = sizeof(msg96);
        msg96.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg96.Signals.SUM_SuspChassisHeiMovmtDir = list.at(1).toMap().value("value").toUInt();
        msg96.Signals.SUM_SuspChassisHeiMovmtDirValid = list.at(2).toMap().value("value").toUInt();
        msg96.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg96, len);
        break;
    case MSG_SUM_SuspSys_17C_ID:
        _c_17C_SUM_SuspSys_msgType msg97;
        len = sizeof(msg97);
        msg97.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg97.Signals.SUM_SuspSysProtnSts = list.at(1).toMap().value("value").toUInt();
        msg97.Signals.SUM_SuspSysFailrSts = list.at(2).toMap().value("value").toUInt();
        msg97.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg97.Signals.SUM_SuspChassisDamperModAct = list.at(4).toMap().value("value").toUInt();
        msg97.Signals.SUM_DampCtrlLimpHome = list.at(5).toMap().value("value").toUInt();
        msg97.Signals.unused1 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg97, len);
        break;
    case MSG_BMS_BatteryRelayErrSts_F7_ID:
        _c_F7_BMS_BatteryRelayErrSts_msgType msg98;
        len = sizeof(msg98);
        msg98.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg98.Signals.BMS_VehHvIsoErr = list.at(1).toMap().value("value").toUInt();
        msg98.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg98, len);
        break;
    case MSG_IPU_DCDCSts_DB_ID:
        _c_DB_IPU_DCDCSts_msgType msg99;
        len = sizeof(msg99);
        msg99.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg99.Signals.IPU_EEMDCDCFailrSts = list.at(1).toMap().value("value").toUInt();
        msg99.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg99, len);
        break;
    case MSG_VCU_CurrEngPwr_2F1_ID:
        _c_2F1_VCU_CurrEngPwr_msgType msg100;
        len = sizeof(msg100);
        msg100.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg100.Signals.VCU_CurrEngPwr = list.at(1).toMap().value("value").toUInt();
        msg100.Signals.VCU_CurrEngPwr_RollingCounter = list.at(2).toMap().value("value").toUInt();
        msg100.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg100.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg100.Signals.VCU_CurrEngPwr_Checksum = list.at(5).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg100, len);
        break;
    case MSG_BMS_HvBattTiRmnChrgn_200_ID:
        _c_200_BMS_HvBattTiRmnChrgn_msgType msg101;
        len = sizeof(msg101);
        msg101.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg101.Signals.BMS_HVBattThermRunaway = list.at(1).toMap().value("value").toUInt();
        msg101.Signals.E2Estatus = list.at(2).toMap().value("value").toUInt();
        msg101.Signals.unused0 = list.at(3).toMap().value("value").toUInt();
        msg101.Signals.BMS_HvBattTiRmnChrgn = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg101, len);
        break;
    case MSG_VCU_ReminDrvgRng_B3_ID:
        _c_B3_VCU_ReminDrvgRng_msgType msg102;
        len = sizeof(msg102);
        msg102.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg102.Signals.VCU_ChrgCnctrDetd = list.at(1).toMap().value("value").toUInt();
        msg102.Signals.VCU_ChassisHeiRaisedTranSuc = list.at(2).toMap().value("value").toUInt();
        msg102.Signals.VCU_SpdLimiterStsAct = list.at(3).toMap().value("value").toUInt();
        msg102.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg102.Signals.VCU_RmnDrvgRng = list.at(5).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg102, len);
        break;
    case MSG_SCM_States_183_ID:
        _c_183_SCM_States_msgType msg103;
        len = sizeof(msg103);
        msg103.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg103.Signals.SCM_HiBeamSwtFailrSts = list.at(1).toMap().value("value").toUInt();
        msg103.Signals.SCM_E_ShiftFault = list.at(2).toMap().value("value").toUInt();
        msg103.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg103, len);
        break;
    case MSG_ADAS_AEB_169_ID:
        _c_169_ADAS_AEB_msgType msg104;
        len = sizeof(msg104);
        msg104.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg104.Signals.ADAS_AdasBrkJerkReq = list.at(1).toMap().value("value").toUInt();
        msg104.Signals.E2Estatus = list.at(2).toMap().value("value").toUInt();
        msg104.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg104, len);
        break;
    case MSG_ADAS_TSRSts_1C1_ID:
        _c_1C1_ADAS_TSRSts_msgType msg105;
        len = sizeof(msg105);
        msg105.Signals.ADAS_TSRTrfcSignVal = list.at(0).toMap().value("value").toUInt();
        msg105.Signals.IsTimeout = list.at(1).toMap().value("value").toUInt();
        msg105.Signals.ADAS_TSR_Warn_Offset_St = list.at(2).toMap().value("value").toUInt();
        msg105.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg105.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg105.Signals.ADAS_TSR_SpeedLimitUnit = list.at(5).toMap().value("value").toUInt();
        msg105.Signals.ADAS_TSR_SpeedLimitype = list.at(6).toMap().value("value").toUInt();
        msg105.Signals.ADAS_TSR_Operating_St = list.at(7).toMap().value("value").toUInt();
        msg105.Signals.ADAS_TSR_LimitSpeed = list.at(8).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg105, len);
        break;
    case MSG_ADAS_FCTA_1C2_ID:
        _c_1C2_ADAS_FCTA_msgType msg106;
        len = sizeof(msg106);
        msg106.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg106.Signals.ADAS_FCTB_St = list.at(1).toMap().value("value").toUInt();
        msg106.Signals.E2Estatus = list.at(2).toMap().value("value").toUInt();
        msg106.Signals.ADAS_FCTA_St = list.at(3).toMap().value("value").toUInt();
        msg106.Signals.ADAS_FCTA_Right_Warn_St = list.at(4).toMap().value("value").toUInt();
        msg106.Signals.ADAS_FCTA_Left_Warn_St = list.at(5).toMap().value("value").toUInt();
        msg106.Signals.unused1 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg106, len);
        break;
    case MSG_ADAS_FCTASts_1C3_ID:
        _c_1C3_ADAS_FCTASts_msgType msg107;
        len = sizeof(msg107);
        msg107.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg107.Signals.ADAS_FCS_TargetType = list.at(1).toMap().value("value").toUInt();
        msg107.Signals.ADAS_AdasEbReqTyp = list.at(2).toMap().value("value").toUInt();
        msg107.Signals.ADAS_FCWRequest = list.at(3).toMap().value("value").toUInt();
        msg107.Signals.ADAS_FCW_St = list.at(4).toMap().value("value").toUInt();
        msg107.Signals.ADAS_FCWSensitvity_St = list.at(5).toMap().value("value").toUInt();
        msg107.Signals.E2Estatus = list.at(6).toMap().value("value").toUInt();
        msg107.Signals.unused0 = list.at(7).toMap().value("value").toUInt();
        msg107.Signals.ADAS_AEB_St = list.at(8).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg107, len);
        break;
    case MSG_ADAS_DOWSts_1C4_ID:
        _c_1C4_ADAS_DOWSts_msgType msg108;
        len = sizeof(msg108);
        msg108.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg108.Signals.ADAS_DOW_FL_Warn_St = list.at(1).toMap().value("value").toUInt();
        msg108.Signals.ADAS_DOW_St = list.at(2).toMap().value("value").toUInt();
        msg108.Signals.ADAS_AdasDirIndcrReq = list.at(3).toMap().value("value").toUInt();
        msg108.Signals.E2Estatus = list.at(4).toMap().value("value").toUInt();
        msg108.Signals.ADAS_RCW_Warn_St = list.at(5).toMap().value("value").toUInt();
        msg108.Signals.ADAS_DOW_RR_Warn_St = list.at(6).toMap().value("value").toUInt();
        msg108.Signals.ADAS_RCW_St = list.at(7).toMap().value("value").toUInt();
        msg108.Signals.ADAS_RCTA_St = list.at(8).toMap().value("value").toUInt();
        msg108.Signals.ADAS_LCA_St = list.at(9).toMap().value("value").toUInt();
        msg108.Signals.ADAS_DOW_FR_Warn_St = list.at(10).toMap().value("value").toUInt();
        msg108.Signals.ADAS_RCTB_St = list.at(11).toMap().value("value").toUInt();
        msg108.Signals.ADAS_RCTA_left_Warn_St = list.at(12).toMap().value("value").toUInt();
        msg108.Signals.ADAS_DOW_RL_Warn_St = list.at(13).toMap().value("value").toUInt();
        msg108.Signals.ADAS_RCTA_Right_Warn_St = list.at(14).toMap().value("value").toUInt();
        msg108.Signals.ADAS_LCA_Left_Warn_St = list.at(15).toMap().value("value").toUInt();
        msg108.Signals.ADAS_LCA_Right_Warn_St = list.at(16).toMap().value("value").toUInt();
        msg108.Signals.unused0 = list.at(17).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg108, len);
        break;
    case MSG_ADAS_LKSSts_1C0_ID:
        _c_1C0_ADAS_LKSSts_msgType msg109;
        len = sizeof(msg109);
        msg109.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg109.Signals.ADAS_LKS_SteernWhlVib_St = list.at(1).toMap().value("value").toUInt();
        msg109.Signals.ADAS_LKS_Active_St = list.at(2).toMap().value("value").toUInt();
        msg109.Signals.ADAS_ELK_Active_St = list.at(3).toMap().value("value").toUInt();
        msg109.Signals.ADAS_ELK_St = list.at(4).toMap().value("value").toUInt();
        msg109.Signals.ADAS_LDW_St = list.at(5).toMap().value("value").toUInt();
        msg109.Signals.E2Estatus = list.at(6).toMap().value("value").toUInt();
        msg109.Signals.unused0 = list.at(7).toMap().value("value").toUInt();
        msg109.Signals.ADAS_LKA_St = list.at(8).toMap().value("value").toUInt();
        msg109.Signals.unused1 = list.at(9).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg109, len);
        break;
    case MSG_ADAS_HWAReq_187_ID:
        _c_187_ADAS_HWAReq_msgType msg110;
        len = sizeof(msg110);
        msg110.Signals.ADAS_AdasHWACtrlTarAccJerkMaxVal = list.at(0).toMap().value("value").toUInt();
        msg110.Signals.IsTimeout = list.at(1).toMap().value("value").toUInt();
        msg110.Signals.E2Estatus = list.at(2).toMap().value("value").toUInt();
        msg110.Signals.ADAS_HWA_status = list.at(3).toMap().value("value").toUInt();
        msg110.Signals.ADAS_AdasHWAShutdownReq = list.at(4).toMap().value("value").toUInt();
        msg110.Signals.ADAS_AdasHWACtrlTarAccJerkMinVal = list.at(5).toMap().value("value").toUInt();
        msg110.Signals.ADAS_HWA_Passive_Reason = list.at(6).toMap().value("value").toUInt();
        msg110.Signals.unused0 = list.at(7).toMap().value("value").toUInt();
        msg110.Signals.ADAS_AdasHWAEmergencyBrakeReq = list.at(8).toMap().value("value").toUInt();
        msg110.Signals.ADAS_EPSStrWarnReq = list.at(9).toMap().value("value").toUInt();
        msg110.Signals.ADAS_ADASSSATrigHWA = list.at(10).toMap().value("value").toUInt();
        msg110.Signals.ADAS_AdasHWATarAAprvd = list.at(11).toMap().value("value").toUInt();
        msg110.Signals.ADAS_AdasHWATarA = list.at(12).toMap().value("value").toUInt();
        msg110.Signals.unused1 = list.at(13).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg110, len);
        break;
    case MSG_ADAS_SysSts_230_ID:
        _c_230_ADAS_SysSts_msgType msg111;
        len = sizeof(msg111);
        msg111.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg111.Signals.ADAS_ADASTurningOptionsLeftLane = list.at(1).toMap().value("value").toUInt();
        msg111.Signals.ADAS_ADASTurningOptionsEgoLane = list.at(2).toMap().value("value").toUInt();
        msg111.Signals.ADAS_ASdM_SystemSt = list.at(3).toMap().value("value").toUInt();
        msg111.Signals.ADAS_ADASTurningOptionsRightLane = list.at(4).toMap().value("value").toUInt();
        msg111.Signals.ADAS_DDWDrowsinessVldy = list.at(5).toMap().value("value").toUInt();
        msg111.Signals.ADAS_DDWWarnLvl = list.at(6).toMap().value("value").toUInt();
        msg111.Signals.ADAS_DDWDrowsinessIdx = list.at(7).toMap().value("value").toUInt();
        msg111.Signals.ADAS_ControllerFaultStatus = list.at(8).toMap().value("value").toUInt();
        msg111.Signals.ADAS_SysSts_RollgCntr = list.at(9).toMap().value("value").toUInt();
        msg111.Signals.ADAS_SysSts_Chks = list.at(10).toMap().value("value").toUInt();
        msg111.Signals.unused0 = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg111, len);
        break;
    case MSG_ADAS_TrackTar01_231_ID:
        _c_231_ADAS_TrackTar01_msgType msg112;
        len = sizeof(msg112);
        msg112.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg112.Signals.unused0 = list.at(1).toMap().value("value").toUInt();
        msg112.Signals.ADAS_TrackTar0_Static_ObjectType = list.at(2).toMap().value("value").toUInt();
        msg112.Signals.ADAS_TrackTar0_Static_St = list.at(3).toMap().value("value").toUInt();
        msg112.Signals.ADAS_TrackTar0_Static_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg112.Signals.ADAS_TrackTar0_Static_LatPo = list.at(5).toMap().value("value").toUInt();
        msg112.Signals.unused1 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg112, len);
        break;
    case MSG_ADAS_TrackTar0_232_ID:
        _c_232_ADAS_TrackTar0_msgType msg113;
        len = sizeof(msg113);
        msg113.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg113.Signals.ADAS_Longitudinal_Speed_0 = list.at(1).toMap().value("value").toUInt();
        msg113.Signals.ADAS_TrackTar0_LgtPo = list.at(2).toMap().value("value").toUInt();
        msg113.Signals.ADAS_Lateral_Speed_0 = list.at(3).toMap().value("value").toUInt();
        msg113.Signals.E2Estatus = list.at(4).toMap().value("value").toUInt();
        msg113.Signals.ADAS_TrackTarget0_St = list.at(5).toMap().value("value").toUInt();
        msg113.Signals.ADAS_TrackTarget0_ObjectType = list.at(6).toMap().value("value").toUInt();
        msg113.Signals.ADAS_TrackTar0_LatPo = list.at(7).toMap().value("value").toUInt();
        msg113.Signals.unused2 = list.at(8).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg113, len);
        break;
    case MSG_ADAS_TrackTar1_233_ID:
        _c_233_ADAS_TrackTar1_msgType msg114;
        len = sizeof(msg114);
        msg114.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg114.Signals.ADAS_Longitudinal_Speed_1 = list.at(1).toMap().value("value").toUInt();
        msg114.Signals.ADAS_TrackTar1_LgtPo = list.at(2).toMap().value("value").toUInt();
        msg114.Signals.ADAS_Lateral_Speed_1 = list.at(3).toMap().value("value").toUInt();
        msg114.Signals.ADAS_TrackTarget1_St = list.at(4).toMap().value("value").toUInt();
        msg114.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg114.Signals.ADAS_TrackTarget1_ObjectType = list.at(6).toMap().value("value").toUInt();
        msg114.Signals.ADAS_TrackTar1_LatPo = list.at(7).toMap().value("value").toUInt();
        msg114.Signals.unused0 = list.at(8).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg114, len);
        break;
    case MSG_ADAS_SRRsts_23F_ID:
        _c_23F_ADAS_SRRsts_msgType msg115;
        len = sizeof(msg115);
        msg115.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg115.Signals.ADAS_FCamSensorCali_St = list.at(1).toMap().value("value").toUInt();
        msg115.Signals.ADAS_FMRRSensorCali_St = list.at(2).toMap().value("value").toUInt();
        msg115.Signals.ADAS_RFSRRSensorBloc_St = list.at(3).toMap().value("value").toUInt();
        msg115.Signals.ADAS_RRSRRSensorBloc_St = list.at(4).toMap().value("value").toUInt();
        msg115.Signals.ADAS_LRSRRSensorBloc_St = list.at(5).toMap().value("value").toUInt();
        msg115.Signals.ADAS_LFSRRSensorBloc_St = list.at(6).toMap().value("value").toUInt();
        msg115.Signals.ADAS_FCamSensorBloc_St = list.at(7).toMap().value("value").toUInt();
        msg115.Signals.ADAS_FMRRSensorBloc_St = list.at(8).toMap().value("value").toUInt();
        msg115.Signals.ADAS_LRSRRSensorFail_St = list.at(9).toMap().value("value").toUInt();
        msg115.Signals.ADAS_LFSRRSensorFail_St = list.at(10).toMap().value("value").toUInt();
        msg115.Signals.ADAS_FCamSensorFail_St = list.at(11).toMap().value("value").toUInt();
        msg115.Signals.ADAS_FMRRSensorFail_St = list.at(12).toMap().value("value").toUInt();
        msg115.Signals.ADAS_RFSRRSensorCali_St = list.at(13).toMap().value("value").toUInt();
        msg115.Signals.ADAS_RRSRRSensorCali_St = list.at(14).toMap().value("value").toUInt();
        msg115.Signals.ADAS_LRSRRSensorCali_St = list.at(15).toMap().value("value").toUInt();
        msg115.Signals.ADAS_LFSRRSensorCali_St = list.at(16).toMap().value("value").toUInt();
        msg115.Signals.ADAS_RFSRRSensorFail_St = list.at(17).toMap().value("value").toUInt();
        msg115.Signals.ADAS_RRSRRSensorFail_St = list.at(18).toMap().value("value").toUInt();
        msg115.Signals.ADAS_ControllerFaultStatus = list.at(19).toMap().value("value").toUInt();
        msg115.Signals.unused0 = list.at(20).toMap().value("value").toUInt();
        msg115.Signals.E2Estatus = list.at(21).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg115, len);
        break;
    case MSG_ANRC_PrkgPDC_196_ID:
        _c_196_ANRC_PrkgPDC_msgType msg116;
        len = sizeof(msg116);
        msg116.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCVisualSwtFb = list.at(1).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCMuteSwtFb = list.at(2).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCActvnSwtFb = list.at(3).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCMod = list.at(4).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCObstclWarning = list.at(5).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCAudibleWarningSwtFb = list.at(6).toMap().value("value").toUInt();
        msg116.Signals.ANRC_PrkgPDCVisualWarningSwtFb = list.at(7).toMap().value("value").toUInt();
        msg116.Signals.unused = list.at(8).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg116, len);
        break;
    case MSG_DMS_DMSInfoHU_24D_ID:
        _c_24D_DMS_DMSInfoHU_msgType msg118;
        len = sizeof(msg118);
        msg118.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg118.Signals.DMS_FaceIdnSetUpSts = list.at(1).toMap().value("value").toUInt();
        msg118.Signals.DMS_DrowsnsLevel = list.at(2).toMap().value("value").toUInt();
        msg118.Signals.DMS_IdnResult = list.at(3).toMap().value("value").toUInt();
        msg118.Signals.DMS_DMSProcSts = list.at(4).toMap().value("value").toUInt();
        msg118.Signals.DMS_DistrctnLevel = list.at(5).toMap().value("value").toUInt();
        msg118.Signals.DMS_DMSAbandon_Reason = list.at(6).toMap().value("value").toUInt();
        msg118.Signals.DMS_DrinkingDetStatus = list.at(7).toMap().value("value").toUInt();
        msg118.Signals.DMS_SmokingDetStatus = list.at(8).toMap().value("value").toUInt();
        msg118.Signals.DMS_PlayPhoneDetStatus = list.at(9).toMap().value("value").toUInt();
        msg118.Signals.unused0 = list.at(10).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg118, len);
        break;
    case MSG_ESC_VehSpd_132h_ID:
        _c_132_ESC_VehSpd_msgType msg119;
        len = sizeof(msg119);
        msg119.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehLatAccl = list.at(1).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehSpdVldy = list.at(2).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehLgtAcclVldy = list.at(3).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehLgtAccl = list.at(4).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehSpd_RollingCounter = list.at(5).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehSpd = list.at(6).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehLatAcclVldy = list.at(7).toMap().value("value").toUInt();
        msg119.Signals.DMS_DrinkingDetStatus = list.at(8).toMap().value("value").toUInt();
        msg119.Signals.ESC_VehSpd_Checksum = list.at(9).toMap().value("value").toUInt();
        msg119.Signals.E2Estatus = list.at(10).toMap().value("value").toUInt();
        msg119.Signals.unused0 = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg119, len);
        break;
    case MSG_ANRC_PrkgDst_SecOC2_20Eh_ID:
        _c_20Eh_ANRC_PrkgDst_SecOC2_msgType msg123;
        len = sizeof(msg123);
        msg123.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg123.Signals.E2Estatus = list.at(1).toMap().value("value").toUInt();
        msg123.Signals.unused0 = list.at(2).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearLeDstToObstcl = list.at(3).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearMidLeDstToObstcl = list.at(4).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearMidRiDstToObstcl = list.at(5).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearMidLeObstclZon = list.at(6).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearLeObstclZon = list.at(7).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearRiObstclZon = list.at(8).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearMidRiObstclZon = list.at(9).toMap().value("value").toUInt();
        msg123.Signals.ANRC_RearDst_RollgCntr = list.at(10).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgRearRiDstToObstcl = list.at(11).toMap().value("value").toUInt();
        msg123.Signals.ANRC_RearDst_Chks = list.at(12).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntLeDstToObstcl = list.at(13).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntRiDstToObstcl = list.at(14).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntMidLeDstToObstcl = list.at(15).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntMidRiDstToObstcl = list.at(16).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntMidLeObstclZon = list.at(17).toMap().value("value").toUInt();
        msg123.Signals.ANRC_FrntDst_Chks = list.at(18).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntLeObstclZon = list.at(19).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntRiObstclZon = list.at(20).toMap().value("value").toUInt();
        msg123.Signals.ANRC_PrkgFrntMidRiObstclZon = list.at(21).toMap().value("value").toUInt();
        msg123.Signals.ANRC_FrntDst_RollgCntr = list.at(22).toMap().value("value").toUInt();
        msg123.Signals.unused1 = list.at(23).toMap().value("value").toUInt();
        msg123.Signals.ANRC_SecOC2_Fresh = list.at(24).toMap().value("value").toUInt();
        msg123.Signals.ANRC_SecOC2_MAC = list.at(25).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg123, len);
        break;
    case MSG_ANRC_SDW_MEB_Info_20C_ID:
        _c_20C_ANRC_SDW_MEB_Info_msgType msg124;
        len = sizeof(msg124);
        msg124.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntMidLeAreaScanned = list.at(1).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntMidRiObstclZon = list.at(2).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntMidLeObstclZon = list.at(3).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearLeObstclZon = list.at(4).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntRiObstclZon = list.at(5).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearMidRiObstclZon = list.at(6).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearMidLeObstclZon = list.at(7).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearLeAreaScanned = list.at(8).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearMidRiAreaScanned = list.at(9).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearMidLeAreaScanned = list.at(10).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntMidRiAreaScanned = list.at(11).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearRiObstclZon = list.at(12).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntLeAreaScanned = list.at(13).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideRearRiAreaScanned = list.at(14).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntLeObstclZon = list.at(15).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgSideFrntRiAreaScanned = list.at(16).toMap().value("value").toUInt();
        msg124.Signals.ANRC_MEB_FuncSts = list.at(17).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgMEBWarnType = list.at(18).toMap().value("value").toUInt();
        msg124.Signals.ANRC_PrkgMEBSettingSt = list.at(19).toMap().value("value").toUInt();
        msg124.Signals.ANRC_SDW_MEB_Info_RollgCntr = list.at(20).toMap().value("value").toUInt();
        msg124.Signals.unused0 = list.at(21).toMap().value("value").toUInt();
        msg124.Signals.ANRC_SDW_MEB_Info_Chks = list.at(22).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg124, len);
        break;
    case MSG_ANRC_PASInfo_SecOC1_176h_ID:
        _c_176_ANRC_PASInfo_SecOC1_msgType msg125;
        len = sizeof(msg125);
        msg125.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg125.Signals.ANRC_PrkgSelParkInOutSts = list.at(1).toMap().value("value").toUInt();
        msg125.Signals.ANRC_PrkgModSelAvl = list.at(2).toMap().value("value").toUInt();
        msg125.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg125.Signals.ANRC_PrkgInDirSelAvl = list.at(4).toMap().value("value").toUInt();
        msg125.Signals.unused0 = list.at(5).toMap().value("value").toUInt();
        msg125.Signals.ANRC_PrkgPASMod = list.at(6).toMap().value("value").toUInt();
        msg125.Signals.ANRC_PrkgFctIndcr = list.at(7).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg125, len);
        break;
    case MSG_ANRC_SVSSts_17A_ID:
        _c_17A_ANRC_SVSSts_msgType msg126;
        len = sizeof(msg126);
        msg126.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSAutoVidSetupReqToHU = list.at(1).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSActStatusToHU = list.at(2).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSAutoViewSwitchValidity = list.at(3).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSAutoViewSwitchModeStatusToHU = list.at(4).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVS360DegPosChgACKToHU = list.at(5).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSDegradationReason = list.at(6).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSAutoSwtModeStatusToHU = list.at(7).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVS_2D_3D_Status = list.at(8).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSModelColorStatusToHU = list.at(9).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSVidSetupStatusToHU = list.at(10).toMap().value("value").toUInt();
        msg126.Signals.ANRC_3D_SVSVidSetupStatusToHU = list.at(11).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSFrontCamSts = list.at(12).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSRearCamSts = list.at(13).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSLeftCamSts = list.at(14).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSRightCamSts = list.at(15).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSGuidanceOLStatusToHU = list.at(16).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSObjWarnOLStatusToHU = list.at(17).toMap().value("value").toUInt();
        msg126.Signals.ANRC_SVSTranspModStatusToHU = list.at(18).toMap().value("value").toUInt();
        msg126.Signals.unused0 = list.at(19).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg126, len);
        break;
    case MSG_ADAS_Line3_242_ID:
        _c_242_ADAS_Line3_msgType msg128;
        len = sizeof(msg128);
        msg128.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg128.Signals.ADAS_Line_3_Display = list.at(1).toMap().value("value").toUInt();
        msg128.Signals.ADAS_Line_3_A0 = list.at(2).toMap().value("value").toUInt();
        msg128.Signals.unused2 = list.at(3).toMap().value("value").toUInt();
        msg128.Signals.ADAS_Line_3_A3 = list.at(4).toMap().value("value").toUInt();
        msg128.Signals.ADAS_Line_3_A1 = list.at(5).toMap().value("value").toUInt();
        msg128.Signals.ADAS_Line_3_Type = list.at(6).toMap().value("value").toUInt();
        msg128.Signals.unused0 = list.at(7).toMap().value("value").toUInt();
        msg128.Signals.ADAS_Line_3_A2 = list.at(8).toMap().value("value").toUInt();
        msg128.Signals.unused1 = list.at(9).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg128, len);
        break;
    case MSG_ADAS_Line4_243_ID:
        _c_243_ADAS_Line4_msgType msg129;
        len = sizeof(msg129);
        msg129.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg129.Signals.ADAS_Line_4_Display = list.at(1).toMap().value("value").toUInt();
        msg129.Signals.ADAS_Line_4_A0 = list.at(2).toMap().value("value").toUInt();
        msg129.Signals.unused2 = list.at(3).toMap().value("value").toUInt();
        msg129.Signals.ADAS_Line_4_A3 = list.at(4).toMap().value("value").toUInt();
        msg129.Signals.ADAS_Line_4_A1 = list.at(5).toMap().value("value").toUInt();
        msg129.Signals.ADAS_Line_4_Type = list.at(6).toMap().value("value").toUInt();
        msg129.Signals.unused0 = list.at(7).toMap().value("value").toUInt();
        msg129.Signals.ADAS_Line_4_A2 = list.at(8).toMap().value("value").toUInt();
        msg129.Signals.unused1 = list.at(9).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg129, len);
        break;
    case MSG_ADAS_TrackTar23_234_ID:
        _c_234_ADAS_TrackTar23_msgType msg130;
        len = sizeof(msg130);
        msg130.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar3_LgtPo = list.at(1).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTarget3_St = list.at(2).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTarget2_St = list.at(3).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTarget3_ObjectType = list.at(4).toMap().value("value").toUInt();
        msg130.Signals.unused0 = list.at(5).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar2_LgtPo = list.at(6).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar23_Chks = list.at(7).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar3_LatPo = list.at(8).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTarget2_ObjectType = list.at(9).toMap().value("value").toUInt();
        msg130.Signals.unused1 = list.at(10).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar2_LatPo = list.at(11).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar23_RollgCntr = list.at(12).toMap().value("value").toUInt();
        msg130.Signals.unused2 = list.at(13).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar1_Static_LgtPo = list.at(14).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar1_Static_ObjectType = list.at(15).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar1_Static_St = list.at(16).toMap().value("value").toUInt();
        msg130.Signals.ADAS_TrackTar1_Static_LatPo = list.at(17).toMap().value("value").toUInt();
        msg130.Signals.unused3 = list.at(18).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg130, len);
        break;
    case MSG_LCMFL_FltSts_254_ID:
        _c_254_LCMFL_FltSts_msgType msg131;
        len = sizeof(msg131);
        msg131.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg131.Signals.LCMFL_LeFrntPosnLampFltSts = list.at(1).toMap().value("value").toUInt();
        msg131.Signals.LCMFL_LeLoBeamFltSts = list.at(2).toMap().value("value").toUInt();
        msg131.Signals.LCMFL_LeGrpdLampModFltSts = list.at(3).toMap().value("value").toUInt();
        msg131.Signals.LCMFL_LeHiBeamFltSts = list.at(4).toMap().value("value").toUInt();
        msg131.Signals.LCMFL_LeFltDayLampSts = list.at(5).toMap().value("value").toUInt();
        msg131.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg131, len);
        break;
    case MSG_LCMFR_FltSts_255_ID:
        _c_255_LCMFR_FltSts_msgType msg132;
        len = sizeof(msg132);
        msg132.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg132.Signals.LCMFR_RiFrntPosnLampFltSts = list.at(1).toMap().value("value").toUInt();
        msg132.Signals.LCMFR_RiLoBeamFltSts = list.at(2).toMap().value("value").toUInt();
        msg132.Signals.LCMFR_RiGrpdLampModFltSts = list.at(3).toMap().value("value").toUInt();
        msg132.Signals.LCMFR_RiHiBeamFltSts = list.at(4).toMap().value("value").toUInt();
        msg132.Signals.LCMFR_RiFltDayLampSts = list.at(5).toMap().value("value").toUInt();
        msg132.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg132, len);
        break;
    case MSG_LCMRL_BCM_LIN1ASWM_1E2_ID:
        _c_1E2_BCM_LIN1ASWM_msgType msg133;
        len = sizeof(msg133);
        msg133.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg133.Signals.LCMRL_LeRePosnFailrSt = list.at(1).toMap().value("value").toUInt();
        msg133.Signals.LCMRR_RiRePosnFailrSt = list.at(2).toMap().value("value").toUInt();
        msg133.Signals.LCMRL_LeReDirIndcrFailrSt = list.at(3).toMap().value("value").toUInt();
        msg133.Signals.LCMRR_RiReDirIndcrFailrSt = list.at(4).toMap().value("value").toUInt();
        msg133.Signals.unused0 = list.at(5).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg133, len);
        break;
    case MSG_LCMFL_LeFrntDirIndcrLam_142_ID:
        _c_142_LCMFL_LeFrntDirIndcrLam_msgType msg138;
        len = sizeof(msg138);
        msg138.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg138.Signals.LCMFL_LeFrntDirIndcrLampSt = list.at(1).toMap().value("value").toUInt();
        msg138.Signals.LCMFL_LeFrntDirIndcrFailrSt = list.at(2).toMap().value("value").toUInt();
        msg138.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg138, len);
        break;
    case MSG_LCMFR_RiFrntDirIndcrLam_143_ID:
        _c_143_LCMFR_RiFrntDirIndcrLam_msgType msg139;
        len = sizeof(msg139);
        msg139.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg139.Signals.LCMFR_RiFrntDirIndcrLampSt = list.at(1).toMap().value("value").toUInt();
        msg139.Signals.LCMFR_RiFrntDirIndcrFailrSt = list.at(2).toMap().value("value").toUInt();
        msg139.Signals.unused0 = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg139, len);
        break;
    case MSG_DCMFL_States1_1C6_ID:
        _c_1C6_DCMFL_States1_msgType msg140;
        len = sizeof(msg140);
        msg140.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg140.Signals.DCMFL_LeSideDirIndcrFailrSt = list.at(1).toMap().value("value").toUInt();
        msg140.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg140, len);
        break;
    case MSG_DCMFR_States_1B4_ID:
        _c_1B4_DCMFR_States_msgType msg141;
        len = sizeof(msg141);
        msg141.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg141.Signals.DCMFR_RiSideDirIndcrFailrSt = list.at(1).toMap().value("value").toUInt();
        msg141.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg141, len);
        break;
    case MSG_BCM_ImobMstWarn_BE_ID:
        _c_BE_BCM_ImobMstWarn_msgType msg142;
        len = sizeof(msg142);
        msg142.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg142.Signals.BCM_ImobMstWarn = list.at(1).toMap().value("value").toUInt();
        msg142.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg142, len);
        break;
    case MSG_PLCU_ParkLockSts_1E1_ID:
        _c_1E1_PLCU_ParkLockSts_msgType msg143;
        len = sizeof(msg143);
        msg143.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg143.Signals.PLCU_ParkLockSt = list.at(1).toMap().value("value").toUInt();
        msg143.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg143, len);
        break;
    case MSG_VCU_DivModReq_208_ID:
        _c_208_VCU_DivModReq_msgType msg144;
        len = sizeof(msg144);
        msg144.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg144.Signals.VCU_VehSrvcWarn = list.at(1).toMap().value("value").toUInt();
        msg144.Signals.VCU_ValetModAct = list.at(2).toMap().value("value").toUInt();
        msg144.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg144.Signals.unused0 = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg144, len);
        break;
    case MSG_ADAS_ACCSts_181_ID:
        _c_181_ADAS_ACCSts_msgType msg146;
        len = sizeof(msg146);
        msg146.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg146.Signals.ADAS_ACC_CurveSpeed = list.at(1).toMap().value("value").toUInt();
        msg146.Signals.ADAS_ACC_GoNotifier = list.at(2).toMap().value("value").toUInt();
        msg146.Signals.ADAS_ACC_Warn_St = list.at(3).toMap().value("value").toUInt();
        msg146.Signals.ADAS_ACC_TimeGap = list.at(4).toMap().value("value").toUInt();
        msg146.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg146.Signals.ADAS_ACC_Passive_Reason = list.at(6).toMap().value("value").toUInt();
        msg146.Signals.unused0 = list.at(7).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg146, len);
        break;
    case MSG_ADAS_HWA_Warn_160_ID:
        _c_160_ADAS_HWA_Warn_msgType msg147;
        len = sizeof(msg147);
        msg147.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg147.Signals.ADAS_HWA_Warn_St = list.at(1).toMap().value("value").toUInt();
        msg147.Signals.ADAS_HWA_HandsonReq = list.at(2).toMap().value("value").toUInt();
        msg147.Signals.E2Estatus = list.at(3).toMap().value("value").toUInt();
        msg147.Signals.unused0 = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg147, len);
        break;
    case MSG_DMS_DMSStatus_24B_ID:
        _c_24B_MSG_DMS_DMSStatus_msgType msg148;
        len = sizeof(msg148);
        msg148.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg148.Signals.DMS_DMSSts = list.at(1).toMap().value("value").toUInt();
        msg148.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg148, len);
        break;
    case MSG_ETC_Module_30B_ID:
        _c_1A1_MSG_ETC_TransSt_msgType msg149;
        len = sizeof(msg149);
        msg149.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg149.Signals.unused0 = list.at(1).toMap().value("value").toUInt();
        msg149.Signals.ETC_EntranceExitType = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg149, len);
        break;
    case MSG_ADAS_Line1_240_ID:
        _c_240_ADAS_Line1_msgType msg151;
        len = sizeof(msg151);
        msg151.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg151.Signals.ADAS_Line_1_A0 = list.at(1).toMap().value("value").toUInt();
        msg151.Signals.ADAS_Line_1_Type = list.at(2).toMap().value("value").toUInt();
        msg151.Signals.ADAS_Line_1_A3 = list.at(3).toMap().value("value").toUInt();
        msg151.Signals.ADAS_Line_1_Display = list.at(4).toMap().value("value").toUInt();
        msg151.Signals.ADAS_Line_1_A1 = list.at(5).toMap().value("value").toUInt();
        msg151.Signals.E2Estatus = list.at(6).toMap().value("value").toUInt();
        msg151.Signals.unused0 = list.at(7).toMap().value("value").toUInt();
        msg151.Signals.ADAS_Line_1_A2 = list.at(8).toMap().value("value").toUInt();
        msg151.Signals.unused1 = list.at(9).toMap().value("value").toUInt();
        msg151.Signals.ADAS_LaneLineRange_1 = list.at(10).toMap().value("value").toUInt();
        msg151.Signals.unused2 = list.at(11).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg151, len);
        break;
    case MSG_ADAS_TrackTar2_235_ID:
        _c_235_MSG_ADAS_TrackTar2_msgType msg152;
        len = sizeof(msg152);
        msg152.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg152.Signals.ADAS_TrackTarget2_ObjectType = list.at(1).toMap().value("value").toUInt();
        msg152.Signals.ADAS_TrackTarget2_St = list.at(2).toMap().value("value").toUInt();
        msg152.Signals.ADAS_TrackTar2_LatPo = list.at(3).toMap().value("value").toUInt();
        msg152.Signals.ADAS_TrackTar2_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg152.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg152.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg152, len);
        break;
    case MSG_ADAS_TrackTar3_236_ID:
        _c_236_MSG_ADAS_TrackTar3_msgType msg153;
        len = sizeof(msg153);
        msg153.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg153.Signals.ADAS_TrackTarget3_ObjectType = list.at(1).toMap().value("value").toUInt();
        msg153.Signals.ADAS_TrackTarget3_St = list.at(2).toMap().value("value").toUInt();
        msg153.Signals.ADAS_TrackTar3_LatPo = list.at(3).toMap().value("value").toUInt();
        msg153.Signals.ADAS_TrackTar3_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg153.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg153.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg153, len);
        break;
    case MSG_ADAS_TrackTar3_Static_23C_ID:
        _c_23C_MSG_ADAS_TrackTar3_Static_msgType msg154;
        len = sizeof(msg154);
        msg154.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg154.Signals.ADAS_TrackTarget3_Static_ObjectType = list.at(1).toMap().value("value").toUInt();
        msg154.Signals.ADAS_TrackTar3_Static_LatPo = list.at(2).toMap().value("value").toUInt();
        msg154.Signals.ADAS_TrackTarget3_Static_St = list.at(3).toMap().value("value").toUInt();
        msg154.Signals.ADAS_TrackTar3_Static_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg154.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg154.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg154, len);
        break;
    case MSG_ADAS_TrackTar4_23A_ID:
        _c_23A_MSG_ADAS_TrackTar4_msgType msg155;
        len = sizeof(msg155);
        msg155.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg155.Signals.ADAS_TrackTarget4_ObjectType = list.at(1).toMap().value("value").toUInt();
        msg155.Signals.ADAS_TrackTarget4_St = list.at(2).toMap().value("value").toUInt();
        msg155.Signals.ADAS_TrackTar4_LatPo = list.at(3).toMap().value("value").toUInt();
        msg155.Signals.ADAS_TrackTar4_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg155.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg155.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg155, len);
        break;
    case MSG_ADAS_TrackTar4_Static_23D_ID:
        _c_23D_MSG_ADAS_TrackTar4_Static_msgType msg156;
        len = sizeof(msg156);
        msg156.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg156.Signals.ADAS_TrackTar4_Static_ObjectType = list.at(1).toMap().value("value").toUInt();
        msg156.Signals.ADAS_TrackTarget4_Static_St = list.at(2).toMap().value("value").toUInt();
        msg156.Signals.ADAS_TrackTar4_Static_LatPo = list.at(3).toMap().value("value").toUInt();
        msg156.Signals.ADAS_TrackTar4_Static_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg156.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg156.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg156, len);
        break;
    case MSG_ADAS_TrackTar5_23B_ID:
        _c_ICGM_ADAS_293h_IP_msgType msg157;
        len = sizeof(msg157);
        msg157.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg157.Signals.DASLKAHandsoff = list.at(1).toMap().value("value").toUInt();
        msg157.Signals.DASFCWWarning = list.at(2).toMap().value("value").toUInt();
        msg157.Signals.DASLKAState = list.at(3).toMap().value("value").toUInt();
        msg157.Signals.unused0 = list.at(4).toMap().value("value").toUInt();
        msg157.Signals.DASIHCState = list.at(5).toMap().value("value").toUInt();
        msg157.Signals.DASAEBState = list.at(6).toMap().value("value").toUInt();
        msg157.Signals.unused1 = list.at(7).toMap().value("value").toUInt();
        msg157.Signals.DASTSRState = list.at(8).toMap().value("value").toUInt();
        msg157.Signals.DASFCWState = list.at(9).toMap().value("value").toUInt();
        msg157.Signals.unused2 = list.at(10).toMap().value("value").toUInt();
        msg157.Signals.DASICCstate = list.at(11).toMap().value("value").toUInt();
        msg157.Signals.unused3 = list.at(12).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg157, len);
        break;
    case MSG_ADAS_TrackTar5_Static_23E_ID:
        _c_23E_MSG_ADAS_TrackTar5_Static_msgType msg175;
        len = sizeof(msg175);
        msg175.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg175.Signals.ADAS_TrackTar5_Static_ObjectType = list.at(1).toMap().value("value").toUInt();
        msg175.Signals.ADAS_TrackTarget5_Static_St = list.at(2).toMap().value("value").toUInt();
        msg175.Signals.ADAS_TrackTar5_Static_LatPo = list.at(3).toMap().value("value").toUInt();
        msg175.Signals.ADAS_TrackTar5_Static_LgtPo = list.at(4).toMap().value("value").toUInt();
        msg175.Signals.E2Estatus = list.at(5).toMap().value("value").toUInt();
        msg175.Signals.unused0 = list.at(6).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg175, len);
        break;
    case MSG_VCU_PwrMtr_430_ID:
        _c_430_MSG_VCU_PwrMtr_msgType msg176;
        len = sizeof(msg176);
        msg176.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg176.Signals.VCU_PwrMtrMax = list.at(1).toMap().value("value").toUInt();
        msg176.Signals.unused = list.at(2).toMap().value("value").toUInt();
        msg176.Signals.VCU_PwrMtrMin = list.at(3).toMap().value("value").toUInt();
        msg176.Signals.unused1 = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg176, len);
        break;
    case MSG_VCU_RngSave1_B7_ID:
        _c_B7_MSG_VCU_RngSave1_msgType msg177;
        len = sizeof(msg177);
        msg177.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg177.Signals.unused = list.at(1).toMap().value("value").toUInt();
        msg177.Signals.VCU_RngSaveSeatHeatg = list.at(2).toMap().value("value").toUInt();
        msg177.Signals.VCU_RngSaveReWinHeatg = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg177, len);
        break;
    case MSG_VCU_RngSave2_B8_ID:
        _c_B8_MSG_VCU_RngSave2_msgType msg178;
        len = sizeof(msg178);
        msg178.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg178.Signals.unused = list.at(1).toMap().value("value").toUInt();
        msg178.Signals.VCU_RngSaveSeatMassg = list.at(2).toMap().value("value").toUInt();
        msg178.Signals.VCU_RngSaveSoundSys = list.at(3).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg178, len);
        break;
    case MSG_VCU_RngSave3_B9_ID:
        _c_B9_MSG_VCU_RngSave3_msgType msg179;
        len = sizeof(msg179);
        msg179.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg179.Signals.unused = list.at(1).toMap().value("value").toUInt();
        msg179.Signals.VCU_RngSaveClimaCmpr = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg179, len);
        break;
    case MSG_VCU_TboxIndcd_2F6_ID:
        _c_2F6_MSG_VCU_TboxIndcd_msgType msg180;
        len = sizeof(msg180);
        msg180.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg180.Signals.VCU_RngSaveStrWhlHeatg = list.at(1).toMap().value("value").toUInt();
        msg180.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg180, len);
        break;
    case MSG_VCU_ChrgSysReq_93_ID:
        _c_93_MSG_VCU_ChrgSysReq_msgType msg181;
        len = sizeof(msg181);
        msg181.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg181.Signals.unused0 = list.at(1).toMap().value("value").toUInt();
        msg181.Signals.VCU_ChrgSocTarSp = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg181, len);
        break;
    case MSG_eBooster_EbbSts_123_ID:
        _c_123_eBooster_EbbSts_msgType msg182;
        len = sizeof(msg182);
        msg182.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg182.Signals.eBooster_HmiLampReqiboosterFlt = list.at(1).toMap().value("value").toUInt();
        msg182.Signals.unused0 = list.at(2).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg182, len);
        break;
    case MSG_ADAS_ACC_ESCRq_185_ID:
        _c_185_ADAS_ACC_ESCRq_msgType msg183;
        len = sizeof(msg183);
        msg183.Signals.IsTimeout = list.at(0).toMap().value("value").toUInt();
        msg183.Signals.ADAS_ACC_St = list.at(1).toMap().value("value").toUInt();
        msg183.Signals.E2Estatus = list.at(2).toMap().value("value").toUInt();
        msg183.Signals.ADAS_AdasAccTypeReqMode = list.at(3).toMap().value("value").toUInt();
        msg183.Signals.unused0 = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg183, len);
        break;
    case MSG_SCM_SAS_Status_9E_ID:
        _c_ICGM_SAS_266h_IP_msgType msg184;
        len = sizeof(msg184);
        msg184.Signals.SteeringAngle = list.at(0).toMap().value("value").toUInt();
        msg184.Signals.SteeringSpeed = list.at(1).toMap().value("value").toUInt();
        msg184.Signals.SASCalibrationStatus = list.at(2).toMap().value("value").toUInt();
        msg184.Signals.IsTimeout = list.at(3).toMap().value("value").toUInt();
        msg184.Signals.unused0 = list.at(4).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg184, len);
        break;
    case MSG_RPCAPP_SET_COVER_ANIMATION_ID:
        _c_SOC_TT1_SET_SIG_TC_msgType msg186;
        len = sizeof(msg186);
        msg186.Signals.EngineOilPressureLowWarn = list.at(0).toMap().value("value").toUInt();
        msg186.Signals.reserved = list.at(1).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg186, len);
        break;
    case MSG_GET_HMI_DIDS_STATUS_ID:
        _c_KERNAL_DIDS_INFO_msgType msg191;
        len = sizeof(msg191);
        msg191.Signals.aubDIDS_244 = list.at(0).toMap().value("value").toUInt();
        msg191.Signals.aubDIDS_245 = list.at(1).toMap().value("value").toUInt();

        byteArray = QByteArray((const char*)&msg191, len);
        break;
    }

    return byteArray;
}
#endif // DYNAMIC_CREATE_H