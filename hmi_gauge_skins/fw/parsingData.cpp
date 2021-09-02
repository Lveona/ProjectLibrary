#include "include/parsingData.h"
#include <string.h>

/*ivs注册信号*/
static RpcMsgId idList[] {
    MSG_EEPROM_0_ID,
    MSG_EEPROM_2_ID,
    MSG_MCU_0_ID,
    MSG_MCU_1_ID,
    MSG_MCU_4_ID,
    MSG_MCU_5_ID,
    MSG_VCU_ReminDrvgRng_B3_ID,
    MSG_VCU_HvCoolgModReq_98h_ID,
    MSG_CCU_AirT_1F7h_ID ,
//    MSG_BCM_HUFeedback_1B2h_ID,
//    MSG_BCM_States_1B1h_ID,
    MSG_ESC_HMIInfo_136h_ID ,
    MSG_VCU_WarnForHU_148_ID,
    MSG_VCU_AccPosGearSts_97h_ID,
    MSG_MCU_3_ID,
    MSG_BCM_TireP_247_ID,
    MSG_BCM_CANFD_212_ID,
    MSG_VCU_HvInfForDrvr_9Ah_ID,
    MSG_EPS_EPSInfo_130h_ID,
    MSG_BMS_BatteryRelayErrSts_F7_ID,
    MSG_ESC_HmiLampReq_138_ID,
    MSG_ESC_FctSt_131_ID,
    MSG_BCM_AlrmWarnIn_245_ID,
    MSG_SUM_SuspSys_17C_ID,
    MSG_BMS_HvBattTiRmnChrgn_200_ID,
    MSG_SCM_States_183_ID,
//qid     MSG_BCM_MirrorPosReq_152_ID,
    MSG_BCM_TireWarn_246_ID,
    MSG_ACM_ACMInfo_201h_ID,
    MSG_BCM_TireT_248_ID,
    MSG_eBooster_EbbSts_123_ID,
    MSG_SUM_SuspSts_1BC_ID,
    MSG_ADAS_LKSSts_1C0_ID,
    MSG_ADAS_TSRSts_1C1_ID,
//qid     MSG_ADAS_SRSts_182_ID,
    MSG_ADAS_DOWSts_1C4_ID,
    MSG_ADAS_SysSts_230_ID,
//    MSG_ADAS_TrackTar1_23F_ID,
    MSG_ADAS_FCTASts_1C3_ID,
    MSG_ADAS_FCTA_1C2_ID,
    MSG_IPU_DCDCSts_DB_ID,
//qid     MSG_VCU_MaxPowerAvl_AC_ID,
    MSG_ANRC_PrkgPDC_196_ID,
    MSG_DMS_DMSInfoHU_24D_ID,
    MSG_ADAS_SRRsts_23F_ID,
    MSG_BMS_BatSocU_F9_ID,
    MSG_BMS_HVBatterySts_FB_ID,
    MSG_ADAS_Line1_240_ID,
    MSG_ADAS_Line2_241_ID,
    MSG_ADAS_Line3_242_ID,
    MSG_ADAS_Line4_243_ID,
    MSG_ADAS_AEB_169_ID,
    MSG_ADAS_TrackTar01_231_ID,         //动态目标物0
    MSG_ADAS_TrackTar0_232_ID,          //静态目标物0
    MSG_ADAS_TrackTar1_233_ID,          //动态目标物1
    MSG_ADAS_TrackTar23_234_ID,         //静态目标物1
    MSG_ADAS_TrackTar2_235_ID,          //动态目标物2
    /* TBD 静态目标物*/
    MSG_ADAS_TrackTar3_236_ID,          //动态目标物3
    MSG_ADAS_TrackTar3_Static_23C_ID,   //静态目标物3
    MSG_ADAS_TrackTar4_23A_ID,          //动态目标物4
    MSG_ADAS_TrackTar4_Static_23D_ID,   //静态目标物4
    MSG_ADAS_TrackTar5_23B_ID,          //动态目标物5
    MSG_ADAS_TrackTar5_Static_23E_ID,   //静态目标物5
//qid    MSG_ADAS_TrackTar45_239_ID,
//xb    MSG_ANRC_HUDisplay_176h_ID,
//qid    MSG_ANRC_ParkingDistance02_179h_ID,
    MSG_ANRC_PrkgDst_SecOC2_20Eh_ID,
    MSG_ANRC_SDW_MEB_Info_20C_ID,
    MSG_LCMFL_FltSts_254_ID,
    MSG_LCMFR_FltSts_255_ID,
    MSG_LCMRL_BCM_LIN1ASWM_1E2_ID,
    MSG_LCMFL_LeFrntDirIndcrLam_142_ID,
    MSG_DCMFL_States1_1C6_ID      ,
    MSG_DCMFR_States_1B4_ID       ,
    MSG_BCM_ImobMstWarn_BE_ID     ,
    MSG_PLCU_ParkLockSts_1E1_ID   ,
    MSG_VCU_DivModReq_208_ID      ,
    MSG_ADAS_HWA_Warn_160_ID      ,
    MSG_DMS_DMSStatus_24B_ID      ,
    MSG_ADAS_HWAReq_187_ID        ,
    MSG_ADAS_ACC_ESCRq_185_ID     ,
    MSG_ETC_Module_30B_ID         ,
    MSG_BCM_LightReq_151h_ID      ,
};

/*ivp注册信号*/
static ivp_callback_id idListMedia[] {
    //phone
    IVP_CB_ID_PHONE_INFO,
    IVP_CB_ID_CALLS_INFO,
    IVP_CB_ID_COLLECS_INFO,
    IVP_CB_ID_IMAGE_INFO,
    IVP_CB_ID_VOLUME_INFO,
    IVP_CB_ID_NAVI_INFO, //导航互联
    IVP_CB_ID_SOURCE_INFO   //多媒体
};


