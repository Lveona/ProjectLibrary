#include "telltalesStrategy.h"
#include <QMutex>
#include "hmi_share.h"
//#include "telltale.h"
#include "telltaleflash.h"
#include "telltalesControl.h"

TelltalesStrategy::TelltalesStrategy(){
//    m_autocheckSts=AUTOCHECK_INIT;
    m_mutex = new QMutex(QMutex::Recursive);
    m_powerMode = 0;
    m_autoCheckState = AUTOCHECK_INIT;///
    m_telltaleFlash1HZ = new TelltaleFlash();
    m_telltaleFlash2HZ = new TelltaleFlash();
    m_telltaleFlash3HZ = new TelltaleFlash();
    m_telltaleFlash4HZ = new TelltaleFlash();

    qRegisterMetaType<TellData>("TellData");
    connect(m_telltaleFlash1HZ, SIGNAL(stateChange(int, const TellData)), this, SIGNAL(PropertyChange(int, const TellData)));
    connect(m_telltaleFlash2HZ, SIGNAL(stateChange(int, const TellData)), this, SIGNAL(PropertyChange(int, const TellData)));
    connect(m_telltaleFlash3HZ, SIGNAL(stateChange(int, const TellData)), this, SIGNAL(PropertyChange(int, const TellData)));
    connect(m_telltaleFlash4HZ, SIGNAL(stateChange(int, const TellData)), this, SIGNAL(PropertyChange(int, const TellData)));
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleTellStrategy
 *  Description:  共同处理本次 灯状态变化
 *	Return:
 *          none: none
 *  Param:
            tell:      tell
 * =====================================================================================
 */
void TelltalesStrategy::handleTellStrategy(Telltale * tell)
{
    QMutexLocker _locker(m_mutex);
    Q_UNUSED(_locker)

    bool result = isMatchPower(tell);

    if(result){
        //允许亮
    }
    else{
        //灭
        tell->targetValue = VISIBLE_false;
    }

    bool r = setPropertyTell(tell->propertyIndex, tell);

    if(r)
    {
        handle(tell);
    }
}
/*处理本次 灯状态变化*/
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handle
 *  Description:  处理本次 灯状态变化
 *	Return:
 *          none: none
 *  Param:
            tell:      tell
 * =====================================================================================
 */
void TelltalesStrategy::handle(Telltale *tell)
{
    if(tell->targetValue != VISIBLE_spangle){
        emit PropertyChange(tell->propertyIndex, TellData(tell->targetValue, tell->colorType));
    }
    else{
        //本次不处理闪烁的状态, 由闪烁策略统一处理
    }
}
/*处理灯和触发电源变化时候，都需要处理灯与电源的匹配问题，此处共通化*/
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  isMatchPower
 *  Description:  共通化 灯与电源的匹配问题
 *	Return:
 *          none: none
 *  Param:
            tell:      tell
 *  Return: bool:      bool
 * =====================================================================================
 */
bool TelltalesStrategy::isMatchPower(Telltale *tell)
{
    if(m_powerMode == static_cast<int>(POWERMODE_ANIMATION))
    {
        return false;
    }
    else{
        return true;
    }
//    if(m_powerMode == static_cast<int>(POWERMODE_D1)){
//        if(tell->powerMode == static_cast<int>(TTPOWERMODE_D1)
//                || tell->powerMode == static_cast<int>(TTPOWERMODE_D1_D2))
//        {
//            return true;
//        }
//        else{
//            return false;
//        }
//    }else if(m_powerMode == static_cast<int>(POWERMODE_D2)){
//        if(tell->powerMode == static_cast<int>(TTPOWERMODE_D2)
//                || tell->powerMode == static_cast<int>(TTPOWERMODE_D1_D2))
//        {
//            return true;
//        }
//        else{
//            return false;
//        }
//    }
//    else{
//        // do nothing D3,D4,D5
//        // 比如左转向灯,D1亮,D3要灭
//        return false;
//    }
}

void TelltalesStrategy::setAutoCheckState(int value)
{

    m_autoCheckState = value;
    if(AUTOCHECK_START == value){
        //自检开始
        foreach(AUTOCHECKTELL autoCheckTell, m_autoCheckList){
            if(autoCheckTell.tell->enable){
                autoCheckTell.tell->targetValue = VISIBLE_true;
                autoCheckTell.tell->colorType = autoCheckTell.colorType;
                setPropertyTell(autoCheckTell.tell->propertyIndex, autoCheckTell.tell);
                emit PropertyChange(autoCheckTell.tell->propertyIndex, TellData(static_cast<int>(VISIBLE_true), autoCheckTell.colorType));
            }
        }
    }
    else{
        //自检结束
    }
}

//添加自检灯时候,要保证此时的灯颜色就是自检的灯颜色
void TelltalesStrategy::addAutoCheckTell(QList<Telltale *> list)
{
    m_autoCheckList.clear();
    foreach(Telltale* tell, list){
        AUTOCHECKTELL autoCheckTell = {tell, tell->colorType};
        m_autoCheckList.push_back(autoCheckTell);
    }
}

int TelltalesStrategy::getAutoCheckState()
{
   return m_autoCheckState;
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  triggerPowerMode
 *  Description:  处理本次 电源状态变化
 *	Return:
 *          none: none
 *  Param:
            powerMode:      powerMode
 * =====================================================================================
 */
void TelltalesStrategy::triggerPowerMode(int value)
{
    QMutexLocker _locker(m_mutex);
    Q_UNUSED(_locker)

    m_powerMode = value;

    //D2灭屏逻辑
    static bool g_warningState = false;
    bool state = false;
    foreach (Telltale* tell, m_tells.values()) {
        if(tell->targetValue != VISIBLE_false && isMatchPower(tell)){
            state = true;
            break;
        }
    }

    if(g_warningState != state){
        g_warningState = state;
//        emit sendToOtherProcess(HMI_SHREMEMORY_CMD_TELLWARN, g_warningState);
    }

    //灯报警状态要清
    //因为仪表切换为D2模式，部分报警灯消去延迟
    //HMI在电源切换是将不满足电源条件的灯强制立刻熄灭
    //部分满足D2电源条件的灯根据真实状态来判断是否需要熄灭
    foreach(Telltale* tell, m_tells.values()) {
//        handleTellStrategy(tell);
        //1. 关心[要灭]的灯
        if(tell->targetValue != VISIBLE_false && !isMatchPower(tell))
        {
            //2. 同步备份灯
            tell->targetValue = VISIBLE_false;

             //3. 通知画面
            handle(tell);
        }
    }
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  get_timeout500ms
 *  Description:  定周期触发,让灯闪烁
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void TelltalesStrategy::get_timeout500ms()
{
}

void TelltalesStrategy::get_timeout10ms()
{
    m_telltaleFlash1HZ->update();
    m_telltaleFlash2HZ->update();
    m_telltaleFlash3HZ->update();
    m_telltaleFlash4HZ->update();
}

//过滤
bool TelltalesStrategy::setPropertyTell(int id, Telltale *tell)
{
    Telltale* t = m_tells.value(id, 0);

    if(0 == t){
        //new tell
        Telltale* tmp = new Telltale(*tell);
        m_tells.insert(id, tmp);

        if(tell->spangleType == FLASHTYPE_1HZ)
            m_telltaleFlash1HZ->addTell(tell);
        else if(tell->spangleType == FLASHTYPE_2HZ)
            m_telltaleFlash2HZ->addTell(tell);
        else if(tell->spangleType == FLASHTYPE_3HZ)
            m_telltaleFlash3HZ->addTell(tell);
        else if(tell->spangleType == FLASHTYPE_4HZ)
            m_telltaleFlash4HZ->addTell(tell);
        return true;
    }
    else{
        if(t->colorType == tell->colorType && t->targetValue == tell->targetValue){
            //一样
        }
        else{
            t->targetValue = tell->targetValue;
            t->colorType = tell->colorType;
            return true;
        }
    }
    return false;
}

/*void TelltalesStrategy::iC_Can_Info_Send(TELLTALE_IC_CAN_INFO_SEND_ID reqSendID){
    IVSProxyRequest _buffer;
    void * pUser_data = NULL;

    memset(&_buffer, 0, sizeof(IVSProxyRequest));
    _buffer.rw	    = 0x01;
    _buffer.length  = 0x0020;
    _buffer.control = 0x00;
    _buffer.opecode = 0x075A;

    switch (reqSendID) {
    case TELLTALE_IC_CAN_INFO_fatigueDrivingWarnning :           //send fatigueDrivingWarnning  疲劳驾驶报警
        _buffer.data[0] = 0x01;                                  //msg id
        _buffer.data[1] = 0x01;                                  //msg len
        //        if(VISIBLE_true == Light_Tired.targetvalue){
        //            _buffer.data[2] = static_cast<unsigned char>(0x01);  //coding
        //        }
        //        else{
        //            _buffer.data[2] = static_cast<unsigned char>(0x00);  //coding
        //        }
        break;
    case TELLTALE_IC_CAN_INFO_SpeedLimitSts :                    //send SpeedLimitSts 限速辅助开关
        _buffer.data[0] = 0x02;                                  //msg id
        _buffer.data[1] = 0x01;                                  //msg len
        _buffer.data[2] = speedLimitOnOffSet;  //coding off
        qWarning()<<"###TELLTALE_IC_CAN_INFO_SpeedLimitSts"<<_buffer.data[2];
        break;
    case TELLTALE_IC_CAN_INFO_overspdWarningSwSts :              //send overspdWarningSwSts 超速报警开关设置状态
        _buffer.data[0] = 0x03;                                  //msg id
        _buffer.data[1] = 0x01;                                  //msg len
        _buffer.data[2] = 0x3;  //coding off //may by ZHZH
        qWarning()<<"###TELLTALE_IC_CAN_INFO_overspdWarningSwSts"<<_buffer.data[2];
        break;
    case TELLTALE_IC_CAN_INFO_overspdWarningSetFeedback :        //send overspdWarningSwSts 超速报警设置值
        _buffer.data[0] = 0x04;                                  //msg id
        _buffer.data[1] = 0x01;                                  //msg len
        _buffer.data[2] = slaspeedToMuc;      //coding
        qWarning()<<"###TELLTALE_IC_CAN_INFO_overspdWarningSetFeedback"<<_buffer.data[2];
        break;
    case TELLTALE_IC_CAN_INFO_SpeedLimitModeSts :                //send SpeedLimitMode 限速辅助模式
        _buffer.data[0] = 0x05;                                  //msg id
        _buffer.data[1] = 0x01;                                  //msg len
        _buffer.data[2] = limitmodeset;  //coding  手动
        qWarning()<<"###TELLTALE_IC_CAN_INFO_SpeedLimitModeSts"<<_buffer.data[2];
        break;
    default:
        return;
        //break;
    }
    ivs_client_send_request(&_buffer, pUser_data);
}*/

