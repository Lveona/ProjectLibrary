#ifndef MANAGER_H
#define MANAGER_H

#include "../telltale/telltalesScreen.h"
#include "../gauge/GaugeScreen.h"
#include "hmi_share.h"

class QTimer;
class QByteArray;
class QObject;
class QQuickView;
class QThread;
class ManagerCustomTimer;
class MyShareMemory;
class Worker;

class Manager : public CBaseScreen, public CSingleton<Manager>
{
    Q_OBJECT
    friend class CSingleton<Manager>;
    Q_ENUMS(qmlPowerMode)
    Q_ENUMS(autoCheck_Status)
    Q_ENUMS(qmlNaviMapMode)
    Q_ENUMS(THEME_SETTING)
    Q_PROPERTY(int receiveCtrlPowerMode READ receiveCtrlPowerMode WRITE setReceiveCtrlPowerMode NOTIFY receiveCtrlPowerModeChanged)
    Q_PROPERTY(double digitSpeedValue READ getdigitSpeedValue WRITE setdigitSpeedValue NOTIFY digitSpeedValueChanged)
    Q_PROPERTY(bool hmiVisible READ hmiVisible WRITE setHmiVisible NOTIFY hmiVisibleChanged)
    Q_PROPERTY(bool rotationSpeedWarning READ rotationSpeedWarning WRITE setRotationSpeedWarning NOTIFY rotationSpeedWarningChanged)
    Q_PROPERTY(bool hmiScreenState READ hmiScreenState WRITE setHmiScreenState NOTIFY hmiScreenStateChanged)

    Q_PROPERTY(bool enterAnimStart READ enterAnimStart WRITE setEnterAnimStart NOTIFY enterAnimStartChanged)
    Q_PROPERTY(bool isLoaderOver READ isLoaderOver WRITE setIsLoaderOver NOTIFY isLoaderOverChanged)
    Q_PROPERTY(bool isCharging READ isCharging WRITE setIsCharging NOTIFY isChargingChanged)

    Q_PROPERTY(QVariant navigationMapMod READ navigationMapMod WRITE setNavigationMapMod NOTIFY navigationMapModChanged)
    Q_PROPERTY(QVariant themeSetting READ themeSetting WRITE setThemeSetting NOTIFY themeSettingChanged)

public:
    enum qmlPowerMode {// 电源
        QML_POWERMODE_ANIMATION = 0,          // Opening
        QML_POWERMODE_D1,
        QML_POWERMODE_D2,
        QML_POWERMODE_D3,
    };
    enum autoCheck_Status{          // 自检
        AUTOCHECK_INIT = 0,         // 初始值
        AUTOCHECK_START,            // 自检开始
        AUTOCHECK_END               // 自检结束
    };

    enum qmlNaviMapMode{
        SMALL_MAP = 0,  //小地图
        BIG_MAP,        //大地图
        AR_MAP,         //AR地图
        MAP_MODE_MAX
    };

    enum THEME_SETTING {
        NONE = 0x00, //上一次默认值
        COMFORT, //舒适主题
        ECO,//经济主题
        SPORT ,//运动主题
        INDIVIDUAL, //自定义主题
        MAXTHEM
    };

    virtual void startControl();
    Manager();
    ~Manager();
    void createCtrl(QQuickView *view);
    void requstAllEEPROMDATAon1stPowerUp(void);
    void handleAutoCheck();
    Worker * m_worker;

    int receiveCtrlPowerMode() const
    {
        return m_receiveCtrlPowerMode;
    }

    double getdigitSpeedValue() const
    {
        return m_digitSpeedValue;
    }

    bool hmiVisible() const
    {
        return m_hmiVisible;
    }

    bool rotationSpeedWarning() const
    {
        return m_rotationSpeedWarning;
    }

    bool hmiScreenState() const
    {
        return m_hmiScreenState;
    }

    bool enterAnimStart() const
    {
        return m_enterAnimStart;
    }

    bool isLoaderOver() const
    {
        return m_isLoaderOver;
    }

    bool isCharging() const
    {
        return m_isCharging;
    }

    QVariant navigationMapMod() const
    {
        return m_navigationMapMod;
    }

    QVariant themeSetting() const
    {
        return m_themeSetting;
    }

signals:
    void receiveDateFromOtherProcessSignal(QString name, QVariant value);
    void receiveCtrlPowerModeChanged(int receiveCtrlPowerMode);

    void digitSpeedValueChanged(double digitSpeedValue);

