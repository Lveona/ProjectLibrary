#ifndef MANAGER_H
#define MANAGER_H

class QTimer;
class QByteArray;
class QObject;
class QQuickView;
class QThread;
class ManagerCustomTimer;
class MyShareMemory;
class PopupScreen;
class PopupControl;
class DiagScreen;
class DiagControl;
class ADASScreen;
class ADASControl;
class CarInfoScreen;
class CarInfoControl;
class SettingScreen;
class SettingControl;
class InterconnectScreen;
class InterconnectControl;
class HomeScreen;
class HomeControl;
class Update_Thread;
class HMICustomTimer;
class Worker;/*
class Popup;*/

#include <QThread>
#include "Singleton.h"
#include "BaseScreen.h"
#include "../popup/popup.h"

class Manager : public CBaseScreen, public CSingleton<Manager>
{
    Q_OBJECT
    friend class CSingleton<Manager>;
    Q_ENUMS(qmlPowerMode)
    Q_PROPERTY(int receiveCtrlPowerMode READ receiveCtrlPowerMode WRITE setReceiveCtrlPowerMode NOTIFY receiveCtrlPowerModeChanged)

    Q_PROPERTY(int isCarInfoScreenIndex READ isCarInfoScreenIndex WRITE setIsCarInfoScreenIndex NOTIFY isCarInfoScreenIndexChanged)
    Q_PROPERTY(int isCarInfoChildDirection READ isCarInfoChildDirection WRITE setIsCarInfoChildDirection NOTIFY isCarInfoChildDirectionChanged)
    Q_PROPERTY(int isCarInfoFaultChildIndex READ isCarInfoFaultChildIndex WRITE setIsCarInfoFaultChildIndex NOTIFY isCarInfoFaultChildIndexChanged)

    Q_PROPERTY(bool isWarningState READ isWarningState WRITE setIsWarningState NOTIFY isWarningStateChanged)    //未来迁移到pop
    Q_PROPERTY(bool updateScreenVisible READ updateScreenVisible WRITE setUpdateScreenVisible NOTIFY updateScreenVisibleChanged)
    Q_PROPERTY(int isMidAreaScreenIndex READ isMidAreaScreenIndex WRITE setIsMidAreaScreenIndex NOTIFY isMidAreaScreenIndexChanged)

    Q_PROPERTY(bool hmiScreenState READ hmiScreenState WRITE setHmiScreenState NOTIFY hmiScreenStateChanged)
    Q_PROPERTY(bool enterAnimStart READ enterAnimStart WRITE setEnterAnimStart NOTIFY enterAnimStartChanged)
    //版本 低配0,高配1
    Q_PROPERTY(int edition READ edition WRITE setEdition NOTIFY editionChanged)

    Q_PROPERTY(int isCarInfoFaultChildDirect READ isCarInfoFaultChildDirect WRITE setIsCarInfoFaultChildDirect NOTIFY isCarInfoFaultChildDirectChanged)

    Q_PROPERTY(QString updateVersion READ updateVersion WRITE setUpdateVersion NOTIFY updateVersionChanged)
    Q_PROPERTY(QString currentVersion READ currentVersion WRITE setCurrentVersion NOTIFY currentVersionChanged)
    Q_PROPERTY(QString popName READ popName WRITE setPopName NOTIFY popNameChanged)


public:
    enum qmlPowerMode {// 电源
        QML_POWERMODE_ANIMATION = 0,          // Opening
        QML_POWERMODE_D1,
        QML_POWERMODE_D2,
        QML_POWERMODE_D3,
    };
    enum MIDAREASCREENINDEX {
        MIDAREASCREENINDEX_CARSTATE = 0,
        MIDAREASCREENINDEX_NAVI,
        MIDAREASCREENINDEX_ADAS,
        MIDAREASCREENINDEX_TYRE
    };
    enum CARINFOSCREENINDEX {
        CARINFOSCREENINDEX_AFTERSTART = 0,
        CARINFOSCREENINDEX_AFTERRESET,
//        CARINFOSCREENINDEX_ENERGYINFO,
        CARINFOSCREENINDEX_TYREINFO,
    };
    enum CARINFOLISTMOVEDIRECT{
        CARINFOLISTMOVEDIRECT_UP = -1,
        CARINFOLISTMOVEDIRECT_NONE = 0,
        CARINFOLISTMOVEDIRECT_DOWN = 1,
    };

    void startControl();
    Manager();
    ~Manager();
    void createCtrl(QQuickView *view);
    void requstAllEEPROMDATAon1stPowerUp(void);
#ifdef DESKTOP
    void testVolumeInfo();
#endif
    HMICustomTimer* volumeTimer;
    Worker * m_worker;

