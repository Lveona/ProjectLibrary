#ifndef SETTINGCONTROL_H
#define SETTINGCONTROL_H

#include <hmi_share.h>

#include <qdatetime.h>
#include "languge/langugeManage.h"
/////Test
#include "pm_proxy.h"
enum uintMode {
    UINTMODE_INIT = 0,
    UINTMODE_KM,
    UINTMODE_MILE
};

// System Used By AnChao Add
enum PROPERTYID_SYSTEM {
    PROPERTYID_SYSTEM_INIT = 0,
    PROPERTYID_SYSTEM_IVITHEME,
    PROPERTYID_SYSTEM_MAX,
    PROPERTYID_SYSTEM_SCREEN_STATE,
    PROPERTYID_SYSTEM_SCREEN_COLOR,
    PROPERTYID_SYSTEM_THEME_SETTING,
    PROPERTYID_SYSTEM_SPEED
};

enum SYSTEM_IC_CAN_INFO_SEND_ID{
    SYSTEM_IC_CAN_INFO_languageSts = 0x0,
    SYSTEM_IC_CAN_INFO_themeSts,
    SYSTEM_IC_CAN_INFO_SOC,
    SYSTEM_IC_CAN_INFO_uint,
    SYSTEM_IC_CAN_INFO_SCREEN,

    SYSTEM_IC_CAN_INFO_ID_MAX
};

enum CHARGE_MODE{
    CHARGE_MODE_INIT = 0,
    CHARGE_MODE_NORMAL,
    CHARGE_MODE_V2V,
    CHARGE_MODE_OBC,
    CHARGE_MODE_MAX
};

class SettingControl : public CBaseControl, public CSingleton<SettingControl>
{
    Q_OBJECT
    friend class CSingleton<SettingControl>;
    Q_PROPERTY(int pCFG_EPB READ pCFG_EPB WRITE setPCFG_EPB NOTIFY pCFG_EPBChanged)

public:
    SettingControl();
    ~SettingControl();
    typedef void (SettingControl::*SettingFunctionParser)();

    void func_MSG_EEPROM_1();               // Hard Key
    void func_MSG_EEPROM_0();

    void func_CARINFO_SCREEN_INDEX();
    void func_HARDKEY_STATUS();
    void func_HARDKEY_NUMBER();

    int pCFG_EPB() const
    {
        return m_pCFG_EPB;
    }

    void savePageToEEP(int leftScreen);

    void handleTheme(int theme);

signals:
//    void PropertyChange(int id, QVariant value);
    void systemDataSendToReceiver(int message_key, int message_value);
//    void sendToOtherProcess(QString name, QVariant value);
    // Hard Key
    void MSG_MCU_4_DataChange(PROPERTYID_SYSTEM id, const Type_uByte &_HardKeyNumber,const Type_uByte &_HardKeyStatus);
//    void sendToOtherCtrl(QString message_key, QVariant value);

    void setlan(QString lan);
    void key_pressed_released(int key, int type);

    void pCFG_EPBChanged(int pCFG_EPB);

public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);

    void dataSendFromSystemToReceiver(unsigned char attribute_key,unsigned char attribute_value);                      // System向Receiver发送数据
    void get_timeout500ms();
    void get_timeout100ms();
    void receiveDateFromOtherProcess(QString name, QVariant value);

    void setPCFG_EPB(int value)
    {
        if (m_pCFG_EPB == value)
            return;

        m_pCFG_EPB = value;
        emit pCFG_EPBChanged(m_pCFG_EPB);
        emit sendToOtherCtrl("CFG_EPB", value);
    }

protected:
    void dataChange();                       // Inherit From CBaseControl 10ms Check Send
//    void handleProperty(int propertyId, QVariant value){ emit PropertyChange(propertyId, value); }
    void selfCheckSendEnd();

private:
    QMutex mutex;
    void iC_Can_Info_Send(SYSTEM_IC_CAN_INFO_SEND_ID reqSendID);
    void isInterruptAutoCheck();
    void handleEEPROM(QString name, int value1, int value2);
    void handleOffScreenState(pm_hmi_notify_em _enumIndex);
    HMICustomTimer* autoCheckTimer;
    int m_pCFG_EPB;
};

#endif // SETTINGCONTROL_H
