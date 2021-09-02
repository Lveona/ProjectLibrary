#include "popupControl.h"
#include <QMutex>
#include <QDebug>
#include "uniqPopAddInfo.h"
#include "popupStrategy.h"
#include "popup.h"
static int accFault;
static int tstLimitSpeed;
static int tstLimitSpeed_BackUp;
static int hwaSt;
static int hwaAbort;
static int tireFrontLe_BackUp;
static int tireFrontRi_BackUp;
static int tireRearLe_BackUp;
static int tireRearRi_BackUp;

static int tireFrontLe;
static int tireFrontRi;
static int tireRearLe;
static int tireRearRi;

static int tireFault;
static int tireSysFault;

static SingleMessage accWarnStatus;
static SingleMessage accWarnReason;
static QList<QString> accReasonStringList = {"前摄像头遮挡", "前雷达遮挡", "车门未关", "驾驶员安全带未系",
                                              "车速过高", "未处于D档", "停车超时", "驾驶员接管超时",
                                              "电子驻车拉起", "系统错误", "AEB激活", "引擎盖开启", "ABS激活"};

static bool g_checksixsecends = false;
static int g_tire_all = 0;
static bool c_popupTyreLFWarning = false;
static bool c_popupTyreRFWarning = false;
static bool c_popupTyreLRWarning = false;
static bool c_popupTyreRRWarning = false;
static int gi_ADAS_L3warningstatus = 0;
static int gb_ADAS_DMS_DMSSts = false;
static int gi_ADAS_DMS_DMSAbandon_Reason = 0;
static PopCarDoor     carDoorSts;
static PopCarDoor     lastcarDoorSts;
static PopSeatBelt    seatBelt;
static PopTyre        tyre;
static UniqPopAddInfo uniqPopAddInfoInc(&carDoorSts,&seatBelt,&tyre);

static struct{
    int kdrv_stblt_sts;
    int kpas_stblt_sts;
    int krl_stblt_sts ;
    int krr_stblt_sts ;
    int krm_stblt_sts ;
}SeatBeltStatus;

//const PopupSound	popupSound_Type2	={AUDIO_INDEX_DOOROPEN,           POP_PM_D1};

const PopupSound	popupSound_A10	={AUDIO_INDEX_CHARGESYS_FAULT,        POP_PM_D1};
const PopupSound	popupSound_A11	={AUDIO_INDEX_MOTOR_FAULT,            POP_PM_D1};
const PopupSound	popupSound_A12	={AUDIO_INDEX_MOTIVE_POWER_FAULT,     POP_PM_D1};
const PopupSound	popupSound_A13	={AUDIO_INDEX_BATTERY_HOT,            POP_PM_D1};
const PopupSound	popupSound_A14	={AUDIO_INDEX_BATTERY_THERMAL_RUNAWAY,POP_PM_D1};
const PopupSound	popupSound_A15	={AUDIO_INDEX_SHIFT_FAULT,            POP_PM_D1};
const PopupSound	popupSound_A16	={AUDIO_INDEX_AIRBAG_WARNING,         POP_PM_D1};
const PopupSound	popupSound_B59	={AUDIO_INDEX_TPMS_FAULT,             POP_PM_D1};
const PopupSound	popupSound_C24	={AUDIO_INDEX_BATTERY_LOW,            POP_PM_D1};
const PopupSound	popupSound_C43	={AUDIO_INDEX_AVH_ALARM,              POP_PM_D1};
const PopupSound	popupSound_D17	={AUDIO_INDEX_AEB_ACTIVE,             POP_PM_D1};
const PopupSound	popupSound_D25	={AUDIO_INDEX_RES_GO_ON,              POP_PM_D1};

const PopupSound	popupSound_A1	={AUDIO_INDEX_EBDSYS_FAULT,           POP_PM_D1};
const PopupSound	popupSound_A2	={AUDIO_INDEX_BRAKE_ASSIST_FAULT,     POP_PM_D1};
const PopupSound	popupSound_A4	={AUDIO_INDEX_STEERINGSYS_FAULT,      POP_PM_D1};
const PopupSound	popupSound_B17	={AUDIO_INDEX_ESCSYS_FAULT,           POP_PM_D1};
const PopupSound	popupSound_B19	={AUDIO_INDEX_ABSSYS_FAULT,           POP_PM_D1};
const PopupSound	popupSound_B20	={AUDIO_INDEX_TCSSYS_FAULT,           POP_PM_D1};
const PopupSound	popupSound_B22	={AUDIO_INDEX_AUTO_PARKING_FAULT,     POP_PM_D1};
const PopupSound	popupSound_B23	={AUDIO_INDEX_HDCSYS_FAULT,           POP_PM_D1};
const PopupSound	popupSound_B25	={AUDIO_INDEX_STEERINGSYS_FAULT,      POP_PM_D1};
const PopupSound	popupSound_C9	={AUDIO_INDEX_BRAKESYS_FAULT,         POP_PM_D1};
const PopupSound	popupSound_C10	={AUDIO_INDEX_BRAKESYS_FAULT,         POP_PM_D1};
const PopupSound	popupSound_C16	={AUDIO_INDEX_EPBSYS_FAULT,           POP_PM_D1};
const PopupSound	popupSound_C18	={AUDIO_INDEX_AVH_ALARM,              POP_PM_D1};
const PopupSound	popupSound_D21	={AUDIO_INDEX_HWA_TAKEOVER,           POP_PM_D1};
const PopupSound	popupSound_D26	={AUDIO_INDEX_HWA_UNABLE,              POP_PM_D1};
const PopupSound	popupSound_D96	={AUDIO_INDEX_HWA_LEVEL1_HANDSON,              POP_PM_D1};
const PopupSound	popupSound_D97	={AUDIO_INDEX_HWA_LEVEL2_HANDSON,              POP_PM_D1};

const PopupSound	popupSound_B69	={AUDIO_INDEX_HWA_EXITED,              POP_PM_D1};
const PopupSound	popupSound_A18	={AUDIO_INDEX_INSULATION_FAULT,             POP_PM_D1};

