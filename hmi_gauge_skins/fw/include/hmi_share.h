#ifndef HMI_SHARE_H
#define HMI_SHARE_H

#include "Singleton.h"
#include "BaseControl.h"
#include "BaseScreen.h"

#include <PF_Common.h>
#include <libaudio.h>
#include <libivp.h>
#include <libivs.h>
#include <pm_proxy.h>
#include <QDateTime>

#ifdef DESKTOP
#else
#include <cls/cls_log.h>
#include <libclsmgrd.h>
#endif
#include <log_proxy.h>

extern int g_hmiPowerMode;
//extern void jkm_log_print(jkm_log_type_em log_type,const char * module_name,const char *format,...);
#ifdef DESKTOP
    #define LOGPRINT(log) \
        qInfo()<<__FILE__<<__FUNCTION__<<log;
    #define LOGPRINTVALUE(key,value) \
        qInfo()<<__FILE__<<__FUNCTION__<<QString("%1:%2").arg(key).arg(value);
    #define LOGPRINTVALUEFLOAT(key,value) \
        qInfo()<<__FILE__<<__FUNCTION__<<QString("%1:%2").arg(key).arg(value);
#else
    #define LOGPRINT(log) \
        jkm_log_print(LOG_INFO,"HMI",log);
    #define LOGPRINTVALUE(key,value) \
        jkm_log_print(LOG_INFO,"HMI", "%s-%d", key, value);
    #define LOGPRINTVALUEFLOAT(key,value) \
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
#define HMI_MSGNAME_VOLUME                  "9"
#define HMI_MSGNAME_SAVEINDEX               "A"
#define HMI_MSGNAME_CARINFOINDEX            "B"
#define HMI_MSGNAME_MAP_MODE                "C"
#define HMI_MSGNAME_THEME                   "D"
#define HMI_MSGNAME_CHARGE_CONN             "E"
#define HMI_MSGNAME_DRIVE_MODE              "F"

enum DIRECTION{
    DIRECTION_BEFORE,
    DIRECTION_AFTER,
};
enum powerMode {// 电源
    POWERMODE_ANIMATION = 0,          // Opening
    POWERMODE_D1,
    POWERMODE_D2,
    POWERMODE_D3,
};

enum key_number{

    HDKEY_RIGHT  = 0x22,
    HDKEY_LEFT   = 0x23,
    HDKEY_DOWN   = 0x20,
    HDKEY_UP     = 0x21,
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
    THEMEMODE_NONE = 0,
    THEMEMODE_COMFORT,       // 舒适主题
    THEMEMODE_ECO,           // 经济主题
    THEMEMODE_SPORT,         // 运动主题
    THEMEMODE_INDIVIDUAL,    // 自定义主题
    THEMEMODE_MAX
};


