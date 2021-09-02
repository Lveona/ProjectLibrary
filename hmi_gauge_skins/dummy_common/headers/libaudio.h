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
    /*  BODY ��   */
    AUDIO_INDEX_TURN_ON = 0,                            /*0*/ //ת��ON
    AUDIO_INDEX_TURN_OFF,                               /*1*/ //ת��OFF
    AUDIO_INDEX_AIRBAG_WARNING,                         /*2*/ //��ȫ���ҹ���
    AUDIO_INDEX_SEATBELT_LEVEL_H,                       /*3*/ //��ȫ������           ����95s ��SPEED >= 40
    AUDIO_INDEX_SEATBELT_LEVEL_M,                       /*4*/ //��ȫ������           ����95s ��SPEED < 40
    AUDIO_INDEX_SEATBELT_LEVEL_L,                       /*5*/ //��ȫ������          ����25s��SPEED < 40
    AUDIO_INDEX_TPMS_FAULT,                             /*6*/ //̥ѹϵͳ����
    AUDIO_INDEX_DOOR_OPEN,                              /*7*/ //�ſ�����
    /*  ADAS ��   */
    AUDIO_INDEX_LDW_LEFT,                               /*8*/ //LDW��ʾ       ��෢��
    AUDIO_INDEX_LDW_RIGHT,                              /*9*/ //LDW��ʾ       �Ҳ෢��
    AUDIO_INDEX_LKA_LEFT,                               /*10*/ //LKA��ʾ      ��෢��
    AUDIO_INDEX_LKA_RIGHT,                              /*11*/ //LKA��ʾ      �Ҳ෢��
    AUDIO_INDEX_BSD_LEVEL2_RL,                          /*12*/ //BSD��ʾ2�� ����෢��
    AUDIO_INDEX_BSD_LEVEL2_RR,                          /*13*/ //BSD��ʾ2�� ���Ҳ෢��
    AUDIO_INDEX_ELK_ACTIVE_LEFT,                        /*14*/ //ELK������ʾ����෢��
    AUDIO_INDEX_ELK_ACTIVE_RIGHT,                       /*15*/ //ELK������ʾ���Ҳ෢��
    AUDIO_INDEX_ACC_UNABLE,                             /*16*/ //ACC �޷����ǰ�ŷ���
    AUDIO_INDEX_ACC_TAKEOVER,                           /*17*/ //ACC ��ӹܳ�����ǰ�ŷ���
    AUDIO_INDEX_HWA_UNABLE,                             /*18*/ //HWA �޷����ǰ�ŷ���
    AUDIO_INDEX_ACC_CRUISE_EXITED,                      /*19*/ //Ѳ�����˳���ǰ�ŷ���
    AUDIO_INDEX_HWA_TAKEOVER,                           /*20*/ //HWA ��ӹܳ�����ǰ�ŷ���
    AUDIO_INDEX_AUTOLANE_FINISHED_LEFT,                 /*21*/ //�Զ������ֹ����෢��
    AUDIO_INDEX_AUTOLANE_FINISHED_RIGHT,                /*22*/ //�Զ������ֹ����෢��
    AUDIO_INDEX_OVERSPEED,                              /*23*/ //���ٱ�����ǰ�ŷ���
    AUDIO_INDEX_DOW_LEVEL1_FL,                          /*24*/ //1���ſ�Ԥ��,ǰ����
    AUDIO_INDEX_DOW_LEVEL1_RL,                          /*25*/ //1���ſ�Ԥ��,������
    AUDIO_INDEX_DOW_LEVEL1_FR,                          /*26*/ //1���ſ�Ԥ��,ǰ�ҷ���
    AUDIO_INDEX_DOW_LEVEL1_RR,                          /*27*/ //1���ſ�Ԥ��,���ҷ���
    AUDIO_INDEX_DOW_LEVEL2_FL,                          /*28*/ //2���ſ�Ԥ��,ǰ����
    AUDIO_INDEX_DOW_LEVEL2_RL,                          /*29*/ //2���ſ�Ԥ��,������
    AUDIO_INDEX_DOW_LEVEL2_FR,                          /*30*/ //2���ſ�Ԥ��,ǰ�ҷ���
    AUDIO_INDEX_DOW_LEVEL2_RR,                          /*31*/ //2���ſ�Ԥ��,���ҷ���
    AUDIO_INDEX_RCW_LEVEL1,                             /*32*/ //RCW 1 ������,���ŷ���
    AUDIO_INDEX_RCW_LEVEL2,                             /*33*/ //RCW 2 ������,���ŷ���
    AUDIO_INDEX_FCW_LEVEL1,                             /*34*/ //FCW 1 ������,ǰ�ŷ���
    AUDIO_INDEX_FCW_LEVEL2,                             /*35*/ //FCW 2 ������,ǰ�ŷ���
    AUDIO_INDEX_FCW_KEEP_DISTANCE,                      /*36*/ //FCW���ֳ��࣬ǰ�ŷ���
    AUDIO_INDEX_BARKE_SHORT,                            /*37*/ //�̴��ƶ���ǰ�ŷ���
    AUDIO_INDEX_AEB_ACTIVE,                             /*38*/ //AEB ���ǰ�ŷ���
    AUDIO_INDEX_FCTA_LEVEL1_FL,                         /*39*/ // 1��FCTA ������ǰ����
    AUDIO_INDEX_FCTA_LEVEL1_FR,                         /*40*/ // 1��FCTA ������ǰ�ҷ���
    AUDIO_INDEX_FCTA_LEVEL2_FL,                         /*41*/ // 2��FCTA ������ǰ����
    AUDIO_INDEX_FCTA_LEVEL2_FR,                         /*42*/ // 2��FCTA ������ǰ�ҷ���
    AUDIO_INDEX_FCTB_WARNING,                           /*43*/ //FCTB ������ǰ�ŷ���
    AUDIO_INDEX_RCTA_LEVEL1_RL,                         /*44*/ // 2��RCTA ������������
    AUDIO_INDEX_RCTA_LEVEL1_RR,                         /*45*/ // 2��RCTA ���������ҷ���
    AUDIO_INDEX_RCTA_LEVEL2_RL,                         /*46*/ // 2��RCTA ������������
    AUDIO_INDEX_RCTA_LEVEL2_RR,                         /*47*/ // 2��RCTA ���������ҷ���
    AUDIO_INDEX_RCTB_WARNING,                           /*48*/ //RCTB ���������ŷ���
    AUDIO_INDEX_HWA_LEVEL1_HANDSON,                     /*49*/ //HWA���뷽���̱���1��,ǰ�ŷ���
    AUDIO_INDEX_HWA_LEVEL2_HANDSON,                     /*50*/ //HWA���뷽���̱���2��,ǰ�ŷ���
    AUDIO_INDEX_HWA_HANDSOFF,                           /*51*/ //HWA Hands-off����,ǰ�ŷ���
    AUDIO_INDEX_FATIGUE_DRIVE_L,                        /*52*/ //ƣ�ͱ�������,ǰ�ŷ���
    AUDIO_INDEX_FATIGUE_DRIVE_H,                        /*53*/ //ƣ�ͱ�����,ǰ�ŷ���
    AUDIO_INDEX_DISTRACTION_L,                          /*54*/ //���ı�������,ǰ�ŷ���
    AUDIO_INDEX_DISTRACTION_H,                          /*55*/ //���ı�����,ǰ�ŷ���
    AUDIO_INDEX_HANDSFREE_ACTION,                       /*56*/ //����Ѳ������,ǰ�ŷ���
    AUDIO_INDEX_RES_GO_ON,                              /*57*/ //Res����Ѳ��,ǰ�ŷ���
    AUDIO_INDEX_HWA_GRADING_ALARM,                      /*58*/ //HWA�����еķּ�����,��������
    AUDIO_INDEX_HWA_HANDSON_AUTOLANE,                   /*59*/ //�Զ�������뷽���̱���,ǰ�ŷ���
    AUDIO_INDEX_HWA_ACTION,                             /*60*/ //HWA����,ǰ�ŷ���
    AUDIO_INDEX_PDC_AUTOCHECK,                          /*61*/ //PDC�Լ죬ǰ�ŷ���,С��5s
    AUDIO_INDEX_ACC_EXITED,                             /*62*/ //ACC ���˳���ǰ�ŷ���
    AUDIO_INDEX_HWA_EXITED,                             /*63*/ //HWA ���˳���ǰ�ŷ���
    /*  POWERTRAIN ��   */
    AUDIO_INDEX_COOLANT_ALARM,                          /*64*/ //���/�����ȴҺ��
    AUDIO_INDEX_BATTERY_LOW,                            /*65*/ //�͵�����ʾ
    AUDIO_INDEX_BMS_BATTERY_FAULT,                      /*66*/ //BMS��ع���
    AUDIO_INDEX_CHARGESYS_FAULT,                        /*67*/ //���ϵͳ����
    AUDIO_INDEX_MOTOR_FAULT,                            /*68*/ //������ع���
    AUDIO_INDEX_MOTIVE_POWER_FAULT,                     /*69*/ //����ϵͳ����
    AUDIO_INDEX_BATTERY_HOT,                            /*70*/ //������ع���
    AUDIO_INDEX_BATTERY_THERMAL_RUNAWAY,                /*71*/ //�����ʧ��
    AUDIO_INDEX_INSULATION_FAULT,                       /*72*/ //��Ե����
    AUDIO_INDEX_SHIFT_FAULT,                            /*73*/ //����������
    /*  CHASSIS ��   */
    AUDIO_INDEX_BRAKESYS_FAULT,                         /*74*/ //�ƶ�ϵͳ����
    AUDIO_INDEX_EPBSYS_FAULT,                           /*75*/ //EPBϵͳ����
    AUDIO_INDEX_STEERINGSYS_FAULT,                      /*76*/ //ת������ϵͳ����
    AUDIO_INDEX_ESCSYS_FAULT,                           /*77*/ //ESCϵͳ����
    AUDIO_INDEX_TCSSYS_FAULT,                           /*78*/ //TCSϵͳ����
    AUDIO_INDEX_ABSSYS_FAULT,                           /*79*/ //ABSϵͳ����
    AUDIO_INDEX_EBDSYS_FAULT,                           /*80*/ //�ƶ�������ϵͳ����
    AUDIO_INDEX_BRAKE_ASSIST_FAULT,                     /*81*/ //�ƶ���������
    AUDIO_INDEX_AUTO_PARKING_FAULT,                     /*82*/ //�Զ�פ������
    AUDIO_INDEX_AVH_ALARM,                              /*83*/ //��ϵ�ϰ�ȫ�����رճ���
    AUDIO_INDEX_HDCSYS_FAULT,                           /*84*/ //���»���ϵͳ����

    /* PDC */
    AUDIO_INDEX_PDC_FRONT_NEAREST,                      /*85*/ //PDCǰ�� ����
    AUDIO_INDEX_PDC_FRONT_NEAR,                         /*86*/ //PDCǰ�� 8HZ
    AUDIO_INDEX_PDC_FRONT_FAR,                          /*87*/ //PDCǰ�� 4HZ
    AUDIO_INDEX_PDC_FRONT_FARTHEST,                     /*88*/ //PDCǰ�� 2HZ
    AUDIO_INDEX_PDC_REAR_NEAREST,                       /*89*/ //PDC���ų���
    AUDIO_INDEX_PDC_REAR_NEAR,                          /*90*/ //PDC���� 8HZ
    AUDIO_INDEX_PDC_REAR_FAR,                           /*91*/ //PDC����4HZ
    AUDIO_INDEX_PDC_REAR_FARTHEST,                      /*92*/ //PDC����2HZ

    AUDIO_INDEX_PDC_FRONT_FAILURE,                      /*93*/ //PDCǰ�Ź���
    AUDIO_INDEX_PDC_REAR_FAILURE,                       /*94*/ //PDC���Ź���
    AUDIO_INDEX_PDC_SYSTEM_FAILURE,                     /*95*/ //PDCϵͳ����

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

