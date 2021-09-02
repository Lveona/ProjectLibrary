#ifndef PARSINGDATA_H
#define PARSINGDATA_H

#include "hmi_share.h"
#include <QThread>
#include <QMutex>
#include <QByteArray>
#include <QThread>
#include <QVariant>

typedef void (*HMIMsgValueHandlerFunction)(unsigned char id, const unsigned char* pData);

#define GMAPMSGVALUESINSERT(id,value,IsTimeout) gMapMsgValues.insert(id, {id, value,IsTimeout});
#define MSG_MACRO(v) (MSG_##v)
extern "C"
{
typedef void (*FunctionParser)(const char *data);

void func_MSG_EEPROM_0_ID                 (const char * data);
void func_MSG_EEPROM_2_ID                 (const char * data);
void func_MSG_MCU_0_ID                    (const char * data);
void func_MSG_MCU_1_ID                    (const char * data);
void func_MSG_MCU_4_ID                    (const char * data);
void func_MSG_MCU_5_ID                    (const char * data);
void func_MSG_VCU_ReminDrvgRng_B3_ID      (const char * data);
void func_MSG_VCU_HvCoolgModReq_98h_ID    (const char * data);
void func_MSG_CCU_AirT_1F7h_ID            (const char * data);
void func_MSG_BCM_HUFeedback_1B2h_ID      (const char * data);
void func_MSG_BCM_States_1B1h_ID          (const char * data);
void func_MSG_ESC_HMIInfo_136h_ID         (const char * data);
void func_MSG_VCU_WarnForHU_148_ID        (const char * data);
void func_MSG_VCU_AccPosGearSts_97h_ID    (const char * data);
void func_MSG_MCU_3_ID                    (const char * data);
void func_MSG_BCM_TireP_247_ID            (const char * data);
void func_MSG_BCM_CANFD_212_ID            (const char * data);
void func_MSG_VCU_HvInfForDrvr_9Ah_ID     (const char * data);
void func_MSG_EPS_EPSInfo_130h_ID         (const char * data);
void func_MSG_BMS_BatteryRelayErrSts_F7_ID(const char * data);
void func_MSG_ESC_HmiLampReq_138_ID       (const char * data);
void func_MSG_ESC_FctSt_131_ID            (const char * data);
void func_MSG_BCM_AlrmWarnIn_245_ID       (const char * data);
void func_MSG_SUM_SuspSys_17C_ID          (const char * data);
void func_MSG_BMS_HvBattTiRmnChrgn_200_ID (const char * data);
void func_MSG_SCM_States_183_ID           (const char * data);
void func_MSG_BCM_LightReq_151h_ID        (const char * data);
void func_MSG_BCM_MirrorPosReq_152_ID     (const char * data);
void func_MSG_BCM_TireWarn_246_ID         (const char * data);
void func_MSG_ACM_ACMInfo_201h_ID         (const char * data);
void func_MSG_BCM_TireT_248_ID            (const char * data);
void func_MSG_eBooster_EbbSts_123_ID      (const char * data);
void func_MSG_SUM_SuspSts_1BC_ID          (const char * data);
void func_MSG_ADAS_LKSSts_1C0_ID          (const char * data);
void func_MSG_ADAS_TSRSts_1C1_ID          (const char * data);
void func_MSG_ADAS_SRSts_182_ID           (const char * data);
void func_MSG_ADAS_DOWSts_1C4_ID          (const char * data);
void func_MSG_ADAS_SysSts_230_ID          (const char * data);
void func_MSG_ADAS_AEB_169_ID             (const char * data);
void func_MSG_ADAS_TrackTar1_23F_ID       (const char * data);
void func_MSG_ADAS_FCTASts_1C3_ID         (const char * data);
void func_MSG_ADAS_FCTA_1C2_ID            (const char * data);
void func_MSG_IPU_DCDCSts_DB_ID           (const char * data);
void func_MSG_VCU_MaxPowerAvl_AC_ID       (const char * data);
void func_MSG_ANRC_PrkgPDC_196_ID         (const char * data);
void func_MSG_DMS_DMSInfoHU_24D_ID        (const char * data);
void func_MSG_ADAS_SRRsts_23F_ID      	 (const char * data);
void func_MSG_BMS_BatSocU_F9_ID             (const char * data);
void func_MSG_BMS_HVBatterySts_FB_ID        (const char * data);
void func_MSG_ADAS_Line1_240_ID            (const char * data);
void func_MSG_ADAS_Line2_241_ID             (const char * data);
void func_MSG_ADAS_Line3_242_ID             (const char * data);
void func_MSG_ADAS_Line4_243_ID             (const char * data);
void func_MSG_ADAS_TrackTar01_231_ID        (const char * data);
void func_MSG_ADAS_TrackTar0_232_ID        (const char * data);
void func_MSG_ADAS_TrackTar1_233_ID        (const char * data);
void func_MSG_ADAS_TrackTar23_234_ID        (const char * data);
void func_MSG_ADAS_TrackTar2_235_ID        (const char * data);
void func_MSG_ADAS_TrackTar3_236_ID        (const char * data);
void func_MSG_ADAS_TrackTar3_Static_23C_ID        (const char * data);
void func_MSG_ADAS_TrackTar4_23A_ID        (const char * data);
void func_MSG_ADAS_TrackTar4_Static_23D_ID        (const char * data);
void func_MSG_ADAS_TrackTar5_23B_ID         (const char * data);
void func_MSG_ADAS_TrackTar5_Static_23E_ID  (const char * data);
void func_MSG_ADAS_TrackTar45_239_ID        (const char * data);
void func_MSG_ANRC_HUDisplay_176h_ID       (const char * data);
void func_MSG_ANRC_ParkingDistance02_179h_ID       (const char * data);
void func_MSG_ANRC_DetailDst2_20E_ID       (const char * data);
void func_MSG_ANRC_SDWInfo_20Ch_ID       (const char * data);
void func_MSG_LCMFL_FltSts_254_ID       (const char * data);
void func_MSG_LCMFL_FltSts_255_ID       (const char * data);
void func_MSG_LCMRL_BCM_LIN1ASWM_1E2_ID       (const char * data);
void func_MSG_LCMFL_LeFrntDirIndcrLam_142_ID       (const char * data);
void func_DCMFL_States1_1C6_ID       (const char * data);
void func_DCMFR_States_1B4_ID       (const char * data);
void func_BCM_ImobMstWarn_BE_ID       (const char * data);
void func_PLCU_ParkLockSts_1E1_ID       (const char * data);
void func_VCU_DivModReq_208_ID       (const char * data);
void func_ADAS_ACCSts_181_ID       (const char * data);
void func_ADAS_HWA_Warn_160_ID       (const char * data);
void func_DMS_DMSStatus_24B_ID       (const char * data);
void func_ETC_Module_30B_ID       (const char * data);
//void func_ETC_TransSt_1A1_ID       (const char * data);
void func_MSG_ADAS_HWAReq_187_ID       (const char * data);
void func_MSG_ADAS_ACC_ESCRq_185_ID   (const char * data);
}

class ParsingData: public QThread, public CSingleton<ParsingData>
{
    Q_OBJECT
public:
    void startControl();
    ParsingData();
    ~ParsingData();

    void RegistIVSMsg();
    void SendMsg(Parsing_Message argument);
    void hmiReceiveMsg(Parsing_Message argument);

protected:
    QList< Parsing_Message > m_messageList;
    void run() Q_DECL_OVERRIDE;

private:
    QMutex mutex;

};
#endif // PARSINGDATA_H