/**********************/
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
    MSG_NONE = 0x0,
    //HOME
    MSG_SPEED,
    MSG_LANGUGE,
    MSG_CHARGE_PERCENT,
    MSG_CHARGE_COLOR,
    MSG_DRIVE_MODE,
    MSG_CHARGE_STATUS,
    MSG_CHARGE_CABLE_STATUS,
    MSG_TEMP,
    MSG_READY,
    MSG_GEAR,
    MSG_FL_DOOR_STATUS,
    MSG_FR_DOOR_STATUS,
    MSG_RL_DOOR_STATUS,
    MSG_RR_DOOR_STATUS,
    MSG_TAIL,
    MSG_HOOD,
    MSG_FL_CHARGE_PORT,
    MSG_RL_CHARGE_PORT,
    MSG_REMAIN_CHARGE_TIME,
    MSG_ODO,

    //CARINFO
    MSG_AS_TRIP,
    MSG_AS_AVG_SPEED,
    MSG_AS_DRIVING_TIME,
    MSG_AS_AVG_POWER,
    MSG_AR_TRIP,
    MSG_AR_AVG_SPEED,
    MSG_AR_DRIVING_TIME,
    MSG_AR_AVG_POWER,
    MSG_REMAIN_RANGE,
    MSG_LF_TIRE_PRESSURE,
    MSG_RF_TIRE_PRESSURE,
    MSG_RR_TIRE_PRESSURE,
    MSG_LR_TIRE_PRESSURE,
    MSG_LF_TIRE_TEMP,
    MSG_RF_TIRE_TEMP,
    MSG_RR_TIRE_TEMP,
    MSG_LR_TIRE_TEMP,
    MSG_LAST_CHARGE_TIME,
    MSG_LAST_CHARGE_ODO,
    MSG_AVG_APC_VALUE,
    MSG_CURRENT_APC_VALUE,

    //DIAG
    MSG_ODO_CLEAR_TIME,

    //SETTING
    MSG_CARINFO_SCREEN_INDEX,
    MSG_HARDKEY_STATUS,
    MSG_HARDKEY_NUMBER,
    MSG_SETLANGUGE,
    //POPUP
    MSG_BRAKE_SYSTEM,
    MSG_EPB_FAULT,
    MSG_HDC,
    MSG_DRV_AVH,
    MSG_ESC_FAULT,
    MSG_STEERING_FAULT,
    MSG_BRAKE_PADS,
    MSG_WIPER_FAULT,
    MSG_BATT_ERROR,
    MSG_TCS_FAULT,
    MSG_ABS_FAULT,
    MSG_EPB_MODE,
    MSG_AVH_FAULT,
    MSG_TCS_OFF,
    MSG_AVL_EBD_FAULT,
    MSG_LOW_BRAKE_FLUID,
    MSG_LOW_GLASS_WATER,
    MSG_KEY_BATT_LOW,
    MSG_SUSPENSION_SYSTEM_FAULT,
    MSG_SUSPENSION_SYSTEM,
    MSG_SUM_DAMP_LIMP,
    MSG_HV_BATT,
    MSG_SHIFTER_FAULT,
    MSG_IMM_WARNING,
    MSG_BOOSTER_FAULT,
    MSG_SUSPENSION_MOVE,
    MSG_ADAS_LKS_ACTIVE, //车道线左右两侧颜色
    MSG_ADAS_ELK_ACTIVE, //ELK提示车道线颜色
    MSG_ADAS_RCW,
    MSG_ADAS_RCTA,
    MSG_ADAS_LCA,
    MSG_ADAS_ELK,
    MSG_ADAS_ACC_WARN,
    MSG_ADAS_TSR_FAULT,
    MSG_ADAS_AHB_FAULT,
    MSG_ADAS_ACC_FAULT,
    MSG_TST_LIMIT_SPEED,
    MSG_ADAS_ACC_TIMEGAP,
    MSG_ADAS_L3_WARNING,
    MSG_ADAS_HWA_HANDSON,
    MSG_ADAS_HWA_ST,
    MSG_ADAS_HWA_ABORT,
    MSG_ADAS_DOW_ST,
    MSG_ADAS_L3_STATUS,
    MSG_ADAS_CONTROLLER_FAULT,
    MSG_ADAS_FMRRSENSOR_BLOC,
    MSG_ADAS_FMRRSENSOR_FAULT,
    MSG_ADAS_FCAMSENSOR_BLOC,
    MSG_ADSS_LFSRRSENSOR_BLOC,
    MSG_ADAS_LRSRRSENSOR_BLOC,
    MSG_ADAS_RRSRRSENSOR_BLOC,
    MSG_ADAS_RFSRRSENSOR_BLOC,
    MSG_ADAS_FMRRSENSOR_CALI,
    MSG_ADAS_FCAMSENSOR_CALI,
    MSG_ADAS_LFSRRSENSOR_CALI,
    MSG_ADAS_LRSRRSENSOR_CALI,
    MSG_ADAS_RRSRRSENSOR_CALI,
    MSG_ADAS_RFSRRSENSOR_CALI,
    MSG_ADAS_FCMASENSOR_FAULT,
    MSG_ADAS_LFSRRSENSOR_FAULT,
    MSG_ADAS_LRSRRSENSOR_FAULT,
    MSG_ADAS_RRSRRSENSOR_FAULT,
    MSG_ADAS_RFSRRSENSOR_FAULT,
    MSG_ADAS_FCW_ST,
    MSG_ADAS_AEB_ST,
    MSG_ADAS_FCTA_ST,
    MSG_IPU_EEM_DCDC_FAULT,
    MSG_TIRE_SYSTEM_FAULT,
    MSG_TIRE_FAULT,
    MSG_VCU_LV_WARN,
    MSG_ANRC_PRKG_PDC_MODE,
    MSG_TIRE_WARN_FRONT_LE,
    MSG_TIRE_WARN_FRONT_RI,
    MSG_TIRE_WARN_REAR_LE,
    MSG_TIRE_WARN_REAR_RI,
    MSG_VCU_SYSTEM_FAULT,
    MSG_VCU_BATT_HEAT,
    MSG_VCU_COOLANT_ALARN,
    MSG_VCU_EMOTOR_ALARM,
    MSG_VCU_SYSTEM_POWER_LIMIT,
    MSG_VCU_INVLD_CDN,
    MSG_VCU_ELEC_PT_LIMD_DECEL,
    MSG_ACM_AIRB_WARN,
    MSG_ACC_PASSIVE_REASON,
    MSG_CHARING_VOLTAGE,
    MSG_CHARING_ELECTRIC,


    MSG_ADAS_DOW_FL, //门开状态
    MSG_ADAS_DOW_RL,
    MSG_ADAS_DOW_FR,
    MSG_ADAS_DOW_RR,
    MSG_ADAS_RCW_WARN, //RCW后碰撞
    MSG_ADAS_FCW_WARN, //FCW前碰撞
    MSG_ADAS_FCTA_LEFT_WARN, //FCTA碰撞提示-左侧
    MSG_ADAS_FCTA_RIGHT_WARN, //FCTA碰撞提示-右侧
    MSG_RCTA_LEFT_WARN, //RCTA碰撞提示-左侧
    MSG_RCTA_RIGHT_WARN, //RCTA碰撞提示-右侧
    MSG_LCA_LEFT_WARN, //BSD提示-左侧
    MSG_LCA_RIGHT_WARN, //BSD提示-右侧
    MSG_ADAS_L3AVAILABLESTATUS, //脱手巡航

    MSG_ADAS_LINE_1_DISPLAY, //车道线是否显示
    MSG_ADAS_LINE_2_DISPLAY,
    MSG_ADAS_LINE_3_DISPLAY,
    MSG_ADAS_LINE_4_DISPLAY,
    MSG_ADSS_HWA_STATUS, //车道线颜色

    MSG_ADAS_LINE_1_TYPE, //车道线类型(不需要类型了)
    MSG_ADAS_LINE_2_TYPE,
    MSG_ADAS_LINE_3_TYPE,
    MSG_ADAS_LINE_4_TYPE,

    MSG_ADAS_LINE_1_A0, //车道线系数
    MSG_ADAS_LINE_2_A0,
    MSG_ADAS_LINE_3_A0,
    MSG_ADAS_LINE_4_A0,
    MSG_ADAS_LINE_1_A1,
    MSG_ADAS_LINE_2_A1,
    MSG_ADAS_LINE_3_A1,
    MSG_ADAS_LINE_4_A1,
    MSG_ADAS_LINE_1_A2,
    MSG_ADAS_LINE_2_A2,
    MSG_ADAS_LINE_3_A2,
    MSG_ADAS_LINE_4_A2,
    MSG_ADAS_LINE_1_A3,
    MSG_ADAS_LINE_2_A3,
    MSG_ADAS_LINE_3_A3,
    MSG_ADAS_LINE_4_A3,

    MSG_ADAS_TRACKTARGET0_ST, //动态目标物是否显示
    MSG_ADAS_TRACKTARGET1_ST,
    MSG_ADAS_TRACKTARGET2_ST,
    MSG_ADAS_TRACKTARGET3_ST,
    MSG_ADAS_TRACKTARGET4_ST,
    MSG_ADAS_TRACKTARGET5_ST,
    MSG_ADAS_TRACKTAR0_STATIC_ST, //静态目标物是否显示
    MSG_ADAS_TRACKTAR1_STATIC_ST,
    MSG_ADAS_TRACKTAR2_STATIC_ST,
    MSG_ADAS_TRACKTAR3_STATIC_ST,
    MSG_ADAS_TRACKTAR4_STATIC_ST,
    MSG_ADAS_TRACKTAR5_STATIC_ST,


    MSG_ADAS_TRACKTARGET0_OBJECTTYPE, //动态目标物类型
    MSG_ADAS_TRACKTARGET1_OBJECTTYPE,
    MSG_ADAS_TRACKTARGET2_OBJECTTYPE,
    MSG_ADAS_TRACKTARGET3_OBJECTTYPE,
    MSG_ADAS_TRACKTARGET4_OBJECTTYPE,
    MSG_ADAS_TRACKTARGET5_OBJECTTYPE,
    MSG_ADAS_TRACKTAR0_STATIC_OBJECTTYPE, //静态目标物类型
    MSG_ADAS_TRACKTAR1_STATIC_OBJECTTYPE,
    MSG_ADAS_TRACKTAR2_STATIC_OBJECTTYPE,
    MSG_ADAS_TRACKTAR3_STATIC_OBJECTTYPE,
    MSG_ADAS_TRACKTAR4_STATIC_OBJECTTYPE,
    MSG_ADAS_TRACKTAR5_STATIC_OBJECTTYPE,


    MSG_ADAS_TRACKTAR0_LATPO, //动态目标物X坐标
    MSG_ADAS_TRACKTAR1_LATPO,
    MSG_ADAS_TRACKTAR2_LATPO,
    MSG_ADAS_TRACKTAR3_LATPO,
    MSG_ADAS_TRACKTAR4_LATPO,
    MSG_ADAS_TRACKTAR5_LATPO,
    MSG_ADAS_TRACKTAR0_STATIC_LATPO, //静态目标物X坐标
    MSG_ADAS_TRACKTAR1_STATIC_LATPO,
    MSG_ADAS_TRACKTAR2_STATIC_LATPO,
    MSG_ADAS_TRACKTAR3_STATIC_LATPO,
    MSG_ADAS_TRACKTAR4_STATIC_LATPO,
    MSG_ADAS_TRACKTAR5_STATIC_LATPO,

    MSG_ADAS_TRACKTAR0_LGTPO, //动态目标物Y坐标
    MSG_ADAS_TRACKTAR1_LGTPO,
    MSG_ADAS_TRACKTAR2_LGTPO,
    MSG_ADAS_TRACKTAR3_LGTPO,
    MSG_ADAS_TRACKTAR4_LGTPO,
    MSG_ADAS_TRACKTAR5_LGTPO,
    MSG_ADAS_TRACKTAR0_STATIC_LGTPO,//静态目标物Y坐标
    MSG_ADAS_TRACKTAR1_STATIC_LGTPO,
    MSG_ADAS_TRACKTAR2_STATIC_LGTPO,
    MSG_ADAS_TRACKTAR3_STATIC_LGTPO,
    MSG_ADAS_TRACKTAR4_STATIC_LGTPO,
    MSG_ADAS_TRACKTAR5_STATIC_LGTPO,

    MSG_ADAS_ADASEBREQTYP, //AEB/FCTB/RCTB报警
    MSG_ADAS_ADASBRKJERKREQ, //AEB短促制动提示
    MSG_ADAS_ACC_OBJECTCAPTUREDSTATUS, //目标物0高亮

    MSG_ANRC_PRKGSTSINDCR, //泊车状态标志位
    MSG_ANRC_PRKGLESLOTTYP1, //左侧车位
    MSG_ANRC_PRKGLESLOTTYP2,
    MSG_ANRC_PRKGLESLOTTYP3,
    MSG_ANRC_PRKGRISLOTTYP1, //右侧车位
    MSG_ANRC_PRKGRISLOTTYP2,
    MSG_ANRC_PRKGRISLOTTYP3,

    /*泊车雷达------------------------------ 前后左右*/
    MSG_ANRC_PRKGFRNTLEDSTTOOBSTCL,
    MSG_ANRC_PRKGFRNTMIDLEDSTTOOBSTCL,
    MSG_ANRC_PRKGFRNTMIDRIDSTTOOBSTCL,
    MSG_ANRC_PRKGFRNTRIDSTTOOBSTCL,

    MSG_ANRC_PRKGREARLEDSTTOOBSTCL,
    MSG_ANRC_PRKGREARMIDLEDSTTOOBSTCL,
    MSG_ANRC_PRKGREARMIDRIDSTTOOBSTCL,
    MSG_ANRC_PRKGREARRIDSTTOOBSTCL,

    MSG_ANRC_PRKGSIDEFRNTLEOBSTCLZON,
    MSG_ANRC_PRKGSIDEFRNTMIDLEOBSTCLZON,
    MSG_ANRC_PRKGSIDEREARMIDLEOBSTCLZON,
    MSG_ANRC_PRKGSIDEREARLEOBSTCLZON,

    MSG_ANRC_PRKGSIDEFRNTRIOBSTCLZON,
    MSG_ANRC_PRKGSIDEFRNTMIDRIOBSTCLZON,
    MSG_ANRC_PRKGSIDEREARMIDRIOBSTCLZON,
    MSG_ANRC_PRKGSIDEREARRIOBSTCLZON,
    /*泊车雷达------------------------------ 前后左右*/

    //Body
    MSG_BCM_AutoLiCtrlWarn,  //自动远光灯系统故障
    MSG_BCM_HeadLightOpenWarn, //请打开车灯
    MSG_LCMFL_LeFrntPosnLampFltSts, //左前位置灯故障
    MSG_LCMFR_RiFrntPosnLampFltSts, //右前位置灯故障
    MSG_LCMRL_LeRePosnFailrSt, //左后位置灯故障
    MSG_LCMRR_RiRePosnFailrSt, //右后位置灯故障
    MSG_LCMFL_LeLoBeamFltSts, //左前近光灯故障
    MSG_LCMFR_RiLoBeamFltSts, //右前近光灯故障
    MSG_LCMFL_LeGrpdLampModFltSts, //左灯模块故障
    MSG_LCMFR_RiGrpdLampModFltSts, //右灯模块故障
    MSG_LCMFL_LeHiBeamFltSts, //左远光灯故障
    MSG_LCMFR_RiHiBeamFltSts, //右远光灯故障
    MSG_SCM_HiBeamSwtFailrSts, //远光灯开关故障
    MSG_BCM_ReLeRvsLiFailrSts, //左倒车灯故障
    MSG_BCM_ReRiRvsLiFailrSts, //右倒车灯故障
    MSG_BCM_ReLeFogFailrSts, //左后雾灯故障
    MSG_BCM_ReRiFogFailrSts, //右后雾灯故障
    MSG_LCMFL_LeFltDayLampSts, //左侧日间行车灯故障
    MSG_LCMFR_RiFltDayLampSts, //右侧日间行车灯故障
    MSG_BCM_ReLeBrkLiFailrSts, //左后制动灯故障
    MSG_BCM_ReRiBrkLiFailrSts, //右后制动灯故障
    MSG_BCM_MidHiBrkLiFailrSts, //高位制动灯故障
    MSG_LCMFL_LeFrntDirIndcrFailrSt, //左前转向灯故障
    MSG_LCMFR_RiFrntDirIndcrFailrSt, //右前转向灯故障 TBD：缺信号
    MSG_DCMFL_LeSideDirIndcrLampSt, //TBD：缺信号
    MSG_DCMFR_RiSideDirIndcrLampSt, //TBD：缺信号
    MSG_LCMRL_LeReDirIndcrFailrSt,
    MSG_LCMRR_RiReDirIndcrFailrSt,
    MSG_BCM_AutoWiprCtrlWarn,
    MSG_BCM_KeyDetectWarn,
    MSG_BCM_KeyInsideWarn,
    MSG_BCM_ImobBkpWarn,
    MSG_BCM_BrkPedlIndcnWarn,
    MSG_BCM_PwrRlyErrWarn,
    MSG_BCM_LvlBattULoWarn,
    MSG_BCM_EgyLvlDegradationWarn,
    MSG_BCM_ImobMstWarn,
    MSG_ADAS_ACC_GoNotifier,
    MSG_ADAS_HWA_Warn_St,
    MSG_ADAS_HWA_HandsonReq,
    MSG_ADAS_FCWRequest,
    MSG_ADAS_L3_HandsonReq, //TBD：缺信号
    MSG_ADAS_FCTB_St,
    MSG_ADAS_RCTB_St,
    MSG_ADAS_LDW_St,
    MSG_ADAS_LKA_St,
    MSG_DMS_DMSSts,
    MSG_DMS_DMSAbandon_Reason,
    MSG_ETC_RFModule,
    MSG_ETC_ESAMModule,
    MSG_ETC_Antitemper,
    MSG_PLCU_ParkLockSt,
    MSG_VCU_VehSrvcWarn,
    MSG_BMS_VehHvIsoErr,
    MSG_DCMFL_LeSideDirIndcrFailrSt,
    MSG_DCMFR_RiSideDirIndcrFailrSt,
    MSG_ANRC_PrkgMEBWarnType,
    MSG_ANRC_MEB_FuncSts,
    MSG_DMS_DrowsnsLevel,
    MSG_DMS_DistrctnLevel,
    MSG_ADAS_FCTA_Left_Active_St,
    MSG_ADAS_FCTA_Right_Active_St,





} RpcMsgValueId;
/**********************/
extern QMap<RpcMsgValueId,SingleMessage> gMapMsgValues;
extern bool getMsgValue(const RpcMsgValueId& msgId,SingleMessage& message);

