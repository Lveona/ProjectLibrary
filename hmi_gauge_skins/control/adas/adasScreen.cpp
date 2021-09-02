#include "adasScreen.h"

static QMap< quint32, ADASScreen::FunctionParser > tableScreen_ADAS = {
    {PROPERTYID_ADAS_DOW_FL,       &ADASScreen::setADAS_DOW_FL},
    {PROPERTYID_ADAS_DOW_RL,       &ADASScreen::setADAS_DOW_RL},
    {PROPERTYID_ADAS_DOW_FR,       &ADASScreen::setADAS_DOW_FR},
    {PROPERTYID_ADAS_DOW_RR,       &ADASScreen::setADAS_DOW_RR},
    {PROPERTYID_ADAS_RCW_WARN,     &ADASScreen::setRCW_WARN},
    {PROPERTYID_ADAS_FCW_WARN,       &ADASScreen::setFCW_WARN},
    {PROPERTYID_RCTA_LEFT_WARN,       &ADASScreen::setRCTA_LEFT_WARN},
    {PROPERTYID_RCTA_RIGHT_WARN,       &ADASScreen::setRCTA_RIGHT_WARN},
    {PROPERTYID_LCA_LEFT_WARN,       &ADASScreen::setLCA_LEFT_WARN},
    {PROPERTYID_LCA_RIGHT_WARN,     &ADASScreen::setLCA_RIGHT_WARN},
    {PROPERTYID_LANELINE3_COLOR,       &ADASScreen::setLaneLine3_Color},
    {PROPERTYID_LANELINE1_COLOR,       &ADASScreen::setLaneLine1_Color},
    {PROPERTYID_LANELINE2_COLOR,       &ADASScreen::setLaneLine2_Color},
    {PROPERTYID_LANELINE4_COLOR,       &ADASScreen::setLaneLine4_Color},
    {PROPERTYID_LANELINE3_DISPLAY, &ADASScreen::setLaneLine3_Display},
    {PROPERTYID_LANELINE1_DISPLAY, &ADASScreen::setLaneLine1_Display},
    {PROPERTYID_LANELINE2_DISPLAY, &ADASScreen::setLaneLine2_Display},
    {PROPERTYID_LANELINE4_DISPLAY, &ADASScreen::setLaneLine4_Display},
    {PROPERTYID_LANELINE3_TYPE,    &ADASScreen::setLaneLine3_Type},
    {PROPERTYID_LANELINE1_TYPE,    &ADASScreen::setLaneLine1_Type},
    {PROPERTYID_LANELINE2_TYPE,    &ADASScreen::setLaneLine2_Type},
    {PROPERTYID_LANELINE4_TYPE,    &ADASScreen::setLaneLine4_Type},
    {PROPERTYID_LANELINE3_CURVATURE,    &ADASScreen::setLaneLine3_Curv},
    {PROPERTYID_LANELINE1_CURVATURE,    &ADASScreen::setLaneLine1_Curv},
    {PROPERTYID_LANELINE2_CURVATURE,    &ADASScreen::setLaneLine2_Curv},
    {PROPERTYID_LANELINE4_CURVATURE,    &ADASScreen::setLaneLine4_Curv},

    {PROPERTYID_FCTA_LEFT_WARN,           &ADASScreen::setFctaLeft},
    {PROPERTYID_FCTA_RIGHT_WARN,          &ADASScreen::setFctaRight},
    {PROPERTYID_ACC_OBJECTCAPTUREDSTATUS, &ADASScreen::setObjectCapturedStatus},
    {PROPERTYID_ADAS_TRACKTAR0_STATIC_ST, &ADASScreen::setTrackTarget0_Static_st},
    {PROPERTYID_ADAS_TRACKTAR1_STATIC_ST, &ADASScreen::setTrackTarget1_Static_st},
    {PROPERTYID_ADAS_TRACKTAR2_STATIC_ST, &ADASScreen::setTrackTarget2_Static_st},
    {PROPERTYID_ADAS_TRACKTAR3_STATIC_ST, &ADASScreen::setTrackTarget3_Static_st},
    {PROPERTYID_ADAS_TRACKTAR4_STATIC_ST, &ADASScreen::setTrackTarget4_Static_st},
    {PROPERTYID_ADAS_TRACKTAR5_STATIC_ST, &ADASScreen::setTrackTarget5_Static_st},
    {PROPERTYID_ADAS_TRACKTARGET0_STATIC_OBJECTTYPE, &ADASScreen::setTrackTarget0_Static_ObjectType},
    {PROPERTYID_ADAS_TRACKTARGET1_STATIC_OBJECTTYPE, &ADASScreen::setTrackTarget1_Static_ObjectType},
    {PROPERTYID_ADAS_TRACKTARGET2_STATIC_OBJECTTYPE, &ADASScreen::setTrackTarget2_Static_ObjectType},
    {PROPERTYID_ADAS_TRACKTARGET3_STATIC_OBJECTTYPE, &ADASScreen::setTrackTarget3_Static_ObjectType},
    {PROPERTYID_ADAS_TRACKTARGET4_STATIC_OBJECTTYPE, &ADASScreen::setTrackTarget4_Static_ObjectType},
    {PROPERTYID_ADAS_TRACKTARGET5_STATIC_OBJECTTYPE, &ADASScreen::setTrackTarget5_Static_ObjectType},

    {PROPERTYID_ADAS_TRACKTAR0_STATIC_LGTPO, &ADASScreen::setTrackTar0_Static_LGTP0},
    {PROPERTYID_ADAS_TRACKTAR1_STATIC_LGTPO, &ADASScreen::setTrackTar1_Static_LGTP0},
    {PROPERTYID_ADAS_TRACKTAR2_STATIC_LGTPO, &ADASScreen::setTrackTar2_Static_LGTP0},
    {PROPERTYID_ADAS_TRACKTAR3_STATIC_LGTPO, &ADASScreen::setTrackTar3_Static_LGTP0},
    {PROPERTYID_ADAS_TRACKTAR4_STATIC_LGTPO, &ADASScreen::setTrackTar4_Static_LGTP0},
    {PROPERTYID_ADAS_TRACKTAR5_STATIC_LGTPO, &ADASScreen::setTrackTar5_Static_LGTP0},
    {PROPERTYID_ADAS_TRACKTAR0_STATIC_LATPO, &ADASScreen::setTrackTar0_Static_LATPO},
    {PROPERTYID_ADAS_TRACKTAR1_STATIC_LATPO, &ADASScreen::setTrackTar1_Static_LATPO},
    {PROPERTYID_ADAS_TRACKTAR2_STATIC_LATPO, &ADASScreen::setTrackTar2_Static_LATPO},
    {PROPERTYID_ADAS_TRACKTAR3_STATIC_LATPO, &ADASScreen::setTrackTar3_Static_LATPO},
    {PROPERTYID_ADAS_TRACKTAR4_STATIC_LATPO, &ADASScreen::setTrackTar4_Static_LATPO},
    {PROPERTYID_ADAS_TRACKTAR5_STATIC_LATPO, &ADASScreen::setTrackTar5_Static_LATPO},
    {PROPERTYID_ANRC_PRKGSTSINDCR,           &ADASScreen::setPrkgStsIndcr},
    {PROPERTYID_ANRC_PRKGLESLOTTYP1,         &ADASScreen::setPrkgLeSlotTyp1},
    {PROPERTYID_ANRC_PRKGLESLOTTYP2,         &ADASScreen::setPrkgLeSlotTyp2},
    {PROPERTYID_ANRC_PRKGLESLOTTYP3,         &ADASScreen::setPrkgLeSlotTyp3},
    {PROPERTYID_ANRC_PRKGRISLOTTYP1,         &ADASScreen::setPrkgRiSlotTyp1},
    {PROPERTYID_ANRC_PRKGRISLOTTYP2,         &ADASScreen::setPrkgRiSlotTyp2},
    {PROPERTYID_ANRC_PRKGRISLOTTYP3,         &ADASScreen::setPrkgRiSlotTyp3},
    {PROPERTYID_PARK_UP_DISTANCE,            &ADASScreen::setParkUpDistance},
    {PROPERTYID_PARK_DOWN_DISTANCE,          &ADASScreen::setParkDownDistance},
    {PROPERTYID_PARK_UP_DISTANCE_COLOR,      &ADASScreen::setParkUpDistanceColor},
    {PROPERTYID_PARK_DOWN_DISTANCE_COLOR,    &ADASScreen::setParkDownDistanceColor},
    {PROPERTYID_PARK_LEFT_DISTANCE_COLOR,    &ADASScreen::setParkLeftDistanceColor},
    {PROPERTYID_PARK_RIGHT_DISTANCE_COLOR,   &ADASScreen::setParkRightDistanceColor},
    {PROPERTYID_ILC_LEFT,                    &ADASScreen::setLeftILC},
    {PROPERTYID_ILC_RIGHT,                   &ADASScreen::setRightILC},
    {PROPERTYID_ILC_LEFT_VISIBLE,            &ADASScreen::setLeftILCVisible},
    {PROPERTYID_ILC_RIGHT_VISIBLE,           &ADASScreen::setRightILCVisible},
    {PROPERTYID_MINIADAS_VISIBLE,            &ADASScreen::setMiniAdasVisible},
    {PROPERTYID_ACC_TIME_GAP,                &ADASScreen::setAccTimeGap},
    {PROPERTYID_ACC_TIME_GAP_VISIBLE,        &ADASScreen::setAccTimeGapVisible},
};

