#ifndef GaugeSCREEN_H
#define GaugeSCREEN_H

#include "GaugeControl.h"

class QQuickView;
class GaugeScreen:  public CBaseScreen, public CSingleton<GaugeScreen>
{
    //Q_PROPERTY 2019/11/20
    Q_PROPERTY(QVariant digitSpeedValue READ getdigitSpeedValue WRITE setdigitSpeedValue NOTIFY digitSpeedValueChanged)
    Q_PROPERTY(QVariant powerValue READ getPowerValue WRITE setPowerValue NOTIFY powerValueChanged)
    Q_PROPERTY(QVariant autoCheckState READ getAutoCheckState WRITE setAutoCheckState NOTIFY autoCheckStateChanged)

    Q_OBJECT
    friend class CSingleton<GaugeScreen>;

public:
    GaugeScreen();
    ~GaugeScreen();

    typedef void ( GaugeScreen::* FunctionParser )(QVariant value);

    virtual void startControl();
    void createCtrl(QQuickView *view);


    QVariant getdigitSpeedValue() const
    {
        return m_digitSpeedValue;
    }

    QVariant getPowerValue() const
    {
        return m_powerValue;
    }

    QVariant getAutoCheckState() const
    {
        return m_autoCheckState;
    }

public slots:
    void SetProperty(int name, QVariant);

    void setdigitSpeedValue(QVariant _visible)
    {
        if(m_digitSpeedValue!= _visible)
        {
            if(_visible.toUInt() == 0xFFFF){//无效值或超时
                m_digitSpeedValue = "--";
            }
            else{
                m_digitSpeedValue = _visible;
            }
            emit digitSpeedValueChanged(m_digitSpeedValue);
        }

    }

    void setAutoCheckState(QVariant autoCheckState)
    {
        if (m_autoCheckState == autoCheckState)
            return;

        m_autoCheckState = autoCheckState;
        emit autoCheckStateChanged(m_autoCheckState);
    }

    void setPowerValue(QVariant powerValue)
    {
        if (m_powerValue == powerValue)
            return;

        m_powerValue = powerValue;
        emit powerValueChanged(m_powerValue);
    }

signals:
    void digitSpeedValueChanged(QVariant);

    void autoCheckStateChanged(QVariant autoCheckState);

    void powerValueChanged(QVariant powerValue);

private:
    QVariant m_digitSpeedValue;
    QVariant m_autoCheckState;
    QVariant m_powerValue;
};


#endif // GaugeSCREEN_H