extern "C"
{
    static std::map<unsigned char, FunctionParser> ParseFunc =
    {
        {MSG_MCU_0_ID,                        func_MSG_MCU_0_ID},
        {MSG_MCU_5_ID,                        func_MSG_MCU_5_ID},
        {MSG_EEPROM_0_ID,                     func_MSG_EEPROM_0_ID},
        {MSG_EEPROM_2_ID,                     func_MSG_EEPROM_2_ID},
        {MSG_MCU_0_ID,                        func_MSG_MCU_0_ID},
        {MSG_MCU_1_ID,                        func_MSG_MCU_1_ID},
        {MSG_MCU_4_ID,                        func_MSG_MCU_4_ID},
        {MSG_MCU_5_ID,                        func_MSG_MCU_5_ID},
        {MSG_VCU_ReminDrvgRng_B3_ID,          func_MSG_VCU_ReminDrvgRng_B3_ID},
        {MSG_VCU_HvCoolgModReq_98h_ID,        func_MSG_VCU_HvCoolgModReq_98h_ID},
        {MSG_CCU_AirT_1F7h_ID ,               func_MSG_CCU_AirT_1F7h_ID },
//        {MSG_BCM_HUFeedback_1B2h_ID,          func_MSG_BCM_HUFeedback_1B2h_ID},
//        {MSG_BCM_States_1B1h_ID,              func_MSG_BCM_States_1B1h_ID         },
        {MSG_ESC_HMIInfo_136h_ID ,            func_MSG_ESC_HMIInfo_136h_ID        },
        {MSG_VCU_WarnForHU_148_ID,            func_MSG_VCU_WarnForHU_148_ID       },
        {MSG_VCU_AccPosGearSts_97h_ID,        func_MSG_VCU_AccPosGearSts_97h_ID},
        {MSG_MCU_3_ID,                        func_MSG_MCU_3_ID},
        {MSG_BCM_TireP_247_ID,                func_MSG_BCM_TireP_247_ID           },
        {MSG_BCM_CANFD_212_ID,                func_MSG_BCM_CANFD_212_ID           },
        {MSG_VCU_HvInfForDrvr_9Ah_ID,         func_MSG_VCU_HvInfForDrvr_9Ah_ID    },
        {MSG_EPS_EPSInfo_130h_ID,             func_MSG_EPS_EPSInfo_130h_ID        },
        {MSG_BMS_BatteryRelayErrSts_F7_ID,    func_MSG_BMS_BatteryRelayErrSts_F7_ID},
        {MSG_ESC_HmiLampReq_138_ID,           func_MSG_ESC_HmiLampReq_138_ID      },
        {MSG_ESC_FctSt_131_ID,                func_MSG_ESC_FctSt_131_ID           },
        {MSG_BCM_AlrmWarnIn_245_ID,           func_MSG_BCM_AlrmWarnIn_245_ID      },
        {MSG_SUM_SuspSys_17C_ID,              func_MSG_SUM_SuspSys_17C_ID         },
        {MSG_BMS_HvBattTiRmnChrgn_200_ID,     func_MSG_BMS_HvBattTiRmnChrgn_200_ID},
        {MSG_SCM_States_183_ID,               func_MSG_SCM_States_183_ID          },
        {MSG_BCM_LightReq_151h_ID,            func_MSG_BCM_LightReq_151h_ID    },
//       {MSG_BCM_MirrorPosReq_152_ID,         func_MSG_BCM_MirrorPosReq_152_ID    },
        {MSG_BCM_TireWarn_246_ID,             func_MSG_BCM_TireWarn_246_ID        },
        {MSG_ACM_ACMInfo_201h_ID,             func_MSG_ACM_ACMInfo_201h_ID        },
        {MSG_BCM_TireT_248_ID,                func_MSG_BCM_TireT_248_ID           },
        {MSG_eBooster_EbbSts_123_ID,          func_MSG_eBooster_EbbSts_123_ID},
        {MSG_SUM_SuspSts_1BC_ID,              func_MSG_SUM_SuspSts_1BC_ID         },
        {MSG_ADAS_LKSSts_1C0_ID,              func_MSG_ADAS_LKSSts_1C0_ID         },
        {MSG_ADAS_TSRSts_1C1_ID,              func_MSG_ADAS_TSRSts_1C1_ID         },
//       {MSG_ADAS_SRSts_182_ID,               func_MSG_ADAS_SRSts_182_ID         },
        {MSG_ADAS_DOWSts_1C4_ID,              func_MSG_ADAS_DOWSts_1C4_ID         },
        {MSG_ADAS_SysSts_230_ID,              func_MSG_ADAS_SysSts_230_ID         },
        {MSG_ADAS_AEB_169_ID,                 func_MSG_ADAS_AEB_169_ID         },
//        {MSG_ADAS_TrackTar1_23F_ID,           func_MSG_ADAS_TrackTar1_23F_ID      },
        {MSG_ADAS_FCTASts_1C3_ID,             func_MSG_ADAS_FCTASts_1C3_ID        },
        {MSG_ADAS_FCTA_1C2_ID,                func_MSG_ADAS_FCTA_1C2_ID        },
        {MSG_IPU_DCDCSts_DB_ID,               func_MSG_IPU_DCDCSts_DB_ID          },
//       {MSG_VCU_MaxPowerAvl_AC_ID,           func_MSG_VCU_MaxPowerAvl_AC_ID      },
        {MSG_ANRC_PrkgPDC_196_ID,             func_MSG_ANRC_PrkgPDC_196_ID        },
        {MSG_DMS_DMSInfoHU_24D_ID,            func_MSG_DMS_DMSInfoHU_24D_ID       },
        {MSG_ADAS_SRRsts_23F_ID,              func_MSG_ADAS_SRRsts_23F_ID         },
        {MSG_BMS_BatSocU_F9_ID,               func_MSG_BMS_BatSocU_F9_ID          },
        {MSG_BMS_HVBatterySts_FB_ID,          func_MSG_BMS_HVBatterySts_FB_ID     },

        {MSG_ADAS_Line1_240_ID,               func_MSG_ADAS_Line1_240_ID         },
        {MSG_ADAS_Line2_241_ID,               func_MSG_ADAS_Line2_241_ID          },
        {MSG_ADAS_Line3_242_ID,               func_MSG_ADAS_Line3_242_ID          },
        {MSG_ADAS_Line4_243_ID,               func_MSG_ADAS_Line4_243_ID          },
        {MSG_ADAS_TrackTar01_231_ID,          func_MSG_ADAS_TrackTar01_231_ID     },
        {MSG_ADAS_TrackTar0_232_ID,           func_MSG_ADAS_TrackTar0_232_ID     },
        {MSG_ADAS_TrackTar1_233_ID,           func_MSG_ADAS_TrackTar1_233_ID     },
        {MSG_ADAS_TrackTar23_234_ID,          func_MSG_ADAS_TrackTar23_234_ID     },
        {MSG_ADAS_TrackTar2_235_ID,           func_MSG_ADAS_TrackTar2_235_ID     },
        {MSG_ADAS_TrackTar3_236_ID,           func_MSG_ADAS_TrackTar3_236_ID     },
        {MSG_ADAS_TrackTar3_Static_23C_ID,    func_MSG_ADAS_TrackTar3_Static_23C_ID     },
        {MSG_ADAS_TrackTar4_23A_ID,           func_MSG_ADAS_TrackTar4_23A_ID     },
        {MSG_ADAS_TrackTar4_Static_23D_ID,    func_MSG_ADAS_TrackTar4_Static_23D_ID     },
        {MSG_ADAS_TrackTar5_23B_ID,           func_MSG_ADAS_TrackTar5_23B_ID     },
        {MSG_ADAS_TrackTar5_Static_23E_ID,    func_MSG_ADAS_TrackTar5_Static_23E_ID     },
//        {MSG_ADAS_TrackTar45_239_ID,          func_MSG_ADAS_TrackTar45_239_ID     },
//xb        {MSG_ANRC_HUDisplay_176h_ID,          func_MSG_ANRC_HUDisplay_176h_ID     },
//        {MSG_ANRC_ParkingDistance02_179h_ID,  func_MSG_ANRC_ParkingDistance02_179h_ID},
        {MSG_ANRC_PrkgDst_SecOC2_20Eh_ID,     func_MSG_ANRC_DetailDst2_20E_ID     },
        {MSG_ANRC_SDW_MEB_Info_20C_ID,        func_MSG_ANRC_SDWInfo_20Ch_ID       },
        {MSG_LCMFL_FltSts_254_ID,             func_MSG_LCMFL_FltSts_254_ID       },
        {MSG_LCMFR_FltSts_255_ID,             func_MSG_LCMFL_FltSts_255_ID       },
        {MSG_LCMRL_BCM_LIN1ASWM_1E2_ID,       func_MSG_LCMRL_BCM_LIN1ASWM_1E2_ID       },
        {MSG_LCMFL_LeFrntDirIndcrLam_142_ID,  func_MSG_LCMFL_LeFrntDirIndcrLam_142_ID       },
        {MSG_DCMFL_States1_1C6_ID             ,func_DCMFL_States1_1C6_ID      },
        {MSG_DCMFR_States_1B4_ID              ,func_DCMFR_States_1B4_ID       },
        {MSG_BCM_ImobMstWarn_BE_ID            ,func_BCM_ImobMstWarn_BE_ID     },
        {MSG_PLCU_ParkLockSts_1E1_ID          ,func_PLCU_ParkLockSts_1E1_ID   },
        {MSG_VCU_DivModReq_208_ID             ,func_VCU_DivModReq_208_ID      },
        {MSG_ADAS_ACCSts_181_ID               ,func_ADAS_ACCSts_181_ID},
        {MSG_ADAS_HWA_Warn_160_ID             ,func_ADAS_HWA_Warn_160_ID      },
        {MSG_DMS_DMSStatus_24B_ID             ,func_DMS_DMSStatus_24B_ID      },
        {MSG_ADAS_HWAReq_187_ID               ,func_MSG_ADAS_HWAReq_187_ID    },
        {MSG_ADAS_ACC_ESCRq_185_ID            ,func_MSG_ADAS_ACC_ESCRq_185_ID },
        {MSG_ETC_Module_30B_ID                ,func_ETC_Module_30B_ID      },


    };

    void display_Msg_CallbackFunc_HMI(unsigned char message_id,const unsigned char * pData, unsigned char data_len, void * pUserData)
    {
        ( void ) pUserData;
        Parsing_Message msg;
        msg.m_messageID = message_id;
        msg.data_len = data_len;
        msg.m_messageData = QByteArray( (const char*)pData, data_len);    //-->数据使用QByteArray存储
//        memset((char *)msg.m_messageData, 0, MAXLENMSG);
//        memcpy((char *)msg.m_messageData, (char *)pData, data_len);
        ParsingData::instance()->SendMsg(msg);
    }

    void func_MSG_MCU_0_ID(const char *data)
    {
        _c_MSG_MCU_0_msgType* pmsg = (_c_MSG_MCU_0_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CHARGE_PERCENT,pmsg->Signals.MCU_BATT_VAL,(unsigned char)0)
    }

    void func_MSG_MCU_1_ID(const char *data)
    {
        _c_MSG_MCU_1_msgType* pmsg = (_c_MSG_MCU_1_msgType *)data;

        GMAPMSGVALUESINSERT(MSG_ODO,pmsg->Signals.MCU_ODO,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AS_TRIP,pmsg->Signals.MCU_TRIP_A,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AS_AVG_SPEED,pmsg->Signals.MCU_AVERAGE_SPEED_A,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AS_DRIVING_TIME,pmsg->Signals.MCU_DRIVING_TIME_A,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AS_AVG_POWER,pmsg->Signals.TripAApc,(unsigned char)0);

        GMAPMSGVALUESINSERT(MSG_AR_TRIP,pmsg->Signals.MCU_TRIP_B,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AR_AVG_SPEED,pmsg->Signals.MCU_AVERAGE_SPEED_B,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AR_DRIVING_TIME,pmsg->Signals.MCU_DRIVING_TIME_B,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_AR_AVG_POWER,pmsg->Signals.TripBApc,(unsigned char)0);
    }


    void func_MSG_MCU_5_ID(const char *data)
    {
        _c_MSG_MCU_5_msgType* pmsg = (_c_MSG_MCU_5_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CHARGE_COLOR,pmsg->Signals.CLS_TT_BATT_COLOR,(unsigned char)0);
    }

    void func_MSG_EEPROM_0_ID                 (const char * data)
    {
        _c_MSG_EEPROM_0_msgType* pmsg = (_c_MSG_EEPROM_0_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ODO_CLEAR_TIME,pmsg->Signals.aubDiagOdoClearTimes,(unsigned char)0);
 		GMAPMSGVALUESINSERT(MSG_SETLANGUGE,pmsg->Signals.LanguageSet,(unsigned char)0);
    }
    void func_MSG_EEPROM_2_ID                 (const char * data)
    {
        _c_MSG_EEPROM_2_msgType* pmsg = (_c_MSG_EEPROM_2_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CARINFO_SCREEN_INDEX,pmsg->Signals.CLS_LAST_SOURCE_CURRENT_REQ_BAR,(unsigned char)0);
    }

    void func_MSG_MCU_4_ID                    (const char * data)
    {
        _c_MSG_MCU_4_msgType* pmsg = (_c_MSG_MCU_4_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_HARDKEY_STATUS,pmsg->Signals.MCU_CLUSTER_HARDL_KEY_STATUS,(unsigned char)0);
        GMAPMSGVALUESINSERT(MSG_HARDKEY_NUMBER,pmsg->Signals.MCU_CLUSTER_HARDL_KEY_NUMBER,(unsigned char)0);
    }

    void func_MSG_VCU_ReminDrvgRng_B3_ID      (const char * data)
    {
        _c_B3_VCU_ReminDrvgRng_msgType* pmsg = (_c_B3_VCU_ReminDrvgRng_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CHARGE_CABLE_STATUS,pmsg->Signals.VCU_ChrgCnctrDetd,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_REMAIN_RANGE,pmsg->Signals.VCU_RmnDrvgRng,pmsg->Signals.IsTimeout);
    }

    void func_MSG_VCU_HvCoolgModReq_98h_ID    (const char * data)
    {
        _c_98_VCU_HvCoolgModReq_msgType* pmsg = (_c_98_VCU_HvCoolgModReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_DRIVE_MODE,pmsg->Signals.VCU_ActvdDrvMod,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_CHARGE_STATUS,pmsg->Signals.VCU_ChrgSts,pmsg->Signals.IsTimeout)
    }

    void func_MSG_CCU_AirT_1F7h_ID            (const char * data)
    {
        _c_1F7_CCU_AirT_msgType* pmsg = (_c_1F7_CCU_AirT_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_TEMP,pmsg->Signals.CCU_AmbAirT,pmsg->Signals.IsTimeout)
    }

    void func_MSG_BCM_HUFeedback_1B2h_ID      (const char * data){}
    void func_MSG_BCM_States_1B1h_ID          (const char * data){}
    void func_MSG_ESC_HMIInfo_136h_ID         (const char * data)
    {
        _c_136_ESC_HMIInfo_msgType* pmsg = (_c_136_ESC_HMIInfo_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BRAKE_SYSTEM,pmsg->Signals.ESC_HmiLampReqBrkSys,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_EPB_FAULT,pmsg->Signals.ESC_HmiLampReqEpbFlt,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_HDC,pmsg->Signals.ESC_HmiLampReqHdc,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_DRV_AVH,pmsg->Signals.ESC_HMIDrvPrstInAVH,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ESC_FAULT,pmsg->Signals.ESC_HmiLampReqEsc,pmsg->Signals.IsTimeout)
    }
    void func_MSG_VCU_WarnForHU_148_ID        (const char * data)
    {
        _c_148_VCU_WarnForHU_msgType* pmsg = (_c_148_VCU_WarnForHU_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_VCU_SYSTEM_FAULT,pmsg->Signals.VCU_SystemFailureHMI,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_VCU_BATT_HEAT,pmsg->Signals.VCU_BatteryHeatCriticalHMI,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_VCU_COOLANT_ALARN,pmsg->Signals.VCU_CoolantAlarmHMI,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_VCU_EMOTOR_ALARM,pmsg->Signals.VCU_EMotorAlarmHMI,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_VCU_SYSTEM_POWER_LIMIT,pmsg->Signals.VCU_SystemPowerLimitationHMI,pmsg->Signals.IsTimeout)
    }
    void func_MSG_VCU_AccPosGearSts_97h_ID    (const char * data)
    {
        _c_97_VCU_AccPosGearSts_msgType* pmsg = (_c_97_VCU_AccPosGearSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_READY, pmsg->Signals.VCU_PtSt, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_GEAR, pmsg->Signals.VCU_LoglGearStsAct, pmsg->Signals.IsTimeout)
    }
    void func_MSG_MCU_3_ID                    (const char * data){}
    void func_MSG_BCM_TireP_247_ID            (const char * data)
    {
        _c_247_BCM_TireP_msgType* pmsg = (_c_247_BCM_TireP_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_LF_TIRE_PRESSURE, pmsg->Signals.BCM_TirePFrntLe, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RF_TIRE_PRESSURE, pmsg->Signals.BCM_TirePFrntRi, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RR_TIRE_PRESSURE, pmsg->Signals.BCM_TirePReRi, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LR_TIRE_PRESSURE, pmsg->Signals.BCM_TirePReLe, pmsg->Signals.IsTimeout)
    }
    void func_MSG_BCM_CANFD_212_ID            (const char * data)
    {
        _c_212_BCM_CANFD_msgType* pmsg = (_c_212_BCM_CANFD_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BRAKE_PADS,pmsg->Signals.BCM_HmiLampReqBrkPadWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_WIPER_FAULT,pmsg->Signals.BCM_ErrWipr,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_AutoLiCtrlWarn,pmsg->Signals.BCM_AutoLiCtrlWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_HeadLightOpenWarn,pmsg->Signals.BCM_HeadLightOpenWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ReLeRvsLiFailrSts,pmsg->Signals.BCM_ReLeRvsLiFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ReRiRvsLiFailrSts,pmsg->Signals.BCM_ReRiRvsLiFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ReLeFogFailrSts,pmsg->Signals.BCM_ReLeFogFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ReRiFogFailrSts,pmsg->Signals.BCM_ReRiFogFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ReLeBrkLiFailrSts,pmsg->Signals.BCM_ReLeBrkLiFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ReRiBrkLiFailrSts,pmsg->Signals.BCM_ReRiBrkLiFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_MidHiBrkLiFailrSts,pmsg->Signals.BCM_MidHiBrkLiFailrSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_EgyLvlDegradationWarn,pmsg->Signals.BCM_EgyLvlDegradationWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_LvlBattULoWarn,pmsg->Signals.BCM_LvlBattULoWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_PwrRlyErrWarn,pmsg->Signals.BCM_PwrRlyErrWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_BrkPedlIndcnWarn,pmsg->Signals.BCM_BrkPedlIndcnWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_ImobBkpWarn,pmsg->Signals.BCM_ImobBkpWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_AutoWiprCtrlWarn,pmsg->Signals.BCM_AutoWiprCtrlWarn,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_BCM_KeyInsideWarn,   pmsg->Signals.BCM_KeyInsideWarn,   pmsg->Signals.IsTimeout)

    }
    void func_MSG_VCU_HvInfForDrvr_9Ah_ID     (const char * data)
    {
        _c_9A_VCU_HvInfForDrvr_msgType* pmsg = (_c_9A_VCU_HvInfForDrvr_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_VCU_INVLD_CDN,         pmsg->Signals.VCU_InvldCdnToDrvr,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_VCU_ELEC_PT_LIMD_DECEL,pmsg->Signals.VCU_ElecPtLimdDecelSts,pmsg->Signals.IsTimeout)
    }
    void func_MSG_EPS_EPSInfo_130h_ID         (const char * data)
    {
        _c_130_EPS_EPSInfo_msgType* pmsg = (_c_130_EPS_EPSInfo_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_STEERING_FAULT,pmsg->Signals.EPS_SteerWarnLamp_Rq,pmsg->Signals.IsTimeout)
    }
    void func_MSG_BMS_BatteryRelayErrSts_F7_ID(const char * data)
    {
        _c_F7_BMS_BatteryRelayErrSts_msgType* pmsg = (_c_F7_BMS_BatteryRelayErrSts_msgType *)data;
  /*[NACA-442448] BUG:绝缘故障无鸣响*/
        GMAPMSGVALUESINSERT(MSG_BMS_VehHvIsoErr,pmsg->Signals.BMS_VehHvIsoErr,pmsg->Signals.IsTimeout)

    }
    void func_MSG_ESC_HmiLampReq_138_ID       (const char * data)
    {
        _c_138_ESC_HmiLampReq_msgType* pmsg = (_c_138_ESC_HmiLampReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_TCS_FAULT,pmsg->Signals.ESC_HmiLampReqTCS,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_ABS_FAULT,pmsg->Signals.ESC_HmiLampReqABS,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_EPB_MODE, pmsg->Signals.ESC_HmiLampReqEPBMode,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_AVH_FAULT,pmsg->Signals.ESC_HmiLampReqAVHSts,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_TCS_OFF,  pmsg->Signals.ESC_HmiLampReqTCSOff,pmsg->Signals.IsTimeout);
    }
    void func_MSG_ESC_FctSt_131_ID            (const char * data)
    {
        _c_131_ESC_FctSt_msgType* pmsg = (_c_131_ESC_FctSt_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_AVL_EBD_FAULT,pmsg->Signals.ESC_CtrlrAvlEbd,pmsg->Signals.IsTimeout);
    }
    void func_MSG_BCM_AlrmWarnIn_245_ID       (const char * data)
    {
        _c_245_BCM_AlrmWarnIn_msgType* pmsg = (_c_245_BCM_AlrmWarnIn_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_FL_DOOR_STATUS, pmsg->Signals.BCM_DoorDrvrNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_FR_DOOR_STATUS, pmsg->Signals.BCM_DoorPassNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RL_DOOR_STATUS, pmsg->Signals.BCM_DoorRearLeNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RR_DOOR_STATUS, pmsg->Signals.BCM_DoorRearRiNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TAIL,           pmsg->Signals.BCM_TrNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_HOOD,           pmsg->Signals.BCM_HoodNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_FL_CHARGE_PORT, pmsg->Signals.BCM_ChrgnFlapNotClsdWarnReq, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RL_CHARGE_PORT, pmsg->Signals.BCM_ChrgnFlapRiNotClsdWarnReq, pmsg->Signals.IsTimeout)

        GMAPMSGVALUESINSERT(MSG_LOW_BRAKE_FLUID,pmsg->Signals.BCM_BrkFldLvlDisp,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LOW_GLASS_WATER,pmsg->Signals.BCM_WtrLvlDisp,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_KEY_BATT_LOW,   pmsg->Signals.BCM_PepsAdvKeyFobBattChrgnSt,pmsg->Signals.IsTimeout)
    }
    void func_MSG_SUM_SuspSys_17C_ID          (const char * data)
    {
        _c_17C_SUM_SuspSys_msgType* pmsg = (_c_17C_SUM_SuspSys_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_SUSPENSION_SYSTEM_FAULT,pmsg->Signals.SUM_SuspSysFailrSts,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_SUSPENSION_SYSTEM,      pmsg->Signals.SUM_SuspSysProtnSts,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_SUM_DAMP_LIMP,          pmsg->Signals.SUM_DampCtrlLimpHome,pmsg->Signals.IsTimeout);
    }
    void func_MSG_BMS_HvBattTiRmnChrgn_200_ID (const char * data)
    {
        _c_200_BMS_HvBattTiRmnChrgn_msgType* pmsg = (_c_200_BMS_HvBattTiRmnChrgn_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_REMAIN_CHARGE_TIME, pmsg->Signals.BMS_HvBattTiRmnChrgn, pmsg->Signals.IsTimeout);
 /*[NACA-442443] 动力电池过温告警无响应*/
        GMAPMSGVALUESINSERT(MSG_HV_BATT,            pmsg->Signals.BMS_HVBattThermRunaway,pmsg->Signals.IsTimeout);

    }
    void func_MSG_SCM_States_183_ID           (const char * data)
    {
        _c_183_SCM_States_msgType* pmsg = (_c_183_SCM_States_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_SHIFTER_FAULT,pmsg->Signals.SCM_E_ShiftFault,pmsg->Signals.IsTimeout);
        GMAPMSGVALUESINSERT(MSG_SCM_HiBeamSwtFailrSts,pmsg->Signals.SCM_HiBeamSwtFailrSts,pmsg->Signals.IsTimeout);

    }

    void func_MSG_BCM_LightReq_151h_ID     (const char * data)
    {

        _c_151_BCM_LightReq_msgType* pmsg = (_c_151_BCM_LightReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BCM_KeyDetectWarn,pmsg->Signals.BCM_KeyDetectWarn,pmsg->Signals.IsTimeout);
    }
    void func_MSG_BCM_MirrorPosReq_152_ID     (const char * data)
    {
        _c_152_BCM_MirrorPosReq_msgType* pmsg = (_c_152_BCM_MirrorPosReq_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_IMM_WARNING,pmsg->Signals.BCM_ImmWarning,pmsg->Signals.IsTimeout);
    }
    void func_MSG_BCM_TireWarn_246_ID         (const char * data)
    {
        _c_246_BCM_TireWarn_msgType* pmsg = (_c_246_BCM_TireWarn_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_TIRE_WARN_FRONT_LE,pmsg->Signals.BCM_TireWarnFrntLe,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TIRE_WARN_FRONT_RI,pmsg->Signals.BCM_TireWarnFrntRi,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TIRE_WARN_REAR_LE, pmsg->Signals.BCM_TireWarnReLe,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TIRE_WARN_REAR_RI, pmsg->Signals.BCM_TireWarnReRi,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ACM_ACMInfo_201h_ID         (const char * data)
    {
        _c_201_ACM_ACMInfo_msgType* pmsg = (_c_201_ACM_ACMInfo_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ACM_AIRB_WARN,pmsg->Signals.ACM_AirbWarnLampSt,pmsg->Signals.IsTimeout)
    }
    void func_MSG_BCM_TireT_248_ID            (const char * data)
    {
        _c_248_BCM_TireT_msgType* pmsg = (_c_248_BCM_TireT_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_LF_TIRE_TEMP,  pmsg->Signals.BCM_TireTFrntLe, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RF_TIRE_TEMP,  pmsg->Signals.BCM_TireTFrntRi, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RR_TIRE_TEMP,  pmsg->Signals.BCM_TireTReRi, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LR_TIRE_TEMP,  pmsg->Signals.BCM_TireTReLe, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TIRE_SYSTEM_FAULT,pmsg->Signals.BCM_TireMonSysSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TIRE_FAULT,    pmsg->Signals.BCM_TireMonTireSts,pmsg->Signals.IsTimeout)
    }
    void func_MSG_eBooster_EbbSts_123_ID      (const char * data)
    {
        _c_123_eBooster_EbbSts_msgType* pmsg = (_c_123_eBooster_EbbSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_BOOSTER_FAULT,pmsg->Signals.eBooster_HmiLampReqiboosterFlt,pmsg->Signals.IsTimeout)
    }
    void func_MSG_SUM_SuspSts_1BC_ID          (const char * data)
    {
        _c_1BC_SUM_SuspSts_msgType* pmsg = (_c_1BC_SUM_SuspSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_SUSPENSION_MOVE,pmsg->Signals.SUM_SuspChassisHeiMovmtDir,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_LKSSts_1C0_ID          (const char * data)
    {
        _c_1C0_ADAS_LKSSts_msgType* pmsg = (_c_1C0_ADAS_LKSSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_LKS_ACTIVE,pmsg->Signals.ADAS_LKS_Active_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_ELK_ACTIVE,pmsg->Signals.ADAS_ELK_Active_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_ELK,       pmsg->Signals.ADAS_ELK_St,pmsg->Signals.IsTimeout)

        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_LDW_St), pmsg->Signals.ADAS_LDW_St, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_LKA_St), pmsg->Signals.ADAS_LKA_St, pmsg->Signals.IsTimeout)


    }
    void func_MSG_ADAS_TSRSts_1C1_ID          (const char * data)
    {
        _c_1C1_ADAS_TSRSts_msgType* pmsg = (_c_1C1_ADAS_TSRSts_msgType *)data;
//wid        GMAPMSGVALUESINSERT(MSG_ADAS_ACC_WARN,pmsg->Signals.ADAS_ACC_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TSR_FAULT,pmsg->Signals.ADAS_TSR_Operating_St,pmsg->Signals.IsTimeout)
        //GMAPMSGVALUESINSERT(MSG_ADAS_ACC_FAULT,pmsg->Signals.ADAS_ACC_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_TST_LIMIT_SPEED,pmsg->Signals.ADAS_TSR_LimitSpeed,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_SRSts_182_ID          (const char * data)
    {
        _c_182_ADAS_SRSts_msgType* pmsg = (_c_182_ADAS_SRSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ACC_PASSIVE_REASON,pmsg->Signals.ADAS_AHB_St,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_DOWSts_1C4_ID          (const char * data)
    {
        _c_1C4_ADAS_DOWSts_msgType* pmsg = (_c_1C4_ADAS_DOWSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_RCW_WARN,  pmsg->Signals.ADAS_RCW_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RCTA_LEFT_WARN, pmsg->Signals.ADAS_RCTA_left_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_RCTA_RIGHT_WARN,pmsg->Signals.ADAS_RCTA_Right_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCA_LEFT_WARN,  pmsg->Signals.ADAS_LCA_Left_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCA_RIGHT_WARN, pmsg->Signals.ADAS_LCA_Right_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RCW,       pmsg->Signals.ADAS_RCW_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RCTA,      pmsg->Signals.ADAS_RCTA_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LCA,       pmsg->Signals.ADAS_LCA_St,pmsg->Signals.IsTimeout)

//qxh        GMAPMSGVALUESINSERT(MSG_ADAS_L3_WARNING,pmsg->Signals.ADAS_L3warningstatus,pmsg->Signals.IsTimeout)
//qxh        GMAPMSGVALUESINSERT(MSG_ADAS_HWA_HANDSON,pmsg->Signals.ADAS_HWA_ILC_HandsonReq,pmsg->Signals.IsTimeout)
//qxh        GMAPMSGVALUESINSERT(MSG_ADAS_HWA_ST,pmsg->Signals.ADAS_HWA_ILC_St,pmsg->Signals.IsTimeout)
//qxh        GMAPMSGVALUESINSERT(MSG_ADAS_HWA_ABORT,pmsg->Signals.ADAS_HWA_ILC_AbortReason,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_DOW_ST,pmsg->Signals.ADAS_DOW_St,pmsg->Signals.IsTimeout)
        //GMAPMSGVALUESINSERT(MSG_ADSS_HWA_STATUS,pmsg->Signals.ADAS_HWA_status,pmsg->Signals.IsTimeout)
                /*同一个信号，为啥定义两个枚举*/
//qxh        GMAPMSGVALUESINSERT(MSG_ADAS_L3_STATUS,pmsg->Signals.ADAS_L3availablestatus,pmsg->Signals.IsTimeout)
//qxh        GMAPMSGVALUESINSERT(MSG_ADAS_L3AVAILABLESTATUS,pmsg->Signals.ADAS_L3availablestatus,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_DOW_FL,pmsg->Signals.ADAS_DOW_FL_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_DOW_RL,pmsg->Signals.ADAS_DOW_RL_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_DOW_FR,pmsg->Signals.ADAS_DOW_FR_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_DOW_RR,pmsg->Signals.ADAS_DOW_RR_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_RCTB_St),pmsg->Signals.ADAS_RCTB_St,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_HWAReq_187_ID(const char *data)
    {
        _c_187_ADAS_HWAReq_msgType *pmsg = (_c_187_ADAS_HWAReq_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADSS_HWA_STATUS,pmsg->Signals.ADAS_HWA_status,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_ACC_ESCRq_185_ID(const char *data)
    {
        _c_185_ADAS_ACC_ESCRq_msgType *pmsg = (_c_185_ADAS_ACC_ESCRq_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_ACC_FAULT,pmsg->Signals.ADAS_ACC_St,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_SysSts_230_ID          (const char * data)
    {
        _c_230_ADAS_SysSts_msgType* pmsg = (_c_230_ADAS_SysSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_CONTROLLER_FAULT,pmsg->Signals.ADAS_ControllerFaultStatus,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_AEB_169_ID          (const char * data)
    {
        _c_169_ADAS_AEB_msgType* pmsg = (_c_169_ADAS_AEB_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_ADASBRKJERKREQ,pmsg->Signals.ADAS_AdasBrkJerkReq, pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TrackTar1_23F_ID       (const char * data)
    {
    }
    void func_MSG_ADAS_FCTASts_1C3_ID         (const char * data)
    {
        _c_1C3_ADAS_FCTASts_msgType* pmsg = (_c_1C3_ADAS_FCTASts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_FCW_ST,pmsg->Signals.ADAS_FCW_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_AEB_ST,pmsg->Signals.ADAS_AEB_St,pmsg->Signals.IsTimeout)

        GMAPMSGVALUESINSERT(MSG_ADAS_FCWRequest,pmsg->Signals.ADAS_FCWRequest,pmsg->Signals.IsTimeout)
 /*[NACA-442825] RCTB报警无鸣响*/
        GMAPMSGVALUESINSERT(MSG_ADAS_ADASEBREQTYP,pmsg->Signals.ADAS_AdasEbReqTyp,pmsg->Signals.IsTimeout)

    }

    void func_MSG_ADAS_FCTA_1C2_ID(const char *data)
    {
        _c_1C2_ADAS_FCTA_msgType* pmsg = (_c_1C2_ADAS_FCTA_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_FCTA_ST,pmsg->Signals.ADAS_FCTA_St,pmsg->Signals.IsTimeout)

//        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Le_LgtPosn           ),pmsg->Signals.ADAS_FCTA_Le_LgtPosn           ,pmsg->Signals.IsTimeout)
//qxh        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Left_Active_St       ),pmsg->Signals.ADAS_FCTA_Left_Active_St       ,pmsg->Signals.IsTimeout)
//        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_RollgCntr            ),pmsg->Signals.ADAS_FCTA_RollgCntr            ,pmsg->Signals.IsTimeout)
//        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Ri_LgtPosn           ),pmsg->Signals.ADAS_FCTA_Ri_LgtPosn           ,pmsg->Signals.IsTimeout)
//        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Chks                 ),pmsg->Signals.ADAS_FCTA_Chks                 ,pmsg->Signals.IsTimeout)
//qxh        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Right_Active_St      ),pmsg->Signals.ADAS_FCTA_Right_Active_St      ,pmsg->Signals.IsTimeout)
//        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Left_LateralPosition ),pmsg->Signals.ADAS_FCTA_Left_LateralPosition ,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTB_St                   ),pmsg->Signals.ADAS_FCTB_St                   ,pmsg->Signals.IsTimeout)
//        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_FCTA_Right_LateralPosition),pmsg->Signals.ADAS_FCTA_Right_LateralPosition,pmsg->Signals.IsTimeout)

    }

    void func_MSG_IPU_DCDCSts_DB_ID           (const char * data)
    {
        _c_DB_IPU_DCDCSts_msgType* pmsg = (_c_DB_IPU_DCDCSts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_IPU_EEM_DCDC_FAULT,pmsg->Signals.IPU_EEMDCDCFailrSts,pmsg->Signals.IsTimeout)
    }
    void func_MSG_VCU_MaxPowerAvl_AC_ID       (const char * data)
    {
        _c_AC_VCU_MaxPowerAvl_msgType* pmsg = (_c_AC_VCU_MaxPowerAvl_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_VCU_LV_WARN,pmsg->Signals.VCU_LvWarn,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ANRC_PrkgPDC_196_ID         (const char * data)
    {
        _c_196_ANRC_PrkgPDC_msgType* pmsg = (_c_196_ANRC_PrkgPDC_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKG_PDC_MODE,pmsg->Signals.ANRC_PrkgPDCMod,pmsg->Signals.IsTimeout)
    }
    void func_MSG_DMS_DMSInfoHU_24D_ID        (const char * data)
    {
        _c_24D_DMS_DMSInfoHU_msgType* pmsg = (_c_24D_DMS_DMSInfoHU_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(DMS_DrowsnsLevel      ),pmsg->Signals.DMS_DrowsnsLevel      ,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(DMS_DistrctnLevel     ),pmsg->Signals.DMS_DistrctnLevel     ,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(DMS_DMSAbandon_Reason ),pmsg->Signals.DMS_DMSAbandon_Reason ,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_SRRsts_23F_ID      	  (const char * data){
        _c_23F_ADAS_SRRsts_msgType* pmsg = (_c_23F_ADAS_SRRsts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_FMRRSENSOR_BLOC,pmsg->Signals.ADAS_FMRRSensorBloc_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_FMRRSENSOR_FAULT,pmsg->Signals.ADAS_FMRRSensorFail_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_FCAMSENSOR_BLOC,pmsg->Signals.ADAS_FCamSensorBloc_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADSS_LFSRRSENSOR_BLOC,pmsg->Signals.ADAS_LFSRRSensorBloc_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LRSRRSENSOR_BLOC,pmsg->Signals.ADAS_LRSRRSensorBloc_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RRSRRSENSOR_BLOC,pmsg->Signals.ADAS_RRSRRSensorBloc_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RFSRRSENSOR_BLOC,pmsg->Signals.ADAS_RFSRRSensorBloc_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_FMRRSENSOR_CALI,pmsg->Signals.ADAS_FMRRSensorCali_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_FCAMSENSOR_CALI,pmsg->Signals.ADAS_FCamSensorCali_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LFSRRSENSOR_CALI,pmsg->Signals.ADAS_LFSRRSensorCali_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LRSRRSENSOR_CALI,pmsg->Signals.ADAS_LRSRRSensorCali_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RRSRRSENSOR_CALI,pmsg->Signals.ADAS_RRSRRSensorCali_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RFSRRSENSOR_CALI,pmsg->Signals.ADAS_RFSRRSensorCali_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_FCMASENSOR_FAULT,pmsg->Signals.ADAS_FCamSensorFail_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LFSRRSENSOR_FAULT,pmsg->Signals.ADAS_LFSRRSensorFail_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LRSRRSENSOR_FAULT,pmsg->Signals.ADAS_LRSRRSensorFail_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RRSRRSENSOR_FAULT,pmsg->Signals.ADAS_RRSRRSensorFail_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_RFSRRSENSOR_FAULT,pmsg->Signals.ADAS_RFSRRSensorFail_St,pmsg->Signals.IsTimeout)
    }
    void func_MSG_BMS_BatSocU_F9_ID      	  (const char * data)
    {
        _c_F9_BMS_BatSocU_msgType* pmsg = (_c_F9_BMS_BatSocU_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CHARING_VOLTAGE,pmsg->Signals.BMS_HvBattU,pmsg->Signals.IsTimeout)
    }
    void func_MSG_BMS_HVBatterySts_FB_ID      (const char * data)
    {
        _c_FB_BMS_HVBatterySts_msgType* pmsg = (_c_FB_BMS_HVBatterySts_msgType *)data;
        GMAPMSGVALUESINSERT(MSG_CHARING_ELECTRIC,pmsg->Signals.BMS_HvBattI,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_Line1_240_ID(const char* data) {
        _c_240_ADAS_Line1_msgType* pmsg = (_c_240_ADAS_Line1_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_1_DISPLAY,pmsg->Signals.ADAS_Line_1_Display,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_1_TYPE,   pmsg->Signals.ADAS_Line_1_Type,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_1_A0,     pmsg->Signals.ADAS_Line_1_A0,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_1_A1,     pmsg->Signals.ADAS_Line_1_A1,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_1_A2,     pmsg->Signals.ADAS_Line_1_A2,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_1_A3,     pmsg->Signals.ADAS_Line_1_A3,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_Line2_241_ID(const char* data) {
        _c_241_ANRC_SVSSts_msgType* pmsg = (_c_241_ANRC_SVSSts_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_2_DISPLAY,pmsg->Signals.ADAS_Line_2_Display,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_2_TYPE,pmsg->Signals.ADAS_Line_2_Type,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_2_A0,pmsg->Signals.ADAS_Line_2_A0,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_2_A1,pmsg->Signals.ADAS_Line_2_A1,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_2_A2,pmsg->Signals.ADAS_Line_2_A2,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_2_A3,pmsg->Signals.ADAS_Line_2_A3,pmsg->Signals.IsTimeout)

    }

    void func_MSG_ADAS_Line3_242_ID(const char* data) {
        _c_242_ADAS_Line3_msgType* pmsg = (_c_242_ADAS_Line3_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_3_DISPLAY,pmsg->Signals.ADAS_Line_3_Display,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_3_TYPE,pmsg->Signals.ADAS_Line_3_Type,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_3_A0,pmsg->Signals.ADAS_Line_3_A0,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_3_A1,pmsg->Signals.ADAS_Line_3_A1,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_3_A2,pmsg->Signals.ADAS_Line_3_A2,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_3_A3,pmsg->Signals.ADAS_Line_3_A3,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_Line4_243_ID(const char* data){
        _c_243_ADAS_Line4_msgType* pmsg = (_c_243_ADAS_Line4_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_4_DISPLAY,pmsg->Signals.ADAS_Line_4_Display,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_4_TYPE,pmsg->Signals.ADAS_Line_4_Type,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_4_A0,pmsg->Signals.ADAS_Line_4_A0,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_4_A1,pmsg->Signals.ADAS_Line_4_A1,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_4_A2,pmsg->Signals.ADAS_Line_4_A2,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_LINE_4_A3,pmsg->Signals.ADAS_Line_4_A3,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TrackTar01_231_ID(const char*data) {
        _c_231_ADAS_TrackTar01_msgType* pmsg = (_c_231_ADAS_TrackTar01_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR0_STATIC_ST,pmsg->Signals.ADAS_TrackTar0_Static_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR0_STATIC_OBJECTTYPE,pmsg->Signals.ADAS_TrackTar0_Static_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR0_STATIC_LATPO,pmsg->Signals.ADAS_TrackTar0_Static_LatPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR0_STATIC_LGTPO,pmsg->Signals.ADAS_TrackTar0_Static_LgtPo,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TrackTar0_232_ID(const char*data) {
        _c_232_ADAS_TrackTar0_msgType* pmsg = (_c_232_ADAS_TrackTar0_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET0_ST,pmsg->Signals.ADAS_TrackTarget0_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET0_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget0_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR0_LGTPO,pmsg->Signals.ADAS_TrackTar0_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR0_LATPO,pmsg->Signals.ADAS_TrackTar0_LatPo,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TrackTar1_233_ID(const char*data) {
        _c_233_ADAS_TrackTar1_msgType* pmsg = (_c_233_ADAS_TrackTar1_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET1_ST,pmsg->Signals.ADAS_TrackTarget1_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET1_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget1_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR1_LGTPO,pmsg->Signals.ADAS_TrackTar1_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR1_LATPO,pmsg->Signals.ADAS_TrackTar1_LatPo,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TrackTar23_234_ID(const char* data) {
        _c_234_ADAS_TrackTar23_msgType* pmsg = (_c_234_ADAS_TrackTar23_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR1_STATIC_ST,pmsg->Signals.ADAS_TrackTar1_Static_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR1_STATIC_OBJECTTYPE,pmsg->Signals.ADAS_TrackTar1_Static_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR1_STATIC_LATPO,pmsg->Signals.ADAS_TrackTar1_Static_LatPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR1_STATIC_LGTPO,pmsg->Signals.ADAS_TrackTar1_Static_LgtPo,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar2_235_ID(const char* data) {
        _c_235_MSG_ADAS_TrackTar2_msgType* pmsg = (_c_235_MSG_ADAS_TrackTar2_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET2_ST,pmsg->Signals.ADAS_TrackTarget2_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET2_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget2_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR2_LGTPO,pmsg->Signals.ADAS_TrackTar2_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR2_LATPO,pmsg->Signals.ADAS_TrackTar2_LatPo,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar3_236_ID(const char* data) {
        _c_236_MSG_ADAS_TrackTar3_msgType* pmsg = (_c_236_MSG_ADAS_TrackTar3_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR3_LGTPO,pmsg->Signals.ADAS_TrackTar3_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR3_LATPO,pmsg->Signals.ADAS_TrackTar3_LatPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET3_ST,pmsg->Signals.ADAS_TrackTarget3_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET3_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget3_ObjectType,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar3_Static_23C_ID(const char* data) {
        _c_23C_MSG_ADAS_TrackTar3_Static_msgType* pmsg = (_c_23C_MSG_ADAS_TrackTar3_Static_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR3_STATIC_ST,pmsg->Signals.ADAS_TrackTarget3_Static_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR3_STATIC_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget3_Static_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR3_STATIC_LATPO,pmsg->Signals.ADAS_TrackTar3_Static_LatPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR3_STATIC_LGTPO,pmsg->Signals.ADAS_TrackTar3_Static_LgtPo,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar4_23A_ID(const char* data) {
        _c_23A_MSG_ADAS_TrackTar4_msgType* pmsg = (_c_23A_MSG_ADAS_TrackTar4_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET4_ST,pmsg->Signals.ADAS_TrackTarget4_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET4_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget4_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR4_LGTPO,pmsg->Signals.ADAS_TrackTar4_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR4_LATPO,pmsg->Signals.ADAS_TrackTar4_LatPo,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar4_Static_23D_ID(const char* data) {
        _c_23D_MSG_ADAS_TrackTar4_Static_msgType* pmsg = (_c_23D_MSG_ADAS_TrackTar4_Static_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR4_STATIC_ST,pmsg->Signals.ADAS_TrackTarget4_Static_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR4_STATIC_OBJECTTYPE,pmsg->Signals.ADAS_TrackTar4_Static_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR4_STATIC_LGTPO,pmsg->Signals.ADAS_TrackTar4_Static_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR4_STATIC_LATPO,pmsg->Signals.ADAS_TrackTar4_Static_LatPo,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar5_23B_ID(const char* data) {
        _c_23B_MSG_ADAS_TrackTar5_msgType* pmsg = (_c_23B_MSG_ADAS_TrackTar5_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET5_ST,pmsg->Signals.ADAS_TrackTarget5_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTARGET5_OBJECTTYPE,pmsg->Signals.ADAS_TrackTarget5_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR5_LGTPO,pmsg->Signals.ADAS_TrackTar5_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR5_LATPO,pmsg->Signals.ADAS_TrackTar5_LatPo,pmsg->Signals.IsTimeout)
    }
    void func_MSG_ADAS_TrackTar5_Static_23E_ID(const char* data) {
        _c_23E_MSG_ADAS_TrackTar5_Static_msgType* pmsg = (_c_23E_MSG_ADAS_TrackTar5_Static_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR5_STATIC_ST,pmsg->Signals.ADAS_TrackTarget5_Static_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR5_STATIC_OBJECTTYPE,pmsg->Signals.ADAS_TrackTar5_Static_ObjectType,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR5_STATIC_LGTPO,pmsg->Signals.ADAS_TrackTar5_Static_LgtPo,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_TRACKTAR5_STATIC_LATPO,pmsg->Signals.ADAS_TrackTar5_Static_LatPo,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ADAS_TrackTar45_239_ID(const char* data){
        _c_239_ADAS_TrackTar45_msgType* pmsg = (_c_239_ADAS_TrackTar45_msgType*)data;
    }

    void func_MSG_ANRC_HUDisplay_176h_ID(const char* data) {
//qxh        _c_176_ANRC_HUDisplay_msgType* pmsg = (_c_176_ANRC_HUDisplay_msgType*)data;
//qxh        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSTSINDCR,pmsg->Signals.ANRC_PrkgStsIndcr,pmsg->Signals.IsTimeout)

    }

    void func_MSG_ANRC_ParkingDistance02_179h_ID(const char* data) {
        _c_179_ANRC_ParkingDistance02_msgType* pmsg = (_c_179_ANRC_ParkingDistance02_msgType*)data;

        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGLESLOTTYP1,pmsg->Signals.ANRC_PrkgLeSlotTyp1,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGLESLOTTYP2,pmsg->Signals.ANRC_PrkgLeSlotTyp2,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGLESLOTTYP3,pmsg->Signals.ANRC_PrkgLeSlotTyp3,pmsg->Signals.IsTimeout)

        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGRISLOTTYP1,pmsg->Signals.ANRC_PrkgRiSlotTyp1,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGRISLOTTYP2,pmsg->Signals.ANRC_PrkgRiSlotTyp2,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGRISLOTTYP3,pmsg->Signals.ANRC_PrkgRiSlotTyp3,pmsg->Signals.IsTimeout)

    }

    void func_MSG_ANRC_DetailDst2_20E_ID(const char* data) {
        _c_20Eh_ANRC_PrkgDst_SecOC2_msgType* pmsg = (_c_20Eh_ANRC_PrkgDst_SecOC2_msgType*)data;

        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGFRNTLEDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgFrntLeDstToObstcl,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGFRNTRIDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgFrntRiDstToObstcl,pmsg->Signals.IsTimeout)

        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGREARLEDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgRearLeDstToObstcl,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGREARMIDLEDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgRearMidLeDstToObstcl,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGFRNTMIDLEDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgFrntMidLeDstToObstcl,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGFRNTMIDRIDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgFrntMidRiDstToObstcl,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGREARMIDRIDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgRearMidRiDstToObstcl,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGREARRIDSTTOOBSTCL,pmsg->Signals.ANRC_PrkgRearRiDstToObstcl,pmsg->Signals.IsTimeout)
    }

    void func_MSG_ANRC_SDWInfo_20Ch_ID(const char* data) {
        _c_20C_ANRC_SDW_MEB_Info_msgType* pmsg = (_c_20C_ANRC_SDW_MEB_Info_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEFRNTLEOBSTCLZON,pmsg->Signals.ANRC_PrkgSideFrntLeObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEFRNTMIDLEOBSTCLZON,pmsg->Signals.ANRC_PrkgSideFrntMidLeObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEREARMIDLEOBSTCLZON,pmsg->Signals.ANRC_PrkgSideRearMidLeObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEREARLEOBSTCLZON,pmsg->Signals.ANRC_PrkgSideRearLeObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEFRNTRIOBSTCLZON,pmsg->Signals.ANRC_PrkgSideFrntRiObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEFRNTMIDRIOBSTCLZON,pmsg->Signals.ANRC_PrkgSideFrntMidRiObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEREARMIDRIOBSTCLZON,pmsg->Signals.ANRC_PrkgSideRearMidRiObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ANRC_PRKGSIDEREARRIOBSTCLZON,pmsg->Signals.ANRC_PrkgSideRearRiObstclZon,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ANRC_PrkgMEBWarnType ),pmsg->Signals.ANRC_PrkgMEBWarnType, pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ANRC_MEB_FuncSts     ),pmsg->Signals.ANRC_MEB_FuncSts,     pmsg->Signals.IsTimeout)


    }

    void func_MSG_LCMFL_FltSts_254_ID(const char *data)
    {
        _c_254_LCMFL_FltSts_msgType* pmsg = (_c_254_LCMFL_FltSts_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeFrntPosnLampFltSts,pmsg->Signals.LCMFL_LeFrntPosnLampFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeLoBeamFltSts,pmsg->Signals.LCMFL_LeLoBeamFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeGrpdLampModFltSts,pmsg->Signals.LCMFL_LeGrpdLampModFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeHiBeamFltSts,pmsg->Signals.LCMFL_LeHiBeamFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeFltDayLampSts,pmsg->Signals.LCMFL_LeFltDayLampSts,pmsg->Signals.IsTimeout)

    }

    void func_MSG_LCMFL_FltSts_255_ID(const char *data)
    {
        _c_255_LCMFR_FltSts_msgType* pmsg = (_c_255_LCMFR_FltSts_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeFrntPosnLampFltSts,pmsg->Signals.LCMFR_RiFrntPosnLampFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFR_RiLoBeamFltSts,pmsg->Signals.LCMFR_RiLoBeamFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFR_RiGrpdLampModFltSts,pmsg->Signals.LCMFR_RiGrpdLampModFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFR_RiHiBeamFltSts,pmsg->Signals.LCMFR_RiHiBeamFltSts,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMFR_RiFltDayLampSts,pmsg->Signals.LCMFR_RiFltDayLampSts,pmsg->Signals.IsTimeout)

    }

    void func_MSG_LCMRL_BCM_LIN1ASWM_1E2_ID(const char *data)
    {
        _c_1E2_BCM_LIN1ASWM_msgType* pmsg = (_c_1E2_BCM_LIN1ASWM_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_LCMRL_LeRePosnFailrSt,pmsg->Signals.LCMRL_LeRePosnFailrSt,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMRR_RiRePosnFailrSt,pmsg->Signals.LCMRR_RiRePosnFailrSt,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMRL_LeReDirIndcrFailrSt,pmsg->Signals.LCMRL_LeReDirIndcrFailrSt,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_LCMRR_RiReDirIndcrFailrSt,pmsg->Signals.LCMRR_RiReDirIndcrFailrSt,pmsg->Signals.IsTimeout)
    }

    void func_MSG_LCMFL_LeFrntDirIndcrLam_142_ID(const char *data)
    {
        _c_142_LCMFL_LeFrntDirIndcrLam_msgType* pmsg = (_c_142_LCMFL_LeFrntDirIndcrLam_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_LCMFL_LeFrntDirIndcrFailrSt,pmsg->Signals.LCMFL_LeFrntDirIndcrFailrSt,pmsg->Signals.IsTimeout)

    }

    void func_DCMFL_States1_1C6_ID(const char *data)
    {
        _c_1C6_DCMFL_States1_msgType* pmsg = (_c_1C6_DCMFL_States1_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_DCMFL_LeSideDirIndcrFailrSt,pmsg->Signals.DCMFL_LeSideDirIndcrFailrSt,pmsg->Signals.IsTimeout)

    }

    void func_DCMFR_States_1B4_ID(const char *data)
    {
        _c_1B4_DCMFR_States_msgType* pmsg = (_c_1B4_DCMFR_States_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_DCMFR_RiSideDirIndcrFailrSt,pmsg->Signals.DCMFR_RiSideDirIndcrFailrSt,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(DCMFR_RiSideDirIndcrFailrSt),pmsg->Signals.DCMFR_RiSideDirIndcrFailrSt,pmsg->Signals.IsTimeout)

    }

    void func_BCM_ImobMstWarn_BE_ID(const char *data)
    {
        _c_BE_BCM_ImobMstWarn_msgType* pmsg = (_c_BE_BCM_ImobMstWarn_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(BCM_ImobMstWarn),pmsg->Signals.BCM_ImobMstWarn,pmsg->Signals.IsTimeout)

    }

    void func_PLCU_ParkLockSts_1E1_ID(const char *data)
    {
        _c_1E1_PLCU_ParkLockSts_msgType* pmsg = (_c_1E1_PLCU_ParkLockSts_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(PLCU_ParkLockSt),pmsg->Signals.PLCU_ParkLockSt,pmsg->Signals.IsTimeout)

    }

    void func_VCU_DivModReq_208_ID(const char *data)
    {
        _c_208_VCU_DivModReq_msgType* pmsg = (_c_208_VCU_DivModReq_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(VCU_VehSrvcWarn),pmsg->Signals.VCU_VehSrvcWarn,pmsg->Signals.IsTimeout)

    }

    void func_ADAS_ACCSts_181_ID(const char *data)
    {
        _c_181_ADAS_ACCSts_msgType* pmsg = (_c_181_ADAS_ACCSts_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_ACC_GoNotifier),pmsg->Signals.ADAS_ACC_GoNotifier,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ACC_PASSIVE_REASON,pmsg->Signals.ADAS_ACC_Passive_Reason,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_ADAS_ACC_TIMEGAP,pmsg->Signals.ADAS_ACC_TimeGap,pmsg->Signals.IsTimeout)

    }

    void func_ADAS_HWA_Warn_160_ID(const char *data)
    {
        _c_160_ADAS_HWA_Warn_msgType* pmsg = (_c_160_ADAS_HWA_Warn_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_HWA_Warn_St),pmsg->Signals.ADAS_HWA_Warn_St,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ADAS_HWA_HandsonReq),pmsg->Signals.ADAS_HWA_HandsonReq,pmsg->Signals.IsTimeout)

    }

    void func_DMS_DMSStatus_24B_ID(const char *data)
    {
        _c_24B_MSG_DMS_DMSStatus_msgType* pmsg = (_c_24B_MSG_DMS_DMSStatus_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(DMS_DMSSts),pmsg->Signals.DMS_DMSSts,pmsg->Signals.IsTimeout)

    }

    void func_ETC_Module_30B_ID(const char *data)
    {
        _c_30B_MSG_ETC_Module_msgType* pmsg = (_c_30B_MSG_ETC_Module_msgType*)data;
        GMAPMSGVALUESINSERT(MSG_MACRO(ETC_RFModule),pmsg->Signals.ETC_RFModule ,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ETC_ESAMModule),pmsg->Signals.ETC_ESAMModule	     ,pmsg->Signals.IsTimeout)
        GMAPMSGVALUESINSERT(MSG_MACRO(ETC_Antitemper),pmsg->Signals.ETC_Antitemper	     ,pmsg->Signals.IsTimeout)
      //  GMAPMSGVALUESINSERT(MSG_MACRO(ETC_ESAMActivation ),pmsg->Signals.ETC_ESAMActivation   ,pmsg->Signals.IsTimeout)

    }

//    void func_ETC_TransSt_1A1_ID(const char *data)
//    {
//        _c_1A1_MSG_ETC_TransSt_msgType* pmsg = (_c_1A1_MSG_ETC_TransSt_msgType*)data;
//        GMAPMSGVALUESINSERT(MSG_MACRO(ETC_EntranceExitType ),pmsg->Signals.ETC_EntranceExitType   ,pmsg->Signals.IsTimeout)

//    }

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