    int receiveCtrlPowerMode() const
    {
        return m_receiveCtrlPowerMode;
    }
    /*
     * ===  FUNCTION  ======================================================================
     *  Name:  isCarInfoScreenIndex
     *  Description:  当前是0:行车电脑画面, 1:故障查询画面
     *	Return:
     *          int: isCarInfoScreenIndex
     *  Param:
                none: none
     * =====================================================================================
     */
    int isCarInfoScreenIndex() const
    {
        return m_isCarInfoScreenIndex;
    }
    /*
     * ===  FUNCTION  ======================================================================
     *  Name:  isCarInfoChildDirection
     *  Description:  行车电脑列表需要循环,提供上下方向
     *	Return:
     *          int: isCarInfoChildDirection
     *  Param:
                none: none
     * =====================================================================================
     */
    int isCarInfoChildDirection() const
    {
        return m_isCarInfoChildDirection;
    }
    /*
     * ===  FUNCTION  ======================================================================
     *  Name:  isCarInfoFaultChildIndex
     *  Description:  当前是故障查询画面某条高亮
     *	Return:
     *          int: isCarInfoFaultChildIndex
     *  Param:
                none: none
     * =====================================================================================
     */
    int isCarInfoFaultChildIndex() const
    {
        return m_isCarInfoFaultChildIndex;
    }
    /*
     * ===  FUNCTION  ======================================================================
     *  Name:  isWarningState
     *  Description:  pop or 行车电脑 显示
     *	Return:
     *          bool: isWarningState
     *  Param:
                none: none
     * =====================================================================================
     */
    bool isWarningState() const
    {
        return m_isWarningState;
    }

    bool updateScreenVisible() const
    {
        return m_updateScreenVisible;
    }

    int isMidAreaScreenIndex() const
    {
        return m_isMidAreaScreenIndex;
    }

    bool hmiScreenState() const
    {
        return m_hmiScreenState;
    }

    bool enterAnimStart() const
    {
        return m_enterAnimStart;
    }

    int edition() const
    {
        return m_edition;
    }

    int isCarInfoFaultChildDirect() const
    {
        return m_isCarInfoFaultChildDirect;
    }
    QString updateVersion() const
    {
        return m_updateVersion;
    }

    QString currentVersion() const
    {
        return m_currentVersion;
    }

    QString popName() const
    {
        return m_popName;
    }


signals:
    void receiveDateFromOtherProcessSignal(QString name, QVariant value);
    void receiveCtrlPowerModeChanged(int receiveCtrlPowerMode);


    void isCarInfoScreenIndexChanged(int isCarInfoScreenIndex);

    void isCarInfoChildDirectionChanged(int isCarInfoChildDirection);

    void isCarInfoFaultChildIndexChanged(int isCarInfoFaultChildIndex);

    void isWarningStateChanged(bool isWarningState);

    void updateScreenVisibleChanged(bool updateScreenVisible);

    void isMidAreaScreenIndexChanged(int isMidAreaScreenIndex);

    void hmiScreenStateChanged(bool hmiScreenState);

    void enterAnimStartChanged(bool enterAnimStart);

    void editionChanged(int edition);

    void isCarInfoFaultChildDirectChanged(int isCarInfoFaultChildDirect);



    void updateVersionChanged(QString updateVersion);

    void currentVersionChanged(QString currentVersion);

    void popNameChanged(QString popName);

public slots:

    void changeProjectMatrix(float angle, float ratio);
    void changeModelviewMatrixTranslate(float x, float y, float z);
    void changeModelviewMatrixRotate(float angle);

    void notifyWarningState(bool state);
    void qmlPrintLog(QString log);
    void qmlPrintValueLog(QString key,QString value);
    void get_timeout10ms();
    void get_timeout100ms();
    void get_timeout500ms();
    void get_timeout250ms();

    void sendToOtherCtrl(QString message_key, QVariant message_value);

    void sendToOtherProcess(QString name, QVariant value);
    void receiveDateFromOtherProcess(QString data);

    void notify_cluster_manager(QString state);

    void key_pressed_released(int _key, int _type);

    void notifyADASWaring();             //adas报警
    void exitDiagScreen();          //退出电检画面

    void setReceiveCtrlPowerMode(int receiveCtrlPowerMode)
    {
        if (m_receiveCtrlPowerMode == receiveCtrlPowerMode)
            return;

        m_receiveCtrlPowerMode = receiveCtrlPowerMode;
        emit receiveCtrlPowerModeChanged(m_receiveCtrlPowerMode);
    }

