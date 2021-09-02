#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H

#include "settingControl.h"

/////Test
#include "pm_proxy.h"

class QQuickView;
class SettingScreen : public CBaseScreen, public CSingleton<SettingScreen>
{
    Q_OBJECT
    friend class CSingleton<SettingScreen>;
public:
    SettingScreen();
    ~SettingScreen();
    typedef void ( SettingScreen::* FunctionParser )(QVariant value);
    // Systemlib to SettingScreen
    void createCtrl( QQuickView *view );
    virtual void startControl();

    Q_ENUMS(THEME_SETTING)

    Q_PROPERTY(QVariant controlScreenState READ getControlScreenState WRITE setControlScreenState NOTIFY controlScreenStateChanged)
    Q_PROPERTY(QVariant controlScreenColor READ getControlScreenColor WRITE setControlScreenColor NOTIFY controlScreenColorChanged)
    //切换主题
    Q_PROPERTY(QVariant themeSetting READ getThemeSetting WRITE setThemeSetting NOTIFY themeSettingChanged)
    //出场动画执行状态 true代表出场动画执行完毕 根据EEP 切换主题
    //Q_PROPERTY(QVariant outAnimationState READ getOutAnimationState WRITE setOutAnimationState NOTIFY outAnimationStateChanged)

    Q_PROPERTY(QVariant currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(QVariant vehicleSpeed READ vehicleSpeed WRITE setVehicleSpeed NOTIFY vehicleSpeedChanged)
    enum THEME_SETTING {
        NONE = 0x00, //上一次默认值
        COMFORT, //舒适主题
        ECO,//经济主题
        SPORT ,//运动主题
        INDIVIDUAL, //自定义主题
        MAXTHEM
    };

    QVariant getControlScreenState() const
    {
        return m_controlScreenState;
    }

    QVariant getControlScreenColor() const
    {
        return m_controlScreenColor;
    }

    QVariant getThemeSetting() const
    {
        return m_themeSetting;
    }

    QVariant getOutAnimationState() const
    {
        return m_outAnimationState;
    }
    QVariant currentPage() const
    {
        return m_currentPage;
    }
    QVariant vehicleSpeed() const
    {
        return m_vehicleSpeed;
    }
signals:


    void controlScreenStateChanged(QVariant controlScreenState);

    void controlScreenColorChanged(QVariant controlScreenColor);

    void themeSettingChanged(QVariant themeSetting);

    void outAnimationStateChanged(QVariant outAnimationState);

    void currentPageChanged(QVariant currentPage);
    void vehicleSpeedChanged(QVariant vehicleSpeed);

public slots:
    void SetProperty(int name, QVariant value);


    void setControlScreenState(QVariant controlScreenState)
    {
        if (m_controlScreenState == controlScreenState)
            return;
        m_controlScreenState = controlScreenState;
        emit controlScreenStateChanged(m_controlScreenState);
    }

    void setControlScreenColor(QVariant controlScreenColor)
    {
        if (m_controlScreenColor == controlScreenColor)
            return;
        m_controlScreenColor = controlScreenColor;
        emit controlScreenColorChanged(m_controlScreenColor);
    }

    void setThemeSetting(QVariant themeSetting)
    {
        if (m_themeSetting == themeSetting)
            return;
        m_themeSetting = themeSetting;
        emit themeSettingChanged(m_themeSetting);
    }

    void setOutAnimationState(QVariant outAnimationState)
    {
        if (m_outAnimationState == outAnimationState)
            return;

        m_outAnimationState = outAnimationState;
        emit outAnimationStateChanged(m_outAnimationState);
    }
    void setCurrentPage(QVariant currentPage)
    {
        if (m_currentPage == currentPage)
            return;

        m_currentPage = currentPage;
        emit currentPageChanged(m_currentPage);
    }
    void setVehicleSpeed(QVariant vehicleSpeed)
    {
        if (m_vehicleSpeed == vehicleSpeed)
            return;

        m_vehicleSpeed = vehicleSpeed;
        emit vehicleSpeedChanged(m_vehicleSpeed);
    }
private:

    QVariant m_controlScreenState;
    QVariant m_controlScreenColor;
    QVariant m_themeSetting;
    QVariant m_outAnimationState;
    QVariant m_currentPage;
    QVariant m_vehicleSpeed;
};

#endif // SETTINGSCREEN_H
