#include "include/parsingData.h"
#include <string.h>

/*ivs注册信号*/
static RpcMsgId idList[] {
    MSG_MCU_0_ID,
    MSG_VCU_CurrEngPwr_2F1_ID,
    MSG_MCU_1_ID,
    MSG_MCU_5_ID,
    MSG_VCU_WarnForHU_148_ID,
    MSG_BCM_LightReq_151h_ID,
    MSG_VCU_AccPosGearSts_97h_ID,
    MSG_VCU_HvCoolgModReq_98h_ID,
    MSG_VCU_HvInfForDrvr_9Ah_ID,
    MSG_ESC_HMIInfo_136h_ID,
    MSG_EPS_EPSInfo_130h_ID,
    MSG_ACM_ACMInfo_201h_ID,
    MSG_ESC_HmiLampReq_138_ID,
    MSG_ESC_FctSt_131_ID,
    MSG_SUM_SuspSts_1BC_ID,
    MSG_SUM_SuspSys_17C_ID,
    MSG_BCM_TireT_248_ID,
    MSG_BCM_AlrmWarnIn_245_ID,
    MSG_AVAS_CurrSts_17F_ID,
    MSG_BMS_BatteryRelayErrSts_F7_ID,
    MSG_IPU_DCDCSts_DB_ID,
    MSG_VCU_ReminDrvgRng_B3_ID,
    MSG_BCM_CANFD_212_ID,
//    MSG_VCU_MaxPowerAvl_AC_ID,
    MSG_BMS_HvBattTiRmnChrgn_200_ID,
    MSG_eBooster_EbbSts_123_ID,
    MSG_ADAS_TSRSts_1C1_ID,
    MSG_ADAS_FCTASts_1C3_ID,
    MSG_ADAS_DOWSts_1C4_ID,
//    MSG_ADAS_TSR_162_ID,
    MSG_PLCU_ParkLockSts_1E1_ID,
    MSG_VCU_DivModReq_208_ID,
    MSG_ADAS_ACCSts_181_ID,
    MSG_ADAS_HWAReq_187_ID,
    MSG_ADAS_ACC_ESCRq_185_ID ,
};

