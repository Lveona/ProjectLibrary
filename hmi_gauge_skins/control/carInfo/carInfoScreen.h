#ifndef CARINFOSCREEN_H
#define CARINFOSCREEN_H

#include "carInfoControl.h"

enum CARINFO_IC_CAN_INFO_SEND_ID {
    CARINFO_INIT = 0,
    CARINFO_MAINTENANCECLEAR
};

class QQuickView;
class CarInfoScreen : public CBaseScreen, public CSingleton<CarInfoScreen>
{
    Q_OBJECT

    QVariant m_afterStartDrivingDistance;

    QVariant m_afterStartDrivingTime;

    QVariant m_afterStartAvgSpeed;

    QVariant m_afterStartAvgEnergy;

    QVariant m_afterResetDrivingDistance;

    QVariant m_afterResetDrivingTime;

    QVariant m_afterResetAvgSpeed;

    QVariant m_afterResetAvgEnergy;

    QVariant m_remainRange;

    QVariant m_carInfoTyreLFPressure;

    QVariant m_carInfoTyreRFPressure;

    QVariant m_carInfoTyreLRPressure;

    QVariant m_carInfoTyreRRPressure;

    QVariant m_carInfoTyreLFTemp;

    QVariant m_carInfoTyreRFTemp;

    QVariant m_carInfoTyreLRTemp;

    QVariant m_carInfoTyreRRTemp;

    QVariant m_cardIndicatorNum;

    QVariant m_isCarInfoChildIndex;

    QVariant m_isCardShown;

    QVariant m_chargeDay;

    QVariant m_chargeHour;

QVariant m_chargeOdo;

QVariant m_averageAPC;

QVariant m_currentAPC;

public:
    CarInfoScreen();
    ~CarInfoScreen();
    typedef void ( CarInfoScreen::* FunctionParser )(QVariant value);
    Q_INVOKABLE void iC_Can_Info_Send(int reqSendID);

    // CarInfolib to CarInfoScreen
    void createCtrl( QQuickView *view );
    virtual void startControl();

    // 续航里程信息
    Q_PROPERTY(QVariant remainRange READ getRemainRange WRITE setRemainRange NOTIFY remainRangeChanged)
    // 左前轮压力
    Q_PROPERTY(QVariant carInfoTyreLFPressure READ getCarInfoTyreLFPressure WRITE setCarInfoTyreLFPressure NOTIFY carInfoTyreLFPressureChanged)
    // 右前轮压力
    Q_PROPERTY(QVariant carInfoTyreRFPressure READ getCarInfoTyreRFPressure WRITE setCarInfoTyreRFPressure NOTIFY carInfoTyreRFPressureChanged)
    // 左后轮压力
    Q_PROPERTY(QVariant carInfoTyreLRPressure READ getCarInfoTyreLRPressure WRITE setCarInfoTyreLRPressure NOTIFY carInfoTyreLRPressureChanged)
    // 右后轮压力
    Q_PROPERTY(QVariant carInfoTyreRRPressure READ getCarInfoTyreRRPressure WRITE setCarInfoTyreRRPressure NOTIFY carInfoTyreRRPressureChanged)
    // 左前温度
    Q_PROPERTY(QVariant carInfoTyreLFTemp READ carInfoTyreLFTemp WRITE setCarInfoTyreLFTemp NOTIFY carInfoTyreLFTempChanged)
    // 右前温度
    Q_PROPERTY(QVariant carInfoTyreRFTemp READ carInfoTyreRFTemp WRITE setCarInfoTyreRFTemp NOTIFY carInfoTyreRFTempChanged)
    // 左后温度
    Q_PROPERTY(QVariant carInfoTyreLRTemp READ carInfoTyreLRTemp WRITE setCarInfoTyreLRTemp NOTIFY carInfoTyreLRTempChanged)
    //右后温度
    Q_PROPERTY(QVariant carInfoTyreRRTemp READ carInfoTyreRRTemp WRITE setCarInfoTyreRRTemp NOTIFY carInfoTyreRRTempChanged)

    //自启动后
    Q_PROPERTY(QVariant afterStartDrivingDistance READ afterStartDrivingDistance WRITE setAfterStartDrivingDistance NOTIFY afterStartDrivingDistanceChanged)
    Q_PROPERTY(QVariant afterStartDrivingTime     READ afterStartDrivingTime     WRITE setAfterStartDrivingTime     NOTIFY afterStartDrivingTimeChanged)
    Q_PROPERTY(QVariant afterStartAvgSpeed        READ afterStartAvgSpeed        WRITE setAfterStartAvgSpeed        NOTIFY afterStartAvgSpeedChanged)
    Q_PROPERTY(QVariant afterStartAvgEnergy       READ afterStartAvgEnergy       WRITE setAfterStartAvgEnergy       NOTIFY afterStartAvgEnergyChanged)

