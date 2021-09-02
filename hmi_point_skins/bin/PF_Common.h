/********************************************************************************************/
/** <!--------------------------------------------------------------------------------------- 
 *	Copyright (C) 2010-2016 Neusoft, Inc. 
 *	All Rights Reserved.
 *	The following programs are the sole property of Neusoft Inc.,
 *	and contain its proprietary and confidential information.
 *	---------------------------------------------------------------------------------------->
 *
 *	\file			PF_Common.h
 *	\date			2018.10.25
 *	\author			lizhongjun
 *	\description	Definitions of the initialization-related tables
 *	\version		1.000
 *
 *********************************************************************************************
 *	\par	Revision History:
 *	<!-----	No.		Date		Revised by		Details	------------------------------------->
 *			0001	20181025	lizhongjun		    New
 *          0002    20190314    liangxiaojian   Theme <-> DriverMode
 *  1. Modify union define _c_MSG_EEPROM_0_msgType, + member THEME_SWITCH for notifing SOC
 *          0003    20190314    liangxiaojian   Define macro _MCU_RH850 in project configuration file, so delete it
 *          0004    20190314    liangxiaojian   Modify MSG_SYS_LCD_COM_ERR_TC_msgType for Cluster DTC Check RPC Proxy
 *          0005    20190316    liangxiaojian   add soc rpc id MSG_0x5A3_WarnMsg_TCU_ID for data pack _c_WarnMsg_TCU_IP_msgType
 *                                              + Set ID°ÍoMSG_HMI_SYS_SET_SIG_TC_ID for last menu set
                                                + _u8LastMenu and rename u8ThemeSwitch in c_MSG_EEPROM_0_msgType
 *          0006    20190523    liangxiaojian   Ref. ∆Ê»T1C_FunctionSpec_Cluster_œ¬œﬂ≈‰÷√.xlsx
 *          0007    20190530    liangxiaojian   + MSG_SOC_TT_SET_SIG_TC_ID::BrakeFluidWarning
 *          0008    20190624    liangxiaojian   Version: 0.7.5
 *                                              1.SET:SOC_SET_CLR_CMD ID + MSG_SOC_FUEL_RESISTANCE_DETECTION
 *                                              2.GET:MSG_EEPROM_3_ID + RESISTANCE_TEST_RESULT
 *          0009    20190715    liangxiaojian   Add IHU Line Configuration
 ********************************************************************************************/
#ifndef PF_COMMON_H
#define PF_COMMON_H

/********************************************************************************************/
/*							Include File Section											*/
/********************************************************************************************/
#ifdef _DEBUG_SOC_PM_
#include "apn_basic_type.h"
#include "Model.h"
#endif

/********************************************************************************************/
/*							Macro Definition Section										*/
/********************************************************************************************/
/*
 * MCU project macro define
---
#define _DEBUG_SOC_PM_
*/

/*
 *rpc message signal value macro define
 */
#define VALID       0x00
#define INVALID     0x01

#define NO_TIMEOUT  0x00
#define TIMEOUT     0x01

/*
**define OPECODE for soc ,define in RPC document
*/
#define OPCODE_SOC_SET_CLR_CMD  0x0601
#define OPCODE_SOC_GET_INFOR    0x0602
#define OPCODE_SOC_SET_INFOR    0x0603
/* t1c delete to add new opcode 0605 #define OPCODE_SOC_GET_EEP_DATA 0x0605 */

/*==========================================================================================*/
/*	Common Typedefs																			*/
/*==========================================================================================*/

#ifndef  _DEBUG_SOC_PM_H/* The file is used in SOC */
typedef unsigned char        Type_uByte;     /*!< Unsigned 8-Bit Integer		*/
typedef unsigned short int	 Type_uHWord;    /*!< Unsigned 16-Bit Integer		*/
typedef unsigned  long int         Type_uWord;     /*!< Unsigned 32-Bit Integer		*/
typedef unsigned  long long int    Type_uDWord;    /*!< Unsigned 64-Bit Integer		*/

//typedef signed int    Type_sWord;    /*!< signed 32-Bit Integer		*/
#endif

/********************************************************************************************/
/*                          enum Definition Section                                         */
/********************************************************************************************/

/*==========================================================================================*/
/*  OPCODE 0x0602 && 0x0605  RPC Message Name - ID Enumeration define                       */
/*==========================================================================================*/
/* 
**Used By ClusterApp & HMI,msg direction: MCU ==> SOC
*/
typedef enum {
    /* NVM type message ID 0x00~ 0x0F */
	MSG_EEPROM_0_ID               = 0x00,
	MSG_EEPROM_1_ID,
	MSG_EEPROM_2_ID,
	MSG_EEPROM_3_ID,
	MSG_EEPROM_4_ID,    // Ref . 0009

	/* DID type message ID 0x10 ~ 0x1F*/
	MSG_DIDCTL_0_ID               = 0x10,

	/* MCU type message ID 0x20~ 0x3F */
	MSG_MCU_0_ID                  = 0x20,
	MSG_MCU_1_ID,
	MSG_MCU_2_ID, 
	MSG_MCU_3_ID,
	MSG_MCU_4_ID,
	MSG_MCU_5_ID,
	MSG_MCU_6_ID,
	MSG_MCU_7_ID,
	/* CAN type message ID 0x40~ 0x7F */
	MSG_ESC_HMIInfo_136h_ID	 = 0x40,
	MSG_VCU_WarnForHU_148_ID,
	MSG_BCM_LightReq_151h_ID,
	MSG_VCU_AccPosGearSts_97h_ID,
	MSG_VCU_HvInfForDrvr_9Ah_ID,
	MSG_VCU_HvCoolgModReq_98h_ID,
	MSG_EPS_EPSInfo_130h_ID,
	MSG_ACM_ACMInfo_201h_ID,
	MSG_CCU_AirT_1F7h_ID,
	MSG_BMS_BatSocU_F9_ID,
	MSG_BMS_HVBatterySts_FB_ID,	
	MSG_BCM_AlrmWarnIn_245_ID,
	MSG_AVAS_CurrSts_17F_ID,//0x50
	MSG_BCM_TireWarn_246_ID,
	MSG_BCM_TireP_247_ID,
	MSG_BCM_TireT_248_ID,
	MSG_BCM_CANFD_212_ID,
	MSG_ESC_HmiLampReq_138_ID,
	MSG_ESC_FctSt_131_ID,
	MSG_SUM_SuspSts_1BC_ID,
	MSG_SUM_SuspSys_17C_ID,
	MSG_BMS_BatteryRelayErrSts_F7_ID,
	MSG_IPU_DCDCSts_DB_ID,
	MSG_VCU_CurrEngPwr_2F1_ID,
	MSG_BMS_HvBattTiRmnChrgn_200_ID,
	MSG_VCU_ReminDrvgRng_B3_ID,
	MSG_SCM_States_183_ID,
	MSG_ADAS_AEB_169_ID,
	MSG_ADAS_TSRSts_1C1_ID,
	MSG_ADAS_FCTA_1C2_ID,
	MSG_ADAS_FCTASts_1C3_ID,
	MSG_ADAS_DOWSts_1C4_ID,
	MSG_ADAS_LKSSts_1C0_ID,
	MSG_ADAS_HWAReq_187_ID,
	MSG_ADAS_SysSts_230_ID,
	MSG_ADAS_TrackTar01_231_ID,
	MSG_ADAS_TrackTar0_232_ID,
	MSG_ADAS_TrackTar1_233_ID,
	MSG_ADAS_SRRsts_23F_ID,
	MSG_ANRC_PrkgPDC_196_ID,
	MSG_DMS_DMSInfoHU_24D_ID,
	MSG_ESC_VehSpd_132h_ID,//0x7d
	MSG_ANRC_PrkgDst_SecOC2_20Eh_ID,
	MSG_ANRC_SDW_MEB_Info_20C_ID,
	MSG_ANRC_PASInfo_SecOC1_176h_ID,
	MSG_ANRC_SVSSts_17A_ID,
	MSG_ADAS_Line2_241_ID,
	MSG_ADAS_Line3_242_ID,
	MSG_ADAS_Line4_243_ID,
	MSG_ADAS_TrackTar23_234_ID,
	MSG_LCMFL_FltSts_254_ID,
	MSG_LCMFR_FltSts_255_ID,
	MSG_LCMRL_BCM_LIN1ASWM_1E2_ID,
	MSG_LCMFL_LeFrntDirIndcrLam_142_ID,
	MSG_LCMFR_RiFrntDirIndcrLam_143_ID,
	MSG_DCMFL_States1_1C6_ID,
	MSG_DCMFR_States_1B4_ID,
	MSG_BCM_ImobMstWarn_BE_ID,
	MSG_PLCU_ParkLockSts_1E1_ID,
	MSG_VCU_DivModReq_208_ID,
	MSG_ADAS_ACCSts_181_ID,
	MSG_ADAS_HWA_Warn_160_ID,
	MSG_DMS_DMSStatus_24B_ID,
	MSG_ETC_Module_30B_ID,
	MSG_ADAS_Line1_240_ID,
	MSG_ADAS_TrackTar2_235_ID,
	MSG_ADAS_TrackTar3_236_ID,
	MSG_ADAS_TrackTar3_Static_23C_ID,
	MSG_ADAS_TrackTar4_23A_ID,
	MSG_ADAS_TrackTar4_Static_23D_ID,
	MSG_ADAS_TrackTar5_23B_ID,
	MSG_ADAS_TrackTar5_Static_23E_ID,
	MSG_VCU_PwrMtr_430_ID,
	MSG_VCU_RngSave1_B7_ID,
	MSG_VCU_RngSave2_B8_ID, 
	MSG_VCU_RngSave3_B9_ID, 
	MSG_VCU_TboxIndcd_2F6_ID, 
	MSG_VCU_ChrgSysReq_93_ID ,
	MSG_eBooster_EbbSts_123_ID,
	MSG_ADAS_ACC_ESCRq_185_ID,
	MSG_SCM_SAS_Status_9E_ID,
	//MSG_CLS_Voltage_STS,
	MSG_CLS_HighTemp_STS_ID,     //= 0x70,
	/* PM MODE type message ID 0xB0~ 0xBF */
	MSG_RPCAPP_SET_COVER_ANIMATION_ID = 0xB0,
	MSG_DIDS_Kernal_Info_ID,
	
	MSG_GET_HMI_DIDS_STATUS_ID
	
}RpcMsgId;
typedef enum
{
	//TSK_ID_CLSCYCLE
    kCluTxCAN_22Dh_Speed=0,
    kCluTxCAN_26Dh_Odo,
    kCluTxCAN_22Eh_DisErr,
}Cluster_TxCANIndex;

/*==========================================================================================*/
/*  OPCODE 0x0603  RPC Message Name - ID Enumeration define                                 */
/*==========================================================================================*/
/*
**SOC_SET_INFOR message id enum,used by ClusterApp & HMI,msg direction: SOC ==> MCU
*/
typedef enum{
    /*general funciton control id enum  : OPCODE 0x0603*/
    MSG_SOC_TT_SET_SIG_TC_ID    = 0x30,
    MSG_SOC_ADAS_SET_SIG_TC_ID,
    MSG_SOC_SYS_SET_SIG_TC_ID,
    MSG_SOC_HOME_SET_SIG_TC_ID,
    MSG_SOC_PR_SET_INFO_TC_ID,
    MSG_SOC_DIDCTL_RET_TC_ID,   /*not used currently,return DIDret upon receiving the DID service */
    MSG_SOC_RVCCTL_CODE_TC_ID,
    MSG_SOC_TT1_SET_SIG_TC_ID,
    MSG_HMI_SYS_SET_SIG_TC_ID,

    /*DID function control id enum      :OPCODE 0x0603*/
    MSG_DIDRET_ILLUMINATION_TC_ID = 0x40,
    MSG_DIDRET_INPUTSTATUS_TC_ID,
    MSG_SOC_AUDIO_ID,
    MSG_DID_HEX_D403h_REQ_ID,
    MSG_DID_HEX_D404h_REQ_ID,
    MSG_DID_HEX_D11Bh_REQ_ID,
    MSG_DID_HEX_D11Ch_REQ_ID,
    MSG_DID_HEX_D11Dh_REQ_ID,
    MSG_DID_HEX_D11Eh_REQ_ID,
    MSG_DID_HEX_E105h_REQ_ID,
    MSG_DID_HEX_E102h_REQ_ID,
    MSG_DID_HEX_E103h_REQ_ID,
    MSG_DID_HEX_E104h_REQ_ID,
    
    MSG_SOC_LAST_SOURCE_REQ_ID = 0xD0,
    MSG_SOC_OIL_PRESSURE_REQ_ID,
    MSG_SOC_REST_FACTORY_REQ_ID,
    MSG_SOC_CFG_WRITE_REQ_ID,

    /*system status control id enum     :OPCODE 0x0603*/
    MSG_SYS_LCD_COM_ERR_TC_ID     = 0x50,
    MSG_SYS_SOC_HIGH_TEMP_TC_ID,
/*DTC*/
	MSG_SOC_Screen_Display_Req=0x60,
	MSG_SOC_Screen_Connection_Req=0x61,
	MSG_SOC_Image_Display_Req=0x62,
	MSG_SOC_Avm_Send_Req=0x63,
/*AVM/RVC*/
    MSG_SOC_SEND_BCM_VehSt_ID=0x70,
    MSG_SOC_SEND_HU_SVSActReqFromHU_ID,
    MSG_SOC_SEND_HU_3D_SVS_ReqFromHU_ID,
    MSG_SOC_HU_SVSManVidSetupReqFromHU_ID,
    MSG_HU_3D_SVS_ViewChgReqFromHU_ID,
    MSG_SOC_HU_TouchInfo_ID,
    MSG_SOC_HU_PrkgPDCMuteSwt_ID,
    MSG_HU_SVS_Transparent_Model_ReqFromHU_ID,
    MSG_HU_SVS_Guidance_Line_ReqFromHU_ID,
    MSG_SOC_HU_SVSObjOverlay_ID,
    MSG_HU_SVSAutoViewSwitchModeReqFromHU_ID,
    /*engine mode control id enum       :OPCODE 0x0601*/
    MSG_SOC_ENGINE_MODE_CTL_ID = 0xF0,    
    MSG_SOC_FUEL_RESISTANCE_DETECTION = 0xF1,
}SocSetMsgTCID;
/********************************************************************************************/
/*							Struct Definition Section										*/
/********************************************************************************************/

/*==========================================================================================*/
/*  OPCODE 0x0603  struct define                                                            */
/*==========================================================================================*/
/*
 *SOC set MCU Type message unioin/struct define ;used by cluster && SOC::HMI
 */
 /*reference by teltale module,set can signals*/
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte ECOModeSWSts : 1;
        Type_uByte AirBagLampFailSts : 2;
        Type_uByte DrivermodeReq : 2;
        Type_uByte QDashACCFail : 2;
        Type_uByte FrontSeatBeltAlarmLight : 1;
        Type_uByte BrakeFluidWarning : 1;
        Type_uByte Reserved : 7;
    }Signals;
}_c_SOC_TT_SET_SIG_TC_msgType;

/*new add for engine oil pressure low warn send by guoping*/
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte EngineOilPressureLowWarn : 1;    /* 0x0:status ok,not active;0x1:status warning,active*/
        Type_uByte reserved                 : 7;
    }Signals;
}_c_SOC_TT1_SET_SIG_TC_msgType;

/*reference by ADAS module,set can signals*/
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte LDWLKA_LaneAssitTypeReq : 2;
        Type_uByte reserved : 6;
    }Signals;
}_c_SOC_ADAS_SET_SIG_TC_msgType;

/*reference by opening module,set can signals*/
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte DISFail : 1;
        Type_uByte reserved : 7;
    }Signals;
}_c_SOC_SYS_SET_SIG_TC_msgType;

/*reference by home control module,set can signals*/
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[3];
    struct
    {
        Type_uHWord ESPOFFSwitchSts      : 1;
        Type_uHWord SPDLMTPA_SATUS       : 2;       /*passive limit sped status ,0 off,can not turn on;1 on ;2 off,can turn on*/
        Type_uHWord unused0              : 1;       /*active limit speed status ,unused in T1C*/
        Type_uHWord unused1              : 12;      /*active limit speed value  ,unused in T1C*/
        Type_uByte SPDLMTPA_SETPOINT;               /*passive limit speed value,factor is 1,unit is Km/h*/
    } Signals;
//#ifndef _MCU_RH850
    //__attribute__ ((packed))
//#endif
   
}_c_SOC_HOME_SET_SIG_TC_msgType;

#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[5];
    struct
    {
        Type_uHWord NaviBtnPressInputValueX;
        Type_uHWord NaviBtnPressInputValueY;
        Type_uByte RRMDisplayAVMOff : 1;    /*0x0: Not active 0x1: Active*/
        Type_uByte TouchEvt         : 2;    /*0x0: Not active 0x1: Press down 0x2: Moving 0x3: Lift up*/
        Type_uByte unused0          : 5;
    }Signals;
//#ifndef _MCU_RH850
  //  __attribute__ ((packed))
//#endif
    
}_c_SOC_PR_SET_INFO_TC_msgType;

#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[3];
    struct
    {
        Type_uHWord DID_NUMBER;
        Type_uByte  CTL_RET;
    }Signals;
//#ifndef _MCU_RH850
 //   __attribute__ ((packed))
//#endif
}_c_SOC_DIDCTL_RET_TC_msgType;
#if 0
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte ESPOFFSwitchSts          :1;
        Type_uByte DrivermodeReq            :2;
        Type_uByte LDWLKA_LaneAssitTypeReq  :2;
        Type_uByte reserved                 :3;
    }Signals;
}MSG_SOC_SET_CAN_MESSAGE_SIGNAL;
#endif

#define SubCode_RVCCTRL_RVCActiveStatus          0x00
#define Content_RVCCTRL_RVCActiveStatus_Inactive 0x00
#define Content_RVCCTRL_RVCActiveStatus_Active   0x01

