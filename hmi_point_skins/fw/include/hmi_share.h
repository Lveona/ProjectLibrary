#ifndef HMI_SHARE_H
#define HMI_SHARE_H

#include "Singleton.h"
#include "BaseControl.h"
#include "BaseScreen.h"

#include <PF_Common.h>
#include <libaudio.h>
#include <libivs.h>
#include <QDateTime>
#ifdef DESKTOP
#else
#include <cls/cls_log.h>
#include <libclsmgrd.h>
#endif

extern int g_hmiPowerMode;

//extern void jkm_log_print(jkm_log_type_em log_type,const char * module_name,const char *format,...);
#ifdef DESKTOP
    #define LOGPRINT(log) \
        qInfo()<<log;
    #define LOGPRINTVALUE(key,value) \
        qInfo()<<QString("%1:%2").arg(key).arg(value);
#else
    #define LOGPRINT(log) \
        jkm_log_print(LOG_INFO,"HMI",log);
    #define LOGPRINTVALUE(key,value) \
        jkm_log_print(LOG_INFO,"HMI", "%s-%lf", key, value);
#endif

#define MAXLENMSG (100)

//2019/12/13
#define HMI_MSGNAME_POWER_MODE              "1"
#define HMI_MSGNAME_VEHICLESPEED            "2"
#define HMI_MSGNAME_OVERSPEED               "3"
#define HMI_MSGNAME_POPWARN                 "4"
#define HMI_MSGNAME_TELLWARN                "5"
#define HMI_SCREEN_STATE                    "6"       //setting off screen at ign off
#define HMI_MSGNAME_AUTOCHECK               "7"
#define HMI_MSGNAME_HAVEREAD                "8"
#define HMI_MSGNAME_ATCHECK_STATE           "9"
enum powerMode {// 电源
    POWERMODE_ANIMATION = 0,          // Opening
    POWERMODE_D1,
    POWERMODE_D2,
    POWERMODE_D3,
};

enum key_number{
//    HDKEY_DOWN = 0,
//    HDKEY_UP,
//    HDKEY_RIGHT,
//    HDKEY_LEFT,
//    HDKEY_OK,
//    HDKEY_RETURN

    HDKEY_RIGHT  = 0x20,
    HDKEY_LEFT   = 0x21,
    HDKEY_DOWN   = 0x22,
    HDKEY_UP     = 0x23,
    HDKEY_OK    = 0x24,
};

enum Key_state{
    KEY_ON = 0x00,     // 短按下
    KEY_OFF,           // 短按下抬起
    KEY_OUT,           // 长按下
    KEY_OUT_OFF        // 长按下抬起
};

enum autoCheck_Status{          // 自检
    AUTOCHECK_INIT = 0,         // 初始值
    AUTOCHECK_START,            // 自检开始
    AUTOCHECK_END               // 自检结束
};

enum themeMode {
    THEMEMODE_INIT = 0,
    THEMEMODE_ECO,              // 科技主题
    THEMEMODE_COMMON,           // 经典主题
    THEMEMODE_SPORT             // 运动主题
};

typedef struct {
    int                 m_messageID;
    QByteArray          m_messageData;
    unsigned char       data_len;
} Parsing_Message;

typedef struct {
    int id;
    unsigned char isTimeout;
    unsigned long int value;
} Parsing_SingleMessage;