ADASScreen::ADASScreen()
{
    m_adasEnumsObject = new ADASEnums();

    m_ADAS_DOW_FL = ADASEnums::NOWARNING;
    m_ADAS_DOW_RL = ADASEnums::NOWARNING;
    m_ADAS_DOW_FR = ADASEnums::NOWARNING;
    m_ADAS_DOW_RR = ADASEnums::NOWARNING;
    m_RCW_WARN = ADASEnums::NOWARNING;
    m_FCW_WARN = ADASEnums::NOWARNING;
    m_RCTA_LEFT_WARN = ADASEnums::NOWARNING;
    m_RCTA_RIGHT_WARN = ADASEnums::NOWARNING;
    m_LCA_LEFT_WARN = ADASEnums::NOWARNING;
    m_LCA_RIGHT_WARN = ADASEnums::NOWARNING;
    m_leftILC = ADASEnums::NOWARNING;
    m_rightILC = ADASEnums::NOWARNING;
    m_leftILCVisible = false;
    m_rightILCVisible = false;
    m_miniAdasVisible = false;
    m_accTimeGap = 0;
    m_accTimeGapVisible = false;

    m_laneLine3 = m_laneLine2 = m_laneLine1 = m_laneLine4 = QColor(Qt::gray).name();
    m_laneLine1_Display = m_laneLine2_Display = m_laneLine3_Display = m_laneLine4_Display = false;
    m_laneLine1_Type = m_laneLine2_Type = m_laneLine3_Type = m_laneLine4_Type = 0;
    m_laneLine1_Curv = m_laneLine2_Curv = m_laneLine3_Curv = m_laneLine4_Curv = 0;
    m_laneLine1_Color = m_laneLine2_Color = m_laneLine3_Color = m_laneLine4_Color = 0;
    qmlRegisterType<TargetData>("TargetData", 1, 0, "TargetData");
    for(int i=0; i< ADASTAEGET_MAX; i++)
    {
        m_adasTargetList.append((QObject*)new TargetData());
    }
}

