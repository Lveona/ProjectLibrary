#ifndef TELLTALESSCREEN_H
#define TELLTALESSCREEN_H

#include "telltalesControl.h"
#include "telltale.h"

class QQuickView;
class TelltalesScreen:  public CBaseScreen, public CSingleton<TelltalesScreen>
{
    Q_OBJECT
    Q_PROPERTY(QVariant accSpeed READ accSpeed WRITE setAccSpeed NOTIFY accSpeedChanged)//acc speed
    Q_PROPERTY(QVariant speedlimit READ speedlimit WRITE setSpeedlimit NOTIFY speedlimitChanged)//speed limit

    Q_PROPERTY(QVariant backLeftNotFasten READ backLeftNotFasten WRITE setBackLeftNotFasten NOTIFY backLeftNotFastenChanged)//安全带后左未系
    Q_PROPERTY(QVariant backRightNotFasten READ backRightNotFasten WRITE setBackRightNotFasten NOTIFY backRightNotFastenChanged)//安全带后右未系
    Q_PROPERTY(QVariant backMinNotFasten READ backMinNotFasten WRITE setBackMinNotFasten NOTIFY backMinNotFastenChanged)//安全带后中未系

    Q_PROPERTY(QVariant backLeftSeatEmpty READ backLeftSeatEmpty WRITE setBackLeftSeatEmpty NOTIFY backLeftSeatEmptyChanged)//安全带后左未坐人
    Q_PROPERTY(QVariant backRightSeatEmpty READ backRightSeatEmpty WRITE setBackRightSeatEmpty NOTIFY backRightSeatEmptyChanged)//安全带后右未坐人
    Q_PROPERTY(QVariant backMinSeatEmpty READ backMinSeatEmpty WRITE setBackMinSeatEmpty NOTIFY backMinSeatEmptyChanged)//安全带后中未坐人
    friend class CSingleton<TelltalesScreen>;
    Q_ENUMS(COLORTYPEQML)
    Q_ENUMS(TELLTALESID)


public:
    enum COLORTYPEQML
    {
        COLORTYPEQML_NONE = 0,
        COLORTYPEQML_GREEN,
        COLORTYPEQML_WHITE,
        COLORTYPEQML_RED,
        COLORTYPEQML_YELLOW,
        COLORTYPEQML_GRAY,
        COLORTYPEQML_BLUE,
    };

    enum TELLTALESID
    {
        PROPERTYID_NONE = 0x00,
        PROPERTYID_CoolantAlarmLamp,//电机/电池冷却液报警
        PROPERTYID_TurnLeftLamp,//左转向灯 //危险警告灯指示
        PROPERTYID_TurnRightLamp ,//右转向灯 //危险警告灯指示
        PROPERTYID_LowBeamLamp ,//近光灯
        PROPERTYID_HighBeamLamp ,//远光灯
        PROPERTYID_LowPowerWarLamp ,//低电量报警报警指示灯
        PROPERTYID_VcuHvBattErrLamp ,//动力电池不可用故障报警
        PROPERTYID_EBDFaultLamp,//EBD故障指示灯
        PROPERTYID_EpsSteerWarnLamp ,//转向助力系统失效故障指示灯
        PROPERTYID_DcdcFailrLamp ,//DCDC故障报警提示
        PROPERTYID_PosiLamp ,//位置灯指示
        PROPERTYID_EMotorAlarm ,//电机系统严重故障报警（电机及控制器过热报警）
        PROPERTYID_MainDrvrLamp ,//主驾安全带未系
        PROPERTYID_PassDriverLamp ,//副驾安全带未系
        PROPERTYID_BackLeftLamp ,//后排左安全带未系
        PROPERTYID_BackMiddleLamp ,//后排中安全带未系
        PROPERTYID_BackRightLamp ,//后排右安全带未系
        PROPERTYID_AntiLockBrakeLamp ,//制动防抱死功能故障
        PROPERTYID_EpbLamp ,//驻车指示灯
        PROPERTYID_EpbFltLamp ,//电子驻车系统故障
        PROPERTYID_ChrgCnctrDetdLamp ,//充电线连接指示灯
        PROPERTYID_SystemFailureLamp,//整车系统故障
        PROPERTYID_SysPowerLimitationLamp,//车辆限功率提示
        PROPERTYID_HDC,//HDC指示灯
        PROPERTYID_BatteryHeat,//动力电池过热指示灯
        PROPERTYID_FogLamp,//后雾灯指示灯
        PROPERTYID_AirbagLamp,//安全气囊指示灯
        PROPERTYID_ESCTCS,//ESCTCS
        PROPERTYID_ESCTCSOff,//ESCTCSOff
        PROPERTYID_AVH,//AVH工作中
        PROPERTYID_AirSuspension_Fault,//空气悬架故障
        PROPERTYID_Tire,//胎压报警灯
        PROPERTYID_LowSpeedLamp,//低速行人报警
        PROPERTYID_chargingLamp,//车辆续驶里程显示
        PROPERTYID_autoLamp,//智能远光指示灯
        PROPERTYID_FCSLamp,//FCS灯
        PROPERTYID_ACCLamp,//ACC灯
        PROPERTYID_HWALamp,//HWA灯
        PROPERTYID_WiperfaultLamp,//前雨刷故障
        PROPERTYID_FrontbonnetfaultLamp,//前舱盖未关
        PROPERTYID_AccStatusLamp,//Acc状态
        PROPERTYID_HWAStatusLamp,//HWA状态
        PROPERTYID_SpeedLimitLamp,//限速标志
        PROPERTYID_SpeedLimitCancelLamp,//限速取消标志
        PROPERTYID_ParkLockLamp,//p档锁故障
        PROPERTYID_VehSrvcWarn, //动力系统异常无响应
        PROPERTYID_MAX
    };