//默认参数省代码 233 猝 函数指针不不接受默认形参 233
#define DEFAULT_SINGLEMESSAGE_RPCMSGVALUE_DATA(RpcMsgValueId)  SingleMessage msg = gMapMsgValues.value(RpcMsgValueId,SingleMessage())
//默认参数判断是否正常获取到参数
#define CHECK_RPCMSGVALUE_DATA if(msg.id == MSG_NONE) return ;

//初始化233
#define INIT_SINGLEMESSAGE_VALUE(id,message) if(!getMsgValue(id,message)) return;


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
    int getTimerCnt();
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

        WARNING_STATE_POP_TURN = 0,									/*0*/ //左右转向
        WARNING_STATE_POP_AIRBAG_WARNING,							/*1*/ //安全气囊故障
        WARNING_STATE_POP_SEATBELT_LEVEL_H,						/*2*/ //安全带报警           持续95s ，SPEED >= 40
        WARNING_STATE_POP_SEATBELT_LEVEL_M,						/*3*/ //安全带报警           持续95s ，SPEED < 40
        WARNING_STATE_POP_SEATBELT_LEVEL_L,     						/*4*/ //安全带报警          持续25s，SPEED < 40
        WARNING_STATE_POP_TPMS_FAULT,								/*5*/ //胎压系统故障，发声TBD
        WARNING_STATE_POP_DOOR_OPEN,								/*6*/ //门开报警，发声TBD
        /*	ADAS 域	*/
        WARNING_STATE_POP_LDW_LEFT,	     							/*7*/ //LDW提示	         左侧发声
        WARNING_STATE_POP_LDW_RIGHT,								/*8*/ //LDW提示		 右侧发声
        WARNING_STATE_POP_LKA_LEFT,	     							/*9*/ //LKA提示	         左侧发声
        WARNING_STATE_POP_LKA_RIGHT,								/*10*/ //LKA提示		 右侧发声
        WARNING_STATE_POP_BSD_LEVEL2_RL,							/*11*/ //BSD提示2级 后左侧发声
        WARNING_STATE_POP_BSD_LEVEL2_RR,							/*12*/ //BSD提示2级 后右侧发声
        WARNING_STATE_POP_ELK_ACTIVE_LEFT,							/*13*/ //ELK激活提示，左侧发声
        WARNING_STATE_POP_ELK_ACTIVE_RIGHT,						/*14*/ //ELK激活提示，右侧发声
        WARNING_STATE_POP_ACC_UNABLE,								/*15*/ //ACC 无法激活，前排发声
        WARNING_STATE_POP_ACC_TAKEOVER,							/*16*/ //ACC 请接管车辆，前排发声
        WARNING_STATE_POP_HWA_UNABLE,								/*17*/ //HWA 无法激活，前排发声
        WARNING_STATE_POP_ACC_CRUISE_EXITED,						/*18*/ //巡航已退出，前排发声
        WARNING_STATE_POP_HWA_TAKEOVER,							/*19*/ //HWA 请接管车辆，前排发声
        WARNING_STATE_POP_AUTOLANE_FINISHED_LEFT,					/*20*/ //自动变道终止，左侧发声
        WARNING_STATE_POP_AUTOLANE_FINISHED_RIGHT,				/*21*/ //自动变道终止，左侧发声
        WARNING_STATE_POP_OVERSPEED,								/*22*/ //超速报警，前排发声
        WARNING_STATE_POP_DOW_LEVEL1_FL,							/*23*/ //1级门开预警,前左发声
        WARNING_STATE_POP_DOW_LEVEL1_RL,							/*24*/ //1级门开预警,后左发声
        WARNING_STATE_POP_DOW_LEVEL1_FR,							/*25*/ //1级门开预警,前右发声
        WARNING_STATE_POP_DOW_LEVEL1_RR,							/*26*/ //1级门开预警,后右发声
        WARNING_STATE_POP_DOW_LEVEL2_FL,							/*27*/ //2级门开预警,前左发声
        WARNING_STATE_POP_DOW_LEVEL2_RL,							/*28*/ //2级门开预警,后左发声
        WARNING_STATE_POP_DOW_LEVEL2_FR,							/*29*/ //2级门开预警,前右发声
        WARNING_STATE_POP_DOW_LEVEL2_RR,							/*30*/ //2级门开预警,后右发声
        WARNING_STATE_POP_RCW_LEVEL1,								/*31*/ //RCW 1 级报警,后排发声
        WARNING_STATE_POP_RCW_LEVEL2,    							/*32*/ //RCW 2 级报警,后排发声
        WARNING_STATE_POP_FCW_LEVEL1,								/*33*/ //FCW 1 级报警,前排发声
        WARNING_STATE_POP_FCW_LEVEL2,    							/*34*/ //FCW 2 级报警,前排发声
        WARNING_STATE_POP_FCW_KEEP_DISTANCE,						/*35*/ //FCW保持车距，前排发声
        WARNING_STATE_POP_BARKE_SHORT,							/*36*/ //短促制动，前排发声
        WARNING_STATE_POP_AEB_ACTIVE,								/*37*/ //AEB 激活，前排发声
        WARNING_STATE_POP_FCTA_LEVEL1_FL,							/*38*/ // 1级FCTA 报警，前左发声
        WARNING_STATE_POP_FCTA_LEVEL1_FR,							/*39*/ // 1级FCTA 报警，前右发声
        WARNING_STATE_POP_FCTA_LEVEL2_FL,							/*40*/ // 2级FCTA 报警，前左发声
        WARNING_STATE_POP_FCTA_LEVEL2_FR,							/*41*/ // 2级FCTA 报警，前右发声
        WARNING_STATE_POP_FCTB_WARNING,							/*42*/ //FCTB 报警，前排发声
        WARNING_STATE_POP_RCTA_LEVEL1_RL,							/*43*/ // 2级RCTA 报警，后左发声
        WARNING_STATE_POP_RCTA_LEVEL1_RR,							/*44*/ // 2级RCTA 报警，后右发声
        WARNING_STATE_POP_RCTA_LEVEL2_RL,							/*45*/ // 2级RCTA 报警，后左发声
        WARNING_STATE_POP_RCTA_LEVEL2_RR,							/*46*/ // 2级RCTA 报警，后右发声
        WARNING_STATE_POP_RCTB_WARNING,							/*47*/ //RCTB 报警，后排发声
        WARNING_STATE_POP_HWA_LEVEL1_HANDSON,					/*48*/ //HWA手离方向盘报警1级,前排发声
        WARNING_STATE_POP_HWA_LEVEL2_HANDSON, 					/*49*/ //HWA手离方向盘报警2级,前排发声
        WARNING_STATE_POP_HWA_HANDSOFF,							/*50*/ //HWA Hands-off报警,前排发声
        WARNING_STATE_POP_FATIGUE_DRIVE_L,							/*51*/ //疲劳报警低中,前排发声
        WARNING_STATE_POP_FATIGUE_DRIVE_H,							/*52*/ //疲劳报警高,前排发声
        WARNING_STATE_POP_DISTRACTION_L,							/*53*/ //分心报警低中,前排发声
        WARNING_STATE_POP_DISTRACTION_H,							/*54*/ //分心报警高,前排发声
        WARNING_STATE_POP_HANDSFREE_ACTION,             		        	/*55*/ //脱手巡航启动,前排发声
        WARNING_STATE_POP_RES_GO_ON,								/*56*/ //Res继续巡航,前排发声
        WARNING_STATE_POP_HWA_GRADING_ALARM,						/*57*/ //HWA脱手中的分级报警,整车发声
        WARNING_STATE_POP_HWA_HANDSON_AUTOLANE,					/*58*/ //自动变道手离方向盘报警,前排发声
        WARNING_STATE_POP_HWA_ACTION,								/*59*/ //HWA启动,前排发声
        WARNING_STATE_POP_PDC_AUTOCHECK,							/*60*/ //PDC自检，前排发声,小于5s
        WARNING_STATE_POP_ACC_EXITED,								/*61*/ //ACC 已退出，前排发声
        WARNING_STATE_POP_HWA_EXITED,								/*62*/ //HWA 已退出，前排发声
        /* POWERTRAIN 域*/
        WARNING_STATE_POP_COOLANT_ALARM,							/*63*/ //电机/电池冷却液低,发声区域TBD
        WARNING_STATE_POP_BATTERY_LOW,							/*64*/ //低电量提示,发声区域TBD
        WARNING_STATE_POP_BMS_BATTERY_FAULT,						/*65*/ //BMS电池故障 ,发声区域TBD
        WARNING_STATE_POP_CHARGESYS_FAULT,						/*66*/ //充电系统故障,发声区域TBD
        WARNING_STATE_POP_MOTOR_FAULT,							/*67*/ //电机严重故障,发声区域TBD
        WARNING_STATE_POP_MOTIVE_POWER_FAULT,					/*68*/ //动力系统故障,发声区域TBD
        WARNING_STATE_POP_BATTERY_HOT,								/*69*/ //动力电池过热,发声区域TBD
        WARNING_STATE_POP_BATTERY_THERMAL_RUNAWAY,				/*70*/ //电池热失控,发声区域TBD
        WARNING_STATE_POP_INSULATION_FAULT,						/*71*/ //绝缘故障,发声区域TBD
        WARNING_STATE_POP_SHIFT_FAULT,								/*72*/ //换挡器故障,发声区域TBD
        /* CHASSIS 域 */
        WARNING_STATE_POP_BRAKESYS_FAULT,							/*73*/ //制动系统故障,发声区域TBD
        WARNING_STATE_POP_EPBSYS_FAULT,							/*74*/ //EPB系统故障,发声区域TBD
        WARNING_STATE_POP_STEERINGSYS_FAULT,						/*75*/ //转向助力系统故障,发声区域TBD
        WARNING_STATE_POP_ESCSYS_FAULT,							/*76*/ //ESC系统故障,发声区域TBD
        WARNING_STATE_POP_TCSSYS_FAULT,							/*77*/ //TCS系统故障,发声区域TBD
        WARNING_STATE_POP_ABSSYS_FAULT,							/*78*/ //ABS系统故障,发声区域TBD
        WARNING_STATE_POP_EBDSYS_FAULT,							/*79*/ //制动力分配系统故障,发声区域TBD
        WARNING_STATE_POP_BRAKE_ASSIST_FAULT,						/*80*/ //制动助力故障,发声区域TBD
        WARNING_STATE_POP_AUTO_PARKING_FAULT,						/*81*/ //自动驻车故障,发声区域TBD
        WARNING_STATE_POP_AVH_ALARM,								/*82*/ //请系上安全带并关闭车门,发声区域TBD
        WARNING_STATE_POP_HDCSYS_FAULT,							/*83*/ //陡坡缓降系统故障,发声区域TBD

        /* PDC */
        WARNING_STATE_POP_PDC_FRONT_NEAREST, 						/*84*/ //PDC前排 长鸣
        WARNING_STATE_POP_PDC_FRONT_NEAR, 						/*85*/ //PDC前排 8HZ
        WARNING_STATE_POP_PDC_FRONT_FAR, 							/*86*/ //PDC前排 4HZ
        WARNING_STATE_POP_PDC_FRONT_FARTHEST,						/*87*/ //PDC前排 2HZ
        WARNING_STATE_POP_PDC_REAR_NEAREST, 						/*84*/ //PDC后排长鸣
        WARNING_STATE_POP_PDC_REAR_NEAR, 							/*85*/ //PDC后排 8HZ
        WARNING_STATE_POP_PDC_REAR_FAR, 							/*86*/ //PDC后排4HZ
        WARNING_STATE_POP_PDC_REAR_FARTHEST,						/*87*/ //PDC后排2HZ

        WARNING_STATE_POP_PDC_FRONT_FAILURE,						/*88*/ //PDC前排故障
        WARNING_STATE_POP_PDC_REAR_FAILURE,						/*89*/ //PDC后排故障
        WARNING_STATE_POP_PDC_SYSTEM_FAILURE,						/*90*/ //PDC系统故障
        WARNING_STATE_POP_HAZARD_WARNING ,      /*0***危险警报灯*/
        WARNING_STATE_DOOROPEN,                /*1***门开*/
        WARNING_STATE_MAIN_SAFETYBELT,         /*2***驾驶侧安全带未系提醒*/
        WARNING_STATE_ACCESSORY_SAFETYBELT,    /*3***副驾驶侧安全带未系*/
        WARNING_STATE_2ND_ROW_SAFETYBELT,      /*4***第二排安全带未系*/
        WARNING_STATE_PWR_BAT_THERMAL_RUNAWAY, /*5***动力电池热失控*/
        WARNING_STATE_TURN_ON,                 /*6***左转向*/
        WARNING_STATE_TURN_OFF,                /*7***右转向*/
        WARNING_STATE_GEAR,                    /*8***档位报警音*/

        WARNING_STATE_MAX                      							/*91*/ //MAX
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
#endif // HMI_SHARE_H
