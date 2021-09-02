
#include "telltalesControl.h"
#include <math.h>
#include <QDebug>
#include <QTimer>
#include "telltalesStrategy.h"

#define SELF_CHECK_STATE 1
#define SEATBELTSOUND 1
static int g_vehicleSpeed = 0;
static int g_tell_ctrlPowerMode = static_cast<int>(POWERMODE_D3);
static QString g_cruise_Target_Speed = "";
static int g_powermode = 0;
static QString g_Gear = "";
static int seatBeltStateWarning_back = 0;
static int seatBeltStateWarning_front = 0;
static bool isNeedRepeatAlarm = false;
static bool isSeatbeltSoundPause = false;
static bool g_checkFrontSeatbelt_25Secends = false;//主副驾安全带是否到25s
static bool g_checkFrontSeatbelt_95Secends = false;//主副驾安全带是否到95s

static bool g_checkBackSeatbelt_25Secends = false;//后座安全带是否到25s
static bool g_checkBackSeatbelt_95Secends = false;//后座安全带是否到95s

static bool g_checkSpeedLimit_10Secends = false;//限速标志10s闪烁

static unsigned char g_lowPowerWarLampTimeOut = 0;
static unsigned char g_batteryHeatCriticalTimeOut = 0;
static unsigned char g_RightTurnTimeOut = 0;
static unsigned char g_LeftTurnTimeOut = 0;
static unsigned char g_epbLampTimeOut = 0;
static unsigned char g_epbFltLampTimeOut = 0;
static unsigned char g_ESCTimeOut = 0;
static unsigned char g_EBDFaultReqBrkSysTimeOut = 0;
static unsigned char g_TCSTimeOut = 0;
static unsigned char g_EBDFaultCtrlrAvlEbdTimeOut = 0;
static unsigned char g_EBDFaultBrkFldLvlDispTimeOut = 0;
static unsigned char g_EBDFaultReqiboosterFltTimeOut = 0;
static unsigned char g_BucDriverTimeOut = 0;
static unsigned char g_BucPassTimeOut = 0;
static unsigned char g_OccPassTimeOut = 0;
static unsigned char g_BucLeftTimeOut = 0;
static unsigned char g_OccLeftTimeOut = 0;
static unsigned char g_BucMidTimeOut = 0;
static unsigned char g_OccMidTimeOut = 0;
static unsigned char g_BucRightTimeOut = 0;
static unsigned char g_OccRightTimeOut = 0;
static unsigned char g_TireStsTimeOut = 0;
static unsigned char g_TireSysStsTimeOut = 0;
static unsigned char g_DcdcFailrLampStsTimeOut = 0;
static unsigned char g_DcdcFailrLampLvWarnTimeOut = 0;
static unsigned char g_CurveSpeedTimeOut = 0;
static unsigned char g_LimitSpeedTimeOut = 0;
static unsigned char g_TSROffsetTimeOut = 0;
static unsigned long int g_LowPowerWarLamp = 0;
static unsigned long int g_BatteryHeatCritical = 0;
static unsigned long int g_BatteryHeatRunaway = 0;
static unsigned long int g_Left_Turn = 0;
static unsigned long int g_Left_Turn_Backup = 0;
static unsigned long int g_Right_Turn = 0;
static unsigned long int g_Right_Turn_Backup = 0;
static unsigned long int g_ESC = 0;
static unsigned long int g_EBDFaultReqBrkSys = 0;
static unsigned long int g_EpbLampActv = 0;
static unsigned long int g_EpbFltLamp = 0;
static unsigned long int g_TCS = 0;
static unsigned long int g_EBDFaultCtrlrAvlEbd = 0;
static unsigned long int g_EBDFaultBrkFldLvlDisp = 0;
static unsigned long int g_EBDFaultReqiboosterFlt = 0;
static unsigned long int g_BucLeft = 0;
static unsigned long int g_OccLeft = 0;
static unsigned long int g_BucMid = 0;
static unsigned long int g_OccMid = 0;
static unsigned long int g_BucRight = 0;
static unsigned long int g_OccRight = 0;
static unsigned long int g_BucDriver = 0;
static unsigned long int g_BucPass = 0;
static unsigned long int g_OccPass = 0;
static unsigned long int g_TireSts = 0;
static unsigned long int g_TireSysSts = 0;
static unsigned long int g_DcdcFailrLampSts = 0;
static unsigned long int g_DcdcFailrLampLvWarn = 0;
static unsigned long int g_CurveSpeed = 0;
static unsigned long int g_LimitSpeed = 0;
static unsigned long int g_TSROffset = 0;


