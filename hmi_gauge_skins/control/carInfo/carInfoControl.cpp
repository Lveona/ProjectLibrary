#include "carInfoControl.h"
#include <QMutex>
#include <math.h>
static int currentIndex = 0;
static bool isCardShown = true; //当前C区卡片是否显示
static bool isCCardDefDisVis = true;
static bool chargeConnStatus = false;
static int theme = THEMEMODE_NONE;
static int mode = MAP_MODE_MAX;
QList<QString> cardlist = {"energy" ,"afterStart", "afterReset", "tyre"};

QList<CarInfoControl::CarInfoFunctionParser> CarInfoVoidControlFunc {
    &CarInfoControl::func_MSG_AS_TRIP,
    &CarInfoControl::func_MSG_AS_AVG_SPEED,
    &CarInfoControl::func_MSG_AS_DRIVING_TIME,
    &CarInfoControl::func_MSG_AS_AVG_POWER,
    &CarInfoControl::func_MSG_AR_TRIP,
    &CarInfoControl::func_MSG_AR_AVG_SPEED,
    &CarInfoControl::func_MSG_AR_DRIVING_TIME,
    &CarInfoControl::func_MSG_AR_AVG_POWER,
    &CarInfoControl::func_MSG_REMAIN_RANGE,
    &CarInfoControl::func_MSG_LF_TIRE_PRESSURE,
    &CarInfoControl::func_MSG_RF_TIRE_PRESSURE,
    &CarInfoControl::func_MSG_RR_TIRE_PRESSURE,
    &CarInfoControl::func_MSG_LR_TIRE_PRESSURE,
    &CarInfoControl::func_MSG_LF_TIRE_TEMP,
    &CarInfoControl::func_MSG_RF_TIRE_TEMP,
    &CarInfoControl::func_MSG_RR_TIRE_TEMP,
    &CarInfoControl::func_MSG_LR_TIRE_TEMP,
    &CarInfoControl::func_MSG_LAST_CHARGE_TIME,
    &CarInfoControl::func_MSG_LAST_CHARGE_ODO,
    &CarInfoControl::func_MSG_AVG_APC_VALUE,
    &CarInfoControl::func_MSG_CURRENT_APC_VALUE,
};

CarInfoControl::CarInfoControl()
{
    setPropertyValue(PROPERTYID_CARINFO_INDICATOR_NUM, cardlist.length());
    showTimer = new HMICustomTimer(12, false);
    connect(showTimer, &HMICustomTimer::timeout, this, [=](){
        showTimer->stop();
        if(isCCardDefDisVis) return;
        if(isCardShown)
        {
            setPropertyValue(PROPERTYID_CARINFO_CARD_SHOWN, isCardShown = false);
        }
    });
    start(QThread::NormalPriority);
}

CarInfoControl::~CarInfoControl()
{
    // Nothing
}

