#include "HomeControl.h"
#include <QMutex>
#include <cmath>
static QString lastGear = "--";
static int g_lastTimeFormat = 0;
static QString g_Time = "";
static QString g_format = "";
static QString driveModeStr = "";
static int g_driveMode = 0;
static int flStatus = 0;
static int frStatus = 0;
static int rlStatus = 0;
static int rrStatus = 0;
static int tailStatus = 0;
static int hoodStatus = 0;
static int flChargeStatus = 0;
static int frChargeStatus = 0;
static bool doorStatus = true;
static Audio_ReqCmd playStatus = AUDIO_STOP;
static bool chargeConn_global = false;
extern "C"{
static QString addZero(int value)
{
    if(value<10)
        return '0'+QString::number(value);
    return QString::number(value);
}
}

QList<HomeControl::HomeFunctionParser> HomeVoidControlFunc {
    &HomeControl::func_CHARGE_PERCENT,
    &HomeControl::func_CHARGE_COLOR,
    &HomeControl::func_DRIVE_MODE,
    &HomeControl::func_CHARGE_STATUS,
    &HomeControl::func_CHARGE_CABLE_STATUS,
    &HomeControl::func_TEMP,
    &HomeControl::func_READY,
    &HomeControl::func_GEAR,
    &HomeControl::func_FL_DOOR_STATUS,
    &HomeControl::func_FR_DOOR_STATUS,
    &HomeControl::func_RL_DOOR_STATUS,
    &HomeControl::func_RR_DOOR_STATUS,
    &HomeControl::func_TAIL,
    &HomeControl::func_HOOD,
    &HomeControl::func_FL_CHARGE_PORT,
    &HomeControl::func_RL_CHARGE_PORT,
    &HomeControl::func_REMAIN_CHARGE_TIME,
    &HomeControl::func_ODO,
    &HomeControl::func_CHARING_VOLTAGE,
    &HomeControl::func_CHARING_ELECTRIC,
};


HomeControl::HomeControl()
{
    start(QThread::NormalPriority);
}

HomeControl::~HomeControl()
{

}
//mcu_0 MCU_BATT_VAL
void HomeControl::func_CHARGE_PERCENT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARGE_PERCENT,msg)
    //电量
    int battVal = msg.value;
    if(battVal == 0xFF){
        setPropertyValue(PROPERTYID_HOME_CHARGE_VALUE,"--");
    }
    else{
        if(battVal <= 100){
            setPropertyValue(PROPERTYID_HOME_CHARGE_VALUE,QString::number(battVal));
        }
        else{
            setPropertyValue(PROPERTYID_HOME_CHARGE_VALUE,"--");
        }
    }
}

//mcu_5 CLS_TT_BATT_COLOR
void HomeControl::func_CHARGE_COLOR()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARGE_COLOR,msg)
    //颜色
    int chargeColor = msg.value;
    if(chargeColor == 1 || chargeColor == 2 || chargeColor == 3){
        if(chargeColor == 1)
            setPropertyValue(PROPERTYID_HOME_CHARGE_COLOR,COLORTYPEQML_RED);//0:red ,1:yellow ,2:green颜色
        if(chargeColor == 2)
            setPropertyValue(PROPERTYID_HOME_CHARGE_COLOR,COLORTYPEQML_YELLOW);//0:red ,1:yellow ,2:green颜色
        if(chargeColor == 3)
            setPropertyValue(PROPERTYID_HOME_CHARGE_COLOR,COLORTYPEQML_GREEN);//0:red ,1:yellow ,2:green颜色
    }
    else{
    }
}

//98 VCU_ActvdDrvMod
void HomeControl::func_DRIVE_MODE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_DRIVE_MODE,msg)
    int dm = 0;
    //驾驶模式
    if(!msg.isTimeout){
        dm = msg.value;
        if(dm == 1){
            driveModeStr = "COMFORT";
        }else if(dm == 2){
            driveModeStr = "ECO";
        }else if(dm == 3){
            driveModeStr = "SPORT";
        }else if(dm == 4){
            driveModeStr = "INDIVIDUAL";
        }
    }else{
        driveModeStr = "--";
    }
    if(g_driveMode != dm){
        emit sendToOtherCtrl(HMI_MSGNAME_DRIVE_MODE,dm);
    }
    setPropertyValue(PROPERTYID_HOME_DRIVEMODE,driveModeStr);
    g_driveMode = dm;
}

//98 VCU_ChrgSts
void HomeControl::func_CHARGE_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARGE_STATUS,msg)
    //充电状态
    int chargeSts = msg.value;
    bool isCharging = false;
    if(chargeSts == 0x2 || chargeSts == 0x4 || chargeSts == 0xA || chargeSts == 0xC){
        isCharging = true;
    }
    setPropertyValue(PROPERTYID_HOME_IS_CHARGING, isCharging);
    setPropertyValue(PROPERTYID_HOME_CHARGE_STATUS, chargeSts);
}

