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

extern "C"
{
typedef void (*FunctionParser)(const char *data);

void func_MSG_MCU_0_ID(const char * data);
void func_MSG_VCU_CurrEngPwr_2F1_ID(const char * data);
void func_MSG_MCU_5_ID(const char * data);
void func_MSG_VCU_HvCoolgModReq_98h_ID(const char * data);
void func_MSG_VCU_WarnForHU_148_ID(const char * data);
void func_MSG_BMS_HvBattTiRmnChrgn_200_ID(const char * data);
void func_MSG_BCM_LightReq_151h_ID(const char * data);
void func_MSG_ESC_HMIInfo_136h_ID(const char * data);
void func_MSG_ESC_HmiLampReq_138_ID(const char * data);
void func_MSG_ESC_FctSt_131_ID(const char * data);
void func_MSG_BCM_AlrmWarnIn_245_ID(const char * data);
void func_MSG_eBooster_EbbSts_123_ID(const char * data);
void func_MSG_EPS_EPSInfo_130h_ID(const char * data);
void func_MSG_ACM_ACMInfo_201h_ID(const char * data);
void func_MSG_SUM_SuspSys_17C_ID(const char * data);
void func_MSG_BCM_TireT_248_ID(const char * data);
void func_MSG_AVAS_CurrSts_17F_ID(const char * data);
void func_MSG_BMS_BatteryRelayErrSts_F7_ID(const char * data);
void func_MSG_MSG_IPU_DCDCSts_DB_ID(const char * data);
void func_MSG_VCU_MaxPowerAvl_AC_ID(const char * data);
void func_MSG_VCU_ReminDrvgRng_B3_ID(const char * data);
void func_MSG_BCM_CANFD_212_ID(const char * data);
void func_MSG_ADAS_TSRSts_1C1_ID(const char * data);
void func_MSG_ADAS_TSR_162_ID(const char * data);
void func_MSG_ADAS_FCTASts_1C3_ID(const char * data);
void func_MSG_ADAS_DOWSts_1C4_ID(const char * data);
void func_MSG_PLCU_ParkLockSts_1E1_ID(const char * data);

void func_MSG_MCU_1_ID(const char * data);
void func_VCU_DivModReq_208_ID(const char * data);
void func_ADAS_ACCSts_181_ID(const char * data);

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