/*电机/电池冷却液低*/static Telltale Light_CoolantAlarmLamp = {TTPOWERMODE_D1,PROPERTYID_CoolantAlarmLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*左转向灯*/static Telltale Light_Left_Turn = {TTPOWERMODE_D1_D2,PROPERTYID_TurnLeftLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*右转向灯*/static Telltale Light_Right_Turn = {TTPOWERMODE_D1_D2,PROPERTYID_TurnRightLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*远光灯提示*/static Telltale Light_HighBeamLamp = {TTPOWERMODE_D1_D2,PROPERTYID_HighBeamLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*近光灯提示*/static Telltale Light_LowBeamLamp = {TTPOWERMODE_D1_D2,PROPERTYID_LowBeamLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*低电量报警报警指示灯*/static Telltale Light_LowPowerWarLamp = {TTPOWERMODE_D1_D2,PROPERTYID_LowPowerWarLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*BMS电池故障*/static Telltale Light_BMSFault = {TTPOWERMODE_D1_D2,PROPERTYID_VcuHvBattErrLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};

/*EBD故障 */static Telltale Light_EBDFault = {TTPOWERMODE_D1,PROPERTYID_EBDFaultLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_RED};

/*EPS故障*/static Telltale Light_EPSFault = {TTPOWERMODE_D1,PROPERTYID_EpsSteerWarnLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_YELLOW};
/*DCDC故障报警提示*/static Telltale Light_DcdcFailrLamp = {TTPOWERMODE_D1,PROPERTYID_DcdcFailrLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*位置灯指示*/static Telltale Light_PosiLamp = {TTPOWERMODE_D1_D2,PROPERTYID_PosiLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*电机系统故障*/static Telltale Light_EMotorAlarm = {TTPOWERMODE_D1,PROPERTYID_EMotorAlarm,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*前排安全带*/static Telltale Light_Seat_Main= {TTPOWERMODE_D1,PROPERTYID_MainDrvrLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*后排安全带*/static Telltale Light_Seat_BACK= {TTPOWERMODE_D1,PROPERTYID_BackLeftLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*ABS故障灯*/static Telltale Light_ABSLamp = {TTPOWERMODE_D1,PROPERTYID_AntiLockBrakeLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*EPB工作指示灯*/static Telltale Light_EpbLamp = {TTPOWERMODE_D1_D2,PROPERTYID_EpbLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*EPB故障*/static Telltale Light_EpbFltLamp = {TTPOWERMODE_D1,PROPERTYID_EpbFltLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*充电线连接指示灯*/static Telltale Light_ChrgCnctrDetdLamp = {TTPOWERMODE_D1_D2,PROPERTYID_ChrgCnctrDetdLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*动力系统故障*/static Telltale Light_SystemFailureLamp = {TTPOWERMODE_D1_D2,PROPERTYID_SystemFailureLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*车辆限功率提示*/static Telltale Light_SysPowerLimitationLamp = {TTPOWERMODE_D1,PROPERTYID_SysPowerLimitationLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*HDC指示灯*/static Telltale Light_HDC = {TTPOWERMODE_D1,PROPERTYID_HDC,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*动力电池过温告警*/static Telltale Light_BatteryHeat = {TTPOWERMODE_D1,PROPERTYID_BatteryHeat,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*后雾灯指示灯*/static Telltale Light_FogLamp = {TTPOWERMODE_D1_D2,PROPERTYID_FogLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*安全气囊指示灯*/static Telltale Light_AirbagLamp = {TTPOWERMODE_D1,PROPERTYID_AirbagLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*ESCTCS*/static Telltale Light_ESCTCS = {TTPOWERMODE_D1,PROPERTYID_ESCTCS,VISIBLE_false,FLASHTYPE_4HZ,COLORTYPE_NONE};
/*ESCTCSOff*/static Telltale Light_ESCTCSOff = {TTPOWERMODE_D1,PROPERTYID_ESCTCSOff,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*AVH工作中*/static Telltale Light_AVH= {TTPOWERMODE_D1,PROPERTYID_AVH,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*空气悬架故障*/static Telltale Light_AirSuspension_Fault = {TTPOWERMODE_D1,PROPERTYID_AirSuspension_Fault,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*胎压报警灯*/static Telltale Light_Tire = {TTPOWERMODE_D1,PROPERTYID_Tire,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};//频率？
/*低速行人报警*/static Telltale Light_LowSpeedLamp = {TTPOWERMODE_D1,PROPERTYID_LowSpeedLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*车辆续驶里程显示*/static Telltale Light_Charging= {TTPOWERMODE_D1,PROPERTYID_chargingLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*智能远光指示灯*/static Telltale Light_AutoLamp= {TTPOWERMODE_D1,PROPERTYID_autoLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*前碰撞系统FCS*/static Telltale Light_FCSLamp= {TTPOWERMODE_D1,PROPERTYID_FCSLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*ACC系统工作指示灯*/static Telltale Light_ACCLamp= {TTPOWERMODE_D1,PROPERTYID_ACCLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*HWA系统工作指示灯*/static Telltale Light_HWALamp= {TTPOWERMODE_D1,PROPERTYID_HWALamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*前雨刷故障指示灯*/static Telltale Light_Wiperfault= {TTPOWERMODE_D1,PROPERTYID_WiperfaultLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*前舱盖未关指示灯*/static Telltale Light_Frontbonnetfault= {TTPOWERMODE_D1,PROPERTYID_FrontbonnetfaultLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*ACC状态指示*/static Telltale Light_AccStatusLamp= {TTPOWERMODE_D1,PROPERTYID_AccStatusLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*HWA状态指示*/static Telltale Light_HWAStatusLamp= {TTPOWERMODE_D1,PROPERTYID_HWAStatusLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*限速标志*/static Telltale Light_SpeedLimitLamp= {TTPOWERMODE_D1,PROPERTYID_SpeedLimitLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*限速取消标志*/static Telltale Light_SpeedLimitCancelLamp= {TTPOWERMODE_D1,PROPERTYID_SpeedLimitCancelLamp,VISIBLE_false,FLASHTYPE_1HZ,COLORTYPE_NONE};
/*P档锁故障*/static Telltale Light_ParkLockLamp= {TTPOWERMODE_D1,PROPERTYID_ParkLockLamp,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};
/*动力系统异常*/static Telltale Light_VehSrvcWarn= {TTPOWERMODE_D1,PROPERTYID_VehSrvcWarn,VISIBLE_false,FLASHTYPE_NONE,COLORTYPE_NONE};

//第一版无自检
static QList<Telltale*> m_autoCheckList = {
    &Light_AirbagLamp,//安全气囊故障
    &Light_Tire,//胎压系统报警
    &Light_ESCTCS,//ESC/TCS指示灯
    &Light_ESCTCSOff,//ESC/TCS off指示灯
    &Light_ABSLamp,//ABS故障灯
    &Light_EBDFault,//EBD故障灯
    &Light_EpbLamp,//EPB工作指示灯
    &Light_EpbFltLamp,//EPB故障
    &Light_EPSFault,//EPS故障
};

static bool warnAlarm = false;
static bool turnAlarm = false;


QList<TelltalesControl::TellFunctionParser> TellVoidControlFunc {
    &TelltalesControl::func_MSG_LowPowerWarLamp,
            &TelltalesControl::func_MSG_LowPowerWarLampTimeOut,
            &TelltalesControl::func_MSG_CoolantAlarmLamp,
            &TelltalesControl::func_MSG_EMotorAlarm,
            &TelltalesControl::func_MSG_SystemFailureLamp,
            &TelltalesControl::func_MSG_SysPowerLimitationLamp,
            &TelltalesControl::func_MSG_BatteryHeatCritical,
            &TelltalesControl::func_MSG_BatteryHeatRunaway,
            &TelltalesControl::func_MSG_Left_Turn,
            &TelltalesControl::func_MSG_Right_Turn,
            &TelltalesControl::func_MSG_LowBeamLamp,
            &TelltalesControl::func_MSG_HighBeamLamp,
            &TelltalesControl::func_MSG_PosiLamp,
            &TelltalesControl::func_MSG_FogLamp,
            &TelltalesControl::func_MSG_ESC,
            &TelltalesControl::func_MSG_TCS,
            &TelltalesControl::func_MSG_EBDFaultReqBrkSys,
            &TelltalesControl::func_MSG_EBDFaultCtrlrAvlEbd,
            &TelltalesControl::func_MSG_EBDFaultBrkFldLvlDisp,
            &TelltalesControl::func_MSG_EBDFaultReqiboosterFlt,
            &TelltalesControl::func_MSG_EpbLampActv,
            &TelltalesControl::func_MSG_EpbFltLamp,
            &TelltalesControl::func_MSG_HDC,
            &TelltalesControl::func_MSG_EPSFault,
            &TelltalesControl::func_MSG_SEAT_BELT,
            &TelltalesControl::func_MSG_AirbagLamp,
            &TelltalesControl::func_MSG_TCSOff,
            &TelltalesControl::func_MSG_ABSLamp,
            &TelltalesControl::func_MSG_AVH,
            &TelltalesControl::func_MSG_AirSuspension_Fault,
            &TelltalesControl::func_MSG_TireSts,
            &TelltalesControl::func_MSG_TireSysSts,
            &TelltalesControl::func_MSG_Frontbonnetfault,
            &TelltalesControl::func_MSG_LowSpeedLamp,
            &TelltalesControl::func_MSG_BMSFault,
            &TelltalesControl::func_MSG_DcdcFailrLampSts,
            &TelltalesControl::func_MSG_DcdcFailrLampLvWarn,
            &TelltalesControl::func_MSG_ChargingTimeout,
            &TelltalesControl::func_MSG_Wiperfault,
            &TelltalesControl::func_MSG_AccStatusLamp,
            &TelltalesControl::func_MSG_CurveSpeed,
            &TelltalesControl::func_MSG_LimitSpeed,
            &TelltalesControl::func_MSG_TSROffset,
            &TelltalesControl::func_MSG_AutoLamp,
            &TelltalesControl::func_MSG_ACCTargetSpeed,
            &TelltalesControl::func_MSG_HWAStatusLamp,
            &TelltalesControl::func_MSG_ParkLockSts,
};

bool inMidValue(int value, int min, int max)
{
    if(value >= min && value <= max) return true;
    return false;
}
TelltalesControl::TelltalesControl()
{
    _TelltalesStrategy = new TelltalesStrategy();

    connect(_TelltalesStrategy, SIGNAL(PropertyChange(int, const TellData)), this,SIGNAL(PropertyChange(int, const TellData)));

    m_Timer_Selt_25secends = new HMICustomTimer(50 ,false);//安全带25s报警
    connect(m_Timer_Selt_25secends, &HMICustomTimer::timeout, this, [=](){
        LOGPRINT("25s timer stop")
                m_Timer_Selt_25secends->stop();
#ifdef SEATBELTSOUND
        seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
#endif
        if(g_vehicleSpeed >= 25 && g_vehicleSpeed < 40){
            isNeedRepeatAlarm = true;
            m_Timer_Selt_95secends->start();
#ifdef SEATBELTSOUND
            seltAudioCommon(LONG_AUDIO, AUDIO_PLAY);
#endif
            if(Light_Seat_Main.targetValue != VISIBLE_false){
                Light_Seat_Main.targetValue = VISIBLE_spangle;
            }
            if(Light_Seat_BACK.targetValue != VISIBLE_false){
                Light_Seat_BACK.targetValue = VISIBLE_spangle;
            }
        }
        else{
            isNeedRepeatAlarm = true;
            if(Light_Seat_Main.targetValue != VISIBLE_false){
                Light_Seat_Main.targetValue = VISIBLE_true;
            }
            if(Light_Seat_BACK.targetValue != VISIBLE_false){
                Light_Seat_BACK.targetValue = VISIBLE_spangle;
            }
            seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
        }
        _TelltalesStrategy->handleTellStrategy(&Light_Seat_Main);
        _TelltalesStrategy->handleTellStrategy(&Light_Seat_BACK);
    });

    m_Timer_Selt_95secends = new HMICustomTimer(180 ,false);//安全带95s报警
    connect(m_Timer_Selt_95secends, &HMICustomTimer::timeout, this, [=](){
        LOGPRINT("95s timer stop")
                isNeedRepeatAlarm = true;
        m_Timer_Selt_95secends->stop();
#ifdef SEATBELTSOUND
        seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
        seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
        if(Light_Seat_Main.targetValue != VISIBLE_false){
            Light_Seat_Main.targetValue = VISIBLE_true;
        }
        if(Light_Seat_BACK.targetValue != VISIBLE_false){
            Light_Seat_BACK.targetValue = VISIBLE_true;
        }
        _TelltalesStrategy->handleTellStrategy(&Light_Seat_Main);
        _TelltalesStrategy->handleTellStrategy(&Light_Seat_BACK);
    });

    m_Timer_SpeedLimit_10secends = new HMICustomTimer(20 ,false);//限速标志10s闪烁
    connect(m_Timer_SpeedLimit_10secends, &HMICustomTimer::timeout, this, [=](){
        m_Timer_SpeedLimit_10secends->stop();
        g_checkSpeedLimit_10Secends = true;
    });

    _TelltalesStrategy->addAutoCheckTell(m_autoCheckList);

    start(QThread::NormalPriority);
}

TelltalesControl::~TelltalesControl()
{
    if(_timer10ms)
    {
        _timer10ms->stop();
    }
    delete TelltalesControl::instance();
}

void TelltalesControl::dataChange()
{
    foreach (TelltalesControl::TellFunctionParser func, TellVoidControlFunc) {
        (this->*(func))();
    }
}

void TelltalesControl::handleTurnLamp()
{
    //灯--> 1：亮 !1:灭
    //声音--> 1：Click Sound  1->!1: Clack
    //声音特殊--> tmieout -> !timeout 如果是 !1: not Clack
    //signal value: {0, 1, 2, 3}
    bool showStateLeft = false;
    bool showStateRight = false;
    static bool isClick = false;

    if(g_RightTurnTimeOut == 0x01 || g_LeftTurnTimeOut == 0x01)
    {
        g_Left_Turn_Backup = 0;
        g_Right_Turn_Backup = 0;
        isClick = false;
        showStateLeft = false;
        showStateRight = false;
    }
    else{
        int left_change_count = -1; //-1,0,1
        int right_change_count = -1; //-1,0,1

        //左转向亮灭
        if(g_Left_Turn == 0x01)
        {
            showStateLeft = true;
        }
        else{
            showStateLeft = false;
        }

        //右转向亮灭
        if(g_Right_Turn == 0x01)
        {
            showStateRight = true;
        }
        else{
            showStateRight = false;
        }

        if(g_Left_Turn_Backup != g_Left_Turn)
        {
            left_change_count = (g_Left_Turn == 1) ? 1 : 0;
        }


        if(g_Right_Turn_Backup != g_Right_Turn)
        {
            right_change_count = (g_Right_Turn == 1) ? 1 : 0;
        }

        if(1 == left_change_count && 1 == right_change_count)
        {
            //危险警告指示灯 亮 仅提示一声转向音
            LOGPRINT("TelltaleControl::DANGER_AUDIO_INDEX_TURN_ON");
            audio_client_Play(AUDIO_INDEX_TURN_ON, AUDIO_PLAY);
        }
        else if(0 == left_change_count && 0 == right_change_count)
        {
            //危险警告指示灯 灭 仅提示一声转向音
            LOGPRINT("TelltaleControl::DANGER_AUDIO_INDEX_TURN_OFF");
            audio_client_Play( AUDIO_INDEX_TURN_OFF, AUDIO_PLAY);
        }
        else{
            //单指示灯
            if(1 == left_change_count || 1 == right_change_count)
            {
                //单指示灯 亮
                isClick = true;
                LOGPRINT("TelltaleControl::SINGLE_AUDIO_INDEX_TURN_ON");
                audio_client_Play( AUDIO_INDEX_TURN_ON, AUDIO_PLAY);
            }
            if(isClick && (0 == left_change_count || 0 == right_change_count))
            {
                isClick = false;
                //单指示灯 灭
                LOGPRINT("TelltaleControl::SINGLE_AUDIO_INDEX_TURN_OFF");
                audio_client_Play(AUDIO_INDEX_TURN_OFF, AUDIO_PLAY);
            }
        }
    }

    Light_Left_Turn.targetValue = static_cast<char>(showStateLeft);
    _TelltalesStrategy->handleTellStrategy(&Light_Left_Turn);

    Light_Right_Turn.targetValue = static_cast<char>(showStateRight);
    _TelltalesStrategy->handleTellStrategy(&Light_Right_Turn);
}

void TelltalesControl::handleDCDCErr()//DCDC故障
{
    bool showState = false;

    if(g_DcdcFailrLampStsTimeOut == 0x01 || g_DcdcFailrLampLvWarnTimeOut == 0x01){
        Light_DcdcFailrLamp.colorType = COLORTYPE_RED;
        showState = true;
    }
    else{
        if(g_DcdcFailrLampSts == 0x02
                || g_DcdcFailrLampSts == 0x03
                || g_DcdcFailrLampSts == 0x04
                || g_DcdcFailrLampSts == 0x05
                || g_DcdcFailrLampSts == 0x06
                || g_DcdcFailrLampSts == 0x07
                || g_DcdcFailrLampLvWarn == 0x04
                || g_DcdcFailrLampLvWarn == 0x05){
            Light_DcdcFailrLamp.colorType = COLORTYPE_RED;
            showState = true;
        }
        else if(g_DcdcFailrLampLvWarn == 0x03
                || g_DcdcFailrLampLvWarn == 0x02){
            Light_DcdcFailrLamp.colorType = COLORTYPE_YELLOW;
            showState = true;
        }
        else{
            showState = false;
        }
    }

    Light_DcdcFailrLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_DcdcFailrLamp);
}

void TelltalesControl::handleEPBActv()//EPB工作指示灯
{
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;

    if(g_epbLampTimeOut == 0x01 || g_epbFltLampTimeOut == 0x01){
        showState = VISIBLE_true;
    }
    else{
        if(g_EpbLampActv == 0x02
                || g_EpbFltLamp == 0x01
                || g_EpbFltLamp == 0x02){
            showState = VISIBLE_spangle;
        }
        else if(g_EpbLampActv == 0x01){
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_EpbLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_EpbLamp);
}

void TelltalesControl::handleEpbFlt()//EPB故障
{
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;

    if(g_epbFltLampTimeOut == 0x01){
        showState = VISIBLE_true;
    }
    else{
        if(g_EpbFltLamp == 0x02){
            showState = VISIBLE_spangle;
        }
        else if(g_EpbFltLamp == 0x01){
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_EpbFltLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_EpbFltLamp);
}

void TelltalesControl::handleChargeState()//低电量报警
{
    bool showState = false;
    int chargeColor = g_LowPowerWarLamp;

    if(0x01 == g_lowPowerWarLampTimeOut)
    {
        showState = false;
    }
    else{
        if(chargeColor == 1 || chargeColor == 2){//:3green ,2:yellow ,1:red颜色
            showState = true;
        }
        else {
            showState = false;
        }
    }
    Light_LowPowerWarLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_LowPowerWarLamp);
}

int TelltalesControl::getFrontSeatBeltStateLace(){
    int bucDriver = g_BucDriver;
    int bucPass = g_BucPass;
    int occPass = g_OccPass;
    int driver = 0;
    int pass = 0;
    driver = (bucDriver == 1) ? 1 : 0;
    pass = (bucPass == 1 && occPass == 0) ? 1 : 0;
    return (driver<<1) | pass;    // 11
}

TargetValue TelltalesControl::calFrontSeatBeltStrategy()
{
    int timeoutFlag_front = (g_BucDriverTimeOut || g_BucPassTimeOut || g_OccPassTimeOut);
    TargetValue result_front = (TargetValue)Light_Seat_Main.targetValue; //主副驾灯状态

    if(1 == timeoutFlag_front)//超时
    {
        result_front = VISIBLE_true;
        seatBeltStateWarning_front = 0;
#ifdef SEATBELTSOUND
        seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
        seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
        seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
        m_Timer_Selt_25secends->stop();
        m_Timer_Selt_95secends->stop();
    }
    else{
        seatBeltStateWarning_front = getFrontSeatBeltStateLace();//获取前排报警状态
        if(g_Gear == "R" || g_Gear == "P")//档位条件不满足或系上
        {
            if(result_front != VISIBLE_false)
            {
                result_front = VISIBLE_true;
            }
            isNeedRepeatAlarm = false;
#ifdef SEATBELTSOUND
            seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
            seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
            seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
            m_Timer_Selt_25secends->stop();
            m_Timer_Selt_95secends->stop();
        }
        else if(seatBeltStateWarning_front == 0)
        {
            result_front = VISIBLE_false;
            if(seatBeltStateWarning_back == 0){
                isNeedRepeatAlarm = false;
#ifdef SEATBELTSOUND
                seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
                seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
                m_Timer_Selt_25secends->stop();
                m_Timer_Selt_95secends->stop();
            }
        }
        else{
            if(!isNeedRepeatAlarm){
                if(g_vehicleSpeed < 25)//速度小于等于25 警告标志点亮（常亮） 无警告声音
                {
                    result_front = VISIBLE_true; //点亮灯
#ifdef SEATBELTSOUND
                    seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
                }
                else if(g_vehicleSpeed >= 25 && g_vehicleSpeed < 40)//速度 大于25 小于等于40
                {
                    result_front = VISIBLE_spangle; //灯闪烁
                    if((isSeatbeltSoundPause||!m_Timer_Selt_25secends->running()) &&
                            !m_Timer_Selt_95secends->running())//未开始
                    {
                        m_Timer_Selt_25secends->start();
#ifdef SEATBELTSOUND
                        seltAudioCommon(SHORT_AUDIO, AUDIO_PLAY);
                        isSeatbeltSoundPause = false;
#endif
                    }
                }
                else{
                    result_front = VISIBLE_spangle; //灯闪烁
                    if(m_Timer_Selt_25secends->running())//未开始
                    {
                        m_Timer_Selt_25secends->stop();
#ifdef SEATBELTSOUND
                        seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                        seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
#endif
                    }
                    if((isSeatbeltSoundPause||!m_Timer_Selt_95secends->running())){
                        m_Timer_Selt_95secends->start();
#ifdef SEATBELTSOUND
                        seltAudioCommon(LONG_AUDIO_2, AUDIO_PLAY);

                        isSeatbeltSoundPause = false;
#endif
                    }

                }
            }
            else{
                if(!m_Timer_Selt_25secends->running() &&
                        !m_Timer_Selt_95secends->running())
                {
                    result_front = VISIBLE_true; //点亮灯
                    seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
                }
            }
        }
    }
    return result_front;
}

int TelltalesControl::getBackSeatBeltStateLace()
{
    {
        int bucLeft = g_BucLeft;
        int occLeft = g_OccLeft;

        int bucMid = g_BucMid;
        int occMid = g_OccMid;

        int bucaRight = g_BucRight;
        int occRight = g_OccRight;

        if(bucLeft == 1)
        {
            setPropertyValue(PROPERTYID_LEFT_NOTFASTEN,VISIBLE_true);
        }
        else{
            setPropertyValue(PROPERTYID_LEFT_NOTFASTEN,VISIBLE_false);
        }

        if(bucMid == 1)
        {
            setPropertyValue(PROPERTYID_MID_NOTFASTEN,VISIBLE_true);
        }
        else{
            setPropertyValue(PROPERTYID_MID_NOTFASTEN,VISIBLE_false);
        }

        if(bucaRight == 1)
        {
            setPropertyValue(PROPERTYID_RIGHT_NOTFASTEN,VISIBLE_true);
        }
        else{
            setPropertyValue(PROPERTYID_RIGHT_NOTFASTEN,VISIBLE_false);
        }


        if(occLeft == 0)
        {
            setPropertyValue(PROPERTYID_LEFT_SEATEMPTY,VISIBLE_false);
        }
        else{
            setPropertyValue(PROPERTYID_LEFT_SEATEMPTY,VISIBLE_true);
        }

        if(occMid == 0)
        {
            setPropertyValue(PROPERTYID_MID_SEATEMPTY,VISIBLE_false);
        }
        else{
            setPropertyValue(PROPERTYID_MID_SEATEMPTY,VISIBLE_true);
        }

        if(occRight == 0)
        {
            setPropertyValue(PROPERTYID_RIGHT_SEATEMPTY,VISIBLE_false);
        }
        else{
            setPropertyValue(PROPERTYID_RIGHT_SEATEMPTY,VISIBLE_true);
        }

        int left = 0;
        int mid = 0;
        int right = 0;
        if(bucLeft == 1 && occLeft == 0){//后左未系
            left = 1;
        }
        if(bucMid == 1 && occMid == 0){//后中未系
            mid = 1;
        }
        if(bucaRight == 1 && occRight == 0){//后右未系
            right = 1;
        }
        return (left<<2) | (mid<<1) | right;    // 111
    }
}

TargetValue TelltalesControl::calcBackSeatBeltStrategy()
{
    int timeoutFlag_back = (g_BucLeftTimeOut || g_OccLeftTimeOut || g_BucMidTimeOut || g_OccMidTimeOut || g_BucRightTimeOut || g_OccRightTimeOut);
    TargetValue result_back = (TargetValue)Light_Seat_BACK.targetValue; //后排灯状态

    //如果信号正常
    if(1 == timeoutFlag_back)
    {
        result_back = VISIBLE_true;
        seatBeltStateWarning_back = 0;
        setPropertyValue(PROPERTYID_LEFT_NOTFASTEN,VISIBLE_true);//角标都是红色
        setPropertyValue(PROPERTYID_MID_NOTFASTEN,VISIBLE_true);
        setPropertyValue(PROPERTYID_RIGHT_NOTFASTEN,VISIBLE_true);

        setPropertyValue(PROPERTYID_LEFT_SEATEMPTY,VISIBLE_false);
        setPropertyValue(PROPERTYID_MID_SEATEMPTY,VISIBLE_false);
        setPropertyValue(PROPERTYID_RIGHT_SEATEMPTY,VISIBLE_false);
#ifdef SEATBELTSOUND
        seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
        seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
        seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
        m_Timer_Selt_25secends->stop();
        m_Timer_Selt_95secends->stop();


    }
    else{
        seatBeltStateWarning_back = getBackSeatBeltStateLace();//获取当前报警状态
        if(g_Gear == "R" || g_Gear == "P")//档位条件不满足或系上
        {
            if(result_back != VISIBLE_false)
            {
                result_back = VISIBLE_true;
            }
            isNeedRepeatAlarm = false;
#ifdef SEATBELTSOUND
            seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
            seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
            seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
            m_Timer_Selt_25secends->stop();
            m_Timer_Selt_95secends->stop();
        }
        else if(seatBeltStateWarning_back == 0)
        {
            result_back = VISIBLE_false;
            if(seatBeltStateWarning_front == 0){
                isNeedRepeatAlarm = false;
#ifdef SEATBELTSOUND
                seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
                seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
                m_Timer_Selt_25secends->stop();
                m_Timer_Selt_95secends->stop();
            }
        }
        else{
            if(!isNeedRepeatAlarm){
                if(g_vehicleSpeed < 25)//速度小于等于25 警告标志点亮（常亮） 无警告声音
                {
                    result_back = VISIBLE_true; //点亮灯
#ifdef SEATBELTSOUND
                    seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);
#endif
                }
                else if(g_vehicleSpeed >= 25 && g_vehicleSpeed < 40)//速度 大于25 小于等于40
                {
                    result_back = VISIBLE_spangle; //灯闪烁
                    if((isSeatbeltSoundPause||!m_Timer_Selt_25secends->running()) &&
                            !m_Timer_Selt_95secends->running())//未开始
                    {
                        m_Timer_Selt_25secends->start();
#ifdef SEATBELTSOUND
                        seltAudioCommon(SHORT_AUDIO, AUDIO_PLAY);
                        isSeatbeltSoundPause = false;
#endif
                    }
                }
                else{
                    result_back = VISIBLE_spangle; //灯闪烁
                    if(m_Timer_Selt_25secends->running())//未开始
                    {
                        m_Timer_Selt_25secends->stop();
#ifdef SEATBELTSOUND
                        seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                        seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
#endif
                    }
                    if(isSeatbeltSoundPause||!m_Timer_Selt_95secends->running()){
                        m_Timer_Selt_95secends->start();
#ifdef SEATBELTSOUND
                        seltAudioCommon(LONG_AUDIO_2, AUDIO_PLAY);
                        isSeatbeltSoundPause = false;
#endif
                    }
                }
            }
            else{
                if(!m_Timer_Selt_25secends->running() &&
                        !m_Timer_Selt_95secends->running())
                {
                    result_back = VISIBLE_true; //点亮灯
#ifdef SEATBELTSOUND
                    seltAudioCommon(SHORT_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO, AUDIO_STOP);
                    seltAudioCommon(LONG_AUDIO_2, AUDIO_STOP);

#endif
                }
            }
        }
    }
    return result_back;
}

void TelltalesControl::handleSeatBelt()
{
    TargetValue backResult = calcBackSeatBeltStrategy();//后座安全带

    Light_Seat_BACK.targetValue = backResult;
    _TelltalesStrategy->handleTellStrategy(&Light_Seat_BACK);

    TargetValue frontResult = calFrontSeatBeltStrategy();//主副驾安全带

    Light_Seat_Main.targetValue = frontResult;
    _TelltalesStrategy->handleTellStrategy(&Light_Seat_Main);

}

void TelltalesControl::handleBatteryHeat()//动力电池过温告警
{
    bool showState = VISIBLE_false;
    if(g_batteryHeatCriticalTimeOut == 0x01)
    {
        showState = VISIBLE_true;
    }
    else{
        if(g_BatteryHeatCritical == 0x01
                || g_BatteryHeatCritical == 0x02
                || g_BatteryHeatRunaway == 0x01)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }
    Light_BatteryHeat.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_BatteryHeat);
}

void TelltalesControl::handleESCTCS()//ESC/TCS指示灯
{
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;
    if(0x01 == g_TCSTimeOut || 0x01 == g_ESCTimeOut)
    {
        showState = VISIBLE_true;
    }
    else{
        if(0x02 == g_TCS || 0x02 == g_ESC)
        {
            showState = VISIBLE_spangle;
        }
        else if(0x01 == g_TCS || 0x01 == g_ESC)
        {
            showState = VISIBLE_true;
        }
        else if(0x03 == g_TCS || 0x03 == g_ESC)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_ESCTCS.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_ESCTCS);
}

void TelltalesControl::handleTireLamp()//胎压
{
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;
    if(0x01 == g_TireStsTimeOut || 0x01 == g_TireSysStsTimeOut)
    {
        showState = VISIBLE_true;
    }
    else{
        if(0x01 == g_TireSts || 0x01 == g_TireSysSts)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }
    Light_Tire.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_Tire);
}

void TelltalesControl::handleEBDFault()//EBD故障
{
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;
    if(g_EBDFaultCtrlrAvlEbdTimeOut == 0x01
            || g_EBDFaultReqBrkSysTimeOut == 0x01
            || g_EBDFaultBrkFldLvlDispTimeOut == 0x01
            || g_EBDFaultReqiboosterFltTimeOut == 0x01)
    {
        Light_EBDFault.colorType = COLORTYPE_RED;
        showState = VISIBLE_true;
    }
    else{
        if(g_EBDFaultCtrlrAvlEbd == 0x00
                || g_EBDFaultCtrlrAvlEbd == 0x03
                || g_EBDFaultReqBrkSys == 0x02
                || g_EBDFaultReqBrkSys == 0x03
                || g_EBDFaultBrkFldLvlDisp == 0x01)
        {
            Light_EBDFault.colorType = COLORTYPE_RED;
            showState = VISIBLE_true;
        }
        else if(g_EBDFaultReqBrkSys == 0x01
                || g_EBDFaultReqiboosterFlt == 0x01){
            Light_EBDFault.colorType = COLORTYPE_YELLOW;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_EBDFault.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_EBDFault);
}

void TelltalesControl::handleSpeedLimit()
{
    int showState = VISIBLE_false;
    int limitCancel_showState = VISIBLE_false;

    static int TSR_Speed = 0;
    int ACC_Speed = (g_CurveSpeed + 30 )/5 *5;//过弯时的提醒限速,需向下取整到个位0或5
    int show_speed = min(TSR_Speed,ACC_Speed);//CSA的速度值取整后，再与TSR的速度值做比较，仪表的限速显示更小的值

    if(0x01 == g_CurveSpeedTimeOut || g_LimitSpeedTimeOut || 0x01 == g_TSROffsetTimeOut)
    {//超时不显示
        showState = VISIBLE_false;
        limitCancel_showState = VISIBLE_false;
        g_checkSpeedLimit_10Secends = false;
        m_Timer_SpeedLimit_10secends->stop();
    }
    else{
        if(0x00 == g_LimitSpeed)
        {//不显示
            showState = VISIBLE_false;
            limitCancel_showState = VISIBLE_false;
            g_checkSpeedLimit_10Secends = false;
            m_Timer_SpeedLimit_10secends->stop();
        }
        else{
            if(0x01 == g_LimitSpeed)
            {//cancelled
                if(Light_SpeedLimitLamp.targetValue == VISIBLE_true
                        || Light_SpeedLimitLamp.targetValue == VISIBLE_spangle)
                {
                    if(show_speed == TSR_Speed)//限速来源是TSR
                    {
                        if(0x7F == g_CurveSpeed)
                        {
                            showState = VISIBLE_false;//显示限速取消标志
                            limitCancel_showState = VISIBLE_true;
                            g_checkSpeedLimit_10Secends = false;
                            m_Timer_SpeedLimit_10secends->stop();
                        }
                        else{
                            show_speed = ACC_Speed;
                            limitCancel_showState = VISIBLE_false;
                            showState = compareSpeedLimit(show_speed);//判断常亮/闪烁
                        }
                    }
                    else{//限速来源不是TSR 不显示
                        showState = VISIBLE_false;
                        limitCancel_showState = VISIBLE_false;
                    }
                }
                else{//不显示
                    showState = VISIBLE_false;
                    limitCancel_showState = VISIBLE_false;
                }
            }
            else{
                if(0x7F == g_CurveSpeed)
                {
                    showState = VISIBLE_false;//显示限速取消标志
                    limitCancel_showState = VISIBLE_false;
                    g_checkSpeedLimit_10Secends = false;
                    m_Timer_SpeedLimit_10secends->stop();
                }
                else{
                    TSR_Speed = (g_LimitSpeed - 1) * 5 ;//道路交通标志识别的限速
                    showState = compareSpeedLimit(show_speed);//判断常亮/闪烁
                    limitCancel_showState = VISIBLE_false;
                }
            }
            setPropertyValue(PROPERTYID_SPEED_LIMIT , show_speed);
        }
    }

    Light_SpeedLimitLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_SpeedLimitLamp);

    Light_SpeedLimitCancelLamp.targetValue = static_cast<char>(limitCancel_showState);
    _TelltalesStrategy->handleTellStrategy(&Light_SpeedLimitCancelLamp);
}

int TelltalesControl::compareSpeedLimit(int show_speed)
{
    int showState = VISIBLE_false;
    int Offset_Speed = 0;
    if(g_TSROffset == 0x7F)
    {
        Offset_Speed = 0;
    }
    else{
        Offset_Speed = g_TSROffset + 30;
    }

    if(g_vehicleSpeed >= show_speed + Offset_Speed)
    {//当 实际（显示）车速≥当前显示的限速值+偏移量时，限速需要报警
        //需要报警
        if(g_checkSpeedLimit_10Secends)//闪烁满10s
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_spangle;
            if(m_Timer_SpeedLimit_10secends->running())
            {

            }
            else{
                m_Timer_SpeedLimit_10secends->start();
            }
        }
    }
    else{//常亮
        showState = VISIBLE_true;
        g_checkSpeedLimit_10Secends = false;
        m_Timer_SpeedLimit_10secends->stop();
    }
    return showState;
}

void TelltalesControl::seltAudioCommon(SAFETYBELTAUDIO audio_id,Audio_ReqCmd audio_Cmd){
    //    static bool frontAudio = false;
    //    static bool backAudio = false;

    //    bool state = (audio_Cmd == AUDIO_PLAY);

    //    if(audio_id == FRONT_AUDIO){
    //        frontAudio = state;
    //    }
    //    else if(audio_id == BACK_AUDIO){
    //        backAudio = state;
    //    }
    //    else{
    //    }

    //    if(frontAudio||backAudio){
    //        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_TELL_SEAT, AUDIO_INDEX_MAIN_SAFETYBELT,AUDIO_PLAY);
    //        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_SEATBELT, 1);
    //    }
    //    else{
    //        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_TELL_SEAT, AUDIO_INDEX_MAIN_SAFETYBELT,AUDIO_STOP);
    //        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_SEATBELT, 0);
    //    }

    static bool shortAudio = false;
    static bool longAudio = false;
    static bool longAudio_2 = false;

    bool state = (audio_Cmd == AUDIO_PLAY);

    if(audio_id == SHORT_AUDIO)
    {
        if(shortAudio!=state)
        {
            shortAudio = state;
            if(state){
                audio_client_Play( AUDIO_INDEX_SEATBELT_LEVEL_L, AUDIO_PLAY);
            }else{
                audio_client_Play( AUDIO_INDEX_SEATBELT_LEVEL_L, AUDIO_STOP);
            }
        }
    }
    if(audio_id == LONG_AUDIO)
    {
        if(longAudio!=state)
        {
            longAudio = state;
            if(state){
                audio_client_Play( AUDIO_INDEX_SEATBELT_LEVEL_M, AUDIO_PLAY);
            }else{
                audio_client_Play( AUDIO_INDEX_SEATBELT_LEVEL_M, AUDIO_STOP);
            }
        }
    }
    if(audio_id == LONG_AUDIO_2)
    {
        if(longAudio_2!=state)
        {
            longAudio_2 = state;
            if(state){
                audio_client_Play( AUDIO_INDEX_SEATBELT_LEVEL_H, AUDIO_PLAY);
            }else{
                audio_client_Play( AUDIO_INDEX_SEATBELT_LEVEL_H, AUDIO_STOP);
            }
        }
    }
    if(shortAudio || longAudio || longAudio_2)
    {
        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_SEATBELT, 1);
    }
    else{
        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_SEATBELT, 0);
    }
}

void TelltalesControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    if ( HMI_MSGNAME_VEHICLESPEED == message_key ) {
        if(0xFFFF == message_value.toInt()){
            g_vehicleSpeed = 0;
        }
        else{
            g_vehicleSpeed = message_value.toInt();
        }
        handleSeatBelt();
        handleSpeedLimit();
    }
    else {
        // Nothing
    }
}

void TelltalesControl::receiveDateFromOtherProcess(QString name, QVariant value)
{
    if(name == HMI_SHREMEMORY_CMD_POWER_MODE){
        qInfo()<<"name:"<<name<<"value:"<<value;
        g_powermode = value.toInt();

        //优先自检,防止灯在自检前显示
        g_tell_ctrlPowerMode = value.toInt();
        //m_cruiseTimer stop 重新报警
        g_cruise_Target_Speed = "";
        //autocheck
        _TelltalesStrategy->triggerPowerMode(g_powermode);
        g_checkSpeedLimit_10Secends = false;
    }
    else if(name == HMI_SHREMEMORY_CMD_AUTOCHECK){
        _TelltalesStrategy->setAutoCheckState(value.toInt());
    }
    else if(name == HMI_SHREMEMORY_CMD_Gear)
    {
        g_Gear = value.toString();
    }
}

void TelltalesControl::get_timeout500ms()
{
    _TelltalesStrategy->get_timeout500ms();
    m_Timer_Selt_25secends->update();
    m_Timer_Selt_95secends->update();
    m_Timer_SpeedLimit_10secends->update();
    //    qInfo()<<"@@@@@@@@@@@";
    //    emit PropertyChange(PROPERTYID_TurnLeftLamp, new TellData(1,3));
}

void TelltalesControl::get_timeout100ms()
{

}

void TelltalesControl::get_timeout10ms()
{
    QMutexLocker _locker(&mutex);
    Q_UNUSED(_locker);
    _TelltalesStrategy->get_timeout10ms();
}

void TelltalesControl::func_MSG_LowPowerWarLamp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LowPowerWarLamp,msg)
    g_LowPowerWarLamp = msg.value;
    handleChargeState();
}

void TelltalesControl::func_MSG_LowPowerWarLampTimeOut()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LowPowerWarLampTimeOut,msg)
    g_lowPowerWarLampTimeOut = msg.isTimeout;
    handleChargeState();
}

void TelltalesControl::func_MSG_CoolantAlarmLamp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CoolantAlarmLamp,msg)
    bool showState = false;

    if(msg.isTimeout == 0x01)
    {
        return;//状态保持
    }
    else{
        if(msg.value == 0x01 || msg.value == 0x02 || msg.value == 0x03)
        {
            showState = true;
        }
        else{
            showState = false;
        }
    }

    Light_CoolantAlarmLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_CoolantAlarmLamp);
}

void TelltalesControl::func_MSG_EMotorAlarm()//电机系统故障
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EMotorAlarm,msg)
    bool showState = false;

    if(msg.isTimeout == 0x01){
        showState = true;
    }
    else{
        if(msg.value == 0x01 || msg.value == 0x02)
        {
            showState = true;
        }
        else if(msg.value == 0x00)
        {
            showState = false;
        }
        else{}
    }

    Light_EMotorAlarm.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_EMotorAlarm);
}

void TelltalesControl::func_MSG_SystemFailureLamp()//动力系统故障
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SystemFailureLamp,msg)
    int showState = VISIBLE_false;

    if(msg.isTimeout == 0x01){
        showState = VISIBLE_true;
    }
    else{
        if(msg.value == 0x01){
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_SystemFailureLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_SystemFailureLamp);
}

void TelltalesControl::func_MSG_SysPowerLimitationLamp()//车辆限功率提示
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SysPowerLimitationLamp,msg)
    bool showState = false;

    if(msg.isTimeout == 0x01){
        showState = true;
    }
    else{
        if(msg.value == 0x01){
            showState = true;
        }
        else{
            showState = false;
        }
    }

    Light_SysPowerLimitationLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_SysPowerLimitationLamp);
}

void TelltalesControl::func_MSG_BatteryHeatCritical()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BatteryHeatCritical,msg)
    g_batteryHeatCriticalTimeOut = msg.isTimeout;
    g_BatteryHeatCritical = msg.value;
    handleBatteryHeat();//动力电池过热
}

void TelltalesControl::func_MSG_BatteryHeatRunaway()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BatteryHeatRunaway,msg)
    g_BatteryHeatRunaway = msg.value;
    handleBatteryHeat();//动力电池过热
}

void TelltalesControl::func_MSG_Left_Turn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_Left_Turn,msg)
    g_LeftTurnTimeOut = msg.isTimeout;
    g_Left_Turn = msg.value;
    handleTurnLamp();
    if(!msg.isTimeout){
        g_Left_Turn_Backup = msg.value;
    }
}

void TelltalesControl::func_MSG_Right_Turn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_Right_Turn,msg)
    g_RightTurnTimeOut = msg.isTimeout;
    g_Right_Turn = msg.value;
    handleTurnLamp();
    if(!msg.isTimeout){
        g_Right_Turn_Backup = msg.value;
    }
}

void TelltalesControl::func_MSG_LowBeamLamp()//近光灯
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LowBeamLamp,msg)
    bool showStateLow = false;

    if(msg.isTimeout == 0x01){
        showStateLow = false;
    }
    else{
        if(msg.value == 0x01){//近光灯
            showStateLow = true;
        }
        else{
            showStateLow = false;
        }
    }

    Light_LowBeamLamp.targetValue = static_cast<char>(showStateLow);
    _TelltalesStrategy->handleTellStrategy(&Light_LowBeamLamp);
}

void TelltalesControl::func_MSG_HighBeamLamp()//远光灯
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HighBeamLamp,msg)
    bool showStateHigh = false;

    if(msg.isTimeout == 0x01){
        showStateHigh = false;
    }
    else{
        if(msg.value == 0x02 || msg.value == 0x03){//远光灯
            showStateHigh = true;
        }
        else{
            showStateHigh = false;
        }
    }

    Light_HighBeamLamp.targetValue = static_cast<char>(showStateHigh);
    _TelltalesStrategy->handleTellStrategy(&Light_HighBeamLamp);
}

void TelltalesControl::func_MSG_PosiLamp()//位置灯
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_PosiLamp,msg)
    bool showState = false;

    if(msg.isTimeout == 0x01){
        showState = false;
    }
    else if(msg.value == 0x00){
        showState = false;
    }
    else if(msg.value == 0x01){
        showState = true;
    }
    else{
        //nothing
    }

    Light_PosiLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_PosiLamp);
}