    enum PROPERTYID_TELL
    {
        PROPERTYID_LEFT_NOTFASTEN = 0x0,
        PROPERTYID_MID_NOTFASTEN,
        PROPERTYID_RIGHT_NOTFASTEN,

        PROPERTYID_LEFT_SEATEMPTY,
        PROPERTYID_MID_SEATEMPTY,
        PROPERTYID_RIGHT_SEATEMPTY,

        PROPERTYID_ACC_SPEED,
        PROPERTYID_SPEED_LIMIT,
    };

    TelltalesScreen();
    ~TelltalesScreen();

    typedef void ( TelltalesScreen::* FunctionParser )(QVariant value);
//    typedef void ( TelltalesScreen::* FunctionParserTellData )(TellData*);

    virtual void startControl();
    void createCtrl(QQuickView *view);

//    TellData* cruiseLight() const
//    {
//        return m_cruiseLight;
//    }

    QVariant accSpeed() const
    {
        return m_accSpeed;
    }

    QVariant speedlimit() const
    {
        return m_speedlimit;
    }

    QVariant backLeftNotFasten() const
    {
        return m_backLeftNotFasten;
    }

    QVariant backRightNotFasten() const
    {
        return m_backRightNotFasten;
    }

    QVariant backMinNotFasten() const
    {
        return m_backMinNotFasten;
    }

    QVariant backLeftSeatEmpty() const
    {
        return m_backLeftSeatEmpty;
    }

    QVariant backRightSeatEmpty() const
    {
        return m_backRightSeatEmpty;
    }

    QVariant backMinSeatEmpty() const
    {
        return m_backMinSeatEmpty;
    }

public slots:
    void SetProperty(int index, const TellData tell);
    void SetProperty(int name,QVariant value);

//    QObject* getTellList(int index){
//        return m_telltaleStates.at(index);
//    }

    QList<QObject*> getTellListAll(){
        return m_telltaleStates;
    }

    void setAccSpeed(QVariant accSpeed)
    {
        if (m_accSpeed == accSpeed)
            return;

        m_accSpeed = accSpeed;
        emit accSpeedChanged(m_accSpeed);
    }

    void setSpeedlimit(QVariant speedlimit)
    {
        if (m_speedlimit == speedlimit)
            return;

        m_speedlimit = speedlimit;
        emit speedlimitChanged(m_speedlimit);
    }

    void setBackLeftNotFasten(QVariant backLeftNotFasten)
    {
        if (m_backLeftNotFasten == backLeftNotFasten)
            return;

        m_backLeftNotFasten = backLeftNotFasten;
        emit backLeftNotFastenChanged(m_backLeftNotFasten);
    }

    void setBackRightNotFasten(QVariant backRightNotFasten)
    {
        if (m_backRightNotFasten == backRightNotFasten)
            return;

        m_backRightNotFasten = backRightNotFasten;
        emit backRightNotFastenChanged(m_backRightNotFasten);
    }

    void setBackMinNotFasten(QVariant backMinNotFasten)
    {
        if (m_backMinNotFasten == backMinNotFasten)
            return;

        m_backMinNotFasten = backMinNotFasten;
        emit backMinNotFastenChanged(m_backMinNotFasten);
    }

    void setBackLeftSeatEmpty(QVariant backLeftSeatEmpty)
    {
        if (m_backLeftSeatEmpty == backLeftSeatEmpty)
            return;

        m_backLeftSeatEmpty = backLeftSeatEmpty;
        emit backLeftSeatEmptyChanged(m_backLeftSeatEmpty);
    }

    void setBackRightSeatEmpty(QVariant backRightSeatEmpty)
    {
        if (m_backRightSeatEmpty == backRightSeatEmpty)
            return;

        m_backRightSeatEmpty = backRightSeatEmpty;
        emit backRightSeatEmptyChanged(m_backRightSeatEmpty);
    }

    void setBackMinSeatEmpty(QVariant backMinSeatEmpty)
    {
        if (m_backMinSeatEmpty == backMinSeatEmpty)
            return;

        m_backMinSeatEmpty = backMinSeatEmpty;
        emit backMinSeatEmptyChanged(m_backMinSeatEmpty);
    }

signals:

    void accSpeedChanged(QVariant accSpeed);

    void speedlimitChanged(QVariant speedlimit);

    void backLeftNotFastenChanged(QVariant backLeftNotFasten);

    void backRightNotFastenChanged(QVariant backRightNotFasten);

    void backMinNotFastenChanged(QVariant backMinNotFasten);

    void backLeftSeatEmptyChanged(QVariant backLeftSeatEmpty);

    void backRightSeatEmptyChanged(QVariant backRightSeatEmpty);

    void backMinSeatEmptyChanged(QVariant backMinSeatEmpty);

private:
    QQuickView * m_view;

    QList<QObject*> m_telltaleStates;
    QVariant m_accSpeed;
    QVariant m_speedlimit;
    QVariant m_backLeftNotFasten;
    QVariant m_backRightNotFasten;
    QVariant m_backMinNotFasten;
    QVariant m_backLeftSeatEmpty;
    QVariant m_backRightSeatEmpty;
    QVariant m_backMinSeatEmpty;
};
Q_DECLARE_METATYPE(TelltalesScreen::COLORTYPEQML)

#endif // TELLTALESSCREEN_H