    //自复位后
    Q_PROPERTY(QVariant afterResetDrivingDistance READ afterResetDrivingDistance WRITE setAfterResetDrivingDistance NOTIFY afterResetDrivingDistanceChanged)
    Q_PROPERTY(QVariant afterResetDrivingTime     READ afterResetDrivingTime     WRITE setAfterResetDrivingTime     NOTIFY afterResetDrivingTimeChanged)
    Q_PROPERTY(QVariant afterResetAvgSpeed        READ afterResetAvgSpeed        WRITE setAfterResetAvgSpeed        NOTIFY afterResetAvgSpeedChanged)
    Q_PROPERTY(QVariant afterResetAvgEnergy       READ afterResetAvgEnergy       WRITE setAfterResetAvgEnergy       NOTIFY afterResetAvgEnergyChanged)

    Q_PROPERTY(QVariant cardIndicatorNum       READ cardIndicatorNum       WRITE setCardIndicatorNum       NOTIFY cardIndicatorNumChanged)
    Q_PROPERTY(QVariant isCarInfoChildIndex READ isCarInfoChildIndex WRITE setIsCarInfoChildIndex NOTIFY isCarInfoChildIndexChanged)
    Q_PROPERTY(QVariant isCardShown       READ isCardShown       WRITE setIsCardShown       NOTIFY isCardShownChanged)
    Q_PROPERTY(QVariant chargeDay READ chargeDay WRITE setChargeDay NOTIFY chargeDayChanged)
    Q_PROPERTY(QVariant chargeHour READ chargeHour WRITE setChargeHour NOTIFY chargeHourChanged)
    Q_PROPERTY(QVariant chargeOdo READ chargeOdo WRITE setChargeOdo NOTIFY chargeOdoChanged)
    Q_PROPERTY(QVariant averageAPC READ averageAPC WRITE setAverageAPC NOTIFY averageAPCChanged)
    Q_PROPERTY(QVariant currentAPC READ currentAPC WRITE setCurrentAPC NOTIFY currentAPCChanged)

    QVariant getRemainRange() const
    {
        return m_remainRange;
    }

    QVariant getCarInfoTyreLFPressure() const
    {
        return m_carInfoTyreLFPressure;
    }

    QVariant getCarInfoTyreRFPressure() const
    {
        return m_carInfoTyreRFPressure;
    }

    QVariant getCarInfoTyreLRPressure() const
    {
        return m_carInfoTyreLRPressure;
    }

    QVariant getCarInfoTyreRRPressure() const
    {
        return m_carInfoTyreRRPressure;
    }

    QVariant carInfoTyreLFTemp() const
    {
        return m_carInfoTyreLFTemp;
    }

    QVariant carInfoTyreRFTemp() const
    {
        return m_carInfoTyreRFTemp;
    }

    QVariant carInfoTyreLRTemp() const
    {
        return m_carInfoTyreLRTemp;
    }

    QVariant carInfoTyreRRTemp() const
    {
        return m_carInfoTyreRRTemp;
    }

    QVariant afterStartDrivingDistance() const
    {
        return m_afterStartDrivingDistance;
    }

    QVariant afterStartDrivingTime() const
    {
        return m_afterStartDrivingTime;
    }

    QVariant afterStartAvgSpeed() const
    {
        return m_afterStartAvgSpeed;
    }

    QVariant afterStartAvgEnergy() const
    {
        return m_afterStartAvgEnergy;
    }

    QVariant afterResetDrivingDistance() const
    {
        return m_afterResetDrivingDistance;
    }

    QVariant afterResetDrivingTime() const
    {
        return m_afterResetDrivingTime;
    }

    QVariant afterResetAvgSpeed() const
    {
        return m_afterResetAvgSpeed;
    }

    QVariant afterResetAvgEnergy() const
    {
        return m_afterResetAvgEnergy;
    }

    QVariant cardIndicatorNum() const
    {
        return m_cardIndicatorNum;
    }

    QVariant isCarInfoChildIndex() const
    {
        return m_isCarInfoChildIndex;
    }

    QVariant isCardShown() const
    {
        return m_isCardShown;
    }

    QVariant chargeDay() const
    {
        return m_chargeDay;
    }

    QVariant chargeHour() const
    {
        return m_chargeHour;
    }

    QVariant chargeOdo() const
    {
        return m_chargeOdo;
    }

    QVariant averageAPC() const
    {
        return m_averageAPC;
    }

