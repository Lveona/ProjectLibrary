#include "diagControl.h"
//#define INEOS_ON
#include <QMutex>

// TODO 初始化的值需要再确认

static QString g_softVersionNum = "";
static QString g_hardVersionNum = "";
static int g_powermode = 0;

static _c_MSG_EEPROM_4_msgType      _c_MSG_EEPROM_4_msgType_BackUp={{0}};
static int global_clearTimes = 0;
static QMap<RpcMsgValueId, DiagControl::DiagFunctionParser> DiagControlFunc =
{
    {MSG_ODO_CLEAR_TIME,     &DiagControl::func_ODO_CLEAR_TIME},
};

QList<DiagControl::DiagFunctionParser> DiagVoidControlFunc {
    &DiagControl::func_ODO_CLEAR_TIME
};

DiagControl::DiagControl()
{
    start(QThread::NormalPriority);
}

DiagControl::~DiagControl()
{
    delete DiagControl::instance();
}

void DiagControl::dataChange()
{
    foreach (DiagControl::DiagFunctionParser func, DiagVoidControlFunc) {
        (this->*(func))();
    }
}

void DiagControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    if ( HMI_MSGNAME_POWER_MODE == message_key ) {
        g_powermode = message_value.toInt();
    } else {
        // Nothing
    }
}

void DiagControl::triggerPowerMode(Type_uByte sts)
{
    m_DiagCtrlInfo.powerMode = sts;
    if( POWERMODE_D1  != m_DiagCtrlInfo.powerMode){
        emit PropertyChange(false);
    }
    else{
    }
}

int DiagControl::get16To10(int value)
{
    //can 实际传18bit
    if(int(value & 0x20000) == 0x0)
    {
        //Zheng
        if(value *0.2<=26000)
        {
            return value*0.2;
        }
        else
        {
            return 0xFFFF;
        }
    }
    else{
        //fu
        if((int((~value) & 0x3FFFF) +1)*0.2 <=26000)
        {
            return -(int((~value) & 0x3FFFF) +1)*0.2;//-26*2000
        }
        else{
            return 0xFFFF;
        }
    }
}

void DiagControl::get_timeout500ms()
{
}

//EEP_0 aubDiagOdoClearTimes
void DiagControl::func_ODO_CLEAR_TIME()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ODO_CLEAR_TIME,msg)
    global_clearTimes = 0;
    //里程清零剩余次数
    if((int)msg.value != global_clearTimes)
    {
        LOGPRINTVALUE("c_clearTotalMileTimes" , msg.value);
        emit PropertyChange("clearTotalMile", (int)msg.value);
        global_clearTimes = (int)msg.value;
    }
}

void DiagControl::func_MSG_EEPROM_4(const char *data)
{
    _c_MSG_EEPROM_4_msgType *msg = (_c_MSG_EEPROM_4_msgType *)data;


    //软件版本号转换
    QString str_softVersion;
    QString c_softVersionNum;
    for(int i=0; i<19; i++) {
        Type_uByte num1 = msg->Signals.softVersionNum[i] - 0x30;
        str_softVersion += QString::number(num1, 16).toUpper();
    }
    c_softVersionNum = str_softVersion.left(6)+"."+str_softVersion.mid(6,6)+"."+str_softVersion.mid(12,6)+"."+str_softVersion.right(1);

    if(g_softVersionNum != c_softVersionNum)
    {
        LOGPRINTVALUE("c_softVersionNum" , c_softVersionNum);
        g_softVersionNum = c_softVersionNum;
        emit PropertyChange("setSoftVersionNum",g_softVersionNum);
    }

    //硬件版本号转换
    QString str_hardVersion;
    QString c_hardVersionNum;
    for(int y=0;y<6;y++){
        Type_uByte num2 = msg->Signals.HardVersionNum[y] - 0x30;
        str_hardVersion += QString::number(num2, 16).toUpper();
    }
    c_hardVersionNum = str_softVersion.left(2)+"."+str_softVersion.mid(2,2)+"."+str_softVersion.right(2);

    if(g_hardVersionNum != c_hardVersionNum)
    {
        LOGPRINTVALUE("c_hardVersionNum" , c_hardVersionNum);
        g_hardVersionNum = c_hardVersionNum;
        emit PropertyChange("setHardVersionNum",g_hardVersionNum);
    }

    //电压值显示
//    if(_c_MSG_EEPROM_4_msgType_BackUp.Signals.BattVoltage != msg->Signals.BattVoltage)
//    {
//        QString c_voltage;
//        c_voltage = QString::number(msg->Signals.BattVoltage*0.01,'f',2);
//        emit PropertyChange("setVoltage", c_voltage);
//        LOGPRINTVALUE("c_voltage" , c_voltage);
//    }

    memcpy((char *)&_c_MSG_EEPROM_4_msgType_BackUp, (char *)msg, sizeof(*msg));
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  logOutput
 *  Description:  log输出
 *	Return:
 *          none: none
 *  Param:
 *          none: none
 * =====================================================================================
 */
void DiagControl::logOutput()
{
    LOGPRINT("logOutput");
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  clearTotalMile
 *  Description:  清除总计里程
 *	Return:
 *          none: none
 *  Param:
 *          none: none
 * =====================================================================================
 */
void DiagControl::clearTotalMile()
{
    LOGPRINT("clearTotalMile");
    //通知mcu 清除总计里程
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0601;

    _buffer.data[0] = 0x40;
    ivs_client_send_request(&_buffer, pUser_data);
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  diagReset
 *  Description:  恢复出厂设置
 *	Return:
 *          none: none
 *  Param:
 *          none: none
 * =====================================================================================
 */
void DiagControl::diagReset()
{
    LOGPRINT("diagReset");
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0603;

    _buffer.data[0] = 0xD2;          // msg_id
    _buffer.data[1] = 0x01;          // msg len
    _buffer.data[2] = 0x01;          // data
    ivs_client_send_request(&_buffer, pUser_data);
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  diagSetPopTimer
 *  Description:  设置一个timer，用于3s消去POP
 *	Return:
 *          none: none
 *  Param:
 *          none: none
 * =====================================================================================
 */
void DiagControl::diagSetPopTimer(bool status)
{
    (void)status;
//    if(status == true){
//        m_diagPopTimer->start();
//    }
//    else{
//        m_diagPopTimer->stop();
//    }
}
