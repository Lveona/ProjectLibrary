#ifndef POPUPSTRATEGY_H
#define POPUPSTRATEGY_H

#include <QObject>
#include "Singleton.h"
#include <QVariant>

class Popup;
class QMutex;

#define MINUTE_TO_SEC(a)                    (a*60)
#define HOUR_TO_SEC(a)                      (a*60*60)

#define CREATE_WMSG_ID(category,priority)   (((category<<8) | priority) | 0x8000)
#define TAKE_CAREGORY(wMsgID)               static_cast<Type_uByte>((0x7F00 & wMsgID) >> 8)
#define TAKE_PRIORITY(wMsgID)               static_cast<Type_uByte>(0x00FF & wMsgID)

#define POP_COUTUP_ADJUST_MAX(a,b,max)      ((a+b)>max) ? max : (a+b)
#define POP_COUTUP_ADJUST_ROUND(a,b,max)    (a>=max)    ? 0   : (a+b)

#define POP_CHEKING_CAREGORY_PRIORITY_VALIDITY(caregory, priority) ((caregory >= POP_WMSG_CATEGORY_NUM)|| (priority >= POP_PRIORITY_LEVEL_NUM_MAX)) ? false : true

#define POP_PRIORITY_LEVEL_HIST_LIMIT              100       // Limit of A B C WarnningMessageNumber
#define POP_PRIORITY_LEVEL_NUM_MAX                 POP_PRIORITY_LEVEL_HIST_LIMIT       // MaxNumber of A B C WarnningMessage(!!!Must!!!)

#define POP_MESSAGEID_INVALID 		               0x7FFF	// Invalid MessageID
#define POP_RECOVERY_TIMER_SEC 		               60		// 60Sec
#define POP_TIMER_PLL				               10		// 定时器分频比: 1Sec/100msec = 10倍 100msec:ReciverCtrlTimerInvartal

#define POP_FATIGUE_REMINDER_INTERVAL_HOUR         4        // 4H
#define POP_FATIGUE_REMINDER_CANCEL_INTERVAL_HOUR  20       // 20min
#define POP_FATIGUE_REMINDER_DEFAULT_MILEAGE_TH    5000     // default Mileage Th:5000km


#define POP_D1_A_TIMEMAX    90000000 //test
#define POP_D1_C_TIMEMAX    50
#define POP_D2_A_TIMEMAX    30
#define POP_DIS_TIMEMIN     10


enum POPALARMEVENT {
    POP_ALARM_OFF = 0x00,            // 解除
    POP_ALARM_ON,                  // 发生

    POP_POPUP_TIMEOUT,              // 取消显示(T1/T2的显示时间已到TimeOut)
    POP_ALARM_CANCEL_ONE,           // 取消显示(短按确认键取消:消当前)
    POP_ALARM_CANCEL_ALL,           // 取消显示(长按确认键取消:全消)
    POP_ALARM_INTERRUPT_DISP_OFF    // 被高优先级POP打断而要消隐
};

enum POPMATCHPOWERMODE{
    POP_PM_D1  = 0x00,
    POP_PM_D2,
    POP_PM_D1_D2
};

enum POPCATEGORY {
    POP_WMSG_CATEGORY_A = 0x00,//red
    POP_WMSG_CATEGORY_B,    //yellow
    POP_WMSG_CATEGORY_C,    //green 只有toast
    POP_WMSG_CATEGORY_D,    //yellow 只有toast
    POP_WMSG_CATEGORY_ADAS_A,//red
    POP_WMSG_CATEGORY_ADAS_B,//yellow
    POP_WMSG_CATEGORY_ADAS_C,//green
    POP_WMSG_CATEGORY_VOLUME,//音量
    POP_WMSG_CATEGORY_NUM
};

enum PROPERTYID_POPUP{
    PROPERTYID_SEAT_DRIV_VISIBLE,
    PROPERTYID_SEAT_DRIV_COLOR,
    PROPERTYID_SEAT_PAS_VISIBLE,
    PROPERTYID_SEAT_PAS_COLOR,
    PROPERTYID_SEAT_RL_VISIBLE,
    PROPERTYID_SEAT_RL_COLOR,
    PROPERTYID_SEAT_RR_VISIBLE,
    PROPERTYID_SEAT_RR_COLOR,
    PROPERTYID_SEAT_RM_VISIBLE,
    PROPERTYID_SEAT_RM_COLOR,
    PROPERTYID_POPUP_LF_TEMP_WARNING,
    PROPERTYID_POPUP_RF_TEMP_WARNING,
    PROPERTYID_POPUP_RR_TEMP_WARNING,
    PROPERTYID_POPUP_LR_TEMP_WARNING,
    PROPERTYID_POPUP_LimitSpeed,
    PROPERTYID_POPUP_REDCARD_LISTLENTH,
    PROPERTYID_POPUP_YELLOWCARD_LISTLENTH,
    PROPERTYID_POPUP_REDCARD_CURRENTINDEX,
    PROPERTYID_POPUP_YELLOWCARD_CURRENTINDEX,
    PROPERTYID_POPUP_YELLOWCARD_HIDELIST,//true: 收起
    PROPERTYID_MAX
};

enum DYMANIC_POP{
    ACC_WARN_POP = 108,
};