    QVariant currentAPC() const
    {
        return m_currentAPC;
    }

signals:

void remainRangeChanged(QVariant remainRange);

void carInfoTyreLFPressureChanged(QVariant carInfoTyreLFPressure);

void carInfoTyreRFPressureChanged(QVariant carInfoTyreRFPressure);

void carInfoTyreLRPressureChanged(QVariant carInfoTyreLRPressure);

void carInfoTyreRRPressureChanged(QVariant carInfoTyreRRPressure);

void carInfoTyreLFTempChanged(QVariant carInfoTyreLFTemp);

void carInfoTyreRFTempChanged(QVariant carInfoTyreRFTemp);

void carInfoTyreLRTempChanged(QVariant carInfoTyreLRTemp);

void carInfoTyreRRTempChanged(QVariant carInfoTyreRRTemp);

void afterStartDrivingDistanceChanged(QVariant afterStartDrivingDistance);

void afterStartDrivingTimeChanged(QVariant afterStartDrivingTime);

void afterStartAvgSpeedChanged(QVariant afterStartAvgSpeed);

void afterStartAvgEnergyChanged(QVariant afterStartAvgEnergy);

void afterResetDrivingDistanceChanged(QVariant afterResetDrivingDistance);

void afterResetDrivingTimeChanged(QVariant afterResetDrivingTime);

void afterResetAvgSpeedChanged(QVariant afterResetAvgSpeed);

void afterResetAvgEnergyChanged(QVariant afterResetAvgEnergy);

void cardIndicatorNumChanged(QVariant cardIndicatorNum);

void isCarInfoChildIndexChanged(QVariant isCarInfoChildIndex);

void isCardShownChanged(QVariant isCardShown);

void chargeDayChanged(QVariant chargeDay);

void chargeHourChanged(QVariant chargeHour);

void chargeOdoChanged(QVariant chargeOdo);

void averageAPCChanged(QVariant averageAPC);

void currentAPCChanged(QVariant currentAPC);

public slots:

    void SetProperty(int name, QVariant value);
    void setEnergyList(QVariant value);
    QVariantList qmlInstanceList();

