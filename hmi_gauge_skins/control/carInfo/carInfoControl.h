#ifndef CARINFOCONTROL_H
#define CARINFOCONTROL_H

#include <hmi_share.h>

// CarInfo Used By AnChao Add
enum PROPERTYID_CARINFO {
    PROPERTYID_CARINFO_INIT = 0,
    PROPERTYID_CARINFO_PLUSMAINMILE,

    PROPERTYID_CARINFO_LF_TEMP_PRESSURE,
    PROPERTYID_CARINFO_RF_TEMP_PRESSURE,
    PROPERTYID_CARINFO_RR_TEMP_PRESSURE,
    PROPERTYID_CARINFO_LR_TEMP_PRESSURE,

    PROPERTYID_CARINFO_LF_TEMP,
    PROPERTYID_CARINFO_RF_TEMP,
    PROPERTYID_CARINFO_RR_TEMP,
    PROPERTYID_CARINFO_LR_TEMP,

    PROPERTYID_CARINFO_AR_DRIVE_DISTANCE,
    PROPERTYID_CARINFO_AR_DRIVE_TIME,
    PROPERTYID_CARINFO_AR_AVG_SPEED,
    PROPERTYID_CARINFO_AR_AVG_ENERGY,

    PROPERTYID_CARINFO_AS_DRIVE_DISTANCE,
    PROPERTYID_CARINFO_AS_DRIVE_TIME,
    PROPERTYID_CARINFO_AS_AVG_SPEED,
    PROPERTYID_CARINFO_AS_AVG_ENERGY,

    PROPERTYID_CARINFO_CHILD_INDEX,
    PROPERTYID_CARINFO_INDICATOR_NUM,
    PROPERTYID_CARINFO_CARD_SHOWN,
    PROPERTYID_LAST_CHARGE_TIME_DAY,
    PROPERTYID_LAST_CHARGE_TIME_HOUR,
    PROPERTYID_LAST_CHARGE_ODO,
    PROPERTYID_AVERAGE_APC_VALUE,
    PROPERTYID_CURRENT_APC_VALUE
};



enum CARINFOSCREENINDEX {
    CARINFOSCREENINDEX_AFTERSTART = 0,
    CARINFOSCREENINDEX_AFTERRESET,
//        CARINFOSCREENINDEX_ENERGYINFO,
    CARINFOSCREENINDEX_TYREINFO,
};

class CarInfoControl : public CBaseControl, public CSingleton<CarInfoControl>
{
    Q_OBJECT
public:
    CarInfoControl();
    ~CarInfoControl();
    typedef void (CarInfoControl::*CarInfoFunctionParser)();

    void func_MSG_AS_TRIP();
    void func_MSG_AS_AVG_SPEED();
    void func_MSG_AS_DRIVING_TIME();
    void func_MSG_AS_AVG_POWER();
    void func_MSG_AR_TRIP();
    void func_MSG_AR_AVG_SPEED();
    void func_MSG_AR_DRIVING_TIME();
    void func_MSG_AR_AVG_POWER();
    void func_MSG_REMAIN_RANGE();
    void func_MSG_LF_TIRE_PRESSURE();
    void func_MSG_RF_TIRE_PRESSURE();
    void func_MSG_RR_TIRE_PRESSURE();
    void func_MSG_LR_TIRE_PRESSURE();
    void func_MSG_LF_TIRE_TEMP();
    void func_MSG_RF_TIRE_TEMP();
    void func_MSG_RR_TIRE_TEMP();
    void func_MSG_LR_TIRE_TEMP();
    void func_MSG_LAST_CHARGE_TIME();
    void func_MSG_LAST_CHARGE_ODO();
    void func_MSG_AVG_APC_VALUE();
    void func_MSG_CURRENT_APC_VALUE();

    void handleCarInfoCardVisible();
    int getNextEnableItem(DIRECTION dir, int currentItem, QList<QString> cardlist);
    bool triggerHardKey(int keyValue, int type);
    bool handleHardKeyForCard();
    void notifyCScreen();
 signals:
    void sendToOtherCtrl(QString name, QVariant value);

public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void get_timeout500ms();

protected:
    void dataChange();

private:
    QMutex mutex;
    bool m_light_on;      //当前周期灯状态
    void tripBInfoClean(void);
    HMICustomTimer* showTimer;
};

#endif // CARINFOCONTROL_H