class PopupStrategy:public QObject, public CSingleton<PopupStrategy>
{
    Q_OBJECT
    friend class CSingleton<PopupStrategy>;
public:
    PopupStrategy(){initlaize();}
    ~PopupStrategy(){
        delete PopupStrategy::instance();
    }
    int getPopById(int type, int id);
    int getTimerCntNormal(){return m_TimerCntNormal;}//获取当前pop显示时间

    void triggerTimeout500ms(void);
    void triggerTimeout100ms(void);
    void triggerPowerMode(int power);
    bool triggerHardKey(int keyValue,int type);
    void triggerAutoCheckState(int sts);
    void updateDisplayList(const Popup* pop, POPALARMEVENT opretion);

    void multiWarning(const Popup* pop);
    void showPopUp(const Popup* pop);

    void setYellowCardVisible();
    int m_autoCheckState;

private:
    void initlaize(void);
    void updateDisplayListTable(const Popup* pop, POPALARMEVENT opretion);

    void displayNextPopFromDispList(const Popup* pop);
    bool handlePriorityForDisplay(const Popup* newPop);
    void hidePopUp(const Popup* pop);
    void reWarning(const Popup* pop);

    void hidePopupToast(const Popup *pop);
    void showPopupToast(const Popup* pop);
    void showPopupADASToast(const Popup* pop);
    void hidePopupADASToast(const Popup* pop);
    void showPopupToastBefore(const Popup *pop);
    void handleDynamicPopText();
    void handleToast100ms();
    void handleAdasToast100ms();
    void handleVolumeToast100ms();
    void handleTyre5secends();

    void handleTyre(Popup* pop);
    void handleSeatbelt(Popup* pop);
    void handleOffTyre(Popup* pop);
    void handleCarDoor();
    void handleCarDoorSound();
    void handleBrakeLevel();
    void handleTyrePop();
    void handleTyreShow();
    void handleToast1Action();
    void handleToast2Action();
    void handleAdasToast(const Popup* pop);
    void showVolume(const Popup* pop);
    void hideVolume(const Popup* pop);

    void calcCurrentPopDisTime();
    bool isExistInLoopList(Popup* pop);
    bool isExistInFaultList(Popup* pop);

    void updateSound(const Popup* newPop, const int state);
    bool matchPower(const Popup* pop);
    void handlefaultQueryPop();
    bool handleTyreExitQueryPop(QString name);
    bool alarmOffHandleTyre(int wMsgID, Popup* p );

signals:
    void notifyWarningState(bool state);    //是否有报警信息
    void sendToOtherProcess(QString name, QVariant value);
    void sendToOtherCtrl(QString name, QVariant value);
    void PropertyChange(Popup*);
    void PropertyChange(int name,QVariant number);

    void PropertyChange_show_toast(QString name, QString iconname, int category);
    void PropertyChange_hide_toast(QString name, QString iconname, int category);
    void PropertyChange_show_adastoast(QString name, QString iconname, int category);
    void PropertyChange_hide_adastoast(QString name, QString iconname, int category);
    void Property_card_number();
private:
    int            m_TimerCntNormal;
    int            m_TimerCntNormalToast1;
    int            m_TimerCntNormalToast2;
    int            m_TimerCntNormalAdas;
    int            m_TimerCntNormalVolume;
//    QByteArray    m_wMsgOccurpHistList[POP_WMSG_CATEGORY_NUM];  //发生队列
//    QByteArray    m_wMsgDispHistList;    //显示队列 - card
//    QByteArray     m_wMsgOccurpHistListToast[POP_WMSG_CATEGORY_NUM * POP_PRIORITY_LEVEL_HIST_LIMIT];   //发生队列 用于过滤报警，可以不匹配优先级

    QList<Popup*>    m_wMsgDispHistListCardRed;    //显示队列 -  包括 红
    QList<Popup*>    m_wMsgDispHistListCardYellow; //显示队列 -  包括 黄
    QList<Popup*>    m_wMsgDispHistListToast;      //显示队列 - toast 白
    QList<Popup*>    m_wMsgDispHistListADASToastRed;  //显示队列 - adas toast 包括 红
    QList<Popup*>    m_wMsgDispHistListADASToastYellow;  //显示队列 - adas toast 包括 黄
    QList<Popup*>    m_wMsgDispHistListADASToastGreen;  //显示队列 - adas toast 包括 绿

    QByteArray       m_wMsgOccurpHistListToast;    //发生队列 包括卡片-toast
    QList<Popup*>       m_loopPop;
    QMutex*             m_mutex;
    int                 m_powermode;
    QList<Popup*>       m_popupC_CardList;

    int             m_CurrentPopIndex;
public:
    Popup*          m_CurrentPop;
    Popup*          m_CurrentPopToast1; // 1号位置
    Popup*          m_CurrentPopToast2; // 2号位置
    Popup*          m_CurrentPopAdasToast; // adas toast
    Popup*          m_OccurpHisPop;
    QList<Popup*>    m_wMsgDispHistListCardYellow_read;//黄色已读队列
    int             g_currenTyreCardIndex = 0;
    int             m_TimerCntNormalTyre;
};

#endif // POPUPSTRATEGY_H
