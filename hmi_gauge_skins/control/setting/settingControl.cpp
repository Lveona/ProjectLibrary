#include "settingControl.h"
#include <QFile>
#include <QMutex>

static _c_MSG_EEPROM_1_msgType _c_MSG_EEPROM_1_msgType_BackUp;


//static int                              ctrlPowerMode             = POWERMODE_D1; // 电源状态
//static int g_uint = UINTMODE_KM;
static int g_version[7] ={0};
static int g_pmState = PM_NOTIFY_MAX;

static bool g_pop_warn = false;
static bool g_tell_warn = false;
static int g_screen_color = -1;
static QString g_current_language = "CN";
static int g_powermode = 0;

static int _setLangugeFlage                       = 0;
static int _setUnitFlage                          = 0;
//仪表休眠唤醒条件确认--D2模式显示需求
static int g_sleep_count = -1;
static int g_displaySpeed = 0;
static int keyNumber = 0;
static int keyStatus = 0;


QList<SettingControl::SettingFunctionParser> SettingControlFunc {
    &SettingControl::func_CARINFO_SCREEN_INDEX,
    &SettingControl::func_HARDKEY_STATUS,
    &SettingControl::func_HARDKEY_NUMBER,
    &SettingControl::func_MSG_EEPROM_1,
    &SettingControl::func_MSG_EEPROM_0
};


SettingControl::SettingControl()
{
    connect(this, &SettingControl::setlan, LangugeManage::instance(), &LangugeManage::setLang, Qt::AutoConnection);
    memset((char *)&_c_MSG_EEPROM_1_msgType_BackUp, 0, sizeof(_c_MSG_EEPROM_1_msgType_BackUp));
    autoCheckTimer = new HMICustomTimer(30);
    connect(autoCheckTimer, &HMICustomTimer::timeout, this, [=](){
        sendToOtherCtrl(HMI_MSGNAME_AUTOCHECK, AUTOCHECK_END);
        sendToOtherProcess(HMI_SHREMEMORY_CMD_AUTOCHECK, AUTOCHECK_END);
    });
    start(QThread::NormalPriority);
}

SettingControl::~SettingControl()
{
    // Nothing
}

void SettingControl::dataChange()
{
    foreach (SettingControl::SettingFunctionParser func, SettingControlFunc) {
        (this->*(func))();
    }
}

void SettingControl::func_MSG_EEPROM_0()
{
    //_c_MSG_EEPROM_0_msgType *msg = (_c_MSG_EEPROM_0_msgType *)data;

    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SETLANGUGE,msg)

    //0x00 chianese
    //0x01 english
    if(0 == msg.value){

        if(g_current_language != "CN"){
            g_current_language = "CN";
            emit setlan("CN");
        }
    }else if(1 == msg.value){

        if(g_current_language != "EN"){
            g_current_language = "EN";
            emit setlan("EN");
        }
    }
}

void SettingControl::func_MSG_EEPROM_1()
{
    //待PF_COMM更新后使用 记得改哦
    //handleTheme(msg->Signals.CFG_Transmission);

    /*示例*/
    //emit sendToOtherCtrl("CFG_EPB", msg->Signals.CFG_EPB);
    //emit sendToOtherProcess("CFG_EPB", msg->Signals.CFG_EPB);
}

//通知manager 存入eep的画面信息（只通知首次）
//eep_2 CLS_LAST_SOURCE_CURRENT_REQ_BAR
void SettingControl::func_CARINFO_SCREEN_INDEX()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CARINFO_SCREEN_INDEX,msg)
    static bool m_init = true;
    if(m_init){
        m_init = false;
        sendToOtherCtrl(HMI_MSGNAME_CARINFOINDEX, (int)msg.value);
    }
}
//mcu_4 MCU_CLUSTER_HARDL_KEY_NUMBER
void SettingControl::func_HARDKEY_NUMBER()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HARDKEY_NUMBER,msg)
    static int keyNumber_BackUp = 0;
    keyNumber = static_cast<int>(msg.value);

    if(keyNumber_BackUp != keyNumber){
        keyNumber_BackUp = keyNumber;
        emit key_pressed_released(keyNumber, keyStatus);
    }
}
//MCU_CLUSTER_HARDL_KEY_STATUS
void SettingControl::func_HARDKEY_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HARDKEY_STATUS,msg)
    static int keyStatus_BackUp = 0;
    keyStatus = static_cast<int>(msg.value);

    if(keyStatus_BackUp != keyStatus){
        keyStatus_BackUp = keyStatus;
        emit key_pressed_released(keyNumber, keyStatus);
    }
}

void SettingControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    if ( HMI_MSGNAME_POWER_MODE == message_key ) {
        g_hmiPowerMode = g_powermode = message_value.toInt();
        handleOffScreenState(HMI_NOTIFY_ALAM);
        if(g_powermode == POWERMODE_D1)
            emit sendToOtherCtrl(HMI_SCREEN_STATE, true);

        else if(g_powermode == POWERMODE_D2){
            emit sendToOtherCtrl(HMI_SCREEN_STATE, true);
            g_sleep_count = 0;
        }
        else{
            emit sendToOtherCtrl(HMI_SCREEN_STATE, false);
            g_sleep_count = -1;
        }
    }
    else if (HMI_MSGNAME_POPWARN == message_key ) {
        g_pop_warn = message_value.toBool();
        g_sleep_count = 0;
        if(g_pop_warn){
            handleOffScreenState(HMI_NOTIFY_ALAM);
        }
    }
    else if (HMI_MSGNAME_TELLWARN == message_key ) {
        g_tell_warn = message_value.toBool();
        g_sleep_count = 0;
        if(g_tell_warn){
            handleOffScreenState(HMI_NOTIFY_ALAM);
        }
    }
    else if(HMI_MSGNAME_SAVEINDEX == message_key)
    {
        savePageToEEP(message_value.toInt()); //将当前画面保存到MCU
    }
    else if(message_key == HMI_MSGNAME_DRIVE_MODE) {
        //1 VCU 来的切换主题
        handleTheme(message_value.toInt());
    }
    else {
        // Nothing
    }
}

void SettingControl::dataSendFromSystemToReceiver(unsigned char attribute_key,unsigned char attribute_value)
{
    if ( POWER_STATE == attribute_key ) {

        if(g_pmState == attribute_value)
        {
            return;
        }else
        {
            g_pmState = attribute_value;
        }

        switch (attribute_value){
        case PM_NOTIFY_ANIMATION:
            LOGPRINT("pm_notify_animation");
            emit sendToOtherCtrl(HMI_MSGNAME_POWER_MODE, POWERMODE_ANIMATION);           // Opening
            //anim
            break;
        case PM_NOTIFY_D1:
            LOGPRINT("pm_notify_PM_NOTIFY_D1");
            PM_proxy_set_info(HMINOTIFY,PM_NOTIFY_D1);
            autoCheckTimer->start();
            emit sendToOtherCtrl(HMI_MSGNAME_AUTOCHECK, AUTOCHECK_START);
            emit sendToOtherProcess(HMI_SHREMEMORY_CMD_AUTOCHECK, AUTOCHECK_START);
            emit sendToOtherCtrl(HMI_MSGNAME_POWER_MODE, PM_NOTIFY_D1);
            //d1
            break;
        case PM_NOTIFY_D2:
            LOGPRINT("pm_notify_PM_NOTIFY_D2");
            PM_proxy_set_info(HMINOTIFY,PM_NOTIFY_D2);
            autoCheckTimer->stop();
            emit sendToOtherCtrl(HMI_MSGNAME_AUTOCHECK, AUTOCHECK_INIT);
            emit sendToOtherProcess(HMI_SHREMEMORY_CMD_AUTOCHECK, AUTOCHECK_INIT);
            emit sendToOtherCtrl(HMI_MSGNAME_POWER_MODE, PM_NOTIFY_D2);
            //d2
            break;
        case PM_NOTIFY_INIT:
            LOGPRINT("pm_notify_PM_NOTIFY_INIT");
            PM_proxy_set_info(HMINOTIFY,HMI_NOTIFY_READY);
            break;
        default:
            break;
        }
    } else {
        // other
    }
}

