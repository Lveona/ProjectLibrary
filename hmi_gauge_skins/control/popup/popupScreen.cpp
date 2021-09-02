#include "popupScreen.h"
#include "popupControl.h"
#include <QList>
#include "uniqPopAddInfo.h"
#include "popup.h"
#include "popupStrategy.h"

//[0]
PopupScreen::PopupScreen()
{
    //qDebug()<<"PopupScreen::PopupScreen"<<QThread::currentThreadId()<<QThread::currentThread();

    //RegisterType:[DataObject] To QML
    qmlRegisterType<DataObject>("PopupDataObject", 1, 0, "DataObject");
    //init
    m_popupDataObject = new DataObject("", "", "",0);
//    m_popupTyreSts    = new PopTyreSts;
//    m_propertyindex   = PROPERTYID_MAX;
    m_driveModeWarningImagePath = "";
    m_driveModeWarningMsgText   = "";
    m_isGlobalNaviSource        = false;

    m_kdrvStblt = "";
    m_kdrvVisible = false;
    m_kpasStblt = "";
    m_kpasVisible = false;
    m_krlStblt = "";
    m_krlVisible = false;
    m_krrStblt = "";
    m_krrVisible = false;
    m_krmStblt = "";
    m_krmVisible = false;
    m_tempwarning_LF = false;
    m_tempwarning_RF = false;
    m_tempwarning_RR = false;
    m_tempwarning_LR = false;
    m_limitSpeed = "";
    m_redCardNumber = 0;
    m_yellowCardNumber = 0;
    m_redCardCurrentIndex = 0;
    m_yellowCardCurrentIndex = 0;
    m_yellowCardListHide = false;
}

PopupScreen::~PopupScreen()
{
//    delete m_popupTyreSts;
    delete m_popupDataObject;
    delete PopupScreen::instance();
}

static QMap< quint32, PopupScreen::FunctionParser > tableScreen_popup = {
    {PROPERTYID_SEAT_DRIV_VISIBLE, &PopupScreen::setKdrvVisible },
    {PROPERTYID_SEAT_DRIV_COLOR, &PopupScreen::setKdrvStblte },
    {PROPERTYID_SEAT_PAS_VISIBLE, &PopupScreen::setKpasVisible },
    {PROPERTYID_SEAT_PAS_COLOR, &PopupScreen::setKpasStblte },
    {PROPERTYID_SEAT_RL_VISIBLE, &PopupScreen::setKrlVisible },
    {PROPERTYID_SEAT_RL_COLOR, &PopupScreen::setKrlStblte },
    {PROPERTYID_SEAT_RR_VISIBLE, &PopupScreen::setKrrVisible },
    {PROPERTYID_SEAT_RR_COLOR, &PopupScreen::setKrrStblte },
    {PROPERTYID_SEAT_RM_VISIBLE, &PopupScreen::setKrmVisible },
    {PROPERTYID_SEAT_RM_COLOR, &PopupScreen::setKrmStblte },
    {PROPERTYID_POPUP_LF_TEMP_WARNING, &PopupScreen::setTempwarning_LF },
    {PROPERTYID_POPUP_RF_TEMP_WARNING, &PopupScreen::setTempwarning_RF },
    {PROPERTYID_POPUP_RR_TEMP_WARNING, &PopupScreen::setTempwarning_RR },
    {PROPERTYID_POPUP_LR_TEMP_WARNING, &PopupScreen::setTempwarning_LR },
    {PROPERTYID_POPUP_LimitSpeed, &PopupScreen::setLimitSpeed },
    {PROPERTYID_POPUP_REDCARD_LISTLENTH, &PopupScreen::setRedCardNumber },
    {PROPERTYID_POPUP_YELLOWCARD_LISTLENTH, &PopupScreen::setYellowCardNumber },
    {PROPERTYID_POPUP_REDCARD_CURRENTINDEX, &PopupScreen::setRedCardCurrentIndex },
    {PROPERTYID_POPUP_YELLOWCARD_CURRENTINDEX, &PopupScreen::setYellowCardCurrentIndex },
    {PROPERTYID_POPUP_YELLOWCARD_HIDELIST, &PopupScreen::setYellowCardListHide },
};