void TelltalesControl::func_MSG_FogLamp()//后雾灯
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_FogLamp,msg)
    bool showState = VISIBLE_false;
    if(msg.isTimeout == 0x01)
    {
        showState = VISIBLE_false;
    }
    else{
        if(msg.value == 0x01)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }
    Light_FogLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_FogLamp);
}

void TelltalesControl::func_MSG_ESC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ESC,msg)
    g_ESCTimeOut = msg.isTimeout;
    g_ESC = msg.value;
    handleESCTCS();
}

void TelltalesControl::func_MSG_TCS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TCS,msg)
    g_TCSTimeOut = msg.isTimeout;
    g_TCS = msg.value;
    handleESCTCS();
}

void TelltalesControl::func_MSG_EBDFaultReqBrkSys()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EBDFaultReqBrkSys,msg)
    g_EBDFaultReqBrkSysTimeOut = msg.isTimeout;
    g_EBDFaultReqBrkSys = msg.value;
    handleEBDFault();
}

void TelltalesControl::func_MSG_EBDFaultCtrlrAvlEbd()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EBDFaultCtrlrAvlEbd,msg)
    g_EBDFaultCtrlrAvlEbdTimeOut = msg.isTimeout;
    g_EBDFaultCtrlrAvlEbd = msg.value;
    handleEBDFault();
}