void CarInfoControl::dataChange()
{
    foreach (CarInfoControl::CarInfoFunctionParser func, CarInfoVoidControlFunc) {
        (this->*(func))();
    }
}
//自启动后
//mcu_1 MCU_TRIP_A
void CarInfoControl::func_MSG_AS_TRIP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AS_TRIP,msg)
    //里程
    float trip_start = msg.value * 0.1;
    trip_start = trip_start > 9999.9 ? 9999.9 : trip_start;
    setPropertyValue(PROPERTYID_CARINFO_AS_DRIVE_DISTANCE, QString::number(trip_start, 'f', 1));

}
//MCU_AVERAGE_SPEED_A
void CarInfoControl::func_MSG_AS_AVG_SPEED()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AS_AVG_SPEED,msg)
    //平均速度
    int trip_speed = msg.value;
    QString tripSpeedStr = "--";
    if(trip_speed != 0xFFFF){
        tripSpeedStr = trip_speed > 300 ? "300" : QString::number(trip_speed);
    }
    setPropertyValue(PROPERTYID_CARINFO_AS_AVG_SPEED, tripSpeedStr);

}
//MCU_DRIVING_TIME_A
void CarInfoControl::func_MSG_AS_DRIVING_TIME()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AS_DRIVING_TIME,msg)
    //平均时间
    int totalMin = msg.value;
    QString hour = "00";
    QString min = "00";
    if(totalMin != 0){
        int temp_hour =  totalMin / 60;
        hour = QString::number(temp_hour);
        if(temp_hour < 10){
            hour = "0" + hour;
        }
        int temp_min = totalMin % 60;
        min = QString::number(temp_min);
        if(temp_min < 10){
            min = "0" + min;
        }
    }
    setPropertyValue(PROPERTYID_CARINFO_AS_DRIVE_TIME, hour + ":" + min);

}
//TripAApc
void CarInfoControl::func_MSG_AS_AVG_POWER()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AS_AVG_POWER,msg)
    //平均电耗
    float avgEnergy = msg.value;
    QString avgEnergyStr = "--";
    if(avgEnergy != 0xFFFF){
        avgEnergy = avgEnergy * 0.1 - 20;
        if(avgEnergy < -20){
            avgEnergyStr = "-20";
        }else if(avgEnergy > 50){
            avgEnergyStr = "50";
        }else{
            avgEnergyStr = QString::number(avgEnergy, 'f', 1);
        }
    }
    setPropertyValue(PROPERTYID_CARINFO_AS_AVG_ENERGY, avgEnergyStr);
}

//自复位后
//mcu_1 MCU_TRIP_B
void CarInfoControl::func_MSG_AR_TRIP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AR_TRIP,msg)
    //里程
    float trip_start = msg.value * 0.1;
    trip_start = trip_start > 9999.9 ? 9999.9 : trip_start;
    setPropertyValue(PROPERTYID_CARINFO_AR_DRIVE_DISTANCE, QString::number(trip_start, 'f', 1));

}
//MCU_AVERAGE_SPEED_B
void CarInfoControl::func_MSG_AR_AVG_SPEED()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AR_AVG_SPEED,msg)
    //平均速度
    int trip_speed = msg.value;
    QString tripSpeedStr = "--";
    if(trip_speed != 0xFFFF){
        tripSpeedStr = trip_speed > 300 ? "300" : QString::number(trip_speed);
    }
    setPropertyValue(PROPERTYID_CARINFO_AR_AVG_SPEED, tripSpeedStr);
}
//MCU_DRIVING_TIME_B
void CarInfoControl::func_MSG_AR_DRIVING_TIME()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AR_DRIVING_TIME,msg)
    //平均时间
    int totalMin = msg.value;
    QString hour = "00";
    QString min = "00";
    if(totalMin != 0){
        int temp_hour =  totalMin / 60;
        hour = QString::number(temp_hour);
        if(temp_hour < 10){
            hour = "0" + hour;
        }
        int temp_min = totalMin % 60;
        min = QString::number(temp_min);
        if(temp_min < 10){
            min = "0" + min;
        }
    }
    setPropertyValue(PROPERTYID_CARINFO_AR_DRIVE_TIME, hour + ":" + min);
}
//TripBApc
void CarInfoControl::func_MSG_AR_AVG_POWER()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AR_AVG_POWER,msg)
    //平均电耗
    float avgEnergy = msg.value;
    QString avgEnergyStr = "--";
    if(avgEnergy != 0xFFFF){
        avgEnergy = avgEnergy * 0.1 - 20;
        if(avgEnergy < -20){
            avgEnergyStr = "-20";
        }else if(avgEnergy > 50){
            avgEnergyStr = "50";
        }else{
            avgEnergyStr = QString::number(avgEnergy, 'f', 1);
        }
    }
    setPropertyValue(PROPERTYID_CARINFO_AR_AVG_ENERGY, avgEnergyStr);
}