#define SubCode_RVCCTRL_RVCConnectStatus         0x01
#define Content_RVCCTRL_RVCConnectStatus_OK      0x00
#define Content_RVCCTRL_RVCConnectStatus_Failed  0x01

typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte SubCode;					/* */
        Type_uByte Content;			/* 0x00 : RVC status inactive  0x01 : RVC status active*/
    }Signals;
}MSG_SOC_RVCCTL_CODE_TC_msgType;


#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IPC_ILLUMINATION;
        Type_uByte IHU_ILLUMINATION;
    }Signals;
//#ifndef _MCU_RH850
 //   __attribute__ ((packed))
//#endif
    
}MSG_DIDRET_ILLUMINATION_TC_msgType;

#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[3];
    struct
    {
        Type_uByte	Vehiche_speed_limit	        : 2;
        Type_uByte	Engine_coolant_level_low	: 2;
        Type_uByte	ECO_mode	                : 2;
        Type_uByte	Vacuum_tank_alarm	        : 2;

        Type_uByte	LDW	                        : 2;
        Type_uByte	Rear_left_seat_belt	        : 2;
        Type_uByte	Rear_middle_seat_belt	    : 2;
        Type_uByte	Rear_right_seat_belt	    : 2;
        
        Type_uByte	Low_oil_pressure	        : 1;
        Type_uByte	Hand_brake	                : 2;
        Type_uByte	Driver_seat_belt	        : 1;
        Type_uByte	Brake_fluid_low	            : 1;
        Type_uByte	Steering_wheel_ICM_button	: 1;
        Type_uByte  reserved                    : 2;

    }Signals;
//#ifndef _MCU_RH850
   // __attribute__ ((packed))
//#endif
}MSG_DIDRET_INPUTSTATUS_TC_msgType;

#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte	audio_index;
        Type_uByte	audio_status;
    }Signals;
//#ifndef _MCU_RH850
   // __attribute__ ((packed))
//#endif
}MSG_SOC_AUDIO_msgType;

typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte	currentPage : 8;
        Type_uByte	currentCarInfoPage : 8;
    }Signals;
}MSG_SOC_LAST_SOURCE_REQ_msgType;

typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte	OilPressureLowWarning : 1;
        Type_uByte	Reversed : 7;
    }Signals;
}MSG_SOC_OIL_PRESSURE_REQ_msgType;

typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte	RestFactorySetting : 1;
        Type_uByte	Reversed : 7;
    }Signals;
}MSG_SOC_REST_FACTORY_REQ_msgType;

typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte	CFG_EPB_Write : 1;
        Type_uByte	Reversed : 7;
    }Signals;
}MSG_SOC_CFG_EPB_REQ_msgType;
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif

typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IPC_LCD_COM_ERR     : 1;
        Type_uByte IHU_LCD_COM_ERR     : 1;
        Type_uByte TUNER_IC_R_W_ERR    : 1;
        Type_uByte AMPLIFIER_R_W_ERR   : 1;
        Type_uByte SPKERS_AMPLIFIER_ERR: 1;
        Type_uByte reserved0           : 3;
    }Signals;
//#ifndef _MCU_RH850
    //__attribute__ ((packed))
//#endif
}MSG_SYS_LCD_COM_ERR_TC_msgType;	//DTC

typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte BCM_VehSt_Val : 8;
    }Signals;
}MSG_SOC_SEND_BCM_VehSt_msgType;

typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte HU_SVSActReqFromHU_Val : 8;
    }Signals;
}MSG_SOC_SEND_HU_SVSActReqFromHU_msgType;

typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_3D_SVS_ReqFromHU_VAL : 16;
    }Signals;
}MSG_SOC_SEND_HU_3D_SVS_ReqFromHU_msgType;

typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_SVSManVidSetupReqFromHU_Val : 16;
    }Signals;
}MSG_SOC_HU_SVSManVidSetupReqFromHU_msgType;

typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uWord HU_3D_SVS_ViewChgReqFromHU_Val : 32;
    }Signals;
}MSG_HU_3D_SVS_ViewChgReqFromHU_msgType;
typedef union
{
    Type_uByte _C[8];
    struct
    {
        Type_uByte HU_TouchEveType : 2;
	 Type_uHWord HU_TouchXCoor:11;
	 Type_uHWord HU_TouchYCoor:11;
	 Type_uByte HU_TouchInfo_RollgCntr:4;
	 Type_uByte HU_TouchInfo_Chks:8;		
    }Signals;
}MSG_SOC_HU_TouchInfo_msgType;
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_PrkgPDCMuteSwt_Val : 16;
    }Signals;
}MSG_SOC_HU_PrkgPDCMuteSwt_msgType;

typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_SVS_Transparent_Model_ReqFromHU : 16;
    }Signals;
}MSG_HU_SVS_Transparent_Model_ReqFromHU_msgType;

typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_SVS_Guidance_Line_ReqFromHU : 16;
    }Signals;
}MSG_HU_SVS_Guidance_Line_ReqFromHU_msgType;
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_SVSObjOverlay : 16;
    }Signals;
}MSG_SOC_HU_SVSObjOverlay_msgType;
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uHWord HU_SVSAutoViewSwitchModeReqFromHU : 16;
    }Signals;
}MSG_HU_SVSAutoViewSwitchModeReqFromHU_msgType;
/*
 * SOC get EEPROM type message union/struct define; used by cluster && SOC::HMI
 */
/*TODO : confirm the data info,include setting info stored in EEPROM*/
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[19];
    struct
    {
        Type_uByte IPC_BackLightLevelDaytime;
        Type_uByte IPC_BackLightLevelNight;
	Type_uByte IHU_BackLightLevel;
	Type_uByte IPC_BackLightLevel;	
	Type_uByte Passenger_BackLightLevel;
        Type_uByte IHU_BackLightLevelDaytime;
        Type_uByte IHU_BackLightLevelNight;
	Type_uByte BackLightingLuminance;
        Type_uByte Diag_flag        : 4;    /*backlight diag adjust flag. 0x0 : diag adjust not active. 0x1 : IHU backlight diag adjust 0x02 : IPC backlight diag adjust 0x3 diag function exit*/
        Type_uByte LanguageSet      : 4;    /*0x00 chianese 0x01 english  */
        Type_uByte IPC_DiagAdjustValue;
        Type_uByte IHU_DiagAdjustValue;
        Type_uByte SPDLMTPA_SATUS;          /*0 off,can not turn on;1 on ;2 off,can turn on*/
        Type_uByte SPDLMTPA_SETPOINT;
        Type_uByte T1C_M36T_DEFINE;
        Type_uByte CAR_SET_ASSIST_LINE  : 1;        /*car assist line on/off switch 0x00:off 0x01:on*/
        Type_uByte CAR_SET_SIA_SWITCH   : 1;        /*car SIA info on/off switch 0x00:off 0x01:on*/
        Type_uByte AudioVolume          : 4;        /*TODO : confirm the volume define according to IHU setting*/
        Type_uByte reserved_bit         : 2;
        Type_uByte u8ThemeSwitch;		// 1 Byte
        Type_uByte u8LastMenu;
	Type_uByte aubDiagOdoClearTimes;
	Type_uByte FatigueSensitivity:1;
	Type_uByte DistractionSensitivity:1;
    } Signals;
//#ifndef _MCU_RH850
   // __attribute__ ((packed))
//#endif
   
}_c_MSG_EEPROM_0_msgType;

/*confirm the data info,include calibration info stored in EEPROM*/
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    struct
    {
        Type_uByte	CFG_Transmission	:2;	
        Type_uByte	CFG_EPB	              :1;
        Type_uByte	CFG_TPMS			:1;
        Type_uByte	CFG_Engine			:2;
        Type_uByte	CFG_PEPS			:1;
        Type_uByte	CFG_ESP			:1;

        Type_uByte	CFG_Driver_position	:1;
        Type_uByte	CFG_Cruise			:2;
        Type_uByte	CFG_Voltage_Display:1;
        Type_uByte	CFG_Multi_media	:2;
        Type_uByte	CFG_Glow			:1;
        Type_uByte	CFG_Rear_fog		:1;

        Type_uByte	CFG_Boot_animation	:2;
        Type_uByte	CFG_WaterInfuel		:1;
        Type_uByte	CFG_OverspeedEn	:2;
        Type_uByte	CFG_Clock			:2;
        Type_uByte	CFG_Fuel_tank		:1;

        Type_uByte	CFG_AutoLight		:1;
        Type_uByte	CFG_Maintenance	:1;
        Type_uByte	CFG_EPS			:1;
        Type_uByte	CFG_Language		:5;

        Type_uByte	CFG_Airbag						:1;
        Type_uByte	CFG_FATIGUE_DRIVING			:1;
        Type_uByte	CFG_Wheel_Deviation				:1;      
        Type_uByte	CFG_Overspeed_switch			:1;      
        Type_uByte	CFG_After_reset_info_display	:1;      
        Type_uByte	CFG_After_start_info_display		:1;      
        Type_uByte	CFG_SCR						:1;      
        Type_uByte	CFG_Mile_unit					:1;      

        Type_uByte	CFG_OverspeedSet	:8;
		
        Type_uByte	CFG_PDC	:2;
        Type_uByte	CFG_LCA	:1;
        Type_uByte	CFG_LDW	:1;
        Type_uByte	CFG_LKA	:1;
        Type_uByte	CFG_FCM	:1;
        Type_uByte	CFG_AEB	:1;
        Type_uByte	CFG_TSR	:1;

        Type_uByte	CFG_Seatbelt	:3;
        Type_uByte	CFG_Seat_layout	:2;
        Type_uByte	CFG_AWD	:2;
        Type_uByte	CFG_Cruise_speed_display	:1;

        Type_uByte  CFG_Navi_display    : 1;
        Type_uByte  CFG_Media_display   : 1;
        Type_uByte  CFG_Call_display    : 1;
        Type_uByte  CFG_Outside_Temp   : 1;
        Type_uByte  CFG_DPF    : 1;
        Type_uByte  CFG_Theme   : 1;
        Type_uByte  CFG_IHC    : 1;
        Type_uByte  CFG_TimeFormat   : 1;

        Type_uByte  CFG_ESCL   : 1;
        Type_uByte  Reserved   : 7;

	Type_uByte Theme_Setting:2;
	Type_uByte  unused   : 6;
	
	Type_uByte SPEAKERS:8;
	Type_uByte MICROPHONE:8;
	Type_uByte VEHICLEBACKUPCAMERA:8;
	Type_uByte PANORAMICVISION:8;
	
	Type_uByte Model:8;
		
	Type_uByte PDCObstclWarning:4;
		
    }Signals;
//#ifndef _MCU_RH850
//    __attribute__ ((packed))
//#endif
    
    Type_uByte _C[10];
}_c_MSG_EEPROM_1_msgType;

/*include alarm value info calculate by clslib */
typedef union
{
    Type_uByte _C[10];
    struct
    {
        Type_uHWord CLS_FUEL_LOW_BAR;
        Type_uHWord CLS_FUEL_LOW_RELEASE_BAR;
        Type_uHWord CLS_COOLANT_HIGH_BAR;
        Type_uHWord CLS_COOLANT_HIGH_RELEASE_BAR;
		Type_uByte CLS_LAST_SOURCE_CURRENT_REQ_BAR : 8;
		Type_uByte CLS_LAST_SOURCE_CARINFO_REQ_BAR2 :8;
    }Signals;
}_c_MSG_EEPROM_2_msgType;

#define RESISTANCE_TEST_RESULT_OK    0x00
#define RESISTANCE_TEST_RESULT_FALSE 0x01

#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[10];
    struct
    {
        Type_uWord CFG_IFE_Range1:10;
        Type_uWord CFG_IFE_Range2:10;
        Type_uByte CFG_DTE_Fuel_Consumption_Idle:1;
        Type_uByte CFG_DTE_Display_Direction:1;
        Type_uByte Reserved0:1;
        Type_uByte Reserved1:1;
		
        Type_uByte CFG_AFE_Init : 8;
		
        Type_uHWord CFG_AFE_Range : 10;
		
        Type_uByte CFG_DTE_Fuel_calculate : 6;
		
        Type_uByte CFG_Current_Fuel_Consumption_Distance : 8;
		
        Type_uByte CFG_MaxFuelConsumption : 8;
		
        Type_uHWord CFG_Mainteance_distance : 16;
    } Signals;
//#ifndef _MCU_RH850
  //  __attribute__ ((packed))
//#endif
   
}_c_MSG_EEPROM_3_msgType;

/* Ref. 0009 */
typedef union
{
    Type_uByte _C[26];
    struct
    {
        Type_uByte softVersionNum[19];
		Type_uByte HardVersionNum[6];
		Type_uByte unused0;
    }
    Signals;
}_c_MSG_EEPROM_4_msgType;

/*DID:6208 Buzzer test*/
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uHWord DID_NUMBER;         //DID number
        Type_uByte SUB_FUNCTION_CODE;   //sub function service
        Type_uByte CONTROLE_CODE;       //control code
    } Signals;
//#ifndef _MCU_RH850
  //  __attribute__ ((packed))
//#endif
   
}_c_MSG_DIDCTL_0_msgType;

#if 0
/*DID:6209 Gauge position*/
#ifdef _MCU_RH850
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte SUB_FUNCTION_CODE;   //sub function service
        Type_uByte CONTROLE_CODE;       //control code
    }
#ifndef _MCU_RH850
    __attribute__ ((packed))
#endif
    Signals;
}_c_MSG_DIDCTL_1_msgType;

/*DID:620A LCD test*/
#ifdef _MCU_RH850
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte SUB_FUNCTION_CODE;   //sub function service
        Type_uByte CONTROLE_CODE;       //control code
    }
#ifndef _MCU_RH850
    __attribute__ ((packed))
#endif
    Signals;
}_c_MSG_DIDCTL_2_msgType;

/*DID:620B Digital output*/
#ifdef _MCU_RH850
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte SUB_FUNCTION_CODE;   //sub function service
        Type_uByte CONTROLE_CODE;       //control code
    }
#ifndef _MCU_RH850
    __attribute__ ((packed))
#endif
    Signals;
}_c_MSG_DIDCTL_3_msgType;
#endif

/*
 * SOC get MCU type message union/struct define; used by cluster && SOC::HMI
 */
/* Name: _c_MSG_MCU_0_msgType,    RPC MSG ID:   0x20 */
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    Type_uByte _C[10];
    struct
    {  
        Type_uHWord MCU_VEHICLE_SPEED;
        Type_uHWord MCU_ENGINE_SPEED;
        Type_uHWord MCU_FUEL_LEVEL;
        Type_uHWord MCU_ENGINE_TEMPERATURE; 
	 Type_uByte MCU_BATT_VAL;
	 Type_uByte	MCU_Interface_Disp:2;
	 Type_uByte unused0;
    }Signals;
}_c_MSG_MCU_0_msgType;

/* Name: _c_MSG_MCU_1_msgType,    RPC MSG ID:   0x21 */
#if 0
#pragma pack 1
#endif
typedef union
{
	Type_uByte _C[57];
	struct
	{  
		Type_uWord MCU_RANGE   : 32;

		Type_uHWord MCU_INSTAT_FC   : 16;
		Type_uHWord MCU_ODO_SYNC_STATUS     : 4;        /* 0 OK, 1 NOT OK */
		Type_uHWord MCU_ODO_EEPGET     : 4;
		Type_uHWord MCU_INSTAT_FC_UNIT      : 4;
		Type_uByte MCU_ODO_CLR_ENABLE		:4;

		Type_uWord MCU_ODO      : 32;		

		Type_uWord MCU_TRIP_A      : 24;
		Type_uByte  unused0:8;

		Type_uWord MCU_TRIP_B      : 24;
		Type_uByte  unused1:8;

		Type_uWord MCU_AVERAGE_SPEED_A      : 16;
		Type_uWord MCU_AVERAGE_SPEED_B        : 16;

		Type_uWord MCU_DRIVING_TIME_A        : 32;
		Type_uWord MCU_DRIVING_TIME_B        : 32;

		Type_uHWord MCU_AVERAGE_FC_A      : 16;
		Type_uHWord MCU_AVERAGE_FC_B      : 16;

		Type_uWord MCU_REMAINING_MAINTENANCE  : 32;

		Type_uByte  MCU_AMBIENT_TEMPERATURE : 8;
		Type_uByte BattVoltage      : 8;

		Type_uHWord	TripBApc:16;
		Type_uHWord TripAApc:16;

		Type_uHWord	MCU_SinceLastChargeTime :16;
		Type_uWord    MCU_SinceLastChargeOdo    : 32;
		
		Type_uHWord	MCU_Recent100KmAPC :16;
		Type_uHWord	MCU_Recent1KmAPC :16;
		
		Type_uByte	MCU_Recent100KmAPCSts:1;
		Type_uByte	MCU_Recent1KmAPCSts:1;
		Type_uByte	unused2:6;
	} Signals;
}
_c_MSG_MCU_1_msgType;

/* Name: _c_MSG_MCU_3_msgType,    RPC MSG ID:   0x23 */
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union
{
    struct
    {  
        Type_uHWord MCU_CLOCK_YEAR        : 16;
        
        Type_uHWord MCU_CLOCK_MONTH       : 8;
        Type_uHWord MCU_CLOCK_DAY         : 8;
        
        Type_uHWord MCU_CLOCK_HOUR        : 8;
        Type_uHWord MCU_CLOCK_MINUTE      : 8;
        
        Type_uHWord MCU_CLOCK_SECOND      : 8;
        Type_uHWord MCU_CLOCK_TIME_FORMAT : 8;  /*0x0 : 24h ;0x1 : 12h*/
    }Signals;
//#ifndef _MCU_RH850
   // __attribute__ ((packed))
//#endif
}
_c_MSG_MCU_3_msgType;

