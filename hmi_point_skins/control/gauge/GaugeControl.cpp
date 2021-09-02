#include "GaugeControl.h"
#include <QMutex>
#include <math.h>

static int maxKmh= 240;//车速最大值240km/h
static CStepperAnimation _digitSpeed	=	{ 2, 0, float(maxKmh), 0, 0 };

static int g_unit = 0;
static int g_autoCheckState = AUTOCHECK_INIT;
static int power = 0;

QList<GaugeControl::GaugeFunctionParser> GaugeVoidControlFunc {
    &GaugeControl::func_HandleSpeed,
    &GaugeControl::func_HandleEngPwr
};

GaugeControl::GaugeControl()
{
    start(QThread::NormalPriority);
}

GaugeControl::~GaugeControl()
{
}

void GaugeControl::dataChange()
{
    foreach (GaugeControl::GaugeFunctionParser func, GaugeVoidControlFunc) {
        (this->*(func))();
    }
}

void GaugeControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    (void)message_value;
    if(HMI_MSGNAME_ATCHECK_STATE == message_key ){
        g_autoCheckState = message_value.toInt();
        setPropertyValue(PROPERTYID_GAUGE_AUTOCHECK, g_autoCheckState);
    }
    else {
        // Nothing
    }
}

void GaugeControl::receiveDateFromOtherProcess(QString name, QVariant value)
{
    (void)value;
}

void GaugeControl::get_timeout500ms()
{

}

float GaugeControl::getForTest(int type)
{
    if(0 == type)//车速
        return _digitSpeed.targetValue;
}
char *GaugeControl::getBackup(int id)
{
    (void)id;
    return nullptr;
}

void GaugeControl::iC_Can_Send(GAUGE_IC_CAN_INFO_SEND_ID reqSendID)
{
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x075A;

    switch (reqSendID) {
    case GAUGE_IC_CAN_INFO_TripSwitchSts :        // send languageSts
        _buffer.data[0] = 0x08;                                                                   // msg id
        _buffer.data[1] = 0x01;                                                                   // msg len
        //        _buffer.data[2] = tripSwitch;//_c_IVI_infoSet_IP_msgType_Backup.Signals.ivi_TripSwitch;                   // msg len
        break;
    default:
        return;
    }
    ivs_client_send_request(&_buffer, pUser_data);
}

void GaugeControl::iC_Can_Info_Send(GAUGE_IC_CAN_INFO_SEND_ID reqSendID)
{
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0603;

    switch (reqSendID) {
    case GAUGE_IC_CAN_INFO_TripSwitchSts :        // send languageSts
        _buffer.data[0] = 0x41;                   // msg id
        _buffer.data[1] = 0x01;                   // msg len
        //        _buffer.data[2] = tripSwitch;             // msg len
        break;
    default:
        return;
    }
    ivs_client_send_request(&_buffer, pUser_data);
}

void GaugeControl::func_HandleSpeed()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_SPEED,msg)
    //车速显示
    double speed = msg.value;
    if(speed >= 0xFFFF){
        setPropertyValue(PROPERTYID_GAUGE_DIGITSPEED,0xFFFF);
        emit sendToOtherCtrl(HMI_MSGNAME_VEHICLESPEED,0xFFFF);
        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_DISPLAY_SPEED,0xFFFF);
        return;
    }
    else if(speed*0.01 >= 300){
        speed = 300;
    }
    else{
        speed = speed*0.01;
    }

    int c_realSpeed = round(speed);
    if(g_unit == 1){//1英里mph
        c_realSpeed = round(c_realSpeed * 0.6214);
    }
    setPropertyValue(PROPERTYID_GAUGE_DIGITSPEED,c_realSpeed);   //0-maxKmh
    emit sendToOtherCtrl(HMI_MSGNAME_VEHICLESPEED,c_realSpeed);   //0-maxKmh
    emit sendToOtherProcess(HMI_SHREMEMORY_CMD_DISPLAY_SPEED,c_realSpeed);
}

void GaugeControl::func_HandleEngPwr()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ENGPWR,msg)
    //功率显示
    //超时显示0,
    //超出有效范围、无效值显示保持不变
    if(msg.isTimeout){
        power = 0;
    }else{
        int r = msg.value;
        if(r == 0x7FF){
            //do nothing
        }else{
            r = r * 0.1 + (-1023);//精度0.1 ,偏移量-1023
            if(r < -100 || r > 100){//无效值
                //do nothing
            }else{
                power = r;
            }
        }
    }
    setPropertyValue(PROPERTYID_GAUGE_POWER,power);
}