const PopupSound	popupSound_A6	={AUDIO_INDEX_COOLANT_ALARM,          POP_PM_D1};
const PopupSound	popupSound_A7	={AUDIO_INDEX_COOLANT_ALARM,          POP_PM_D1};
const PopupSound	popupSound_A8	={AUDIO_INDEX_COOLANT_ALARM,          POP_PM_D1};
const PopupSound	popupSound_A9	={AUDIO_INDEX_BMS_BATTERY_FAULT,          POP_PM_D1};
//	Popup of CATEGORY_A 			wmsgID		                  priorityvalue	       category	     dispPowerMode	symbol	name	text	targetvalue		currentvalue	POPUPSoundInstancePointer
//body
static	Popup	PopupA16	          ={1  ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "安全气囊故障",&popupSound_A16, HMIAudioCtrl::WARNING_STATE_POP_AIRBAG_WARNING, POP_DISPLAY, false};	/*	安全气囊故障	*/
static	Popup	PopupC43	          ={2  ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请系好安全带", &popupSound_C43, HMIAudioCtrl::WARNING_STATE_POP_AVH_ALARM, POP_DISPLAY, false};	/*	请系好安全带	*/
static	Popup	PopupB59	          ={3  ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "胎压系统故障", &popupSound_B59, HMIAudioCtrl::WARNING_STATE_POP_TPMS_FAULT, POP_DISPLAY, false};	/*	胎压系统故障	*/
static	Popup	PopupB13	          ={4  ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请及时更换刹车片",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请及时更换刹车片*/
static	Popup	PopupB15	          ={5  ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请添加玻璃洗涤液",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请添加玻璃洗涤液*/
static	Popup	PopupB29	          ={6  ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雨刮故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雨刮故障*/
static	Popup	PopupB30	          ={7  ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "自动雨刮系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	自动雨刮系统故障*/
static	Popup	PopupC44	          ={8  ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "未搜索到钥匙",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	未搜索到钥匙*/
static	Popup	PopupC45	          ={9  ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请带好钥匙",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请带好钥匙*/
static	Popup	PopupC46	          ={10 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "启用immo backup提醒",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	启用immo backup提醒*/
static	Popup	PopupC47	          ={11 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "钥匙不在车内",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	钥匙不在车内	*/
static	Popup	PopupB16	          ={12 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "钥匙电量低",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	钥匙电量低*/
static	Popup	PopupC2	              ={13 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请踩刹车",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请踩刹车	*/
static	Popup	PopupB31	          ={14 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "电源继电器错误",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	电源继电器错误*/
static	Popup	PopupB4	              ={15 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "防盗认证失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	防盗认证失败*/
static	Popup	PopupB5	              ={16 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "防盗认证系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	防盗认证系统故障*/
static	Popup	PopupB32	          ={17 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "自动远光灯系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	自动远光灯系统故障*/
static	Popup	PopupC48	          ={18 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "请打开远光灯",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请打开远光灯*/

static	Popup	PopupB33	          ={19 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左前位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前位置灯故障*/
static	Popup	PopupB34	          ={20 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右前位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前位置灯故障*/
static	Popup	PopupB35	          ={21 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左后位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后位置灯故障*/
static	Popup	PopupB36	          ={22 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右后位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后位置灯故障*/

static	Popup	PopupB37	          ={23 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左前近光灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前近光灯故障*/
static	Popup	PopupB38	          ={24 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右前近光灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前近光灯故障*/

static	Popup	PopupB39	          ={25 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左灯模块故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左灯模块故障*/
static	Popup	PopupB40	          ={26 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右灯模块故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右灯模块故障*/
static	Popup	PopupB41	          ={27 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左远光灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左远光灯故障*/
static	Popup	PopupB42	          ={28 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右远光灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右远光灯故障*/
static	Popup	PopupB43	          ={29 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "远光灯开关故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	远光灯开关故障*/

static	Popup	PopupB44	          ={30 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左倒车灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左倒车灯故障*/
static	Popup	PopupB45	          ={31 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右倒车灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右倒车灯故障*/
static	Popup	PopupB46	          ={32 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左后雾灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后雾灯故障*/
static	Popup	PopupB47	          ={33 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右后雾灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后雾灯故障*/

static	Popup	PopupB48	          ={34 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左侧日间行车灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左侧日间行车灯故障*/
static	Popup	PopupB49	          ={35 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右侧日间行车灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右侧日间行车灯故障*/

static	Popup	PopupB50	          ={36 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左后制动灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后制动灯故障*/
static	Popup	PopupB51	          ={37 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右后制动灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后制动灯故障*/
static	Popup	PopupB52	          ={38 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "高位制动灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	高位制动灯故障*/

static	Popup	PopupB53	          ={39 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左前转向灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前转向灯故障*/
static	Popup	PopupB54	          ={40 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右前转向灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前转向灯故障*/
static	Popup	PopupB55	          ={41 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左侧转向灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左侧转向灯故障*/
static	Popup	PopupB56	          ={42 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右侧转向灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右侧转向灯故障*/
static	Popup	PopupB57	          ={43 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "左后转向灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后转向灯故障*/
static	Popup	PopupB58	          ={44 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "右后转向灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后转向灯故障*/

static	Popup	PopupTyre	          ={45 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"tire_car.png", "",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	胎压异常*/


//powertrain
static	Popup	PopupA6  	          ={46 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "电池冷却液不足",&popupSound_A6, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	电池冷却液不足*/
static	Popup	PopupA7 	          ={47 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "电机冷却液不足",&popupSound_A7, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	电机冷却液不足*/
static	Popup	PopupA8 	          ={48 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "电池/电机冷却液不足",&popupSound_A8, HMIAudioCtrl::WARNING_STATE_POP_COOLANT_ALARM, POP_DISPLAY, false};	/*	电池/电机冷却液不足*/
static	Popup	PopupC24	          ={49 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "电池电量低，请及时充电",&popupSound_C24, HMIAudioCtrl::WARNING_STATE_POP_BATTERY_LOW, POP_DISPLAY, false};	/*	电池电量低，请及时充电*/
static	Popup	PopupB28	          ={50 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "电池功率受限",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	电池功率受限*/
static	Popup	PopupA9 	          ={51 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "电池严重故障",&popupSound_A9, HMIAudioCtrl::WARNING_STATE_POP_BMS_BATTERY_FAULT, POP_DISPLAY, false};	/*	电池严重故障*/
static	Popup	PopupA10 	          ={52 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "充电系统故障",&popupSound_A10, HMIAudioCtrl::WARNING_STATE_POP_CHARGESYS_FAULT, POP_DISPLAY, false};	/*	充电系统故障*/
static	Popup	PopupA11	          ={53 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "电机严重故障",&popupSound_A11, HMIAudioCtrl::WARNING_STATE_POP_MOTOR_FAULT, POP_DISPLAY, false};	/*	电机严重故障*/
static	Popup	PopupA12	          ={54 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "动力系统故障",&popupSound_A12, HMIAudioCtrl::WARNING_STATE_POP_MOTIVE_POWER_FAULT, POP_DISPLAY, false};	/*	动力系统故障*/
static	Popup	PopupB26	          ={55 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "驱动功率限制",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	驱动功率限制*/
static	Popup	PopupA13	          ={56 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "动力电池过热，请停车检查",&popupSound_A13, HMIAudioCtrl::WARNING_STATE_POP_BATTERY_HOT, POP_DISPLAY, false};	/*	动力电池过热，请停车检查	*/
static	Popup	PopupA14              ={57 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1_D2,"Icon_Seatbelt_Car.png", "动力电池热失控，请立即停车并远离车辆",&popupSound_A14, HMIAudioCtrl::WARNING_STATE_POP_BATTERY_THERMAL_RUNAWAY, POP_DISPLAY, false};	/*	动力电池热失控，请立即停车并远离车辆*/
static	Popup	PopupA15	          ={58 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "换挡器故障",&popupSound_A15, HMIAudioCtrl::WARNING_STATE_POP_SHIFT_FAULT, POP_DISPLAY, false};	/*	换挡器故障	*/
static	Popup	PopupB27	          ={59 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "减速器驻车锁故障，请尽快维修",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	减速器驻车锁故障，请尽快维修	*/
static	Popup	PopupC40	          ={60 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请踩刹车换挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请踩刹车换挡	*/
static	Popup	PopupC41	          ={61 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请拔下充电枪！",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	无法换挡，车速超限	*/
static	Popup	PopupC42	          ={62 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "能量回收受限",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	能量回收受限	*/
static	Popup	PopupB60	          ={63 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "低压系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	低压系统故障	*/
static	Popup	PopupA17	          ={64 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "低压系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	低压系统故障	*/

//chassis
static	Popup	PopupB17	          ={68 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ESC故障,请维修",&popupSound_B17, HMIAudioCtrl::WARNING_STATE_POP_ESCSYS_FAULT, POP_DISPLAY, false};	/*	ESC故障*/
static	Popup	PopupB20	          ={69 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "TCS故障,请维修",&popupSound_B20, HMIAudioCtrl::WARNING_STATE_POP_TCSSYS_FAULT, POP_DISPLAY, false};	/*	TCS故障	*/
static	Popup	PopupC28	          ={70 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ESC/TCS已关闭",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	ESC/TCS已关闭*/
static	Popup	PopupB19	          ={71 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ABS故障",&popupSound_B19, HMIAudioCtrl::WARNING_STATE_POP_ABSSYS_FAULT, POP_DISPLAY, false};	/*	ABS故障*/
static	Popup	PopupA1	              ={72 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "制动力分配系统故障",&popupSound_A1, HMIAudioCtrl::WARNING_STATE_POP_EBDSYS_FAULT, POP_DISPLAY, false};	/*	制动力分配系统故障	*/
static	Popup	PopupA2               ={73 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "制动助力故障",&popupSound_A2, HMIAudioCtrl::WARNING_STATE_POP_BRAKE_ASSIST_FAULT, POP_DISPLAY, false};	/*	制动助力故障	*/
static	Popup	PopupC10	          ={74 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "制动系统故障",&popupSound_C10, HMIAudioCtrl::WARNING_STATE_POP_BRAKESYS_FAULT, POP_DISPLAY, false};	/*	制动系统故障	*/
static	Popup	PopupC9	              ={75 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "制动系统严重故障",&popupSound_C9, HMIAudioCtrl::WARNING_STATE_POP_BRAKESYS_FAULT, POP_DISPLAY, false};	/*	制动系统严重故障	*/
static	Popup	PopupC11	          ={76 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "制动液位低",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	制动液位低	*/
static	Popup	PopupC16	          ={77 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "EPB系统故障",&popupSound_C16, HMIAudioCtrl::WARNING_STATE_POP_EPBSYS_FAULT, POP_DISPLAY, false};	/*	EPB系统故障*/
static	Popup	PopupB21	          ={78 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "EPB处于诊断模式",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	EPB处于诊断模式*/
static	Popup	PopupC13	          ={79 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请系上安全带",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请系上安全带	*/
static	Popup	PopupC15	          ={80 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请使用开关手动释放EPB",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请使用开关手动释放EPB*/
static	Popup	PopupC12	          ={81 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请踩下制动踏板释放EPB",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请踩下制动踏板释放EPB	*/
static	Popup	PopupC29	          ={82 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "驻车力不足，无法驻车",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	驻车力不足，无法驻车	*/
static	Popup	PopupC14	          ={83 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "坡度过大无法驻车",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	坡度过大无法驻车	*/
static	Popup	PopupB22	          ={84 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "自动驻车故障",&popupSound_B22, HMIAudioCtrl::WARNING_STATE_POP_AUTO_PARKING_FAULT, POP_DISPLAY, false};	/*	自动驻车故障*/
static	Popup	PopupC18	          ={85 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请系上安全带并关闭车门",&popupSound_C18, HMIAudioCtrl::WARNING_STATE_POP_AVH_ALARM, POP_DISPLAY, false};	/*	请系上安全带并关闭车门*/
static	Popup	PopupC30	          ={86 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "陡坡缓降工作中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	陡坡缓降工作中*/
static	Popup	PopupB23	          ={87 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "陡坡缓降系统故障",&popupSound_B23, HMIAudioCtrl::WARNING_STATE_POP_HDCSYS_FAULT, POP_DISPLAY, false};	/*	陡坡缓降系统故障*/
static	Popup	PopupB25              ={88 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "转向助力系统故障",&popupSound_B25, HMIAudioCtrl::WARNING_STATE_POP_STEERINGSYS_FAULT, POP_DISPLAY, false};	/*	转向助力系统故障*/
static	Popup	PopupA4	              ={89 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "转向助力系统严重故障",&popupSound_A4, HMIAudioCtrl::WARNING_STATE_POP_STEERINGSYS_FAULT, POP_DISPLAY, false};	/*	转向助力系统严重故障*/
static	Popup	PopupC31	          ={90 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架下降",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架下降*/
static	Popup	PopupC32	          ={91 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架上升",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架上升*/
static	Popup	PopupA5	              ={92 ,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架系统故障*/
static	Popup	PopupC20	          ={93 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架系统故障*/
static	Popup	PopupC21	          ={94 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架系统维修模式",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架系统维修模式*/
static	Popup	PopupC34	          ={95 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架系统过热",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架系统过热*/
static	Popup	PopupC35	          ={96 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架系统繁忙",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架系统繁忙*/
static	Popup	PopupC36	          ={97 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "海拔过高，悬架系统异常",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	海拔过高，悬架系统异常*/
static	Popup	PopupC37	          ={98 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "汽车升起，悬架不可用",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	汽车升起，悬架不可用*/
static	Popup	PopupC38	          ={99 ,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "气泵压力低，悬架系统异常",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	气泵压力低，悬架系统异常*/
static	Popup	PopupC39	          ={100,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "车辆倾斜，悬架不可用",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	车辆倾斜，悬架不可用*/
static	Popup	PopupB24	          ={101,POP_WMSG_CATEGORY_B,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "悬架系统跛行模式，请注意安全",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	悬架系统跛行模式，请注意安全*/

//adas
static	Popup	PopupD17	          ={102 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "AEB启动",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	AEB启动*/
static	Popup	PopupD18	          ={103 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "FCTB启动",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	FCTB启动*/
static	Popup	PopupD19	          ={104 ,POP_WMSG_CATEGORY_ADAS_B,    POP_PM_D1,   "Icon_Seatbelt_Car.png", "RCTB启动",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	RCTB启动*/
static	Popup	PopupD38	          ={105 ,POP_WMSG_CATEGORY_ADAS_B,   POP_PM_D1,   "Icon_Seatbelt_Car.png", "AEB启动",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	AEB启动*/

static	Popup	PopupD21	          ={106 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请接管方向盘",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请接管方向盘*/
static	Popup	PopupD22	          ={107 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ELK激活",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	ELK激活*/

static	Popup	PopupD23	          ={108 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "因为****，ACC无法激活",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	因为****，ACC无法激活*/

static	Popup	PopupD24	          ={109 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请接管车辆",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请接管车辆*/
static	Popup	PopupD25	          ={110 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "Res继续巡航",&popupSound_D25, HMIAudioCtrl::WARNING_STATE_POP_RES_GO_ON, POP_DISPLAY, false};	/*	Res继续巡航*/
static	Popup	PopupD26	          ={111 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "因为****，HWA无法激活",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	因为****，HWA无法激活*/

static	Popup	PopupD27	          ={112 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请接管方向盘",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请接管方向盘*/
static	Popup	PopupD28	          ={113 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请将双手放在方向盘上",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请将双手放在方向盘上*/

static	Popup	PopupD29	          ={114 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请监视道路情况",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请监视道路情况*/
static	Popup	PopupD37	          ={115 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请接管方向盘",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请接管方向盘*/
static	Popup	PopupD39	          ={116 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请接管车辆",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请接管车辆*/
static	Popup	PopupD30	          ={117 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "安全停车中，请接管车辆",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	安全停车中，请接管车辆*/

static	Popup	PopupD96	          ={118 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请将双手放在方向盘上",&popupSound_D96, HMIAudioCtrl::WARNING_STATE_POP_HWA_LEVEL1_HANDSON, POP_DISPLAY, false};	/*	请将双手放在方向盘上*/

static	Popup	PopupD97	          ={119 ,POP_WMSG_CATEGORY_ADAS_A,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请将双手放在方向盘上",&popupSound_D97, HMIAudioCtrl::WARNING_STATE_POP_HWA_LEVEL2_HANDSON, POP_DISPLAY, false};	/*	请将双手放在方向盘上*/
static	Popup	PopupD31	          ={120 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "目标车道未检测出车道线",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	目标车道未检测出车道线*/
static	Popup	PopupD32	          ={121 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "车道线不允许超车",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	车道线不允许超车*/
static	Popup	PopupD33	          ={122 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "变道风险检测未通过",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	变道风险检测未通过*/
static	Popup	PopupD34	          ={123 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "驾驶员取消变道",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	驾驶员取消变道*/
static	Popup	PopupD35	          ={124 ,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "自动变道故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	自动变道故障*/

static	Popup	PopupD36	          ={125 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "自动驾驶控制器故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	自动驾驶控制器故障*/
static	Popup	PopupD40	          ={126 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雷达故障*/
static	Popup	PopupD41	          ={127 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前摄像头遮挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前摄像头遮挡*/
static	Popup	PopupD42	          ={128 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左前角雷达遮挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前角雷达遮挡*/
static	Popup	PopupD43	          ={129 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左后角雷达遮挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后角雷达遮挡*/
static	Popup	PopupD44	          ={130 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右后角雷达遮挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后角雷达遮挡*/
static	Popup	PopupD45	          ={131 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右前角雷达遮挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前角雷达遮挡*/
static	Popup	PopupD46	          ={132 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雷达校准失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雷达校准失败*/
static	Popup	PopupD47	          ={133 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前摄像头校准失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前摄像头校准失败*/
static	Popup	PopupD48	          ={134 ,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左前角雷达校准失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前角雷达校准失败*/
static	Popup	PopupD49	          ={135,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左后角雷达校准失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后角雷达校准失败*/
static	Popup	PopupD50	          ={136,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右后角雷达校准失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后角雷达校准失败*/
static	Popup	PopupD51	          ={137,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右前角雷达校准失败",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前角雷达校准失败*/
static	Popup	PopupD52	          ={138,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雷达未校准",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雷达未校准*/
static	Popup	PopupD53	          ={139,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前摄像头未校准",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前摄像头未校准*/
static	Popup	PopupD54	          ={140,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左前角雷达未校准",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前角雷达未校准*/
static	Popup	PopupD55	          ={141,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左后角雷达未校准",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后角雷达未校准*/
static	Popup	PopupD56	          ={142,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右后角雷达未校准",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后角雷达未校准*/
static	Popup	PopupD57	          ={143,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右前角雷达未校准",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前角雷达未校准*/

static	Popup	PopupD58	          ={144,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雷达校准中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雷达校准中*/
static	Popup	PopupD59	          ={145,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前摄像头校准中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前摄像头校准中*/
static	Popup	PopupD60	          ={146,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左前角雷达校准中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前角雷达校准中*/
static	Popup	PopupD61	          ={147,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左后角雷达校准中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后角雷达校准中*/
static	Popup	PopupD62	          ={148,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右后角雷达校准中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后角雷达校准中*/
static	Popup	PopupD63	          ={149,POP_WMSG_CATEGORY_ADAS_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右前角雷达校准中",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前角雷达校准中*/

static	Popup	PopupD64	          ={150,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雷达故障*/
static	Popup	PopupD65	          ={151,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前摄像头故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前摄像头故障*/
static	Popup	PopupD66	          ={152,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左前角雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左前角雷达故障*/
static	Popup	PopupD67	          ={153,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左后角雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	左后角雷达故障*/
static	Popup	PopupD68	          ={154,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右后角雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右后角雷达故障*/
static	Popup	PopupD69	          ={155,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右前角雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	右前角雷达故障*/
static	Popup	PopupD70	          ={156,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "TSR功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	TSR功能故障*/
static	Popup	PopupD71	          ={157,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "DOW功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	DOW功能故障*/
static	Popup	PopupD72	          ={158,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "IHBC功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	IHBC功能故障*/
static	Popup	PopupD73	          ={159,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "RCW功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	RCW功能故障*/
static	Popup	PopupD74	          ={160,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "FCW功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	FCW功能故障*/
static	Popup	PopupD75	          ={161,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "AEB功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	AEB功能故障*/
static	Popup	PopupD76	          ={162,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "FCTA功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	FCTA功能故障*/
static	Popup	PopupD77	          ={163,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "FCTB功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	FCTB功能故障*/
static	Popup	PopupD78	          ={164,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "RCTA功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	RCTA功能故障*/
static	Popup	PopupD79	          ={165,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "RCTB功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	RCTB功能故障*/
static	Popup	PopupD80	          ={166,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "LDW功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	LDW功能故障*/
static	Popup	PopupD81	          ={167,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "LKA功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	LKA功能故障*/
static	Popup	PopupD82	          ={168,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "BSD功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	BSD功能故障*/
static	Popup	PopupD83	          ={169,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ELK功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	ELK功能故障*/
static	Popup	PopupD84	          ={170,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ACC功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	ACC功能故障*/
static	Popup	PopupD85	          ={171,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "HWA 功能故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	HWA 功能故障*/
static	Popup	PopupD86	          ={172,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "前雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	前雷达故障*/
static	Popup	PopupD87	          ={173,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "后雷达故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	后雷达故障*/
static	Popup	PopupD88	          ={174,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "雷达系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	雷达系统故障*/
static	Popup	PopupD89	          ={175,POP_WMSG_CATEGORY_ADAS_C,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "脱手巡航启动，可以将手放开方向盘",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	脱手巡航启动，可以将手放开方向盘*/
static	Popup	PopupD95	          ={176,POP_WMSG_CATEGORY_ADAS_C,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "检测到限速xx，按SET/-设置为巡航速度",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	脱手巡航启动，可以将手放开方向盘*/

static	Popup	PopupD90	          ={177,POP_WMSG_CATEGORY_ADAS_A,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "请专心驾驶",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请专心驾驶*/
static	Popup	PopupD91	          ={178,POP_WMSG_CATEGORY_ADAS_B,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "请专心驾驶",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请专心驾驶*/
static	Popup	PopupD92	          ={179,POP_WMSG_CATEGORY_ADAS_C,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "请专心驾驶",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请专心驾驶*/

static	Popup	PopupD93	          ={180,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "驾驶员监控摄像头故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	驾驶员监控摄像头故障*/
static	Popup	PopupD94	          ={181,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "驾驶员监控系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	驾驶员监控系统故障*/

static	Popup	Popup_volume	      ={182,POP_WMSG_CATEGORY_VOLUME,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "音量",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	音量*/
static	Popup	PopupC49	          ={183,POP_WMSG_CATEGORY_C,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请打开大灯",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};/*请打开大灯*/
static	Popup	PopupB61	          ={184,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左前位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*左前位置灯故障*/
static	Popup	PopupB62	          ={185,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右前位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*右前位置灯故障*/
static	Popup	PopupB63	          ={186,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "左后位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*左后位置灯故障*/
static	Popup	PopupB64	          ={187,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "右后位置灯故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*右后位置灯故障*/
static	Popup	PopupB65	          ={188,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "自动雨刮系统故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*自动雨刮系统故障*/
static	Popup	PopupB66	          ={189,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "蓄电池电压低",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*蓄电池电压低*/
static	Popup	PopupB67	          ={190,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "进入节电模式",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*进入节电模式*/
static	Popup	PopupB68	          ={191,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "ETC故障",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*ETC故障*/
static	Popup	PopupB69	          ={192,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "HWA已退出",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*HWA已退出*/
static	Popup	PopupC50	          ={193,POP_WMSG_CATEGORY_C,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请将钥匙放至中央扶手备份启动位",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	车辆倾斜，悬架不可用*/
static	Popup	PopupB70	          ={194,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "动力系统异常",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*动力系统异常*/
static	Popup	PopupA18	          ={195,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "绝缘故障，请立即离开",&popupSound_A18, HMIAudioCtrl::WARNING_STATE_POP_INSULATION_FAULT, POP_DISPLAY, false};	/*	绝缘故障，请立即离开*/
static	Popup	PopupB71	          ={196,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "请保持车距",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*请保持车距*/
static	Popup	PopupA19	          ={197,POP_WMSG_CATEGORY_A,	    POP_PM_D1,	 "Icon_Seatbelt_Car.png", "请保持车距",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	请保持车距*/
static	Popup	PopupD98	          ={198,POP_WMSG_CATEGORY_ADAS_B,	POP_PM_D1,   "Icon_Seatbelt_Car.png", "MEB不可用",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	MEB不可用*/
static	Popup	PopupD99	          ={199,POP_WMSG_CATEGORY_B,	    POP_PM_D1,   "Icon_Seatbelt_Car.png", "驾驶员监控摄像头遮挡",NULL, HMIAudioCtrl::WARNING_STATE_MAX, POP_DISPLAY, false};	/*	驾驶员监控摄像头遮挡*/

static QList<Popup*> syncToSettingPopList;

//global value
static int g_powermode = 0;
static int g_vehicleSpeed = 0;
static int g_drive4L_speed_area = 0;  //0:[:5),1:[5:]

QList<PopupControl::PopupFunctionParser> PopupVoidControlFunc {
    &PopupControl::func_MSG_BRAKE_SYSTEM,
    &PopupControl::func_MSG_EPB_FAULT,
    &PopupControl::func_MSG_HDC,
    &PopupControl::func_MSG_DRV_AVH,
    &PopupControl::func_MSG_ESC_FAULT,
    &PopupControl::func_MSG_STEERING_FAULT,
    &PopupControl::func_MSG_BATT_LOW,
    &PopupControl::func_MSG_BRAKE_PADS,
    &PopupControl::func_MSG_WIPER_FAULT,
    &PopupControl::func_MSG_BATT_ERROR,
    &PopupControl::func_MSG_TCS_FAULT,
    &PopupControl::func_MSG_ABS_FAULT,
    &PopupControl::func_MSG_EPB_MODE,
    &PopupControl::func_MSG_AVH_FAULT,
    &PopupControl::func_MSG_TCS_OFF,
    &PopupControl::func_MSG_AVL_EBD_FAULT,
    &PopupControl::func_MSG_LOW_BRAKE_FLUID,
    &PopupControl::func_MSG_LOW_GLASS_WATER,
    &PopupControl::func_MSG_KEY_BATT_LOW,
    &PopupControl::func_MSG_SUSPENSION_SYSTEM_FAULT,
    &PopupControl::func_MSG_SUSPENSION_SYSTEM,
    &PopupControl::func_MSG_SUM_DAMP_LIMP,
    &PopupControl::func_MSG_HV_BATT,
    &PopupControl::func_MSG_SHIFTER_FAULT,
    &PopupControl::func_MSG_IMM_WARNING,
    &PopupControl::func_MSG_BOOSTER_FAULT,
    &PopupControl::func_MSG_SUSPENSION_MOVE,
    &PopupControl::func_MSG_ADAS_LKS_ACTIVE,
    &PopupControl::func_MSG_ADAS_ELK_ACTIVE,
    &PopupControl::func_MSG_ADAS_RCW,
    &PopupControl::func_MSG_ADAS_RCTA,
    &PopupControl::func_MSG_ADAS_LCA,
    &PopupControl::func_MSG_ADAS_ELK,
    &PopupControl::func_MSG_ADAS_ACC_WARN,
    &PopupControl::func_MSG_ADAS_TSR_FAULT,
    &PopupControl::func_MSG_ADAS_AHB_FAULT,
    &PopupControl::func_MSG_ADAS_ACC_FAULT,
    &PopupControl::func_MSG_TST_LIMIT_SPEED,
    &PopupControl::func_MSG_ADAS_L3_WARNING,
    &PopupControl::func_MSG_ADAS_HWA_HANDSON,
    &PopupControl::func_MSG_ADAS_HWA_ST,
    &PopupControl::func_MSG_ADAS_HWA_ABORT,
    &PopupControl::func_MSG_ADAS_DOW_ST,
    &PopupControl::func_MSG_ADSS_HWA_STATUS,
    &PopupControl::func_MSG_ADAS_L3_STATUS,
    &PopupControl::func_MSG_ADAS_CONTROLLER_FAULT,
    &PopupControl::func_MSG_ADAS_FMRRSENSOR_BLOC,
    &PopupControl::func_MSG_ADAS_FMRRSENSOR_FAULT,
    &PopupControl::func_MSG_ADAS_FCAMSENSOR_BLOC,
    &PopupControl::func_MSG_ADSS_LFSRRSENSOR_BLOC,
    &PopupControl::func_MSG_ADAS_LRSRRSENSOR_BLOC,
    &PopupControl::func_MSG_ADAS_RRSRRSENSOR_BLOC,
    &PopupControl::func_MSG_ADAS_RFSRRSENSOR_BLOC,
    &PopupControl::func_MSG_ADAS_FMRRSENSOR_CALI,
    &PopupControl::func_MSG_ADAS_FCAMSENSOR_CALI,
    &PopupControl::func_MSG_ADAS_LFSRRSENSOR_CALI,
    &PopupControl::func_MSG_ADAS_LRSRRSENSOR_CALI,
    &PopupControl::func_MSG_ADAS_RRSRRSENSOR_CALI,
    &PopupControl::func_MSG_ADAS_RFSRRSENSOR_CALI,
    &PopupControl::func_MSG_ADAS_FCMASENSOR_FAULT,
    &PopupControl::func_MSG_ADAS_LFSRRSENSOR_FAULT,
    &PopupControl::func_MSG_ADAS_LRSRRSENSOR_FAULT,
    &PopupControl::func_MSG_ADAS_RRSRRSENSOR_FAULT,
    &PopupControl::func_MSG_ADAS_RFSRRSENSOR_FAULT,
    &PopupControl::func_MSG_ADAS_FCW_ST,
    &PopupControl::func_MSG_ADAS_AEB_ST,
    &PopupControl::func_MSG_ADAS_FCTA_ST,
    &PopupControl::func_MSG_ADAS_ADASEBREQTYP,
    &PopupControl::func_MSG_IPU_EEM_DCDC_FAULT,
    &PopupControl::func_MSG_TIRE_SYSTEM_FAULT,
    &PopupControl::func_MSG_TIRE_FAULT,
    &PopupControl::func_MSG_VCU_LV_WARN,
    &PopupControl::func_MSG_ANRC_PRKG_PDC_MODE,
    &PopupControl::func_MSG_TIRE_WARN_FRONT_LE,
    &PopupControl::func_MSG_TIRE_WARN_FRONT_RI,
    &PopupControl::func_MSG_TIRE_WARN_REAR_LE,
    &PopupControl::func_MSG_TIRE_WARN_REAR_RI,
    &PopupControl::func_MSG_VCU_SYSTEM_FAULT,
    &PopupControl::func_MSG_VCU_BATT_HEAT,
    &PopupControl::func_MSG_VCU_COOLANT_ALARN,
    &PopupControl::func_MSG_VCU_EMOTOR_ALARM,
    &PopupControl::func_MSG_VCU_SYSTEM_POWER_LIMIT,
    &PopupControl::func_MSG_VCU_INVLD_CDN,
    &PopupControl::func_MSG_VCU_ELEC_PT_LIMD_DECEL,
    &PopupControl::func_MSG_ACM_AIRB_WARN,
    &PopupControl::func_MSG_ACC_PASSIVE_REASON,
    &PopupControl::func_MSG_ADAS_ADASBRKJERKREQ,
    &PopupControl::func_MSG_BCM_AutoLiCtrlWarn,
    &PopupControl::func_MSG_BCM_HeadLightOpenWarn,
    &PopupControl::func_MSG_LCMFL_LeFrntPosnLampFltSts,
    &PopupControl::func_MSG_LCMFR_RiFrntPosnLampFltSts,
    &PopupControl::func_MSG_LCMRL_LeRePosnFailrSt,
    &PopupControl::func_MSG_LCMRR_RiRePosnFailrSt,
    &PopupControl::func_MSG_LCMFL_LeLoBeamFltSts,
    &PopupControl::func_MSG_LCMFR_RiLoBeamFltSts,
    &PopupControl::func_MSG_LCMFL_LeGrpdLampModFltSts,
    &PopupControl::func_MSG_LCMFR_RiGrpdLampModFltSts,
    &PopupControl::func_MSG_LCMFL_LeHiBeamFltSts,
    &PopupControl::func_MSG_LCMFR_RiHiBeamFltSts,
    &PopupControl::func_MSG_SCM_HiBeamSwtFailrSts,
    &PopupControl::func_MSG_BCM_ReLeRvsLiFailrSts,
    &PopupControl::func_MSG_BCM_ReRiRvsLiFailrSts,
    &PopupControl::func_MSG_BCM_ReLeFogFailrSts,
    &PopupControl::func_MSG_BCM_ReRiFogFailrSts,
    &PopupControl::func_MSG_LCMFL_LeFltDayLampSts,
    &PopupControl::func_MSG_LCMFR_RiFltDayLampSts,
    &PopupControl::func_MSG_BCM_ReLeBrkLiFailrSts,
    &PopupControl::func_MSG_BCM_ReRiBrkLiFailrSts,
    &PopupControl::func_MSG_BCM_MidHiBrkLiFailrSts,
    &PopupControl::func_MSG_LCMFL_LeFrntDirIndcrFailrSt,
    &PopupControl::func_MSG_LCMFR_RiFrntDirIndcrFailrSt,
    &PopupControl::func_MSG_DCMFL_LeSideDirIndcrLampSt,
    &PopupControl::func_MSG_DCMFR_RiSideDirIndcrLampSt,
    &PopupControl::func_MSG_LCMRL_LeReDirIndcrFailrSt,
    &PopupControl::func_MSG_LCMRR_RiReDirIndcrFailrSt,
    &PopupControl::func_MSG_BCM_AutoWiprCtrlWarn,
    &PopupControl::func_MSG_BCM_KeyDetectWarn,
    &PopupControl::func_MSG_BCM_KeyInsideWarn,
    &PopupControl::func_MSG_BCM_ImobBkpWarn,
    &PopupControl::func_MSG_BCM_BrkPedlIndcnWarn,
    &PopupControl::func_MSG_BCM_PwrRlyErrWarn,
    &PopupControl::func_MSG_BCM_LvlBattULoWarn,
    &PopupControl::func_MSG_BCM_EgyLvlDegradationWarn,
    &PopupControl::func_MSG_BCM_ImobMstWarn,
    &PopupControl::func_MSG_ADAS_ACC_GoNotifier,
    &PopupControl::func_MSG_ADAS_HWA_Warn_St,
    &PopupControl::func_MSG_ADAS_HWA_HandsonReq,
    &PopupControl::func_MSG_ADAS_FCWRequest,
    &PopupControl::func_MSG_ADAS_L3_HandsonReq,
    &PopupControl::func_MSG_ADAS_FCTB_St,
    &PopupControl::func_MSG_ADAS_RCTB_St,
    &PopupControl::func_MSG_ADAS_LDW_St,
    &PopupControl::func_MSG_ADAS_LKA_St,
    &PopupControl::func_MSG_DMS_DMSSts,
    &PopupControl::func_MSG_DMS_DMSAbandon_Reason,
    &PopupControl::func_MSG_ETC_RFModule,
    &PopupControl::func_MSG_ETC_ESAMModule,
    &PopupControl::func_MSG_ETC_Antitemper,
    &PopupControl::func_MSG_PLCU_ParkLockSt,
    &PopupControl::func_MSG_VCU_VehSrvcWarn,
    &PopupControl::func_MSG_BMS_VehHvIsoErr,
    &PopupControl::func_MSG_DCMFL_LeSideDirIndcrFailrSt,
    &PopupControl::func_MSG_DCMFR_RiSideDirIndcrFailrSt,
    &PopupControl::func_MSG_ANRC_PrkgMEBWarnType,
    &PopupControl::func_MSG_ANRC_MEB_FuncSts,
    &PopupControl::func_MSG_DMS_DrowsnsLevel,
    &PopupControl::func_MSG_ADAS_FCTA_Left_Active_St,
    &PopupControl::func_MSG_ADAS_FCTA_Right_Active_St,
};


PopupControl::PopupControl()
{
    _PopupStrategy = PopupStrategy::instance();

    connect(_PopupStrategy, &PopupStrategy::notifyWarningState, this, &PopupControl::notifyWarningState, Qt::QueuedConnection);
    connect(_PopupStrategy, &PopupStrategy::sendToOtherProcess, this, &PopupControl::sendToOtherProcess, Qt::QueuedConnection);
    connect(_PopupStrategy, &PopupStrategy::sendToOtherCtrl, this, &PopupControl::sendToOtherCtrl, Qt::QueuedConnection);
    qRegisterMetaType<Popup*>("Popup*");
    connect(_PopupStrategy, SIGNAL(PropertyChange(Popup*)), this, SIGNAL(PropertyChange(Popup*)));
    connect(_PopupStrategy, SIGNAL(PropertyChange(int, QVariant)), this, SIGNAL(PropertyChange(int, QVariant)));
    m_seatbelt = new HMICustomTimer(5, false);

    connect(m_seatbelt, &HMICustomTimer::timeout, this, [=](){
        static bool seatBeltLightOn = false;
        seatBeltLightOn = !seatBeltLightOn;

        if(2 == SeatBeltStatus.kdrv_stblt_sts){
            setPropertyValue(PROPERTYID_SEAT_DRIV_VISIBLE, seatBeltLightOn);
        }
        if(2 == SeatBeltStatus.kpas_stblt_sts){
            setPropertyValue(PROPERTYID_SEAT_PAS_VISIBLE, seatBeltLightOn);
        }
        if(2 == SeatBeltStatus.krl_stblt_sts){
            setPropertyValue(PROPERTYID_SEAT_RL_VISIBLE, seatBeltLightOn);
        }
        if(2 == SeatBeltStatus.krr_stblt_sts){
            setPropertyValue(PROPERTYID_SEAT_RR_VISIBLE, seatBeltLightOn);
        }
        if(2 == SeatBeltStatus.krm_stblt_sts){
            setPropertyValue(PROPERTYID_SEAT_RM_VISIBLE, seatBeltLightOn);
        }

    });

    m_seatbelt->start();
    start(QThread::NormalPriority);
}

PopupControl::~PopupControl()
{
    delete PopupControl::instance();
}

//136 ESC_HmiLampReqBrkSys
void PopupControl::func_MSG_BRAKE_SYSTEM()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BRAKE_SYSTEM,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC10, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC9, POP_ALARM_OFF);
    }else {
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC10, POP_ALARM_ON);//制动系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC10, POP_ALARM_OFF);
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC9, POP_ALARM_ON);//制动系统严重故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC9, POP_ALARM_OFF);
        }
    }
}

//136 ESC_HmiLampReqEpbFlt
void PopupControl::func_MSG_EPB_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EPB_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC16, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupB21, POP_ALARM_OFF);
    }else {
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC16, POP_ALARM_ON);//EPB系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC16, POP_ALARM_OFF);
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB21, POP_ALARM_ON);//EPB处于诊断模式
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB21, POP_ALARM_OFF);
        }
    }
}

//136 ESC_HmiLampReqHdc
void PopupControl::func_MSG_HDC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HDC,msg)
    if(msg.isTimeout)
    {
        _PopupStrategy->updateDisplayList(&PopupC30, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupB23, POP_ALARM_OFF);
    }else {
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC30, POP_ALARM_ON);//陡坡缓降工作中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC30, POP_ALARM_OFF);
        }

        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB23, POP_ALARM_ON);//陡坡缓降系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB23, POP_ALARM_OFF);
        }
    }
}

//136 ESC_HMIDrvPrstInAVH
void PopupControl::func_MSG_DRV_AVH()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DRV_AVH,msg)
    if(msg.isTimeout)
    {
        _PopupStrategy->updateDisplayList(&PopupC18, POP_ALARM_OFF);
    }else {
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC18, POP_ALARM_ON);//请系上安全带并关闭车门
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC18, POP_ALARM_OFF);
        }
    }
}

//136 ESC_HmiLampReqEsc
void PopupControl::func_MSG_ESC_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ESC_FAULT,msg)
    if(msg.isTimeout)
    {
        _PopupStrategy->updateDisplayList(&PopupB17, POP_ALARM_OFF);
    }else {
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB17, POP_ALARM_ON);//ESC故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB17, POP_ALARM_OFF);
        }
    }
}

//130 EPS_SteerWarnLamp_Rq
void PopupControl::func_MSG_STEERING_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_STEERING_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB25, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupA4, POP_ALARM_OFF);
    } else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB25, POP_ALARM_ON);//转向助力系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB25, POP_ALARM_OFF);
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA4, POP_ALARM_ON);//转向助力系统严重故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA4, POP_ALARM_OFF);
        }
    }
}

//mcu_0 MCU_BATT_VAL
void PopupControl::func_MSG_BATT_LOW()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARGE_PERCENT,msg)
    if(msg.value < 22){
        _PopupStrategy->updateDisplayList(&PopupC24, POP_ALARM_ON);//电池电量较低，请及时充电!
    }else{
        _PopupStrategy->updateDisplayList(&PopupC24, POP_ALARM_OFF);
    }
}

//212 BCM_HmiLampReqBrkPadWarn
void PopupControl::func_MSG_BRAKE_PADS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BRAKE_PADS,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB13, POP_ALARM_OFF);
    }else{
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB13, POP_ALARM_ON);//请及时更换刹车片
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB13, POP_ALARM_OFF);//请及时更换刹车片
        }
    }
}

//212 BCM_ErrWipr
void PopupControl::func_MSG_WIPER_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_WIPER_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB29, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB29, POP_ALARM_ON);//前雨刮故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB29, POP_ALARM_OFF);//前雨刮故障
        }
    }
}

//F7 BMS_HvBattErrSt
void PopupControl::func_MSG_BATT_ERROR()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BATT_ERROR,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA9, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupB28, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB28, POP_ALARM_ON);//电池功率受限
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB28, POP_ALARM_OFF);//电池功率受限
        }

        if(0x02 == msg.value
                || 0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA9, POP_ALARM_ON);//电池严重故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA9, POP_ALARM_OFF);//电池严重故障
        }
    }
}

//138 ESC_HmiLampReqTCS
void PopupControl::func_MSG_TCS_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TCS_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB20, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB20, POP_ALARM_ON);//TCS故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB20, POP_ALARM_OFF);
        }
    }
}

//138 ESC_HmiLampReqABS
void PopupControl::func_MSG_ABS_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ABS_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB19, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB19, POP_ALARM_ON);//ABS故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB19, POP_ALARM_OFF);
        }
    }
}

//138 ESC_HmiLampReqEPBMode
void PopupControl::func_MSG_EPB_MODE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_EPB_MODE,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC13, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC15, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC12, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC29, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC14, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC13, POP_ALARM_ON);//请系上安全带
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC13, POP_ALARM_OFF);
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC15, POP_ALARM_ON);//请使用开关手动释放EPB
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC15, POP_ALARM_OFF);
        }

        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC12, POP_ALARM_ON);//请踩下制动踏板释放EPB
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC12, POP_ALARM_OFF);
        }

        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC29, POP_ALARM_ON);//驻车力不足，无法驻车
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC29, POP_ALARM_OFF);
        }

        if(0x05 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC14, POP_ALARM_ON);//坡度过大无法驻车
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC14, POP_ALARM_OFF);
        }
    }
}

//138 ESC_HmiLampReqAVHSts
void PopupControl::func_MSG_AVH_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AVH_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB22, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB22, POP_ALARM_ON);//自动驻车故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB22, POP_ALARM_OFF);
        }
    }
}

//138 ESC_HmiLampReqTCSOff
void PopupControl::func_MSG_TCS_OFF()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TCS_OFF,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC28, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC28, POP_ALARM_ON);//ESC/TCS已关闭
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC28, POP_ALARM_OFF);
        }
    }
}

//131 ESC_CtrlrAvlEbd
void PopupControl::func_MSG_AVL_EBD_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AVL_EBD_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA1, POP_ALARM_OFF);
    }else{
        if(0x00 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA1, POP_ALARM_ON);//制动力分配系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA1, POP_ALARM_OFF);
        }
    }
}

//245 BCM_BrkFldLvlDisp
void PopupControl::func_MSG_LOW_BRAKE_FLUID()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LOW_BRAKE_FLUID,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC11, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC11, POP_ALARM_ON);//制动液位低
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC11, POP_ALARM_OFF);//制动液位低
        }
    }
}

//245 BCM_WtrLvlDisp
void PopupControl::func_MSG_LOW_GLASS_WATER()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LOW_GLASS_WATER,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB15, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB15, POP_ALARM_ON);//请添加玻璃洗涤液
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB15, POP_ALARM_OFF);//请添加玻璃洗涤液
        }
    }
}

//245 BCM_PepsAdvKeyFobBattChrgnSt
void PopupControl::func_MSG_KEY_BATT_LOW()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_KEY_BATT_LOW,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB16, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB16, POP_ALARM_ON);//钥匙电量低
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB16, POP_ALARM_OFF);//钥匙电量低
        }
    }
}

//17C SUM_SuspSysFailrSts
void PopupControl::func_MSG_SUSPENSION_SYSTEM_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SUSPENSION_SYSTEM_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA5, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC20, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA5, POP_ALARM_ON);//悬架系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA5, POP_ALARM_OFF);
        }

        if(0x02 == msg.value
                || 0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC20, POP_ALARM_ON);//悬架系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC20, POP_ALARM_OFF);
        }
    }
}

//17C SUM_SuspSysProtnSts
void PopupControl::func_MSG_SUSPENSION_SYSTEM()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SUSPENSION_SYSTEM,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC21, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC34, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC35, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC36, POP_ALARM_OFF);/*
        _PopupStrategy->updateDisplayList(&PopupC37, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC38, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC39, POP_ALARM_OFF);*/
    }else{

        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC21, POP_ALARM_ON);//悬架系统维修模式
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC21, POP_ALARM_OFF);
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC34, POP_ALARM_ON);//悬架系统过热
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC34, POP_ALARM_OFF);
        }

        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC35, POP_ALARM_ON);//悬架系统繁忙
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC35, POP_ALARM_OFF);
        }

        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC36, POP_ALARM_ON);//海拔过高，悬架系统异常
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC36, POP_ALARM_OFF);
        }

//        if(0x05 == msg.value)
//        {
//            _PopupStrategy->updateDisplayList(&PopupC37, POP_ALARM_ON);//汽车升起，悬架不可用
//        }
//        else{
//            _PopupStrategy->updateDisplayList(&PopupC37, POP_ALARM_OFF);
//        }

//        if(0x06 == msg.value)
//        {
//            _PopupStrategy->updateDisplayList(&PopupC38, POP_ALARM_ON);//气泵压力低，悬架系统异常
//        }
//        else{
//            _PopupStrategy->updateDisplayList(&PopupC38, POP_ALARM_OFF);
//        }

//        if(0x07 == msg.value)
//        {
//            _PopupStrategy->updateDisplayList(&PopupC39, POP_ALARM_ON);//车辆倾斜，悬架不可用
//        }
//        else{
//            _PopupStrategy->updateDisplayList(&PopupC39, POP_ALARM_OFF);
//        }
    }
}

//17C SUM_DampCtrlLimpHome
void PopupControl::func_MSG_SUM_DAMP_LIMP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SUM_DAMP_LIMP,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB24, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB24, POP_ALARM_ON);//悬架系统跛行模式，请注意安全
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB24, POP_ALARM_OFF);
        }
    }
}

//200 BMS_HVBattTherRunaway
void PopupControl::func_MSG_HV_BATT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HV_BATT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA14, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA14, POP_ALARM_ON);//动力电池热失控，请立即停车并远离车辆
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA14, POP_ALARM_OFF);
        }
    }
}

//183 SCM_E_ShiftFault
void PopupControl::func_MSG_SHIFTER_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SHIFTER_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA15, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value
                || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA15, POP_ALARM_ON);//换挡器故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA15, POP_ALARM_OFF);//换挡器故障
        }
    }
}

//152 BCM_ImmWarning
void PopupControl::func_MSG_IMM_WARNING()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_IMM_WARNING,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB4, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupB5, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB4, POP_ALARM_ON);//防盗认证失败
        }
        else if(0x00 == msg.value
                || 0x02 == msg.value){
            _PopupStrategy->updateDisplayList(&PopupB4, POP_ALARM_OFF);//防盗认证失败
        }
        else{}

        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB5, POP_ALARM_ON);//防盗认证系统故障！
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB5, POP_ALARM_OFF);//防盗认证系统故障！
        }
    }
}

//123 eBooster_HmiLampReqiboosterFlt
void PopupControl::func_MSG_BOOSTER_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BOOSTER_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA2, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA2, POP_ALARM_ON);//制动助力故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA2, POP_ALARM_OFF);
        }
    }
}

//1BC SUM_SuspChassisHeiMovmtDir
void PopupControl::func_MSG_SUSPENSION_MOVE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SUSPENSION_MOVE,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC31, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC32, POP_ALARM_OFF);
    }else{
        if(0x00 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC31, POP_ALARM_ON);//悬架下降
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC31, POP_ALARM_OFF);
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC32, POP_ALARM_ON);//悬架上升
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC32, POP_ALARM_OFF);
        }
    }
}

//1C0 ADAS_LKS_Active_St
void PopupControl::func_MSG_ADAS_LKS_ACTIVE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LKS_ACTIVE,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD21, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value
                || 0x03 == msg.value
                || 0x04 == msg.value
                || 0x06 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD21, POP_ALARM_ON);//请接管方向盘
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD21, POP_ALARM_OFF);//请接管方向盘
        }
    }
}

//1C0 ADAS_ELK_Active_St
void PopupControl::func_MSG_ADAS_ELK_ACTIVE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ELK_ACTIVE,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD22, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value
                || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD22, POP_ALARM_ON);//ELK激活
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD22, POP_ALARM_OFF);
        }
    }
}

//1C0 ADAS_RCW_St
void PopupControl::func_MSG_ADAS_RCW()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RCW,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD73, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD73, POP_ALARM_ON);//RCW功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD73, POP_ALARM_OFF);//RCW功能故障
        }

    }
}

//1C0 ADAS_RCTA_St
void PopupControl::func_MSG_ADAS_RCTA()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RCTA,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD78, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD78, POP_ALARM_ON);//RCTA功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD78, POP_ALARM_OFF);//RCTA功能故障
        }
    }
}