    void setIsCarInfoScreenIndex(int isCarInfoScreenIndex)
    {
        if (m_isCarInfoScreenIndex == isCarInfoScreenIndex)
            return;

        m_isCarInfoScreenIndex = isCarInfoScreenIndex;
        emit isCarInfoScreenIndexChanged(m_isCarInfoScreenIndex);
    }

    void setIsCarInfoChildDirection(int isCarInfoChildDirection)
    {
        if (m_isCarInfoChildDirection == isCarInfoChildDirection)
            return;

        m_isCarInfoChildDirection = isCarInfoChildDirection;
        emit isCarInfoChildDirectionChanged(m_isCarInfoChildDirection);
    }

    void setIsCarInfoFaultChildIndex(int isCarInfoFaultChildIndex)
    {
        if (m_isCarInfoFaultChildIndex == isCarInfoFaultChildIndex)
            return;

        m_isCarInfoFaultChildIndex = isCarInfoFaultChildIndex;
        emit isCarInfoFaultChildIndexChanged(m_isCarInfoFaultChildIndex);
    }

    void setIsWarningState(bool isWarningState)
    {
        if (m_isWarningState == isWarningState)
            return;

        m_isWarningState = isWarningState;
        emit isWarningStateChanged(m_isWarningState);
    }

    void setUpdateScreenVisible(bool updateScreenVisible);


    void setIsMidAreaScreenIndex(int isMidAreaScreenIndex)
    {
        if (m_isMidAreaScreenIndex == isMidAreaScreenIndex)
            return;

        m_isMidAreaScreenIndex = isMidAreaScreenIndex;
        emit isMidAreaScreenIndexChanged(m_isMidAreaScreenIndex);
    }

    void setHmiScreenState(bool hmiScreenState)
    {
        if (m_hmiScreenState == hmiScreenState)
            return;

        m_hmiScreenState = hmiScreenState;
        emit hmiScreenStateChanged(m_hmiScreenState);
    }

    void setEnterAnimStart(bool enterAnimStart);

    void setEdition(int edition)
    {
        if (m_edition == edition)
            return;

        m_edition = edition;
        emit editionChanged(m_edition);
    }

    void setIsCarInfoFaultChildDirect(int isCarInfoFaultChildDirect)
    {
        if (m_isCarInfoFaultChildDirect == isCarInfoFaultChildDirect)
            return;

        m_isCarInfoFaultChildDirect = isCarInfoFaultChildDirect;
        emit isCarInfoFaultChildDirectChanged(m_isCarInfoFaultChildDirect);
    }

    void setUpdateVersion(QString updateVersion)
    {
        if (m_updateVersion == updateVersion)
            return;

        m_updateVersion = updateVersion;
        emit updateVersionChanged(m_updateVersion);
    }

    void setCurrentVersion(QString currentVersion)
    {
        if (m_currentVersion == currentVersion)
            return;

        m_currentVersion = currentVersion;
        emit currentVersionChanged(m_currentVersion);
    }

    void setPopName(QString popName)
    {
        if (m_popName == popName)
            return;

        m_popName = popName;
        emit popNameChanged(m_popName);
    }

private:
    QQuickView* m_view;
    int m_receiveCtrlPowerMode;
    int m_isCarInfoChildIndex;
    int m_isCarInfoScreenIndex;
    int m_isCarInfoChildDirection;
    int m_isCarInfoFaultChildIndex;
    bool m_isWarningState;

    ADASControl* _ADASControl;
    CarInfoControl* _CarInfoControl;
    SettingControl* _SettingControl;
    DiagControl* _DiagControl;
    DiagScreen* _DiagScreen;
    InterconnectControl* _InterconnectControl;
    HomeControl* _HomeControl;
    PopupControl* _PopupControl;

    MyShareMemory* _MyShareMemory;
    bool m_updateScreenVisible;

    int m_isMidAreaScreenIndex;
    bool m_hmiScreenState;


    void handleRemainingMaintenanceMileage();   //通知mcu清除 剩余保养里程
    int switchCarInfoScreen(int index,int Direction);   //获取行车电脑画面切换下一个index

    bool m_enterAnimStart;
    int m_edition;
    HMICustomTimer* m_adasWaringTimer;
    HMICustomTimer* m_midAreaScreenSwitchTimer;

    int m_isCarInfoFaultChildDirect;
    QString m_updateVersion;
    QString m_currentVersion;

    //行车电脑列表切换
    int m_currentIndex;//当前显示page
    int m_maxPage;
    QString m_popName;
    int m_cardIndicatorNum;
    Popup* pop = nullptr;
};

Q_DECLARE_METATYPE(Manager::qmlPowerMode)

#endif // MANAGER_H
