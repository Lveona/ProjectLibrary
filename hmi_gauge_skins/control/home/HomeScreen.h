#ifndef HomeScreen_H
#define HomeScreen_H

#include "HomeControl.h"

class HomeScreen : public CBaseScreen, public CSingleton<HomeScreen>
{

    Q_PROPERTY(QVariant gear READ gear WRITE setGear NOTIFY gearChanged) //档位
    Q_PROPERTY(QVariant chargeValue READ chargeValue WRITE setChargeValue NOTIFY chargeValueChanged)    //剩余电量值
    Q_PROPERTY(QVariant chargeColor READ chargeColor WRITE setChargeColor NOTIFY chargeColorChanged) //进度条颜色 红 黄 绿
    Q_PROPERTY(QVariant odo READ getodo WRITE setOdo NOTIFY odoChanged) //总计里程
    Q_PROPERTY(QVariant temp READ temp WRITE setTemp NOTIFY tempChanged) //室外温度
    Q_PROPERTY(QVariant clock READ clock WRITE setClock NOTIFY clockChanged)//时间
    Q_PROPERTY(QVariant clockFormat READ clockFormat WRITE setClockFormat NOTIFY clockFormatChanged)//时间
    Q_PROPERTY(QVariant doorWarning READ doorWarning WRITE setDoorWarning NOTIFY doorWarningChanged)//车门报警
    Q_PROPERTY(QVariant hood READ hood WRITE sethood NOTIFY hoodChanged)          //前舱盖
    Q_PROPERTY(QVariant flDoor READ flDoor WRITE setflDoor NOTIFY flDoorChanged) //主驾
    Q_PROPERTY(QVariant frDoor READ frDoor WRITE setfrDoor NOTIFY frDoorChanged) //副驾
    Q_PROPERTY(QVariant rlDoor READ rlDoor WRITE setrlDoor NOTIFY rlDoorChanged) //后排左
    Q_PROPERTY(QVariant rrDoor READ rrDoor WRITE setrrDoor NOTIFY rrDoorChanged) //后排右
    Q_PROPERTY(QVariant tail READ tail WRITE settail NOTIFY tailChanged)         //尾门
    Q_PROPERTY(QVariant flChargePort READ flChargePort WRITE setFlChargePort NOTIFY flChargePortChanged)         //左充电口盖
    Q_PROPERTY(QVariant frChargePort READ frChargePort WRITE setFrChargePort NOTIFY frChargePortChanged)         //右充电口盖
    Q_PROPERTY(QVariant driveMode READ driveMode WRITE setDriveMode NOTIFY driveModeChanged)//驾驶模式
    Q_PROPERTY(QVariant isReady READ isReady WRITE setIsReady NOTIFY isReadyChanged)//Ready
    Q_PROPERTY(QVariant chargeConn READ chargeConn WRITE setChargeConn NOTIFY chargeConnChanged)//充电线连接
    Q_PROPERTY(QVariant remainTime READ remainTime WRITE setRemainTime NOTIFY remainTimeChanged)//剩余充电时间
    Q_PROPERTY(QVariant chargeStatus READ chargeStatus WRITE setChargeStatus NOTIFY chargeStatusChanged)//充电状态
    Q_PROPERTY(QVariant isCharging READ isCharging WRITE setIsCharging NOTIFY isChargingChanged)//充电中
    Q_PROPERTY(QVariant chargeVoltage READ chargeVoltage WRITE setChargeVoltage NOTIFY chargeVoltageChanged)//充电电压
    Q_PROPERTY(QVariant chargeElect READ chargeElect WRITE setChargeElect NOTIFY chargeElectChanged)//充电电流
    Q_PROPERTY(QVariant chargeCnctrdetd READ chargeCnctrdetd WRITE setChargeCnctrdetd NOTIFY chargeCnctrdetdChanged)//充电电流


    Q_OBJECT
    friend class CSingleton<HomeScreen>;
    Q_ENUMS(COLORTYPEQML)

    QVariant m_gear;

    QVariant m_chargeValue;

    QVariant m_chargeColor;

    QVariant m_odo;

    QVariant m_temp;

    QVariant m_clock;

    QVariant m_clockFormat;

    QVariant m_hood;

    QVariant m_flDoor;

    QVariant m_frDoor;

    QVariant m_rlDoor;

    QVariant m_rrDoor;

    QVariant m_tail;

    QVariant m_driveMode;

    QVariant m_isReady;

    QVariant m_doorWarning;

    QVariant m_chargeConn;

    QVariant m_remainTime;

