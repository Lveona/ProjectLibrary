#include "popupStrategy.h"
#include "popup.h"
#include "hmi_share.h"
#include <QMutex>
#include "uniqPopAddInfo.h"
#include "popupControl.h"

static Popup CurrentPopupNon = {
    POP_PRIORITY_LEVEL_HIST_LIMIT,
    POP_WMSG_CATEGORY_NUM,
    POP_PM_D1,
    "",
    "",
    NULL,
    HMIAudioCtrl::WARNING_STATE_MAX
};

static int g_show_C_Card_index = -1;
static int g_currentToast1PopNeedOff = 0;//判断满足最小显示时长
static int g_currentToast2PopNeedOff = 0;

static int g_currentAdasToastPopNeedOff = 0;//判断满足最小显示时长

static int gPopAlarmOffIndex = 0;

static int m_RedCardIndex = 0;//分页标 当前红色卡片位置
static int m_YellowCardIndex = 0;//分页标 当前黄色卡片位置
static bool g_hideAllYellowCard = false;//true:黄色卡片被隐藏

static	Popup * ptPopupTbl[POP_WMSG_CATEGORY_NUM][POP_PRIORITY_LEVEL_NUM_MAX];
//已维数组,每类pop最大100个
static	Popup * ptPopupTbl_toast[POP_WMSG_CATEGORY_NUM * POP_PRIORITY_LEVEL_NUM_MAX];
static	Popup * ptPopupTbl_Adaa_toast[POP_WMSG_CATEGORY_NUM * POP_PRIORITY_LEVEL_NUM_MAX];

// 判断pop是否是空的
static bool checkPopIsNone(const Popup* pop){
    return pop->category == CurrentPopupNon.category;
}

int PopupStrategy::getPopById(int type, int id)
{
    return 0;
//    if(id <= 0) return 0;

//    return (m_wMsgOccurpHistList[type].at(id-1));
}

//static QByteArray     m_wMsgOccurpHistListToast[POP_WMSG_CATEGORY_NUM * POP_PRIORITY_LEVEL_HIST_LIMIT] = {
//    0
//};

void PopupStrategy::initlaize(void){    // TODO
    m_TimerCntNormal      = 0;
    m_TimerCntNormalToast1 = 0;
//    m_TimerCntNormalToast2 = 0;
    m_powermode           = 0;
    m_TimerCntNormalAdas = 0;
    m_TimerCntNormalTyre = 0;
    m_TimerCntNormalVolume = 0;

    m_CurrentPop  = &CurrentPopupNon;
    m_CurrentPopToast1  = &CurrentPopupNon;
//    m_CurrentPopToast2  = &CurrentPopupNon;
    m_CurrentPopAdasToast = &CurrentPopupNon;
    m_autoCheckState = AUTOCHECK_INIT;

//    m_wMsgDispHistList.fill(0, POP_WMSG_CATEGORY_C * POP_PRIORITY_LEVEL_HIST_LIMIT);
    m_wMsgDispHistListCardRed.clear();
    emit PropertyChange(PROPERTYID_POPUP_REDCARD_LISTLENTH,m_wMsgDispHistListCardRed.length());
    m_wMsgDispHistListCardYellow.clear();
    emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_LISTLENTH,m_wMsgDispHistListCardYellow.length());
    m_wMsgDispHistListToast.clear();
    m_wMsgDispHistListADASToastRed.clear();
    m_wMsgDispHistListADASToastYellow.clear();
    m_wMsgDispHistListADASToastGreen.clear();
    m_wMsgDispHistListCardYellow_read.clear();
    emit sendToOtherCtrl(HMI_MSGNAME_HAVEREAD,1);

    // 考虑到数组浪费比较多，将二维数组合并为一维
    m_wMsgOccurpHistListToast.fill(0, POP_WMSG_CATEGORY_NUM * POP_PRIORITY_LEVEL_HIST_LIMIT);
//     *POP_PRIORITY_LEVEL_HIST_LIMIT

    m_CurrentPopIndex = 0;
    m_mutex = new QMutex(QMutex::Recursive);

}

