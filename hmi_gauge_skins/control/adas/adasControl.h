#ifndef ADASCONTROL_H
#define ADASCONTROL_H


#include <libaudio.h>
#include <hmi_share.h>
#include "adasEnums.h"
#include "adasTarget.h"

#define LINE_1_MAX_CURVATURE  3.0;
#define LINE_2_MAX_CURVATURE  3.0;
#define LINE_3_MAX_CURVATURE  3.0;
#define LINE_4_MAX_CURVATURE  3.0;
#define miniAdasValueMax  20;
//#define NONE     0
class WorkingStateFlash;

//#define ADAS_ON
//adas信号未对应，暂时不能编译0422
enum PROPERTYID
{
    ADASTAEGET_T0,
    ADASTAEGET_T1,
    ADASTAEGET_T2,
    ADASTAEGET_T3,
    ADASTAEGET_T4,
    ADASTAEGET_T5,
    ADASTAEGET_MAX,
};
enum PROPERTYID_ADAS {
    PROPERTYID_NONE,
    PROPERTYID_ADAS_WORKING_STATE,
    PROPERTYID_ADAS_DOW_FL,
    PROPERTYID_ADAS_DOW_RL,
    PROPERTYID_ADAS_DOW_FR,
    PROPERTYID_ADAS_DOW_RR,
    PROPERTYID_ADAS_RCW_WARN,
    PROPERTYID_ADAS_FCW_WARN,
    PROPERTYID_RCTA_LEFT_WARN,
    PROPERTYID_RCTA_RIGHT_WARN,
    PROPERTYID_LCA_LEFT_WARN,
    PROPERTYID_LCA_RIGHT_WARN,
    PROPERTYID_L3AVAILABLESTATUS,
    PROPERTYID_LANELINE1_COLOR,
    PROPERTYID_LANELINE2_COLOR,
    PROPERTYID_LANELINE3_COLOR,
    PROPERTYID_LANELINE4_COLOR,

    PROPERTYID_LANELINE1_DISPLAY,
    PROPERTYID_LANELINE2_DISPLAY,
    PROPERTYID_LANELINE3_DISPLAY,
    PROPERTYID_LANELINE4_DISPLAY,
    PROPERTYID_LANELINE1_TYPE,
    PROPERTYID_LANELINE2_TYPE,
    PROPERTYID_LANELINE3_TYPE,
    PROPERTYID_LANELINE4_TYPE,
    PROPERTYID_LANELINE1_CURVATURE,
    PROPERTYID_LANELINE2_CURVATURE,
    PROPERTYID_LANELINE3_CURVATURE,
    PROPERTYID_LANELINE4_CURVATURE,

    PROPERTYID_FCTA_LEFT_WARN,
    PROPERTYID_FCTA_RIGHT_WARN,
    PROPERTYID_ACC_OBJECTCAPTUREDSTATUS,

    PROPERTYID_ADAS_TRACKTAR0_STATIC_ST,
    PROPERTYID_ADAS_TRACKTAR1_STATIC_ST,
    PROPERTYID_ADAS_TRACKTAR2_STATIC_ST,
    PROPERTYID_ADAS_TRACKTAR3_STATIC_ST,
    PROPERTYID_ADAS_TRACKTAR4_STATIC_ST,
    PROPERTYID_ADAS_TRACKTAR5_STATIC_ST,


    PROPERTYID_ADAS_TRACKTARGET0_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET1_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET2_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET3_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET4_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET5_OBJECTTYPE,

    PROPERTYID_ADAS_TRACKTARGET0_STATIC_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET1_STATIC_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET2_STATIC_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET3_STATIC_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET4_STATIC_OBJECTTYPE,
    PROPERTYID_ADAS_TRACKTARGET5_STATIC_OBJECTTYPE,

    PROPERTYID_ADAS_TRACKTAR0_STATIC_LGTPO,
    PROPERTYID_ADAS_TRACKTAR1_STATIC_LGTPO,
    PROPERTYID_ADAS_TRACKTAR2_STATIC_LGTPO,
    PROPERTYID_ADAS_TRACKTAR3_STATIC_LGTPO,
    PROPERTYID_ADAS_TRACKTAR4_STATIC_LGTPO,
    PROPERTYID_ADAS_TRACKTAR5_STATIC_LGTPO,
    PROPERTYID_ADAS_TRACKTAR0_STATIC_LATPO,
    PROPERTYID_ADAS_TRACKTAR1_STATIC_LATPO,
    PROPERTYID_ADAS_TRACKTAR2_STATIC_LATPO,
    PROPERTYID_ADAS_TRACKTAR3_STATIC_LATPO,
    PROPERTYID_ADAS_TRACKTAR4_STATIC_LATPO,
    PROPERTYID_ADAS_TRACKTAR5_STATIC_LATPO,

    PROPERTYID_ANRC_PRKGSTSINDCR,
    PROPERTYID_ANRC_PRKGLESLOTTYP1,
    PROPERTYID_ANRC_PRKGLESLOTTYP2,
    PROPERTYID_ANRC_PRKGLESLOTTYP3,
    PROPERTYID_ANRC_PRKGRISLOTTYP1,
    PROPERTYID_ANRC_PRKGRISLOTTYP2,
    PROPERTYID_ANRC_PRKGRISLOTTYP3,