void SettingControl::get_timeout500ms()
{
}
void SettingControl::get_timeout100ms()
{
    autoCheckTimer->update();
    isInterruptAutoCheck();
    if(g_sleep_count >= 0){
        g_sleep_count++;
        if(g_sleep_count >= 20){
            //暂定2s的信号检测时间
            g_sleep_count = -1;
            if(g_pop_warn || g_tell_warn){
                handleOffScreenState(HMI_NOTIFY_ALAM);
            }
            else{
                if(g_powermode == POWERMODE_D2)
                    handleOffScreenState(HMI_NOTIFY_NORMAL);
            }
        }
    }
}

void SettingControl::handleOffScreenState(pm_hmi_notify_em _enumIndex){
//    LOGPRINT(QString("handleOffScreenState:%1").arg(_enumIndex));
//    PM_proxy_set_info(HMINOTIFY, _enumIndex);
//    emit sendToOtherCtrl(HMI_SCREEN_STATE, QVariant(_enumIndex==HMI_NOTIFY_NORMAL?false:true));
}

void SettingControl::receiveDateFromOtherProcess(QString name, QVariant value)
{
    Q_UNUSED(name)
    Q_UNUSED(value)
    if(name == HMI_SHREMEMORY_CMD_DISPLAY_SPEED)
    {
        g_displaySpeed = value.toInt();
        setPropertyValue(PROPERTYID_SYSTEM_SPEED,g_displaySpeed);
    }
}

/**
 * @brief SettingControl::isInterruptAutoCheck 是否打断自检
 * @param displaySpeed
 * 车速大于2打断自检，最小显示时间0.5s
 */
void SettingControl::isInterruptAutoCheck(){
    if(autoCheckTimer->getTimerCnt() >= -1 && autoCheckTimer->getTimerCnt() < 5){
        return;
    }
    if(g_displaySpeed < 2){
        return;
    }
    autoCheckTimer->stop();
    sendToOtherCtrl(HMI_MSGNAME_AUTOCHECK, AUTOCHECK_END);
    sendToOtherProcess(HMI_SHREMEMORY_CMD_AUTOCHECK, AUTOCHECK_END);

}

