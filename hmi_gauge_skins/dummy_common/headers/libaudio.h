/*
 * =====================================================================================
 *
 *       Filename:  libaudio.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/08/2019 10:08:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  huqiang
 *   Organization:  www.neusoft.com
 *
 * =====================================================================================
 */
#ifndef __LIBAUDIO_H__
#define __LIBAUDIO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdbool.h>

#define AUDIO_INIT_OK 0
#define AUDIO_INIT_NG 1

typedef enum
{
    AUDIO_INDEX_INVALID        = -1,
    /*  BODY 域   */
    AUDIO_INDEX_TURN_ON = 0,                            /*0*/ //转向ON
    AUDIO_INDEX_TURN_OFF,                               /*1*/ //转向OFF
    AUDIO_INDEX_AIRBAG_WARNING,                         /*2*/ //安全气囊故障
    AUDIO_INDEX_SEATBELT_LEVEL_H,                       /*3*/ //安全带报警           持续95s ，SPEED >= 40
    AUDIO_INDEX_SEATBELT_LEVEL_M,                       /*4*/ //安全带报警           持续95s ，SPEED < 40
    AUDIO_INDEX_SEATBELT_LEVEL_L,                       /*5*/ //安全带报警          持续25s，SPEED < 40
    AUDIO_INDEX_TPMS_FAULT,                             /*6*/ //胎压系统故障
    AUDIO_INDEX_DOOR_OPEN,                              /*7*/ //门开报警
    /*  ADAS 域   */
    AUDIO_INDEX_LDW_LEFT,                               /*8*/ //LDW提示       左侧发声
    AUDIO_INDEX_LDW_RIGHT,                              /*9*/ //LDW提示       右侧发声
    AUDIO_INDEX_LKA_LEFT,                               /*10*/ //LKA提示      左侧发声
    AUDIO_INDEX_LKA_RIGHT,                              /*11*/ //LKA提示      右侧发声
    AUDIO_INDEX_BSD_LEVEL2_RL,                          /*12*/ //BSD提示2级 后左侧发声
    AUDIO_INDEX_BSD_LEVEL2_RR,                          /*13*/ //BSD提示2级 后右侧发声
    AUDIO_INDEX_ELK_ACTIVE_LEFT,                        /*14*/ //ELK激活提示，左侧发声
    AUDIO_INDEX_ELK_ACTIVE_RIGHT,                       /*15*/ //ELK激活提示，右侧发声
    AUDIO_INDEX_ACC_UNABLE,                             /*16*/ //ACC 无法激活，前排发声
    AUDIO_INDEX_ACC_TAKEOVER,                           /*17*/ //ACC 请接管车辆，前排发声
    AUDIO_INDEX_HWA_UNABLE,                             /*18*/ //HWA 无法激活，前排发声
    AUDIO_INDEX_ACC_CRUISE_EXITED,                      /*19*/ //巡航已退出，前排发声
    AUDIO_INDEX_HWA_TAKEOVER,                           /*20*/ //HWA 请接管车辆，前排发声
    AUDIO_INDEX_AUTOLANE_FINISHED_LEFT,                 /*21*/ //自动变道终止，左侧发声
    AUDIO_INDEX_AUTOLANE_FINISHED_RIGHT,                /*22*/ //自动变道终止，左侧发声
    AUDIO_INDEX_OVERSPEED,                              /*23*/ //超速报警，前排发声
    AUDIO_INDEX_DOW_LEVEL1_FL,                          /*24*/ //1级门开预警,前左发声
    AUDIO_INDEX_DOW_LEVEL1_RL,                          /*25*/ //1级门开预警,后左发声
    AUDIO_INDEX_DOW_LEVEL1_FR,                          /*26*/ //1级门开预警,前右发声
    AUDIO_INDEX_DOW_LEVEL1_RR,                          /*27*/ //1级门开预警,后右发声
    AUDIO_INDEX_DOW_LEVEL2_FL,                          /*28*/ //2级门开预警,前左发声
    AUDIO_INDEX_DOW_LEVEL2_RL,                          /*29*/ //2级门开预警,后左发声
    AUDIO_INDEX_DOW_LEVEL2_FR,                          /*30*/ //2级门开预警,前右发声
    AUDIO_INDEX_DOW_LEVEL2_RR,                          /*31*/ //2级门开预警,后右发声
    AUDIO_INDEX_RCW_LEVEL1,                             /*32*/ //RCW 1 级报警,后排发声
    AUDIO_INDEX_RCW_LEVEL2,                             /*33*/ //RCW 2 级报警,后排发声
    AUDIO_INDEX_FCW_LEVEL1,                             /*34*/ //FCW 1 级报警,前排发声
    AUDIO_INDEX_FCW_LEVEL2,                             /*35*/ //FCW 2 级报警,前排发声
    AUDIO_INDEX_FCW_KEEP_DISTANCE,                      /*36*/ //FCW保持车距，前排发声
    AUDIO_INDEX_BARKE_SHORT,                            /*37*/ //短促制动，前排发声
    AUDIO_INDEX_AEB_ACTIVE,                             /*38*/ //AEB 激活，前排发声
    AUDIO_INDEX_FCTA_LEVEL1_FL,                         /*39*/ // 1级FCTA 报警，前左发声
    AUDIO_INDEX_FCTA_LEVEL1_FR,                         /*40*/ // 1级FCTA 报警，前右发声
    AUDIO_INDEX_FCTA_LEVEL2_FL,                         /*41*/ // 2级FCTA 报警，前左发声
    AUDIO_INDEX_FCTA_LEVEL2_FR,                         /*42*/ // 2级FCTA 报警，前右发声
    AUDIO_INDEX_FCTB_WARNING,                           /*43*/ //FCTB 报警，前排发声
    AUDIO_INDEX_RCTA_LEVEL1_RL,                         /*44*/ // 2级RCTA 报警，后左发声
    AUDIO_INDEX_RCTA_LEVEL1_RR,                         /*45*/ // 2级RCTA 报警，后右发声
    AUDIO_INDEX_RCTA_LEVEL2_RL,                         /*46*/ // 2级RCTA 报警，后左发声
    AUDIO_INDEX_RCTA_LEVEL2_RR,                         /*47*/ // 2级RCTA 报警，后右发声
    AUDIO_INDEX_RCTB_WARNING,                           /*48*/ //RCTB 报警，后排发声
    AUDIO_INDEX_HWA_LEVEL1_HANDSON,                     /*49*/ //HWA手离方向盘报警1级,前排发声
    AUDIO_INDEX_HWA_LEVEL2_HANDSON,                     /*50*/ //HWA手离方向盘报警2级,前排发声
    AUDIO_INDEX_HWA_HANDSOFF,                           /*51*/ //HWA Hands-off报警,前排发声
    AUDIO_INDEX_FATIGUE_DRIVE_L,                        /*52*/ //疲劳报警低中,前排发声
    AUDIO_INDEX_FATIGUE_DRIVE_H,                        /*53*/ //疲劳报警高,前排发声
    AUDIO_INDEX_DISTRACTION_L,                          /*54*/ //分心报警低中,前排发声
    AUDIO_INDEX_DISTRACTION_H,                          /*55*/ //分心报警高,前排发声
    AUDIO_INDEX_HANDSFREE_ACTION,                       /*56*/ //脱手巡航启动,前排发声
    AUDIO_INDEX_RES_GO_ON,                              /*57*/ //Res继续巡航,前排发声
    AUDIO_INDEX_HWA_GRADING_ALARM,                      /*58*/ //HWA脱手中的分级报警,整车发声
    AUDIO_INDEX_HWA_HANDSON_AUTOLANE,                   /*59*/ //自动变道手离方向盘报警,前排发声
    AUDIO_INDEX_HWA_ACTION,                             /*60*/ //HWA启动,前排发声
    AUDIO_INDEX_PDC_AUTOCHECK,                          /*61*/ //PDC自检，前排发声,小于5s
    AUDIO_INDEX_ACC_EXITED,                             /*62*/ //ACC 已退出，前排发声
    AUDIO_INDEX_HWA_EXITED,                             /*63*/ //HWA 已退出，前排发声
    /*  POWERTRAIN 域   */
    AUDIO_INDEX_COOLANT_ALARM,                          /*64*/ //电机/电池冷却液低
    AUDIO_INDEX_BATTERY_LOW,                            /*65*/ //低电量提示
    AUDIO_INDEX_BMS_BATTERY_FAULT,                      /*66*/ //BMS电池故障
    AUDIO_INDEX_CHARGESYS_FAULT,                        /*67*/ //充电系统故障
    AUDIO_INDEX_MOTOR_FAULT,                            /*68*/ //电机严重故障
    AUDIO_INDEX_MOTIVE_POWER_FAULT,                     /*69*/ //动力系统故障
    AUDIO_INDEX_BATTERY_HOT,                            /*70*/ //动力电池过热
    AUDIO_INDEX_BATTERY_THERMAL_RUNAWAY,                /*71*/ //电池热失控
    AUDIO_INDEX_INSULATION_FAULT,                       /*72*/ //绝缘故障
    AUDIO_INDEX_SHIFT_FAULT,                            /*73*/ //换挡器故障
    /*  CHASSIS 域   */
    AUDIO_INDEX_BRAKESYS_FAULT,                         /*74*/ //制动系统故障
    AUDIO_INDEX_EPBSYS_FAULT,                           /*75*/ //EPB系统故障
    AUDIO_INDEX_STEERINGSYS_FAULT,                      /*76*/ //转向助力系统故障
    AUDIO_INDEX_ESCSYS_FAULT,                           /*77*/ //ESC系统故障
    AUDIO_INDEX_TCSSYS_FAULT,                           /*78*/ //TCS系统故障
    AUDIO_INDEX_ABSSYS_FAULT,                           /*79*/ //ABS系统故障
    AUDIO_INDEX_EBDSYS_FAULT,                           /*80*/ //制动力分配系统故障
    AUDIO_INDEX_BRAKE_ASSIST_FAULT,                     /*81*/ //制动助力故障
    AUDIO_INDEX_AUTO_PARKING_FAULT,                     /*82*/ //自动驻车故障
    AUDIO_INDEX_AVH_ALARM,                              /*83*/ //请系上安全带并关闭车门
    AUDIO_INDEX_HDCSYS_FAULT,                           /*84*/ //陡坡缓降系统故障

    /* PDC */
    AUDIO_INDEX_PDC_FRONT_NEAREST,                      /*85*/ //PDC前排 长鸣
    AUDIO_INDEX_PDC_FRONT_NEAR,                         /*86*/ //PDC前排 8HZ
    AUDIO_INDEX_PDC_FRONT_FAR,                          /*87*/ //PDC前排 4HZ
    AUDIO_INDEX_PDC_FRONT_FARTHEST,                     /*88*/ //PDC前排 2HZ
    AUDIO_INDEX_PDC_REAR_NEAREST,                       /*89*/ //PDC后排长鸣
    AUDIO_INDEX_PDC_REAR_NEAR,                          /*90*/ //PDC后排 8HZ
    AUDIO_INDEX_PDC_REAR_FAR,                           /*91*/ //PDC后排4HZ
    AUDIO_INDEX_PDC_REAR_FARTHEST,                      /*92*/ //PDC后排2HZ

    AUDIO_INDEX_PDC_FRONT_FAILURE,                      /*93*/ //PDC前排故障
    AUDIO_INDEX_PDC_REAR_FAILURE,                       /*94*/ //PDC后排故障
    AUDIO_INDEX_PDC_SYSTEM_FAILURE,                     /*95*/ //PDC系统故障

    AUDIO_INDEX_MAX                                     /*96*/ //MAX
} Audio_ID_Index;


typedef enum
{
    AUDIO_STOP= 0,
    AUDIO_PLAY
} Audio_ReqCmd;
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  libaudio_Init
 *  Description:  Request Audio client  to init and connect Audio  server
 *	Return:	True ;Audio init and connect OK
 *			false ;Audio init or connect fail  please retry until Connection success
 * =====================================================================================
 */
int audio_client_Init(void);
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  libaudio_AudioPlay
 *  Description:  Audio Request interface
 *	Return:		None
 *  Param	audio_id: -
                        audio_Cmd :-
 * =====================================================================================
 */
void audio_client_Play(Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd);
/*
* ===  FUNCTION  ======================================================================
        *         Name:  libaudio_AudioAllStop
        *  Description:  Terminate all unfinished processing
        *	Return:		None
        *  Param	audio_id: -
audio_Cmd :-
* =====================================================================================
*/
void audio_client_AllStop(void);

#ifdef __cplusplus
}
#endif

#endif /* __LIBAUDIO_H__ */