ADASScreen::~ADASScreen()
{
}

void ADASScreen::createCtrl(QQuickView *view)
{
    createAppControl(view->rootContext(), "ADASScreen");
}

void ADASScreen::startControl()
{
    qRegisterMetaType<PROPERTYID_ADAS>("PROPERTYID_ADAS");
    qRegisterMetaType<TargetData>("TargetData");
    connect(ADASControl::instance(), SIGNAL(PropertyChange(int,QVariant)), this, SLOT(SetProperty(int,QVariant)), Qt::QueuedConnection);
    connect(ADASControl::instance(), SIGNAL(PropertyChange(int, const TargetData)),  this,SLOT(SetProperty(int, const TargetData)), Qt::QueuedConnection);

}

void ADASScreen::SetProperty(int index, const TargetData target)
{
    TargetData* targetData = (TargetData*)m_adasTargetList[index];
    targetData->setTargetObjectType(target.m_targetObjectType);
    targetData->setPositionX(target.m_positionX);
    targetData->setpositionY(target.m_positionY);
    targetData->setArcRadius(target.m_arcRadius);
    targetData->setArcStartAngle(target.m_arcStartAngle);
    targetData->setArcColor(target.m_arcColor);
    targetData->setEnable(target.m_enable);
}

void ADASScreen::SetProperty(int name, QVariant value)
{
    if(tableScreen_ADAS.value(name))
    {
        (this->*(tableScreen_ADAS.value(name)))(value);
    }
}



