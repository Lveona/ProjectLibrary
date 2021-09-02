#include "telltalesScreen.h"

//static QMap< quint32, TelltalesScreen::FunctionParserTellData > tableScreen_TellData = {
////	{PROPERTYID_CRUISE, &TelltalesScreen::setCruiseLight },
////    {PROPERTYID_HDC, &TelltalesScreen::setHdcLight },
//    {PROPERTYID_CoolantAlarmLamp, &TelltalesScreen::setCoolantAlarmLamp },
//    {PROPERTYID_TurnLeftLamp, &TelltalesScreen::setTurnLeftLamp },
//    {PROPERTYID_TurnRightLamp, &TelltalesScreen::setTurnRightLamp },
//    {PROPERTYID_LowBeamLamp, &TelltalesScreen::setLowBeamLamp },
//    {PROPERTYID_HighBeamLamp, &TelltalesScreen::setHighBeamLamp },
//    {PROPERTYID_GearLamp, &TelltalesScreen::setGearLamp },
//    {PROPERTYID_LowPowerWarLamp, &TelltalesScreen::setLowPowerWarLamp },
//    {PROPERTYID_ChrgAcChrgnFailLamp, &TelltalesScreen::setChrgAcChrgnFailLamp },
//    {PROPERTYID_VcuHvBattErrLamp, &TelltalesScreen::setVcuHvBattErrLamp },
//    {PROPERTYID_EscReqBrkSysLamp, &TelltalesScreen::setEscReqBrkSysLamp },
//    {PROPERTYID_EpsSteerWarnLamp, &TelltalesScreen::setEpsSteerWarnLamp },
//    {PROPERTYID_DcdcFailrLamp, &TelltalesScreen::setDcdcFailrLamp },
//    {PROPERTYID_PosiLamp, &TelltalesScreen::setPosiLamp },
//    {PROPERTYID_EMotorAlarm, &TelltalesScreen::setEMotorAlarm },
//    {PROPERTYID_MainDrvrLamp, &TelltalesScreen::setMainDrvrLamp },
//    {PROPERTYID_PassDriverLamp, &TelltalesScreen::setPassDriverLamp },
//    {PROPERTYID_BackLeftLamp, &TelltalesScreen::setBackLeftLamp },
//    {PROPERTYID_BackMiddleLamp, &TelltalesScreen::setBackMiddleLamp },
//    {PROPERTYID_BackRightLamp, &TelltalesScreen::setBackRightLamp },
//    {PROPERTYID_AntiLockBrakeLamp, &TelltalesScreen::setAntiLockBrakeLamp },
//    {PROPERTYID_EbdBrakeLamp, &TelltalesScreen::setEbdBrakeLamp },
//    {PROPERTYID_EpbLamp, &TelltalesScreen::setEpbLamp },
//    {PROPERTYID_EpbFltLamp, &TelltalesScreen::setEpbFltLamp },
//    {PROPERTYID_ChrgAcChrgnLamp, &TelltalesScreen::setChrgAcChrgnLamp },
//    {PROPERTYID_ChrgCnctrDetdLamp, &TelltalesScreen::setChrgCnctrDetdLamp },
//    {PROPERTYID_VcuPtLamp, &TelltalesScreen::setVcuPtLamp },
//    {PROPERTYID_SystemFailureLamp, &TelltalesScreen::setSystemFailureLamp },
//    {PROPERTYID_SysPowerLimitationLamp, &TelltalesScreen::setSysPowerLimitationLamp },

//};

static QMap< quint32, TelltalesScreen::FunctionParser > tableScreen_Telltales = {
//    {PROPERTYID_ERROR, &TelltalesScreen::setErrorVisible }
    {PROPERTYID_ACC_SPEED, &TelltalesScreen::setAccSpeed},
    {PROPERTYID_SPEED_LIMIT, &TelltalesScreen::setSpeedlimit},

    {PROPERTYID_LEFT_NOTFASTEN, &TelltalesScreen::setBackLeftNotFasten},
    {PROPERTYID_RIGHT_NOTFASTEN, &TelltalesScreen::setBackRightNotFasten},
    {PROPERTYID_MID_NOTFASTEN, &TelltalesScreen::setBackMinNotFasten},

    {PROPERTYID_LEFT_SEATEMPTY, &TelltalesScreen::setBackLeftSeatEmpty},
    {PROPERTYID_RIGHT_SEATEMPTY, &TelltalesScreen::setBackRightSeatEmpty},
    {PROPERTYID_MID_SEATEMPTY, &TelltalesScreen::setBackMinSeatEmpty},
};

//[0]
TelltalesScreen::TelltalesScreen()
    :m_accSpeed("--")
    ,m_speedlimit("")
    ,m_backLeftNotFasten(false)
    ,m_backRightNotFasten(false)
    ,m_backMinNotFasten(false)
    ,m_backLeftSeatEmpty(false)
    ,m_backRightSeatEmpty(false)
    ,m_backMinSeatEmpty(false)
{
	qmlRegisterType<TellData>("TellData", 1, 0, "TellData");
//    qmlRegisterType<QList<TellData*>>("TellDataList", 1, 0, "TellDataList>");

    for(int i=0; i< PROPERTYID_MAX; i++)
    {
        m_telltaleStates.append((QObject*)new TellData());
    }

}


TelltalesScreen::~TelltalesScreen()
{
    delete TelltalesScreen::instance();
}
//[2]
void TelltalesScreen::startControl()
{
    qRegisterMetaType<TellData>("TellData");
    connect( TelltalesControl::instance(), SIGNAL(PropertyChange(int, const TellData)),  this,SLOT(SetProperty(int, const TellData)), Qt::QueuedConnection);    
    connect( TelltalesControl::instance(), SIGNAL(PropertyChange(int,QVariant)), this, SLOT(SetProperty(int,QVariant)), Qt::QueuedConnection);

}

//[1]
void TelltalesScreen::createCtrl(QQuickView *view)
{
    m_view = view;
    createAppControl(view->rootContext(), "TelltalesScreen");
}


void TelltalesScreen::SetProperty(int index, const TellData tell)
{
    TellData* tellData = (TellData*)m_telltaleStates[index];
    tellData->setTargetValue(tell.m_targetValue);
    tellData->setColorType(tell.m_colorType);

}

void TelltalesScreen::SetProperty(int name, QVariant value)
{
    if(tableScreen_Telltales.value(name))
    {
        (this->*(tableScreen_Telltales.value(name)))(value);
    }
    else{
    }
}