void TelltalesControl::func_MSG_EBDFaultBrkFldLvlDisp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EBDFaultBrkFldLvlDisp,msg)
    g_EBDFaultBrkFldLvlDispTimeOut = msg.isTimeout;
    g_EBDFaultBrkFldLvlDisp = msg.value;
    handleEBDFault();
}

void TelltalesControl::func_MSG_EBDFaultReqiboosterFlt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EBDFaultReqiboosterFlt,msg)
    g_EBDFaultReqiboosterFltTimeOut = msg.isTimeout;
    g_EBDFaultReqiboosterFlt = msg.value;
    handleEBDFault();
}

void TelltalesControl::func_MSG_EpbLampActv()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EpbLampActv,msg)
    g_epbLampTimeOut = msg.isTimeout;
    g_EpbLampActv = msg.value;
    handleEPBActv();
}

void TelltalesControl::func_MSG_EpbFltLamp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EpbFltLamp,msg)
    g_epbFltLampTimeOut = msg.isTimeout;
    g_EpbFltLamp = msg.value;
    handleEPBActv();
    handleEpbFlt();
}

void TelltalesControl::func_MSG_HDC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HDC,msg)
    int showState = VISIBLE_false;

    if(msg.isTimeout == 0x01)
    {
        showState = VISIBLE_false;
    }
    else{
        if(msg.value == 0x01)
        {
            Light_HDC.colorType = COLORTYPE_GREEN;
            showState = VISIBLE_spangle;
        }
        else if(msg.value == 0x02)
        {
            Light_HDC.colorType = COLORTYPE_GREEN;
            showState = VISIBLE_true;
        }
        else if(msg.value == 0x03)
        {
            Light_HDC.colorType = COLORTYPE_YELLOW;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_HDC.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_HDC);
}