    QVariant m_flChargePort;

    QVariant m_frChargePort;

    QVariant m_chargeStatus;

    QVariant m_chargeVoltage;

    QVariant m_chargeElect;

    QVariant m_isCharging;
    QVariant m_chargeCnctrdetd;

public:
    virtual void startControl();
    HomeScreen();
    ~HomeScreen();

    enum COLORTYPEQML
    {
        COLORTYPEQML_NONE = 0,
        COLORTYPEQML_GREEN,
        COLORTYPEQML_WHITE,
        COLORTYPEQML_RED,
        COLORTYPEQML_YELLOW,
        COLORTYPEQML_GRAY,
    };

    typedef void ( HomeScreen::* FunctionParser )(QVariant value);

    void createCtrl(QQuickView *view);

    QVariant temp() const
    {
        return m_temp;
    }

    QVariant clock() const
    {
        return m_clock;
    }

    QVariant clockFormat() const
    {
        return m_clockFormat;
    }

    QVariant getodo() const
    {
        return m_odo;
    }

    QVariant driveMode() const
    {
        return m_driveMode;
    }

    QVariant gear() const
    {
        return m_gear;
    }

    QVariant chargeValue() const
    {
        return m_chargeValue;
    }

    QVariant chargeColor() const
    {
        return m_chargeColor;
    }

    QVariant hood() const
    {
        return m_hood;
    }

    QVariant flDoor() const
    {
        return m_flDoor;
    }

    QVariant frDoor() const
    {
        return m_frDoor;
    }

    QVariant rlDoor() const
    {
        return m_rlDoor;
    }

    QVariant rrDoor() const
    {
        return m_rrDoor;
    }

    QVariant tail() const
    {
        return m_tail;
    }

    QVariant isReady() const
    {
        return m_isReady;
    }

    QVariant doorWarning() const
    {
        return m_doorWarning;
    }

    QVariant chargeConn() const
    {
        return m_chargeConn;
    }

    QVariant remainTime() const
    {
        return m_remainTime;
    }

    QVariant flChargePort() const
    {
        return m_flChargePort;
    }

    QVariant frChargePort() const
    {
        return m_frChargePort;
    }

    QVariant chargeStatus() const
    {
        return m_chargeStatus;
    }

    QVariant chargeCnctrdetd() const
    {
        return m_chargeCnctrdetd;
    }

    QVariant chargeVoltage() const
    {
        return m_chargeVoltage;
    }

    QVariant chargeElect() const
    {
        return m_chargeElect;
    }

    QVariant isCharging() const
    {
        return m_isCharging;
    }

public slots:
    void SetProperty(int name, QVariant value);

    void setTemp(QVariant temp)
    {
        if (m_temp == temp)
            return;

        m_temp = temp;
        emit tempChanged(m_temp);
    }
    void setClock(QVariant clock)
    {
        if (m_clock == clock)
            return;

        m_clock = clock;
        emit clockChanged(m_clock);
    }

    void setClockFormat(QVariant clockFormat)
    {
        if (m_clockFormat == clockFormat)
            return;

        m_clockFormat = clockFormat;
        emit clockFormatChanged(m_clockFormat);
    }

    void setOdo(QVariant odo)
    {
        if (m_odo == odo)
            return;

        m_odo = odo;
        emit odoChanged(m_odo);
    }

    /*
     * normal, sport, eco
     */
    void setDriveMode(QVariant driveMode)
    {
        if (m_driveMode == driveMode)
            return;

        m_driveMode = driveMode;
        emit driveModeChanged(m_driveMode);
    }

    void setGear(QVariant gear)
    {
        if (m_gear == gear)
            return;

        m_gear = gear;
        emit gearChanged(m_gear);
    }

    void setChargeValue(QVariant chargeValue)
    {
        if (m_chargeValue == chargeValue)
            return;

        m_chargeValue = chargeValue;
        emit chargeValueChanged(m_chargeValue);
    }

    void setChargeColor(QVariant chargeColor)
    {
        if (m_chargeColor == chargeColor)
            return;

        m_chargeColor = chargeColor;
        emit chargeColorChanged(m_chargeColor);
    }

    void sethood(QVariant hood)
    {
        if (m_hood == hood)
            return;

        m_hood = hood;
        emit hoodChanged(m_hood);
    }

    void setflDoor(QVariant flDoor)
    {
        if (m_flDoor == flDoor)
            return;

        m_flDoor = flDoor;
        emit flDoorChanged(m_flDoor);
    }