typedef enum {
    MSG_NONE = 0x00,
    MSG_SPEED,                     /* Gauge 车辆限功率提示*/
    MSG_ENGPWR,                    /* Gauge 功率*/
    MSG_LowPowerWarLamp,           /* tell 低电量报警报警指示灯颜色*/
    MSG_LowPowerWarLampTimeOut,    /* tell 低电量报警灯超时*/
    MSG_CoolantAlarmLamp,          /* 148 tell 电机/电池冷却液低*/
    MSG_EMotorAlarm,               /* tell 电机系统故障*/
    MSG_SystemFailureLamp,         /* tell 动力系统故障*/
    MSG_SysPowerLimitationLamp,    /* tell 车辆限功率提示*/
    MSG_BatteryHeatCritical,       /* tell 动力电池过温告警*/
    MSG_BatteryHeatRunaway,        /* tell 动力电池过温告警*/
    MSG_Left_Turn,                 /* tell 左转向灯*/
    MSG_Right_Turn,                /* tell 右转向灯*/
    MSG_LowBeamLamp,               /* tell 近光灯提示*/
    MSG_HighBeamLamp,              /* tell 远光灯提示*/
    MSG_PosiLamp,                  /* tell 位置灯指示*/
    MSG_FogLamp,                   /* tell 后雾灯指示灯*/
    MSG_ESC,                       /* tell ESCTCS*/
    MSG_TCS,                       /* tell ESCTCS*/
    MSG_EBDFaultReqBrkSys,         /* tell EBD故障*/
    MSG_EBDFaultCtrlrAvlEbd,       /* tell EBD故障*/
    MSG_EBDFaultBrkFldLvlDisp,     /* tell EBD故障*/
    MSG_EBDFaultReqiboosterFlt,    /* tell EBD故障*/
    MSG_EpbLampActv,               /* tell EPB工作指示灯*/
    MSG_EpbFltLamp,                /* tell EPB/EPB故障工作指示灯*/
    MSG_HDC,                       /* tell HDC指示灯*/
    MSG_EPSFault,                  /* tell EPS故障*/
    MSG_BucLeft,                   /* tell bucLeft*/
    MSG_OccLeft,                   /* tell occLeft*/
    MSG_BucMid,                    /* tell bucMid*/
    MSG_OccMid,                    /* tell occMid*/
    MSG_BucRight,                  /* tell bucRight*/
    MSG_OccRight,                  /* tell occRight*/
    MSG_BucDriver,                 /* tell bucDriver*/
    MSG_BucPass,                   /* tell bucPass*/
    MSG_OccPass,                   /* tell occPass*/
    MSG_AirbagLamp,                /* tell 安全气囊指示灯*/
    MSG_TCSOff,                    /* tell ESCTCSOff*/
    MSG_ABSLamp,                   /* tell ABS故障灯*/
    MSG_AVH,                       /* tell AVH工作中*/
    MSG_AirSuspension_Fault,       /* tell 空气悬架故障*/
    MSG_TireSts,                   /* tell 胎压报警灯*/
    MSG_TireSysSts,                /* tell 胎压报警灯*/
    MSG_Frontbonnetfault,          /* tell 前舱盖未关指示灯*/
    MSG_LowSpeedLamp,              /* tell 低速行人报警*/
    MSG_BMSFault,                  /* tell BMS电池故障*/
    MSG_DcdcFailrLampSts,          /* tell DCDC故障报警提示*/
    MSG_DcdcFailrLampLvWarn,       /* tell DCDC故障报警提示*/
    MSG_ChargingTimeout,           /* tell 车辆续驶里程显示*/
    MSG_Wiperfault,                /* tell 前雨刷故障指示灯*/
    MSG_AccStatusLamp,             /* tell ACC状态指示*/
    MSG_CurveSpeed,                /* tell 限速标志/限速取消标志*/
    MSG_LimitSpeed,                /* tell 限速标志/限速取消标志*/
    MSG_TSROffset,                 /* tell 限速标志/限速取消标志*/
    MSG_AutoLamp,                  /* tell 智能远光指示灯*/
    MSG_ACCTargetSpeed,            /* tell ACCSPEED*/
    MSG_HWAStatusLamp,             /* tell HWA状态指示*/
    MSG_ParkLockSts,               /* tell P档锁故障*/
    MSG_VCU_VehSrvcWarn,           /* tell 动力系统异常*/
} RpcMsgValueId;

extern QMap<RpcMsgValueId,SingleMessage> gMapMsgValues;
extern bool getMsgValue(const RpcMsgValueId& msgId,SingleMessage& message);
//初始化233
#define INIT_SINGLEMESSAGE_VALUE(id,message) if(!getMsgValue(id,message)) return;

enum hmiModule{
    HMI_MID_RECV     = 0x00,
    HMI_MID_POPUP    = 0x01,
    HMI_MID_SYS      = 0x02,
    HMI_MID_GAGUE    = 0x03,
    HMI_MID_ADAS     = 0x04,
    HMI_MID_TELLTALE = 0x05,
    HMI_MID_CARINFO  = 0x06,
    HMI_MID_DIAG     = 0x07,
};