void TelltalesControl::func_MSG_EPSFault()//EPS故障
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EPSFault,msg)
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    bool showState = false;

    if(msg.isTimeout == 0x01){
        Light_EPSFault.colorType = COLORTYPE_RED;
        showState = true;
    }
    else{
        if(msg.value == 0x01)
        {
            Light_EPSFault.colorType = COLORTYPE_YELLOW;
            showState = true;
        }
        else if(msg.value == 0x02)
        {
            Light_EPSFault.colorType = COLORTYPE_RED;
            showState = true;
        }
        else{
            showState = false;
        }
    }

    Light_EPSFault.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_EPSFault);
}

void TelltalesControl::func_MSG_SEAT_BELT()
{
    SingleMessage msg;
    if(getMsgValue(MSG_BucLeft,msg)){
        g_BucLeftTimeOut = msg.isTimeout;
        g_BucLeft = msg.value;
    }

    if(getMsgValue(MSG_OccLeft,msg)){
        g_OccLeftTimeOut = msg.isTimeout;
        g_OccLeft = msg.value;
    }

    if(getMsgValue(MSG_BucMid,msg)){
        g_BucMidTimeOut = msg.isTimeout;
        g_BucMid = msg.value;
    }

    if(getMsgValue(MSG_OccMid,msg)){
        g_OccMidTimeOut = msg.isTimeout;
        g_OccMid = msg.value;
    }

    if(getMsgValue(MSG_BucRight,msg)){
        g_BucRightTimeOut = msg.isTimeout;
        g_BucRight = msg.value;
    }

    if(getMsgValue(MSG_OccRight,msg)){
        g_OccRightTimeOut = msg.isTimeout;
        g_OccRight = msg.value;
    }

    if(getMsgValue(MSG_BucDriver,msg)){
        g_BucDriverTimeOut = msg.isTimeout;
        g_BucDriver = msg.value;
    }

    if(getMsgValue(MSG_BucPass,msg)){
        g_BucPassTimeOut = msg.isTimeout;
        g_BucPass = msg.value;
    }

    if(getMsgValue(MSG_OccPass,msg)){
        g_OccPassTimeOut = msg.isTimeout;
        g_OccPass = msg.value;
    }

    handleSeatBelt();
}