/* Name: _c_MSG_MCU_2_msgType,    RPC MSG ID:   0x22 */
typedef union
{
    Type_uByte _C[1];
    struct
    {  
        Type_uByte MCU_Hand_brake_Pin6 : 1;
        Type_uByte MCU_Brake_fluid_Pin7   : 1;
        Type_uByte MCU_Charge_Indicator_Pin8  : 1;
        Type_uByte reserved                   : 5;
    }Signals;
}_c_MSG_MCU_2_msgType;

/* Name: _c_MSG_MCU_4_msgType,    RPC MSG ID:   0x24 */
typedef union
{
    Type_uByte _C[3];
    struct
    {  
        Type_uByte MCU_CLUSTER_HARDL_KEY_NUMBER         : 8;
        Type_uByte MCU_CLUSTER_HARDL_KEY_STATUS         : 8;

        Type_uByte MCU_CLUSTER_HARDKEY_DRIVER_MODE      : 2; /*0x00:driver mode button enable 0x01:driver mode button disable 0x02~03:reserved*/
        Type_uByte MCU_CLUSTER_HARDKEY_LDW_LKA_BUTTON   : 2; /*0x00:LD/LKA button enabale 0x01:LDW/LKA button disable 0x02~0x03:not use*/
        Type_uByte MCU_CLUSTER_HARDKEY_POWER            : 2; /*0x02:PowerKey out (Restart IHU) 0x03:PowerKey out off (Ignore)*/
        Type_uByte reserved : 2;
    }Signals;
}_c_MSG_MCU_4_msgType;

/* Name: _c_MSG_MCU_5_msgType,    RPC MSG ID:   0x25 */
#ifdef _DEBUG_SOC_PM_
#pragma pack 1
#endif
typedef union 
{
    Type_uByte _C[10];
    struct
    {
        Type_uHWord FuelLowWaring       :2;
        Type_uHWord CoolantTtState      :1;
        Type_uHWord CLS_FAD_WARNING     :1;     /*0 Not warning, 1 warning*/
        Type_uHWord CLS_SIA_STATUS      :2;     /*0:SNA 1:SIA_SOON 2:SIA_NOW*/
        Type_uHWord CLS_SIA_DISTSTATUS  :2;     /*new add for hmi 2019.1.17*/

        Type_uHWord CLS_SIA_DAYSTATUS   :2;     /*new add for hmi 2019.1.17*/
        Type_uHWord CoolantPopState   :2;  
	 Type_uHWord CLS_TT_BATT_COLOR :2;	/*0:red ,1:yellow ,2:green*/
        Type_uHWord reserved            :2; 

        Type_uWord CLS_SIA_LASTODO      :24;
        Type_uWord CLS_SIA_INVLDAY      :8;
        
        Type_uWord CLS_SIA_LASTDATE     :16;
        Type_uWord CLS_SIA_INVLDIST     :16;
    } Signals;

//#ifndef _MCU_RH850
  //  __attribute__ ((packed))
//#endif
   }_c_MSG_MCU_5_msgType;

/*add end*/

/* Name: _c_MSG_MCU_6_msgType,    RPC MSG ID:   0x26 */
typedef union
{
    Type_uByte _C[2];
    struct
    {  
        Type_uHWord StartLightCnt : 16;
    }Signals;
}_c_MSG_MCU_6_msgType;

/*
 *CAN message struct define
 */
 
/* Name: _c_ICGM_EMS_210h_IP_msgType,    RPC MSG ID:   0x40 */
typedef union
{
    Type_uByte _C[3];
    struct
    {
        Type_uByte IsTimeout : 1;
	    Type_uByte EngineRunActive : 1;
        Type_uByte CruiseControlActive : 1;
        Type_uByte AcceleratorPedalPositionValidity : 1;
        Type_uByte AcceleratoreffectivepositionValidity : 1;	
        Type_uByte CruiseControlStandBy : 1; 
        Type_uByte unused0 : 2;
		
        Type_uByte AcceleratorPedalPosition : 8;  
		
        Type_uByte Acceleratoreffectiveposition : 8;
    } Signals;
}_c_ICGM_EMS_210h_IP_msgType;

/* Name: _c_ICGM_EMS_220h_IP_msgType,    RPC MSG ID:   0x41 */
typedef union
{
    Type_uByte _C[3];
    struct
    {		
        Type_uByte IsTimeout : 1;
        Type_uByte unused0 : 7;
		
        Type_uHWord EngineSpeed : 16;
    } Signals;
}_c_ICGM_EMS_220h_IP_msgType;

/* Name: _c_ICGM_EMS_223h_IP_msgType,    RPC MSG ID:   0x42 */
typedef union
{
    Type_uByte _C[3];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte CoolingFANlevelFeedback : 4;
        Type_uByte unused0 : 3;
		
        Type_uByte EngineCoolantTemperature : 8;
		
        Type_uByte CruiseTargetSpeed : 8;
    } Signals;
}_c_ICGM_EMS_223h_IP_msgType;

/* Name: _c_ICGM_EMS_227h_IP_msgType,    RPC MSG ID:   0x43 */
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte DPFWarnLamp : 2;	
        Type_uByte unused0 : 5;
		
        Type_uByte DpfWarningInf : 3;
        Type_uByte RGNinactivereason : 5;
		
        Type_uByte RGNpercent : 8;

        Type_uByte EnCltLvlWrnngSts : 1;
        Type_uByte unused1 : 7;	
    } Signals;
}_c_ICGM_EMS_227h_IP_msgType;

/* Name: _c_ICGM_EMS_322h_IP_msgType,    RPC MSG ID:   0x44 */
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte unused0 : 7;
		
        Type_uByte EngineMILOn : 1;	
        Type_uByte EngineFault : 1;		
        Type_uByte WaterInFuelIndicator : 1;
        Type_uByte GlowTimeIndicator : 1;
        Type_uByte ChargingIndicator : 1;
        Type_uByte EngineOilPressureLowIndicator : 1;
        Type_uByte FuelConsumptionValidity : 1;
        Type_uByte EngineOilPressureLowIndicatorValidity : 1;
		
        Type_uHWord FuelConsumption : 16;
    } Signals;
}_c_ICGM_EMS_322h_IP_msgType;

/* Name: _c_ICGM_EMS_323h_IP_msgType,    RPC MSG ID:   0x45 */
typedef union
{
    Type_uByte _C[7];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte AdBlueMessageCounter : 1;/*error = 1*/
        Type_uByte AdBlueChecksum : 1;/*error = 1*/
        Type_uByte AdBlueLevelWarning_LD : 3;
        Type_uByte AdBlueLamp : 2;
		
        Type_uHWord AdBlueRange : 16;	
		
        Type_uByte AdBlueLevel : 8;
		
		
        Type_uByte AdBlueRangeValidity : 1;
        Type_uByte AdBlueSystemError_LD : 4;
        Type_uByte AdBlueLevelWarning_HD : 3;

        Type_uByte AdBlueSystemError_HD : 3;
        Type_uByte AdBlueSystemErrorLevel_LD : 2;
        Type_uByte AdBlueSystemErrorLevel_HD : 3;
		
        Type_uHWord AdBlueLevelValidity : 1;
        Type_uByte unused0 : 7;
    } Signals;
}_c_ICGM_EMS_323h_IP_msgType;

/* Name: _c_ICGM_EPS_335h_IP_msgType,    RPC MSG ID:   0x46 */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte EPSFail_WL : 1;	
        Type_uByte EPSMessageCounter : 4;
        Type_uByte unused0 : 2;
		
        Type_uByte EPSChecksum : 8;
		
    } Signals;
}_c_ICGM_EPS_335h_IP_msgType;

/* Name: _c_ICGM_ESC_1E9h_IP_msgType,    RPC MSG ID:   0x47 */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte HDCControlStatus : 2;	
        Type_uByte ESPActive : 1;
        Type_uByte ESPOffLampStatus : 1;
        Type_uByte ESPFault : 1;
        Type_uByte ESCFunctionFeedback : 1;
        Type_uHWord AvhAvaliable : 1;
		
        Type_uByte ESCFactoryDefaultSettingFinished : 2;	
        Type_uByte AvhActive : 1;
        Type_uByte AvhStandy : 1;
        Type_uByte unused0 : 4;
    } Signals;
}_c_ICGM_ESC_1E9h_IP_msgType;

/* Name: _c_ICGM_ESC_245h_IP_msgType,    RPC MSG ID:   0x48 */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte EPBMessageCounter : 1;
        Type_uByte EPBChecksum : 1;
        Type_uByte Failurelamp : 2;
        Type_uByte unused0 : 3;
		
        Type_uByte TXTmessage : 4;	
        Type_uByte Parkinglamp : 2;
        Type_uByte unused1 : 2;
    } Signals;
}_c_ICGM_ESC_245h_IP_msgType;

/* Name: _c_ICGM_ESC_269h_IP_msgType,    RPC MSG ID:   0x49 */
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte ESCMessageCounter : 4;
        Type_uByte ABSFault : 1;
        Type_uByte EBDFault : 1;
        Type_uByte VehicleSpeedStatus : 1;
		
        Type_uByte ESCCheckSum : 8;
		
        Type_uHWord VehicleSpeed : 13;
        Type_uByte unused0 : 3;
		
    } Signals;
}_c_ICGM_ESC_269h_IP_msgType;

/* Name: _c_ICGM_HVAC_510h_IP_msgType,    RPC MSG ID:   0x4A */
typedef union
{
    Type_uByte _C[6];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte HVACCycleMode : 2;
        Type_uByte HVACFrontDefrostStatus : 1;
        Type_uByte HVACFrontDefrostStatusValidity : 1;
        Type_uByte HVACRearDefrostStatus : 1;
        Type_uByte HVACRearDefrostStatusValidity : 1;
        Type_uByte HVACAutoIndicationStatus : 1;
		
        Type_uByte HVACAirVolume : 4;	
        Type_uByte HVACMode : 4;
		
        Type_uByte HVACSetTemperature : 8;
		
        Type_uByte HVACEnvirmentTemperature : 8;
		
        Type_uByte EvaporatorTemperature : 8;
		
        Type_uByte HVACAutoIndicationStatusValidity : 1;	
        Type_uByte HVACAirClearingIndicationStatus : 1;
        Type_uByte HVACAirClearingIndicationStatusValidity : 1;
        Type_uByte HVACEnvirmentTemperatureMask : 1;
        Type_uByte HVACPowerStatus : 1;
        Type_uByte HVACOnRequestIndication : 1;
        Type_uByte unused0 : 2;
		
    } Signals;
}_c_ICGM_HVAC_510h_IP_msgType;

/* Name: _c_ICGM_IBDU_281h_IP_msgType,    RPC MSG ID:   0x4B */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte SystemPowerMode : 2;	
        Type_uByte SystemPowerModeValidity : 1;		
        Type_uByte TurnLampLeftStatus : 1;		
        Type_uByte TurnLampRightStatus : 1;
        Type_uByte IMMOIndicator : 2;

        Type_uByte ReverseGear : 1;
        Type_uByte DriverDoorLockStatus : 2;
        Type_uByte PassengerDoorLockStatus : 2;		
        Type_uByte HoodOpenStatus : 1;
        Type_uByte HoodOpenStatusValidity : 1;
        Type_uByte unused0 : 1;
		
    } Signals;
}_c_ICGM_IBDU_281h_IP_msgType;

/* Name: _c_ICGM_IBDU_310h_IP_msgType,    RPC MSG ID:   0x4C */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte iBDUToIPKAlarm : 4;	
        Type_uByte TransShiftLevPositionForP : 1;
		Type_uByte PEPS_IGN1FailureWarning : 1;
		Type_uByte PEPS_SSB_Failure_warning : 1;
		
    } Signals;
}_c_ICGM_IBDU_310h_IP_msgType;


/* Name: _c_ICGM_IBDU_330h_IP_msgType,    RPC MSG ID:   0x4D */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte DriveMode : 3;
        Type_uByte unused0 : 4;
		
    } Signals;
}_c_ICGM_IBDU_330h_IP_msgType;

/* Name: _c_ICGM_IBDU_348h_IP_msgType,    RPC MSG ID:   0x4E */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte AlarmTriggeredIndicate : 1;	
        Type_uByte AWDIndicationReq : 1;	
        Type_uByte SWTODDrivingModReqValid : 1;	
        Type_uByte SWTODDrivingModReq : 4;	
				
    } Signals;
}_c_ICGM_IBDU_348h_IP_msgType;


/* Name: _c_ICGM_IBDU_373h_IP_msgType,    RPC MSG ID:   0x4F */
typedef union
{
    Type_uByte _C[7];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte RemoteVehicleStartStatus : 1;
		Type_uByte FrontWiperOperationStatus: 3;
        Type_uByte unused0 : 3;
		
        Type_uWord ODOofiBDU : 24;	
		
        Type_uWord SIA_ODOofiBDU : 24;
		
		
    } Signals;
}_c_ICGM_IBDU_373h_IP_msgType;

/* Name: _c_ICGM_IBDU_375h_IP_msgType,    RPC MSG ID:   0x50 */
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte PositionLampStatus : 1;	
        Type_uByte DippedBeamStatus : 1;		
        Type_uByte MainBeamStatus : 1;	
        Type_uByte FrontFogLightStatus : 1;
        Type_uByte RearFogLightStatus : 1;
        Type_uByte DoorAjarDriverStatus : 1;
        Type_uByte DoorAjarPassengerStatus : 1;
		
        Type_uByte DoorAjarRightRearStatus : 1;
        Type_uByte DoorAjarLeftRearStatus : 1;
        Type_uByte DoorAjarTailgateStatus : 1;
        Type_uByte KeyInWarning : 1;
        Type_uByte PositionLampNotOFFWaring : 1;
        Type_uByte LightAutoControl : 1;
        Type_uByte BackLightingStatus : 1;
        Type_uByte DaytimeRunningLampStatus : 1;	
		

        Type_uByte BackLightingLuminance : 8;

        Type_uByte SpeedWiperConfig : 1;
        Type_uByte ParkGearUnlockingFunctionStatus : 1;
        Type_uByte BatteryReplaceReminder : 1;
        Type_uByte unused0 : 5;
		
    } Signals;
}_c_ICGM_IBDU_375h_IP_msgType;

/* Name: _c_ICGM_IBDU_379h_IP_msgType,    RPC MSG ID:   0x51 */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte DDDDrowsyWarning : 2;	
        Type_uByte DDDDriveTimeWarning : 1;		
        Type_uByte DDDSwitchStatusFeedback : 1;		
        Type_uByte DirectionIndicationSwitchStatus : 2;
        Type_uByte FLWdwCompleteOpen : 1;
		
        Type_uByte FLWdwCompleteClose : 1;	
        Type_uByte LogisticsTransportMode : 2;
        Type_uByte unused0 : 5;
		
    } Signals;
}_c_ICGM_IBDU_379h_IP_msgType;

/* Name: _c_ICGM_IBDU_5E0h_IP_msgType,    RPC MSG ID:   0x52 */
typedef union
{
    Type_uByte _C[9];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte unused0 : 7;
		
        Type_uByte LFPressure : 8;
		
        Type_uByte RFPressure : 8;
		
        Type_uByte RRPressure : 8;
		
        Type_uByte LRPressure : 8;

        Type_uByte LFTemperature : 8;
		
        Type_uByte RFTemperature : 8;

        Type_uByte RRTemperature : 8;

        Type_uByte LRTemperature : 8;
		
	} Signals;
}_c_ICGM_IBDU_5E0h_IP_msgType;

/* Name: _c_ICGM_IBDU_5E1h_IP_msgType,    RPC MSG ID:   0x53 */
typedef union
{
    Type_uByte _C[3];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte TPMSLampStatus : 2;
        Type_uByte TPMSSystemStatus : 2;
        Type_uByte unused0 : 3;
		
        Type_uByte LFPressureWarning : 4;	
        Type_uByte RFPressureWarning : 4;
		
        Type_uByte RRPressureWarning : 4;	
        Type_uByte LRPressureWarning : 4;
		
		
    } Signals;
}_c_ICGM_IBDU_5E1h_IP_msgType;



/* Name: _c_ICGM_PDC_289h_IP_msgType,    RPC MSG ID:   0x54 */
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte PDCSensorStatus_9 : 1;
        Type_uByte PDCSensorStatus_10 : 1;
        Type_uByte AudibleBeepRate : 4;
        Type_uByte RadarWorkSts : 1;

        Type_uByte RadarSensorDistance_9 : 8;	
		
        Type_uByte RadarSensorDistance_10 : 8;
		
        Type_uByte PDCRearObjectStatus_9 : 2;
        Type_uByte PDCRearObjectStatus_10 : 2;
        Type_uByte unused0 : 4;
		
    } Signals;
}_c_ICGM_PDC_289h_IP_msgType;

/* Name: _c_ICGM_SRS_355h_IP_msgType,    RPC MSG ID:   0x55 */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte RollingCounter : 1;
        Type_uByte SRSCheckSum : 1;
        Type_uByte AirbagSystemError : 1;
        Type_uByte SeatBeltWarningRL : 2;
        Type_uByte SeatBeltWarningRM : 2;
		
        Type_uByte SeatBeltWarningRR : 2;
		Type_uByte PassengerSeatBeltStatus:1;
		Type_uByte SeatBeltWarningDrivertoIPK:2;
		Type_uByte SeatBeltWarningPassengertoIPK:2;
        Type_uByte unused0 : 1;
		
    } Signals;
}_c_ICGM_SRS_355h_IP_msgType;

/* Name: _c_ICGM_TCCU_328h_IP_msgType,    RPC MSG ID:   0x56 */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte TCCUDiagnosticLampRequest : 1;	
        Type_uByte TCCULamp2WD : 2;
        Type_uByte TCCULamp4WDLock : 2;
        Type_uByte TCCULamp4WDLow : 2;
		
        Type_uByte TCCUShiftingTimeout : 2;		
        Type_uByte TCCUSystemOperatingMode : 4;
        Type_uByte TCCUModeChangeInProgress : 1;
        Type_uByte TCCUCouplingThermalFailsafe : 1;
		
    } Signals;
}_c_ICGM_TCCU_328h_IP_msgType;