////[2]
void PopupScreen::startControl()
{
    //qDebug()<<"PopupScreen::startControl"<<QThread::currentThreadId()<<QThread::currentThread();

    // connect to PopupLib
    connect(PopupControl::instance(), SIGNAL(PropertyChange(int, QVariant)), this, SLOT(SetProperty(int ,QVariant)), Qt::QueuedConnection);
    qRegisterMetaType<Popup*>("Popup*");
    connect(PopupControl::instance(), SIGNAL(PropertyChange(Popup*)), this, SLOT(SetProperty(Popup*)), Qt::QueuedConnection);

    qRegisterMetaType<QList<PopupFaultQuery>>("QList<PopupFaultQuery>");
    connect(PopupControl::instance(), SIGNAL(PropertyChange(QList<PopupFaultQuery>)), this, SLOT(SetProperty(QList<PopupFaultQuery>)), Qt::QueuedConnection);

    connect(PopupControl::instance(), SIGNAL(PropertyChange(QList<PopupFaultQuery>)), this, SLOT(SetProperty(QList<PopupFaultQuery>)), Qt::QueuedConnection);

    connect(PopupStrategy::instance(),SIGNAL(PropertyChange_show_toast(QString, QString, int)), this, SLOT(SetProperty_show_toast(QString , QString, int)), Qt::QueuedConnection);

    connect(PopupStrategy::instance(),SIGNAL(PropertyChange_hide_toast(QString, QString, int)), this, SLOT(SetProperty_hide_toast(QString , QString, int)), Qt::QueuedConnection);

    connect(PopupStrategy::instance(),SIGNAL(PropertyChange_show_adastoast(QString, QString, int)), this, SLOT(SetProperty_show_adas_toast(QString , QString, int)), Qt::QueuedConnection);

    connect(PopupStrategy::instance(),SIGNAL(PropertyChange_hide_adastoast(QString, QString, int)), this, SLOT(SetProperty_hide_adas_toast(QString , QString, int)), Qt::QueuedConnection);
}

//[1]
void PopupScreen::createCtrl(QQuickView *view)
{
//    qDebug()<<"PopupScreen::createCtrl"<<QThread::currentThreadId()<<QThread::currentThread();
    m_view = view;
    createAppControl(view->rootContext(), "PopupScreen");
    createAppControl(view->rootContext(), "DataObject");
}
//PropertyChange_show_toast
void PopupScreen::SetProperty_show_toast(QString name , QString iconname, int category)
{
//    add
//    del
    emit addToast(name, iconname, category);
}
//PropertyChange_hide_toast
void PopupScreen::SetProperty_hide_toast( QString name , QString iconname, int category)
{
//    add
//    del
    emit delToast(name, iconname, category);
}

void PopupScreen::SetProperty_show_adas_toast(QString name, QString iconname, int category)
{
    emit addAdasToast(name, iconname, category);
}

void PopupScreen::SetProperty_hide_adas_toast(QString name, QString iconname, int category)
{
    emit delAdasToast(name, iconname, category);
}

void PopupScreen::SetProperty(Popup * ptPop)
{
    //qInfo()<<__FUNCTION__<<ptPop->symbol<<ptPop->name;
    m_popupDataObject->seticonname(ptPop->symbol);
    m_popupDataObject->setName(ptPop->name);
    m_popupDataObject->setPriorityvalue(ptPop->category);
}

void PopupScreen::SetProperty(QList<PopupFaultQuery> pop)
{
    // 报警信息列表
    int lenQ = m_popupFaultQueryList.length();
    for(int i=0; i<lenQ; i++){
        delete m_popupFaultQueryList[i];
    }
    m_popupFaultQueryList.clear();

    int len = pop.length();
    for(int i=0; i<len; i++){
        m_popupFaultQueryList.prepend(new PopupFaultQuery(pop.at(i)));
    }

    //为了满足pathview描画，保证数据量超过5条
    if(m_popupFaultQueryList.count() == 3 || m_popupFaultQueryList.count() == 4 ){
        for(int i=0; i<len; i++){
            m_popupFaultQueryList.prepend(new PopupFaultQuery(pop.at(i)));
        }
    }

    if(m_view){
        m_view->rootContext()->setContextProperty("popupFaultQueryList", QVariant::fromValue(m_popupFaultQueryList));
    }
}

void PopupScreen::SetProperty(int name,QVariant value)
{
    if(tableScreen_popup.value(name))
    {
        (this->*(tableScreen_popup.value(name)))(value);
    }
    else{
    }
}

