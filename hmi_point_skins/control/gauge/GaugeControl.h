#ifndef GaugeCONTROL_H
#define GaugeCONTROL_H

#include <hmi_share.h>

class QMutex;

class CStepperAnimation;
class GaugeControl;
class CStrategyAnimation;
class GaugeThread;

/***********************************ENUM*****************************************/
enum PROPERTYID_GAUGE
{
    PROPERTYID_GAUGE_AUTOCHECK,
    PROPERTYID_GAUGE_DIGITSPEED,
    PROPERTYID_GAUGE_POWER,
};

enum POWERMODE_POINT {// 电源
    POWERMODE_POINT_INIT = 0,         // 初始值
    POWERMODE_POINT_OPENING,          // Opening
    POWERMODE_POINT_IGON,            // IG_ON
    POWERMODE_POINT_IGOFF,           // IG_OFF
};

enum GAUGE_IC_CAN_INFO_SEND_ID{
    GAUGE_IC_CAN_INFO_TripSwitchSts = 0x0,
    GAUGE_IC_CAN_INFO_ID_MAX
};

class CStepperAnimation
{
public:

    uint32_t spanTime;                          /* Seconds */
    float minValue;
    float maxValue;
    float currentValue;
    float targetValue;
};

class GaugeControl: public CBaseControl, public CSingleton<GaugeControl>
{
    Q_OBJECT
    friend class CSingleton<GaugeControl>;
public:
    GaugeControl();
    ~GaugeControl();

    typedef void (GaugeControl::*GaugeFunctionParser)();
    //typedef void (GaugeControl::*GaugeVoidFunctionParser)();

    void iC_Can_Send(GAUGE_IC_CAN_INFO_SEND_ID reqSendID);
    char* getBackup(int id);
    float getForTest(int type);

    void func_HandleSpeed();
    void func_HandleEngPwr();
signals:
    void PorpertyChange(int id,QVariant value);
public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void get_timeout500ms();
    void receiveDateFromOtherProcess(QString name, QVariant value);

protected:
    void dataChange();

private:
    void iC_Can_Info_Send(GAUGE_IC_CAN_INFO_SEND_ID reqSendID);
};

#endif // GaugeCONTROL_H
