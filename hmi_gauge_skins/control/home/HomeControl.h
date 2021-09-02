#ifndef HomeCONTROL_H
#define HomeCONTROL_H

#include <hmi_share.h>


/***********************************ENUM*****************************************/
enum PROPERTYID_HOME
{
    PROPERTYID_HOME_CHARGE_VALUE,
    PROPERTYID_HOME_CHARGE_COLOR,
    PROPERTYID_HOME_DOORWARNING,
    PROPERTYID_HOME_HOOD,
    PROPERTYID_HOME_FLDOOR,
    PROPERTYID_HOME_FRDOOR,
    PROPERTYID_HOME_RLDOOR,
    PROPERTYID_HOME_RRDOOR,
    PROPERTYID_HOME_TAIL,
    PROPERTYID_HOME_FLCHARGE,
    PROPERTYID_HOME_FRCHARGE,
    PROPERTYID_HOME_BATTERY_HEAT_STATE,
    PROPERTYID_HOME_TEMP,
    PROPERTYID_HOME_TOTAL_MILE,

    PROPERTYID_HOME_CLOCK,
    PROPERTYID_HOME_CLOCK_FORMAT,
    PROPERTYID_HOME_RANGE_MILE,
    PROPERTYID_HOME_UNIT_MILE,
    PROPERTYID_HOME_GEAR,
    PROPERTYID_HOME_READY,
    PROPERTYID_HOME_DRIVEMODE,
    PROPERTYID_HOME_CHARGE_CONNECT,
    PROPERTYID_HOME_CHARGE_STATUS,
    PROPERTYID_HOME_REMAIN_TIME,
    PROPERTYID_HOME_CHARGE_CNCTRDETD,
    PROPERTYID_HOME_IS_CHARGING,

    PROPERTYID_HOME_VOLTAGE,
    PROPERTYID_HOME_ELECTRIC,

};


enum COLORTYPEQML
{
    COLORTYPEQML_NONE = 0,
    COLORTYPEQML_GREEN,
    COLORTYPEQML_WHITE,
    COLORTYPEQML_RED,
    COLORTYPEQML_YELLOW,
    COLORTYPEQML_GRAY,
};

#define MCU_LEVEL_P     0x01
#define MCU_LEVEL_R     0x02
#define MCU_LEVEL_N     0x03
#define MCU_LEVEL_D     0x04
#define MCU_LEVEL_M     0x05
#define MCU_LEVEL_M1    0x05
#define MCU_LEVEL_M2    0x06
#define MCU_LEVEL_M3    0x07
#define MCU_LEVEL_M4    0x08
#define MCU_LEVEL_M5    0x09
#define MCU_LEVEL_M6    0x0a
#define MCU_LEVEL_M7    0x0b
#define MCU_LEVEL_LOW   0x0c
#define MCU_LEVEL_M1U   0x0d
#define MCU_LEVEL_M2U   0x0e
#define MCU_LEVEL_M3U   0x0f
#define MCU_LEVEL_M4U   0x10
#define MCU_LEVEL_M5U   0x11
#define MCU_LEVEL_M6U   0x12
#define MCU_LEVEL_M2D   0x14
#define MCU_LEVEL_M3D   0x15
#define MCU_LEVEL_M4D   0x16
#define MCU_LEVEL_M5D   0x17
#define MCU_LEVEL_M6D   0x18
#define MCU_LEVEL_M7D   0x19
//D
#define MCU_LEVEL_D1    0x05
#define MCU_LEVEL_D2    0x06
#define MCU_LEVEL_D3    0x07
#define MCU_LEVEL_D4    0x08
#define MCU_LEVEL_D5    0x09
#define MCU_LEVEL_D6    0x0a
#define MCU_LEVEL_D7    0x0b
//#define MCU_LEVER_NONE  0x00
/***********************************ENUM*****************************************/

class QMutex;
class HomeControl : public CBaseControl, public CSingleton<HomeControl>
{
    Q_OBJECT
    friend class CSingleton<HomeControl>;

public:
    HomeControl();
    ~HomeControl();
    typedef void (HomeControl::*HomeFunctionParser)();

    void func_CHARGE_PERCENT();
    void func_CHARGE_COLOR();
    void func_DRIVE_MODE();
    void func_CHARGE_STATUS ();
    void func_CHARGE_CABLE_STATUS();
    void func_TEMP();
    void func_READY();
    void func_GEAR();
    void func_FL_DOOR_STATUS();
    void func_FR_DOOR_STATUS();
    void func_RL_DOOR_STATUS();
    void func_RR_DOOR_STATUS();
    void func_TAIL();
    void func_HOOD();
    void func_FL_CHARGE_PORT();
    void func_RL_CHARGE_PORT();
    void func_REMAIN_CHARGE_TIME();
    void func_ODO();
    void func_CHARING_VOLTAGE();
    void func_CHARING_ELECTRIC();

public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);

protected:
    virtual void dataChange();

private:
    QMutex mutex;
    void handleDoorVoice();
};


#endif // HomeCONTROL_H