//1C0 ADAS_LCA_St
void PopupControl::func_MSG_ADAS_LCA()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LCA,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD82, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD82, POP_ALARM_ON);//BSD功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD82, POP_ALARM_OFF);//BSD功能故障
        }

    }
}

//1C0 ADAS_ELK_St
void PopupControl::func_MSG_ADAS_ELK()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ELK,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD83, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD83, POP_ALARM_ON);//ELK功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD83, POP_ALARM_OFF);//ELK功能故障
        }
    }
}

//1C1 ADAS_ACC_Warn_St
void PopupControl::func_MSG_ADAS_ACC_WARN()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ACC_WARN,msg)
 /*[NACA-442817] ACC无法激活/ACC请接管车辆无鸣响*/
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_ACC_EXITED,AUDIO_INDEX_ACC_EXITED,!msg.isTimeout&&msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_ACC_UNABLE,AUDIO_INDEX_ACC_UNABLE,!msg.isTimeout&&msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_ACC_TAKEOVER,AUDIO_INDEX_ACC_TAKEOVER,!msg.isTimeout&&msg.value==0x3?AUDIO_PLAY:AUDIO_STOP);
    accWarnStatus = msg;
    handleACCWarnReason();
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD24, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD24, POP_ALARM_ON);//请接管车辆
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD24, POP_ALARM_OFF);//请接管车辆
        }

    }
}