void TelltalesControl::func_MSG_AirbagLamp()//安全气囊
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AirbagLamp,msg)
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;
    if(msg.isTimeout == 0x01)
    {
        showState = VISIBLE_true;
    }
    else{
        if(msg.value == 0x01)
        {
            showState = VISIBLE_true;
        }
        else if(msg.value == 0x02)
        {
            showState = VISIBLE_spangle;
        }
        else if(msg.value == 0x00)
        {
            showState = VISIBLE_false;
        }
        else{}
    }
    Light_AirbagLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_AirbagLamp);
}

void TelltalesControl::func_MSG_TCSOff()//ESC/TCS off指示灯
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TCSOff,msg)
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;
    if(0x01 == msg.isTimeout)
    {
        showState = VISIBLE_true;
    }
    else{
        if(0x01 == msg.value)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_ESCTCSOff.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_ESCTCSOff);
}

void TelltalesControl::func_MSG_ABSLamp()//制动防抱死功能故障
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ABSLamp,msg)
    if(_TelltalesStrategy->getAutoCheckState() == AUTOCHECK_START) return;
    int showState = VISIBLE_false;
    if(0x01 == msg.isTimeout)
    {
        showState = VISIBLE_true;
    }
    else{
        if(0x01 == msg.value || msg.value == 0x3)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_ABSLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_ABSLamp);
}

