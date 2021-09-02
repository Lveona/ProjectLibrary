#include "GaugeScreen.h"
#include <math.h>


static QMap< quint32, GaugeScreen::FunctionParser > tableScreen_Gauge = {
    {PROPERTYID_GAUGE_AUTOCHECK, &GaugeScreen::setAutoCheckState },//自检
    {PROPERTYID_GAUGE_DIGITSPEED, &GaugeScreen::setdigitSpeedValue },//车速
    {PROPERTYID_GAUGE_POWER, &GaugeScreen::setPowerValue },
};

//[0]
GaugeScreen::GaugeScreen()
    :m_digitSpeedValue("0")
    ,m_powerValue(0)
    ,m_autoCheckState(0)
{
}

GaugeScreen::~GaugeScreen()
{
}
//[2]
void GaugeScreen::startControl()
{
    qRegisterMetaType<PROPERTYID_GAUGE>("PROPERTYID_GAUGE");
    connect( GaugeControl::instance(), SIGNAL(PropertyChange(int,QVariant)),  GaugeScreen::instance(), SLOT(SetProperty(int,QVariant)), Qt::AutoConnection);
}

//[1]
void GaugeScreen::createCtrl(QQuickView *view)
{
    createAppControl(view->rootContext(), "GaugeScreen");
}

void GaugeScreen::SetProperty(int name, QVariant value){

    if(tableScreen_Gauge.value(name))
    {
        (this->*(tableScreen_Gauge.value(name)))(value);
    }
    else{
    }
}