void PopupScreen::SetProperty(const UniqPopAddInfo* ptUniqInfo){
    if(NULL == ptUniqInfo){
       qCritical()<<"ptUniqInfo is Error!"<<ptUniqInfo;
       return;
    }

    m_popupDataObject->setmainSeat(ptUniqInfo->ptPopSeatBelt->m_FrontLeftSeat);
    m_popupDataObject->setcopilotSeat(ptUniqInfo->ptPopSeatBelt->m_FrontRightSeat);
    m_popupDataObject->setrearLeftSeat(ptUniqInfo->ptPopSeatBelt->m_RearLeftSeat);
    m_popupDataObject->setrearMiddleSeat(ptUniqInfo->ptPopSeatBelt->m_RearMiddleSeat);
    m_popupDataObject->setrearRightSeat(ptUniqInfo->ptPopSeatBelt->m_RearRightSeat);
    m_popupDataObject->setVertical_View(ptUniqInfo->ptPopSeatBelt->m_Vertical_View);

    m_popupDataObject->sethood(((ptUniqInfo->ptPopCarDoor->m_HoodSts==0x01)? true: false));
    m_popupDataObject->setflDoor(((ptUniqInfo->ptPopCarDoor->m_FLDoorSts==0x01)? true: false));
    m_popupDataObject->setfrDoor(((ptUniqInfo->ptPopCarDoor->m_FRDoorSts==0x01)? true: false));
    m_popupDataObject->setrlDoor(((ptUniqInfo->ptPopCarDoor->m_RLDoorSts==0x01)? true: false));
    m_popupDataObject->setrrDoor(((ptUniqInfo->ptPopCarDoor->m_RRDoorSts==0x01)? true: false));
    m_popupDataObject->settail(false);
    m_popupDataObject->setIsWarning(ptUniqInfo->ptPopCarDoor->m_isWarning);

//    LOGPRINT(QString("ptUniqInfo->ptPopTyre->m_popupTyreLFWarning:%1").arg(ptUniqInfo->ptPopTyre->m_popupTyreLFWarning));
    m_popupDataObject->settyreWarnningLine_FL(ptUniqInfo->ptPopTyre->m_popupTyreLFWarning);
    m_popupDataObject->settyreWarnningLine_FR(ptUniqInfo->ptPopTyre->m_popupTyreRFWarning);
    m_popupDataObject->settyreWarnningLine_RL(ptUniqInfo->ptPopTyre->m_popupTyreLRWarning);
    m_popupDataObject->settyreWarnningLine_RR(ptUniqInfo->ptPopTyre->m_popupTyreRRWarning);
}

void PopupScreen::SetPropertyGlobalNaviSource(bool _isGlobalNaviSource){
    setisGlobalNaviSource(_isGlobalNaviSource);
}

void PopupScreen::setisGlobalNaviSource(const bool   &_isGlobalNaviSource)
{
    if (_isGlobalNaviSource != m_isGlobalNaviSource) {
        m_isGlobalNaviSource = _isGlobalNaviSource;
        emit isGlobalNaviSourceChanged();
    }
}


void DataObject::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

void DataObject::setPriorityvalue(const int &priorityvalue)
{
    if (priorityvalue != m_priorityvalue) {
        m_priorityvalue = priorityvalue;
        emit priorityvalueChanged();
    }
}

void DataObject::settext(const QString &text)
{
    if (text != m_text) {
        m_text = text;
        emit textChanged();
    }
}

void DataObject::seticonname(const QString &iconname)
{
    if (iconname != m_iconname) {
        m_iconname = iconname;
        emit iconnameChanged();
    }
}

void DataObject::sethood(const bool &hood)
{
    if (hood != m_hood) {
        m_hood = hood;
        emit hoodChanged();
        //qDebug()<<"##########seticonname!"<<hood;
    }
}

void DataObject::setflDoor(const bool &flDoor)
{
    if (flDoor != m_flDoor) {
        m_flDoor = flDoor;
        emit flDoorChanged();
        //qDebug()<<"##########seticonname!"<<flDoor;
    }
}

void DataObject::setfrDoor(const bool &frDoor)
{
    if (frDoor != m_frDoor) {
        m_frDoor = frDoor;
        emit frDoorChanged();
        //qDebug()<<"##########seticonname!"<<frDoor;
    }
}

void DataObject::setrlDoor(const bool &rlDoor)
{
    if (rlDoor != m_rlDoor) {
        m_rlDoor = rlDoor;
        emit rlDoorChanged();
        //qDebug()<<"##########seticonname!"<<rlDoor;
    }
}