    void setRemainRange(QVariant remainRange)
    {
        if (m_remainRange == remainRange)
            return;

        m_remainRange = remainRange;
        emit remainRangeChanged(m_remainRange);
    }
    void setCarInfoTyreLFPressure(QVariant carInfoTyreLFPressure)
    {
        if (m_carInfoTyreLFPressure == carInfoTyreLFPressure)
            return;

        m_carInfoTyreLFPressure = carInfoTyreLFPressure;
        emit carInfoTyreLFPressureChanged(m_carInfoTyreLFPressure);
    }
    void setCarInfoTyreRFPressure(QVariant carInfoTyreRFPressure)
    {
        if (m_carInfoTyreRFPressure == carInfoTyreRFPressure)
            return;

        m_carInfoTyreRFPressure = carInfoTyreRFPressure;
        emit carInfoTyreRFPressureChanged(m_carInfoTyreRFPressure);
    }
    void setCarInfoTyreLRPressure(QVariant carInfoTyreLRPressure)
    {
        if (m_carInfoTyreLRPressure == carInfoTyreLRPressure)
            return;

        m_carInfoTyreLRPressure = carInfoTyreLRPressure;
        emit carInfoTyreLRPressureChanged(m_carInfoTyreLRPressure);
    }
    void setCarInfoTyreRRPressure(QVariant carInfoTyreRRPressure)
    {
        if (m_carInfoTyreRRPressure == carInfoTyreRRPressure)
            return;

        m_carInfoTyreRRPressure = carInfoTyreRRPressure;
        emit carInfoTyreRRPressureChanged(m_carInfoTyreRRPressure);
    }
    void setCarInfoTyreLFTemp(QVariant carInfoTyreLFTemp)
    {
        if (m_carInfoTyreLFTemp == carInfoTyreLFTemp)
            return;

        m_carInfoTyreLFTemp = carInfoTyreLFTemp;
        emit carInfoTyreLFTempChanged(m_carInfoTyreLFTemp);
    }
    void setCarInfoTyreRFTemp(QVariant carInfoTyreRFTemp)
    {
        if (m_carInfoTyreRFTemp == carInfoTyreRFTemp)
            return;

        m_carInfoTyreRFTemp = carInfoTyreRFTemp;
        emit carInfoTyreRFTempChanged(m_carInfoTyreRFTemp);
    }
    void setCarInfoTyreLRTemp(QVariant carInfoTyreLRTemp)
    {
        if (m_carInfoTyreLRTemp == carInfoTyreLRTemp)
            return;

        m_carInfoTyreLRTemp = carInfoTyreLRTemp;
        emit carInfoTyreLRTempChanged(m_carInfoTyreLRTemp);
    }
    void setCarInfoTyreRRTemp(QVariant carInfoTyreRRTemp)
    {
        if (m_carInfoTyreRRTemp == carInfoTyreRRTemp)
            return;

        m_carInfoTyreRRTemp = carInfoTyreRRTemp;
        emit carInfoTyreRRTempChanged(m_carInfoTyreRRTemp);
    }
    void setAfterStartDrivingDistance(QVariant afterStartDrivingDistance)
    {
        if (m_afterStartDrivingDistance == afterStartDrivingDistance)
            return;

        m_afterStartDrivingDistance = afterStartDrivingDistance;
        emit afterStartDrivingDistanceChanged(m_afterStartDrivingDistance);
    }
    void setAfterStartDrivingTime(QVariant afterStartDrivingTime)
    {
        if (m_afterStartDrivingTime == afterStartDrivingTime)
            return;

        m_afterStartDrivingTime = afterStartDrivingTime;
        emit afterStartDrivingTimeChanged(m_afterStartDrivingTime);
    }
    void setAfterStartAvgSpeed(QVariant afterStartAvgSpeed)
    {
        if (m_afterStartAvgSpeed == afterStartAvgSpeed)
            return;

        m_afterStartAvgSpeed = afterStartAvgSpeed;
        emit afterStartAvgSpeedChanged(m_afterStartAvgSpeed);
    }
    void setAfterStartAvgEnergy(QVariant afterStartAvgEnergy)
    {
        if (m_afterStartAvgEnergy == afterStartAvgEnergy)
            return;

        m_afterStartAvgEnergy = afterStartAvgEnergy;
        emit afterStartAvgEnergyChanged(m_afterStartAvgEnergy);
    }
    void setAfterResetDrivingDistance(QVariant afterResetDrivingDistance)
    {
        if (m_afterResetDrivingDistance == afterResetDrivingDistance)
            return;

        m_afterResetDrivingDistance = afterResetDrivingDistance;
        emit afterResetDrivingDistanceChanged(m_afterResetDrivingDistance);
    }
    void setAfterResetDrivingTime(QVariant afterResetDrivingTime)
    {
        if (m_afterResetDrivingTime == afterResetDrivingTime)
            return;

        m_afterResetDrivingTime = afterResetDrivingTime;
        emit afterResetDrivingTimeChanged(m_afterResetDrivingTime);
    }
    void setAfterResetAvgSpeed(QVariant afterResetAvgSpeed)
    {
        if (m_afterResetAvgSpeed == afterResetAvgSpeed)
            return;

        m_afterResetAvgSpeed = afterResetAvgSpeed;
        emit afterResetAvgSpeedChanged(m_afterResetAvgSpeed);
    }
    void setAfterResetAvgEnergy(QVariant afterResetAvgEnergy)
    {
        if (m_afterResetAvgEnergy == afterResetAvgEnergy)
            return;

        m_afterResetAvgEnergy = afterResetAvgEnergy;
        emit afterResetAvgEnergyChanged(m_afterResetAvgEnergy);
    }
    void setCardIndicatorNum(QVariant cardIndicatorNum)
    {
        if (m_cardIndicatorNum == cardIndicatorNum)
            return;

        m_cardIndicatorNum = cardIndicatorNum;
        emit cardIndicatorNumChanged(m_cardIndicatorNum);
    }
    void setIsCarInfoChildIndex(QVariant isCarInfoChildIndex)
    {
        if (m_isCarInfoChildIndex == isCarInfoChildIndex)
            return;

        m_isCarInfoChildIndex = isCarInfoChildIndex;
        emit isCarInfoChildIndexChanged(m_isCarInfoChildIndex);
    }
    void setIsCardShown(QVariant isCardShown)
    {
        if (m_isCardShown == isCardShown)
            return;

        m_isCardShown = isCardShown;
        emit isCardShownChanged(m_isCardShown);
    }
    void setChargeDay(QVariant chargeDay)
    {
        if (m_chargeDay == chargeDay)
            return;

        m_chargeDay = chargeDay;
        emit chargeDayChanged(m_chargeDay);
    }
    void setChargeHour(QVariant chargeHour)
    {
        if (m_chargeHour == chargeHour)
            return;

        m_chargeHour = chargeHour;
        emit chargeHourChanged(m_chargeHour);
    }
    void setChargeOdo(QVariant chargeOdo)
    {
        if (m_chargeOdo == chargeOdo)
            return;

        m_chargeOdo = chargeOdo;
        emit chargeOdoChanged(m_chargeOdo);
    }
    void setAverageAPC(QVariant averageAPC)
    {
        if (m_averageAPC == averageAPC)
            return;

        m_averageAPC = averageAPC;
        emit averageAPCChanged(m_averageAPC);
    }
    void setCurrentAPC(QVariant currentAPC)
    {
        if (m_currentAPC == currentAPC)
            return;

        m_currentAPC = currentAPC;
        emit currentAPCChanged(m_currentAPC);
        setEnergyList(currentAPC);
    }
};

#endif // CARINFOSCREEN_H
