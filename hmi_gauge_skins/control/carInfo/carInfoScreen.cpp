#include "carInfoScreen.h"

static QList<QVariant>g_instanceAPCList;

static QMap< quint32, CarInfoScreen::FunctionParser > tableScreen_CarInfo = {
    {PROPERTYID_CARINFO_PLUSMAINMILE, &CarInfoScreen::setRemainRange},

    {PROPERTYID_CARINFO_LF_TEMP_PRESSURE, &CarInfoScreen::setCarInfoTyreLFPressure},
    {PROPERTYID_CARINFO_RF_TEMP_PRESSURE, &CarInfoScreen::setCarInfoTyreRFPressure},
    {PROPERTYID_CARINFO_RR_TEMP_PRESSURE, &CarInfoScreen::setCarInfoTyreRRPressure},
    {PROPERTYID_CARINFO_LR_TEMP_PRESSURE, &CarInfoScreen::setCarInfoTyreLRPressure},
    {PROPERTYID_CARINFO_LF_TEMP,          &CarInfoScreen::setCarInfoTyreLFTemp},
    {PROPERTYID_CARINFO_RF_TEMP,          &CarInfoScreen::setCarInfoTyreRFTemp},
    {PROPERTYID_CARINFO_RR_TEMP,          &CarInfoScreen::setCarInfoTyreLRTemp},
    {PROPERTYID_CARINFO_LR_TEMP,          &CarInfoScreen::setCarInfoTyreRRTemp},

    {PROPERTYID_CARINFO_AR_DRIVE_DISTANCE,&CarInfoScreen::setAfterResetDrivingDistance},
    {PROPERTYID_CARINFO_AR_DRIVE_TIME,    &CarInfoScreen::setAfterResetDrivingTime},
    {PROPERTYID_CARINFO_AR_AVG_SPEED,     &CarInfoScreen::setAfterResetAvgSpeed},
    {PROPERTYID_CARINFO_AR_AVG_ENERGY,    &CarInfoScreen::setAfterResetAvgEnergy},

    {PROPERTYID_CARINFO_AS_DRIVE_DISTANCE,&CarInfoScreen::setAfterStartDrivingDistance},
    {PROPERTYID_CARINFO_AS_DRIVE_TIME,    &CarInfoScreen::setAfterStartDrivingTime},
    {PROPERTYID_CARINFO_CHILD_INDEX,      &CarInfoScreen::setIsCarInfoChildIndex},
    {PROPERTYID_CARINFO_INDICATOR_NUM,    &CarInfoScreen::setCardIndicatorNum},
    {PROPERTYID_CARINFO_CARD_SHOWN,       &CarInfoScreen::setIsCardShown},
    {PROPERTYID_LAST_CHARGE_TIME_DAY,     &CarInfoScreen::setChargeDay},
    {PROPERTYID_LAST_CHARGE_TIME_HOUR,    &CarInfoScreen::setChargeHour},
    {PROPERTYID_LAST_CHARGE_ODO,          &CarInfoScreen::setChargeOdo},
    {PROPERTYID_AVERAGE_APC_VALUE,        &CarInfoScreen::setAverageAPC},
    {PROPERTYID_CURRENT_APC_VALUE,        &CarInfoScreen::setCurrentAPC},
};

CarInfoScreen::CarInfoScreen()
{
    int len = 8;
    for(int i = 0; i<len; i++){
        g_instanceAPCList.append(0);
    }
    m_remainRange                   = "0";
    m_carInfoTyreLFPressure         = "--";
    m_carInfoTyreRFPressure         = "--";
    m_carInfoTyreLRPressure         = "--";
    m_carInfoTyreRRPressure         = "--";
    m_carInfoTyreLFTemp = "--";
    m_carInfoTyreRFTemp = "--";
    m_carInfoTyreLRTemp = "--";
    m_carInfoTyreRRTemp = "--";
    m_afterStartDrivingDistance = "0.0";
    m_afterStartDrivingTime = "00:00";
    m_afterStartAvgSpeed = "0";
    m_afterStartAvgEnergy = "0";

    m_afterResetDrivingDistance = "0.0";
    m_afterResetDrivingTime = "00:00";
    m_afterResetAvgSpeed = "0";
    m_afterResetAvgEnergy = "0";
    m_cardIndicatorNum = 0;
    m_isCarInfoChildIndex = 0;
    m_isCardShown = true;
    m_chargeDay = 0;
    m_chargeHour = 0;
    m_chargeOdo = 0;
    m_averageAPC = 0;
}

CarInfoScreen::~CarInfoScreen()
{
    // Nothing
}

void CarInfoScreen::createCtrl(QQuickView *view)
{
    createAppControl(view->rootContext(), "CarInfoScreen");
}

void CarInfoScreen::startControl()
{
    qRegisterMetaType<PROPERTYID_CARINFO>("PROPERTYID_CARINFO");
    connect(CarInfoControl::instance(), &CarInfoControl::PropertyChange, this, &CarInfoScreen::SetProperty, Qt::QueuedConnection);
}
void CarInfoScreen::SetProperty(int name, QVariant value)
{
    if(tableScreen_CarInfo.value(name))
    {
        (this->*(tableScreen_CarInfo.value(name)))(value);
    }
    else{
    }
}
void CarInfoScreen::setEnergyList(QVariant value)
{
    if(g_instanceAPCList.length()>0){
        g_instanceAPCList.pop_front();
        g_instanceAPCList.append(value);
    }else{
        g_instanceAPCList.append(value);
    }
}
QVariantList CarInfoScreen::qmlInstanceList()
{
    return g_instanceAPCList;
}

void CarInfoScreen::iC_Can_Info_Send(int reqSendID)
{
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;
    (void)pUser_data;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0601;

    switch (reqSendID) {
    case CARINFO_MAINTENANCECLEAR :
        _buffer.data[1] = 0x02;
        break;
    default:
        return;
    }
    ivs_client_send_request(&_buffer, pUser_data);
}