//1C1 ADAS_TSR_Operating_St
void PopupControl::func_MSG_ADAS_TSR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TSR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD70, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD70, POP_ALARM_ON);//TSR功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD70, POP_ALARM_OFF);//TSR功能故障
        }
    }
}

//1C1 ADAS_AHB_St
void PopupControl::func_MSG_ADAS_AHB_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_AHB_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD72, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD72, POP_ALARM_ON);//IHBC功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD72, POP_ALARM_OFF);//IHBC功能故障
        }

    }
}

//1C1 ADAS_ACC_St
void PopupControl::func_MSG_ADAS_ACC_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ACC_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD84, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD95, POP_ALARM_OFF);
    }else{
        accFault = msg.value;
        if(0x07 == accFault)
        {
            _PopupStrategy->updateDisplayList(&PopupD84, POP_ALARM_ON);//ACC功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD84, POP_ALARM_OFF);//ACC功能故障
        }
        handleACCSpeedLimit();
    }
}

//1C1 ADAS_TSR_LimitSpeed
void PopupControl::func_MSG_TST_LIMIT_SPEED()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TST_LIMIT_SPEED,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD95, POP_ALARM_OFF);
    }else{
        tstLimitSpeed = msg.value;
        handleACCSpeedLimit();
        tstLimitSpeed_BackUp = tstLimitSpeed;
    }
}

//1C4 ADAS_L3warningstatus
void PopupControl::func_MSG_ADAS_L3_WARNING()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_L3_WARNING,msg)
 /*[NACA-442830] bug:HWA脱手中的分级报警无鸣响*/
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_LEVEL1_HANDSON,AUDIO_INDEX_HWA_LEVEL1_HANDSON,!msg.isTimeout&&msg.value==0x3?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_LEVEL2_HANDSON,AUDIO_INDEX_HWA_LEVEL2_HANDSON,!msg.isTimeout&&msg.value==0x4?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_HANDSOFF,AUDIO_INDEX_HWA_HANDSOFF,!msg.isTimeout&&msg.value==0x5?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_GRADING_ALARM,AUDIO_INDEX_HWA_GRADING_ALARM,!msg.isTimeout&&msg.value==0x6?AUDIO_PLAY:AUDIO_STOP);

    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_ACC_CRUISE_EXITED,AUDIO_INDEX_ACC_CRUISE_EXITED,gi_ADAS_L3warningstatus==0x6&&msg.value==0x0?AUDIO_PLAY:AUDIO_STOP);
    gi_ADAS_L3warningstatus = msg.value;
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD37, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD29, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD39, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD30, POP_ALARM_OFF);
    }else{
        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD37, POP_ALARM_ON);//请接管方向盘
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD37, POP_ALARM_OFF);//请接管方向盘
        }

        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD29, POP_ALARM_ON);//请监视道路情况
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD29, POP_ALARM_OFF);//请监视道路情况
        }

        if(0x05 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD39, POP_ALARM_ON);//请接管车辆
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD39, POP_ALARM_OFF);//请接管车辆
        }

        if(0x06 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD30, POP_ALARM_ON);//安全停车中，请接管车辆
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD30, POP_ALARM_OFF);//安全停车中，请接管车辆
        }
    }
}

//1C4 ADAS_HWA_ILC_HandsonReq
void PopupControl::func_MSG_ADAS_HWA_HANDSON()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_HWA_HANDSON,msg)
/*[NACA-442831] bug:自动变道手离方向盘报警无鸣响*/
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_HANDSON_AUTOLANE,AUDIO_INDEX_HWA_HANDSON_AUTOLANE,!msg.isTimeout&&msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);

    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD97, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD97, POP_ALARM_ON);//请将双手放在方向盘上
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD97, POP_ALARM_OFF);//请将双手放在方向盘上
        }
    }
}

//1C4 ADAS_HWA_ILC_St
void PopupControl::func_MSG_ADAS_HWA_ST()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_HWA_ST,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD31, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD32, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD33, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD34, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD35, POP_ALARM_OFF);
    }else{
        if(0x07 == msg.value || 0x0E == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD35, POP_ALARM_ON);//自动变道故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD35, POP_ALARM_OFF);//自动变道故障
        }
        hwaSt = msg.value;
        handleADASHWA();
    }
}

//1C4 ADAS_HWA_ILC_AbortReason
void PopupControl::func_MSG_ADAS_HWA_ABORT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_HWA_ABORT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD31, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD32, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD33, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD34, POP_ALARM_OFF);
    }else{
        hwaAbort = msg.value;
        handleADASHWA();
    }
}

//1C4 ADAS_DOW_St
void PopupControl::func_MSG_ADAS_DOW_ST()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_DOW_ST,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD71, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD71, POP_ALARM_ON);//DOW功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD71, POP_ALARM_OFF);//DOW功能故障
        }
    }
}

//1C4 ADAS_HWA_status
void PopupControl::func_MSG_ADSS_HWA_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADSS_HWA_STATUS,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD85, POP_ALARM_OFF);
    }else{
        if(0x07 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD85, POP_ALARM_ON);//HWA 功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD85, POP_ALARM_OFF);//HWA 功能故障
        }

    }
}

//1C4 ADAS_L3availablestatus
void PopupControl::func_MSG_ADAS_L3_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_L3_STATUS,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD89, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD89, POP_ALARM_ON);//脱手巡航启动，可以将手放开方向盘
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD89, POP_ALARM_OFF);//脱手巡航启动，可以将手放开方向盘
        }
    }
}

//230 ADAS_ControllerFaultStatus
void PopupControl::func_MSG_ADAS_CONTROLLER_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_CONTROLLER_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD36, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD36, POP_ALARM_ON);//自动驾驶控制器故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD36, POP_ALARM_OFF);//自动驾驶控制器故障
        }
    }
}

//23F ADAS_FMRRSensorBloc_St
void PopupControl::func_MSG_ADAS_FMRRSENSOR_BLOC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FMRRSENSOR_BLOC,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD40, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD40, POP_ALARM_ON);//前雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD40, POP_ALARM_OFF);//前雷达故障
        }
    }
}

//23F ADAS_FMRRSensorFail_St
void PopupControl::func_MSG_ADAS_FMRRSENSOR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FMRRSENSOR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD64, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD64, POP_ALARM_ON);//前雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD64, POP_ALARM_OFF);//前雷达故障
        }
    }
}

//23F ADAS_FCamSensorBloc_St
void PopupControl::func_MSG_ADAS_FCAMSENSOR_BLOC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCAMSENSOR_BLOC,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD41, POP_ALARM_OFF);
    }else{

        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD41, POP_ALARM_ON);//前摄像头遮挡
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD41, POP_ALARM_OFF);//前摄像头遮挡
        }
    }
}

//23F ADAS_LFSRRSensorBloc_St
void PopupControl::func_MSG_ADSS_LFSRRSENSOR_BLOC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADSS_LFSRRSENSOR_BLOC,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD42, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD42, POP_ALARM_ON);//左前角雷达遮挡
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD42, POP_ALARM_OFF);//左前角雷达遮挡
        }
    }
}

//23F ADAS_LRSRRSensorBloc_St
void PopupControl::func_MSG_ADAS_LRSRRSENSOR_BLOC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LRSRRSENSOR_BLOC,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD43, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD43, POP_ALARM_ON);//左后角雷达遮挡
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD43, POP_ALARM_OFF);//左后角雷达遮挡
        }
    }
}