    void hmiVisibleChanged(bool hmiVisible);

    void rotationSpeedWarningChanged(bool rotationSpeedWarning);

    void hmiScreenStateChanged(bool hmiScreenState);

    void enterAnimStartChanged(bool enterAnimStart);

    void isLoaderOverChanged(bool isLoaderOver);

    void isChargingChanged(bool isCharging);

    void navigationMapModChanged(QVariant navigationMapMod);

    void themeSettingChanged(QVariant themeSetting);

public slots:
    void qmlPrintLog(QString log);
    void qmlPrintValueLog(QString key,QString value);
    void get_timeout10ms();
    void get_timeout100ms();
    void get_timeout500ms();

    void sendToOtherCtrlP(QString message_key, QVariant message_value);

    void sendToOtherProcessP(QString name, QVariant value);

    void receiveDateFromOtherProcess(QString data);

    void notify_cluster_manager(QString state);

    void selfReceiveDateFromOtherProcessSignal(QString name, QVariant value);

    void setReceiveCtrlPowerMode(int receiveCtrlPowerMode)
    {
        if (m_receiveCtrlPowerMode == receiveCtrlPowerMode)
            return;

        m_receiveCtrlPowerMode = receiveCtrlPowerMode;
        emit receiveCtrlPowerModeChanged(m_receiveCtrlPowerMode);
    }

    void setdigitSpeedValue(double digitSpeedValue)
    {
        if (m_digitSpeedValue == digitSpeedValue)
            return;

        m_digitSpeedValue = digitSpeedValue;
        emit digitSpeedValueChanged(m_digitSpeedValue);
    }

    void setHmiVisible(bool hmiVisible)
    {
        if (m_hmiVisible == hmiVisible)
            return;

        m_hmiVisible = hmiVisible;
        emit hmiVisibleChanged(m_hmiVisible);
    }

    void setRotationSpeedWarning(bool rotationSpeedWarning)
    {
        if (m_rotationSpeedWarning == rotationSpeedWarning)
            return;

        m_rotationSpeedWarning = rotationSpeedWarning;
        emit rotationSpeedWarningChanged(m_rotationSpeedWarning);
    }

    void setHmiScreenState(bool hmiScreenState)
    {
        if (m_hmiScreenState == hmiScreenState)
            return;

        m_hmiScreenState = hmiScreenState;
        emit hmiScreenStateChanged(m_hmiScreenState);
    }

    void setEnterAnimStart(bool enterAnimStart)
    {
        if (m_enterAnimStart == enterAnimStart)
            return;

        m_enterAnimStart = enterAnimStart;
        emit enterAnimStartChanged(m_enterAnimStart);
    }

    void setIsLoaderOver(bool isLoaderOver)
    {
        if (m_isLoaderOver == isLoaderOver)
            return;

        g_loaderOver = m_isLoaderOver = isLoaderOver;
        emit isLoaderOverChanged(m_isLoaderOver);
//        handleAutoCheck();
    }

    void setIsCharging(bool isCharging)
    {
        if (m_isCharging == isCharging)
            return;

        m_isCharging = isCharging;
        emit isChargingChanged(m_isCharging);
    }

    void setNavigationMapMod(QVariant navigationMapMod)
    {
        if (m_navigationMapMod == navigationMapMod)
            return;

        m_navigationMapMod = navigationMapMod;
        emit navigationMapModChanged(m_navigationMapMod);
    }

    void setThemeSetting(QVariant themeSetting)
    {
        if (m_themeSetting == themeSetting)
            return;

        m_themeSetting = themeSetting;
        emit themeSettingChanged(m_themeSetting);
    }

private:
    QQuickView* m_view;
    int m_receiveCtrlPowerMode;
    TelltalesControl* _TelltalesControl;

    GaugeControl* _GaugeControl;
    MyShareMemory* _MyShareMemory;

    double m_digitSpeedValue;
    bool m_hmiVisible;
    bool m_rotationSpeedWarning;
    bool m_hmiScreenState;
    bool m_enterAnimStart;

    void updatePointScreen();
    bool m_isLoaderOver;
    bool g_loaderOver;
    //    HMICustomTimer* acTimer;
    bool m_isCharging;
    QVariant m_navigationMapMod;
    QVariant m_themeSetting;
};
Q_DECLARE_METATYPE(Manager::qmlPowerMode)
Q_DECLARE_METATYPE(Manager::autoCheck_Status)

#endif // MANAGER_H
