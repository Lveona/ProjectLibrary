#include "manager.h"
#include "mysharememory.h"
#include <QTimer>
#include "worker.h"
#include "parsingData.h"

#include "../popup/popupScreen.h"
#include "../popup/popupControl.h"
#include "../diag/diagScreen.h"
#include "../adas/adasScreen.h"
#include "../carInfo/carInfoScreen.h"
#include "../setting/settingScreen.h"
#include "../interconnect/InterconnectScreen.h"
#include "../home/HomeScreen.h"
#include "../updateControl/update_thread.h"

static QMatrix4x4 projectMatrix;
static QMatrix4x4 modelviewMatrix;

static bool notify_started = false;
//static bool updateInit = false;
//static bool isWarningState = false;     //pop 优先 行车电脑 显示
//static int isCarInfoScreenIndex = 0;  //0:行车电脑画面, 1:故障查询画面
//0:瞬时油耗, 1:续航里程, 2:自启动后信息, 3:自复位后信息,
//4:剩余保养里程, 5:故障查询
static int isCarInfoChildMax = 6;
//static int isCarInfoChildDirection = 1;   //行车电脑列表上下移动方向, 1 下, -1 上
//static int isCarInfoFaultChildIndex = 0; //0:返回,1-n:报警信息
//static int carInfoFaultCount = 0;       //报警数量

//static int isMidAreaScreenIndex = 0;   //0:车状态画面,1:navi,2:adas,3:tyre
static int g_lastADASWaringScreenIndex = 2;   //adas报警时记录上一次中间位置画面
//static int g_lastMidAreaScreenIndex = 2;      //记录中间区域画面切换时上一次画面，用于区别是否与当前画面一致。如不一致则通知muc保存当前画面
//static int g_lastCarInforScreenIndex = 0;     //记录行车电脑画面切换时上一次画面，用于区别是否与当前画面一致。如不一致则通知muc保存当前画面
static int g_vehicleSpeed = 0;      //车速
static int g_diagPassWord = 0;      //记录按键，判断是否满足进入电检画面条件

//static bool g_isLCDUpdateExist = false;
//static bool g_isUpdateExist = false;
static bool isNaviExist = false;
static bool isTyreExist = true;

static bool g_midAreaScreenSwitchTimer = false;     //设置flag，主动切换画面1s内adas报警不做画面跳转

static int g_remaining_odo_timer_count = -1;
static int g_remaining_odo_ok_count = 0;
static int g_account = -1;//初始化ivs...

static int cardNum = 1; //正常是3 胎压、行车电脑、小计里程，此版都不组
int gCurrentCarInfoIndex = 0;
QString readFile(QString path)
{
    QString dataTemp;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        dataTemp = "";
        return dataTemp;
    }
    dataTemp = QString(file.readAll());
    file.close();
    return dataTemp;
}


static void display_Msg_CallbackFunc_PM(unsigned char attribute_key,unsigned char attribute_value,void *puser_data) {
    Q_UNUSED(puser_data);
    SettingControl::instance()->dataSendFromSystemToReceiver(attribute_key,attribute_value);
}

static void display_Interconnect(ivp_callback_id message_id,  void *pData)
{
    InterconnectControl::instance()->handleIVPData(message_id, pData);

}

/*ivp注册信号*/
static ivp_callback_id idListMedia[] {
    //phone
    IVP_CB_ID_PHONE_INFO,
    IVP_CB_ID_CALLS_INFO,
    IVP_CB_ID_COLLECS_INFO,
    IVP_CB_ID_IMAGE_INFO,
    IVP_CB_ID_VOLUME_INFO,
    IVP_CB_ID_NAVI_INFO, //导航互联
    IVP_CB_ID_SOURCE_INFO   //多媒体

};