/* Name: _c_ICGM_TCU_1F5h_IP_msgType,    RPC MSG ID:   0x57 */
typedef union
{
    Type_uByte _C[5];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte TCUDriverWarnings_ZF_1_0 : 1;
        Type_uByte TCUDriverWarnings_ZF_1_1 : 1;
        Type_uByte TCUDriverWarnings_ZF_1_2 : 1;
        Type_uByte TCUDriverWarnings_ZF_1_3 : 1;
        Type_uByte TransShiftLeverPositionValidity_ZF : 1;
        Type_uByte TCUDesireGearState : 1;
        Type_uByte unused0 : 1;
		
        Type_uByte TCUDriverWarnings_ZF_2_0 : 1;	
        Type_uByte TCUDriverWarnings_ZF_2_1 : 1;
        Type_uByte TCUDriverWarnings_ZF_2_2 : 1;
        Type_uByte TCUDriverWarnings_ZF_2_3 : 1;
        Type_uByte TransShiftLeverPosition : 4;
			
        Type_uByte TCUDriverWarnings_ZF_0 : 1;
        Type_uByte TCUDriverWarnings_ZF_1 : 1;
        Type_uByte TCUDriverWarnings_ZF_2 : 1;
        Type_uByte TCUDriverWarnings_ZF_3 : 1;
        Type_uByte TCUDriverWarnings_ZF_4 : 1;
        Type_uByte TCUDriverWarnings_ZF_5 : 1;
        Type_uByte TCUDriverWarnings_ZF_6 : 1;
        Type_uByte TCUDriverWarnings_ZF_7 : 1;
		
        Type_uByte DisplayGear_ZF : 4;
        Type_uByte TCUMessageCounter : 4;
		
        Type_uByte TCUChecksum : 8;
    } Signals;
}_c_ICGM_TCU_1F5h_IP_msgType;

/* Name: _c_ICGM_TCU_1F5h_IP_msgType,    RPC MSG ID:   0x57 */
typedef union
{
    Type_uByte _C[6];
    struct
    {
		Type_uByte AutoTransCommandedGear : 4;
		Type_uByte TransEstimatedGear : 4;
		
		Type_uByte DriverShiftControlTargetGear : 4;
		Type_uByte TransShiftLeverPosition : 4;
		
		Type_uByte TransRangeInhibitStatus : 3;
		Type_uByte TransTapUpDownModeStatus : 2;
		Type_uByte TransEngagedState : 2;
		Type_uByte IsTimeout : 1;
		
		Type_uByte TransEngagedStateValidity : 1;
		Type_uByte TransEstimatedGearValidity : 1;
		Type_uByte TransShiftLeverPositionValidity : 1;
		Type_uByte DriverShiftControlRequestDeniedIndicationOn : 1;
		Type_uByte TransFluidPressurePresent : 1;
		Type_uByte ShiftInProgress : 1;
		Type_uByte ShiftInProgressValidity : 1;
		Type_uByte TCMAvaliable : 1;
		
		Type_uByte TCUSystemOperatingMode : 3;
		Type_uByte TCUSystemOperatingModeValid : 1;
		Type_uByte TCUMessageCounter : 4;
		
		Type_uByte TCUChecksum : 8;

    } Signals;
}_c_ICGM_TCU_1F5h_Turbocharging_IP_msgType;


/* Name: _c_ICGM_TCU_6F1h_IP_msgType,    RPC MSG ID:   */
typedef union
{
    Type_uByte _C[5];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte IPKDisplayedFuelWarning : 1;
        Type_uByte IPKDisplayedEMSWarning : 1;
        Type_uByte IPKDisplayedEPSWarning : 1;
        Type_uByte IPKDisplayedAlternatorWarning : 1;
        Type_uByte IPKDisplayedOilPressureLowWarning : 1;
        Type_uByte IPKDisplayedAFSSystemWarning : 1;
        Type_uByte IPKDisplayedCoolantTemperatureWarning : 1;
		
        Type_uByte IPKDisplayedSecurityKeyBatteryLowWarning : 1;	
        Type_uByte IPKDisplayedWasherFluidLowWarning : 1;
        Type_uByte IPKDisplayTPMSWarning : 1;
        Type_uByte IPKOverSpeedFunctionStatus : 1;
		Type_uByte IPKDisplayDPFStatus : 2;
        Type_uByte unused0 : 2;
			
        Type_uByte IPKOverSpeedThreshholdValue : 8;
		
        Type_uByte IPKLanguageFeadback : 7;
		Type_uByte unused1 : 1;
		
        Type_uByte FuelLvlPcnt : 8;
		
        

    } Signals;
}_c_ICGM_TCU_6F1h_IP_msgType;

/* Name: _c_iCGM_ESCL_261h_IP_msgType,     */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte ClutchBottomSwitch : 2;	
        Type_uByte unused0 : 5;
		
    } Signals;
}_c_ICGM_ESCL_261h_IP_msgType;

/* Name: _c_iCGM_ESCL_279h_IP_msgType,     */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte ESCL_Warning_to_IPK : 3;	
        Type_uByte unused0 : 4;
		
    } Signals;
}_c_ICGM_ESCL_279h_IP_msgType;

/* Name: _c_ICGM_SAS_266h_IP_msgType,     */
typedef union
{
    Type_uByte _C[4];
    struct
    {
        Type_uHWord SteeringAngle : 16;
		Type_uByte SteeringSpeed;
		Type_uByte SASCalibrationStatus : 1;
		Type_uByte IsTimeout : 1;
        Type_uByte unused0 : 6;
    } Signals;
}_c_ICGM_SAS_266h_IP_msgType;
/* Name: _c_iCGM_iBDU_581h_IP_msgType,     */
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte IsTimeout : 1;
		Type_uByte unused0 : 7;
        Type_uByte BackLightingTargetValue : 5;
		Type_uByte BrightnessStatus : 3;       		
    } Signals;
}_c_iCGM_iBDU_581h_IP_msgType;
/* Name: _c_GET_HMI_DIDS_STATUS_msgType,     */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IoDiagDid;	
		
    } Signals;
}_c_GET_HMI_DIDS_STATUS_msgType;

/* Name: _c_DIDS_HEX_D403h_IP_msgType,     */
typedef union
{
    Type_uByte _C[3];
    struct
    {	
		Type_uByte PDCsts : 1;
		Type_uByte SeatBelt : 1;
		Type_uByte DoorTone : 1;
		Type_uByte unused0 : 1;
		Type_uByte HandBrakeWarning : 1;
		Type_uByte OverSpeedAlarm : 1;
		Type_uByte KeyInWarning : 1;
		Type_uByte Headlamp_Reminder : 1;

		Type_uByte LCD_Warning_Reminder : 1;
		Type_uByte Doubleflashlamprisk : 1;
		Type_uByte SCRWarning : 1;
		Type_uByte DPFsts : 1;
		Type_uByte Lane_Departure_Warning : 1;
		Type_uByte SCRsts : 1;
		Type_uByte ADAS_request_overcontrol : 1;
		Type_uByte FCA_Imminent_Alert : 1;
		
		Type_uByte Mode : 2;
		Type_uByte unused1 : 6;

	} Signals;
}_c_DIDS_HEX_D403h_IP_msgType;
/* Name: _c_DIDS_HEX_D404h_IP_msgType,	   */
typedef union
{
    Type_uByte _C[2];
    struct
    {	

		Type_uByte unused0 : 4;
		Type_uByte Fatigue_driving2 : 1;
		Type_uByte Fatigue_driving1 : 1;
		Type_uByte DPFWarning2 : 1;
		Type_uByte DPFWarning1 : 1;

		Type_uByte Mode : 2;
		Type_uByte unused1 : 6;

	} Signals;
}_c_DIDS_HEX_D404h_IP_msgType;


/* Name: _c_DIDS_HEX_D11Bh_IP_msgType,     */
typedef union
{
    Type_uByte _C[3];
    struct
    {
    	Type_uByte TurnLampLeftStatus : 1;
    	Type_uByte TurnLampRightStatus : 1;
		Type_uByte PositionLampStatus : 1;
		Type_uByte ABSFault : 1;
		Type_uByte unused0 : 1;
		Type_uByte RearFogLightStatus : 1;
		Type_uByte MainBeamStatus : 1;
        Type_uByte Reserved : 1;
		
		Type_uByte ESPOffLampStatus : 1;
		Type_uByte EBDFault : 1;
		Type_uByte EngineMILOn : 1;
		Type_uByte EngineCoolantTemperature : 1;
		Type_uByte FuelLevelLampStatus : 2;
		Type_uByte EngineOilPressurLow : 1;
		Type_uByte EngineFault : 1;
		
		Type_uByte Mode : 2;
		Type_uByte unused1 : 6;
		
    } Signals;
}_c_DIDS_HEX_D11Bh_IP_msgType;


/* Name: _c_DIDS_HEX_D11Ch_IP_msgType,     */
typedef union
{
    Type_uByte _C[3];
    struct
    {
    	Type_uByte ChargeLampStatus : 1;
    	Type_uByte BreakSyetermParking : 1;
    	Type_uByte unused0 : 1;
    	Type_uByte Resevrved : 1;
    	Type_uByte CruiseControlLampStatus : 2;
    	Type_uByte TPMSLampStatus : 2;
		
		Type_uByte IMMOindication : 2;//
		Type_uByte unused1 : 2;
		Type_uByte DriverSafetyBelt : 2;
		Type_uByte EPBSystemindication : 2;
		
		Type_uByte Mode : 2;
		Type_uByte unused2 : 6;
		
    } Signals;
}_c_DIDS_HEX_D11Ch_IP_msgType;
/* Name: _c_DIDS_HEX_D11Dh_IP_msgType,     */
typedef union
{
    Type_uByte _C[3];
    struct
    {
		Type_uByte EPBFault : 2;
		Type_uByte AutoholdSystem : 2;
		Type_uByte unused0 : 2;
		Type_uByte ESPwaringLamp : 2;

    	Type_uByte LdwWarning : 3;
    	Type_uByte TCCUFault : 1;
    	Type_uByte IHCsts : 2;
    	Type_uByte OverSpeedAlarm : 1;
    	Type_uByte WaterInfuel : 1;
		
		Type_uByte Mode : 2;
		Type_uByte unused2 : 6;
		
    } Signals;
}_c_DIDS_HEX_D11Dh_IP_msgType;
/* Name: _c_DIDS_HEX_D11Eh_IP_msgType,     */
typedef union
{
    Type_uByte _C[3];
    struct
    {
		Type_uByte DASFCMWarning : 2;
		Type_uByte AirbagSystemError : 2;
		Type_uByte Glow : 1;
		Type_uByte DASTSRState : 2;
		Type_uByte DASACCSetSpeed : 1;

    	Type_uByte HDCControlStatus : 2;
    	Type_uByte DpfWarningInf : 2;
    	Type_uByte AdBlueLevelWarning_LD : 3;
    	Type_uByte EPSFail_WL : 1;
		
		Type_uByte Mode : 2;
		Type_uByte unused2 : 6;
		
    } Signals;
}_c_DIDS_HEX_D11Eh_IP_msgType;
/* Name: _c_DIDS_HEX_E105h_IP_msgType,     */
typedef union
{
    Type_uByte _C[4];
    struct
    {
		Type_uHWord EngineSpeed : 16;
		
		Type_uByte Mode : 2;
		Type_uHWord unused0 : 14;
		
    } Signals;
}_c_DIDS_HEX_E105h_IP_msgType;
/* Name: _c_DIDS_HEX_E102h_IP_msgType,     */
typedef union
{
    Type_uByte _C[4];
    struct
    {
		Type_uHWord VehicleSpeed : 16;
		
		Type_uByte Mode : 2;
		Type_uHWord unused0 : 14;
		
    } Signals;
}_c_DIDS_HEX_E102h_IP_msgType;
/* Name: _c_DIDS_HEX_E103h_IP_msgType,     */
typedef union
{
    Type_uByte _C[4];
    struct
    {
		Type_uHWord EngineCoolantTemp;
		
		Type_uByte Mode : 2;
		Type_uHWord unused2 : 14;
		
    } Signals;
}_c_DIDS_HEX_E103h_IP_msgType;
/* Name: _c_DIDS_HEX_E104h_IP_msgType,     */
typedef union
{
    Type_uByte _C[8];
    struct
    {
		Type_uWord FuelVolume :32;
		
		Type_uByte Mode : 2;
		Type_uWord unused0 : 30;
		
    } Signals;
}_c_DIDS_HEX_E104h_IP_msgType;


/* Name: _c_ICGM_ADAS_259h_msgTypeTag,     */
typedef union
{
    Type_uByte _C[12];
    struct
    {
		Type_uHWord IsTimeout 					: 1;
		Type_uHWord Left_Obstacle_Indicator 	: 1;
		Type_uHWord LeftCloseRangeRLaneCutln 	: 1;
		Type_uHWord LeftCloseToLLane 			: 1;
		Type_uHWord CIPV_ObstacleType 			: 3;
		Type_uHWord unused0						: 1;

		Type_uHWord Left_ObstacleType 					: 3;
		Type_uHWord Left_Obstacle_Rlane_Cut_in_and_out 	: 3;
		Type_uHWord unused1								: 2;

		Type_uHWord Left_ObstaclePosX 			: 16;
		Type_uHWord Left_ObstaclePosY 			: 16;

		Type_uHWord ID_CIPV 					: 8;
		Type_uHWord ID_Left_Obstacle 			: 8;
		Type_uHWord ID_Right_Obstacle 			: 7;
		Type_uHWord unused2						: 1;
		
		Type_uHWord Left_Obstacle_Llane_Status 	: 3;
		Type_uHWord CIPV_Rlane_Cut_in_and_out 	: 3;
		Type_uHWord unused3						: 2;
		
		Type_uHWord CIPV_LLane_Cut_in_and_out   : 3;
		Type_uHWord unused4						: 13;		
    } Signals;
}_c_ICGM_ADAS_259h_IP_msgType;


typedef union
{
    Type_uByte _C[12];
    struct
    {
		Type_uHWord IsTimeout 							: 1;
		Type_uHWord Right_Obstacle_Indicator 			: 1;
		Type_uHWord RightCloseRangeLLaneCutln 			: 1;
		Type_uHWord RightCloseToRLane 					: 1;
		Type_uHWord CIPV_ObstacleStatus 				: 3;
		Type_uHWord unused0 							: 1;
		
		Type_uHWord Right_Obstacle_Rlane_Status  		: 3;
		Type_uHWord Right_Obstacle_Llane_Cut_in_and_out : 3;
		Type_uHWord unused2 							: 2;
		
		Type_uHWord Right_ObstacleType 					: 3;
		Type_uHWord Right_ObstacleStatus 				: 3;
		Type_uHWord unused3 							: 2;
		
		Type_uHWord CIPV_Crossing 						: 2;
		Type_uHWord unused4 							: 6;
		
		Type_uHWord CIPV_ObstaclePosX 					: 16;
		Type_uHWord CIPV_ObstaclePosY 					: 16;
		Type_uHWord Right_ObstaclePosX 					: 16;	
		Type_uHWord Right_ObstaclePosY 					: 16;
    } Signals;
}_c_ICGM_ADAS_25Bh_IP_msgType;

typedef union
{
    Type_uByte _C[10];
    struct
    {
		Type_uHWord IsTimeout 						: 1;
		Type_uHWord Lane0_Quality 					: 2;
		Type_uHWord unused0 						: 5;

		Type_uHWord Lane0_Crossing 					: 1;
		Type_uHWord Lane0_Lane_Mark_Width 			: 7;
		
		Type_uHWord Lane0_C0_Lane_Position 			: 16;	
		Type_uHWord Lane0_C1_Heading_Angle 			: 16;
		Type_uHWord Lane0_C2_Lane_Curvature 		: 16;		
		Type_uHWord Lane0_C3_Lane_Curvature_Driv 	: 16;
    }Signals;
}_c_ICGM_ADAS_25Dh_IP_msgType;


typedef union
{
    Type_uByte _C[10];
    struct
    {
		Type_uHWord IsTimeout 						: 1;
		Type_uHWord Lane1_Lane_Mark_Width 			: 7;
		
		Type_uHWord Lane1_Crossing 					: 1;
		Type_uHWord Lane1_Quality 					: 2;
		Type_uHWord unused0 						: 5;

		Type_uHWord Lane1_C0_Lane_Position 			: 16;
		Type_uHWord Lane1_C1_Heading_Angle 			: 16;		
		Type_uHWord Lane1_C2_Lane_Curvature 		: 16;				
		Type_uHWord Lane1_C3_Lane_Curvature_Driv 	: 16;	
   	}Signals;
}_c_ICGM_ADAS_263h_IP_msgType;


typedef union
{
    Type_uByte _C[10];
    struct
    {
		Type_uHWord IsTimeout 						: 1;
		Type_uHWord Lane2_Lane_Mark_Width 			: 7;

		Type_uHWord Lane2_Crossing 					: 1;
		Type_uHWord Lane2_Quality 					: 2;
		Type_uHWord unused0 						: 5;
		
		Type_uHWord Lane2_C0_Lane_Position 			: 16;
		Type_uHWord Lane2_C1_Heading_Angle 			: 16;	
		Type_uHWord Lane2_C2_Lane_Curvature 		: 16;
		Type_uHWord Lane2_C3_Lane_Curvature_Driv 	: 16;	
   	}Signals;
}_c_ICGM_ADAS_265h_IP_msgType;


typedef union
{
    Type_uByte _C[10];
    struct
    {
		Type_uHWord IsTimeout 					: 1;
		Type_uHWord Lane3_Crossing 				: 1;
		Type_uHWord Lane3_Quality 				: 2;
		Type_uHWord unused0 					: 4;
		
		Type_uHWord Lane3_Lane_Mark_Width 		: 7;
		Type_uHWord unused1 					: 1;
		
		Type_uHWord Lane3_C0_Lane_Position 		: 16;	
		Type_uHWord Lane3_C1_Heading_Angle 		: 16;
		Type_uHWord Lane3_C2_Lane_Curvature 	: 16;
		Type_uHWord Lane3_C3_Lane_Curvature_Driv : 16;
   	}Signals;
}_c_ICGM_ADAS_26Ah_IP_msgType;