    PROPERTYID_PARK_UP_DISTANCE,
    PROPERTYID_PARK_DOWN_DISTANCE,
    PROPERTYID_PARK_UP_DISTANCE_COLOR,
    PROPERTYID_PARK_DOWN_DISTANCE_COLOR,
    PROPERTYID_PARK_LEFT_DISTANCE_COLOR,
    PROPERTYID_PARK_RIGHT_DISTANCE_COLOR,
    PROPERTYID_ILC_LEFT,
    PROPERTYID_ILC_RIGHT,
    PROPERTYID_ILC_LEFT_VISIBLE,
    PROPERTYID_ILC_RIGHT_VISIBLE,
    PROPERTYID_MINIADAS_VISIBLE,
    PROPERTYID_ACC_TIME_GAP,
    PROPERTYID_ACC_TIME_GAP_VISIBLE,
    PROPERTYID_RCTA_LEFT_WARN_F,
    PROPERTYID_LCA_LEFT_WARN_F,
    PROPERTYID_LCA_RIGHT_WARN_F,
    PROPERTYID_ILC_LEFT_F,
    PROPERTYID_ILC_RIGHT_F,
    PROPERTYID_ADAS_FCW_WARN_F,
    PROPERTYID_ADAS_RCW_WARN_F,
    PROPERTYID_FCTA_LEFT_WARN_F,
    PROPERTYID_FCTA_RIGHT_WARN_F,
    PROPERTYID_RCTA_RIGHT_WARN_F,
};

enum MINI_VISIBLE{
    CARDOOR_FL = 0x0,
    CARDOOR_RL,
    CARDOOR_FR,
    CARDOOR_RR,
    RCTA_LEFT,
    RCTA_RIGHT,
    LCA_LEFT,
    LCA_RIGHT,
    ILC_ACTIVE,
    FCW_ACTIVE,
    RCW_ACTIVE,
    LKS_ACTIVE,
    ELK_ACTIVE,
    FCTA_LEFT,
    FCTA_RIGHT,

    MINI_VISIBLE_MAX
};

class ADASControl : public CBaseControl, public CSingleton<ADASControl>
{
    Q_OBJECT
public:
    ADASControl();
    ~ADASControl();

    void handleDoorWarn();
    void handleRctaLeftWarn();
    void handleRctaRightWarn();
    void handleLcaLeftWarn();
    void handleLcaRightWarn();
    void handleHwaIlcSt();
    void handleL3Availablestatus();
    void handWarningMap();
    void handLaneLinesColor();
    void handLaneLinesDisplay();
    void handLaneLinesType();
    void handLaneLine1CurVature();
    void handLaneLine2CurVature();
    void handLaneLine3CurVature();
    void handLaneLine4CurVature();
    void handFctaLeftWarn();
    void handFctaRightWarn();
    void handAccObjectCapturedStatus();
    ADASEnums::qmlTargetObjectType getTrackTargetObjectType(const PROPERTYID_ADAS& propertyId,const int& value);
    void handTrackTar();
    void handTrackTarStaticObjectType();
    void handTrackTar_Static_LgtPo();
    void handTrackTar_Static_LatPo();
        //泊车
    void handAnrcPrkgStsIndcr();
    void handAnrcAnrcPrkgLeSlotTyp();
    void handAnrcAnrcPrkgRiSlotTyp();

    void handParkUpDistance();
    void handParkDownDistance();
    void handParkLeftDistance();
    void handParkRightDistance();

    void checkDistanceValue(const int& value, int &distance);
    void checkDistanceValue(const int& value,ADASEnums::qmlParkDistance& distance);
    void handPark_Up_Down_Distance_Color(const PROPERTYID_ADAS& propertyId,const int& value);

    void handleTarget0Object();
    void handleTarget1Object();
    void handleTarget2Object();
    void handleTarget3Object();
    void handleTarget4Object();
    void handleTarget5Object();
    void handleACCTimeGap();
    void handleAdasTarget(AdasTarget*);
    typedef void ( ADASControl::* FunctionParser )();

    HMICustomTimer* m_leftILCTime;
    HMICustomTimer* m_rightILCTime;
    HMICustomTimer* m_gapTimer;
signals:
    void notifyADASWaring();             //ADAS报警
    void PropertyChange(int index, const TargetData tell);

public slots:

    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void get_timeout500ms();
    void get_timeout10ms();
    void get_timeout250ms();

protected:

    void dataChange();

private:
    QMutex mutex;
    void iC_Can_Info_Send(int reqSendID);
    WorkingStateFlash* M_ARDS_WORKING_STATE;
    void func_adas_AudioPlay(Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd);
    QMap <PROPERTYID_ADAS,ADASEnums::qmlWarnLevel> m_WarningMap;
    QByteArray  miniAdasValue;
} ;

/*
 * 封装一个特殊的闪烁类,实现非1hz闪烁功能
*/
class WorkingStateFlash: public QObject
{
    Q_OBJECT
public:
    WorkingStateFlash(int circle)
    {
        _circle = circle/10;
        m_timercnt = -1;
    }
    ~WorkingStateFlash(){}
    void  update(){

            if(m_timercnt>=0)
            {
                m_timercnt++;
                if(m_timercnt >= _circle) m_timercnt = 0;
                if(m_timercnt == 0)
                {
                    _state = !_state;
                    emit stateChange(_state);
                }
            }


    }
    void start()
    {
        m_timercnt = 0;
        _state = true;
        emit stateChange(_state);
    }
    void stop()
    {
        m_timercnt = -1;
        _state = false;
    }

    bool running() {
        return m_timercnt>=0?true:false;
    }

signals:
    void stateChange(bool state);
private:
    int m_timercnt;
    int _circle;
    bool _state;

};

#endif // ADASCONTROL_H