//B3 VCU_ChrgCnctrDetd
void HomeControl::func_CHARGE_CABLE_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARGE_CABLE_STATUS,msg)
    //充电线连接状态
    bool connState = false;
    if(msg.isTimeout){
    }else{
        int chargeConn = msg.value;
        if(chargeConn == 0x1 || chargeConn == 0x2 ||
                chargeConn == 0x3 || chargeConn == 0x4 || chargeConn == 0x5){
            connState = true;
        }
        setPropertyValue(PROPERTYID_HOME_CHARGE_CNCTRDETD,chargeConn);
    }
    setPropertyValue(PROPERTYID_HOME_CHARGE_CONNECT,connState);
    if(chargeConn_global != connState){
        sendToOtherCtrl(HMI_MSGNAME_CHARGE_CONN, connState);
        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_CHARGING, connState);
        chargeConn_global = connState;
    }
}

//1F7 CCU_AmbAirT
void HomeControl::func_TEMP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TEMP,msg)
    //温度
    QString tempStr = "-.-";
    if(msg.isTimeout){
        // do nothing
    }else{
        int tempValue = msg.value;
        float precision = 0.5;
        float offset = -40.0;

        float result = tempValue * precision + offset;
        int iresult = (int)result;
        float decimal = result - iresult;

        //显示精度为0.5℃
        if(abs(decimal) - 0.5 >= 0 ){
            //0.5-1.0
            result = (float)(iresult) + (decimal >= 0 ? 0.5 : -0.5);
        }
        else{
           //0-1.5
            result = (float)(iresult);
        }
        if(result >= -40 && result <= 85)
            tempStr = QString::number(result,'f',1);
    }
    setPropertyValue(PROPERTYID_HOME_TEMP, tempStr);
}

//97 VCU_PtSt
void HomeControl::func_READY()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_READY,msg)
    //Ready
    bool isReady = false;
    if(msg.isTimeout){
        //do nothing
    }else{
        int r = msg.value;
        if(r == 3) isReady = true;
    }
    setPropertyValue(PROPERTYID_HOME_READY,isReady);
}

//97 VCU_LoglGearStsAct
void HomeControl::func_GEAR()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_GEAR,msg)
    //gear
    QString curGear = "";
    Audio_ReqCmd audio = AUDIO_STOP;
    if(msg.isTimeout == 0x01){
        //do nothing
    }else{
        int r = msg.value;
        if(r == 0x1){
            curGear = "P";
        }else if(r == 0x2){
            audio = AUDIO_PLAY;
            curGear = "R";
        }else if(r == 0x3){
            curGear = "N";
        }else if(r == 0x4){
            curGear = "D";
        }else if(r == 0x5 || r == 0x6){
            curGear = lastGear;
        }else{
            //do nothing
        }
    }
    if(lastGear != curGear)
    {
        lastGear = curGear;
        setPropertyValue(PROPERTYID_HOME_GEAR, curGear);
        sendToOtherProcess(HMI_SHREMEMORY_CMD_Gear,curGear);
//        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_GEAR, AUDIO_INDEX_GEAR ,audio);
    }
}

//245 BCM_DoorDrvrNotClsdWarnReq;
void HomeControl::func_FL_DOOR_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_FL_DOOR_STATUS,msg)
    //前左门
    flStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_FLDOOR, (flStatus == 0x1 || flStatus == 0x2));
    handleDoorVoice();
}
//BCM_DoorPassNotClsdWarnReq
void HomeControl::func_FR_DOOR_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_FR_DOOR_STATUS,msg)
    //前右门
    frStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_FRDOOR, (frStatus == 0x1 || frStatus == 0x2));
    handleDoorVoice();
}
//BCM_DoorRearLeNotClsdWarnReq
void HomeControl::func_RL_DOOR_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RL_DOOR_STATUS,msg)
    //后左门
    rlStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_RLDOOR, (rlStatus == 0x1 || rlStatus == 0x2));
    handleDoorVoice();
}
//BCM_DoorRearRiNotClsdWarnReq
void HomeControl::func_RR_DOOR_STATUS()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RR_DOOR_STATUS,msg)
    //后右门
    rrStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_RRDOOR, (rrStatus == 0x1 || rrStatus == 0x2));
    handleDoorVoice();
}
//BCM_TrNotClsdWarnReq
void HomeControl::func_TAIL()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_TAIL,msg)
    //尾门
    tailStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_TAIL, (tailStatus == 0x1 || tailStatus == 0x2));
    handleDoorVoice();
}
//BCM_HoodNotClsdWarnReq
void HomeControl::func_HOOD()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_HOOD,msg)
    //引擎盖
    hoodStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_HOOD, (hoodStatus == 0x1 || hoodStatus == 0x2));
    handleDoorVoice();
}
//BCM_ChrgnFlapNotClsdWarnReq
void HomeControl::func_FL_CHARGE_PORT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_FL_CHARGE_PORT,msg)
    //前左充电盖
    flChargeStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_FLCHARGE, (flChargeStatus == 0x1 || flChargeStatus == 0x2));
    handleDoorVoice();
}
//BCM_ChrgnFlapRiNotClsdWarnReq
void HomeControl::func_RL_CHARGE_PORT()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RL_CHARGE_PORT,msg)
    //前右充电盖
    frChargeStatus = msg.isTimeout ? 0 : msg.value;
    setPropertyValue(PROPERTYID_HOME_FRCHARGE, (frChargeStatus == 0x1 || frChargeStatus == 0x2));
    handleDoorVoice();
}