typedef union
{
    Type_uByte _C[8];
    struct
    {
		Type_uByte IsTimeout 			: 1;
		Type_uByte Lane0_MarkColor 		: 3;
		Type_uByte Lane1_MarkColor 		: 3;		
		Type_uByte unused0 				: 1;

		Type_uByte Lane2_MarkColor 		: 3;
		Type_uByte Lane3_MarkColor 		: 3;
		Type_uByte unused1 				: 2;
		
		Type_uByte Lane0_TLC 			: 8;
		Type_uByte Lane1_TLC 			: 8;
		Type_uByte Lane2_TLC 			: 8;
		Type_uByte Lane3_TLC 			: 8;
		
		Type_uByte Lane0_Type 			: 4;
		Type_uByte Lane1_Type 			: 4;
		Type_uByte Lane2_Type 			: 4;
		Type_uByte Lane3_Type 			: 4;
   	}Signals;
}_c_ICGM_ADAS_26Bh_IP_msgType;


typedef union
{
    Type_uByte _C[5];
    struct
    {
		Type_uByte IsTimeout 				: 1;
		Type_uByte DASACCTakeoverIndicator 	: 1;
		Type_uByte DASACCGOIndicator 		: 1;
		Type_uByte DASACCDriverCancel 		: 1;
		Type_uByte DASCIPVIndicator 		: 1;
		Type_uByte DASACCOverrideIndicator 	: 1;
		Type_uByte DASLDWWarning 			: 2;

		Type_uByte DASACCState 				: 3;
		Type_uByte DASACCSetHeadway 		: 3;
		Type_uByte unused0 					: 2;

		Type_uByte DASLDWState 				: 3;
		Type_uByte DASCIPVRealHeadway 		: 3;
		Type_uByte unused1 					: 2;
		
		Type_uByte DASSensorError 			: 4;
		Type_uByte unused2 					: 4;

		Type_uByte DASACCSetSpeed 			: 8;
    }Signals;
}_c_ICGM_ADAS_290h_IP_msgType;


typedef union
{
    Type_uByte _C[2];
    struct
    {
		Type_uByte IsTimeout 				: 1;
		Type_uByte unused0 					: 7;
		Type_uByte DASTSRTargetSpeed 		: 8;
    }Signals;
}_c_ICGM_ADAS_291h_IP_msgType;
 
typedef union
{
	 Type_uByte _C[4];
	 struct
	 {
		 Type_uByte IsTimeout			: 1;
		 Type_uByte DASLKAHandsoff 		: 1;
		 Type_uByte DASFCWWarning 		: 2;
		 Type_uByte DASLKAState 		: 3;
		 Type_uByte unused0 			: 1;

		 Type_uByte DASIHCState 		: 3;
		 Type_uByte DASAEBState 		: 3;
		 Type_uByte unused1 			: 2;
		 
		 Type_uByte DASTSRState 		: 3;
		 Type_uByte DASFCWState 		: 3;		 
		 Type_uByte unused2 			: 2;

		 Type_uByte DASICCstate 		: 3;
		 Type_uByte unused3 			: 5;
	  }Signals;
}_c_ICGM_ADAS_293h_IP_msgType;

/* Mileage */
typedef union
{
	Type_uByte _C[8];
	struct
	{
		Type_uWord odovalue : 32;
		Type_uWord tripvalue : 32; 
		
	} Outdata;
}IPK_Mileage;
/* TripA */
typedef union
{
	Type_uByte _C[8];
	struct
	{
		Type_uWord triptimeA : 32;
		Type_uWord avrfuel : 32; 
		
	} Outdata;
}IPK_TripA;

/* IPK_Gauge */
typedef union
{
	Type_uByte _C[8];
	struct
	{
		Type_uByte AVSValue_A : 8;
		Type_uByte CoolantVal : 8;
		Type_uHWord TachoValue : 16;
		Type_uHWord SpeedVal : 16;
		Type_uHWord EngRunTime : 16;
	} Outdata;
}IPK_Gauge;
/* IPK_Fuel */
typedef union
{
	Type_uByte _C[8];
	struct
	{
		Type_uHWord Reserved : 16;
		Type_uHWord FuelOil_AD : 16;
		Type_uHWord FuelOil_AD_REF : 16;
		Type_uHWord FuelResist : 16;
	} Outdata;
}IPK_Fuel;
/* IPK_FuelRemain */
typedef union
{
	Type_uByte _C[8];
	struct
	{
		Type_uWord FuelRemain : 32;
		Type_uWord Reserved : 32;
	} Outdata;
}IPK_FuelRemain;
/* IPK_Other */
typedef union
{
	Type_uByte _C[8];
	struct
	{
		Type_uHWord BattVoltage : 16;
		Type_uByte OilTemp : 8;
		Type_uByte IFC_UNIT : 8;
		Type_uHWord FuleInjected :16;
		Type_uHWord EnduranceMileage :16;
	} Outdata;
}IPK_Other;

/* Name: _c_ICGM_IBDU_5B0h_IP_msgType,     */
typedef union
{
    Type_uByte _C[9];
    struct
    {
        Type_uByte IsTimeout : 1;      
        Type_uByte unused0 : 7;

        Type_uByte VINofBCM_b0 : 8;
        Type_uByte VINofBCM_b1 : 8;
        Type_uByte VINofBCM_b2 : 8;
        Type_uByte VINofBCM_b3 : 8;
        Type_uByte VINofBCM_b4 : 8;
        Type_uByte VINofBCM_b5 : 8;
        Type_uByte VINofBCM_b6 : 8;
        Type_uByte VINofBCM_b7 : 8;
		
    } Signals;
}_c_ICGM_IBDU_5B0h_IP_msgType;
typedef union
{
    Type_uByte _C[2];
    struct
    {
        Type_uByte aubDIDS_244 : 8;
        Type_uByte aubDIDS_245 : 8;	
    } Signals;
}_c_KERNAL_DIDS_INFO_msgType;

#if 0
/* Name: _c_ICU_FICM_558h_IP_msgType,    RPC MSG ID:   0x58 */
typedef union
{
    Type_uByte _C[8];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte LanguageSettingAdjustRequestActive : 1;
        Type_uByte TimeDisplayFormatAdjustment : 1;
        Type_uByte DateAdjustmentRequestActive : 1;
        Type_uByte TimeAdjustmentRequstActive : 1;
        Type_uByte AutoSetTimeDate : 2;
        Type_uByte unused0 : 1;
		
        Type_uByte DateYearAdjustment : 8;

        Type_uByte DateMonthAdjustment : 4;
        Type_uByte unused1 : 4;

        Type_uByte DateDayAdjustment : 5;
        Type_uByte unused2 : 3;

        Type_uByte TimeHourAdjustment : 5;	
        Type_uByte unused3 : 3;

        Type_uByte TimeZoneAdjustment : 5;
        Type_uByte unused4 : 3;

        Type_uByte TimeMinuteAdjustment : 6;
        Type_uByte unused5 : 2;

        Type_uByte TimeSecondAdjustment : 6;
        Type_uByte unused6 : 2;

    } Signals;
}_c_ICU_FICM_558h_IP_msgType;

/* Name: _c_ICU_FICM_560h_IP_msgType,    RPC MSG ID:   0x59 */
typedef union
{
    Type_uByte _C[6];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte BackLightingSetValue : 5;
        Type_uByte FICMParkGearUnlockingFunctionStatus : 2;
		
        Type_uByte FindMyCarDurationChangeRequest : 3;
        Type_uByte FollowMeHomeDurationChangeRe : 3;
        Type_uByte FICMDDDFunctionStatus : 2;
		
        Type_uByte RemoteLockingFeedbackChangeRequest : 2;
        Type_uByte FindMyCarFeedbackOptionsChangeRequest : 2;
        Type_uByte SinglePointEntryChangeRequest : 2;		
        Type_uByte AutoUnlockingChangeRequest : 2;

        Type_uByte AutomaticLockChangeRequest : 2;
        Type_uByte BSDSwitchStatus : 2;
        Type_uByte ESCFunctionStatus : 2;
        Type_uByte RCTAFunctionStatus : 2;
		
        Type_uByte LDWMainSensitivity : 2;	
        Type_uByte FICMDriveModeReq : 2;
        Type_uByte FICMFrontPDCEnableRequest : 2;
        Type_uByte FICM_SpeedWiperConfig : 2;
		
        Type_uByte FICMRestoreFactoryDefaultsRequest : 1;
        Type_uByte unused0 : 7;


    } Signals;
}_c_ICU_FICM_560h_IP_msgType;

/* Name: _c_ICU_FICM_580h_IP_msgType,    RPC MSG ID:   0x5A */
typedef union
{
    Type_uByte _C[1];
    struct
    {
        Type_uByte IsTimeout : 1;
        Type_uByte MirrorAutoFoldChangeRequest : 2;
        Type_uByte unused0 : 5;

    } Signals;
}_c_ICU_FICM_580h_IP_msgType;
#endif
/********************************************************************************************/
/*							Macro Definition Section										*/
/********************************************************************************************/
/* Name: _c_136_ESC_HMIInfo_msgType,    RPC MSG ID:   0x136 */
typedef union 
{
  Type_uByte _c[3];
  struct
  {		
		Type_uByte ESC_BrkLiActvnReq : 2;
		Type_uByte ESC_HmiLampReqEpbActv : 2;
		Type_uByte ESC_HmiLampReqEpbFlt : 2;
		Type_uByte ESC_HmiLampReqBrkSys : 2;
		
		Type_uByte ESC_HMIDrvPrstInAVH : 2;
		Type_uByte ESC_HmiLampReqEsc : 2;
		Type_uByte ESC_AdpvBrkLiActvnReq : 2;		
		Type_uByte IsTimeout : 1;		
		Type_uByte E2Estatus : 1;
		
		Type_uByte ESC_HmiTxtReqScm : 1;
		Type_uByte ESC_HmiLampReqHdc : 2;
		Type_uByte unused0 : 5;
  }Signals;
} _c_136_ESC_HMIInfo_msgType;

/* Name: _c_148_VCU_WarnForHU_msgType,    RPC MSG ID:   0x148 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
	  Type_uByte VCU_CoolantAlarmHMI : 2;
	  Type_uByte VCU_BatteryHeatCriticalHMI : 2;
	  Type_uByte VCU_SystemFailureHMI : 2;
	  Type_uByte VCU_SystemPowerLimitationHMI : 2;
	  
	  Type_uByte VCU_EMotorAlarmHMI : 2;
	  Type_uByte IsTimeout : 1;
	  Type_uByte E2Estatus : 1;
	  Type_uByte  unused0 : 4;
	  
  }Signals;
} _c_148_VCU_WarnForHU_msgType;

/* Name: _c_151_BCM_LightReq_msgType,    RPC MSG ID:   0x151 */
typedef union
{
  Type_uByte _c[7];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte BCM_RiSideDirIndcrReq : 1;
		Type_uByte BCM_LeDirIndcrTelltlLampReq : 2;
		Type_uByte E2Estatus : 1;
		Type_uByte unused0 : 3;
		Type_uByte BCM_FrntAxleLvlSnsrRawVal : 8;
		Type_uByte BCM_ReAxleLvlSnsrRawVal : 8;
		
		Type_uByte BCM_ReFogLiTelltlLampReq : 1;
		Type_uByte BCM_LeSideDirIndcrReq : 1;
		Type_uByte BCM_RiPosnLiReq : 1;
		Type_uByte BCM_LoBeamTelltlLampReq : 1;
		Type_uByte BCM_HiBeamReq : 2;
		Type_uByte BCM_LeWelcomePrjnRotReq : 1;
		Type_uByte BCM_ReFogLiSt : 1;
		
		Type_uByte BCM_LeDaytiRunngLiReq : 1;
		Type_uByte BCM_PosnLiSt : 1;
		Type_uByte unused1 : 1;
		Type_uByte BCM_RiWelcomePrjnReq : 1;
		Type_uByte BCM_RiWelcomePrjnRotReq : 1;
		Type_uByte BCM_LoBeamReq : 1;
		Type_uByte BCM_RiDirIndcrTelltlLampReq : 2;
		
		Type_uByte BCM_LePosnLiReq : 1;
		Type_uByte BCM_RiFrntDirIndcrReq : 1;
		Type_uByte BCM_LeFrntDirIndcrReq : 1;
		Type_uByte BCM_PosnLiTelltlLampReq : 1;
		Type_uByte BCM_HiBeamTelltlLampReq : 2;
		Type_uByte BCM_BCMHBAMXBReq : 2;
		
		Type_uByte unused2 : 4;
		Type_uByte BCM_KeyDetectWarn:2;
		Type_uByte BCM_LeWelcomePrjnReq : 1;
		Type_uByte BCM_RiDaytiRunngLiReq : 1;
  }Signals;
} _c_151_BCM_LightReq_msgType;

typedef union
{
  Type_uByte _c[6];
  struct
  {
	  Type_uByte VCU_AccrPosnAct : 8;

	  Type_uByte IsTimeout : 1;	
	  Type_uByte VCU_AccrPosnActVldy : 1; 
	  Type_uByte E2Estatus : 1;
	  Type_uHWord unused1 : 5;
	
	  Type_uHWord VCU_VehSpdLimReqdPtl :15;
	  Type_uByte unused0 : 1;

	  Type_uByte VCU_PtSt : 3;
	  Type_uByte VCU_LoglGearStsAct : 4;
	  Type_uByte VCU_VirtAccrPedlPosnVldy:1;
	  
	  Type_uByte VCU_VirtAccrPedlPosn:8;
	  
  }Signals;
} _c_97_VCU_AccPosGearSts_msgType;

/* Name: _c_9A_VCU_HvInfForDrvr_msgType,    RPC MSG ID:   0x9A */
typedef union
{
  Type_uByte _c[2];
  struct
  {
          Type_uByte IsTimeout : 1;
	  Type_uByte VCU_CoastLvlAct : 3;  
	  Type_uByte VCU_InvldCdnToDrvr : 3;
	  Type_uByte VCU_ElecPtLimdDecelSts : 1;
	  Type_uByte unused0 : 8;
  }Signals;
} _c_9A_VCU_HvInfForDrvr_msgType;
/* Name: _c_98_VCU_HvCoolgModReq_msgType,    RPC MSG ID:   0x98 */
typedef union
{
  Type_uByte _c[6];
  struct
  {
     	  Type_uByte IsTimeout : 1;
	  Type_uByte E2Estatus : 1;
	  Type_uByte VCU_LvDegradationDem:2;
	  Type_uByte VCU_AvlDrvMod : 4;
	  
	  Type_uByte VCU_ActvdDrvMod : 3;
	  Type_uByte VCU_HvCoolgModReq_RollingCounter : 4;
	  Type_uByte unused0 : 1;
	 
	  Type_uByte VCU_HvCoolgModReq_Checksum : 8;
	  
	  Type_uByte VCU_ChrgSts : 4;
	  Type_uByte unused1: 4; 
	  
	  Type_uByte VCU_DisChrgTarSOCRsp:8;
	  
	  Type_uByte VCU_HvBattSocDrv:7;
	  Type_uByte unused2 : 1;    
  }Signals;
} _c_98_VCU_HvCoolgModReq_msgType;
/* Name: _c_130_EPS_EPSInfo_msgType,    RPC MSG ID:   0x130 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
      	  Type_uByte IsTimeout : 1;
	  Type_uByte EPS_SteerWarnLamp_Rq : 2;
	  Type_uHWord unused0 : 13;
  }Signals;
} _c_130_EPS_EPSInfo_msgType;

/* Name: _c_1B2_BCM_HUFeedback_msgType,    RPC MSG ID:   0x1B2 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
      	  Type_uByte IsTimeout : 1;
	  Type_uByte BCM_ParkModCfgFb : 2;
	  Type_uByte BCM_MirrDimSnvtyCfgFb : 2;
	  Type_uByte BCM_EasyLveCfgFb : 1;
	  Type_uByte BCM_MirrAutoDimCfgFb : 1;
	  Type_uByte BCM_SideMirrAutFoldCfgFb : 1;
	  Type_uByte BCM_SideMirrAutHeatgCfgFb:1;
	  Type_uHWord unused0 : 7;

  }Signals;
} _c_1B2_BCM_HUFeedback_msgType;
/* Name: _c_1B1_BCM_States_msgType,    RPC MSG ID:   0x1B1 */
typedef union
{
  Type_uByte _c[4];
  struct
  {
      	  Type_uByte IsTimeout : 1;
	  Type_uByte BCM_T30R : 1;
	  Type_uByte BCM_T30S : 1;
	  Type_uByte BCM_T15D : 1;
	  Type_uByte BCM_VehSt : 3;
	  Type_uByte BCM_HoodSt : 1;
	  
	  Type_uByte BCM_TrClsSt : 2;
	  Type_uByte BCM_DirIndcrSt : 2;
	  Type_uByte BCM_States_RollingCounter : 4;
	  
	  Type_uByte BCM_States_Checksum : 8;
	  
	  Type_uByte BCM_ChdLockSt : 1;
	  Type_uByte E2Estatus : 1;
	  Type_uByte unused0 : 6;
  }Signals;
} _c_1B1_BCM_States_SecOC1_msgType;