void DataObject::setrrDoor(const bool &rrDoor)
{
    if (rrDoor != m_rrDoor) {
        m_rrDoor = rrDoor;
        emit rrDoorChanged();
        //qDebug()<<"##########seticonname!"<<rrDoor;
    }
}

void DataObject::settail(const bool &tail)
{
    if (tail != m_tail) {
        m_tail = tail;
        emit tailChanged();
        //qDebug()<<"##########seticonname!"<<tail;
    }
}

void DataObject::setFLTyreSts(const int &fLTyreSts)
{
    if (fLTyreSts != m_FLTyreSts) {
        m_FLTyreSts = fLTyreSts;
        emit fLTyreStsChanged();
        //qDebug()<<"##########setFLTyreSts!"<<fLTyreSts;
    }
}
void DataObject::setFRTyreSts(const int &fRTyreSts)
{
    if (fRTyreSts != m_FRTyreSts) {
        m_FRTyreSts = fRTyreSts;
        emit fRTyreStsChanged();
        //qDebug()<<"##########setFRTyreSts!"<<fRTyreSts;
    }
}
void DataObject::setRLTyreSts(const int &rLTyreSts)
{
    if (rLTyreSts != m_RLTyreSts) {
        m_RLTyreSts = rLTyreSts;
        emit rLTyreStsChanged();
        //qDebug()<<"##########setRLTyreSts!"<<rLTyreSts;
    }
}
void DataObject::setRRTyreSts(const int &rRTyreSts)
{
    if (rRTyreSts != m_RRTyreSts) {
        m_RRTyreSts = rRTyreSts;
        emit rRTyreStsChanged();
        //qDebug()<<"##########setRRTyreSts!"<<rRTyreSts;
    }
}
void DataObject::setFLPRESSURE(const QString  &fLPRESSURE)
{
    if (fLPRESSURE != m_FLPRESSURE) {
        m_FLPRESSURE = fLPRESSURE;
        emit fLPRESSUREChanged();
        //qDebug()<<"##########setFLPRESSURE!"<<fLPRESSURE;
    }
}
void DataObject::setFRPRESSURE(const QString  &fRPRESSURE)
{
    if (fRPRESSURE != m_FRPRESSURE) {
        m_FRPRESSURE = fRPRESSURE;
        emit fRPRESSUREChanged();
        //qDebug()<<"##########setFRPRESSURE!"<<fRPRESSURE;
    }
}
void DataObject::setRLPRESSURE(const QString  &rLPRESSURE)
{
    if (rLPRESSURE != m_RLPRESSURE) {
        m_RLPRESSURE = rLPRESSURE;
        emit rLPRESSUREChanged();
        //qDebug()<<"##########setRLPRESSURE!"<<rLPRESSURE;
    }
}
void DataObject::setRRPRESSURE(const QString  &rRPRESSURE)
{
    if (rRPRESSURE != m_RRPRESSURE) {
        m_RRPRESSURE = rRPRESSURE;
        emit rRPRESSUREChanged();
        //qDebug()<<"##########setRRPRESSURE!"<<rRPRESSURE;
    }
}
void DataObject::setFLTEMP(const QString  &fLTEMP)
{
    if (fLTEMP != m_FLTEMP) {
        m_FLTEMP = fLTEMP;
        emit fLTEMPChanged();
        //qDebug()<<"##########setFLTEMP!"<<fLTEMP;
    }
}
void DataObject::setFRTEMP(const QString  &fRTEMP)
{
    if (fRTEMP != m_FRTEMP) {
        m_FRTEMP = fRTEMP;
        emit fRTEMPChanged();
        //qDebug()<<"##########setFRTEMP!"<<fRTEMP;
    }
}
void DataObject::setRLTEMP(const QString  &rLTEMP)
{
    if (rLTEMP != m_RLTEMP) {
        m_RLTEMP = rLTEMP;
        emit rLTEMPChanged();
        //qDebug()<<"##########setRLTEMP!"<<rLTEMP;
    }
}
void DataObject::setRRTEMP(const QString  &rRTEMP)
{
    if (rRTEMP != m_RRTEMP) {
        m_RRTEMP = rRTEMP;
        emit rRTEMPChanged();
        //qDebug()<<"##########setRRTEMP!"<<rRTEMP;
    }
}

