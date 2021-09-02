#ifndef POPUPCONTROL_H
#define POPUPCONTROL_H

//#include <hmi_share.h>
#include <hmi_share.h>
#include "popupFaultQuery.h"
#include <QVariant>

class QMutex;
class Popup;
class PopupStrategy;

enum POPFROM {
    POP_DISPLAY = 0x00,
    POP_LOOP,
};

class PopupControl: public CBaseControl, public CSingleton<PopupControl>
{
    Q_OBJECT
    friend class CSingleton<PopupControl>;
public:
    PopupControl();
    ~PopupControl();
    typedef void (PopupControl::*PopupFunctionParser)();
    void func_MSG_BRAKE_SYSTEM();
    void func_MSG_EPB_FAULT();
    void func_MSG_HDC();
    void func_MSG_DRV_AVH();
    void func_MSG_ESC_FAULT();
    void func_MSG_STEERING_FAULT();
    void func_MSG_BATT_LOW();
    void func_MSG_BRAKE_PADS();
    void func_MSG_WIPER_FAULT();
    void func_MSG_BATT_ERROR();
    void func_MSG_TCS_FAULT();
    void func_MSG_ABS_FAULT();
    void func_MSG_EPB_MODE();
    void func_MSG_AVH_FAULT();
    void func_MSG_TCS_OFF();
    void func_MSG_AVL_EBD_FAULT();
    void func_MSG_LOW_BRAKE_FLUID();
    void func_MSG_LOW_GLASS_WATER();
    void func_MSG_KEY_BATT_LOW();
    void func_MSG_SUSPENSION_SYSTEM_FAULT();
    void func_MSG_SUSPENSION_SYSTEM();
    void func_MSG_SUM_DAMP_LIMP();
    void func_MSG_HV_BATT();
    void func_MSG_SHIFTER_FAULT();
    void func_MSG_IMM_WARNING();
    void func_MSG_BOOSTER_FAULT();
    void func_MSG_SUSPENSION_MOVE();
    void func_MSG_ADAS_LKS_ACTIVE();
    void func_MSG_ADAS_ELK_ACTIVE();
    void func_MSG_ADAS_RCW();
    void func_MSG_ADAS_RCTA();
    void func_MSG_ADAS_LCA();
    void func_MSG_ADAS_ELK();
    void func_MSG_ADAS_ACC_WARN();
    void func_MSG_ADAS_TSR_FAULT();
    void func_MSG_ADAS_AHB_FAULT();
    void func_MSG_ADAS_ACC_FAULT();
    void func_MSG_TST_LIMIT_SPEED();
    void func_MSG_ADAS_L3_WARNING();
    void func_MSG_ADAS_HWA_HANDSON();
    void func_MSG_ADAS_HWA_ST();
    void func_MSG_ADAS_HWA_ABORT();
    void func_MSG_ADAS_DOW_ST();
    void func_MSG_ADSS_HWA_STATUS();
    void func_MSG_ADAS_L3_STATUS();
    void func_MSG_ADAS_CONTROLLER_FAULT();
    void func_MSG_ADAS_FMRRSENSOR_BLOC();
    void func_MSG_ADAS_FMRRSENSOR_FAULT();
    void func_MSG_ADAS_FCAMSENSOR_BLOC();
    void func_MSG_ADSS_LFSRRSENSOR_BLOC();
    void func_MSG_ADAS_LRSRRSENSOR_BLOC();
    void func_MSG_ADAS_RRSRRSENSOR_BLOC();
    void func_MSG_ADAS_RFSRRSENSOR_BLOC();
    void func_MSG_ADAS_FMRRSENSOR_CALI();
    void func_MSG_ADAS_FCAMSENSOR_CALI();
    void func_MSG_ADAS_LFSRRSENSOR_CALI();
    void func_MSG_ADAS_LRSRRSENSOR_CALI();
    void func_MSG_ADAS_RRSRRSENSOR_CALI();
    void func_MSG_ADAS_RFSRRSENSOR_CALI();
    void func_MSG_ADAS_FCMASENSOR_FAULT();
    void func_MSG_ADAS_LFSRRSENSOR_FAULT();
    void func_MSG_ADAS_LRSRRSENSOR_FAULT();
    void func_MSG_ADAS_RRSRRSENSOR_FAULT();
    void func_MSG_ADAS_RFSRRSENSOR_FAULT();
    void func_MSG_ADAS_FCW_ST();
    void func_MSG_ADAS_AEB_ST();
    void func_MSG_ADAS_FCTA_ST();
    void func_MSG_ADAS_ADASEBREQTYP();
    void func_MSG_IPU_EEM_DCDC_FAULT();
    void func_MSG_TIRE_SYSTEM_FAULT();
    void func_MSG_TIRE_FAULT();
    void func_MSG_VCU_LV_WARN();
    void func_MSG_ANRC_PRKG_PDC_MODE();
    void func_MSG_TIRE_WARN_FRONT_LE();
    void func_MSG_TIRE_WARN_FRONT_RI();
    void func_MSG_TIRE_WARN_REAR_LE();
    void func_MSG_TIRE_WARN_REAR_RI();
    void func_MSG_VCU_SYSTEM_FAULT();
    void func_MSG_VCU_BATT_HEAT();
    void func_MSG_VCU_COOLANT_ALARN();
    void func_MSG_VCU_EMOTOR_ALARM();
    void func_MSG_VCU_SYSTEM_POWER_LIMIT();
    void func_MSG_VCU_INVLD_CDN();
    void func_MSG_VCU_ELEC_PT_LIMD_DECEL();
    void func_MSG_ACM_AIRB_WARN();
    void func_MSG_ACC_PASSIVE_REASON();
    void func_MSG_ADAS_ADASBRKJERKREQ();
    void func_MSG_BCM_AutoLiCtrlWarn();
    void func_MSG_BCM_HeadLightOpenWarn();
    void func_MSG_LCMFL_LeFrntPosnLampFltSts();
    void func_MSG_LCMFR_RiFrntPosnLampFltSts();
    void func_MSG_LCMRL_LeRePosnFailrSt();
    void func_MSG_LCMRR_RiRePosnFailrSt();
    void func_MSG_LCMFL_LeLoBeamFltSts();
    void func_MSG_LCMFR_RiLoBeamFltSts();
    void func_MSG_LCMFL_LeGrpdLampModFltSts();
    void func_MSG_LCMFR_RiGrpdLampModFltSts();
    void func_MSG_LCMFL_LeHiBeamFltSts();
    void func_MSG_LCMFR_RiHiBeamFltSts();
    void func_MSG_SCM_HiBeamSwtFailrSts();
    void func_MSG_BCM_ReLeRvsLiFailrSts();
    void func_MSG_BCM_ReRiRvsLiFailrSts();
    void func_MSG_BCM_ReLeFogFailrSts();
    void func_MSG_BCM_ReRiFogFailrSts();
    void func_MSG_LCMFL_LeFltDayLampSts();
    void func_MSG_LCMFR_RiFltDayLampSts();
    void func_MSG_BCM_ReLeBrkLiFailrSts();
    void func_MSG_BCM_ReRiBrkLiFailrSts();
    void func_MSG_BCM_MidHiBrkLiFailrSts();
    void func_MSG_LCMFL_LeFrntDirIndcrFailrSt();
    void func_MSG_LCMFR_RiFrntDirIndcrFailrSt();
    void func_MSG_DCMFL_LeSideDirIndcrLampSt();
    void func_MSG_DCMFR_RiSideDirIndcrLampSt();
    void func_MSG_LCMRL_LeReDirIndcrFailrSt();
    void func_MSG_LCMRR_RiReDirIndcrFailrSt();
    void func_MSG_BCM_AutoWiprCtrlWarn();
    void func_MSG_BCM_KeyDetectWarn();
    void func_MSG_BCM_KeyInsideWarn();
    void func_MSG_BCM_ImobBkpWarn();
    void func_MSG_BCM_BrkPedlIndcnWarn();
    void func_MSG_BCM_PwrRlyErrWarn();
    void func_MSG_BCM_LvlBattULoWarn();
    void func_MSG_BCM_EgyLvlDegradationWarn();
    void func_MSG_BCM_ImobMstWarn();
    void func_MSG_ADAS_ACC_GoNotifier();
    void func_MSG_ADAS_HWA_Warn_St();
    void func_MSG_ADAS_HWA_HandsonReq();
    void func_MSG_ADAS_FCWRequest();
    void func_MSG_ADAS_L3_HandsonReq();
    void func_MSG_ADAS_FCTB_St();
    void func_MSG_ADAS_RCTB_St();
    void func_MSG_ADAS_LDW_St();
    void func_MSG_ADAS_LKA_St();
    void func_MSG_DMS_DMSSts();
    void func_MSG_DMS_DMSAbandon_Reason();
    void func_MSG_ETC_RFModule();
    void func_MSG_ETC_ESAMModule();
    void func_MSG_ETC_Antitemper();
    void func_MSG_PLCU_ParkLockSt();
    void func_MSG_VCU_VehSrvcWarn();
    void func_MSG_BMS_VehHvIsoErr();
    void func_MSG_DCMFL_LeSideDirIndcrFailrSt();
    void func_MSG_DCMFR_RiSideDirIndcrFailrSt();
    void func_MSG_ANRC_PrkgMEBWarnType();
    void func_MSG_ANRC_MEB_FuncSts();
    void func_MSG_DMS_DrowsnsLevel();
    void func_MSG_DMS_DistrctnLevel();
    void func_MSG_ADAS_FCTA_Left_Active_St();
    void func_MSG_ADAS_FCTA_Right_Active_St();
    bool isMessageReceiverEmpty(void){return (m_messageList.empty());}