//23F ADAS_RRSRRSensorBloc_St
void PopupControl::func_MSG_ADAS_RRSRRSENSOR_BLOC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RRSRRSENSOR_BLOC,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD44, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD44, POP_ALARM_ON);//右后角雷达遮挡
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD44, POP_ALARM_OFF);//右后角雷达遮挡
        }
    }
}

//23F ADAS_RFSRRSensorBloc_St
void PopupControl::func_MSG_ADAS_RFSRRSENSOR_BLOC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RFSRRSENSOR_BLOC,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD45, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD45, POP_ALARM_ON);//右前角雷达遮挡
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD45, POP_ALARM_OFF);//右前角雷达遮挡
        }
    }
}

//23F ADAS_FMRRSensorCali_St
void PopupControl::func_MSG_ADAS_FMRRSENSOR_CALI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FMRRSENSOR_CALI,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD46, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD52, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD58, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD46, POP_ALARM_ON);//前雷达校准失败
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD46, POP_ALARM_OFF);//前雷达校准失败
        }

        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD52, POP_ALARM_ON);//前雷达未校准
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD52, POP_ALARM_OFF);//前雷达未校准
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD58, POP_ALARM_ON);//前雷达校准中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD58, POP_ALARM_OFF);//前雷达校准中
        }
    }
}

//23F ADAS_FCamSensorCali_St
void PopupControl::func_MSG_ADAS_FCAMSENSOR_CALI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCAMSENSOR_CALI,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD53, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD47, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD59, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD53, POP_ALARM_ON);//前摄像头未校准
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD53, POP_ALARM_OFF);//前摄像头未校准
        }
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD47, POP_ALARM_ON);//前摄像头校准失败
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD47, POP_ALARM_OFF);//前摄像头校准失败
        }
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD59, POP_ALARM_ON);//前摄像头校准中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD59, POP_ALARM_OFF);//前摄像头校准中
        }
    }
}

//23F ADAS_LFSRRSensorCali_St
void PopupControl::func_MSG_ADAS_LFSRRSENSOR_CALI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LFSRRSENSOR_CALI,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD48, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD54, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD60, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD48, POP_ALARM_ON);//左前角雷达校准失败
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD48, POP_ALARM_OFF);//左前角雷达校准失败
        }
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD54, POP_ALARM_ON);//左前角雷达未校准
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD54, POP_ALARM_OFF);//左前角雷达未校准
        }
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD60, POP_ALARM_ON);//左前角雷达校准中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD60, POP_ALARM_OFF);//左前角雷达校准中
        }
    }
}

//23F ADAS_LRSRRSensorCali_St
void PopupControl::func_MSG_ADAS_LRSRRSENSOR_CALI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LRSRRSENSOR_CALI,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD49, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD55, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD61, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD49, POP_ALARM_ON);//左后角雷达校准失败
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD49, POP_ALARM_OFF);//左后角雷达校准失败
        }
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD55, POP_ALARM_ON);//左后角雷达未校准
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD55, POP_ALARM_OFF);//左后角雷达未校准
        }
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD61, POP_ALARM_ON);//左后角雷达校准中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD61, POP_ALARM_OFF);//左后角雷达校准中
        }
    }
}

//23F ADAS_RRSRRSensorCali_St
void PopupControl::func_MSG_ADAS_RRSRRSENSOR_CALI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RRSRRSENSOR_CALI,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD50, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD56, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD62, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD50, POP_ALARM_ON);//右后角雷达校准失败
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD50, POP_ALARM_OFF);//右后角雷达校准失败
        }
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD56, POP_ALARM_ON);//右后角雷达未校准
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD56, POP_ALARM_OFF);//右后角雷达未校准
        }
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD62, POP_ALARM_ON);//右后角雷达校准中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD62, POP_ALARM_OFF);//右后角雷达校准中
        }
    }
}

//23F ADAS_RFSRRSensorCali_St
void PopupControl::func_MSG_ADAS_RFSRRSENSOR_CALI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RFSRRSENSOR_CALI,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD51, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD57, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD63, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD51, POP_ALARM_ON);//右前角雷达校准失败
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD51, POP_ALARM_OFF);//右前角雷达校准失败
        }
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD57, POP_ALARM_ON);//右前角雷达未校准
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD57, POP_ALARM_OFF);//右前角雷达未校准
        }
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD63, POP_ALARM_ON);//右前角雷达校准中
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD63, POP_ALARM_OFF);//右前角雷达校准中
        }
    }
}

//23F ADAS_FCamSensorFail_St
void PopupControl::func_MSG_ADAS_FCMASENSOR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCMASENSOR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD65, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD65, POP_ALARM_ON);//前摄像头故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD65, POP_ALARM_OFF);//前摄像头故障
        }
    }
}

//23F ADAS_LFSRRSensorFail_St
void PopupControl::func_MSG_ADAS_LFSRRSENSOR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LFSRRSENSOR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD66, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD66, POP_ALARM_ON);//左前角雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD66, POP_ALARM_OFF);//左前角雷达故障
        }
    }
}

//23F ADAS_LRSRRSensorFail_St
void PopupControl::func_MSG_ADAS_LRSRRSENSOR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LRSRRSENSOR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD67, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD67, POP_ALARM_ON);//左后角雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD67, POP_ALARM_OFF);//左后角雷达故障
        }
    }
}

//23F ADAS_RRSRRSensorFail_St
void PopupControl::func_MSG_ADAS_RRSRRSENSOR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RRSRRSENSOR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD68, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD68, POP_ALARM_ON);//右后角雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD68, POP_ALARM_OFF);//右后角雷达故障
        }
    }
}

//23F ADAS_RFSRRSensorFail_St
void PopupControl::func_MSG_ADAS_RFSRRSENSOR_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RFSRRSENSOR_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD69, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD69, POP_ALARM_ON);//右前角雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD69, POP_ALARM_OFF);//右前角雷达故障
        }
    }
}

//1C3 ADAS_FCW_St
void PopupControl::func_MSG_ADAS_FCW_ST()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCW_ST,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD74, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD74, POP_ALARM_ON);//FCW功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD74, POP_ALARM_OFF);//FCW功能故障
        }
    }
}

//1C3 ADAS_AEB_St
void PopupControl::func_MSG_ADAS_AEB_ST()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_AEB_ST,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD75, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD75, POP_ALARM_ON);//AEB功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD75, POP_ALARM_OFF);//AEB功能故障
        }
    }
}

//1C3 ADAS_FCTA_St
void PopupControl::func_MSG_ADAS_FCTA_ST()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCTA_ST,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD76, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD76, POP_ALARM_ON);//FCTA功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD76, POP_ALARM_OFF);//FCTA功能故障
        }
    }
}
//1C3 ADAS_ADASEBREQTYP
void PopupControl::func_MSG_ADAS_ADASEBREQTYP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ADASEBREQTYP,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD17, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD18, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD19, POP_ALARM_OFF);

    }else{
        if(0x03 == msg.value || 0x02 == msg.value || 0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD17, POP_ALARM_ON);//AEB启动
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD17, POP_ALARM_OFF);//AEB启动
        }
        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD18, POP_ALARM_ON);//FCTB启动
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD18, POP_ALARM_OFF);//FCTB启动
        }
        if(0x05 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD19, POP_ALARM_ON);//RCTB启动
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD19, POP_ALARM_OFF);//RCTB启动
        }
    }
}

//DB_IPU_DCDCSts IPU_EEMDCDCFailrSts
void PopupControl::func_MSG_IPU_EEM_DCDC_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_IPU_EEM_DCDC_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA10, POP_ALARM_OFF);
    }else{
        if(0x02 == msg.value
                || 0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA10, POP_ALARM_ON);//充电系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA10, POP_ALARM_OFF);//充电系统故障
        }
    }
}

//248 BCM_TireMonSysSts
void PopupControl::func_MSG_TIRE_SYSTEM_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TIRE_SYSTEM_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB59, POP_ALARM_OFF);
    }else{
        tireSysFault = static_cast<int>(msg.value);
        handleTireFault();
    }
}
//MSG_BCM_AutoLiCtrlWarn
void PopupControl::func_MSG_BCM_AutoLiCtrlWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_AutoLiCtrlWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB32, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB32, POP_ALARM_ON);//自动远光灯系统故障
        }else{
            _PopupStrategy->updateDisplayList(&PopupB32, POP_ALARM_OFF);
        }
    }
}

//BCM_HeadLightOpenWarn
void PopupControl::func_MSG_BCM_HeadLightOpenWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_HeadLightOpenWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC49, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC49, POP_ALARM_ON);//请打开大灯
        }else{
            _PopupStrategy->updateDisplayList(&PopupC49, POP_ALARM_OFF);
        }
    }
}

//LCMFL_LeFrntPosnLampFltSts
void PopupControl::func_MSG_LCMFL_LeFrntPosnLampFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFL_LeFrntPosnLampFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB61, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB61, POP_ALARM_ON);//左前位置灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB61, POP_ALARM_OFF);

        }
    }
}