void SettingControl::iC_Can_Info_Send(SYSTEM_IC_CAN_INFO_SEND_ID reqSendID)
{
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    //    _buffer.rw	    = 0x01;
    //    _buffer.length  = 0x0020;
    //    _buffer.control = 0x00;
    //    _buffer.opecode = 0x0603;

    switch (reqSendID) {
    case SYSTEM_IC_CAN_INFO_languageSts :        // send languageSts
        _buffer.rw	    = 0x01;
        _buffer.length  = 0x0020;
        _buffer.control = 0x00;
        _buffer.opecode = 0x075A;
        _buffer.data[0] = 0x09;                                                                   // msg id
        _buffer.data[1] = 0x01;                                                                   // msg len
        if (1 == _setLangugeFlage) {
//            _buffer.data[2] = _c_IVI_set_IP_msgType_BackUp.Signals.ivi_languageSet;               // msg coding

        } else if (2 == _setLangugeFlage){
//            if (0x0 == _c_MSG_EEPROM_1_msgType_BackUp.Signals.EE_LANGUAGE && 0x1 == _c_MSG_EEPROM_1_msgType_BackUp.Signals.EE_LANGUAGE) {
                // Nothing
//            } else {
//                _buffer.data[2] = 0xF;                                                            // msg len
//            }
        } else {
            // Nothing
        }
        _setLangugeFlage = 0;
        break;
    case SYSTEM_IC_CAN_INFO_themeSts:            // send themeSts
        _buffer.rw	    = 0x01;
        _buffer.length  = 0x0020;
        _buffer.control = 0x00;
        _buffer.opecode = 0x0603;
        _buffer.data[0] = 0x38;                                                                   // msg id
        _buffer.data[1] = 0x01;                                                                   // msg len
//        if (1 == _setUnitFlage) {
//            _buffer.data[2] = _c_IVI_infoSet_IP_msgType_BackUp.Signals.ivi_themeSet;                  // msg coding
//        } else if (2 == _setUnitFlage) {
//            _buffer.data[2] = 0x7;                  // msg coding
//        } else {
//            // Nothing
//        }
        _setUnitFlage = 0;
        break;
    case SYSTEM_IC_CAN_INFO_SOC:            //SOC
        _buffer.rw	    = 0x01;
        _buffer.length  = 0x0020;
        _buffer.control = 0x00;
        _buffer.opecode = 0x060F;

        _buffer.data[1] = static_cast<unsigned char>(g_version[0]);
        _buffer.data[2] = static_cast<unsigned char>(g_version[1]);
        _buffer.data[3] = static_cast<unsigned char>(g_version[2]);
        _buffer.data[4] = static_cast<unsigned char>(g_version[3]);
        _buffer.data[5] = static_cast<unsigned char>(g_version[4]);
        _buffer.data[6] = static_cast<unsigned char>(g_version[5]);
        _buffer.data[7] = static_cast<unsigned char>(g_version[6]);

        qWarning()<<"SOC revision has been send";
        break;

    case SYSTEM_IC_CAN_INFO_uint:
//        _buffer.rw	    = 0x01;
//        _buffer.length  = 0x0020;
//        _buffer.control = 0x00;
//        _buffer.opecode = 0x0603;
//        _buffer.data[0] = 0x39;                                                                   // msg id
//        _buffer.data[1] = 0x01;
//        if(UINTMODE_KM ==g_uint){
//            _buffer.data[2] = 0x00;
//        }else if(UINTMODE_MILE ==g_uint){
//            _buffer.data[2] = 0x01;
//        }
//         qWarning()<<"uint 3 ===================================== _Msg->Signals.EE_UNIT"<<g_uint;                                                                    // msg len
        break;
    case SYSTEM_IC_CAN_INFO_SCREEN:
        _buffer.rw	    = 0x01;
        _buffer.length  = 0x0020;
        _buffer.control = 0x00;
        _buffer.opecode = 0x0603;
        _buffer.data[0] = 0x44;                                                                   // msg id
        _buffer.data[1] = 0x01;
        _buffer.data[2] = g_screen_color<<1 | 1;                                                                      // msg len
        break;
    default:
        return;
    }
    ivs_client_send_request(&_buffer, pUser_data);

}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleEEPROM
 *  Description:  处理eeprom数据,分发给其他模块
 *	Return:
 *          none: none
 *  Param:
            name: name
            value1: value1
            value2: value2
 * =====================================================================================
 */
void SettingControl::handleEEPROM(QString name, int value1, int value2)
{
    if(value1 != value2)
    {
        emit sendToOtherCtrl(name, value1);
    }
}

void SettingControl::savePageToEEP(int leftScreen)
{
    static int _leftScreen = 0;

    if((_leftScreen == leftScreen)){
        return;
    }

    _leftScreen = leftScreen;

    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0603;

    _buffer.data[0] = 0xD0;                                 // msg_id
    _buffer.data[1] = 0x02;                                 // msg len
    _buffer.data[2] = _leftScreen+1;          // 行车电脑画面index

    LOGPRINTVALUE("savePageToEEP", _leftScreen+1);
    ivs_client_send_request(&_buffer, pUser_data);
}

void SettingControl::handleTheme(int theme)
{
    //2 容错 非有效值或者使用上一次同步状态就不发生改变
    if(theme <= THEMEMODE_NONE  || theme >= THEMEMODE_MAX) {
        return ;
    }
    //EEP 保存过滤 要求不能频繁保存 等待EEP 保存

    setPropertyValue(PROPERTYID_SYSTEM_THEME_SETTING,theme);
    sendToOtherCtrl(HMI_MSGNAME_THEME, theme);
    emit sendToOtherProcess(HMI_SHREMEMORY_CMD_THEMESETTING,theme);
}