/* Name: _c_201_ACM_ACMInfo_msgType,    RPC MSG ID:   0x201 */
typedef union
{
  Type_uByte _c[8];
  struct
  {
	  Type_uByte ACM_CrashOutpSts : 8;
	  
	  Type_uByte ACM_CrashSevLvl : 2;
	  Type_uByte ACM_FrntCrashOutpSts : 1;
	  Type_uByte ACM_PedProtnCrashOutpSts : 1;
	  Type_uByte ACM_RiSideCrashOutpSts : 1;
	  Type_uByte ACM_RollovrCrashOutpSts : 1;
	  Type_uByte ACM_RearCrashOutpSts : 1;
      	  Type_uByte IsTimeout : 1;
		  
	  Type_uByte ACM_LeSideCrashOutpSts : 1;
	  Type_uByte ACM_BucSwtSt2ndSeatRowLe : 2;
	  Type_uByte ACM_BucSwtStFrntPass : 2;
	  Type_uByte ACM_BucSwtStFrntDrvr : 2;
	  Type_uByte ACM_EmgyCall : 1;
	  
	  Type_uByte ACM_AirbWarnLampSt : 2;
	  Type_uByte ACM_BucSwtSt2ndSeatRowRi : 2;
	  Type_uByte ACM_BucSwtSt2ndSeatRowCentr : 2;
	  Type_uByte E2Estatus : 1;
	  Type_uByte unused1 : 1;
	  
	  Type_uByte ACM_OccptDetnSt2ndSeatRowRi : 2;
	  Type_uByte ACM_OccptDetnSt2ndSeatRowCentr : 2;
	  Type_uByte ACM_OccptDetnSt2ndSeatRowLe : 2;
	  Type_uByte ACM_OccptDetnStPassSeat : 2;
	  
	  Type_uByte ACM_SeatTrkPosnSwtFrntPass : 2;
	  Type_uByte ACM_SeatTrkPosnSwtFrntDrvr : 2;
	  Type_uByte ACM_ACMInfo_RollingCounter : 4;

	  Type_uByte ACM_ACMInfo_Checksum : 8;
	  Type_uByte unused0 : 8;
  }Signals;
} _c_201_ACM_ACMInfo_msgType;
/* Name: _c_1F7_CCU_AirT_msgType,    RPC MSG ID:   0x1F7 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
	  Type_uByte CCU_AmbAirT : 8;
	  
      	  Type_uByte IsTimeout : 1;
	  Type_uByte E2Estatus : 1;
	  Type_uByte unused0 : 6;
	  
  }Signals;
} _c_1F7_CCU_AirT_msgType;

/* Name: _c_245_BCM_AlrmWarnIn_msgType,    RPC MSG ID:   0x4B */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte BCM_AutHdlampLvlgLtgCdnSt : 1;
		Type_uByte BCM_HoodNotClsdWarnReq : 2;
		Type_uByte E2Estatus : 1;
		Type_uByte unused0 : 3;
		
		Type_uByte BCM_ChdLockErrSt : 2;
		Type_uByte BCM_WtrLvlDisp : 1;
		Type_uByte BCM_PasSettingCfgFb : 1;
		Type_uByte BCM_RedGuardCfgFb : 1;
		Type_uByte BCM_PepsKeyFobInVehSt : 1;
		Type_uByte BCM_BrkFldLvlDisp : 1;
		Type_uByte BCM_KeyFobInsVehSt : 1;
		
		Type_uByte BCM_ChrgnFlapRiNotClsdWarnReq : 2;
		Type_uByte BCM_ChrgnFlapNotClsdWarnReq : 2;
		Type_uByte BCM_PepsAdvKeyFobBattChrgnSt : 2;
		Type_uByte BCM_TrNotClsdWarnReq : 2;
		
		Type_uByte BCM_DoorRearLeNotClsdWarnReq : 2;
		Type_uByte BCM_DoorRearRiNotClsdWarnReq : 2;
		Type_uByte BCM_DoorPassNotClsdWarnReq : 2;
		Type_uByte BCM_DoorDrvrNotClsdWarnReq : 2;
  }Signals;
} _c_245_BCM_AlrmWarnIn_msgType;

/* Name: _c_152_BCM_MirrorPosReq_msgType,    RPC MSG ID:   0x4C */
typedef union
{
  Type_uByte _c[1];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte BCM_ImmWarning : 2;
		Type_uByte unused0 : 5;
  }Signals;
} _c_152_BCM_MirrorPosReq_msgType;

/* Name: _c_17F_AVAS_CurrSts_msgType,    RPC MSG ID:   0x4D */
typedef union
{
  Type_uByte _c[1];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte AVAS_AVASShowCurrSoundSeln : 3;
		Type_uByte AVAS_AVASShowCurrSts : 1;
		Type_uByte unused0 : 3;
  }Signals;
} _c_17F_AVAS_CurrSts_msgType;

/* Name: _c_246_BCM_TireWarn_msgType,    RPC MSG ID:   0x4E */
typedef union
{
  Type_uByte _c[8];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte unused0 : 7;
		
		Type_uByte BCM_TireWarnReLe : 8;
		Type_uByte BCM_TireWarnReRi : 8;
		Type_uByte BCM_TireWarnFrntLe : 8;
		Type_uByte BCM_TireWarnFrntRi : 8;
		Type_uByte unused1 : 8;
		
		Type_uByte BCM_TireWarn_RollgCntr : 4;
		Type_uByte unused2 : 4;
		
		Type_uByte BCM_TireWarn_Chks : 8;
  }Signals;
} _c_246_BCM_TireWarn_msgType;

/* Name: _c_247_BCM_TireP_msgType,    RPC MSG ID:   0x4F */
typedef union
{
  Type_uByte _c[8];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte unused0 : 7;
		
		Type_uByte BCM_TirePReLe : 8;
		Type_uByte BCM_TirePReRi : 8;
		Type_uByte BCM_TirePFrntLe : 8;
		Type_uByte BCM_TirePFrntRi : 8;
		Type_uByte unused1 : 8;
		
		Type_uByte BCM_TireP_RollgCntr : 4;
		Type_uByte unused2 : 4;
		
		Type_uByte BCM_TireP_Chks : 8;
  }Signals;
} _c_247_BCM_TireP_msgType;

/* Name: _c_248_BCM_TireT_msgType,    RPC MSG ID:   0x50 */
typedef union
{
  Type_uByte _c[8];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte BCM_TireMonTireSts : 1;
		Type_uByte BCM_TireMonSysSts : 1;
		Type_uByte unused0 : 5;
		
		Type_uByte BCM_TireTReLe : 8;
		Type_uByte BCM_TireTReRi : 8;
		Type_uByte BCM_TireTFrntLe : 8;
		Type_uByte BCM_TireTFrntRi : 8;
		Type_uByte unused1 : 8;
		
		Type_uByte BCM_TireT_RollgCntr : 4;
		Type_uByte unused2 : 4;
		
		Type_uByte BCM_TireT_Chks : 8;
  }Signals;
} _c_248_BCM_TireT_msgType;

/* Name: _c_212_BCM_CANFD_msgType,    RPC MSG ID:   0x51 */
typedef union
{
  Type_uByte _c[3];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte E2Estatus : 1;
		Type_uByte BCM_HmiLampReqBrkPadWarn : 2;
		Type_uByte BCM_PASSwtPsd : 1;
		Type_uByte BCM_ErrWipr : 1;
		Type_uByte BCM_MidHiBrkLiFailrSts:1;
		Type_uByte BCM_ImobBkpWarn:1;
		
		Type_uByte BCM_LvlBattULoWarn:2;
		Type_uByte BCM_EgyLvlDegradationWarn:2;
		Type_uByte BCM_AutoWiprCtrlWarn:1;
		Type_uByte BCM_KeyInsideWarn:1;
		Type_uByte BCM_BrkPedlIndcnWarn:1;
		Type_uByte BCM_PwrRlyErrWarn:1;
				

		Type_uByte BCM_AutoLiCtrlWarn:1;
		Type_uByte BCM_HeadLightOpenWarn:1;
		Type_uByte BCM_ReLeRvsLiFailrSts:1;
		Type_uByte BCM_ReRiRvsLiFailrSts:1;
		Type_uByte BCM_ReLeFogFailrSts:1;
		Type_uByte BCM_ReLeBrkLiFailrSts :1;
		Type_uByte BCM_ReRiBrkLiFailrSts:1;
		Type_uByte BCM_ReRiFogFailrSts : 1;
		
  }Signals;
} _c_212_BCM_CANFD_msgType;

/* Name: _c_138_ESC_HmiLampReq_msgType,    RPC MSG ID:   0x52 */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte ESC_HmiLampReqHHCFlt : 1;
		Type_uByte ESC_HmiLampReqEPBMode : 3;
		Type_uByte E2Estatus : 1;
		Type_uByte unused0 : 2;
		
		Type_uByte ESC_HmiLampReqAVHSts : 2;
		Type_uByte ESC_HmiLampReqABS : 2;
		Type_uByte ESC_HmiLampReqTCSOff : 2;
		Type_uByte ESC_HmiLampReqTCS : 2;
		
		Type_uByte ESC_HmiLampReq_RollgCntr : 4;
		Type_uByte unused5 : 4;
		
		Type_uByte ESC_HmiLampReq_Chks : 8;
  }Signals;
} _c_138_ESC_HmiLampReq_msgType;

/* Name: _c_131_ESC_FctSt_msgType,    RPC MSG ID:   0x53 */
typedef union
{
  Type_uByte _c[8];
  struct
  {
  		Type_uHWord ESC_VehYawRate : 12;
		Type_uByte ESC_CtrlrAvlTcs : 2;
		Type_uByte ESC_CtrlrAvlAbs : 2;
		
		Type_uByte IsTimeout : 1;
		Type_uByte ESC_EpbSts : 3;
		Type_uByte ESC_FctAvlHbb : 2;
		Type_uByte ESC_CtrlrAvlEbd : 2;
				
		Type_uByte ESC_FctActvCdp : 1;
		Type_uByte ESC_CtrlrActvTcs : 1;
		Type_uByte ESC_CtrlrActvDtc : 1;
		Type_uByte ESC_CtrlrActvEbd : 1;
		Type_uByte ESC_CtrlrActvAbs : 1;
		Type_uByte ESC_EscSysSts : 3;
		
		Type_uByte ESC_BrkPedlStsVldy : 1;
		Type_uByte ESC_BrkPedlSts : 1;
		Type_uByte ESC_FctAvlCdp : 1;
		Type_uByte ESC_FctAvlAvh : 1;
		Type_uByte ESC_FctActvAvh : 2;
		Type_uByte ESC_FctActvHba : 1;
		Type_uByte ESC_FctAvlHba : 1;
		
		Type_uByte ESC_CtrlrAvlEsc : 2;
		Type_uByte ESC_FctActvHdc : 2;
		Type_uByte ESC_FctActvHbb : 1;
		Type_uByte ESC_VehMovgDir : 3;
		
		Type_uByte ESC_FctSt_RollingCounter : 4;
		Type_uByte ESC_PrimBrkSysAvl : 2;
		Type_uByte E2Estatus : 1;
		Type_uByte ESC_CtrlrActvEsc : 1;
		
		Type_uByte ESC_FctSt_Checksum : 8;
  }Signals;
} _c_131_ESC_FctSt_msgType;




/* Name: _c_1BC_SUM_SuspSts_msgType,    RPC MSG ID:   0x55 */
typedef union
{
  Type_uByte _c[1];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte SUM_SuspChassisHeiMovmtDir : 2;
		Type_uByte SUM_SuspChassisHeiMovmtDirValid : 1;
		Type_uByte unused0 : 4;
  }Signals;
} _c_1BC_SUM_SuspSts_msgType;

/* Name: _c_17C_SUM_SuspSys_msgType,    RPC MSG ID:   0x56 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte SUM_SuspSysProtnSts : 3;
		Type_uByte SUM_SuspSysFailrSts : 3;
		Type_uByte E2Estatus : 1;
		
		Type_uByte SUM_SuspChassisDamperModAct : 2;
		Type_uByte SUM_DampCtrlLimpHome : 1;
		Type_uByte unused1 : 5;
		
  }Signals;
} _c_17C_SUM_SuspSys_msgType;

/* Name: _c_F7_BMS_BatteryRelayErrSts_msgType,    RPC MSG ID:   0x57 */
typedef union
{
  Type_uByte _c[1];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte BMS_VehHvIsoErr : 4;
		Type_uByte unused0 : 3;
  }Signals;
} _c_F7_BMS_BatteryRelayErrSts_msgType;

/* Name: _c_D8_IPU_DCDCSts_msgType,    RPC MSG ID:   0x58 */
typedef union
{
  Type_uByte _c[1];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte IPU_EEMDCDCFailrSts : 3;
		Type_uByte unused0 : 4;
  }Signals;
} _c_DB_IPU_DCDCSts_msgType;

/* Name: _c_2F1_VCU_CurrEngPwr_msgType,    RPC MSG ID:   0x59 */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uHWord VCU_CurrEngPwr : 15;

		Type_uByte VCU_CurrEngPwr_RollingCounter : 4;
		Type_uByte E2Estatus : 1;
		Type_uByte unused0 : 3;
		
		Type_uByte VCU_CurrEngPwr_Checksum : 8;
  }Signals;
} _c_2F1_VCU_CurrEngPwr_msgType;
	
/* Name: _c_AC_VCU_MaxPowerAvl_msgType,    RPC MSG ID:   0x5A */
typedef union
{
  Type_uByte _c[6];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte E2Estatus : 1;
		Type_uHWord unused0 :14;
		
		Type_uHWord VCU_MaxDrivePowerAvl_1 : 13;
		Type_uByte VCU_LvWarn : 3;

		Type_uHWord VCU_MaxRegenPowerAvl_1 : 13;
		Type_uByte VCU_HvWarn : 3;
  }Signals;
} _c_AC_VCU_MaxPowerAvl_msgType;

/* Name: _c_E3_INVF_MotSpd_msgType,    RPC MSG ID:   0x5B */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uHWord unused0 :15;
		
		Type_uHWord INVF_IvtrFrntIdcAct : 16;
  }Signals;
} _c_E3_INVF_MotSpd_msgType;

/* Name: _c_E4_INVF_MotTq_msgType,    RPC MSG ID:   0x5C */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uHWord unused0 :15;
		
		Type_uHWord INVF_IvtrFrntUdc : 16;
  }Signals;
} _c_E4_INVF_MotTq_msgType;

/* Name: _c_F3_INVR_MotSpd_msgType,    RPC MSG ID:   0x5D */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uHWord unused0 :15;
		
		Type_uHWord INVR_IvtrReIdcAct : 16;
  }Signals;
} _c_F3_INVR_MotSpd_msgType;

/* Name: _c_F4_INVR_MotTq_msgType,    RPC MSG ID:   0x5E */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uHWord unused0 :15;
		
		Type_uHWord INVR_IvtrReUdc : 16;
  }Signals;
} _c_F4_INVR_MotTq_msgType;

/* Name: _c_200_BMS_HvBattTiRmnChrgn_msgType,    RPC MSG ID:   0x5F */
typedef union
{
  Type_uByte _c[4];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte BMS_HVBattThermRunaway:2;
		Type_uByte E2Estatus : 1;
		Type_uHWord unused0 : 12;
		
		
		Type_uHWord BMS_HvBattTiRmnChrgn : 16;
  }Signals;
} _c_200_BMS_HvBattTiRmnChrgn_msgType;

/* Name: _c_B3_VCU_ReminDrvgRng_msgType,    RPC MSG ID:   0x60 */
typedef union
{
  Type_uByte _c[8];
  struct
  {
		Type_uByte IsTimeout : 1;
		Type_uByte VCU_ChrgCnctrDetd : 2;
		Type_uByte VCU_ChassisHeiRaisedTranSuc : 3;
		Type_uByte VCU_SpdLimiterStsAct:2;
		Type_uWord unused0 : 24;
		
		Type_uWord VCU_RmnDrvgRng : 32;
  }Signals;
} _c_B3_VCU_ReminDrvgRng_msgType;

/* Name: _c_183_SCM_States_msgType,    RPC MSG ID:   0x61 */
typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte SCM_HiBeamSwtFailrSts : 1;
	Type_uByte SCM_E_ShiftFault:2;
	Type_uByte unused0 : 4;
  }Signals;
} _c_183_SCM_States_msgType;

/* Name: _c_F9_BMS_BatSocU_msgType,    RPC MSG ID:   0x62 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
      	  Type_uByte IsTimeout : 1;
	  Type_uHWord BMS_HvBattU : 14;
	  Type_uByte unused0 : 1;	  
  }Signals;
} _c_F9_BMS_BatSocU_msgType;
/* Name: _c_FB_BMS_HVBatterySts_msgType,    RPC MSG ID:   0x63 */
typedef union
{
  Type_uByte _c[2];
  struct
  {
      	  Type_uByte IsTimeout : 1;
	  Type_uHWord BMS_HvBattI : 15; 
  }Signals;
} _c_FB_BMS_HVBatterySts_msgType;

/* Name: _c_164_ADAS_States_msgType,    RPC MSG ID:   0x66 */
typedef union
{
  Type_uByte _c[3];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_AdasTJASts : 2;
	Type_uByte ADAS_AdasLCCFailr : 1;
	Type_uByte ADAS_AdasISASetSpdProposalSts : 2;
	Type_uByte ADAS_AdasTJAFailr : 1;
	Type_uByte ADAS_States_RollingCounter : 4;
	Type_uByte unused0 : 5;
	
	Type_uByte ADAS_States_Checksum : 8;
  }Signals;
} _c_164_ADAS_States_msgType;
/* Name: _c_169_ADAS_AEB_msgType,    RPC MSG ID:   0x67 */
typedef union
{
  Type_uByte _c[1];
  struct
  {
      	  Type_uByte IsTimeout : 1;
	  Type_uByte ADAS_AdasBrkJerkReq:1;
	  Type_uByte E2Estatus: 1;
	  Type_uByte unused0 : 5;
  }Signals;
} _c_169_ADAS_AEB_msgType;

/* Name: _c_173_ADAS_Infor_msgType,    RPC MSG ID:   0x68 */
typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte E2Estatus: 1;
	Type_uByte unused0 : 6;
  }Signals;
} _c_173_ADAS_Infor_msgType;
/* Name: _c_1C1_ADAS_TSRSts_msgType,    RPC MSG ID:   0x69 */
typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte ADAS_TSRTrfcSignVal : 8;

	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TSR_Warn_Offset_St : 7;
	
	Type_uByte E2Estatus: 1;
	Type_uByte unused0 : 3;
	Type_uByte ADAS_TSR_SpeedLimitUnit : 2;
	Type_uByte ADAS_TSR_SpeedLimitype : 2;

	Type_uByte ADAS_TSR_Operating_St : 3;
	Type_uByte ADAS_TSR_LimitSpeed : 5;
	

	
  }Signals;
} _c_1C1_ADAS_TSRSts_msgType;

