#ifndef TELLTALESCONTROL_H
#define TELLTALESCONTROL_H

#include <hmi_share.h>
#include "telltale.h"
#include "telltaleflash.h"

#include <QMutex>
class Telltale;
class TelltalesStrategy;

#define MINUTE_TO_SEC(a)                       (a*60)
#define HOUR_TO_SEC(a)                         (a*60*60)

#define TELLTALE_COUTUP_ADJUST_MAX(a,b,max)      ((a+b)>max) ? max : (a+b)

#define TELLTALE_REMINDER_INTERVAL_HOUR         4        // 4H
#define TELLTALE_REMINDER_CANCEL_INTERVAL_HOUR  20       // 20min

#define TELLTALE_SELT_INTERVAL_HOUR             90
#define TELLTALE_SECOND_SELT_INTERVAL_HOUR      60


#define TELLTALE_TIMER_PLL				            2		// 定时器分频比: 1Sec/500msec = 2倍 500msec:ReciverCtrlTimerInvartal
/***********************************ENUM*****************************************/

enum PROPERTYID
{
    PROPERTYID_NONE = 0x00,
    PROPERTYID_CoolantAlarmLamp,//电机/电池冷却液报警
    PROPERTYID_TurnLeftLamp,
    PROPERTYID_TurnRightLamp ,
    PROPERTYID_LowBeamLamp ,
    PROPERTYID_HighBeamLamp ,
    PROPERTYID_LowPowerWarLamp ,
    PROPERTYID_VcuHvBattErrLamp ,
    PROPERTYID_EBDFaultLamp,
    PROPERTYID_EpsSteerWarnLamp ,
    PROPERTYID_DcdcFailrLamp ,
    PROPERTYID_PosiLamp ,
    PROPERTYID_EMotorAlarm ,
    PROPERTYID_MainDrvrLamp ,
    PROPERTYID_PassDriverLamp ,
    PROPERTYID_BackLeftLamp ,
    PROPERTYID_BackMiddleLamp ,
    PROPERTYID_BackRightLamp ,
    PROPERTYID_AntiLockBrakeLamp ,
    PROPERTYID_EpbLamp ,
    PROPERTYID_EpbFltLamp ,
    PROPERTYID_ChrgCnctrDetdLamp ,
    PROPERTYID_SystemFailureLamp,
    PROPERTYID_SysPowerLimitationLamp,
    PROPERTYID_HDC,
    PROPERTYID_BatteryHeat,
    PROPERTYID_FogLamp,
    PROPERTYID_AirbagLamp,
    PROPERTYID_ESCTCS,
    PROPERTYID_ESCTCSOff,
    PROPERTYID_AVH,
    PROPERTYID_AirSuspension_Fault,
    PROPERTYID_Tire,
    PROPERTYID_LowSpeedLamp,
    PROPERTYID_chargingLamp,
    PROPERTYID_autoLamp,
    PROPERTYID_FCSLamp,
    PROPERTYID_ACCLamp,
    PROPERTYID_HWALamp,
    PROPERTYID_WiperfaultLamp,
    PROPERTYID_FrontbonnetfaultLamp,
    PROPERTYID_AccStatusLamp,
    PROPERTYID_HWAStatusLamp,
    PROPERTYID_SpeedLimitLamp,
    PROPERTYID_SpeedLimitCancelLamp,
    PROPERTYID_ParkLockLamp,
    PROPERTYID_VehSrvcWarn,
    PROPERTYID_MAX
};

enum PROPERTYID_TELL
{
    PROPERTYID_LEFT_NOTFASTEN = 0x0,
    PROPERTYID_MID_NOTFASTEN,
    PROPERTYID_RIGHT_NOTFASTEN,

    PROPERTYID_LEFT_SEATEMPTY,
    PROPERTYID_MID_SEATEMPTY,
    PROPERTYID_RIGHT_SEATEMPTY,

    PROPERTYID_ACC_SPEED,
    PROPERTYID_SPEED_LIMIT,
};


enum TELLTALE_IC_CAN_INFO_SEND_ID{
    TELLTALE_IC_CAN_INFO_fatigueDrivingWarnning = 0x0,
    TELLTALE_IC_CAN_INFO_SpeedLimitSts,
    TELLTALE_IC_CAN_INFO_overspdWarningSwSts,
    TELLTALE_IC_CAN_INFO_overspdWarningSetFeedback,
    TELLTALE_IC_CAN_INFO_SpeedLimitModeSts,
    TELLTALE_IC_CAN_INFO_ID_MAX
};

enum SAFETYBELTAUDIO
{
    SHORT_AUDIO=0,
    LONG_AUDIO,
    LONG_AUDIO_2,
};
/***********************************class*****************************************/
class QMutex;
class TelltalesStrategy;
class TelltaleCustomTimer;
class TelltaleFlash;