void DataObject::settyreWarnningLine_FL(const bool   &tyreWarnningLine_FL)
{
    if (tyreWarnningLine_FL != m_tyreWarnningLine_FL) {
        m_tyreWarnningLine_FL = tyreWarnningLine_FL;
        emit tyreWarnningLine_FLChanged();
        //qDebug()<<"##########settyreWarnningLine_FL!"<<tyreWarnningLine_FL;
    }
}
void DataObject::settyreWarnningLine_FR(const bool  &tyreWarnningLine_FR)
{
    if (tyreWarnningLine_FR != m_tyreWarnningLine_FR) {
        m_tyreWarnningLine_FR = tyreWarnningLine_FR;
        emit tyreWarnningLine_FRChanged();
        //qDebug()<<"##########settyreWarnningLine_FR!"<<tyreWarnningLine_FR;
    }
}
void DataObject::settyreWarnningLine_RL(const bool   &tyreWarnningLine_RL)
{
    if (tyreWarnningLine_RL != m_tyreWarnningLine_RL) {
        m_tyreWarnningLine_RL = tyreWarnningLine_RL;
        emit tyreWarnningLine_RLChanged();
        //qDebug()<<"##########settyreWarnningLine_RL!"<<tyreWarnningLine_RL;
    }
}
void DataObject::settyreWarnningLine_RR(const bool    &tyreWarnningLine_RR)
{
    if (tyreWarnningLine_RR != m_tyreWarnningLine_RR) {
        m_tyreWarnningLine_RR = tyreWarnningLine_RR;
        emit tyreWarnningLine_RRChanged();
        //qDebug()<<"##########settyreWarnningLine_RR!"<<tyreWarnningLine_RR;
    }
}
void DataObject::settyreWarnningIcon(const int &tyreWarnningIcon)
{
    if (tyreWarnningIcon != m_tyreWarnningIcon) {
        m_tyreWarnningIcon = tyreWarnningIcon;
        emit tyreWarnningIconChanged();
        //qDebug()<<"##########settyreWarnningIcon!"<<tyreWarnningIcon;
    }
}

void DataObject::settyreUnit(const QString &tyreUnit){
    if(tyreUnit != m_tyreUnit){
        m_tyreUnit = tyreUnit;
        emit tyreUnitChanged();
        //qDebug()<<"##########tyreUnitChanged!"<<tyreUnit;
    }
}

void DataObject::setdisplayFLValue(const QString  &displayFLValue){
    if(displayFLValue != m_DisplayFLValue){
        m_DisplayFLValue = displayFLValue;
        emit displayFLValueChanged();
    }
}

void DataObject::setdisplayFRValue(const QString  &displayFRValue){
    if(displayFRValue != m_DisplayFRValue){
        m_DisplayFRValue = displayFRValue;
        emit displayFRValueChanged();
    }
}

void DataObject::setdisplayRLValue(const QString  &displayRLValue){
    if(displayRLValue != m_DisplayRLValue){
        m_DisplayRLValue = displayRLValue;
        emit displayRLValueChanged();
    }
}

void DataObject::setdisplayRRValue(const QString  &displayRRValue){
    if(displayRRValue != m_DisplayRRValue){
        m_DisplayRRValue = displayRRValue;
        emit displayRRValueChanged();
    }
}

void DataObject::setmainSeat(const bool   &_mainSeat)
{
    if (_mainSeat != m_mainSeat) {
        m_mainSeat = _mainSeat;
        emit mainSeatChanged();
    }
}

void DataObject::setcopilotSeat(const bool   &_copilotSeat)
{
    if (_copilotSeat != m_copilotSeat) {
        m_copilotSeat = _copilotSeat;
        emit copilotSeatChanged();
    }
}

void DataObject::setrearLeftSeat(const bool   &_rearLeftSeat)
{
    if (_rearLeftSeat != m_rearLeftSeat) {
        m_rearLeftSeat = _rearLeftSeat;
        emit rearLeftSeatChanged();
    }
}

void DataObject::setrearMiddleSeat(const bool   &_rearMiddleSeat)
{
    if (_rearMiddleSeat != m_rearMiddleSeat) {
        m_rearMiddleSeat = _rearMiddleSeat;
        emit rearMiddleSeatChanged();
    }
}

void DataObject::setrearRightSeat(const bool   &_rearRightSeat)
{
    if (_rearRightSeat != m_rearRightSeat) {
        m_rearRightSeat = _rearRightSeat;
        emit rearRightSeatChanged();
    }
}