/* Name: _c_1C2_ADAS_FCTA_msgType,    RPC MSG ID:   0x6A */
typedef union
{
  Type_uByte _c[2];
  struct
  {

	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_FCTB_St :3;
	Type_uByte E2Estatus: 1;
	Type_uByte ADAS_FCTA_St : 3;

	Type_uByte ADAS_FCTA_Right_Warn_St:3;
	Type_uByte ADAS_FCTA_Left_Warn_St:3;
	Type_uByte unused1 : 2;
  }Signals;
} _c_1C2_ADAS_FCTA_msgType;

/* Name: _c_1C3_ADAS_FCTASts_msgType,    RPC MSG ID:   0x6B */
typedef union
{
  Type_uByte _c[3];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_FCS_TargetType : 4;
	Type_uByte ADAS_AdasEbReqTyp : 3;
	
	Type_uByte ADAS_FCWRequest : 2;
	Type_uByte ADAS_FCW_St : 3;
	Type_uByte ADAS_FCWSensitvity_St : 2;
	Type_uByte E2Estatus : 1;
	
	Type_uByte unused0 : 5;
	Type_uByte ADAS_AEB_St : 3;

  }Signals;
} _c_1C3_ADAS_FCTASts_msgType;
/* Name: _c_1C4_ADAS_DOWSts_msgType,    RPC MSG ID:   0x6C */
typedef union
{
  Type_uByte _c[5];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_DOW_FL_Warn_St : 2;
	Type_uByte ADAS_DOW_St : 3;
	Type_uByte ADAS_AdasDirIndcrReq : 2;
	
	Type_uByte E2Estatus : 1;
	Type_uByte ADAS_RCW_Warn_St : 2;
	Type_uByte ADAS_DOW_RR_Warn_St : 2;
	Type_uByte ADAS_RCW_St : 3;
	
	Type_uByte ADAS_RCTA_St : 3;
	Type_uByte ADAS_LCA_St : 3;
	Type_uByte ADAS_DOW_FR_Warn_St : 2;

	Type_uByte ADAS_RCTB_St : 3;
	Type_uByte ADAS_RCTA_left_Warn_St : 3;
	Type_uByte ADAS_DOW_RL_Warn_St : 2;
	
	Type_uByte ADAS_RCTA_Right_Warn_St : 3;
	Type_uByte ADAS_LCA_Left_Warn_St : 2;
	Type_uByte ADAS_LCA_Right_Warn_St : 2;
	Type_uByte unused0 : 1;
	
  }Signals;
} _c_1C4_ADAS_DOWSts_msgType;
/* Name: _c_1C0_ADAS_DOWSts_msgType,    RPC MSG ID:   0x6D */
typedef union
{
  Type_uByte _c[3];
  struct
  {

	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_LKS_SteernWhlVib_St : 1;
	Type_uByte ADAS_LKS_Active_St : 3;
	Type_uByte ADAS_ELK_Active_St : 3;
	
	Type_uByte ADAS_ELK_St : 3;	
	Type_uByte ADAS_LDW_St:3;
	Type_uByte E2Estatus: 1;
	Type_uByte unused0:1;
	
	Type_uByte ADAS_LKA_St:3;
	Type_uByte unused1:5;
  }Signals;
} _c_1C0_ADAS_LKSSts_msgType;
/* Name: _c_186_ADAS_SSASts_msgType,    RPC MSG ID:   0x6E*/
typedef union
{
  Type_uByte _c[5];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_AdasHWALaneTopologyType : 4;
	Type_uByte ADAS_AdasHWALaneTopologySide : 2;
	Type_uHWord ADAS_AdasHWALaneTopologyDx : 9;
	
	Type_uHWord ADAS_AdasHWACrosswalkDx : 9;
	Type_uByte ADAS_AdasHWACrosswalkDetected : 1;
	Type_uByte ADAS_AECDshbReq : 2;
	Type_uByte ADAS_SSASts_RollgCntr : 4;
	
	Type_uByte ADAS_SSASts_Chks : 8;
  }Signals;
} _c_186_ADAS_SSASts_msgType;
/* Name: _c_187_ADAS_HWAReq_msgType,    RPC MSG ID:   0x6F*/
typedef union
{
  Type_uByte _c[6];
  struct
  {
	Type_uByte ADAS_AdasHWACtrlTarAccJerkMaxVal : 8;
	Type_uByte IsTimeout : 1;
	Type_uByte E2Estatus: 1;
	Type_uByte ADAS_HWA_status:3;
	Type_uByte ADAS_AdasHWAShutdownReq : 3;
	
	Type_uByte ADAS_AdasHWACtrlTarAccJerkMinVal : 8;
	Type_uByte ADAS_HWA_Passive_Reason : 2;
	Type_uByte unused0 : 2;
	Type_uByte ADAS_AdasHWAEmergencyBrakeReq : 1;
	Type_uByte ADAS_EPSStrWarnReq : 1;
	Type_uByte ADAS_ADASSSATrigHWA : 1;
	Type_uByte ADAS_AdasHWATarAAprvd : 1;
	
	Type_uHWord ADAS_AdasHWATarA : 9;
	Type_uByte unused1 : 7;
  }Signals;
} _c_187_ADAS_HWAReq_msgType;
/* Name: _c_193_ADAS_AdasSettingSt_msgType,    RPC MSG ID:   0x70*/
typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_DDWSettingSt : 2;
	Type_uByte ADAS_AdasCSATarSpdWarnSetting : 2;
	Type_uByte ADAS_AdasCSASettingSt : 2;
	Type_uByte ADAS_AdasISASettingSt : 2;
	Type_uByte unused0 : 7;
  }Signals;
} _c_193_ADAS_AdasSettingSt_msgType;
/* Name: _c_193_ADAS_AdasSettingSt_msgType,    RPC MSG ID:   0x71*/

/* Name: _c_193_ADAS_AdasSettingSt_msgType,    RPC MSG ID:   0x72*/
typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_AdasSRFailr : 1;
	Type_uByte ADAS_AdasSRSts : 1;
	Type_uByte ADAS_AdasHWAPopMsg : 5;
	
	Type_uByte ADAS_AHB_St : 3;
	Type_uByte unused0 : 5;
  }Signals;
} _c_182_ADAS_SRSts_msgType;
typedef union
{
  Type_uByte _c[3];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_ADASTurningOptionsLeftLane : 4;
	Type_uByte ADAS_ADASTurningOptionsEgoLane : 4;
	Type_uByte ADAS_ASdM_SystemSt : 3;
	Type_uByte ADAS_ADASTurningOptionsRightLane : 4;
	
	Type_uByte ADAS_DDWDrowsinessVldy : 1;
	Type_uByte ADAS_DDWWarnLvl : 2;
	Type_uByte ADAS_DDWDrowsinessIdx : 5;
	
	Type_uByte ADAS_ControllerFaultStatus : 1;
	Type_uByte ADAS_SysSts_RollgCntr : 4;
	Type_uByte ADAS_SysSts_Chks : 8;
	Type_uByte unused0 : 3;
  }Signals;
} _c_230_ADAS_SysSts_msgType;
typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte unused0 : 2;
	Type_uByte ADAS_TrackTar0_Static_ObjectType:4;
	Type_uByte ADAS_TrackTar0_Static_St:1;
	Type_uByte ADAS_TrackTar0_Static_LgtPo:8;

	Type_uHWord ADAS_TrackTar0_Static_LatPo:10;
	Type_uByte unused1: 6;
	
  }Signals;
} _c_231_ADAS_TrackTar01_msgType;
typedef union
{
  Type_uByte _c[6];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_Longitudinal_Speed_0 : 7;
	Type_uByte ADAS_TrackTar0_LgtPo : 8;
	
	Type_uHWord ADAS_Lateral_Speed_0 : 10;
	Type_uByte E2Estatus: 1;
	Type_uByte ADAS_TrackTarget0_St : 1;
	Type_uByte ADAS_TrackTarget0_ObjectType : 4;
		
	Type_uHWord ADAS_TrackTar0_LatPo:10;
	Type_uByte unused2 : 6;
		
  }Signals;
} _c_232_ADAS_TrackTar0_msgType;

typedef union
{
  Type_uByte _c[6];
  struct
  {
	
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_Longitudinal_Speed_1 : 7;
	Type_uByte ADAS_TrackTar1_LgtPo:8;

	Type_uHWord ADAS_Lateral_Speed_1 : 10;
	Type_uByte ADAS_TrackTarget1_St:1;
	Type_uByte E2Estatus : 1;
	Type_uByte ADAS_TrackTarget1_ObjectType:4;
		
	Type_uHWord ADAS_TrackTar1_LatPo:10;
	Type_uByte unused0 : 6;
  }Signals;
} _c_233_ADAS_TrackTar1_msgType;

typedef union
{
  Type_uByte _c[3];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_FCamSensorCali_St : 1;
	Type_uByte ADAS_FMRRSensorCali_St : 1;
	Type_uByte ADAS_RFSRRSensorBloc_St : 1;
	Type_uByte ADAS_RRSRRSensorBloc_St : 1;
	Type_uByte ADAS_LRSRRSensorBloc_St : 1;
	Type_uByte ADAS_LFSRRSensorBloc_St : 1;
	Type_uByte ADAS_FCamSensorBloc_St : 1;
	
	Type_uByte ADAS_FMRRSensorBloc_St : 1;
	Type_uByte ADAS_LRSRRSensorFail_St : 1;
	Type_uByte ADAS_LFSRRSensorFail_St : 1;
	Type_uByte ADAS_FCamSensorFail_St : 1;
	Type_uByte ADAS_FMRRSensorFail_St : 1;
	Type_uByte ADAS_RFSRRSensorCali_St : 1;
	Type_uByte ADAS_RRSRRSensorCali_St : 1;
	Type_uByte ADAS_LRSRRSensorCali_St : 1;
	
	Type_uByte ADAS_LFSRRSensorCali_St : 1;
	Type_uByte ADAS_RFSRRSensorFail_St : 1;
	Type_uByte ADAS_RRSRRSensorFail_St : 1;
	Type_uByte ADAS_ControllerFaultStatus : 1;
	Type_uByte unused0 : 3;
	Type_uByte E2Estatus : 1;
  }Signals;
} _c_23F_ADAS_SRRsts_msgType;
typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ANRC_PrkgPDCVisualSwtFb : 1;
	Type_uByte ANRC_PrkgPDCMuteSwtFb : 1;
	Type_uByte ANRC_PrkgPDCActvnSwtFb : 1;
	Type_uByte ANRC_PrkgPDCMod : 4;
	
	Type_uByte ANRC_PrkgPDCObstclWarning:4;
	Type_uByte ANRC_PrkgPDCAudibleWarningSwtFb:1;
	Type_uByte ANRC_PrkgPDCVisualWarningSwtFb:1;
	Type_uByte unused:2;
  }Signals;
} _c_196_ANRC_PrkgPDC_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte DMS_FaceIdnSetUpSts : 2;
	Type_uByte DMS_DrowsnsLevel : 3;
	Type_uByte DMS_IdnResult : 4;
	Type_uByte DMS_DMSProcSts : 4;
	
	Type_uByte DMS_DistrctnLevel : 3;
	Type_uByte DMS_DMSAbandon_Reason : 2;
	Type_uByte DMS_DrinkingDetStatus : 2;
	Type_uByte DMS_SmokingDetStatus : 2;
	Type_uByte DMS_PlayPhoneDetStatus : 2;
	Type_uByte unused0 : 5;
  }Signals;
} _c_24D_DMS_DMSInfoHU_msgType;
typedef union
{
  Type_uByte _c[8];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uHWord ESC_VehLatAccl : 12;
	Type_uByte ESC_VehSpdVldy : 2;
	Type_uByte ESC_VehLgtAcclVldy : 1;
	
	Type_uHWord ESC_VehLgtAccl : 12;
	Type_uByte ESC_VehSpd_RollingCounter : 4;
	
	Type_uHWord ESC_VehSpd : 13;
	Type_uByte ESC_VehLatAcclVldy : 1;
	Type_uByte DMS_DrinkingDetStatus : 2;
	
	Type_uByte ESC_VehSpd_Checksum : 8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_132_ESC_VehSpd_msgType;

 typedef union
{
  Type_uByte _c[20];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 6;
	
	Type_uByte ANRC_PrkgRearLeDstToObstcl : 8;
	Type_uByte ANRC_PrkgRearMidLeDstToObstcl : 8;
	Type_uByte ANRC_PrkgRearMidRiDstToObstcl : 8;
	
	Type_uByte ANRC_PrkgRearMidLeObstclZon : 3;
	Type_uByte ANRC_PrkgRearLeObstclZon : 3;
	Type_uByte ANRC_PrkgRearRiObstclZon : 3;
	Type_uByte ANRC_PrkgRearMidRiObstclZon : 3;
	Type_uByte ANRC_RearDst_RollgCntr : 4;
	Type_uByte ANRC_PrkgRearRiDstToObstcl : 8;
	Type_uByte ANRC_RearDst_Chks : 8;
	
	Type_uByte ANRC_PrkgFrntLeDstToObstcl : 8;
	Type_uByte ANRC_PrkgFrntRiDstToObstcl : 8;
	Type_uByte ANRC_PrkgFrntMidLeDstToObstcl : 8;
	Type_uByte ANRC_PrkgFrntMidRiDstToObstcl : 8;
	
	Type_uByte ANRC_PrkgFrntMidLeObstclZon : 8;
	Type_uByte ANRC_FrntDst_Chks : 8;
	Type_uByte ANRC_PrkgFrntLeObstclZon : 3;
	Type_uByte ANRC_PrkgFrntRiObstclZon : 3;
	Type_uByte ANRC_PrkgFrntMidRiObstclZon : 3;
	Type_uByte ANRC_FrntDst_RollgCntr : 4;
	Type_uByte unused1 : 3;
	
	Type_uByte ANRC_SecOC2_Fresh : 8;
	Type_uWord ANRC_SecOC2_MAC : 24;
  }Signals;
} _c_20Eh_ANRC_PrkgDst_SecOC2_msgType;

typedef union
{
  Type_uByte _c[12];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte HU_SVS_Transparent_Model_ReqFromHU : 2;
	Type_uByte HU_SVS_Guidance_Line_ReqFromHU : 2;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 2;
	
	Type_uByte HU_SVS_Model_Color_ReqFromHU : 4;
	Type_uByte HU_3D_SVS_ReqFromHU : 2;
	Type_uByte HU_PASCrossInDirSel : 2;
	
	Type_uByte HU_3D_SVS_ViewChgReqFromHU : 4;
	Type_uByte HU_SVSObjOverlay : 2;
	Type_uByte HU_PrkgFuncSel : 2;
	
	Type_uByte HU_SVSActReqFromHU : 2;
	Type_uByte HU_SVSAutoViewSwitchModeReqFromHU : 2;
	Type_uByte HU_MCSCommand_RollgCntr : 4;
		
	Type_uByte HU_SecOC0_Fresh : 8;
	Type_uWord HU_SecOC0_MAC : 24;

	Type_uByte HU_MCSCommand_Chks : 8;
	Type_uWord unused1 : 24;
  }Signals;
} _c_21C_HU_MCSCommand_SecOC0_msgType;

typedef union
{
  Type_uByte _c[6];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ANRC_PrkgSideFrntMidLeAreaScanned : 1;
	Type_uByte ANRC_PrkgSideFrntMidRiObstclZon : 2;
	Type_uByte ANRC_PrkgSideFrntMidLeObstclZon : 2;
	Type_uByte ANRC_PrkgSideRearLeObstclZon : 2;
	
	Type_uByte ANRC_PrkgSideFrntRiObstclZon : 2;
	Type_uByte ANRC_PrkgSideRearMidRiObstclZon : 2;
	Type_uByte ANRC_PrkgSideRearMidLeObstclZon : 2;
	Type_uByte ANRC_PrkgSideRearLeAreaScanned : 1;
	Type_uByte ANRC_PrkgSideRearMidRiAreaScanned : 1;

	Type_uByte ANRC_PrkgSideRearMidLeAreaScanned : 1;
	Type_uByte ANRC_PrkgSideFrntMidRiAreaScanned : 1;
	Type_uByte ANRC_PrkgSideRearRiObstclZon : 2;
	Type_uByte ANRC_PrkgSideFrntLeAreaScanned : 1;
	Type_uByte ANRC_PrkgSideRearRiAreaScanned : 1;
	Type_uByte ANRC_PrkgSideFrntLeObstclZon : 2;
	
	Type_uByte ANRC_PrkgSideFrntRiAreaScanned : 1;
	Type_uByte ANRC_MEB_FuncSts : 4;
	Type_uByte ANRC_PrkgMEBWarnType : 3;
	
	Type_uByte ANRC_PrkgMEBSettingSt : 2;
	Type_uByte ANRC_SDW_MEB_Info_RollgCntr : 4;
	Type_uByte unused0 : 2;
	
	Type_uByte ANRC_SDW_MEB_Info_Chks : 8;
  }Signals;
} _c_20C_ANRC_SDW_MEB_Info_msgType;