//B3 VCU_RmnDrvgRng
void CarInfoControl::func_MSG_REMAIN_RANGE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_REMAIN_RANGE,msg)
    //续航里程
    QString rmnRngStr = "--";
    if(msg.isTimeout == 0x01){
        //do nothing
    }else{
        long int rngValue = msg.value;
        //无效值
        if(rngValue != 0x7FFFFFFF){
 /*[NACA-445608] 仪表端显示当前续航为NaNKM*/
            long int r = floor(rngValue * 0.001);
            if(r >= 10 && r <= 3999){
                rmnRngStr = QString::number(r);
            }
        }
    }
    setPropertyValue(PROPERTYID_CARINFO_PLUSMAINMILE,rmnRngStr);
}

QString getValidValue(float unit, int offset, int result, int invalid, float maxValue, float minValue, bool isFloat, float convert){
    QString resultStr = "--";
    float f = 0.0;
    if(result == invalid){
        return resultStr;
    }

    if(unit != 1 || offset != 0){
        f = result * unit + offset;
    }
    if(f > maxValue || f < minValue){
        f = (float)maxValue;
    }
    if(convert){
        f = f * convert;
    }
    return isFloat ? QString::number(f,'f',1) : QString::number(f);
}

/**
* 胎压:
* 无效值,超时显示--
* 超范围显示上一有效值
* 精度1.373
*/
//247 BCM_TirePFrntLe
void CarInfoControl::func_MSG_LF_TIRE_PRESSURE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LF_TIRE_PRESSURE,msg)
    QString lfPressure = "--";
    if(!msg.isTimeout){
        int i_fl = msg.value;
        lfPressure = getValidValue(1.373, 0, i_fl, 0xFF, 348.742, 0, true, 0.01);
    }
    setPropertyValue(PROPERTYID_CARINFO_LF_TEMP_PRESSURE , lfPressure);
}
//BCM_TirePFrntRi
void CarInfoControl::func_MSG_RF_TIRE_PRESSURE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RF_TIRE_PRESSURE,msg)
    QString rfPressure = "--";
    if(!msg.isTimeout){
        int i_rf = msg.value;
        rfPressure = getValidValue(1.373, 0, i_rf, 0xFF, 348.742, 0, true, 0.01);
    }
    setPropertyValue(PROPERTYID_CARINFO_RF_TEMP_PRESSURE , rfPressure);
}
//BCM_TirePReRi
void CarInfoControl::func_MSG_RR_TIRE_PRESSURE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RR_TIRE_PRESSURE,msg)
    QString rrPressure = "--";
    if(!msg.isTimeout){
        int i_rr = msg.value;
        rrPressure = getValidValue(1.373, 0, i_rr, 0xFF, 348.742, 0, true, 0.01);
    }
    setPropertyValue(PROPERTYID_CARINFO_RR_TEMP_PRESSURE , rrPressure);
}
//BCM_TirePReLe
void CarInfoControl::func_MSG_LR_TIRE_PRESSURE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LR_TIRE_PRESSURE,msg)
    QString lrPressure = "--";
    if(!msg.isTimeout){
        int i_lr = msg.value;
        lrPressure = getValidValue(1.373, 0, i_lr, 0xFF, 348.742, 0, true, 0.01);
    }
    setPropertyValue(PROPERTYID_CARINFO_LR_TEMP_PRESSURE , lrPressure);
}