void PopupStrategy::triggerTimeout500ms()
{
    handleTyre5secends();
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  triggerTimeout100ms
 *  Description:  更新策略
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void PopupStrategy::triggerTimeout100ms(){

    QMutexLocker _lock(m_mutex);
    Q_UNUSED(_lock)
    handleDynamicPopText();

    handleToast100ms();

    handleAdasToast100ms();

    handleVolumeToast100ms();
//    m_TimerCntNormal++;
//    calcCurrentPopDisTime();

    //是否有报警显示
    bool warningState = false;

//    if(m_CurrentPop->category != POP_WMSG_CATEGORY_NUM
//            && g_hideAllYellowCard == false)//当前文言不为空 并且未隐藏黄色卡片
//    {
//        warningState = true;
//    }

    if(m_CurrentPop->category == POP_WMSG_CATEGORY_A
            ||( m_CurrentPop->category == POP_WMSG_CATEGORY_B && g_hideAllYellowCard == false))
    {
        warningState = true;
    }

//    qInfo()<<"m_CurrentPop->category"<<m_CurrentPop->name<<QString::number(m_CurrentPop->category);

    static bool g_warningState = false;
    if(g_warningState != warningState)
    {
        g_warningState = warningState;
        emit notifyWarningState(g_warningState);
    }

//    if(m_TimerCntNormal >= POP_DIS_TIMEMIN
//            && g_show_C_Card_index >= 0
//            && g_show_C_Card_index <= m_popupC_CardList.length()-1)
//    {
//        showPopUp(m_popupC_CardList[g_show_C_Card_index]);
//    }
}

// AutoCheck自检模式处理
void PopupStrategy::triggerAutoCheckState(int sts){
    Q_UNUSED(sts)
    m_autoCheckState = sts;
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  triggerPowerMode
 *  Description:  切换电源模式处理
 *	Return:
 *          none: none
 *  Param:
            power: power
 * =====================================================================================
 */
void PopupStrategy::triggerPowerMode(int power){
    QMutexLocker _lock(m_mutex);
    Q_UNUSED(_lock)

    m_powermode = power;

    m_wMsgDispHistListToast.clear();
    m_wMsgDispHistListADASToastRed.clear();
    m_wMsgDispHistListADASToastYellow.clear();
    m_wMsgDispHistListADASToastGreen.clear();
    m_wMsgDispHistListCardRed.clear();
    emit PropertyChange(PROPERTYID_POPUP_REDCARD_LISTLENTH,m_wMsgDispHistListCardRed.length());
    m_wMsgDispHistListCardYellow.clear();
    emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_LISTLENTH,m_wMsgDispHistListCardYellow.length());
    m_wMsgDispHistListCardYellow_read.clear();
    m_CurrentPopToast1 = &CurrentPopupNon;
//    m_CurrentPopToast2 = &CurrentPopupNon;
    m_CurrentPopAdasToast = &CurrentPopupNon;
    m_TimerCntNormalToast1 = 0;
//    m_TimerCntNormalToast2 = 0;

    m_wMsgOccurpHistListToast.fill(0, POP_WMSG_CATEGORY_NUM * POP_PRIORITY_LEVEL_HIST_LIMIT);


    emit sendToOtherCtrl(HMI_MSGNAME_HAVEREAD,1);

//    PopupControl::instance()->clearBackupList();


    //必须在数据清空后,处理当前pop
    if(m_CurrentPop->category != POP_WMSG_CATEGORY_NUM)
    {
        bool meetPower = matchPower(m_CurrentPop);

        if(false == meetPower)
        {
            hidePopUp(m_CurrentPop);
        }
        else{
            //保持显示
//            int index = static_cast<int>(m_CurrentPop->priorityvalue-1);
//            int category = static_cast<int>(m_CurrentPop->category);

//            if(category == POP_WMSG_CATEGORY_A){
//                m_wMsgDispHistListCardRed.append(const_cast<Popup *>(m_CurrentPop));
//            }
//            else if(category == POP_WMSG_CATEGORY_B){
//                m_wMsgDispHistListCardYellow.append(const_cast<Popup *>(m_CurrentPop));
//            }
//            m_wMsgDispHistListToast.append(const_cast<Popup *>(pop)); // 不能放
        }
    }

//    if(m_CurrentPopToast2->category != POP_WMSG_CATEGORY_NUM)
//    {
//        bool meetPower = matchPower(m_CurrentPopToast2);
//        if(false == meetPower)
//        {
//            g_currentToast2PopNeedOff = 0;
//            handleToast2Action();
//        }
//        else{
//            //保持显示
////            m_wMsgOccurpHistListToast[static_cast<int>((m_CurrentPopToast2->priorityvalue) - 1)] = 0x01;
//        }
//    }

    if(m_CurrentPopToast1->category != POP_WMSG_CATEGORY_NUM)
    {
        bool meetPower = matchPower(m_CurrentPopToast1);
        if(false == meetPower)
        {
            g_currentToast1PopNeedOff = 0;
            handleToast1Action();
        }
        else{
            //保持显示
//            m_wMsgOccurpHistListToast[static_cast<int>((m_CurrentPopToast1->priorityvalue) - 1)] = 0x01;
        }
    }

    triggerTimeout100ms();
}
// HK键处理 来自gui的线程
bool PopupStrategy::triggerHardKey(int keyValue, int type){
    QMutexLocker _lock(m_mutex);
    Q_UNUSED(_lock)
    if(HDKEY_DOWN == keyValue && KEY_OFF == type) {//短按下翻页
        if(m_CurrentPop->category == POP_WMSG_CATEGORY_A)
        {
            if(m_CurrentPopIndex <= 0){

                m_CurrentPopIndex = m_wMsgDispHistListCardRed.length() - 1;
            }
            else{
                m_CurrentPopIndex--;
            }

            m_RedCardIndex = m_wMsgDispHistListCardRed.length()-1-m_CurrentPopIndex;
            emit PropertyChange(PROPERTYID_POPUP_REDCARD_CURRENTINDEX,m_RedCardIndex);
            showPopUp(m_wMsgDispHistListCardRed.at(m_CurrentPopIndex));
            return true;
        }
        else if(m_CurrentPop->category == POP_WMSG_CATEGORY_B)
        {
            if(g_hideAllYellowCard)
            {
                return false;
            }
            if(m_CurrentPopIndex <= 0){

                m_CurrentPopIndex = m_wMsgDispHistListCardYellow.length() - 1;
            }
            else{
                m_CurrentPopIndex--;
            }

            m_YellowCardIndex = m_wMsgDispHistListCardYellow.length()-1-m_CurrentPopIndex;
            emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_CURRENTINDEX,m_YellowCardIndex);
            showPopUp(m_wMsgDispHistListCardYellow.at(m_CurrentPopIndex));
            return true;
        }
        return false;
    }
    else if(HDKEY_UP == keyValue && KEY_OFF == type) {
        if(m_CurrentPop->category == POP_WMSG_CATEGORY_A)
        {
            if(m_CurrentPopIndex >= m_wMsgDispHistListCardRed.length() - 1){
                m_CurrentPopIndex = 0;
            }
            else{
                m_CurrentPopIndex++;
            }

            m_RedCardIndex = m_wMsgDispHistListCardRed.length()-1-m_CurrentPopIndex;

            emit PropertyChange(PROPERTYID_POPUP_REDCARD_CURRENTINDEX,m_RedCardIndex);
            showPopUp(m_wMsgDispHistListCardRed.at(m_CurrentPopIndex));
            return true;
        }
        else if(m_CurrentPop->category == POP_WMSG_CATEGORY_B)
        {
            if(g_hideAllYellowCard)
            {
                return false;
            }
            if(m_CurrentPopIndex >= m_wMsgDispHistListCardYellow.length() - 1){
                m_CurrentPopIndex = 0;
            }
            else{
                m_CurrentPopIndex++;
            }

            m_YellowCardIndex = m_wMsgDispHistListCardYellow.length()-1-m_CurrentPopIndex;

            emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_CURRENTINDEX,m_YellowCardIndex);
            showPopUp(m_wMsgDispHistListCardYellow.at(m_CurrentPopIndex));
            return true;
        }
        return false;
    }
    if(m_wMsgDispHistListCardYellow.length() > 0){
        if(HDKEY_DOWN == keyValue && KEY_OUT_OFF == type)//长按下 隐藏
        {
            if(!g_hideAllYellowCard)
            {
                setYellowCardVisible();
                return true;
            }
        }
        else if(HDKEY_UP == keyValue  && KEY_OUT_OFF == type)//长按上 显示
        {
            if(g_hideAllYellowCard)
            {
                setYellowCardVisible();
                return true;
            }
        }
    }
    return false;
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  calcCurrentPopDisTime
 *  Description:  计算当前pop显示时长
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void PopupStrategy::calcCurrentPopDisTime()
{
    //当前有pop
    bool needReset = false;
    if(m_CurrentPop->category != POP_WMSG_CATEGORY_NUM)
    {
        if(POWERMODE_D1 == m_powermode || POWERMODE_D2 == m_powermode)
        {
            if(POP_WMSG_CATEGORY_A == m_CurrentPop->category || POP_WMSG_CATEGORY_B == m_CurrentPop->category)
            {
                if(m_TimerCntNormal >= POP_D1_A_TIMEMAX)
                {
                    //end
                    needReset = true;
                }
            }
            else{
                //C类报警优先级最高且显示累计3秒结束
                if(m_TimerCntNormal >= POP_D1_C_TIMEMAX)
                {
                    //end
                    needReset = true;
                }
            }
        }
//        else if(POWERMODE_D2 == m_powermode)
//        {
//            //3
//            if(m_TimerCntNormal >= POP_D2_A_TIMEMAX)
//            {
//                //end
//                needReset = true;
//            }
//        }
    }

    //显示显示时间够了
//    if(needReset)
//    {
////        m_wMsgDispHistList[static_cast<int>(m_CurrentPop->category)][m_CurrentPop->priorityvalue-1] = 0x0;
//        hidePopUp(m_CurrentPop);
//    }
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  isExistInLoopList
 *  Description:  查询是否在循环队列存在
 *	Return:
 *          true: 存在
 *          false: 不存在
 *  Param:
            pop: pop
 * =====================================================================================
 */
bool PopupStrategy::isExistInLoopList(Popup *pop)
{
    (void)pop;
//    foreach (Popup* p, m_loopPop) {
//        if(p->wMsgID == pop->wMsgID)
//        {
//            return true;
//        }
//    }
    return false;
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  isExistInFaultList
 *  Description:  查询是否在查询列表存在
 *	Return:
 *          true: 存在
 *          false: 不存在
 *  Param:
            pop: pop
 * =====================================================================================
 */
bool PopupStrategy::isExistInFaultList(Popup *pop)
{
    (void)pop;
//    foreach (Popup p, m_faultQueryPop) {
//        if(p.wMsgID == pop->wMsgID)
//        {
//            return true;
//        }
//    }
    return false;
}

void PopupStrategy::setYellowCardVisible()
{
    g_hideAllYellowCard = !g_hideAllYellowCard;
    emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_HIDELIST,g_hideAllYellowCard);
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleTyre
 *  Description:  胎压逻辑处理
 *	Return:
 *          none: none
 *  Param:
            popCount:      popCount
            soundCount:     soundCount
 * =====================================================================================
 */
void PopupStrategy::handleTyre(Popup* pop)
{
    (void)pop;
}

void PopupStrategy::handleSeatbelt(Popup *pop)
{
    (void)pop;
}

//报警列表中解除(某轮胎)胎压相关文言
void PopupStrategy::handleOffTyre(Popup *pop)
{
    (void)pop;
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleCarDoor
 *  Description:  车门逻辑处理
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void PopupStrategy::handleCarDoor()
{
}
/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleCarDoorSound
 *  Description:  车门声音逻辑处理
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void PopupStrategy::handleCarDoorSound()
{
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  handleBrakeLevel
 *  Description:  手刹报警
 *	Return:
 *          none: none
 *  Param:
            none: none
 * =====================================================================================
 */
void PopupStrategy::handleBrakeLevel()
{
//    if(1== 0x0){
////        PopupDisplayStrategyPopup_EPB();
//    }
//    if(0x01 == _c_MSG_MCU_2_msgType_Backup.Signals.MCU_Brake_fluid_Pin7){
//        ////updateDisplayList(&PopupB10, POP_ALARM_ON);
//    }
//    else{
//        ////updateDisplayList(&PopupB10, POP_ALARM_OFF);
//    }
}
//废弃
void PopupStrategy::handleTyrePop()
{
}

void PopupStrategy::handleTyreShow()
{

}

void PopupStrategy::handleToast1Action()
{
    hidePopupToast(m_CurrentPopToast1);
    m_CurrentPopToast1 = &CurrentPopupNon;
    m_TimerCntNormalToast1 = 0;
}

//void PopupStrategy::handleToast2Action()
//{
//    hidePopupToast(m_CurrentPopToast2);
//    m_CurrentPopToast2 = &CurrentPopupNon;
//    m_TimerCntNormalToast2 = 0;
//}

void PopupStrategy::handleAdasToast(const Popup* pop)
{
    hidePopupADASToast(pop);
    m_TimerCntNormalAdas = 0;
    m_CurrentPopAdasToast = &CurrentPopupNon;
}

void PopupStrategy::showVolume(const Popup* pop)
{
    m_CurrentPopToast1 = const_cast<Popup *>(pop);
    g_currentToast1PopNeedOff = 0;
    showPopupToast(m_CurrentPopToast1);
    m_TimerCntNormalVolume = 0;
}

void PopupStrategy::hideVolume(const Popup *pop)
{
    hidePopupToast(m_CurrentPopToast1);
    m_CurrentPopToast1 = &CurrentPopupNon;
    m_TimerCntNormalVolume = 0;
}
void PopupStrategy::showPopUp(const Popup* pop){
    m_CurrentPop = const_cast<Popup *>(pop);
    m_TimerCntNormal = 0;
    if(pop->symbol == "tire_car.png")//胎压文言
    {
        if(PopupControl::instance()->tyreNameList.length() >0)
        {
            g_currenTyreCardIndex = PopupControl::instance()->tyreNameList.length() - 1;
            m_TimerCntNormalTyre = 0;
            m_CurrentPop->name = PopupControl::instance()->tyreNameList[g_currenTyreCardIndex];
        }
    }
    emit PropertyChange(m_CurrentPop);
}

void PopupStrategy::hidePopUp(const Popup* pop){
    (void)pop;
    if(m_CurrentPop == NULL) return;

    if(m_CurrentPop->category != POP_WMSG_CATEGORY_NUM){
        m_CurrentPop = &CurrentPopupNon;
        emit PropertyChange(&CurrentPopupNon);

        m_TimerCntNormal = 0;
        //TODO 需要显示下一个pop
        displayNextPopFromDispList(pop);
    }
}

//重复报警
void PopupStrategy::multiWarning(const Popup *pop)
{
//    QMutexLocker _lock(m_mutex);
//    Q_UNUSED(_lock)

//    int popHistoryOpretion = m_wMsgOccurpHistList[static_cast<int>(pop->category)].at(pop->priorityvalue-1);
//    if(1 == popHistoryOpretion){
////        reWarning(pop);
//        updateDisplayList(pop, POP_ALARM_ON);
//    }
//    else{
//        //new
//        updateDisplayList(pop, POP_ALARM_ON);
//    }
}

void PopupStrategy::reWarning(const Popup *pop)
{
    if(m_CurrentPop->category == POP_WMSG_CATEGORY_NUM){
        m_TimerCntNormal = 0;
        //文字更新？
    }
    else{
        updateDisplayList(pop, POP_ALARM_OFF);
        updateDisplayList(pop, POP_ALARM_ON);
    }
}

void PopupStrategy::hidePopupToast(const Popup *pop)
{
    int category = pop->category;
    emit PropertyChange_hide_toast(pop->name, pop->symbol,category);
}

void PopupStrategy::showPopupToast(const Popup *pop)
{
    int category = pop->category;
    emit PropertyChange_show_toast(pop->name, pop->symbol,category);
}

void PopupStrategy::showPopupADASToast(const Popup *pop)
{
    if(m_CurrentPopAdasToast->category != POP_WMSG_CATEGORY_NUM
            && m_CurrentPopAdasToast->priorityvalue != pop->priorityvalue)//取消上一个文言
    {
        handleAdasToast(m_CurrentPopAdasToast);
    }
    m_CurrentPopAdasToast = const_cast<Popup *>(pop);
    m_TimerCntNormalAdas = 0;
//    g_currentAdasToastPopNeedOff = 0;
    int category = pop->category;
    emit PropertyChange_show_adastoast(pop->name, pop->symbol,category);
}

void PopupStrategy::hidePopupADASToast(const Popup *pop)
{
    if(pop->category != POP_WMSG_CATEGORY_NUM)
    {
        int category = pop->category;
        emit PropertyChange_hide_adastoast(pop->name, pop->symbol,category);
    }
}

void PopupStrategy::handleDynamicPopText()
{
    if(m_CurrentPopAdasToast->priorityvalue == ACC_WARN_POP){
        emit PropertyChange_show_adastoast(m_CurrentPopAdasToast->name, m_CurrentPopAdasToast->symbol,m_CurrentPopAdasToast->category);
    }
}

void PopupStrategy::handleToast100ms()
{
    // 计时,控制toast显示逻辑
    if(m_CurrentPopToast1->category == POP_WMSG_CATEGORY_VOLUME) return;

    m_TimerCntNormalToast1++;
//    m_TimerCntNormalToast2++;

    // 计时
    if(m_TimerCntNormalToast1 >= 20 && checkPopIsNone(m_CurrentPopToast1) == false){
        // hide toast1 action
        handleToast1Action();
    }
//    if(m_TimerCntNormalToast2 >= 50 && checkPopIsNone(m_CurrentPopToast2) == false){
//        // hide toast1 action
//        handleToast2Action();
//    }

    // 初次显示
    if(checkPopIsNone(m_CurrentPopToast1)){
        // Toast1 is
        if(m_wMsgDispHistListToast.length() > 0){
            // 可以显示一个pop
            m_CurrentPopToast1 = m_wMsgDispHistListToast.takeAt(0);
            bool meetPower = matchPower(m_CurrentPopToast1);
            if(meetPower)
            {
                g_currentToast1PopNeedOff = 0;
                showPopupToast(m_CurrentPopToast1);
                m_TimerCntNormalToast1 = 0;
            }
        }
    }

//    if(checkPopIsNone(m_CurrentPopToast2)){
//        // Toast2 is 空
//        if(m_wMsgDispHistListToast.length() > 0){
//            // 可以显示一个pop
//            m_CurrentPopToast2 = m_wMsgDispHistListToast.takeAt(0);
//            bool meetPower = matchPower(m_CurrentPopToast2);
//            if(meetPower)
//            {
//                g_currentToast2PopNeedOff = 0;
//                showPopupToast(m_CurrentPopToast2);
//                m_TimerCntNormalToast2 = 0;
//            }
//        }
//    }

    if(g_currentToast1PopNeedOff == 1)
    {
        if(m_TimerCntNormalToast1 >= 10)
        {
            g_currentToast1PopNeedOff = 0;
            handleToast1Action();

            // 3 -> 1
            if(m_wMsgDispHistListToast.length() > 0){
                // 可以显示一个pop
                m_CurrentPopToast1 = m_wMsgDispHistListToast.takeAt(0);
                if(matchPower(m_CurrentPopToast1))
                {
                    showPopupToast(m_CurrentPopToast1);
                    m_TimerCntNormalToast1 = 0;
                }
            }
        }
    }

    //    if(g_currentToast2PopNeedOff == 1)
    //    {
    //        g_currentToast2PopNeedOff = 0;
    //        handleToast2Action();
    //        // 3 -> 2
    //        if(m_wMsgDispHistListToast.length() > 0){
    //            // 可以显示一个pop
    //            m_CurrentPopToast2 = m_wMsgDispHistListToast.takeAt(0);
    //            if(matchPower(m_CurrentPopToast1))
    //            {
    //                showPopupToast(m_CurrentPopToast1);
    //                m_TimerCntNormalToast1 = 0;
    //            }
    //        }
    //    }
}

void PopupStrategy::handleAdasToast100ms()
{
    //如果有ADASToast展示的话
    if(m_CurrentPopAdasToast->category >= POP_WMSG_CATEGORY_ADAS_A
            && m_CurrentPopAdasToast->category <= POP_WMSG_CATEGORY_ADAS_C)
    {
        //计时累计
        m_TimerCntNormalAdas++;
        //如果当前展示的是最后一个ADASToast且已经被消除且展示满2秒
        if(m_TimerCntNormalAdas>=20&&m_wMsgDispHistListADASToastRed.size()+m_wMsgDispHistListADASToastYellow.size()+m_wMsgDispHistListADASToastGreen.size()==0)
        {
            //隐藏当前ADASToast
              handleAdasToast(m_CurrentPopAdasToast);
        }
        //如果展示的是绿ADASToast的话
        if(m_CurrentPopAdasToast->category == POP_WMSG_CATEGORY_ADAS_C)
        {
            //如果展示满5秒钟
            if(m_TimerCntNormalAdas >= 50)
            {
                //找到这个ADASToast，消除并隐藏
                for(int i = 0; i < m_wMsgDispHistListADASToastGreen.length(); i++){
                    if(m_wMsgDispHistListADASToastGreen.at(i) == m_CurrentPopAdasToast){
                        m_wMsgDispHistListADASToastGreen.removeAt(i);
                        handleAdasToast(m_CurrentPopAdasToast);
                        break;
                    }
                }
            }
        }
    }
    else{
        m_TimerCntNormalAdas = 0;
    }
}

void PopupStrategy::handleVolumeToast100ms()
{
    if(m_CurrentPopToast1->category == POP_WMSG_CATEGORY_VOLUME)
    {
        m_TimerCntNormalVolume ++;
        if(m_TimerCntNormalVolume >= 20)
        {
            hideVolume(m_CurrentPopToast1);
        }
    }
    else{
        m_TimerCntNormalVolume = 0;
    }
}

void PopupStrategy::handleTyre5secends()
{
    QMutexLocker _lock(m_mutex);
    Q_UNUSED(_lock)

    if(m_CurrentPop->symbol == "tire_car.png" && g_hideAllYellowCard == false)
    {
        m_TimerCntNormalTyre ++;
        int tyreNameListLenth = PopupControl::instance()->tyreNameList.length();
        if(tyreNameListLenth > 0)
        {
            if(m_TimerCntNormalTyre >= 10)//显示下一个胎压文言
            {
                g_currenTyreCardIndex --;

                if(g_currenTyreCardIndex < 0)
                {
                    g_currenTyreCardIndex = tyreNameListLenth -1;
                }

                m_CurrentPop->name = PopupControl::instance()->tyreNameList[g_currenTyreCardIndex];
                emit PropertyChange(m_CurrentPop);
                m_TimerCntNormalTyre = 0;
            }
            else{
                return;
            }
        }
    }
    else{
        m_TimerCntNormalTyre = 0;
    }
}

void PopupStrategy::updateSound(const Popup* newPop, const int state){
    if(NULL == newPop){return;}

    //Send out alarm sound
    if((NULL != newPop->ptSoundInc)
            && (newPop->ptSoundInc->soundType != AUDIO_INDEX_MAX)){
//        audio_client_Play(newPop->ptSoundInc->soundType, AUDIO_PLAY);
        HMIAudioCtrl::setAudioStatByPower(static_cast<HMIAudioCtrl::WARNING_STATE>(newPop->audio_flag), newPop->ptSoundInc->soundType, static_cast<Audio_ReqCmd>(state));
    }
}

bool PopupStrategy::matchPower(const Popup *pop)
{
    bool meetPower = false;
    if(pop == NULL) return meetPower;

    if(m_powermode == static_cast<int>(POWERMODE_ANIMATION))
    {
        meetPower = false;
    }
    else{
        meetPower = true;
    }
//    if(POWERMODE_D1 == m_powermode)
//    {
//        if(POP_PM_D1 == pop->dispPowerMode || POP_PM_D1_D2 == pop->dispPowerMode)
//        {
//            meetPower = true;
//        }
//    }
//    else if(POWERMODE_D2 == m_powermode)
//    {
//        if(POP_PM_D2 == pop->dispPowerMode || POP_PM_D1_D2 == pop->dispPowerMode)
//        {
//            meetPower = true;
//        }
//    }
    return meetPower;
}


/*
 * ===  FUNCTION  ======================================================================
 *  Name:  //updateDisplayListTable
 *  Description:  更新显示队列表格,都是从can信号方向来的处理,策略内部调用该函数会有问题
 *	Return:
 *          none: none
 *  Param:
            pop: pop
            opretion: on/off
 * =====================================================================================
 */
//#最短1s
//#循环A
//#故障列表
//#同优先级pop
//#安全带重新报警
void PopupStrategy::updateDisplayListTable(const Popup* pop, POPALARMEVENT opretion){
    QMutexLocker _lock(m_mutex);
    Q_UNUSED(_lock)

    int category = static_cast<int>(pop->category); //a,b,c
    int index  = static_cast<int>((pop->priorityvalue) - 1);  //一维数组,(0:100)(101:200)(201:300)

    int cardRedlen = m_wMsgDispHistListCardRed.length();
    int carYellowlen = m_wMsgDispHistListCardYellow.length();
    int carYellowlen_red = m_wMsgDispHistListCardYellow_read.length();
    bool high_level = handlePriorityForDisplay(pop);
    int DisHistToastlen = m_wMsgDispHistListToast.length();
    int DisHistADASToastRedlen = m_wMsgDispHistListADASToastRed.length();
    int DisHistADASToastYellowlen = m_wMsgDispHistListADASToastYellow.length();
    int DisHistADASToastGreenlen = m_wMsgDispHistListADASToastGreen.length();

    bool meetPowerToast1 = matchPower(m_CurrentPopToast1);
//    bool meetPowerToast2 = matchPower(m_CurrentPopToast2);
    bool meetPower = false;

    switch(opretion)
    {
    case POP_ALARM_ON:
        // 发生队列
        m_wMsgOccurpHistListToast[index] = 0x01;

        // 显示队列
        if(category == POP_WMSG_CATEGORY_A){
            m_wMsgDispHistListCardRed.append(const_cast<Popup *>(pop));
            emit PropertyChange(PROPERTYID_POPUP_REDCARD_LISTLENTH,m_wMsgDispHistListCardRed.length());
        }
        else if(category == POP_WMSG_CATEGORY_B){
            m_wMsgDispHistListCardYellow.append(const_cast<Popup *>(pop));
            emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_LISTLENTH,m_wMsgDispHistListCardYellow.length());
        }
        else{}

        // toast update
        //红黄卡片不显示toast
        if(category < POP_WMSG_CATEGORY_C)
        {

        }else if(category < POP_WMSG_CATEGORY_ADAS_A)
        {
            if(pop->symbol == "tire_car.png")
            {}
            else{
                m_wMsgDispHistListToast.append(const_cast<Popup *>(pop));
                ptPopupTbl_toast[index] = const_cast<Popup *>(pop);  //动态存储pop
            }
        }
        else{
            if(category < POP_WMSG_CATEGORY_VOLUME)// adas toast update
            {
                //按优先级顺序，判断是否需要展示该ADASToast
                if(category == POP_WMSG_CATEGORY_ADAS_A)
                {
                    m_wMsgDispHistListADASToastGreen.clear();
                    m_wMsgDispHistListADASToastRed.append(const_cast<Popup *>(pop));
                    showPopupADASToast(pop);
                }
                if(category == POP_WMSG_CATEGORY_ADAS_B)
                {
                    m_wMsgDispHistListADASToastGreen.clear();
                    m_wMsgDispHistListADASToastYellow.append(const_cast<Popup *>(pop));
                    if(m_wMsgDispHistListADASToastRed.size()==0)
                        showPopupADASToast(pop);
                }
                if(category == POP_WMSG_CATEGORY_ADAS_C)
                {
                     if(m_wMsgDispHistListADASToastRed.size()==0&&m_wMsgDispHistListADASToastYellow.size()==0)
                    {
                        m_wMsgDispHistListADASToastGreen.append(const_cast<Popup *>(pop));
                        showPopupADASToast(pop);
                    }
                }
            }
            else{//音量
                showVolume(pop);
            }
        }

        //报警音判断的时机根据CAN信号的触发时机进行确认
        meetPower = matchPower(pop);
        if(meetPower)
        {
            updateSound(pop, AUDIO_PLAY);
            //优先级判断
            if(category < POP_WMSG_CATEGORY_C)
            {
                if(high_level){
                    if(m_wMsgDispHistListCardRed.length() > 0){
                        m_CurrentPopIndex = m_wMsgDispHistListCardRed.length() -1;
                        m_RedCardIndex = m_wMsgDispHistListCardRed.length() -1 -m_CurrentPopIndex;
                        emit PropertyChange(PROPERTYID_POPUP_REDCARD_CURRENTINDEX,m_RedCardIndex);
                    }
                    else{
                        m_CurrentPopIndex = m_wMsgDispHistListCardYellow.length() -1;
                    }

                    showPopUp(pop);
                    //弹出新的黄色卡片，隐藏的列表需要显示
                    if(pop->category == POP_WMSG_CATEGORY_B)
                    {
                        if(g_hideAllYellowCard)
                        {
                            setYellowCardVisible();
                        }
                    }
                }
            }
        }
        break;
    case POP_ALARM_OFF:
        //stop sound
        updateSound(pop, AUDIO_STOP);
        // 发生队列
        m_wMsgOccurpHistListToast[index] = 0x0;

        // 显示队列
        if(category == POP_WMSG_CATEGORY_A){
            for(int i = 0; i < cardRedlen; i++){
                if(m_wMsgDispHistListCardRed.at(i) == const_cast<Popup *>(pop)){
                    gPopAlarmOffIndex = i;
                    // 因为A可以翻页,不一定显示最后一个
                    if(m_wMsgDispHistListCardRed.length() > 0){
                        // 通过显示下一个pop来更新 m_CurrentPopIndex
                        m_CurrentPopIndex = m_wMsgDispHistListCardRed.length()-1;
                        m_RedCardIndex = m_wMsgDispHistListCardRed.length()-1-m_CurrentPopIndex;
                        emit PropertyChange(PROPERTYID_POPUP_REDCARD_CURRENTINDEX,m_RedCardIndex);
                    }
                    else if(m_wMsgDispHistListCardYellow.length() > 0){
                        m_CurrentPopIndex = m_wMsgDispHistListCardYellow.length()-1;
                    }
                    m_wMsgDispHistListCardRed.removeAt(i);
                    emit PropertyChange(PROPERTYID_POPUP_REDCARD_LISTLENTH,m_wMsgDispHistListCardRed.length());
                    hidePopUp(pop);
                    break;
                }
            }
        }
        else if(category == POP_WMSG_CATEGORY_B){
            bool state = true;
            for(int i = 0; i < carYellowlen; i++){
                if(m_wMsgDispHistListCardYellow.at(i) == const_cast<Popup *>(pop)){
                    m_wMsgDispHistListCardYellow.removeAt(i);
                    emit PropertyChange(PROPERTYID_POPUP_YELLOWCARD_LISTLENTH,m_wMsgDispHistListCardYellow.length());
                    if(m_CurrentPop->category == POP_WMSG_CATEGORY_A)
                    {}
                    else{
                        hidePopUp(pop);
                    }
                    state = false;
                    break;
                }
            }

            if(state)
            {
                for(int i = 0; i < carYellowlen_red; i++){
                    if(m_wMsgDispHistListCardYellow_read.at(i) == const_cast<Popup *>(pop)){
                        m_wMsgDispHistListCardYellow_read.removeAt(i);
                        emit sendToOtherCtrl(HMI_MSGNAME_HAVEREAD,1);
                        break;
                    }
                }
            }
        }

        // toast update
        // 只会解除列表里的
        if(category < POP_WMSG_CATEGORY_ADAS_A)
        {
            for(int i = 0; i < DisHistToastlen; i++){
                if(m_wMsgDispHistListToast.at(i) == const_cast<Popup *>(pop)){
                    m_wMsgDispHistListToast.removeAt(i);
                    break;
                }
            }

    //        // 解除当前pop
    //        hidePopUp(pop);

            // 解除当前toast1,toast2
            if(const_cast<Popup *>(pop) == m_CurrentPopToast1)
            {
                // hide toast1 action
                if(m_TimerCntNormalToast1 >= 10)
                {
                    handleToast1Action();

                    // 3 -> 1
                    if(m_wMsgDispHistListToast.length() > 0){
                        // 可以显示一个pop
                        m_CurrentPopToast1 = m_wMsgDispHistListToast.takeAt(0);
                        if(meetPowerToast1)
                        {
                            showPopupToast(m_CurrentPopToast1);
                            m_TimerCntNormalToast1 = 0;
                        }
                    }
                    g_currentToast1PopNeedOff = 0;
                }
                else{
                    g_currentToast1PopNeedOff = 1;
                }
            }
//            else if(const_cast<Popup *>(pop) == m_CurrentPopToast2){
//                if(m_TimerCntNormalToast2 >= 10)
//                {
//                    handleToast2Action();
//                    // 3 -> 2
//                    if(m_wMsgDispHistListToast.length() > 0){
//                        // 可以显示一个pop
//                        m_CurrentPopToast2 = m_wMsgDispHistListToast.takeAt(0);
//                        if(meetPowerToast1)
//                        {
//                            showPopupToast(m_CurrentPopToast1);
//                            m_TimerCntNormalToast1 = 0;
//                        }
//                    }
//                    g_currentToast2PopNeedOff = 0;
//                }
//                else{
//                    g_currentToast2PopNeedOff = 1;
//                }
//            }
        }
        else if(category >= POP_WMSG_CATEGORY_ADAS_A
                && category < POP_WMSG_CATEGORY_VOLUME)//adas toast
        {
            //找到该ADASToast并消除
            if(category == POP_WMSG_CATEGORY_ADAS_A)
            {
                for(int i = 0; i < DisHistADASToastRedlen; i++){
                    if(m_wMsgDispHistListADASToastRed.at(i) == const_cast<Popup *>(pop)){
                        m_wMsgDispHistListADASToastRed.removeAt(i);
                        break;
                    }
                }
            }
            if(category == POP_WMSG_CATEGORY_ADAS_B)
            {
                for(int i = 0; i < DisHistADASToastYellowlen; i++){
                    if(m_wMsgDispHistListADASToastYellow.at(i) == const_cast<Popup *>(pop)){
                        m_wMsgDispHistListADASToastYellow.removeAt(i);
                        break;
                    }
                }
            }
            if(category == POP_WMSG_CATEGORY_ADAS_C)
            {
                for(int i = 0; i < DisHistADASToastGreenlen; i++){
                    if(m_wMsgDispHistListADASToastGreen.at(i) == const_cast<Popup *>(pop)){
                        m_wMsgDispHistListADASToastGreen.removeAt(i);
                        break;
                    }
                }
            }

            if(m_CurrentPopAdasToast->priorityvalue == pop->priorityvalue)//消隐当前adas toast
            {  
                //按照优先级找到下一个该展示的adastoast
                if(m_wMsgDispHistListADASToastRed.size()>0)
                {
                    showPopupADASToast(m_wMsgDispHistListADASToastRed.last());
                }else if(m_wMsgDispHistListADASToastYellow.size()>0){
                    showPopupADASToast(m_wMsgDispHistListADASToastYellow.last());

                }else if(m_wMsgDispHistListADASToastGreen.size()>0){
                    showPopupADASToast(m_wMsgDispHistListADASToastGreen.last());
                }else{
                    //没有可展示的adastoast了。判断是否展示足够时间后隐藏
                    if(m_TimerCntNormalAdas>=20)
                         handleAdasToast(m_CurrentPopAdasToast);
                }
            }
        }

        break;
    default:
        qInfo()<<"opretion is error! value:"<<opretion;
        break;
    }
}

/*
 * ===  FUNCTION  ======================================================================
 *  Name:  //updateDisplayList
 *  Description:  更新显示队列
 *	Return:
 *          none: none
 *  Param:
            pop: pop
            opretion: 报警状态
 * =====================================================================================
 */
void PopupStrategy::updateDisplayList(const Popup* pop, POPALARMEVENT opretion){

    if(m_autoCheckState == AUTOCHECK_START)
    {
        return;
    }

    int index  = (pop->priorityvalue) - 1;  // a1-a100, b101-b200, c201-c300

    int popHistoryOpretion_toast = m_wMsgOccurpHistListToast[index];
    //需要check报警发生队列,防止重复报警
    if((0 == popHistoryOpretion_toast && POP_ALARM_ON == opretion)  // warnning: un-occurred -> occurred
            || (1 == popHistoryOpretion_toast && POP_ALARM_OFF == opretion) ) // warnning: occurred    -> un-occurred
    {
        updateDisplayListTable(pop,opretion);
    }
}

//遍历显示队列 显示下一个pop
//前置条件: 无当前pop
void PopupStrategy::displayNextPopFromDispList(const Popup* pop)
{
    // input 1. offAB 2. keyB => hide => displayNextPopFromDispList
    // A B
    if(m_wMsgDispHistListCardRed.length() > 0){
        // 因为A可以翻页,不一定显示最后一个
        // A1 A2 A3
//        解除位置<cur m_CurrentPopIndex 	-1
//        解除位置=cur m_CurrentPopIndex 	-1
//        解除位置>cur m_CurrentPopIndex 	0
        if(pop->category == POP_WMSG_CATEGORY_A){
            // 说明case：offA
            if(gPopAlarmOffIndex <= m_CurrentPopIndex){
                m_CurrentPopIndex --;
            }
            else{
                // nothing
            }

            // 容错
            if(m_CurrentPopIndex < 0){
                m_CurrentPopIndex = m_wMsgDispHistListCardRed.length() - 1;
            }

            m_RedCardIndex = m_wMsgDispHistListCardRed.length()-1-m_CurrentPopIndex;
            emit PropertyChange(PROPERTYID_POPUP_REDCARD_CURRENTINDEX,m_RedCardIndex);
            showPopUp(m_wMsgDispHistListCardRed.at(m_CurrentPopIndex));
        }
        else{
            // b c 不需要处理
        }
    }
    else if(m_wMsgDispHistListCardYellow.length() > 0){
        showPopUp(m_wMsgDispHistListCardYellow.at(m_wMsgDispHistListCardYellow.length()-1));
    }
}

//优先级判断 打断
bool PopupStrategy::handlePriorityForDisplay(const Popup* newPop)
{
    // card
    if(m_CurrentPop->category != POP_WMSG_CATEGORY_NUM)
    {
        if(newPop->category == POP_WMSG_CATEGORY_A){
            return true;    //?->A
        }
        else if(newPop->category == POP_WMSG_CATEGORY_B){
            if(m_CurrentPop->category == POP_WMSG_CATEGORY_A){
                return false;   //A->B
            }
            return true;    //B->B
        }
        else{
            // c
            return false;
        }
    }
    else{
        //new pop
        return true;
    }
}

void PopupStrategy::handlefaultQueryPop()
{


}

bool PopupStrategy::handleTyreExitQueryPop(QString name)
{
    (void)name;
    return false;
}

//判断查询列表中要取消的报警是否是胎压报警
bool PopupStrategy::alarmOffHandleTyre(int wMsgID, Popup* p)
{
    (void)wMsgID;
    (void)p;
    return false;
}