    bool getCardoorState();
    bool getPopMinDisplayTime();
    void handleLowbattery();
    void handleTireFault();

    void seatBeltVisible(int id ,int value);
    QList<Popup*> getReadList();
    bool triggerHardKey(int keyValue, int type);
    void removeTyre(QString str);
    void addTyre(QString str);
    QList<QString> tyreNameList;
    int g_check_volume = 0;

    struct{
        bool g_LFTiresWarning;
        bool g_RFTiresWarning;
        bool g_RRTiresWarning;
        bool g_LRTiresWarning;
    }TyreWarnStatus;
signals:
    void PropertyChange(Popup*);
    void PropertyChange(QList<PopupFaultQuery> pop);
    void PropertyChangeGlobalNaviSource(bool);
    void notifyWarningState(bool state);    //是否有报警信息

private:

public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void get_timeout100ms(void);
    void get_timeout500ms();
    void receiveDateFromOtherProcess(QString name, int value);
    void receiveDateFromOtherProcess(QString name, QVariant value);
protected:
    void dataChange();
//    void handleProperty(int propertyId, QVariant value){ emit PropertyChange( propertyId,value );}

private:
    QMutex mutex;
    PopupStrategy* _PopupStrategy;
    HMICustomTimer* m_seatbelt;
    HMICustomTimer* m_tyreWarn;
    int            m_TimerCntNormalTyre;
    void handleACCSpeedLimit();
    void handleADASHWA();
    void handleTyre();
    void handleACCWarnReason();
};

#endif // POPUPCONTROL_H