    void setfrDoor(QVariant frDoor)
    {
        if (m_frDoor == frDoor)
            return;

        m_frDoor = frDoor;
        emit frDoorChanged(m_frDoor);
    }

    void setrlDoor(QVariant rlDoor)
    {
        if (m_rlDoor == rlDoor)
            return;

        m_rlDoor = rlDoor;
        emit rlDoorChanged(m_rlDoor);
    }

    void setrrDoor(QVariant rrDoor)
    {
        if (m_rrDoor == rrDoor)
            return;

        m_rrDoor = rrDoor;
        emit rrDoorChanged(m_rrDoor);
    }

    void settail(QVariant tail)
    {
        if (m_tail == tail)
            return;

        m_tail = tail;
        emit tailChanged(m_tail);
    }

    void setIsReady(QVariant isReady)
    {
        if (m_isReady == isReady)
            return;

        m_isReady = isReady;
        emit isReadyChanged(m_isReady);
    }

    void setDoorWarning(QVariant doorWarning)
    {
        if (m_doorWarning == doorWarning)
            return;

        m_doorWarning = doorWarning;
        emit doorWarningChanged(m_doorWarning);
    }

    void setChargeConn(QVariant chargeConn)
    {
        if (m_chargeConn == chargeConn)
            return;

        m_chargeConn = chargeConn;
        emit chargeConnChanged(m_chargeConn);
    }

    void setRemainTime(QVariant remainTime)
    {
        if (m_remainTime == remainTime)
            return;

        m_remainTime = remainTime;
        emit remainTimeChanged(m_remainTime);
    }

    void setFlChargePort(QVariant flChargePort)
    {
        if (m_flChargePort == flChargePort)
            return;

        m_flChargePort = flChargePort;
        emit flChargePortChanged(m_flChargePort);
    }

    void setFrChargePort(QVariant frChargePort)
    {
        if (m_frChargePort == frChargePort)
            return;

        m_frChargePort = frChargePort;
        emit frChargePortChanged(m_frChargePort);
    }

    void setChargeStatus(QVariant chargeStatus)
    {
        if (m_chargeStatus == chargeStatus)
            return;

        m_chargeStatus = chargeStatus;
        emit chargeStatusChanged(m_chargeStatus);
    }
    void setChargeCnctrdetd(QVariant chargeCnctrdetd)
    {
        if (m_chargeCnctrdetd == chargeCnctrdetd)
            return;

        m_chargeCnctrdetd = chargeCnctrdetd;
        emit chargeCnctrdetdChanged(m_chargeCnctrdetd);
    }
    void setChargeVoltage(QVariant chargeVoltage)
    {
        if (m_chargeVoltage == chargeVoltage)
            return;

        m_chargeVoltage = chargeVoltage;
        emit chargeVoltageChanged(m_chargeVoltage);
    }

    void setChargeElect(QVariant chargeElect)
    {
        if (m_chargeElect == chargeElect)
            return;

        m_chargeElect = chargeElect;
        emit chargeElectChanged(m_chargeElect);
    }

    void setIsCharging(QVariant isCharging)
    {
        if (m_isCharging == isCharging)
            return;

        m_isCharging = isCharging;
        emit isChargingChanged(m_isCharging);
    }

signals:
    void tempChanged(QVariant temp);
    void clockChanged(QVariant clock);
    void clockFormatChanged(QVariant clockFormat);
    void odoChanged(QVariant odo);
    void driveModeChanged(QVariant driveMode);
    void gearChanged(QVariant gear);
    void chargeValueChanged(QVariant chargeValue);
    void chargeColorChanged(QVariant chargeColor);
    void hoodChanged(QVariant hood);
    void flDoorChanged(QVariant flDoor);
    void frDoorChanged(QVariant frDoor);
    void rlDoorChanged(QVariant rlDoor);
    void rrDoorChanged(QVariant rrDoor);
    void tailChanged(QVariant tail);
    void isReadyChanged(QVariant isReady);
    void doorWarningChanged(QVariant doorWarning);
    void chargeConnChanged(QVariant chargeConn);
    void remainTimeChanged(QVariant remainTime);
    void flChargePortChanged(QVariant flChargePort);
    void frChargePortChanged(QVariant frChargePort);
    void chargeStatusChanged(QVariant chargeStatus);
    void chargeVoltageChanged(QVariant chargeVoltage);
    void chargeElectChanged(QVariant chargeElect);
    void isChargingChanged(QVariant isCharging);
    void chargeCnctrdetdChanged(QVariant chargeCnctrdetd);
};

#endif // HomeScreen_H