//LCMFR_RiFrntPosnLampFltSts
void PopupControl::func_MSG_LCMFR_RiFrntPosnLampFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFR_RiFrntPosnLampFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB62, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB62, POP_ALARM_ON);//右前位置灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB62, POP_ALARM_OFF);

        }
    }
}
//LCMRL_LeRePosnFailrSt
void PopupControl::func_MSG_LCMRL_LeRePosnFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMRL_LeRePosnFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB63, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB63, POP_ALARM_ON);//左后位置灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB63, POP_ALARM_OFF);

        }
    }
}
//LCMRR_RiRePosnFailrSt
void PopupControl::func_MSG_LCMRR_RiRePosnFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMRR_RiRePosnFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB64, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB64, POP_ALARM_ON);//右后位置灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB64, POP_ALARM_OFF);

        }
    }
}
//LCMFL_LeLoBeamFltSts
void PopupControl::func_MSG_LCMFL_LeLoBeamFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFL_LeLoBeamFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB37, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB37, POP_ALARM_ON);//左前近光灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB37, POP_ALARM_OFF);

        }
    }
}
//LCMFR_RiLoBeamFltSts
void PopupControl::func_MSG_LCMFR_RiLoBeamFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFR_RiLoBeamFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB38, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB38, POP_ALARM_ON);//右前近光灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB38, POP_ALARM_OFF);

        }
    }
}
//LCMFL_LeGrpdLampModFltSts
void PopupControl::func_MSG_LCMFL_LeGrpdLampModFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFL_LeGrpdLampModFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB39, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB39, POP_ALARM_ON);//左灯模块故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB39, POP_ALARM_OFF);

        }
    }
}
//LCMFR_RiGrpdLampModFltSts
void PopupControl::func_MSG_LCMFR_RiGrpdLampModFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFR_RiGrpdLampModFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB40, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB40, POP_ALARM_ON);//右灯模块故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB40, POP_ALARM_OFF);

        }
    }
}
//LCMFL_LeHiBeamFltSts
void PopupControl::func_MSG_LCMFL_LeHiBeamFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFL_LeHiBeamFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB41, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB41, POP_ALARM_ON);//左远光灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB41, POP_ALARM_OFF);

        }
    }
}
//LCMFR_RiHiBeamFltSts
void PopupControl::func_MSG_LCMFR_RiHiBeamFltSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFR_RiHiBeamFltSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB42, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB42, POP_ALARM_ON);//右远光灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB42, POP_ALARM_OFF);

        }
    }
}
//SCM_HiBeamSwtFailrSts
void PopupControl::func_MSG_SCM_HiBeamSwtFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SCM_HiBeamSwtFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB43, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB43, POP_ALARM_ON);//远光灯开关故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB43, POP_ALARM_OFF);

        }
    }
}
//BCM_ReLeRvsLiFailrSts
void PopupControl::func_MSG_BCM_ReLeRvsLiFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ReLeRvsLiFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB44, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB44, POP_ALARM_ON);//左倒车灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB44, POP_ALARM_OFF);

        }
    }
}
//BCM_ReRiRvsLiFailrSts
void PopupControl::func_MSG_BCM_ReRiRvsLiFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ReRiRvsLiFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB45, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB45, POP_ALARM_ON);//右倒车灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB45, POP_ALARM_OFF);

        }
    }
}
//BCM_ReLeFogFailrSts
void PopupControl::func_MSG_BCM_ReLeFogFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ReLeFogFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB46, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB46, POP_ALARM_ON);//左后雾灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB46, POP_ALARM_OFF);

        }
    }
}
//BCM_ReRiFogFailrSts
void PopupControl::func_MSG_BCM_ReRiFogFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ReRiFogFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB47, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB47, POP_ALARM_ON);//右后雾灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB47, POP_ALARM_OFF);

        }
    }
}
//LCMFL_LeFltDayLampSts
void PopupControl::func_MSG_LCMFL_LeFltDayLampSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFL_LeFltDayLampSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB48, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB48, POP_ALARM_ON);//左侧日间行车灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB48, POP_ALARM_OFF);

        }
    }
}
//LCMFR_RiFltDayLampSts
void PopupControl::func_MSG_LCMFR_RiFltDayLampSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFR_RiFltDayLampSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB49, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB49, POP_ALARM_ON);//右侧日间行车灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB49, POP_ALARM_OFF);

        }
    }
}
//BCM_ReLeBrkLiFailrSts
void PopupControl::func_MSG_BCM_ReLeBrkLiFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ReLeBrkLiFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB50, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB50, POP_ALARM_ON);//左后制动灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB50, POP_ALARM_OFF);

        }
    }
}
//BCM_ReRiBrkLiFailrSts
void PopupControl::func_MSG_BCM_ReRiBrkLiFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ReRiBrkLiFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB51, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB51, POP_ALARM_ON);//右后制动灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB51, POP_ALARM_OFF);

        }
    }
}
//BCM_MidHiBrkLiFailrSts
void PopupControl::func_MSG_BCM_MidHiBrkLiFailrSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_MidHiBrkLiFailrSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB52, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB52, POP_ALARM_ON);//高位制动灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB52, POP_ALARM_OFF);

        }
    }
}
//LCMFL_LeFrntDirIndcrFailrSt
void PopupControl::func_MSG_LCMFL_LeFrntDirIndcrFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFL_LeFrntDirIndcrFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB53, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value )
        {
            _PopupStrategy->updateDisplayList(&PopupB53, POP_ALARM_ON);//左前转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB53, POP_ALARM_OFF);

        }
    }
}
//DCMFL_LeSideDirIndcrFailrSt
void PopupControl::func_MSG_DCMFL_LeSideDirIndcrFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DCMFL_LeSideDirIndcrFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB55, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB55, POP_ALARM_ON);//左侧转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB55, POP_ALARM_OFF);

        }
    }
}
//DCMFR_RiSideDirIndcrFailrSt
void PopupControl::func_MSG_DCMFR_RiSideDirIndcrFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DCMFR_RiSideDirIndcrFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB56, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB56, POP_ALARM_ON);//右侧转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB56, POP_ALARM_OFF);

        }
    }
}
//LCMFR_RiFrntDirIndcrFailrSt
void PopupControl::func_MSG_LCMFR_RiFrntDirIndcrFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMFR_RiFrntDirIndcrFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB54, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value )
        {
            _PopupStrategy->updateDisplayList(&PopupB54, POP_ALARM_ON);//右前转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB54, POP_ALARM_OFF);

        }
    }
}
//DCMFL_LeSideDirIndcrLampSt
void PopupControl::func_MSG_DCMFL_LeSideDirIndcrLampSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DCMFL_LeSideDirIndcrLampSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB55, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB55, POP_ALARM_ON);//左侧转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB55, POP_ALARM_OFF);

        }
    }
}
//DCMFR_RiSideDirIndcrLampSt
void PopupControl::func_MSG_DCMFR_RiSideDirIndcrLampSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DCMFR_RiSideDirIndcrLampSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB56, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB56, POP_ALARM_ON);//右侧转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB56, POP_ALARM_OFF);

        }
    }
}
//LCMRL_LeReDirIndcrFailrSt
void PopupControl::func_MSG_LCMRL_LeReDirIndcrFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMRL_LeReDirIndcrFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB57, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB57, POP_ALARM_ON);//左后转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB57, POP_ALARM_OFF);

        }
    }
}
//LCMRR_RiReDirIndcrFailrSt
void PopupControl::func_MSG_LCMRR_RiReDirIndcrFailrSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCMRR_RiReDirIndcrFailrSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB58, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB58, POP_ALARM_ON);//右后转向灯故障

        }else{
            _PopupStrategy->updateDisplayList(&PopupB58, POP_ALARM_OFF);

        }
    }
}
//BCM_AutoWiprCtrlWarn
void PopupControl::func_MSG_BCM_AutoWiprCtrlWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_AutoWiprCtrlWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB65, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB65, POP_ALARM_ON);//自动雨刮系统故障报警

        }else{
            _PopupStrategy->updateDisplayList(&PopupB65, POP_ALARM_OFF);

        }
    }
}
//BCM_KeyDetectWarn
void PopupControl::func_MSG_BCM_KeyDetectWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_KeyDetectWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC44, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC44, POP_ALARM_ON);//未搜索到钥匙

        }else{
            _PopupStrategy->updateDisplayList(&PopupC44, POP_ALARM_OFF);

        }
    }
}
//BCM_KeyInsideWarn
void PopupControl::func_MSG_BCM_KeyInsideWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_KeyInsideWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC45, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC45, POP_ALARM_ON);//请带好钥匙

        }else{
            _PopupStrategy->updateDisplayList(&PopupC45, POP_ALARM_OFF);

        }
    }
}
//BCM_ImobBkpWarn
void PopupControl::func_MSG_BCM_ImobBkpWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ImobBkpWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC46, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC46, POP_ALARM_ON);//启用immo backup提醒

        }else{
            _PopupStrategy->updateDisplayList(&PopupC46, POP_ALARM_OFF);

        }
    }
}
//BCM_BrkPedlIndcnWarn
void PopupControl::func_MSG_BCM_BrkPedlIndcnWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_BrkPedlIndcnWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC2, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC2, POP_ALARM_ON);//请踩刹车

        }else{
            _PopupStrategy->updateDisplayList(&PopupC2, POP_ALARM_OFF);

        }
    }
}
//BCM_PwrRlyErrWarn
void PopupControl::func_MSG_BCM_PwrRlyErrWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_PwrRlyErrWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB31, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB31, POP_ALARM_ON);//电源继电器错误

        }else{
            _PopupStrategy->updateDisplayList(&PopupB31, POP_ALARM_OFF);

        }
    }
}
//BCM_LvlBattULoWarn
void PopupControl::func_MSG_BCM_LvlBattULoWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_LvlBattULoWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB66, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB66, POP_ALARM_ON);//蓄电池电压低

        }else{
            _PopupStrategy->updateDisplayList(&PopupB66, POP_ALARM_OFF);

        }
    }
}
//BCM_EgyLvlDegradationWarn
void PopupControl::func_MSG_BCM_EgyLvlDegradationWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_EgyLvlDegradationWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB67, POP_ALARM_OFF);

    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB67, POP_ALARM_ON);//进入节电模式

        }else{
            _PopupStrategy->updateDisplayList(&PopupB67, POP_ALARM_OFF);

        }
    }
}
//BCM_ImobMstWarn
void PopupControl::func_MSG_BCM_ImobMstWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BCM_ImobMstWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB4, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupB5, POP_ALARM_OFF);
    }else{
        if(0x02 == msg.value ||0x03 == msg.value||0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB4, POP_ALARM_ON);//防盗认证失败
        }else if(15 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB5, POP_ALARM_ON);//防盗认证系统故障
        }else{
            _PopupStrategy->updateDisplayList(&PopupB4, POP_ALARM_OFF);
            _PopupStrategy->updateDisplayList(&PopupB5, POP_ALARM_OFF);
        }
    }
}
//ADAS_ACC_GoNotifier
void PopupControl::func_MSG_ADAS_ACC_GoNotifier()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ACC_GoNotifier,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD25, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD25, POP_ALARM_ON);//Res 键继续巡航
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD25, POP_ALARM_OFF);
        }
    }
}
//ADAS_HWA_Warn_St
void PopupControl::func_MSG_ADAS_HWA_Warn_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_HWA_Warn_St,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD21, POP_ALARM_OFF);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_EXITED,AUDIO_INDEX_HWA_EXITED,AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_UNABLE,AUDIO_INDEX_HWA_UNABLE,AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_TAKEOVER,AUDIO_INDEX_HWA_TAKEOVER,AUDIO_STOP);
    }else{
            _PopupStrategy->updateDisplayList(&PopupB69,0x01 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//HWA已退出
            _PopupStrategy->updateDisplayList(&PopupD26,0x02 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//HWA 无法激活
            _PopupStrategy->updateDisplayList(&PopupD21,0x03 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请接管方向盘
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_EXITED,AUDIO_INDEX_HWA_EXITED,0x01 == msg.value?AUDIO_PLAY:AUDIO_STOP);
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_UNABLE,AUDIO_INDEX_HWA_UNABLE,0x02 == msg.value?AUDIO_PLAY:AUDIO_STOP);
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_TAKEOVER,AUDIO_INDEX_HWA_TAKEOVER,0x03 == msg.value?AUDIO_PLAY:AUDIO_STOP);
    }
}
//ANRC_PrkgMEBWarnType
void PopupControl::func_MSG_ANRC_PrkgMEBWarnType()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ANRC_PrkgMEBWarnType,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD98, POP_ALARM_OFF);
    }else{
            _PopupStrategy->updateDisplayList(&PopupD98,0x03 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//MEB不可用
    }
}
//ANRC_MEB_FuncSts
void PopupControl::func_MSG_ANRC_MEB_FuncSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ANRC_MEB_FuncSts,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD98, POP_ALARM_OFF);
    }else{
            _PopupStrategy->updateDisplayList(&PopupD98,0x08 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//MEB不可用
    }
}
//DMS_DrowsnsLevel
void PopupControl::func_MSG_DMS_DrowsnsLevel()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DMS_DrowsnsLevel,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD90, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD91, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD92, POP_ALARM_OFF);
/*[NACA-442828] 疲劳报警相关信号无鸣响*/
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FATIGUE_DRIVE_L,AUDIO_INDEX_FATIGUE_DRIVE_L,AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FATIGUE_DRIVE_H,AUDIO_INDEX_FATIGUE_DRIVE_H,AUDIO_STOP);

    }else{
            _PopupStrategy->updateDisplayList(&PopupD90,0x03 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请专心驾驶
            _PopupStrategy->updateDisplayList(&PopupD91,0x02 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请专心驾驶
            _PopupStrategy->updateDisplayList(&PopupD92,0x01 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请专心驾驶
/*[NACA-442828] 疲劳报警相关信号无鸣响*/
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FATIGUE_DRIVE_H,AUDIO_INDEX_FATIGUE_DRIVE_H,!msg.isTimeout&&(msg.value==0x3)?AUDIO_PLAY:AUDIO_STOP);
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FATIGUE_DRIVE_L,AUDIO_INDEX_FATIGUE_DRIVE_L,!msg.isTimeout&&(msg.value==0x2||msg.value==0x1)?AUDIO_PLAY:AUDIO_STOP);

    }
}
//DMS_DistrctnLevel
void PopupControl::func_MSG_DMS_DistrctnLevel()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DMS_DistrctnLevel,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD90, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD91, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD92, POP_ALARM_OFF);
 /*[NACA-442829] 分心报警相关信号无鸣响*/
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DISTRACTION_L,AUDIO_INDEX_DISTRACTION_L,AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DISTRACTION_H,AUDIO_INDEX_DISTRACTION_H,AUDIO_STOP);

    }else{
            _PopupStrategy->updateDisplayList(&PopupD90,0x03 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请专心驾驶
            _PopupStrategy->updateDisplayList(&PopupD91,0x02 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请专心驾驶
            _PopupStrategy->updateDisplayList(&PopupD92,0x01 == msg.value? POP_ALARM_ON:POP_ALARM_OFF);//请专心驾驶
 /*[NACA-442829] 分心报警相关信号无鸣响*/
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DISTRACTION_H,AUDIO_INDEX_DISTRACTION_H,!msg.isTimeout&&(msg.value==0x3)?AUDIO_PLAY:AUDIO_STOP);
            HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DISTRACTION_L,AUDIO_INDEX_DISTRACTION_L,!msg.isTimeout&&(msg.value==0x2||msg.value==0x1)?AUDIO_PLAY:AUDIO_STOP);

    }
}

//ADAS_HWA_HandsonReq
void PopupControl::func_MSG_ADAS_HWA_HandsonReq()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_HWA_HandsonReq,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD96, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD97, POP_ALARM_OFF);

    }else{
         _PopupStrategy->updateDisplayList(&PopupD96, 0x01 == msg.value?POP_ALARM_ON:POP_ALARM_OFF);//请将双手放在方向盘上
         _PopupStrategy->updateDisplayList(&PopupD97, 0x02 == msg.value?POP_ALARM_ON:POP_ALARM_OFF);//请将双手放在方向盘上
    }
}
//ADAS_FCWRequest
void PopupControl::func_MSG_ADAS_FCWRequest()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCWRequest,msg)
     if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA19, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupB71, POP_ALARM_OFF);

    }else{
         _PopupStrategy->updateDisplayList(&PopupB71, 0x01 == msg.value?POP_ALARM_ON:POP_ALARM_OFF);//请保持车距
         _PopupStrategy->updateDisplayList(&PopupA19, 0x02 == msg.value?POP_ALARM_ON:POP_ALARM_OFF);//请保持车距
    }
}
//ADAS_L3_HandsonReq
void PopupControl::func_MSG_ADAS_L3_HandsonReq()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_L3_HandsonReq,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD28, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD28, POP_ALARM_ON);//请将双手放在方向盘上
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD28, POP_ALARM_OFF);
        }
    }
}
//ADAS_FCTB_St
void PopupControl::func_MSG_ADAS_FCTB_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCTB_St,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD77, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD77, POP_ALARM_ON);//FCTB 功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD77, POP_ALARM_OFF);
        }
    }
}
//ADAS_FCTA_Left_Active_St
void PopupControl::func_MSG_ADAS_FCTA_Left_Active_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCTA_Left_Active_St,msg);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTA_LEVEL1_FL,AUDIO_INDEX_FCTA_LEVEL1_FL,!msg.isTimeout&&(msg.value==0x1)?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTA_LEVEL2_FL,AUDIO_INDEX_FCTA_LEVEL2_FL,!msg.isTimeout&&(msg.value==0x2)?AUDIO_PLAY:AUDIO_STOP);

}
//ADAS_FCTA_Right_Active_St
void PopupControl::func_MSG_ADAS_FCTA_Right_Active_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCTA_Right_Active_St,msg);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTA_LEVEL1_FR,AUDIO_INDEX_FCTA_LEVEL1_FR,!msg.isTimeout&&(msg.value==0x1)?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTA_LEVEL2_FR,AUDIO_INDEX_FCTA_LEVEL2_FR,!msg.isTimeout&&(msg.value==0x2)?AUDIO_PLAY:AUDIO_STOP);
}
//ADAS_RCTB_St
void PopupControl::func_MSG_ADAS_RCTB_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_RCTB_St,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD79, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD79, POP_ALARM_ON);//RCTB 功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD79, POP_ALARM_OFF);
        }
    }
}
//ADAS_LDW_St
void PopupControl::func_MSG_ADAS_LDW_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LDW_St,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD80, POP_ALARM_OFF);
    }else{
        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD80, POP_ALARM_ON);//LDW 功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD80, POP_ALARM_OFF);
        }
    }
}
//ADAS_LKA_St
void PopupControl::func_MSG_ADAS_LKA_St()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_LKA_St,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD81, POP_ALARM_OFF);
    }else{
        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD81, POP_ALARM_ON);//LKA 功能故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD81, POP_ALARM_OFF);
        }
    }
}
//DMS_DMSSts
void PopupControl::func_MSG_DMS_DMSSts()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DMS_DMSSts,msg);
    if(msg.isTimeout){
    }else{
        if(!gb_ADAS_DMS_DMSSts)
        {
            if(msg.value==0x1)
                gb_ADAS_DMS_DMSSts = !gb_ADAS_DMS_DMSSts;
        }else
        {
            if(0x0 == msg.value)
            {
                switch(gi_ADAS_DMS_DMSAbandon_Reason)
                {
                case 1:
                    _PopupStrategy->updateDisplayList(&PopupD93, POP_ALARM_ON);
                    _PopupStrategy->updateDisplayList(&PopupD99, POP_ALARM_OFF);
                    _PopupStrategy->updateDisplayList(&PopupD94, POP_ALARM_OFF);
                    break;
                case 2:
                    _PopupStrategy->updateDisplayList(&PopupD93, POP_ALARM_OFF);
                    _PopupStrategy->updateDisplayList(&PopupD99, POP_ALARM_ON);
                    _PopupStrategy->updateDisplayList(&PopupD94, POP_ALARM_OFF);
                    break;
                case 3:
                    _PopupStrategy->updateDisplayList(&PopupD93, POP_ALARM_OFF);
                    _PopupStrategy->updateDisplayList(&PopupD99, POP_ALARM_OFF);
                    _PopupStrategy->updateDisplayList(&PopupD94, POP_ALARM_ON);
                    break;
                default:
                    _PopupStrategy->updateDisplayList(&PopupD93, POP_ALARM_OFF);
                    _PopupStrategy->updateDisplayList(&PopupD99, POP_ALARM_OFF);
                    _PopupStrategy->updateDisplayList(&PopupD94, POP_ALARM_OFF);
                }
            }else if(0x1 == msg.value){
                _PopupStrategy->updateDisplayList(&PopupD93, POP_ALARM_OFF);
                _PopupStrategy->updateDisplayList(&PopupD99, POP_ALARM_OFF);
                _PopupStrategy->updateDisplayList(&PopupD94, POP_ALARM_OFF);
            }
        }
    }
}
//DMS_DMSAbandon_Reason
void PopupControl::func_MSG_DMS_DMSAbandon_Reason()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DMS_DMSAbandon_Reason,msg)
    if(msg.isTimeout){
    }else{
        gi_ADAS_DMS_DMSAbandon_Reason = msg.value;
    }
}
//ETC_RFModule
void PopupControl::func_MSG_ETC_RFModule()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ETC_RFModule,msg);
    SingleMessage msg2;
    INIT_SINGLEMESSAGE_VALUE(MSG_ETC_ESAMModule,msg2);
    SingleMessage msg3;
    INIT_SINGLEMESSAGE_VALUE(MSG_ETC_Antitemper,msg3);
    if((0x01 == msg.value&&!msg.isTimeout)||(0x01 == msg2.value&&!msg2.isTimeout)||(0x01 == msg3.value&&!msg3.isTimeout))
    {
        _PopupStrategy->updateDisplayList(&PopupB68, POP_ALARM_ON);//ETC故障
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupB68, POP_ALARM_OFF);
    }
}
//ETC_ESAMModule
void PopupControl::func_MSG_ETC_ESAMModule()
{
}
//ETC_Antitemper
void PopupControl::func_MSG_ETC_Antitemper()
{
}
//PLCU_ParkLockSt
void PopupControl::func_MSG_PLCU_ParkLockSt()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_PLCU_ParkLockSt,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB27, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB27, POP_ALARM_ON);//减速器驻车锁故障，请尽快维修
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB27, POP_ALARM_OFF);
        }
    }
}
//VCU_VehSrvcWarn
void PopupControl::func_MSG_VCU_VehSrvcWarn()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_VehSrvcWarn,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB70, POP_ALARM_OFF);
    }else{
        if(0x0 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB70, POP_ALARM_ON);//动力系统异常
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB70, POP_ALARM_OFF);
        }
    }
}
//BMS_VehHvIsoErr
void PopupControl::func_MSG_BMS_VehHvIsoErr()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_BMS_VehHvIsoErr,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA18, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA18, POP_ALARM_ON);//绝缘故障,请立即离开
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA18, POP_ALARM_OFF);
        }
    }
}
void PopupControl::func_MSG_TIRE_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TIRE_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB59, POP_ALARM_OFF);
    }else{
        tireFault = static_cast<int>(msg.value);
        handleTireFault();
    }
}

