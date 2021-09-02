#include "manager.h"
#include "mysharememory.h"
#include <QTimer>
#include "worker.h"
#include "parsingData.h"
#ifdef DESKTOP
#else
#include "pm_proxy.h"
#endif

static bool notify_started = false;
static bool g_isDiagnoseScreen = false;
static bool g_isUpdateScreen = false;
static bool g_isDiagScreen = false;
static bool g_isD2OffScreen = false;
//static int g_lastADASWaringScreenIndex = 2;   //adas报警时记录上一次中间位置画面
//static int g_lastMidAreaScreenIndex = 2;      //记录中间区域画面切换时上一次画面，用于区别是否与当前画面一致。如不一致则通知muc保存当前画面
//static int g_lastCarInforScreenIndex = 0;     //记录行车电脑画面切换时上一次画面，用于区别是否与当前画面一致。如不一致则通知muc保存当前画面
static int g_vehicleSpeed = 0;      //车速
//static int g_diagPassWord = 0;      //记录按键，判断是否满足进入电检画面条件
static int g_account = -1;//初始化ivs...
static int autoCheckState = AUTOCHECK_INIT;

void Manager::startControl()
{

    //connect lib to ohter lib

    //connect Control to other process
    //connect share memory to reveivelib
    connect(_MyShareMemory, &MyShareMemory::receiveDateFromOtherProcess, this, &Manager::receiveDateFromOtherProcess, Qt::AutoConnection);
    connect(_TelltalesControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrlP(QString,QVariant)),  Qt::AutoConnection);
    connect(_GaugeControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrlP(QString,QVariant)),  Qt::AutoConnection);
    connect(_GaugeControl, &GaugeControl::sendToOtherProcess, this, &Manager::sendToOtherProcessP, Qt::AutoConnection);
    connect(_TelltalesControl, &GaugeControl::sendToOtherProcess, this, &Manager::sendToOtherProcessP, Qt::AutoConnection);
    m_worker = new Worker();
    //timer connect ReceiverLib to other
    connect(m_worker, &Worker::notify500ms, this, &Manager::get_timeout500ms, Qt::AutoConnection);
    connect(m_worker, &Worker::notify100ms, this, &Manager::get_timeout100ms, Qt::DirectConnection);
    connect(m_worker, &Worker::notify10ms, this, &Manager::get_timeout10ms, Qt::AutoConnection);
    m_worker->start(QThread::NormalPriority);

    //connect other process to other Control
    connect(this, SIGNAL(receiveDateFromOtherProcessSignal(QString, QVariant)), _TelltalesControl, SLOT(receiveDateFromOtherProcess(QString, QVariant)), Qt::AutoConnection);
    connect(this, SIGNAL(receiveDateFromOtherProcessSignal(QString, QVariant)), _GaugeControl, SLOT(receiveDateFromOtherProcess(QString, QVariant)), Qt::AutoConnection);

    //create shareMemory
    _MyShareMemory->setSendKeyA("Cluster_HMI_Second");
    _MyShareMemory->setSendKeyB("Cluster_HMI_First");
}

void Manager::sendToOtherProcessP(QString name, QVariant value)
{
    _MyShareMemory->sendData(name, value);
}
//[0]
Manager::Manager()
    :m_receiveCtrlPowerMode(static_cast<int>(POWERMODE_D3))
    ,m_digitSpeedValue(0)
    ,m_hmiVisible(true)
    ,m_rotationSpeedWarning(false)
    ,m_hmiScreenState(true)
    ,m_enterAnimStart(false)
    ,m_isLoaderOver(false)
    ,m_isCharging(false)
    ,m_navigationMapMod(SMALL_MAP)
    ,m_themeSetting(COMFORT)
{
    g_loaderOver = false;
//    acTimer = new HMICustomTimer(6);
//    connect(acTimer, &HMICustomTimer::timeout, this, [=](){
//        sendToOtherCtrlP(HMI_MSGNAME_ATCHECK_STATE, AUTOCHECK_END);
//    });
    _TelltalesControl = TelltalesControl::instance();
    _GaugeControl = GaugeControl::instance();
    _MyShareMemory = MyShareMemory::instance();
}

Manager::~Manager()
{
    m_worker->quit();
    m_worker->wait(500);
    delete m_worker;
    delete _MyShareMemory;
}

void Manager::sendToOtherCtrlP(QString message_key, QVariant message_value)

{
    _TelltalesControl->getFromOtherCtrl(message_key, message_value);
    _GaugeControl->getFromOtherCtrl(message_key, message_value);

    if(HMI_SCREEN_STATE == message_key){
        setHmiScreenState(message_value.toBool());
        sendToOtherProcessP(HMI_SHREMEMORY_CMD_HMI_SCREEN_STATE, message_value);
    }
    else if(HMI_MSGNAME_VEHICLESPEED == message_key)
    {
        if(0xFFFF == message_value.toInt()){
            g_vehicleSpeed = 0;
        }
        else{
            g_vehicleSpeed = message_value.toInt();
        }
    }
    else {
        // Nothing
    }
}

