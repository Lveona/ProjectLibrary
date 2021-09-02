#include "settingScreen.h"
#include <QTimer>

//static CTRLDataParser ctrlParses[] {
////    {PROPERTYID_HOME_TEMP, setTemp },
//};

SettingScreen::SettingScreen()
{

    m_controlScreenState            = false;
    m_controlScreenColor            = 0;
    m_themeSetting = COMFORT; //默认舒适主题
    m_outAnimationState = false;
    qmlRegisterType<SettingScreen>("qmlEnums", 1, 0, "SettingScreenEnums");
    m_currentPage = 0;
    m_vehicleSpeed = 0;
}


SettingScreen::~SettingScreen()
{
    // Nothing
}

static QMap< quint32, SettingScreen::FunctionParser > tableScreen_Setting = {
    {PROPERTYID_SYSTEM_SCREEN_STATE, &SettingScreen::setControlScreenState },
    {PROPERTYID_SYSTEM_SCREEN_COLOR, &SettingScreen::setControlScreenColor },
    {PROPERTYID_SYSTEM_THEME_SETTING,&SettingScreen::setThemeSetting},
    {PROPERTYID_SYSTEM_SPEED,&SettingScreen::setVehicleSpeed}
};

void SettingScreen::createCtrl(QQuickView *view)
{
    // First entry[1]
//    qInfo()<<"SettingScreen"<<QThread::currentThread();
    createAppControl(view->rootContext(), "SettingScreen");
    view->rootContext()->setContextProperty("LangugeManage", LangugeManage::instance());

//    // registe
//    PM_proxy_init();
//    PM_proxy_register_callback(PowerState, send_Msg_receiver, nullptr);
}

void SettingScreen::startControl()
{
    // Second entry[2]
    qRegisterMetaType<PROPERTYID_SYSTEM>("PROPERTYID_SYSTEM");
//    qRegisterMetaType<Type_uDWord>("Type_uDWord");

    connect(SettingControl::instance(), SIGNAL(PropertyChange(int , QVariant)), this, SLOT(SetProperty(int , QVariant)), Qt::QueuedConnection);

//    connect(this, &SettingScreen::sendTheme, SettingControl::instance(), &SettingControl::sendTheme, Qt::QueuedConnection);
    //    connect(this, &SettingScreen::sendIsHide, SettingControl::instance(), &SettingControl::sendIsHide, Qt::QueuedConnection);
}

void SettingScreen::SetProperty(int name, QVariant value)
{
    if(tableScreen_Setting.value(name))
    {
        (this->*(tableScreen_Setting.value(name)))(value);
    }
}