/* Interprocess communication Command */
#define HMI_SHREMEMORY_CMD_POINTSIDP_CTRL               "1"
#define HMI_SHREMEMORY_CMD_DISPLAY_SPEED                "2"
//#define HMI_SHREMEMORY_CMD_DISPLAY_ENGINEROTATION       "3"
#define HMI_SHREMEMORY_CMD_DISPLAY_SOURCE               "4"
#define HMI_SHREMEMORY_CMD_DISPLAY_THEME                "5"
#define HMI_SHREMEMORY_CMD_POWER_MODE                   "6"
#define HMI_SHREMEMORY_CMD_HMI_SCREEN_STATE             "7"
#define HMI_SHREMEMORY_CMD_UINT                         "8"
#define HMI_SHREMEMORY_CMD_CARMODE                      "9"
#define HMI_SHREMEMORY_CMD_LANGUAGE                     "A"
#define HMI_SHREMEMORY_CMD_POINTSIDP_CTRL_UPDATE        "B"
#define HMI_SHREMEMORY_CMD_POINTSIDP_ENTERANIM          "C"
#define HMI_SHREMEMORY_CMD_HMI_SCREEN_DIAG              "D"
#define HMI_SHREMEMORY_CMD_DIAGNOSE_SCREEN              "E"
#define HMI_SHREMEMORY_CMD_Gear                         "F"
#define HMI_SHREMEMORY_CMD_AUTOCHECK                    "10"
#define HMI_SHREMEMORY_CMD_SEATBELT                     "11"
#define HMI_SHREMEMORY_CMD_CHARGING                     "12"
#define HMI_SHREMEMORY_CMD_NAVMAPMOD                    "NAVMAPMOD"
#define HMI_SHREMEMORY_CMD_THEMESETTING                 "THEMESETTING"
//封装一个timer
class HMICustomTimer: public QObject
{
    Q_OBJECT
public:
    HMICustomTimer(int _max, bool _single=true);
    ~HMICustomTimer(){}

    void update();
    void reset();
    void stop();
    void start();
    bool running();
signals:
    void timeout();
private:
    int m_Max;
    int m_timercnt;
    bool m_single;
};

class HMIAudioCtrl: public QObject
{
    Q_OBJECT
public:
    enum WARNING_STATE{
        /*tell*/
        WARNING_STATE_TELL_SEAT = 0,

        /*pop*/
        WARNING_STATE_PWR_BAT_THERMAL_RUNAWAY,
        WARNING_STATE_DOOROPEN,
        WARNING_STATE_POP_TEST,

        WARNING_STATE_MAX
    };

    HMIAudioCtrl();
    ~HMIAudioCtrl(){}
    static void setAudioStatByPower(WARNING_STATE state, int audio_id,Audio_ReqCmd audio_Cmd);

private:

    static void setAudioState(WARNING_STATE state, int audio_id,Audio_ReqCmd audio_Cmd);

};

/* 统计从HMI处理msg开始 到HMI处理完msg结束，一共花费的时间 */
class HMIProcessTime: public QObject
{
    Q_OBJECT
public:
    static void process(QString tag);
private:
    HMIProcessTime(){}
    ~HMIProcessTime(){}

};

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  hmi_lib_AudioPlay
 *  Description:  Audio Request interface(HMI Module DebugLog Track-1)
 *	Return:	None
 *  Param:
            mid:      Pop/Gauge...
            localID:  CustomInfo of The Module
            audio_id: -
            audio_Cmd:-
 *  History:
 *	<!-----	No.		Date		Revised by		Details	------------------------------->
 *          1      2019/05/28    HanYong        Create
 * =====================================================================================
 */
inline void hmi_lib_AudioPlay(hmiModule mid, int localID, Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd){
//    qDebug()<<QTime::currentTime().toString("hh:mm:ss.zzz")<<"hmi_lib_AudioPlay "<<((audio_Cmd == AUDIO_PLAY)?"PLAY":"STOP")<<"audio_id:"<<audio_id <<"MID:"<<mid<<"eventID:"<<localID<<"ThreadId:"<<QThread::currentThreadId()<<"audio_id:"<<audio_id;

    Q_UNUSED(mid)
    Q_UNUSED(localID)

    audio_client_Play(audio_id, audio_Cmd);
}

#endif // HMI_SHARE_H