//200 BMS_HvBattTiRmnChrgn
void HomeControl::func_REMAIN_CHARGE_TIME()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_REMAIN_CHARGE_TIME,msg)
    //续航里程
    QString remainTimeStr = "";
    if(msg.isTimeout){

    }else{
        int seconds = msg.value;
        if(seconds == 0xFFFE || seconds == 0xFFFF){

        }else{
            int mins = seconds / 60;
            int hour = mins / 60;
            int min = mins % 60;
            if(mins / 60 > 0){
                remainTimeStr = QString::number(hour) + "小时";
            }
            min += seconds % 60 < 30 ? 0 : 1; //＜30s向下显示，≥30s向上显示
            if(min > 0){
                remainTimeStr += QString::number(min) + "分钟";
            }
        }
    }
    setPropertyValue(PROPERTYID_HOME_REMAIN_TIME, remainTimeStr);
}

//mcu_1 MCU_ODO
void HomeControl::func_ODO ()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ODO,msg)
    //总计里程
    QString c_odo = "";
    if(msg.value == 0xFFFFFFFF){
        c_odo = "ERROR";
    }
    else{
        int _tmp = 0;
        if(msg.value * 0.001 > 999999){
            _tmp = 999999;
        }
        else{
            _tmp = msg.value * 0.001;
        }

        c_odo = QString::number(_tmp);
    }
    setPropertyValue(PROPERTYID_HOME_TOTAL_MILE,c_odo);
}

//F9 BMS_HvBattU
void HomeControl::func_CHARING_VOLTAGE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARING_VOLTAGE,msg)
    QString voltage = "";
    if(!msg.isTimeout){
        if(msg.value == 0x3FFF){
            //
        }else if(msg.value > 0x27F8){
            voltage = "--";
        }else {
            int val = msg.value * 0.1;
            voltage = (val <= 500) ? QString::number(val, 'f', 1) : "--";
        }
    }
    setPropertyValue(PROPERTYID_HOME_VOLTAGE, voltage);
}

//FB BMS_HvBattI
void HomeControl::func_CHARING_ELECTRIC()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CHARING_ELECTRIC,msg)
    QString electric = "";
    if(!msg.isTimeout){
        if(msg.value == 0x7FFF){
            //
        }else if(msg.value == 0x7FFE){
            electric = "--";
        }else {
            float val = msg.value * 0.1 - 2047;
            electric = (val >= -500 && val <= 500) ? QString::number(val, 'f', 1) : "--";
        }
    }
    setPropertyValue(PROPERTYID_HOME_ELECTRIC, electric);
}

void HomeControl::handleDoorVoice()
{
    if(flStatus == 0x01 || frStatus == 0x01 || rlStatus == 0x01 || rrStatus == 0x01 || tailStatus == 0x01 ||
            hoodStatus == 0x01 || flStatus == 0x01 || frStatus == 0x01 || flChargeStatus == 0x01 || frChargeStatus == 0x01){
        playStatus = AUDIO_STOP;
        doorStatus = true;
    }
    else if(flStatus == 0x02 || frStatus == 0x02 || rlStatus == 0x02 || rrStatus == 0x02 || tailStatus == 0x02
            || hoodStatus == 0x02 || flStatus == 0x02 || frStatus == 0x02 || flChargeStatus == 0x02 || frChargeStatus == 0x02){
        //TBD:重新响声音
        playStatus = AUDIO_PLAY;
        doorStatus = true;
    }else{
        doorStatus = false;
        playStatus = AUDIO_STOP;
    }
    setPropertyValue(PROPERTYID_HOME_DOORWARNING, doorStatus);
    //HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_DOOROPEN, AUDIO_INDEX_DOOR_OPEN, playStatus);
}

void HomeControl::getFromOtherCtrl(QString message_key, QVariant message_value){}

void HomeControl::dataChange()
{
    foreach (HomeControl::HomeFunctionParser func, HomeVoidControlFunc) {
        (this->*(func))();
    }

}