//AC_VCU_MaxPowerAvl VCU_LvWarn
void PopupControl::func_MSG_VCU_LV_WARN()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_LV_WARN,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB60, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupA17, POP_ALARM_OFF);
    }else{
        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB60, POP_ALARM_ON);//低压系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB60, POP_ALARM_OFF);//低压系统故障
        }

        if(0x04 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA17, POP_ALARM_ON);//低压系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA17, POP_ALARM_OFF);//低压系统故障
        }

    }
}

//196 ANRC_PrkgPDCMod
void PopupControl::func_MSG_ANRC_PRKG_PDC_MODE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ANRC_PRKG_PDC_MODE,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD86, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD87, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupD88, POP_ALARM_OFF);
    }else{
        if(0x02 == msg.value
                || 0x07 == msg.value
                || 0x0A == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD86, POP_ALARM_ON);//前雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD86, POP_ALARM_OFF);//前雷达故障
        }

        if(0x03 == msg.value
                || 0x05 == msg.value
                || 0x0B == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD87, POP_ALARM_ON);//后雷达故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD87, POP_ALARM_OFF);//后雷达故障
        }

        if(0x09 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD88, POP_ALARM_ON);//雷达系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD88, POP_ALARM_OFF);//雷达系统故障
        }

    }
}

//246 BCM_TireWarnFrntLe
void PopupControl::func_MSG_TIRE_WARN_FRONT_LE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TIRE_WARN_FRONT_LE,msg)
    if(msg.isTimeout){
        TyreWarnStatus.g_LFTiresWarning = false;
        setPropertyValue(PROPERTYID_POPUP_LF_TEMP_WARNING, TyreWarnStatus.g_LFTiresWarning);
        _PopupStrategy->updateDisplayList(&PopupTyre, POP_ALARM_OFF);
    }else{
        tireFrontLe = msg.value;
        handleTyre();
        if(tireFrontLe == 0x00)
        {
            TyreWarnStatus.g_LFTiresWarning = false;
        }
        else{
            TyreWarnStatus.g_LFTiresWarning = true;
        }
        //轮胎颜色
        setPropertyValue(PROPERTYID_POPUP_LF_TEMP_WARNING, TyreWarnStatus.g_LFTiresWarning);

        //胎压低
        if(1 == (tireFrontLe & 0x01 ))
        {
            //左前轮胎压低
            if(0 == (tireFrontLe_BackUp & 0x01))
            {
                addTyre("左前轮胎压低");
            }
        }
        else{//
            if(1 == (tireFrontLe_BackUp & 0x01))
            {
               removeTyre("左前轮胎压低");
            }
        }
        //胎压高
        if(1 == ((tireFrontLe >> 1) & 0x01 ))
        {
            //左前轮胎压高
            if(0 == ((tireFrontLe_BackUp >> 1) & 0x01 ))
            {
                addTyre("左前轮胎压高");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 1) & 0x01 ))
            {
                removeTyre("左前轮胎压高");
            }
        }
        //左前轮传感器电量低
        if(1 == ((tireFrontLe >> 2) & 0x01 ))
        {
            if(0 == ((tireFrontLe_BackUp >> 2) & 0x01 ))
            {
                addTyre("左前轮传感器电量低");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 2) & 0x01 ))
            {
                removeTyre("左前轮传感器电量低");
            }
        }
        //左前轮胎温高
        if(1 == ((tireFrontLe >> 3) & 0x01 ))
        {
            if(0 == ((tireFrontLe_BackUp >> 3) & 0x01 ))
            {
                addTyre("左前轮胎温高");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 3) & 0x01 ))
            {
                removeTyre("左前轮胎温高");
            }
        }
        //左前轮快速漏气
        if(1 == ((tireFrontLe >> 4) & 0x01 ))
        {
            if(0 == ((tireFrontLe_BackUp >> 4) & 0x01 ))
            {
                addTyre("左前轮快速漏气");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 4) & 0x01 ))
            {
                removeTyre("左前轮快速漏气");
            }
        }
        //左前轮传感器故障
        if(1 == ((tireFrontLe >> 5) & 0x01 ))
        {
            if(0 == ((tireFrontLe_BackUp >> 5) & 0x01 ))
            {
                addTyre("左前轮传感器故障");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 5) & 0x01 ))
            {
                removeTyre("左前轮传感器故障");
            }
        }
        if(1 == ((tireFrontLe >> 6) & 0x01 ))
        {
            //左前轮传感器未标定
            if(0 == ((tireFrontLe_BackUp >> 6) & 0x01 ))
            {
                addTyre("左前轮传感器未标定");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 6) & 0x01 ))
            {
                removeTyre("左前轮传感器未标定");
            }
        }
        if(1 == ((tireFrontLe >> 7) & 0x01 ))
        {
            //左前轮传感器信号丢失
            if(0 == ((tireFrontLe_BackUp >> 7) & 0x01 ))
            {
                addTyre("左前轮传感器信号丢失");
            }
        }
        else{
            if(1 == ((tireFrontLe_BackUp >> 7) & 0x01 ))
            {
                removeTyre("左前轮传感器信号丢失");
            }
        }
        tireFrontLe_BackUp = tireFrontLe;
    }
}

//246 BCM_TireWarnFrntRi
void PopupControl::func_MSG_TIRE_WARN_FRONT_RI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TIRE_WARN_FRONT_RI,msg)
    if(msg.isTimeout){
        TyreWarnStatus.g_RFTiresWarning = false;
        setPropertyValue(PROPERTYID_POPUP_RF_TEMP_WARNING, TyreWarnStatus.g_RFTiresWarning);
        _PopupStrategy->updateDisplayList(&PopupTyre, POP_ALARM_OFF);
    }else{
        tireFrontRi = msg.value;
        handleTyre();
        if(tireFrontRi == 0x00)
        {
            TyreWarnStatus.g_RFTiresWarning = false;
        }
        else{
            TyreWarnStatus.g_RFTiresWarning = true;
        }
        //轮胎颜色
        setPropertyValue(PROPERTYID_POPUP_RF_TEMP_WARNING, TyreWarnStatus.g_RFTiresWarning);

        //胎压低
        if(1 == (tireFrontRi & 0x01 ))
        {
            //左后轮胎压低
            if(0 == (tireFrontRi_BackUp & 0x01))
            {
                addTyre("右前轮胎压低");
            }
        }
        else{
            if(1 == (tireFrontRi_BackUp & 0x01))
            {
                removeTyre("右前轮胎压低");
            }
        }
        if(1 == ((tireFrontRi >> 1) & 0x01 ))
        {
            //右前轮胎压高
            if(0 == ((tireFrontRi_BackUp >> 1) & 0x01 ))
            {
                addTyre("右前轮胎压高");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 1) & 0x01 ))
            {
                removeTyre("右前轮胎压高");
            }
        }
        if(1 == ((tireFrontRi >> 2) & 0x01 ))
        {
            //右前轮传感器电量低
            if(0 == ((tireFrontRi_BackUp >> 2) & 0x01 ))
            {
                addTyre("右前轮传感器电量低");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 2) & 0x01 ))
            {
                removeTyre("右前轮传感器电量低");
            }
        }
        if(1 == ((tireFrontRi >> 3) & 0x01 ))
        {
            //右前轮胎温高
            if(0 == ((tireFrontRi_BackUp >> 3) & 0x01 ))
            {
                addTyre("右前轮胎温高");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 3) & 0x01 ))
            {
                removeTyre("右前轮胎温高");
            }
        }
        if(1 == ((tireFrontRi >> 4) & 0x01 ))
        {
            //右前轮快速漏气
            if(0 == ((tireFrontRi_BackUp >> 4) & 0x01 ))
            {
                addTyre("右前轮快速漏气");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 4) & 0x01 ))
            {
                removeTyre("右前轮快速漏气");
            }
        }
        if(1 == ((tireFrontRi >> 5) & 0x01 ))
        {
            //右前轮传感器故障
            if(0 == ((tireFrontRi_BackUp >> 5) & 0x01 ))
            {
                addTyre("右前轮传感器故障");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 5) & 0x01 ))
            {
                removeTyre("右前轮传感器故障");
            }
        }
        if(1 == ((tireFrontRi >> 6) & 0x01 ))
        {
            //右前轮传感器未标定
            if(0 == ((tireFrontRi_BackUp >> 6) & 0x01 ))
            {
                addTyre("右前轮传感器未标定");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 6) & 0x01 ))
            {
                removeTyre("右前轮传感器未标定");
            }
        }
        if(1 == ((tireFrontRi >> 7) & 0x01 ))
        {
            //右前轮传感器信号丢失
            if(0 == ((tireFrontRi_BackUp >> 7) & 0x01 ))
            {
                addTyre("右前轮传感器信号丢失");
            }
        }
        else{
            if(1 == ((tireFrontRi_BackUp >> 7) & 0x01 ))
            {
                removeTyre("右前轮传感器信号丢失");
            }
        }
        tireFrontRi_BackUp = tireFrontRi;
    }
}

//246 BCM_TireWarnReLe
void PopupControl::func_MSG_TIRE_WARN_REAR_LE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TIRE_WARN_REAR_LE,msg)
    if(msg.isTimeout){
        TyreWarnStatus.g_LRTiresWarning = false;
        setPropertyValue(PROPERTYID_POPUP_LR_TEMP_WARNING, TyreWarnStatus.g_LRTiresWarning);
        _PopupStrategy->updateDisplayList(&PopupTyre, POP_ALARM_OFF);
    }else{
        tireRearLe = msg.value;
        handleTyre();
        if(tireRearLe == 0x00)
        {
            TyreWarnStatus.g_LRTiresWarning = false;
        }
        else{
            TyreWarnStatus.g_LRTiresWarning = true;
        }
        //轮胎颜色
        setPropertyValue(PROPERTYID_POPUP_LR_TEMP_WARNING, TyreWarnStatus.g_LRTiresWarning);

        //胎压低
        if(1 == (tireRearLe & 0x01 ))
        {
            //左后轮胎压低
            if(0 == (tireRearLe_BackUp & 0x01))
            {
                addTyre("左后轮胎压低");
            }
        }
        else{
            if(1 == (tireRearLe_BackUp & 0x01))
            {
               removeTyre("左后轮胎压低");
            }
        }
        if(1 == ((tireRearLe>> 1) & 0x01 ))
        {
            //左后轮胎压高
            if(0 == ((tireRearLe_BackUp >> 1) & 0x01 ))
            {
                addTyre("左后轮胎压高");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 1) & 0x01 ))
            {
                removeTyre("左后轮胎压高");
            }
        }
        if(1 == ((tireRearLe>> 2) & 0x01 ))
        {
            //左后轮传感器电量低
            if(0 == ((tireRearLe_BackUp >> 2) & 0x01 ))
            {
                addTyre("左后轮传感器电量低");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 2) & 0x01 ))
            {
                removeTyre("左后轮传感器电量低");
            }
        }
        if(1 == ((tireRearLe>> 3) & 0x01 ))
        {
            //左后轮胎温高
            if(0 == ((tireRearLe_BackUp >> 3) & 0x01 ))
            {
                addTyre("左后轮胎温高");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 3) & 0x01 ))
            {
                removeTyre("左后轮胎温高");
            }
        }
        if(1 == ((tireRearLe>> 4) & 0x01 ))
        {
            //左后轮快速漏气
            if(0 == ((tireRearLe_BackUp >> 4) & 0x01 ))
            {
                addTyre("左后轮快速漏气");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 4) & 0x01 ))
            {
                removeTyre("左后轮快速漏气");
            }
        }

        if(1 == ((tireRearLe>> 5) & 0x01 ))
        {
            //左后轮传感器故障
            if(0 == ((tireRearLe_BackUp >> 5) & 0x01 ))
            {
                addTyre("左后轮传感器故障");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 5) & 0x01 ))
            {
                removeTyre("左后轮传感器故障");
            }
        }
        if(1 == ((tireRearLe>> 6) & 0x01 ))
        {
            //左后轮传感器未标定
            if(0 == ((tireRearLe_BackUp >> 6) & 0x01 ))
            {
                addTyre("左后轮传感器未标定");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 6) & 0x01 ))
            {
                removeTyre("左后轮传感器未标定");
            }
        }
        if(1 == ((tireRearLe>> 7) & 0x01 ))
        {
            //左后轮传感器信号丢失
            if(0 == ((tireRearLe_BackUp >> 7) & 0x01 ))
            {
                addTyre("左后轮传感器信号丢失");
            }
        }
        else{
            if(1 == ((tireRearLe_BackUp >> 7) & 0x01 ))
            {
                removeTyre("左后轮传感器信号丢失");
            }
        }
        tireRearLe_BackUp = tireRearLe;
    }
}

//246 BCM_TireWarnReRi
void PopupControl::func_MSG_TIRE_WARN_REAR_RI()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TIRE_WARN_REAR_RI,msg)
    if(msg.isTimeout){
        TyreWarnStatus.g_RRTiresWarning = false;
        setPropertyValue(PROPERTYID_POPUP_RR_TEMP_WARNING, TyreWarnStatus.g_RRTiresWarning);
        _PopupStrategy->updateDisplayList(&PopupTyre, POP_ALARM_OFF);
    }else{
        tireRearRi = msg.value;
        handleTyre();
        if(tireRearRi == 0x00)
        {
            TyreWarnStatus.g_RRTiresWarning = false;
        }
        else{
            TyreWarnStatus.g_RRTiresWarning = true;
        }
        //轮胎颜色
        setPropertyValue(PROPERTYID_POPUP_RR_TEMP_WARNING, TyreWarnStatus.g_RRTiresWarning);

        //胎压低
        if(1 == (tireRearRi & 0x01 ))
        {
            //右后轮胎压低
            if(0 == (tireRearRi_BackUp & 0x01))
            {
                addTyre("右后轮胎压低");
            }
        }
        else{
            if(1 == (tireRearRi_BackUp & 0x01))
            {
                removeTyre("右后轮胎压低");
            }
        }
        if(1 == ((tireRearRi >> 1) & 0x01 ))
        {
            //右后轮胎压高
            if(0 == ((tireRearRi_BackUp >> 1) & 0x01 ))
            {
                addTyre("右后轮胎压高");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 1) & 0x01 ))
            {
                removeTyre("右后轮胎压高");
            }
        }

        if(1 == ((tireRearRi >> 2) & 0x01 ))
        {
            //右后轮传感器电量低
            if(0 == ((tireRearRi_BackUp >> 2) & 0x01 ))
            {
                addTyre("右后轮传感器电量低");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 2) & 0x01 ))
            {
                removeTyre("右后轮传感器电量低");
            }
        }
        if(1 == ((tireRearRi >> 3) & 0x01 ))
        {
            //右后轮胎温高
            if(0 == ((tireRearRi_BackUp >> 3) & 0x01 ))
            {
                addTyre("右后轮胎温高");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 3) & 0x01 ))
            {
                removeTyre("右后轮胎温高");
            }
        }
        if(1 == ((tireRearRi >> 4) & 0x01 ))
        {
            //右后轮快速漏气
            if(0 == ((tireRearRi_BackUp >> 4) & 0x01 ))
            {
                addTyre("右后轮快速漏气");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 4) & 0x01 ))
            {
                removeTyre("右后轮快速漏气");
            }
        }
        if(1 == ((tireRearRi >> 5) & 0x01 ))
        {
            //右后轮传感器故障
            if(0 == ((tireRearRi_BackUp >> 5) & 0x01 ))
            {
                addTyre("右后轮传感器故障");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 5) & 0x01 ))
            {
                removeTyre("右后轮传感器故障");
            }
        }
        if(1 == ((tireRearRi >> 6) & 0x01 ))
        {
            //右后轮传感器未标定
            if(0 == ((tireRearRi_BackUp >> 6) & 0x01 ))
            {
                addTyre("右后轮传感器未标定");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 6) & 0x01 ))
            {
                removeTyre("右后轮传感器未标定");
            }
        }
        if(1 == ((tireRearRi >> 7) & 0x01 ))
        {
            //右后轮传感器信号丢失
            if(0 == ((tireRearRi_BackUp >> 7) & 0x01 ))
            {
                addTyre("右后轮传感器信号丢失");
            }
        }
        else{
            if(1 == ((tireRearRi_BackUp >> 7) & 0x01 ))
            {
                removeTyre("右后轮传感器信号丢失");
            }
        }
        tireRearRi_BackUp = tireRearRi;
    }
}