typedef union
{
  Type_uByte _c[10];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uHWord ADAS_Line_1_A0 : 11;
	Type_uByte ADAS_Line_1_Type : 4;
	
	Type_uHWord ADAS_Line_1_A3 : 16;
	
	Type_uByte ADAS_Line_1_Display : 2;
	Type_uHWord ADAS_Line_1_A1 : 11;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 2;
	
	Type_uHWord ADAS_Line_1_A2 : 11;
	Type_uByte unused1 : 5;
	
	Type_uByte ADAS_LaneLineRange_1 : 8;
	Type_uByte unused2 : 8;
  }Signals;
} _c_240_ADAS_Line1_msgType;
typedef union
{
  Type_uByte _c[9];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ANRC_PrkgPASQuitIndcn : 6;
	Type_uByte ANRC_PrkgDrvReq : 5;
	Type_uByte ANRC_PrkgRcvIntrptIndcn : 4;
	
	Type_uByte ANRC_PrkgPASMod : 3;
	
	Type_uByte ANRC_PrkgLeSlotTyp1 : 3;
	Type_uByte ANRC_PrkgLeSlotTyp3 : 3;
	Type_uByte ANRC_PrkgLeSlotTyp2 : 3;
	Type_uByte ANRC_PrkgRiSlotTyp2 : 3;
	Type_uByte unused0 : 1;
	
	Type_uByte ANRC_PrkgRiSlotTyp1 : 3;
	Type_uByte ANRC_ParkingDistance02_RollgCntr : 4;
	Type_uByte unused1 : 6;
	
	Type_uByte ANRC_FunctionIndication : 5;
	Type_uByte ANRC_PrkgRiSlotTyp3 : 3;
	Type_uByte ANRC_ParkingDistance02_Chks : 8;
	
	Type_uByte ANRC_PrkgPASSwtPsdFb : 3;
	Type_uByte unused2 : 5;
  }Signals;
} _c_179_ANRC_ParkingDistance02_msgType;
typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ANRC_PrkgSelParkInOutSts : 2;
	Type_uByte ANRC_PrkgModSelAvl : 1;
	Type_uByte E2Estatus : 1;
	Type_uByte ANRC_PrkgInDirSelAvl : 1;
	Type_uByte unused0 : 2;
	
	Type_uByte ANRC_PrkgPASMod : 3;
	Type_uByte ANRC_PrkgFctIndcr : 5;
  }Signals;
} _c_176_ANRC_PASInfo_SecOC1_msgType;

typedef union
{
  Type_uByte _c[6];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ANRC_SVSAutoVidSetupReqToHU : 4;
	Type_uByte ANRC_SVSActStatusToHU : 2;
	Type_uByte ANRC_SVSAutoViewSwitchValidity : 1;
	
	Type_uByte ANRC_SVSAutoViewSwitchModeStatusToHU:2;
	Type_uByte ANRC_SVS360DegPosChgACKToHU:2;
	Type_uByte ANRC_SVSDegradationReason:4;

	
	Type_uByte ANRC_SVSAutoSwtModeStatusToHU : 2;
	Type_uByte ANRC_SVS_2D_3D_Status : 2;
	Type_uByte ANRC_SVSModelColorStatusToHU : 4;
	
	Type_uByte ANRC_SVSVidSetupStatusToHU : 4;
	Type_uByte ANRC_3D_SVSVidSetupStatusToHU : 4;
	
	Type_uByte ANRC_SVSFrontCamSts : 2;
	Type_uByte ANRC_SVSRearCamSts : 2;
	Type_uByte ANRC_SVSLeftCamSts : 2;
	Type_uByte ANRC_SVSRightCamSts : 2;
 
	
	Type_uByte ANRC_SVSGuidanceOLStatusToHU : 2;
	Type_uByte ANRC_SVSObjWarnOLStatusToHU : 2;
	Type_uByte ANRC_SVSTranspModStatusToHU : 2;
	Type_uByte unused0 : 2;
  }Signals;
} _c_17A_ANRC_SVSSts_msgType;
typedef union
{
  Type_uByte _c[8];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_Line_2_Display : 2;
	Type_uHWord ADAS_Line_2_A0 : 11;
	Type_uByte unused2 :2;
	
	Type_uHWord ADAS_Line_2_A3 : 16;

	Type_uHWord ADAS_Line_2_A1:11;
	Type_uByte ADAS_Line_2_Type:4;
	Type_uByte unused0 : 1;
	
	Type_uHWord ADAS_Line_2_A2:11;
	Type_uByte unused1 : 5;
  }Signals;
} _c_241_ANRC_SVSSts_msgType;
typedef union
{
  Type_uByte _c[8];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_Line_3_Display : 2;
	Type_uHWord ADAS_Line_3_A0 : 11;
	Type_uByte unused2 :2;
	
	Type_uHWord ADAS_Line_3_A3 : 16;

	
	Type_uHWord ADAS_Line_3_A1:11;
	Type_uByte ADAS_Line_3_Type:4;
	Type_uByte unused0 : 1;
	
	Type_uHWord ADAS_Line_3_A2:11;
	Type_uByte unused1 : 5;
  }Signals;
} _c_242_ADAS_Line3_msgType;
typedef union
{
  Type_uByte _c[8];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_Line_4_Display : 2;
	Type_uHWord ADAS_Line_4_A0 : 11;
	Type_uByte unused2 :2;
	
	Type_uHWord ADAS_Line_4_A3 : 16;

	
	Type_uHWord ADAS_Line_4_A1:11;
	Type_uByte ADAS_Line_4_Type:4;
	Type_uByte unused0 : 1;
	
	Type_uHWord ADAS_Line_4_A2:11;
	Type_uByte unused1 : 5;
  }Signals;
} _c_243_ADAS_Line4_msgType;
typedef union
{
  Type_uByte _c[11];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTar3_LgtPo : 8;
	Type_uByte ADAS_TrackTarget3_St : 1;
	Type_uByte ADAS_TrackTarget2_St:1;
	Type_uByte ADAS_TrackTarget3_ObjectType:4;
	Type_uByte unused0 : 1;

	Type_uByte ADAS_TrackTar2_LgtPo : 8;
	Type_uHWord ADAS_TrackTar23_Chks:8;
	
	Type_uHWord ADAS_TrackTar3_LatPo:10;
	Type_uByte ADAS_TrackTarget2_ObjectType:4;
	Type_uByte unused1 : 2;
	
	Type_uHWord ADAS_TrackTar2_LatPo:10;
	Type_uByte ADAS_TrackTar23_RollgCntr:4;
	Type_uByte unused2 : 2;	

	Type_uByte ADAS_TrackTar1_Static_LgtPo:8;
	
	Type_uByte ADAS_TrackTar1_Static_ObjectType:4;
	Type_uByte ADAS_TrackTar1_Static_St:1;
	Type_uHWord ADAS_TrackTar1_Static_LatPo:10;
	Type_uByte unused3 : 1;
  }Signals;
} _c_234_ADAS_TrackTar23_msgType;
typedef union
{
  Type_uByte _c[6];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTar4_LatPo : 8;
	Type_uByte ADAS_TrackTar4_LgtPo:7;
	
	Type_uByte ADAS_TrackTarget4_St : 1;
	Type_uHWord ADAS_TrackTar5_LgtPo:7;
	Type_uByte ADAS_TrackTar5_LatPo : 8;
	
	Type_uHWord ADAS_TrackTar45_RollgCntr:4;
	Type_uByte ADAS_TrackTar45_Chks:8;
	Type_uByte ADAS_TrackTarget5_St:1;
	Type_uByte unused0 : 3;
  }Signals;
} _c_239_ADAS_TrackTar45_msgType;

typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte LCMFL_LeFrntPosnLampFltSts : 2;
	Type_uByte LCMFL_LeLoBeamFltSts:2;
	Type_uByte LCMFL_LeGrpdLampModFltSts:1;
	Type_uByte LCMFL_LeHiBeamFltSts:2;

	Type_uByte LCMFL_LeFltDayLampSts:2;
	Type_uByte unused0 : 6;
  }Signals;
} _c_254_LCMFL_FltSts_msgType;

typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte LCMFR_RiFrntPosnLampFltSts : 2;
	Type_uByte LCMFR_RiLoBeamFltSts:2;
	Type_uByte LCMFR_RiGrpdLampModFltSts:1;
	Type_uByte LCMFR_RiHiBeamFltSts:2;
	
	Type_uByte LCMFR_RiFltDayLampSts:2;
	Type_uByte unused0 : 6;
  }Signals;
} _c_255_LCMFR_FltSts_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte LCMRL_LeRePosnFailrSt : 1;
	Type_uByte LCMRR_RiRePosnFailrSt:1;
	Type_uByte LCMRL_LeReDirIndcrFailrSt	 :1 ;
	Type_uByte LCMRR_RiReDirIndcrFailrSt:1;
	Type_uByte unused0 : 3;
  }Signals;
} _c_1E2_BCM_LIN1ASWM_msgType;
typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte LCMFL_LeFrntDirIndcrLampSt : 1;
	Type_uByte LCMFL_LeFrntDirIndcrFailrSt:2;
	Type_uByte unused0 : 4;
  }Signals;
} _c_142_LCMFL_LeFrntDirIndcrLam_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte LCMFR_RiFrntDirIndcrLampSt : 1;
	Type_uByte LCMFR_RiFrntDirIndcrFailrSt:2;
	Type_uByte unused0 : 4;
  }Signals;
} _c_143_LCMFR_RiFrntDirIndcrLam_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte DCMFL_LeSideDirIndcrFailrSt : 2;
	Type_uByte unused0 : 5;
  }Signals;
} _c_1C6_DCMFL_States1_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte DCMFR_RiSideDirIndcrFailrSt : 2;
	Type_uByte unused0 : 5;
  }Signals;
} _c_1B4_DCMFR_States_msgType;
typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte BCM_ImobMstWarn : 4;
	Type_uByte unused0 : 3;
  }Signals;
} _c_BE_BCM_ImobMstWarn_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte PLCU_ParkLockSt : 3;
	Type_uByte unused0 : 4;
  }Signals;
} _c_1E1_PLCU_ParkLockSts_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte VCU_VehSrvcWarn	 : 3;
	Type_uByte VCU_ValetModAct:2;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 1;
  }Signals;
} _c_208_VCU_DivModReq_msgType;

typedef union
{
  Type_uByte _c[3];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_ACC_CurveSpeed : 7;
	
	Type_uByte ADAS_ACC_GoNotifier	 : 1;
	Type_uByte ADAS_ACC_Warn_St : 3;
	Type_uByte ADAS_ACC_TimeGap : 4;
	
	Type_uByte E2Estatus : 1;
	Type_uByte ADAS_ACC_Passive_Reason : 5;
	Type_uByte unused0 : 2;
  }Signals;
} _c_181_ADAS_ACCSts_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_HWA_Warn_St	 : 3;
	Type_uByte ADAS_HWA_HandsonReq	:2;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 1;
  }Signals;
} _c_160_ADAS_HWA_Warn_msgType;
typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte DMS_DMSSts	 : 3;
	Type_uByte unused0 : 4;
  }Signals;
} _c_24B_MSG_DMS_DMSStatus_msgType;
typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ETC_RFModule	 : 1;
	Type_uByte ETC_ESAMModule	 : 1;
	Type_uByte ETC_Antitemper	 : 1;
	Type_uByte ETC_ESAMActivation	 : 1;
	Type_uByte unused0 : 3;
  }Signals;
} _c_30B_MSG_ETC_Module_msgType;

typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte unused0 : 7;
	
	Type_uByte ETC_EntranceExitType	 : 8;
  }Signals;
} _c_1A1_MSG_ETC_TransSt_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTarget2_ObjectType:4;
	Type_uByte ADAS_TrackTarget2_St:1;
	Type_uHWord ADAS_TrackTar2_LatPo:10;

	Type_uByte ADAS_TrackTar2_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_235_MSG_ADAS_TrackTar2_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTarget3_ObjectType:4;
	Type_uByte ADAS_TrackTarget3_St:1;
	Type_uHWord ADAS_TrackTar3_LatPo:10;

	Type_uByte ADAS_TrackTar3_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_236_MSG_ADAS_TrackTar3_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTarget3_Static_ObjectType:4;
	Type_uHWord ADAS_TrackTar3_Static_LatPo:10;
	Type_uByte	ADAS_TrackTarget3_Static_St:1;
	
	Type_uByte ADAS_TrackTar3_Static_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_23C_MSG_ADAS_TrackTar3_Static_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTarget4_ObjectType:4;
	Type_uByte ADAS_TrackTarget4_St:1;
	Type_uHWord ADAS_TrackTar4_LatPo:10;

	Type_uByte ADAS_TrackTar4_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_23A_MSG_ADAS_TrackTar4_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTar4_Static_ObjectType:4;
	Type_uByte ADAS_TrackTarget4_Static_St:1;
	Type_uHWord ADAS_TrackTar4_Static_LatPo:10;
	
	Type_uByte ADAS_TrackTar4_Static_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_23D_MSG_ADAS_TrackTar4_Static_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTarget5_ObjectType:4;
	Type_uByte ADAS_TrackTarget5_St:1;
	Type_uHWord ADAS_TrackTar5_LatPo:10;

	Type_uByte ADAS_TrackTar5_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_23B_MSG_ADAS_TrackTar5_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_TrackTar5_Static_ObjectType:4;
	Type_uByte ADAS_TrackTarget5_Static_St:1;
	Type_uHWord ADAS_TrackTar5_Static_LatPo:10;

	Type_uByte ADAS_TrackTar5_Static_LgtPo:8;
	Type_uByte E2Estatus : 1;
	Type_uByte unused0 : 7;
  }Signals;
} _c_23E_MSG_ADAS_TrackTar5_Static_msgType;

typedef union
{
  Type_uByte _c[4];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uHWord VCU_PwrMtrMax:10;
	Type_uByte unused:5;
	
	Type_uHWord VCU_PwrMtrMin:10;
	Type_uByte unused1:6;
	
  }Signals;
} _c_430_MSG_VCU_PwrMtr_msgType;

typedef union
{
  Type_uByte _c[9];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte unused:7;
	
	Type_uWord VCU_RngSaveSeatHeatg:32;

	Type_uWord VCU_RngSaveReWinHeatg:32;	
  }Signals;
} _c_B7_MSG_VCU_RngSave1_msgType;

typedef union
{
  Type_uByte _c[9];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte unused:7;
	
	Type_uWord VCU_RngSaveSeatMassg:32;

	Type_uWord VCU_RngSaveSoundSys:32;	
  }Signals;
} _c_B8_MSG_VCU_RngSave2_msgType;

typedef union
{
  Type_uByte _c[5];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte unused:7;
	
	Type_uWord VCU_RngSaveClimaCmpr:32;	
  }Signals;
} _c_B9_MSG_VCU_RngSave3_msgType;

typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uHWord VCU_RngSaveStrWhlHeatg:10;	
	Type_uByte unused0:5;
  }Signals;
} _c_2F6_MSG_VCU_TboxIndcd_msgType;

typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte unused0:7;
	
	Type_uByte VCU_ChrgSocTarSp:8;
  }Signals;
} _c_93_MSG_VCU_ChrgSysReq_msgType;

typedef union
{
  Type_uByte _c[1];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte eBooster_HmiLampReqiboosterFlt:1;	
	Type_uByte unused0:6;
  }Signals;
} _c_123_eBooster_EbbSts_msgType;

typedef union
{
  Type_uByte _c[2];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte ADAS_ACC_St:6;	
	Type_uByte E2Estatus:1;

	Type_uByte ADAS_AdasAccTypeReqMode:2;
	Type_uByte unused0:6;
  }Signals;
} _c_185_ADAS_ACC_ESCRq_msgType;

typedef union
{
  Type_uByte _c[6];
  struct
  {
	Type_uByte IsTimeout : 1;
	Type_uByte E2Estatus : 1;
	Type_uHWord unused0 : 14;
	
	Type_uHWord SCM_SteerWhlAg : 15;
	Type_uByte SCM_SasFailrSts : 1;
	
	Type_uHWord SCM_SteerWhlAgRate : 15;
	Type_uByte SCM_SasCalSts : 1;
  }Signals;
} _c_9E_SCM_SAS_Status_msgType;

/********************************************************************************************/
/*							Extern Declaration												*/
/********************************************************************************************/
extern Type_uByte crclib_getCRC8(const Type_uByte *xData, Type_uHWord xDataLen);
extern Type_uByte CalculateCheckSum(const Type_uByte *data, Type_uHWord len);
extern Type_uByte messageCounterCheck(Type_uByte lastCounter, Type_uByte newCounter);
extern Type_uByte compareTwoDatas(Type_uByte checkData1, Type_uByte checkData2);

/* Set message */
extern void nudCanClusterSetSignle(const Type_uByte *aubCanDataCache_p);

/* message receive */
extern void nvdCANRxMsgBCM_4( void);
extern void nvdCANRxMsgBCM_5( void);
extern void nvdCANRxMsgCLM_1( void);
extern void nvdCANRxMsgPEPS_1( void);
extern void nvdCANRxMsgRADAR_1( void);
extern void nvdCANRxMsgAVM_2( void);
extern void nvdCANRxMsgPLG_1( void);
extern void nvdCANRxMsgEMS_4( void);
extern void nvdCANRxMsgEMS_1_G( void);
extern void nvdCANRxMsgEMS_2_G( void);
extern void nvdCANRxMsgABS_ESP_1( void);
extern void nvdCANRxMsgABS_ESP_G( void);
extern void nvdCANRxMsgTCU_G( void);
extern void nvdCANRxMsgABM_1( void);
extern void nvdCANRxMsgEPB_G( void);
extern void nvdCANRxMsgBSD_1_G( void);
extern void nvdCANRxMsgEPS_1( void);
extern void nvdCANRxMsgLDW_1( void);
extern void nvdCANRxMsgFCM_2( void);
extern void nvdCANRxMsgFRM_3( void);
extern void nvdCANRxMsgEGS_2( void);
extern void nvdCANRxMsgAVM_APA_1( void);
extern void nvdCANRxMsgMFS_2( void);
extern void nvdCANRxMsgRADAR_2(void);
extern void nvdCANRxMsgSCU_1(void);
extern void nvdCANRxMsgWarnMsg_TCU(void);

extern void nvdCANRxMsgSAM_1_G( void); /* Info CAN Message */

/********************************************************************************************/
/*							Global Function Prototype Declaration							*/
/********************************************************************************************/


#endif 

/* End of File */