//void Manager::handleAutoCheck()
//{
//    if(g_loaderOver){
//        if(g_hmiPowerMode == POWERMODE_D1){
//            autoCheckState = AUTOCHECK_START;
//            acTimer->start();
//        }else{
//            acTimer->stop();
//            autoCheckState = AUTOCHECK_INIT;
//        }
//    }
//    sendToOtherCtrlP(HMI_MSGNAME_ATCHECK_STATE, autoCheckState);
//}


void Manager::createCtrl(QQuickView *view)
{
    LOGPRINT("Manager::createCtrl");
    static HMIAudioCtrl hmiAudioCtrl;
    (void)hmiAudioCtrl;

    GaugeScreen::instance()->createCtrl(view);
    TelltalesScreen::instance()->createCtrl(view);

    createAppControl(view->rootContext(),"Manager");
    m_view = view;


    qInfo()<<"point:createCtrl finsh";

    g_account = 0;
}

void Manager::qmlPrintLog(QString log)
{
    LOGPRINT(log.toUtf8().data());
}

void Manager::qmlPrintValueLog(QString key,QString value)
{
    LOGPRINTVALUE(key.toUtf8().data(),value.toUtf8().data());
}


void Manager::get_timeout10ms()
{
    _TelltalesControl->get_timeout10ms();
}

void Manager::get_timeout100ms()
{
    _TelltalesControl->get_timeout100ms();
    if(g_account>=0){
        //init，防止阻塞总线程
        g_account = -1;
        //注册Ivs
        ParsingData::instance()->RegistIVSMsg();

        if(0 != audio_client_Init()){
            qWarning()<<"audio_CONNECT_NG";
        }

    }
}

void Manager::get_timeout500ms()
{

    if(notify_started){
        notify_cluster_manager("wd");
    }
    _TelltalesControl->get_timeout500ms();
    _GaugeControl->get_timeout500ms();
//    acTimer->update();
}

void Manager::receiveDateFromOtherProcess(QString data)
{
    if(!data.contains("&")) return;

    QStringList list = data.remove(data.length()-1,1).split("&");

    foreach(QString str, list)
    {
        if(str.isEmpty()) continue;
        QStringList strlist = str.split(":");
        if(strlist.length() != 2) continue;

        emit receiveDateFromOtherProcessSignal(strlist.at(0), strlist.at(1));

        selfReceiveDateFromOtherProcessSignal(strlist.at(0), strlist.at(1));
    }
}

void Manager::notify_cluster_manager(QString state)
{
    Q_UNUSED(state)
#ifdef DESKTOP
#else
    if(state == "start")
    {
        PM_proxy_set_info(HMINOTIFY, HMI_NOTIFY_READY);
        LOGPRINT("point notify_cluster_manager=start");
        notify_started = true;
//        libclsmgr_notify((char*)CLS_MGR_HMI_POINT_NAME, (int)clsmgr_notify_started);
    }
    else{
//        libclsmgr_notify((char*)CLS_MGR_HMI_POINT_NAME, (int)clsmgr_notify_wd);
    }
#endif
}

void Manager::selfReceiveDateFromOtherProcessSignal(QString name, QVariant value)
{
//    qInfo()<<"__FUNCTION__"<<name<<value;
    if(HMI_SHREMEMORY_CMD_AUTOCHECK == name){
        sendToOtherCtrlP(HMI_MSGNAME_ATCHECK_STATE, value.toInt());
    }
    else if(name == HMI_SHREMEMORY_CMD_DISPLAY_SPEED){
        setdigitSpeedValue(value.toDouble());
    }
    else if(name == HMI_SHREMEMORY_CMD_DIAGNOSE_SCREEN){
        //诊断屏幕颜色
        g_isDiagnoseScreen = value.toBool();
        updatePointScreen();
    }
    else if(name == HMI_SHREMEMORY_CMD_POINTSIDP_CTRL_UPDATE){
        g_isUpdateScreen = value.toBool();
        updatePointScreen();
    }
    else if(name == HMI_SHREMEMORY_CMD_POWER_MODE){
        g_hmiPowerMode = value.toInt();
        setReceiveCtrlPowerMode(value.toInt());
//        // 自检
//        handleAutoCheck();
    }
    else if(name == HMI_SHREMEMORY_CMD_HMI_SCREEN_STATE){//D2模式两秒无报警后隐藏point
        g_isD2OffScreen = !(value.toBool());
        updatePointScreen();
    }
    else if(name == HMI_SHREMEMORY_CMD_POINTSIDP_ENTERANIM){
        setEnterAnimStart(value.toBool());
    }
    else if(name == HMI_SHREMEMORY_CMD_HMI_SCREEN_DIAG){//进入电检画面后隐藏point
        g_isDiagScreen = value.toBool();
        updatePointScreen();
    }
    else if(name == HMI_SHREMEMORY_CMD_CHARGING){
        setIsCharging(value.toBool());
    }
    else if (name == HMI_SHREMEMORY_CMD_NAVMAPMOD) {
        this->setNavigationMapMod(value.toInt());
    } else if(name == HMI_SHREMEMORY_CMD_THEMESETTING) {
        this->setThemeSetting(value.toInt());
    }
}

void Manager::updatePointScreen()
{
    if(g_isUpdateScreen || g_isDiagScreen || g_isD2OffScreen || g_isDiagnoseScreen)    //升级过程中已隐藏point，无需二次处理
    {
        setHmiVisible(false);
    }
    else{
        setHmiVisible(true);
    }
}