void TelltalesControl::func_MSG_AVH()//AVH工作中 绿色
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AVH,msg)
    int showState = VISIBLE_false;
    if(0x01 == msg.isTimeout)
    {
        Light_AVH.colorType = COLORTYPE_YELLOW;
        showState = VISIBLE_true;
    }
    else{
        if(0x01 == msg.value)
        {
            Light_AVH.colorType = COLORTYPE_WHITE;
            showState = VISIBLE_true;
        }
        else if(0x02 == msg.value)
        {
            Light_AVH.colorType = COLORTYPE_GREEN;
            showState = VISIBLE_true;
        }
        else if(0x03 == msg.value)
        {
            Light_AVH.colorType = COLORTYPE_YELLOW;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_AVH.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_AVH);
}

void TelltalesControl::func_MSG_AirSuspension_Fault()//空气悬架故障
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AirSuspension_Fault,msg)
    int showState = VISIBLE_false;
    if(0x01 == msg.isTimeout)
    {
        Light_AirSuspension_Fault.colorType = COLORTYPE_RED;
        showState = VISIBLE_true;
    }
    else{
        if(0x01 == msg.value)
        {
            Light_AirSuspension_Fault.colorType = COLORTYPE_RED;
            showState = VISIBLE_true;
        }
        else if(0x02 == msg.value || 0x03 == msg.value)
        {
            Light_AirSuspension_Fault.colorType = COLORTYPE_YELLOW;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }
    Light_AirSuspension_Fault.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_AirSuspension_Fault);
}