extern "C"
{
    static std::map<unsigned char, FunctionParser> ParseFunc =
    {
        {MSG_MCU_0_ID, func_MSG_MCU_0_ID},
        {MSG_VCU_CurrEngPwr_2F1_ID, func_MSG_VCU_CurrEngPwr_2F1_ID},
        {MSG_MCU_5_ID, func_MSG_MCU_5_ID},
        {MSG_VCU_HvCoolgModReq_98h_ID,func_MSG_VCU_HvCoolgModReq_98h_ID},
        {MSG_VCU_WarnForHU_148_ID,func_MSG_VCU_WarnForHU_148_ID},
        {MSG_BMS_HvBattTiRmnChrgn_200_ID,func_MSG_BMS_HvBattTiRmnChrgn_200_ID},
        {MSG_BCM_LightReq_151h_ID,func_MSG_BCM_LightReq_151h_ID},
        {MSG_ESC_HMIInfo_136h_ID,func_MSG_ESC_HMIInfo_136h_ID},
        {MSG_ESC_HmiLampReq_138_ID,func_MSG_ESC_HmiLampReq_138_ID},
        {MSG_ESC_FctSt_131_ID,func_MSG_ESC_FctSt_131_ID},
        {MSG_BCM_AlrmWarnIn_245_ID,func_MSG_BCM_AlrmWarnIn_245_ID},
        {MSG_eBooster_EbbSts_123_ID,func_MSG_eBooster_EbbSts_123_ID},
        {MSG_EPS_EPSInfo_130h_ID,func_MSG_EPS_EPSInfo_130h_ID},
        {MSG_ACM_ACMInfo_201h_ID,func_MSG_ACM_ACMInfo_201h_ID},
        {MSG_SUM_SuspSys_17C_ID,func_MSG_SUM_SuspSys_17C_ID},
        {MSG_BCM_TireT_248_ID,func_MSG_BCM_TireT_248_ID},
        {MSG_AVAS_CurrSts_17F_ID,func_MSG_AVAS_CurrSts_17F_ID},
        {MSG_BMS_BatteryRelayErrSts_F7_ID,func_MSG_BMS_BatteryRelayErrSts_F7_ID},
        {MSG_IPU_DCDCSts_DB_ID,func_MSG_MSG_IPU_DCDCSts_DB_ID},
//        {MSG_VCU_MaxPowerAvl_AC_ID,func_MSG_VCU_MaxPowerAvl_AC_ID},
        {MSG_VCU_ReminDrvgRng_B3_ID,func_MSG_VCU_ReminDrvgRng_B3_ID},
        {MSG_BCM_CANFD_212_ID,func_MSG_BCM_CANFD_212_ID},
        {MSG_ADAS_TSRSts_1C1_ID,func_MSG_ADAS_TSRSts_1C1_ID},
//        {MSG_ADAS_TSR_162_ID,func_MSG_ADAS_TSR_162_ID},
        {MSG_ADAS_FCTASts_1C3_ID,func_MSG_ADAS_FCTASts_1C3_ID},
        {MSG_ADAS_DOWSts_1C4_ID,func_MSG_ADAS_DOWSts_1C4_ID},
        {MSG_PLCU_ParkLockSts_1E1_ID,func_MSG_PLCU_ParkLockSts_1E1_ID},
        {MSG_VCU_DivModReq_208_ID,func_VCU_DivModReq_208_ID},
        {MSG_ADAS_ACCSts_181_ID,func_ADAS_ACCSts_181_ID},
        {MSG_ADAS_HWAReq_187_ID               ,func_MSG_ADAS_HWAReq_187_ID    },
        {MSG_ADAS_ACC_ESCRq_185_ID            ,func_MSG_ADAS_ACC_ESCRq_185_ID },
    };

    void display_Msg_CallbackFunc_HMI(unsigned char message_id,const unsigned char * pData, unsigned char data_len, void * pUserData)
    {
        ( void ) pUserData;
        Parsing_Message msg;

        msg.m_messageID = message_id;
        msg.data_len = data_len;
        msg.m_messageData = QByteArray( (const char*)pData, data_len);    //-->数据使用QByteArray存储
        //memset((char *)msg.m_messageData, 0, MAXLENMSG);
        //memcpy((char *)msg.m_messageData, (char *)pData, data_len);
        ParsingData::instance()->SendMsg(msg);
    }

    void func_MSG_MCU_0_ID(const char *data)
    {
        _c_MSG_MCU_0_msgType* pmsg = (_c_MSG_MCU_0_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_SPEED, pmsg->Signals.MCU_VEHICLE_SPEED, (unsigned char)0)
    }

    void func_MSG_VCU_CurrEngPwr_2F1_ID(const char *data)
    {
        _c_2F1_VCU_CurrEngPwr_msgType* pmsg = (_c_2F1_VCU_CurrEngPwr_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ENGPWR, pmsg->Signals.VCU_CurrEngPwr, pmsg->Signals.IsTimeout)
    }

    void func_MSG_MCU_5_ID(const char *data)
    {
        _c_MSG_MCU_5_msgType* pmsg = (_c_MSG_MCU_5_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_LowPowerWarLamp, pmsg->Signals.CLS_TT_BATT_COLOR, (unsigned char)0)
    }

    void func_MSG_VCU_HvCoolgModReq_98h_ID(const char *data)
    {
        _c_98_VCU_HvCoolgModReq_msgType* pmsg = (_c_98_VCU_HvCoolgModReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_LowPowerWarLampTimeOut, 0, pmsg->Signals.IsTimeout)
    }

    void func_MSG_VCU_WarnForHU_148_ID(const char *data)
    {
        _c_148_VCU_WarnForHU_msgType* pmsg = (_c_148_VCU_WarnForHU_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CoolantAlarmLamp, pmsg->Signals.VCU_CoolantAlarmHMI, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_EMotorAlarm, pmsg->Signals.VCU_EMotorAlarmHMI, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_SystemFailureLamp, pmsg->Signals.VCU_SystemFailureHMI, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_SysPowerLimitationLamp, pmsg->Signals.VCU_SystemPowerLimitationHMI, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BatteryHeatCritical, pmsg->Signals.VCU_BatteryHeatCriticalHMI, pmsg->Signals.IsTimeout)
    }

    void func_MSG_BMS_HvBattTiRmnChrgn_200_ID(const char *data)
    {
        _c_200_BMS_HvBattTiRmnChrgn_msgType* pmsg = (_c_200_BMS_HvBattTiRmnChrgn_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BatteryHeatRunaway, pmsg->Signals.BMS_HVBattThermRunaway, pmsg->Signals.IsTimeout)
    }

    void func_MSG_BCM_LightReq_151h_ID(const char *data)
    {
        _c_151_BCM_LightReq_msgType* pmsg = (_c_151_BCM_LightReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_Left_Turn, pmsg->Signals.BCM_LeDirIndcrTelltlLampReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_Right_Turn, pmsg->Signals.BCM_RiDirIndcrTelltlLampReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LowBeamLamp, pmsg->Signals.BCM_LoBeamReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_HighBeamLamp, pmsg->Signals.BCM_HiBeamTelltlLampReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_PosiLamp, pmsg->Signals.BCM_PosnLiTelltlLampReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_FogLamp, pmsg->Signals.BCM_ReFogLiTelltlLampReq, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ESC_HMIInfo_136h_ID(const char *data)
    {
        _c_136_ESC_HMIInfo_msgType* pmsg = (_c_136_ESC_HMIInfo_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ESC, pmsg->Signals.ESC_HmiLampReqEsc, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_EBDFaultReqBrkSys, pmsg->Signals.ESC_HmiLampReqBrkSys, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_EpbLampActv, pmsg->Signals.ESC_HmiLampReqEpbActv, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_EpbFltLamp, pmsg->Signals.ESC_HmiLampReqEpbFlt, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_HDC, pmsg->Signals.ESC_HmiLampReqHdc, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ESC_HmiLampReq_138_ID(const char *data)
    {
        _c_138_ESC_HmiLampReq_msgType* pmsg = (_c_138_ESC_HmiLampReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_TCS, pmsg->Signals.ESC_HmiLampReqTCS, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TCSOff, pmsg->Signals.ESC_HmiLampReqTCSOff, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ABSLamp, pmsg->Signals.ESC_HmiLampReqABS, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_AVH, pmsg->Signals.ESC_HmiLampReqAVHSts, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ESC_FctSt_131_ID(const char *data)
    {
        _c_131_ESC_FctSt_msgType* pmsg = (_c_131_ESC_FctSt_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_EBDFaultCtrlrAvlEbd, pmsg->Signals.ESC_CtrlrAvlEbd, pmsg->Signals.IsTimeout)
    }

    void func_MSG_BCM_AlrmWarnIn_245_ID(const char *data)
    {
        _c_245_BCM_AlrmWarnIn_msgType* pmsg = (_c_245_BCM_AlrmWarnIn_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_EBDFaultBrkFldLvlDisp, pmsg->Signals.BCM_BrkFldLvlDisp, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_Frontbonnetfault, pmsg->Signals.BCM_HoodNotClsdWarnReq, pmsg->Signals.IsTimeout)
    }

    void func_MSG_eBooster_EbbSts_123_ID(const char *data)
    {
        _c_123_eBooster_EbbSts_msgType* pmsg = (_c_123_eBooster_EbbSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_EBDFaultReqiboosterFlt, pmsg->Signals.eBooster_HmiLampReqiboosterFlt, pmsg->Signals.IsTimeout)
    }

    void func_MSG_EPS_EPSInfo_130h_ID(const char *data)
    {
        _c_130_EPS_EPSInfo_msgType* pmsg = (_c_130_EPS_EPSInfo_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_EPSFault, pmsg->Signals.EPS_SteerWarnLamp_Rq, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ACM_ACMInfo_201h_ID(const char *data)
    {
        _c_201_ACM_ACMInfo_msgType* pmsg = (_c_201_ACM_ACMInfo_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BucLeft, pmsg->Signals.ACM_BucSwtSt2ndSeatRowLe, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_OccLeft, pmsg->Signals.ACM_OccptDetnSt2ndSeatRowLe, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BucMid, pmsg->Signals.ACM_BucSwtSt2ndSeatRowCentr, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_OccMid, pmsg->Signals.ACM_OccptDetnSt2ndSeatRowCentr, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BucRight, pmsg->Signals.ACM_BucSwtSt2ndSeatRowRi, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_OccRight, pmsg->Signals.ACM_OccptDetnSt2ndSeatRowRi, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BucDriver, pmsg->Signals.ACM_BucSwtStFrntDrvr, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BucPass, pmsg->Signals.ACM_BucSwtStFrntPass, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_OccPass, pmsg->Signals.ACM_OccptDetnStPassSeat, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_AirbagLamp, pmsg->Signals.ACM_AirbWarnLampSt, pmsg->Signals.IsTimeout)
    }

    void func_MSG_SUM_SuspSys_17C_ID(const char *data)
    {
        _c_17C_SUM_SuspSys_msgType* pmsg = (_c_17C_SUM_SuspSys_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_AirSuspension_Fault, pmsg->Signals.SUM_SuspSysFailrSts, pmsg->Signals.IsTimeout)
    }

    void func_MSG_BCM_TireT_248_ID(const char *data)
    {
        _c_248_BCM_TireT_msgType* pmsg = (_c_248_BCM_TireT_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_TireSts, pmsg->Signals.BCM_TireMonTireSts, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TireSysSts, pmsg->Signals.BCM_TireMonSysSts, pmsg->Signals.IsTimeout)
    }

    void func_MSG_AVAS_CurrSts_17F_ID(const char *data)
    {
        _c_17F_AVAS_CurrSts_msgType* pmsg = (_c_17F_AVAS_CurrSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_LowSpeedLamp, pmsg->Signals.AVAS_AVASShowCurrSts, pmsg->Signals.IsTimeout)
    }

    void func_MSG_BMS_BatteryRelayErrSts_F7_ID(const char *data)
    {
        _c_F7_BMS_BatteryRelayErrSts_msgType* pmsg = (_c_F7_BMS_BatteryRelayErrSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BMSFault, pmsg->Signals.BMS_VehHvIsoErr, pmsg->Signals.IsTimeout)
    }

    void func_MSG_MSG_IPU_DCDCSts_DB_ID(const char *data)
    {
        _c_DB_IPU_DCDCSts_msgType* pmsg = (_c_DB_IPU_DCDCSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_DcdcFailrLampSts, pmsg->Signals.IPU_EEMDCDCFailrSts, pmsg->Signals.IsTimeout)
    }

    void func_MSG_VCU_MaxPowerAvl_AC_ID(const char *data)
    {
        _c_AC_VCU_MaxPowerAvl_msgType* pmsg = (_c_AC_VCU_MaxPowerAvl_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_DcdcFailrLampLvWarn, pmsg->Signals.VCU_LvWarn, pmsg->Signals.IsTimeout)
    }

    void func_MSG_VCU_ReminDrvgRng_B3_ID(const char *data)
    {
        _c_B3_VCU_ReminDrvgRng_msgType* pmsg = (_c_B3_VCU_ReminDrvgRng_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ChargingTimeout, 0, pmsg->Signals.IsTimeout)
    }

    void func_MSG_BCM_CANFD_212_ID(const char *data)
    {
        _c_212_BCM_CANFD_msgType* pmsg = (_c_212_BCM_CANFD_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_Wiperfault, pmsg->Signals.BCM_ErrWipr, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TSRSts_1C1_ID(const char *data)
    {
        _c_1C1_ADAS_TSRSts_msgType* pmsg = (_c_1C1_ADAS_TSRSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_LimitSpeed, pmsg->Signals.ADAS_TSR_LimitSpeed, pmsg->Signals.IsTimeout)
//qid        GMAPMSGVALUESINSERT(MSG_AutoLamp, pmsg->Signals.ADAS_AHB_St, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TSR_162_ID(const char *data)
    {
//        _c_162_ADAS_TSR_msgType* pmsg = (_c_162_ADAS_TSR_msgType *)data;
//qxh        GMAPMSGVALUESINSERT(MSG_TSROffset, pmsg->Signals.ADAS_TSR_Warn_Offset_Set, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_FCTASts_1C3_ID(const char *data)
    {
        _c_1C3_ADAS_FCTASts_msgType* pmsg = (_c_1C3_ADAS_FCTASts_msgType *)data;
//qxh        GMAPMSGVALUESINSERT(MSG_ACCTargetSpeed, pmsg->Signals.ADAS_ACC_TargetSpeed, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_DOWSts_1C4_ID(const char *data)
    {
    }

    void func_MSG_ADAS_HWAReq_187_ID(const char *data)
    {
        _c_187_ADAS_HWAReq_msgType *pmsg = (_c_187_ADAS_HWAReq_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_HWAStatusLamp,pmsg->Signals.ADAS_HWA_status,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_ACC_ESCRq_185_ID(const char *data)
    {
        _c_185_ADAS_ACC_ESCRq_msgType *pmsg = (_c_185_ADAS_ACC_ESCRq_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_AccStatusLamp,pmsg->Signals.ADAS_ACC_St,pmsg->Signals.IsTimeout)
    }

    void func_MSG_PLCU_ParkLockSts_1E1_ID(const char *data)
    {
        _c_1E1_PLCU_ParkLockSts_msgType* pmsg = (_c_1E1_PLCU_ParkLockSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ParkLockSts, pmsg->Signals.PLCU_ParkLockSt, pmsg->Signals.IsTimeout)
    }
    void func_VCU_DivModReq_208_ID(const char *data)
    {
        _c_208_VCU_DivModReq_msgType* pmsg = (_c_208_VCU_DivModReq_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_VCU_VehSrvcWarn,pmsg->Signals.VCU_VehSrvcWarn,pmsg->Signals.IsTimeout)
    }
    void func_ADAS_ACCSts_181_ID(const char *data)
    {
        _c_181_ADAS_ACCSts_msgType* pmsg = (_c_181_ADAS_ACCSts_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_CurveSpeed, pmsg->Signals.ADAS_ACC_CurveSpeed, pmsg->Signals.IsTimeout)
    }
}

void ParsingData::run()
{
    while(!isInterruptionRequested())
    {
        while( false == m_messageList.empty() )
        {
            // 在子线程解析数据
            QMutexLocker _locker(&mutex);
            Parsing_Message _messageData = m_messageList.front();

            m_messageList.pop_front();  //delete list
            _locker.unlock();

            hmiReceiveMsg(_messageData);
        }
        msleep(10);
    }
}

ParsingData::ParsingData()
{
    start(QThread::NormalPriority);
}

void ParsingData::startControl()
{
}


ParsingData::~ParsingData()
{
    requestInterruption();
    quit();
    wait(100);
}

void ParsingData::RegistIVSMsg()
{
    if(true != ivs_client_init()){
        qWarning()<<"IVS_CONNECT_NG";
    }
    int len = sizeof(idList)/sizeof(RpcMsgId);
    for(int i=0; i<len; i++) {
        ivs_client_set_message_callback(idList[i], display_Msg_CallbackFunc_HMI,0);
    }
}

void ParsingData::SendMsg(Parsing_Message argument)
{
    QMutexLocker _locker(&mutex);
    Q_UNUSED(_locker)
    m_messageList.push_back(argument);
}

void ParsingData::hmiReceiveMsg(Parsing_Message argument)
{
    // 根据id调用不同的拆包函数
    std::map<unsigned char, FunctionParser>::iterator it;
    it = ParseFunc.find(argument.m_messageID);
    if(it != ParseFunc.end())
    {
        //        (it->second)((const char *)argument.m_messageData);
                (it->second)((const char *)argument.m_messageData.data());    //-->QByteArray转回const char *使用
    }

}