void Manager::startControl()
{
    //create shareMemory
    _MyShareMemory->setSendKeyA("Cluster_HMI_First");
    _MyShareMemory->setSendKeyB("Cluster_HMI_Second");
    connect(_PopupControl, &PopupControl::notifyWarningState, this, &Manager::notifyWarningState, Qt::AutoConnection);

    //connect lib to ohter lib
    connect(_ADASControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    connect(_CarInfoControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    connect(_SettingControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    //    connect(_TelltalesControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    //    connect(_GaugeControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    connect(_PopupControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    connect(_InterconnectControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    connect(_DiagControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);
    connect(_HomeControl, SIGNAL(sendToOtherCtrl(QString,QVariant)), this, SLOT(sendToOtherCtrl(QString,QVariant)),  Qt::AutoConnection);

    //connect sys to Manager
    connect(_SettingControl, &SettingControl::key_pressed_released, this, &Manager::key_pressed_released, Qt::QueuedConnection);

    //connect Control to other process
    connect(_InterconnectControl, &InterconnectControl::sendToOtherProcess, this, &Manager::sendToOtherProcess, Qt::AutoConnection);
    connect(_SettingControl, &SettingControl::sendToOtherProcess, this, &Manager::sendToOtherProcess, Qt::AutoConnection);
    connect(_PopupControl, &PopupControl::sendToOtherProcess, this, &Manager::sendToOtherProcess, Qt::AutoConnection);
    connect(_HomeControl, &PopupControl::sendToOtherProcess, this, &Manager::sendToOtherProcess, Qt::AutoConnection);

    //connect other process to other Control
    connect(this, SIGNAL(receiveDateFromOtherProcessSignal(QString, QVariant)), _PopupControl, SLOT(receiveDateFromOtherProcess(QString, QVariant)), Qt::AutoConnection);
    connect(this, SIGNAL(receiveDateFromOtherProcessSignal(QString, QVariant)), _SettingControl, SLOT(receiveDateFromOtherProcess(QString, QVariant)), Qt::AutoConnection);

    //connect share memory to reveivelib
    connect(_MyShareMemory, &MyShareMemory::receiveDateFromOtherProcess, this, &Manager::receiveDateFromOtherProcess, Qt::AutoConnection);

    m_worker = new Worker();
    //timer connect ReceiverLib to other
    connect(m_worker, &Worker::notify500ms, this, &Manager::get_timeout500ms, Qt::AutoConnection);
    connect(m_worker, &Worker::notify100ms, this, &Manager::get_timeout100ms, Qt::DirectConnection);
    connect(m_worker, &Worker::notify250ms, this, &Manager::get_timeout250ms, Qt::AutoConnection);
    //    connect(m_worker, &Worker::notify10ms, this, &Manager::get_timeout10ms, Qt::AutoConnection);
    m_worker->start(QThread::NormalPriority);

    connect(_ADASControl, &ADASControl::notifyADASWaring, this, &Manager::notifyADASWaring, Qt::AutoConnection);
    //    connect(_TelltalesControl, &TelltalesControl::notifyADASWaring, this, &Manager::notifyADASWaring, Qt::AutoConnection);
    connect(_DiagScreen, &DiagScreen::exitDiagScreen, this, &Manager::exitDiagScreen, Qt::AutoConnection);


}

Manager::Manager()
    :m_receiveCtrlPowerMode(static_cast<int>(POWERMODE_D3)) //POWERMODE_D3
    //参考静态变量声明
    ,m_isCarInfoChildIndex(0)
    ,m_isCarInfoScreenIndex(0)
    ,m_isCarInfoChildDirection(1)
    ,m_isCarInfoFaultChildIndex(0)
    ,m_isWarningState(false)
    ,m_updateScreenVisible(false)
    ,m_isMidAreaScreenIndex(2)  //等车状态对应了初始化0
    ,m_hmiScreenState(true)
    ,m_enterAnimStart(false)
    ,m_edition(0)
    ,m_isCarInfoFaultChildDirect(0)
    ,m_currentIndex(0)
    ,m_maxPage(0)
{
    //    qDebug()<<"Manager::Manager()"<<QThread::currentThreadId()<<QThread::currentThread();
    m_view = NULL;

    _ADASControl = ADASControl::instance();
    _CarInfoControl = CarInfoControl::instance();
    _SettingControl = SettingControl::instance();
    _DiagControl = DiagControl::instance();
    _DiagScreen = DiagScreen::instance();
    _InterconnectControl = InterconnectControl::instance();

    _HomeControl = HomeControl::instance();
    _PopupControl = PopupControl::instance();

    _MyShareMemory = MyShareMemory::instance();

    m_adasWaringTimer = new HMICustomTimer(30);     //新建一个timer，用于adas报警时画面跳转到adas3s后回到报警之前画面
    connect(m_adasWaringTimer, &HMICustomTimer::timeout, this, [=](){
        setIsMidAreaScreenIndex(g_lastADASWaringScreenIndex);
    });

    m_midAreaScreenSwitchTimer = new HMICustomTimer(10);    //新建一个timer，用于主动切换画面1s内adas报警不做画面跳转
    connect(m_midAreaScreenSwitchTimer, &HMICustomTimer::timeout, this, [=](){
        g_midAreaScreenSwitchTimer = false;
    });

    volumeTimer = new HMICustomTimer(2, false);
    volumeTimer->start();
    connect(volumeTimer, &HMICustomTimer::timeout, this, [=](){
#ifdef DESKTOP
//        testVolumeInfo();
#endif
    });
}

Manager::~Manager()
{
    m_worker->quit();
    m_worker->wait(500);
    delete m_worker;
    delete _MyShareMemory;
}

void Manager::createCtrl(QQuickView *view)
{
    LOGPRINT("Manager::createCtrl");
    static HMIAudioCtrl hmiAudioCtrl;
    (void)hmiAudioCtrl;
    ADASScreen::instance()->createCtrl(view);
    CarInfoScreen::instance()->createCtrl(view);
    InterconnectScreen::instance()->createCtrl(view);
    PopupScreen::instance()->createCtrl(view);
    DiagScreen::instance()->createCtrl(view);
    HomeScreen::instance()->createCtrl(view);
    SettingScreen::instance()->createCtrl(view);

    createAppControl(view->rootContext(),"Manager");

    m_view = view;

    view->rootContext()->setContextProperty("Update_Thread", &(Update_Thread::instance()));

    g_account = 0;

    projectMatrix.setToIdentity();
    modelviewMatrix.setToIdentity();

    changeProjectMatrix(90, 18);

    changeModelviewMatrixTranslate(-300, -55.0, 0.0);
    changeModelviewMatrixRotate(-69);
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
}

void Manager::get_timeout100ms()
{

    if(g_account>=0){
        //1 Manager 启动
        ParsingData::instance()->RegistIVSMsg();

        //init，防止阻塞总线程
        g_account = -1;


        if(0 != audio_client_Init()){
            qWarning()<<"audio_CONNECT_NG";
        }

        //powermanager
        PM_proxy_init();
        PM_proxy_register_callback(HMINOTIFY, display_Msg_CallbackFunc_PM, 0);
        PM_proxy_set_info(HMINOTIFY, HMI_NOTIFY_READY);

        //Interconnect
        libivp_connect();

        int lenMedia = sizeof(idListMedia)/sizeof(ivp_callback_id);
        for(int i=0; i<lenMedia; i++) {
            libivp_Set_callback(idListMedia[i], display_Interconnect);
        }
        requstAllEEPROMDATAon1stPowerUp();
    }

    _SettingControl->get_timeout100ms();
    _PopupControl->get_timeout100ms();
    _InterconnectControl->get_timeout100ms();

    m_adasWaringTimer->update();
    m_midAreaScreenSwitchTimer->update();
}

void Manager::get_timeout500ms()
{
    if(notify_started){
        notify_cluster_manager("wd");
    }
    _ADASControl->get_timeout500ms();
    _CarInfoControl->get_timeout500ms();
    _SettingControl->get_timeout500ms();
    _DiagControl->get_timeout500ms();

    _InterconnectControl->get_timeout500ms();
    _PopupControl->get_timeout500ms();
    volumeTimer->update();
}

void Manager::get_timeout250ms()
{
    _ADASControl->get_timeout250ms();
}

void Manager::sendToOtherCtrl(QString message_key, QVariant message_value)
{

    _ADASControl->getFromOtherCtrl(message_key, message_value);
    _CarInfoControl->getFromOtherCtrl(message_key, message_value);
    _SettingControl->getFromOtherCtrl(message_key, message_value);
    _PopupControl->getFromOtherCtrl(message_key, message_value);
    _InterconnectControl->getFromOtherCtrl(message_key, message_value);
    _DiagControl->getFromOtherCtrl(message_key, message_value);
    _HomeControl->getFromOtherCtrl(message_key, message_value);

    if ( HMI_MSGNAME_POWER_MODE == message_key ) {
        setReceiveCtrlPowerMode(message_value.toInt());//用于qml,有anim,D1/D2
        sendToOtherProcess(HMI_SHREMEMORY_CMD_POWER_MODE, message_value.toInt());
    }
    else if(HMI_SCREEN_STATE == message_key){
        setHmiScreenState(message_value.toBool());
        sendToOtherProcess(HMI_SHREMEMORY_CMD_HMI_SCREEN_STATE, message_value);
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

void Manager::sendToOtherProcess(QString name, QVariant value)
{
    _MyShareMemory->sendData(name, value);
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
    }
}

void Manager::notify_cluster_manager(QString state)
{
    Q_UNUSED(state)
#ifdef DESKTOP
#else
    if(state == "start")
    {
        //PM_proxy_set_info(HMINOTIFY, HMI_NOTIFY_READY);
        LOGPRINT("gauge notify_cluster_manager=start");
        notify_started = true;
       // libclsmgr_notify((char*)CLS_MGR_HMI_GAUGE_NAME, (int)clsmgr_notify_started);
    }
    else{
        //libclsmgr_notify((char*)CLS_MGR_HMI_GAUGE_NAME, (int)clsmgr_notify_wd);
    }
#endif
}

/*按键逻辑在这里处理, 按键逻辑导致的画面切换也在这处理*/
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  key_pressed_released
 *  Description:  按键逻辑处理
 *	Return:
 *          none: none
 *  Param:
            key:      key_number
            type:     Key_state
 * =====================================================================================
 */
key_number key;
Key_state type;
void Manager::key_pressed_released(int _key, int _type)
{
    key = static_cast<key_number>(_key);
    type = static_cast<Key_state>(_type);
    //开机动画播放过程中不响应按键操作。
    if(m_receiveCtrlPowerMode != static_cast<int>(POWERMODE_D1))
    {
        return;
    }

    if(DiagScreen::instance()->diag_key_pressed_released(key,type))
    {
        return;
    }
    //判断是否满足进入电检
    if(DiagScreen::instance()->canEnterDiagScreen(key, type)){
        LOGPRINT("ENTER DIAG");
        return;
    }
    if(_PopupControl->triggerHardKey(key, type)){
        return;
    }
    if(_CarInfoControl->triggerHardKey(key, type)){
        return;
    }
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  notifyMCUCurrentPage
 *  Description:  将当前画面保存到MCU
 *	Return:
 *          none: none
 *  Param:
 *          none: none
 * =====================================================================================
 */
//void Manager::notifyMCUCurrentPage(){
//    int notifyIndex = (m_isCarInfoChildIndex + 1) - cardlist.length() > 0 ? cardlist.length() : m_isCarInfoChildIndex;
//    _SettingControl->savePageToEEP(notifyIndex);
//}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  notifyWarningState
 *  Description:  是否有报警信息
 *	Return:
 *          none: none
 *  Param:
            state:      true/false
 * =====================================================================================
 */
void Manager::notifyWarningState(bool state)
{
    setIsWarningState(state);
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleRemainingMaintenanceMileage
 *  Description:  通知mcu清除 剩余保养里程
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void Manager::handleRemainingMaintenanceMileage()
{
    if(g_remaining_odo_ok_count >= 5 && g_remaining_odo_timer_count <=30){
        g_remaining_odo_ok_count = 0;       //clear ok count
        g_remaining_odo_timer_count = -1;   //stop timer
    }
    else{
        //可能是3到了,ok次数不够5,来源定时器触发
        return;
    }

    LOGPRINT("-----------send to mcu handleRemainingMaintenanceMileage-----------");
    //通知mcu清除 剩余保养里程
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0601;

    _buffer.data[0] = 0x80;
    ivs_client_send_request(&_buffer, pUser_data);
}


void Manager::requstAllEEPROMDATAon1stPowerUp(void){
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0605;
    ivs_client_send_request(&_buffer, pUser_data);
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  notifyADASWaring
 *  Description:  非adas界面，adas报警需跳转到adas界面3s，然后回到之前界面
 *	Return:
 *          none: none
 *  Param:
            state:      true/false
 * =====================================================================================
 */
void Manager::notifyADASWaring()
{
    if(g_midAreaScreenSwitchTimer == true)  //主动切换画面1s内adas报警不做画面跳转
    {
        return;
    }
    if(isMidAreaScreenIndex() != MIDAREASCREENINDEX_ADAS)
    {
        setIsMidAreaScreenIndex(MIDAREASCREENINDEX_ADAS);
    }
    m_adasWaringTimer->reset();
}

void Manager::exitDiagScreen()
{
    sendToOtherProcess(HMI_SHREMEMORY_CMD_HMI_SCREEN_DIAG, DiagScreen::instance()->getIsDiagScreen());
}

void Manager::setUpdateScreenVisible(bool updateScreenVisible)
{
    if (m_updateScreenVisible == updateScreenVisible)
        return;

    m_updateScreenVisible = updateScreenVisible;
    emit updateScreenVisibleChanged(m_updateScreenVisible);

    sendToOtherProcess(HMI_SHREMEMORY_CMD_POINTSIDP_CTRL_UPDATE, QVariant(m_updateScreenVisible));
}

void Manager::setEnterAnimStart(bool enterAnimStart)
{
    if (m_enterAnimStart == enterAnimStart)
        return;

    m_enterAnimStart = enterAnimStart;
    emit enterAnimStartChanged(m_enterAnimStart);
    qInfo()<<"HMI_SHREMEMORY_CMD_POINTSIDP_ENTERANIM"<<m_enterAnimStart;
    sendToOtherProcess(HMI_SHREMEMORY_CMD_POINTSIDP_ENTERANIM, m_enterAnimStart);
}

void Manager::changeProjectMatrix(float angle, float ratio)
{
    projectMatrix.setToIdentity();
    projectMatrix.perspective(angle, ratio, 1., 10000.);     //缩放

    m_view->rootContext()->setContextProperty("projectMatrix", QVariant(projectMatrix));
}

static float modex=0;
static float modey=0;
static float modez=0;
static float modeangle=0;

void Manager::changeModelviewMatrixTranslate(float x, float y, float z)
{
    modelviewMatrix.setToIdentity();
    modelviewMatrix.translate(x,y,z);   //车道线平移:x/y/z轴
    modex=x;
    modey=y;
    modez=z;
    modelviewMatrix.rotate(modeangle, 1.0, 0.0, 0.0);
    m_view->rootContext()->setContextProperty("modelviewMatrix", QVariant(modelviewMatrix));
}

void Manager::changeModelviewMatrixRotate(float angle)
{
    //-80,1.0, 0.0, 0.0
    modeangle = angle;
    modelviewMatrix.setToIdentity();
    modelviewMatrix.translate(modex,modey,modez);   //车道线平移:x/y/z轴
    modelviewMatrix.rotate(angle, 1.0, 0.0, 0.0);
    m_view->rootContext()->setContextProperty("modelviewMatrix", QVariant(modelviewMatrix));
}

#ifdef DESKTOP
static void* volume_info = new IVP_volume;
static IVP_volume _IVP_volume_info;
void Manager::testVolumeInfo()
{
    memset((&_IVP_volume_info), 0, sizeof(IVP_volume));
    _IVP_volume_info.currentValue = 20;
    _IVP_volume_info.maxValue = 30;
    memmove(volume_info, &_IVP_volume_info, sizeof(IVP_volume));
    display_Interconnect(IVP_CB_ID_VOLUME_INFO, volume_info);
}
#endif