/**
* 胎温:
* 无效值,超时显示--
* 超范围显示上一有效值
*/
//248 BCM_TireTFrntLe
void CarInfoControl::func_MSG_LF_TIRE_TEMP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LF_TIRE_TEMP,msg)
    QString flTemp = "--";
    if(!msg.isTimeout){
        int flTempValue = msg.value;
        flTemp = getValidValue(1, -50, flTempValue, 0xFF, 120, -40, false, 0);
    }
    setPropertyValue(PROPERTYID_CARINFO_LF_TEMP , flTemp);
}
//BCM_TireTFrntRi
void CarInfoControl::func_MSG_RF_TIRE_TEMP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RF_TIRE_TEMP,msg)
    QString frTemp = "--";
    if(!msg.isTimeout){
        int frTempValue = msg.value;
        frTemp = getValidValue(1, -50, frTempValue, 0xFF, 120, -40, false, 0);
    }
    setPropertyValue(PROPERTYID_CARINFO_RF_TEMP , frTemp);
}
//BCM_TireTReRi
void CarInfoControl::func_MSG_RR_TIRE_TEMP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RR_TIRE_TEMP,msg)
    QString rrTemp = "--";
    if(!msg.isTimeout){
        int rrTempValue = msg.value;
        rrTemp = getValidValue(1, -50, rrTempValue, 0xFF, 120, -40, false, 0);
    }
    setPropertyValue(PROPERTYID_CARINFO_RR_TEMP , rrTemp);
}
//BCM_TireTReLe
void CarInfoControl::func_MSG_LR_TIRE_TEMP()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LR_TIRE_TEMP,msg)
    QString rlTemp = "--";
    if(!msg.isTimeout){
        int rlTempValue = msg.value;
        rlTemp = getValidValue(1, -50, rlTempValue, 0xFF, 120, -40, false, 0);
    }
    setPropertyValue(PROPERTYID_CARINFO_LR_TEMP , rlTemp);
}
//上次充电时间
void CarInfoControl::func_MSG_LAST_CHARGE_TIME()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LAST_CHARGE_TIME, msg)
    int chargeHour = (msg.value)/60;
    int chargeDay = chargeHour/24;
    setPropertyValue(PROPERTYID_LAST_CHARGE_TIME_HOUR,chargeHour);
    setPropertyValue(PROPERTYID_LAST_CHARGE_TIME_DAY, chargeDay);

}
//上次充电里程
void CarInfoControl::func_MSG_LAST_CHARGE_ODO()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LAST_CHARGE_ODO, msg)
    setPropertyValue(PROPERTYID_LAST_CHARGE_ODO, (int)msg.value);
}
//平均能耗
void CarInfoControl::func_MSG_AVG_APC_VALUE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_AVG_APC_VALUE, msg)
    float aveageAPC = msg.value*0.1-20;
    if(aveageAPC<-20){
        aveageAPC = -20;
    }else if(aveageAPC>50){
        aveageAPC = 50;
    }else{
        aveageAPC = aveageAPC;
    }
    setPropertyValue(PROPERTYID_AVERAGE_APC_VALUE, QString::number(aveageAPC ,'f', 1));
}
//瞬时能耗
void CarInfoControl::func_MSG_CURRENT_APC_VALUE()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_CURRENT_APC_VALUE, msg);
    float currentAPC = msg.value*0.1-20;
    if(currentAPC<-20){
        currentAPC = -20;
    }else if(currentAPC>99.9){
        currentAPC = 99.9;
    }else{
        currentAPC = currentAPC;
    }
    setPropertyValue(PROPERTYID_CURRENT_APC_VALUE, currentAPC);
}

void CarInfoControl::handleCarInfoCardVisible()
{
    if(theme == THEMEMODE_SPORT || //运动主题
            mode == BIG_MAP ||   mode == AR_MAP ||//非小地图模式
            chargeConnStatus){      //充电页面
        isCCardDefDisVis = isCardShown = false;
    }else{
        isCCardDefDisVis = isCardShown = true;
    }
    setPropertyValue(PROPERTYID_CARINFO_CARD_SHOWN, isCardShown);
}

void CarInfoControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    //接受SettingControl的存入eep的画面信息
    if(message_key == HMI_MSGNAME_CARINFOINDEX)
    {
        int tempIndex = message_value.toInt();
        currentIndex = (tempIndex == 0) ? CARINFOSCREENINDEX_AFTERSTART : tempIndex - 1;
        setPropertyValue(PROPERTYID_CARINFO_CHILD_INDEX,   currentIndex - 1);
    }
    else if(message_key == HMI_MSGNAME_THEME)
    {
        qInfo()<<"---HMI_MSGNAME_THEME---"<<message_value.toInt();
        theme = message_value.toInt();
        handleCarInfoCardVisible();
    }
    else if(message_key == HMI_MSGNAME_MAP_MODE){
        qInfo()<<"---HMI_MSGNAME_MAP_MODE---"<<message_value.toInt();
        mode = message_value.toInt();
        handleCarInfoCardVisible();
    }
    else if(message_key == HMI_MSGNAME_CHARGE_CONN)
    {
        qInfo()<<"---HMI_MSGNAME_CHARGE_CONN---"<<message_value.toInt();
        chargeConnStatus = message_value.toBool();
        handleCarInfoCardVisible();
    }
}

void CarInfoControl::get_timeout500ms()
{
    m_light_on = !m_light_on;
    showTimer->update();
}

bool isEnable(QString str){
    if(str.isEmpty())
        return false;
    return true;
}
int CarInfoControl::getNextEnableItem(DIRECTION dir, int currentItem, QList<QString> cardlist)
{
        int maxLen = cardlist.length();
        if(DIRECTION_AFTER == dir){
            for(int i = currentItem + 1; i < maxLen; i++){
                if(i < cardlist.length() - 1){
                    if(isEnable(cardlist.at(i))){
                        return i;
                    }
                }
                return i;
            }
            for(int i = 0; i < maxLen; i++){
                if(isEnable(cardlist.at(i))){
                    return i;
                }
            }
        }
        else if(DIRECTION_BEFORE == dir){
            for(int i = currentItem - 1; i >= 0; i--)
            {
                if(i < cardlist.length() - 1){
                    if(isEnable(cardlist.at(i))) {
                        return i;
                    }
                }
                return i;
            }
            for(int i = maxLen - 1; i > currentItem; i--)
            {
                if(i < cardlist.length() - 1){
                    if(isEnable(cardlist.at(i))) {
                        return i;
                    }
                }
                return i;
            }
        }
        return -1;
}

bool CarInfoControl::triggerHardKey(int key, int type)
{
    if(HDKEY_UP == key && KEY_OFF == type )
    {
        if(!handleHardKeyForCard()){
            currentIndex = getNextEnableItem(DIRECTION_BEFORE, currentIndex, cardlist);
            notifyCScreen();
            return true;
        }
    }
    else if(HDKEY_DOWN == key && KEY_OFF == type)
    {
        if(!handleHardKeyForCard()){
            currentIndex = getNextEnableItem(DIRECTION_AFTER, currentIndex, cardlist);
            notifyCScreen();
            return true;
        }
    }
    else{
        if(currentIndex == CARINFOSCREENINDEX_AFTERRESET)
        {
            if(HDKEY_DOWN == key && KEY_OUT_OFF == type)
            {
                if(!handleHardKeyForCard()){
                    LOGPRINT("tripBInfoClean");
                    tripBInfoClean();
                    return true;
                }
            }
        }
    }
    return false;
}

bool CarInfoControl::handleHardKeyForCard()
{
    if(isCCardDefDisVis) return false;
    showTimer->reset();
    if(!isCardShown){
        isCardShown = true;
        setPropertyValue(PROPERTYID_CARINFO_CARD_SHOWN, isCardShown);
        return true;
    }
}

void CarInfoControl::notifyCScreen(){
    if(currentIndex != -1){
        setPropertyValue(PROPERTYID_CARINFO_CHILD_INDEX,   currentIndex);
        int notifyIndex = (currentIndex + 1) - cardlist.length() > 0 ? cardlist.length() : currentIndex;
        emit sendToOtherCtrl(HMI_MSGNAME_SAVEINDEX, notifyIndex);
    }
}


/*
 * 自复位后清零
 */
void CarInfoControl::tripBInfoClean(void){
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x0601;

    _buffer.data[0]= 0x03;
    ivs_client_send_request(&_buffer, pUser_data);
}