//148 VCU_SystemFailureHMI
void PopupControl::func_MSG_VCU_SYSTEM_FAULT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_SYSTEM_FAULT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA12, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA12, POP_ALARM_ON);//动力系统故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA12, POP_ALARM_OFF);//动力系统故障
        }
    }
}

//148 VCU_BatteryHeatCriticalHMI
void PopupControl::func_MSG_VCU_BATT_HEAT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_BATT_HEAT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA13, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value
                ||0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA13, POP_ALARM_ON);//动力电池过热，请停车检查
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA13, POP_ALARM_OFF);//动力电池过热，请停车检查
        }
    }
}

//148 VCU_CoolantAlarmHMI
void PopupControl::func_MSG_VCU_COOLANT_ALARN()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_COOLANT_ALARN,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA6, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupA7, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupA8, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA6, POP_ALARM_ON);//电池冷却液不足
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA6, POP_ALARM_OFF);//电池冷却液不足
        }
        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA7, POP_ALARM_ON);//电机冷却液不足
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA7, POP_ALARM_OFF);//电机冷却液不足
        }

        if(0x03 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA8, POP_ALARM_ON);//电池/电机冷却液不足
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA8, POP_ALARM_OFF);//电池/电机冷却液不足
        }
    }
}

//148 VCU_EMotorAlarmHMI
void PopupControl::func_MSG_VCU_EMOTOR_ALARM()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_EMOTOR_ALARM,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA11, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value
                || 0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA11, POP_ALARM_ON);//电机严重故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA11, POP_ALARM_OFF);//电机严重故障
        }
    }
}

//148 VCU_SystemPowerLimitationHMI
void PopupControl::func_MSG_VCU_SYSTEM_POWER_LIMIT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_SYSTEM_POWER_LIMIT,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupB26, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupB26, POP_ALARM_ON);//驱动功率限制
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupB26, POP_ALARM_OFF);//驱动功率限制
        }
    }
}

//9A VCU_InvldCdnToDrvr
void PopupControl::func_MSG_VCU_INVLD_CDN()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_INVLD_CDN,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC40, POP_ALARM_OFF);
        _PopupStrategy->updateDisplayList(&PopupC41, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC40, POP_ALARM_ON);//请踩刹车换挡
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC40, POP_ALARM_OFF);//请踩刹车换挡
        }

        if(0x02 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC41, POP_ALARM_ON);//请拔下充电枪！
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC41, POP_ALARM_OFF);//请拔下充电枪！
        }
    }
}

//9A VCU_ElecPtLimdDecelSts
void PopupControl::func_MSG_VCU_ELEC_PT_LIMD_DECEL()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_VCU_ELEC_PT_LIMD_DECEL,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupC42, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupC42, POP_ALARM_ON);//能量回收受限
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC42, POP_ALARM_OFF);//能量回收受限
        }
    }
}

//201 ACM_AirbWarnLampSt
void PopupControl::func_MSG_ACM_AIRB_WARN()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ACM_AIRB_WARN,msg)
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupA16, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupA16, POP_ALARM_ON);//安全气囊故障
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupA16, POP_ALARM_OFF);//安全气囊故障
        }
    }
}

//181 ADAS_ACC_Passive_Reason
void PopupControl::func_MSG_ACC_PASSIVE_REASON()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ACC_PASSIVE_REASON,msg)
    accWarnReason = msg;
    handleACCWarnReason();
}

//181 ADAS_ADASBRKJERKREQ
void PopupControl::func_MSG_ADAS_ADASBRKJERKREQ()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ADASBRKJERKREQ,msg);
    if(msg.isTimeout){
        _PopupStrategy->updateDisplayList(&PopupD38, POP_ALARM_OFF);
    }else{
        if(0x01 == msg.value)
        {
            _PopupStrategy->updateDisplayList(&PopupD38, POP_ALARM_ON);//AEB启动
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupD38, POP_ALARM_OFF);//AEB启动
        }
    }

}
/****PopupControlFunction Define**************************************************************************************/


//void PopupControl::func_MSG_DMS_DMSInfoHU_24D(const char *data)
//{
//    _c_24D_DMS_DMSInfoHU_msgType *msg = (_c_24D_DMS_DMSInfoHU_msgType *)data;
////    if(msg->Signals.IsTimeout)
////    {
////        _PopupStrategy->updateDisplayList(&PopupD90, POP_ALARM_OFF);//请专心驾驶 红
////        _PopupStrategy->updateDisplayList(&PopupD91, POP_ALARM_OFF);//请专心驾驶 黄
////        _PopupStrategy->updateDisplayList(&PopupD92, POP_ALARM_OFF);//请专心驾驶 绿
////    }
////    else{
////        if(0x03 == msg->Signals.DMS_DrowsnsLevel)
////        {
////            _PopupStrategy->updateDisplayList(&PopupD90, POP_ALARM_ON);//请专心驾驶 红
////        }
////        else{
////            _PopupStrategy->updateDisplayList(&PopupD90, POP_ALARM_OFF);//请专心驾驶 红
////        }

////        if(0x02 == msg->Signals.DMS_DrowsnsLevel)
////        {
////            _PopupStrategy->updateDisplayList(&PopupD91, POP_ALARM_ON);//请专心驾驶 黄
////        }
////        else{
////            _PopupStrategy->updateDisplayList(&PopupD91, POP_ALARM_OFF);//请专心驾驶 黄
////        }

////        if(0x01 == msg->Signals.DMS_DrowsnsLevel)
////        {
////            _PopupStrategy->updateDisplayList(&PopupD92, POP_ALARM_ON);//请专心驾驶 绿
////        }
////        else{
////            _PopupStrategy->updateDisplayList(&PopupD92, POP_ALARM_OFF);//请专心驾驶 绿
////        }
////    }
//}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  getCardoorState
 *  Description:  门开（含后备厢和前舱盖门）报警显示状态
 *	Return:
 *          true: 门开
 *          false: 门关
 *  Param:
            none:      none
 * =====================================================================================
 */
bool PopupControl::getCardoorState()
{
    //TODO
    return false;
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  getPopMinDisplayTime
 *  Description:  报警显示的最小时间（1s）内
 *	Return:
 *          true: 1s内
 *          false: 1s外或无报警
 *  Param:
            none:      none
 * =====================================================================================
 */
bool PopupControl::getPopMinDisplayTime()
{
    //TODO
    if(_PopupStrategy->getTimerCntNormal() < POP_DIS_TIMEMIN){
        return true;
    }
    return false;
}

void PopupControl::handleLowbattery()
{

}

void PopupControl::handleTireFault()
{
    if(tireFault == 0x1 || tireSysFault == 0x1){
        _PopupStrategy->updateDisplayList(&PopupB59, POP_ALARM_ON);//胎压系统故障
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupB59, POP_ALARM_OFF);//胎压系统故障
    }
}

void PopupControl::dataChange()
{
    foreach (PopupControl::PopupFunctionParser func, PopupVoidControlFunc) {
        (this->*(func))();
    }
}

QList<Popup *> PopupControl::getReadList()
{
    return _PopupStrategy->m_wMsgDispHistListCardYellow_read;
}

void PopupControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    if ( HMI_MSGNAME_POWER_MODE == message_key ) {
        g_powermode = message_value.toInt();
        _PopupStrategy->triggerPowerMode(g_powermode);
    }else if ( HMI_MSGNAME_VEHICLESPEED == message_key ) {
        if(0xFFFF == message_value.toInt()){
            g_vehicleSpeed = 0;
        }
        else{
            g_vehicleSpeed = message_value.toInt();
        }

        //新pop策略可以接受频繁车速变化,不会产生逻辑复杂性
//        _PopupStrategy->PopupDisplayStrategyPopup_EPB();

        //drivw mode 逻辑多,先保留该优化策略
        if(g_vehicleSpeed<5 && g_drive4L_speed_area!=0)
        {
            g_drive4L_speed_area = 0;
//            _PopupStrategy->handleDriveModeAboutSpeed();
        }
        else if(g_vehicleSpeed>=5 && g_drive4L_speed_area!=1)
        {
            g_drive4L_speed_area = 1;
//            _PopupStrategy->handleDriveModeAboutSpeed();
        }
        if(1 == 0x02)
        {
//            _PopupStrategy->handleDriveModeAboutSpeed_Fenshi();
        }
//        _PopupStrategy->handleCarDoor();
        //        _PopupStrategy->handleCarDoorSound();
    }
    else if ( HMI_MSGNAME_OVERSPEED == message_key ) {
        int value = message_value.toInt();
        if(value == 0)
        {
            if(1 == 0x01)
            {
                //_PopupStrategy->//updateDisplayList(&PopupA14, POP_ALARM_OFF);
            }
            else if(1 == 0x02)
            {
                //_PopupStrategy->//updateDisplayList(&PopupA14_N, POP_ALARM_OFF);
            }
        }
        else{
            if(1 == 0x01)
            {
                //_PopupStrategy->//updateDisplayList(&PopupA14, POP_ALARM_ON);
            }
            else if(1 == 0x02)
            {
                //_PopupStrategy->//updateDisplayList(&PopupA14_N, POP_ALARM_ON);
            }
        }
    }
    else if ("CFG_EPB" == message_key){
        int value = message_value.toInt();
        //do something
    }
    else if(HMI_MSGNAME_AUTOCHECK == message_key){
        int value = message_value.toInt();
        _PopupStrategy->triggerAutoCheckState(value);
    }
    else if(HMI_MSGNAME_VOLUME == message_key){
        int value = message_value.toInt();
        if(value == 1)
        {
            g_check_volume = 1;
            _PopupStrategy->updateDisplayList(&Popup_volume, POP_ALARM_ON);
        }
        else{
            g_check_volume = 0;
            _PopupStrategy->updateDisplayList(&Popup_volume, POP_ALARM_OFF);
        }
    }
    else {
        // Nothing
    }
}

void PopupControl::get_timeout100ms()
{
//    qDebug()<<"PopupControl::get_timeout100ms"<<QThread::currentThreadId()<<QThread::currentThread();
    m_seatbelt->update();
    _PopupStrategy->triggerTimeout100ms();
}

void PopupControl::get_timeout500ms()
{
    _PopupStrategy->triggerTimeout500ms();
}

void PopupControl::receiveDateFromOtherProcess(QString name, int value)
{
    Q_UNUSED(name)
    Q_UNUSED(value)
    //    qDebug()<<"PopupControl::receiveDateFromOtherProcess"<<QThread::currentThreadId()<<QThread::currentThread();
    //    qDebug()<<name<<value;
}

void PopupControl::receiveDateFromOtherProcess(QString name, QVariant value)
{
    Q_UNUSED(value)
    Q_UNUSED(name)
    if(name == HMI_SHREMEMORY_CMD_SEATBELT)
    {
        if(value.toInt() == 0x01)
        {
            _PopupStrategy->updateDisplayList(&PopupC43, POP_ALARM_ON);
        }
        else{
            _PopupStrategy->updateDisplayList(&PopupC43, POP_ALARM_OFF);
        }
    }
}

void PopupControl::seatBeltVisible(int id ,int value){
    if(value==1||value==3)
    {
        setPropertyValue(id, true);
    }
    else if(value==2)
    {
    }
    else
    {
        setPropertyValue(id, false);
    }
}

bool PopupControl::triggerHardKey(int keyValue,int type)
{
    return _PopupStrategy->triggerHardKey(keyValue,type);
}

void PopupControl::removeTyre(QString str)
{
    int findIndex = 0;
    int cIndex = PopupStrategy::instance()->g_currenTyreCardIndex;
    foreach (QString name, tyreNameList) {
        if(name == str)
        {
            tyreNameList.removeAt(findIndex);
            break;
        }
        findIndex ++;
    }
    // T1, T1 T2 T3
    //更新文字显示内容
    if(findIndex <= cIndex)
    {
        // (T1) [T2] T3
        if(PopupStrategy::instance()->g_currenTyreCardIndex > 0)
        {
            PopupStrategy::instance()->g_currenTyreCardIndex--;
        }
    }

    // 显示下一条胎压信息 g_currenTyreCardIndex
//    QString _name = "";
//    if(tyreNameList.length() >0)
//    {
//        _name = tyreNameList[PopupStrategy::instance()->g_currenTyreCardIndex];
//    }

//    PopupStrategy::instance()->m_CurrentPop->name = _name;

    if(tyreNameList.length() >0)
    {
        PopupStrategy::instance()->m_CurrentPop->name = tyreNameList[PopupStrategy::instance()->g_currenTyreCardIndex];
    }

    if(cIndex == findIndex)
    {
        PopupStrategy::instance()->m_TimerCntNormalTyre = 0;
    }
    emit PropertyChange(PopupStrategy::instance()->m_CurrentPop);
}

void PopupControl::addTyre(QString str)
{
    tyreNameList.append(str);

    //跟随信号变化更新显示文字
    if(PopupStrategy::instance()->m_CurrentPop->symbol == "tire_car.png")//胎压文言
    {
        if(tyreNameList.length() >0)
        {
            PopupStrategy::instance()->g_currenTyreCardIndex = tyreNameList.length() - 1;
            PopupStrategy::instance()->m_TimerCntNormalTyre = 0;
            PopupStrategy::instance()->m_CurrentPop->name = tyreNameList[PopupStrategy::instance()->g_currenTyreCardIndex];
        }
    }
    emit PropertyChange(PopupStrategy::instance()->m_CurrentPop);
}

void PopupControl::handleACCSpeedLimit()
{
    if((0x03 == accFault
        || 0x05 == accFault
        || 0x06 == accFault)
            &&(tstLimitSpeed >= 0x02
               && tstLimitSpeed <= 0x1B))
    {
        int limitspeed = (tstLimitSpeed -1) *5 ;
        setPropertyValue(PROPERTYID_POPUP_LimitSpeed, QString::number(limitspeed));
        if(tstLimitSpeed != tstLimitSpeed_BackUp)
        {
            _PopupStrategy->updateDisplayList(&PopupD95, POP_ALARM_OFF);
            _PopupStrategy->updateDisplayList(&PopupD95, POP_ALARM_ON);//检测到限速xx，按SET/-设置为巡航速度
        }
        else{
        }
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupD95, POP_ALARM_OFF);
    }
}

void PopupControl::handleADASHWA()
{
    if((0x06 == hwaSt || 0x0D == hwaSt) && (0x01 == hwaAbort))
    {
        _PopupStrategy->updateDisplayList(&PopupD31, POP_ALARM_ON);//目标车道未检测出车道线
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupD31, POP_ALARM_OFF);//目标车道未检测出车道线
    }

    if((0x06 == hwaSt || 0x0D == hwaSt) && (0x02 == hwaAbort))
    {
        _PopupStrategy->updateDisplayList(&PopupD32, POP_ALARM_ON);//车道线不允许超车
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupD32, POP_ALARM_OFF);//车道线不允许超车
    }

    if((0x06 == hwaSt || 0x0D == hwaSt) && (0x03 == hwaAbort))
    {
        _PopupStrategy->updateDisplayList(&PopupD33, POP_ALARM_ON);//变道风险检测未通过
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupD33, POP_ALARM_OFF);//变道风险检测未通过
    }

    if((0x06 == hwaSt || 0x0D == hwaSt) && (0x04 == hwaAbort))
    {
        _PopupStrategy->updateDisplayList(&PopupD34, POP_ALARM_ON);//驾驶员取消变道
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupD34, POP_ALARM_OFF);//驾驶员取消变道
    }

}

void PopupControl::handleTyre()
{
    if(tireFrontLe != 0x0 || tireFrontRi != 0x0 || tireRearLe != 0x0 || tireRearRi != 0x0){
        _PopupStrategy->updateDisplayList(&PopupTyre, POP_ALARM_ON);
    }
    else{
        _PopupStrategy->updateDisplayList(&PopupTyre, POP_ALARM_OFF);
    }
}

void PopupControl::handleACCWarnReason()
{
    POPALARMEVENT alarmStatus = POP_ALARM_OFF;
    if(accWarnReason.isTimeout || accWarnStatus.isTimeout){
    }else{
        if(accWarnStatus.value == 0x02){
            int index = accWarnReason.value == 0 ? 0 : accWarnReason.value - 1;
            QString str = accReasonStringList.at(index);
            PopupD23.name = QString("因为%1，ACC无法激活").arg(str);
            alarmStatus = POP_ALARM_ON;
        }
    }

    _PopupStrategy->updateDisplayList(&PopupD23, alarmStatus);
}