class TelltalesControl: public CBaseControl, public CSingleton<TelltalesControl>
{
    Q_OBJECT
    friend class CSingleton<TelltalesControl>;
public:
    TelltalesControl();
    ~TelltalesControl();

    typedef void (TelltalesControl::*TellFunctionParser)();
    typedef void (TelltalesControl::*TellVoidFunctionParser)();

    Telltale* getTellById(int id);
    char* getBackup(int id);

    void func_MSG_LowPowerWarLamp();
    void func_MSG_LowPowerWarLampTimeOut();
    void func_MSG_CoolantAlarmLamp();
    void func_MSG_EMotorAlarm();
    void func_MSG_SystemFailureLamp();
    void func_MSG_SysPowerLimitationLamp();
    void func_MSG_BatteryHeatCritical();
    void func_MSG_BatteryHeatRunaway();
    void func_MSG_Left_Turn();
    void func_MSG_Right_Turn();
    void func_MSG_LowBeamLamp();
    void func_MSG_HighBeamLamp();
    void func_MSG_PosiLamp();
    void func_MSG_FogLamp();
    void func_MSG_ESC();
    void func_MSG_TCS();
    void func_MSG_EBDFaultReqBrkSys();
    void func_MSG_EBDFaultCtrlrAvlEbd();
    void func_MSG_EBDFaultBrkFldLvlDisp();
    void func_MSG_EBDFaultReqiboosterFlt();
    void func_MSG_EpbLampActv();
    void func_MSG_EpbFltLamp();
    void func_MSG_HDC();
    void func_MSG_EPSFault();
    void func_MSG_SEAT_BELT();
//    void func_MSG_OccLeft();
//    void func_MSG_BucMid();
//    void func_MSG_OccMid();
//    void func_MSG_BucRight();
//    void func_MSG_OccRight();
//    void func_MSG_BucDriver();
//    void func_MSG_BucPass();
//    void func_MSG_OccPass();
    void func_MSG_AirbagLamp();
    void func_MSG_TCSOff();
    void func_MSG_ABSLamp();
    void func_MSG_AVH();
    void func_MSG_AirSuspension_Fault();
    void func_MSG_TireSts();
    void func_MSG_TireSysSts();
    void func_MSG_Frontbonnetfault();
    void func_MSG_LowSpeedLamp();
    void func_MSG_BMSFault();
    void func_MSG_DcdcFailrLampSts();
    void func_MSG_DcdcFailrLampLvWarn();
    void func_MSG_ChargingTimeout();
    void func_MSG_Wiperfault();
    void func_MSG_AccStatusLamp();
    void func_MSG_CurveSpeed();
    void func_MSG_LimitSpeed();
    void func_MSG_TSROffset();
    void func_MSG_AutoLamp();
    void func_MSG_ACCTargetSpeed();
    void func_MSG_HWAStatusLamp();
    void func_MSG_ParkLockSts();
    void func_MSG_VCU_VehSrvcWarn();
signals:
    void PropertyChange(int index, const TellData tell);
    void notifyADASWaring();             //ADAS报警

public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void receiveDateFromOtherProcess(QString name, QVariant value);
    void get_timeout500ms();
    void get_timeout100ms();
    void get_timeout10ms();
protected:
    void dataChange();

    bool m_light_on;

private:
    QMutex mutex;
    TelltalesStrategy* _TelltalesStrategy;
//    HMICustomTimer* m_cruiseTimer;
//    HMICustomTimer* m_oilPressureLowTimer;
    HMICustomTimer* m_selfCheckTimer;

    QTimer* _timer10ms;
//    int m_pCFG_EPB;

    void handleTurnLamp();
    void handleDCDCErr();
    void handleEPBActv();
    void handleEpbFlt();
    void handleChargeState();
    void handleSeatBelt();
    void handleBatteryHeat();
    void handleESCTCS();
    void handleTireLamp();
    void handleEBDFault();
    void handleSpeedLimit();
    int compareSpeedLimit(int show_speed);
    void seltAudioCommon(SAFETYBELTAUDIO audio_id,Audio_ReqCmd audio_Cmd);
    TargetValue calcBackSeatBeltStrategy();
    int getBackSeatBeltStateLace();
    HMICustomTimer* m_Timer_BackSelt;
    TargetValue calFrontSeatBeltStrategy();
    int getFrontSeatBeltStateLace();
    HMICustomTimer* m_Timer_Selt_25secends;
    HMICustomTimer* m_Timer_Selt_95secends;
    HMICustomTimer* m_Timer_SpeedLimit_10secends;

};

#endif // TELLTALESCONTROL_H