void TelltalesControl::func_MSG_TireSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TireSts,msg)
    g_TireStsTimeOut = msg.isTimeout;
    g_TireSts = msg.value;
    handleTireLamp();
}

void TelltalesControl::func_MSG_TireSysSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TireSysSts,msg)
    g_TireSysStsTimeOut = msg.isTimeout;
    g_TireSysSts = msg.value;
    handleTireLamp();
}

void TelltalesControl::func_MSG_Frontbonnetfault()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_Frontbonnetfault,msg)
    int showState = VISIBLE_false;
    if(msg.isTimeout == 0x01)
    {
        showState = VISIBLE_false;
    }
    else{
        if(msg.value == 0x01 || msg.value == 0x02)
        {
            showState = VISIBLE_true;
        }
        else if(msg.value == 0x00 || msg.value == 0x03)
        {
            showState = VISIBLE_false;
        }
        else{}
    }

    Light_Frontbonnetfault.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_Frontbonnetfault);
}

void TelltalesControl::func_MSG_LowSpeedLamp()//低速行人报警
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LowSpeedLamp,msg)
    int showState = VISIBLE_false;
    if(0x01 == msg.isTimeout)
    {
        showState = VISIBLE_false;
    }
    else{
        if(0x00 == msg.value)
        {
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }
    Light_LowSpeedLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_LowSpeedLamp);
}

void TelltalesControl::func_MSG_BMSFault()//BMS电池故障
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BMSFault,msg)
    bool showState = false;

    if(msg.isTimeout == 0x01){
        showState = true;
    }
    else{
       if(msg.value == 0x05 || msg.value == 0x06 || msg.value == 0x07){
            showState = true;
       }
    }

    Light_BMSFault.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_BMSFault);
}

void TelltalesControl::func_MSG_DcdcFailrLampSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DcdcFailrLampSts,msg)
    g_DcdcFailrLampStsTimeOut = msg.isTimeout;
    g_DcdcFailrLampSts = msg.value;
    handleDCDCErr();
}

void TelltalesControl::func_MSG_DcdcFailrLampLvWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DcdcFailrLampLvWarn,msg)
    g_DcdcFailrLampLvWarnTimeOut = msg.isTimeout;
    g_DcdcFailrLampLvWarn = msg.value;
    handleDCDCErr();
}

void TelltalesControl::func_MSG_ChargingTimeout()//车辆续驶里程显示灯
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ChargingTimeout,msg)
    int showState = VISIBLE_false;
    if(0x01 == msg.isTimeout)
    {
        showState = VISIBLE_false;
    }
    else{
        showState = VISIBLE_true;
    }
    Light_Charging.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_Charging);
}

void TelltalesControl::func_MSG_Wiperfault()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_Wiperfault,msg)
    int showState = VISIBLE_false;
    if(msg.isTimeout == 0x01)
    {
        showState = VISIBLE_true;
    }
    else{
        if(msg.value == 0x00)
        {
            showState = VISIBLE_false;
        }
        else if(msg.value == 0x01)
        {
            showState = VISIBLE_true;
        }
        else{}
    }

    Light_Wiperfault.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_Wiperfault);
}

void TelltalesControl::func_MSG_AccStatusLamp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AccStatusLamp,msg)
    int showState = VISIBLE_false;
    if(msg.isTimeout == 0x01)
    {
        showState = VISIBLE_false;
    }
    else{
        if(msg.value == 0x02)
        {
            Light_AccStatusLamp.colorType = COLORTYPE_GRAY;
            showState = VISIBLE_true;
        }
        else if(msg.value == 0x03
                || msg.value == 0x04
                || msg.value == 0x06)
        {
            Light_AccStatusLamp.colorType = COLORTYPE_BLUE;
            showState = VISIBLE_true;
        }
        else if(msg.value == 0x05)
        {
            Light_AccStatusLamp.colorType = COLORTYPE_BLUE;
            showState = VISIBLE_spangle;
        }
        else if(msg.value == 0x07)
        {
            Light_AccStatusLamp.colorType = COLORTYPE_YELLOW;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_AccStatusLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_AccStatusLamp);
}

void TelltalesControl::func_MSG_CurveSpeed()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CurveSpeed,msg)
    g_CurveSpeedTimeOut = msg.isTimeout;
    g_CurveSpeed = msg.value;
    handleSpeedLimit();
}

void TelltalesControl::func_MSG_LimitSpeed()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LimitSpeed,msg)
    g_LimitSpeedTimeOut = msg.isTimeout;
    g_LimitSpeed = msg.value;
    handleSpeedLimit();
}

void TelltalesControl::func_MSG_TSROffset()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TSROffset,msg)
    g_TSROffsetTimeOut = msg.isTimeout;
    g_TSROffset = msg.value;
    handleSpeedLimit();
}

void TelltalesControl::func_MSG_AutoLamp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AutoLamp,msg)
    int showState = VISIBLE_false;
    if(msg.isTimeout)
    {
        showState = VISIBLE_false;
    }
    else{
        if(0x01 == msg.value)
        {
            Light_AutoLamp.colorType = COLORTYPE_WHITE;
            showState = VISIBLE_true;
        }
        else if(0x02 == msg.value)
        {
            Light_AutoLamp.colorType = COLORTYPE_BLUE;
            showState = VISIBLE_true;
        }
        else if(0x03 == msg.value)
        {
            Light_AutoLamp.colorType = COLORTYPE_RED;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_AutoLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_AutoLamp);
}

void TelltalesControl::func_MSG_ACCTargetSpeed()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ACCTargetSpeed,msg)
    QString ADAS_ACC_TargetSpeed = "";
    if(msg.value == 0x7F)
    {
        ADAS_ACC_TargetSpeed = "--";
    }
    else{
        ADAS_ACC_TargetSpeed = QString::number(msg.value + 30);
    }

    setPropertyValue(PROPERTYID_ACC_SPEED , ADAS_ACC_TargetSpeed);
}

void TelltalesControl::func_MSG_HWAStatusLamp()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HWAStatusLamp,msg)
    int showState = VISIBLE_false;
    if(msg.isTimeout)
    {
        showState = VISIBLE_false;
    }
    else{
        if(0x02 == msg.value)
        {
            Light_HWAStatusLamp.colorType = COLORTYPE_GRAY;
            showState = VISIBLE_true;
        }
        else if(0x03 == msg.value
                || 0x04 == msg.value
                || 0x06 == msg.value)
        {
            Light_HWAStatusLamp.colorType = COLORTYPE_BLUE;
            showState = VISIBLE_true;
        }
        else if(0x05 == msg.value)
        {
            Light_HWAStatusLamp.colorType = COLORTYPE_BLUE;
            showState = VISIBLE_spangle;
        }
        else if(0x07 == msg.value)
        {
            Light_HWAStatusLamp.colorType = COLORTYPE_YELLOW;
            showState = VISIBLE_true;
        }
        else{
            showState = VISIBLE_false;
        }
    }

    Light_HWAStatusLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_HWAStatusLamp);
}

void TelltalesControl::func_MSG_ParkLockSts()
{
    SingleMessage msg;
    int showState = VISIBLE_false;
    INIT_SINGLEMESSAGE_VALUE(MSG_ParkLockSts,msg)
    if(msg.isTimeout)
    {
        showState = VISIBLE_false;
    }
    else{
        showState = (msg.value == 3) ? VISIBLE_true : VISIBLE_false;
    }
    Light_ParkLockLamp.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_ParkLockLamp);
}
void TelltalesControl::func_MSG_VCU_VehSrvcWarn()
{
    SingleMessage msg;
    int showState = VISIBLE_false;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_VehSrvcWarn,msg)
    if(msg.isTimeout)
    {
        showState = VISIBLE_false;
    }
    else{
        showState = (msg.value == 0) ? VISIBLE_true : VISIBLE_false;
    }
    Light_VehSrvcWarn.targetValue = static_cast<char>(showState);
    _TelltalesStrategy->handleTellStrategy(&Light_VehSrvcWarn);
}
