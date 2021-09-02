#include "HomeScreen.h"

static QMap< quint32, HomeScreen::FunctionParser > tableScreen_Home = {

    {PROPERTYID_HOME_CHARGE_VALUE,       &HomeScreen::setChargeValue   },
    {PROPERTYID_HOME_CHARGE_COLOR,       &HomeScreen::setChargeColor },
    {PROPERTYID_HOME_TOTAL_MILE,         &HomeScreen::setOdo},
    {PROPERTYID_HOME_TEMP,               &HomeScreen::setTemp },
    {PROPERTYID_HOME_DOORWARNING,        &HomeScreen::setDoorWarning },
    {PROPERTYID_HOME_HOOD,               &HomeScreen::sethood },
    {PROPERTYID_HOME_FLDOOR,             &HomeScreen::setflDoor },
    {PROPERTYID_HOME_FRDOOR,             &HomeScreen::setfrDoor },
    {PROPERTYID_HOME_RLDOOR,             &HomeScreen::setrlDoor },
    {PROPERTYID_HOME_RRDOOR,             &HomeScreen::setrrDoor },
    {PROPERTYID_HOME_TAIL,               &HomeScreen::settail },
    {PROPERTYID_HOME_FLCHARGE,           &HomeScreen::setFlChargePort },
    {PROPERTYID_HOME_FRCHARGE,           &HomeScreen::setFrChargePort },
    {PROPERTYID_HOME_DRIVEMODE,          &HomeScreen::setDriveMode },
    {PROPERTYID_HOME_GEAR,               &HomeScreen::setGear },
    {PROPERTYID_HOME_CLOCK_FORMAT,       &HomeScreen::setClockFormat },
    {PROPERTYID_HOME_CLOCK,              &HomeScreen::setClock },
    {PROPERTYID_HOME_READY,              &HomeScreen::setIsReady },
    {PROPERTYID_HOME_CHARGE_CONNECT,     &HomeScreen::setChargeConn },
    {PROPERTYID_HOME_REMAIN_TIME,        &HomeScreen::setRemainTime },
    {PROPERTYID_HOME_CHARGE_STATUS,      &HomeScreen::setChargeStatus },
    {PROPERTYID_HOME_CHARGE_CNCTRDETD,   &HomeScreen::setChargeCnctrdetd },
    {PROPERTYID_HOME_IS_CHARGING,        &HomeScreen::setIsCharging },
    {PROPERTYID_HOME_VOLTAGE,            &HomeScreen::setChargeVoltage },
    {PROPERTYID_HOME_ELECTRIC,           &HomeScreen::setChargeElect },
};
HomeScreen::HomeScreen()
{
    m_chargeValue = "--";
    m_chargeColor  = COLORTYPEQML_RED;
    m_hood =   0;
    m_flDoor = 0;
    m_frDoor = 0;
    m_rlDoor = 0;
    m_rrDoor = 0;
    m_tail = 0;
    m_frChargePort = 0;
    m_flChargePort = 0;
    m_temp = "-.-";
    m_odo = "0";
    m_clock = "";
    m_clockFormat = "";
    m_driveMode = "";
    m_gear = "--";
    m_isReady = false;
    m_doorWarning = false;
    m_chargeConn = false;
    m_remainTime = "--";
    m_chargeStatus = "";
    m_chargeElect = "";
    m_chargeVoltage = "";
    m_isCharging = false;
    m_chargeCnctrdetd = 0;
}

HomeScreen::~HomeScreen()
{

}
void HomeScreen::startControl()
{
    connect(HomeControl::instance(), &HomeControl::PropertyChange, this, &HomeScreen::SetProperty, Qt::QueuedConnection);

}

void HomeScreen::createCtrl(QQuickView *view)
{
    createAppControl(view->rootContext(), "HomeScreen");
}

void HomeScreen::SetProperty(int name, QVariant value)
{
    if(tableScreen_Home.value(name))
    {
        (this->*(tableScreen_Home.value(name)))(value);
    }
    else{
    }
}

