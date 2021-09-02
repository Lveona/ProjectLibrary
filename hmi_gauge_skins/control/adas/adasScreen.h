#ifndef ADASSCREEN_H
#define ADASSCREEN_H

#include "adasControl.h"
#include "adasEnums.h"
#include "adasTarget.h"

class ADASScreen : public CBaseScreen, public CSingleton<ADASScreen>
{
    Q_OBJECT

    //公共枚举
    Q_PROPERTY(ADASEnums* adasEnumsObject READ getAdasEnumsObject WRITE setAdasEnumsObject NOTIFY adasEnumsObjectChanged)

    //门开提示 左前门 右前门 左后门 右后门
    Q_PROPERTY(QVariant ADAS_DOW_FL READ ADAS_DOW_FL WRITE setADAS_DOW_FL NOTIFY ADAS_DOW_FLChanged)
    Q_PROPERTY(QVariant ADAS_DOW_RL READ ADAS_DOW_RL WRITE setADAS_DOW_RL NOTIFY ADAS_DOW_RLChanged)
    Q_PROPERTY(QVariant ADAS_DOW_FR READ ADAS_DOW_FR WRITE setADAS_DOW_FR NOTIFY ADAS_DOW_FRChanged)
    Q_PROPERTY(QVariant ADAS_DOW_RR READ ADAS_DOW_RR WRITE setADAS_DOW_RR NOTIFY ADAS_DOW_RRChanged)

    //追尾预警
    Q_PROPERTY(QVariant RCW_WARN READ RCW_WARN WRITE setRCW_WARN NOTIFY RCW_WARNChanged)
    //前碰撞预警
    Q_PROPERTY(QVariant FCW_WARN READ FCW_WARN WRITE setFCW_WARN NOTIFY FCW_WARNChanged)

    //碰撞提示左后侧
    Q_PROPERTY(QVariant RCTA_LEFT_WARN READ RCTA_LEFT_WARN WRITE setRCTA_LEFT_WARN NOTIFY RCTA_LEFT_WARNChanged)
    //碰撞提示右后侧
    Q_PROPERTY(QVariant RCTA_RIGHT_WARN READ RCTA_RIGHT_WARN WRITE setRCTA_RIGHT_WARN NOTIFY RCTA_RIGHT_WARNChanged)

    //BSD盲区检测 左后侧 右后侧
    Q_PROPERTY(QVariant LCA_LEFT_WARN READ LCA_LEFT_WARN WRITE setLCA_LEFT_WARN NOTIFY LCA_LEFT_WARNChanged)
    Q_PROPERTY(QVariant LCA_RIGHT_WARN READ LCA_RIGHT_WARN WRITE setLCA_RIGHT_WARN NOTIFY LCA_RIGHT_WARNChanged)

    //车道线颜色
    Q_PROPERTY(QVariant laneLine3_Color READ laneLine3_Color WRITE setLaneLine3_Color NOTIFY laneLine3Changed)
    Q_PROPERTY(QVariant laneLine1_Color READ laneLine1_Color WRITE setLaneLine1_Color NOTIFY laneLine1Changed)
    Q_PROPERTY(QVariant laneLine2_Color READ laneLine2_Color WRITE setLaneLine2_Color NOTIFY laneLine2Changed)
    Q_PROPERTY(QVariant laneLine4_Color READ laneLine4_Color WRITE setLaneLine4_Color NOTIFY laneLine4Changed)

    //---
    //车道线显示
    Q_PROPERTY(QVariant laneLine3_Display READ laneLine3_Display WRITE setLaneLine3_Display NOTIFY laneLine3_DisplayChanged)
    Q_PROPERTY(QVariant laneLine1_Display READ laneLine1_Display WRITE setLaneLine1_Display NOTIFY laneLine1_DisplayChanged)
    Q_PROPERTY(QVariant laneLine2_Display READ laneLine2_Display WRITE setLaneLine2_Display NOTIFY laneLine2_DisplayChanged)
    Q_PROPERTY(QVariant laneLine4_Display READ laneLine4_Display WRITE setLaneLine4_Display NOTIFY laneLine4_DisplayChanged)

    //车道线类型
    Q_PROPERTY(QVariant laneLine3_Type READ laneLine3_Type WRITE setLaneLine3_Type NOTIFY laneLine3_TypeChanged)
    Q_PROPERTY(QVariant laneLine1_Type READ laneLine1_Type WRITE setLaneLine1_Type NOTIFY laneLine1_TypeChanged)
    Q_PROPERTY(QVariant laneLine2_Type READ laneLine2_Type WRITE setLaneLine2_Type NOTIFY laneLine2_TypeChanged)
    Q_PROPERTY(QVariant laneLine4_Type READ laneLine4_Type WRITE setLaneLine4_Type NOTIFY laneLine4_TypeChanged)

    //车道线曲率
    Q_PROPERTY(QVariant laneLine1_Curv READ laneLine1_Curv WRITE setLaneLine1_Curv NOTIFY laneLine1_CurvChanged)
    Q_PROPERTY(QVariant laneLine2_Curv READ laneLine2_Curv WRITE setLaneLine2_Curv NOTIFY laneLine2_CurvChanged)
    Q_PROPERTY(QVariant laneLine4_Curv READ laneLine4_Curv WRITE setLaneLine4_Curv NOTIFY laneLine4_CurvChanged)
    Q_PROPERTY(QVariant laneLine3_Curv READ laneLine3_Curv WRITE setLaneLine3_Curv NOTIFY laneLine3_CurvChanged)

    //FCTA 左前侧 右前侧碰撞提示
    Q_PROPERTY(QVariant fctaLeft READ fctaLeft WRITE setFctaLeft NOTIFY fctaLeftChanged)
    Q_PROPERTY(QVariant fctaRight READ fctaRight WRITE setFctaRight NOTIFY fctaRightChanged)

    //跟车高亮
    Q_PROPERTY(QVariant objectCapturedStatus READ objectCapturedStatus WRITE setObjectCapturedStatus NOTIFY objectCapturedStatusChanged)

    //静态目标是否显示
    Q_PROPERTY(QVariant trackTarget0_Static_st READ trackTarget0_Static_st WRITE setTrackTarget0_Static_st NOTIFY trackTarget0_Static_stChanged)
    Q_PROPERTY(QVariant trackTarget1_Static_st READ trackTarget1_Static_st WRITE setTrackTarget1_Static_st NOTIFY trackTarget1_Static_stChanged)
    Q_PROPERTY(QVariant trackTarget2_Static_st READ trackTarget2_Static_st WRITE setTrackTarget2_Static_st NOTIFY trackTarget2_Static_stChanged)
    Q_PROPERTY(QVariant trackTarget3_Static_st READ trackTarget3_Static_st WRITE setTrackTarget3_Static_st NOTIFY trackTarget3_Static_stChanged)
    Q_PROPERTY(QVariant trackTarget4_Static_st READ trackTarget4_Static_st WRITE setTrackTarget4_Static_st NOTIFY trackTarget4_Static_stChanged)
    Q_PROPERTY(QVariant trackTarget5_Static_st READ trackTarget5_Static_st WRITE setTrackTarget5_Static_st NOTIFY trackTarget5_Static_stChanged)

    //静态目标物类型
    Q_PROPERTY(QVariant trackTarget0_Static_ObjectType READ trackTarget0_Static_ObjectType WRITE setTrackTarget0_Static_ObjectType NOTIFY trackTarget0_Static_ObjectTypeChanged)
    Q_PROPERTY(QVariant trackTarget1_Static_ObjectType READ trackTarget1_Static_ObjectType WRITE setTrackTarget1_Static_ObjectType NOTIFY trackTarget1_Static_ObjectTypeChanged)
    Q_PROPERTY(QVariant trackTarget2_Static_ObjectType READ trackTarget2_Static_ObjectType WRITE setTrackTarget2_Static_ObjectType NOTIFY trackTarget2_Static_ObjectTypeChanged)
    Q_PROPERTY(QVariant trackTarget3_Static_ObjectType READ trackTarget3_Static_ObjectType WRITE setTrackTarget3_Static_ObjectType NOTIFY trackTarget3_Static_ObjectTypeChanged)
    Q_PROPERTY(QVariant trackTarget4_Static_ObjectType READ trackTarget4_Static_ObjectType WRITE setTrackTarget4_Static_ObjectType NOTIFY trackTarget4_Static_ObjectTypeChanged)
    Q_PROPERTY(QVariant trackTarget5_Static_ObjectType READ trackTarget5_Static_ObjectType WRITE setTrackTarget5_Static_ObjectType NOTIFY trackTarget5_Static_ObjectTypeChanged)

    //静态目标物横向坐标 纵向坐标
    Q_PROPERTY(QVariant trackTar0_Static_LATPO READ trackTar0_Static_LATPO WRITE setTrackTar0_Static_LATPO NOTIFY trackTar0_Static_LATPOChanged)
    Q_PROPERTY(QVariant trackTar1_Static_LATPO READ trackTar1_Static_LATPO WRITE setTrackTar1_Static_LATPO NOTIFY trackTar1_Static_LATPOChanged)
    Q_PROPERTY(QVariant trackTar2_Static_LATPO READ trackTar2_Static_LATPO WRITE setTrackTar2_Static_LATPO NOTIFY trackTar2_Static_LATPOChanged)
    Q_PROPERTY(QVariant trackTar3_Static_LATPO READ trackTar3_Static_LATPO WRITE setTrackTar3_Static_LATPO NOTIFY trackTar3_Static_LATPOChanged)
    Q_PROPERTY(QVariant trackTar4_Static_LATPO READ trackTar4_Static_LATPO WRITE setTrackTar4_Static_LATPO NOTIFY trackTar4_Static_LATPOChanged)
    Q_PROPERTY(QVariant trackTar5_Static_LATPO READ trackTar5_Static_LATPO WRITE setTrackTar5_Static_LATPO NOTIFY trackTar5_Static_LATPOChanged)

    Q_PROPERTY(QVariant trackTar0_Static_LGTP0 READ trackTar0_Static_LGTP0 WRITE setTrackTar0_Static_LGTP0 NOTIFY trackTar0_Static_LGTP0Changed)
    Q_PROPERTY(QVariant trackTar1_Static_LGTP0 READ trackTar1_Static_LGTP0 WRITE setTrackTar1_Static_LGTP0 NOTIFY trackTar1_Static_LGTP0Changed)
    Q_PROPERTY(QVariant trackTar2_Static_LGTP0 READ trackTar2_Static_LGTP0 WRITE setTrackTar2_Static_LGTP0 NOTIFY trackTar2_Static_LGTP0Changed)
    Q_PROPERTY(QVariant trackTar3_Static_LGTP0 READ trackTar3_Static_LGTP0 WRITE setTrackTar3_Static_LGTP0 NOTIFY trackTar3_Static_LGTP0Changed)
    Q_PROPERTY(QVariant trackTar4_Static_LGTP0 READ trackTar4_Static_LGTP0 WRITE setTrackTar4_Static_LGTP0 NOTIFY trackTar4_Static_LGTP0Changed)
    Q_PROPERTY(QVariant trackTar5_Static_LGTP0 READ trackTar5_Static_LGTP0 WRITE setTrackTar5_Static_LGTP0 NOTIFY trackTar5_Static_LGTP0Changed)
    //泊车状态标志位
    Q_PROPERTY(QVariant prkgStsIndcr READ prkgStsIndcr WRITE setPrkgStsIndcr NOTIFY prkgStsIndcrChanged)
    //左侧泊车位提示
    Q_PROPERTY(QVariant prkgLeSlotTyp1 READ prkgLeSlotTyp1 WRITE setPrkgLeSlotTyp1 NOTIFY prkgLeSlotTyp1Changed)
    Q_PROPERTY(QVariant prkgLeSlotTyp2 READ prkgLeSlotTyp2 WRITE setPrkgLeSlotTyp2 NOTIFY prkgLeSlotTyp2Changed)
    Q_PROPERTY(QVariant prkgLeSlotTyp3 READ prkgLeSlotTyp3 WRITE setPrkgLeSlotTyp3 NOTIFY prkgLeSlotTyp3Changed)
    //右侧泊车位提示
    Q_PROPERTY(QVariant PrkgRiSlotTyp1 READ PrkgRiSlotTyp1 WRITE setPrkgRiSlotTyp1 NOTIFY prkgRiSlotTyp1Changed)
    Q_PROPERTY(QVariant PrkgRiSlotTyp2 READ PrkgRiSlotTyp2 WRITE setPrkgRiSlotTyp2 NOTIFY prkgRiSlotTyp2Changed)
    Q_PROPERTY(QVariant PrkgRiSlotTyp3 READ PrkgRiSlotTyp3 WRITE setPrkgRiSlotTyp3 NOTIFY prkgRiSlotTyp3Changed)

    //泊车距离显示
    Q_PROPERTY(QVariant parkUpDistance READ parkUpDistance                WRITE setParkUpDistance         NOTIFY parkUpDistanceChanged)
    Q_PROPERTY(QVariant parkDownDistance READ parkDownDistance            WRITE setParkDownDistance       NOTIFY parkDownDistanceChanged)
    Q_PROPERTY(QVariant parkUpDistanceColor READ parkUpDistanceColor      WRITE setParkUpDistanceColor    NOTIFY parkUpDistanceColorChanged)
    Q_PROPERTY(QVariant parkDownDistanceColor READ parkDownDistanceColor  WRITE setParkDownDistanceColor  NOTIFY parkDownDistanceColorChanged)
    Q_PROPERTY(QVariant parkLeftDistanceColor READ parkLeftDistanceColor  WRITE setParkLeftDistanceColor  NOTIFY parkLeftDistanceColorChanged)
    Q_PROPERTY(QVariant parkRightistanceColor READ parkRightDistanceColor WRITE setParkRightDistanceColor NOTIFY parkRightDistanceColorChanged)

    Q_PROPERTY(QVariant leftILC READ leftILC WRITE setLeftILC NOTIFY leftILCChanged)
    Q_PROPERTY(QVariant rightILC READ rightILC WRITE setRightILC NOTIFY rightILCChanged)
    Q_PROPERTY(QVariant leftILCVisible READ leftILCVisible WRITE setLeftILCVisible NOTIFY leftILCVisibleChanged)
    Q_PROPERTY(QVariant rightILCVisible READ rightILCVisible WRITE setRightILCVisible NOTIFY rightILCVisibleChanged)
    Q_PROPERTY(QVariant miniAdasVisible READ miniAdasVisible WRITE setMiniAdasVisible NOTIFY miniAdasVisibleChanged)

    //跟车距
    Q_PROPERTY(QVariant accTimeGap READ accTimeGap WRITE setAccTimeGap NOTIFY accTimeGapChanged)
    Q_PROPERTY(QVariant accTimeGapVisible READ accTimeGapVisible WRITE setAccTimeGapVisible NOTIFY accTimeGapVisibleChanged)

public:

    enum ADASTARGETID
    {
        ADASTAEGET_T0,
        ADASTAEGET_T1,
        ADASTAEGET_T2,
        ADASTAEGET_T3,
        ADASTAEGET_T4,
        ADASTAEGET_T5,
        ADASTAEGET_MAX,
    };

    ADASScreen();
    ~ADASScreen();

    typedef void ( ADASScreen::* FunctionParser )(QVariant value);

    // ADASlib to ADASScreen
    void createCtrl( QQuickView *view );
    virtual void startControl();

    ADASEnums* getAdasEnumsObject() const
    {
        return m_adasEnumsObject;
    }

    QVariant ADAS_DOW_FL() const
    {
        return m_ADAS_DOW_FL;
    }

    QVariant ADAS_DOW_RL() const
    {
        return m_ADAS_DOW_RL;
    }

    QVariant ADAS_DOW_FR() const
    {
        return m_ADAS_DOW_FR;
    }

    QVariant ADAS_DOW_RR() const
    {
        return m_ADAS_DOW_RR;
    }

    QVariant RCW_WARN() const
    {
        return m_RCW_WARN;
    }

    QVariant FCW_WARN() const
    {
        return m_FCW_WARN;
    }

    QVariant RCTA_LEFT_WARN() const
    {
        return m_RCTA_LEFT_WARN;
    }

    QVariant RCTA_RIGHT_WARN() const
    {
        return m_RCTA_RIGHT_WARN;
    }

    QVariant LCA_LEFT_WARN() const
    {
        return m_LCA_LEFT_WARN;
    }

    QVariant LCA_RIGHT_WARN() const
    {
        return m_LCA_RIGHT_WARN;
    }

    QVariant laneLine3_Color() const
    {
        return m_laneLine3_Color;
    }

    QVariant laneLine1_Color() const
    {
        return m_laneLine1_Color;
    }

    QVariant laneLine2_Color() const
    {
        return m_laneLine2_Color;
    }

    QVariant laneLine4_Color() const
    {
        return m_laneLine4_Color;
    }

    QVariant laneLine3_Display() const
    {
        return m_laneLine3_Display;
    }

    QVariant laneLine1_Display() const
    {
        return m_laneLine1_Display;
    }

    QVariant laneLine2_Display() const
    {
        return m_laneLine2_Display;
    }

    QVariant laneLine4_Display() const
    {
        return m_laneLine4_Display;
    }

    QVariant laneLine3_Type() const
    {
        return m_laneLine3_Type;
    }

    QVariant laneLine1_Type() const
    {
        return m_laneLine1_Type;
    }

    QVariant laneLine2_Type() const
    {
        return m_laneLine2_Type;
    }

    QVariant laneLine4_Type() const
    {
        return m_laneLine4_Type;
    }

    QVariant fctaRight() const
    {
        return m_fctaRight;
    }

    QVariant objectCapturedStatus() const
    {
        return m_objectCapturedStatus;
    }

    QVariant trackTarget0_Static_st() const
    {
        return m_trackTarget0_Static_st;
    }

    QVariant trackTarget1_Static_st() const
    {
        return m_trackTarget1_Static_st;
    }

    QVariant trackTarget2_Static_st() const
    {
        return m_trackTarget2_Static_st;
    }

    QVariant trackTarget3_Static_st() const
    {
        return m_trackTarget3_Static_st;
    }

    QVariant trackTarget4_Static_st() const
    {
        return m_trackTarget4_Static_st;
    }

    QVariant trackTarget5_Static_st() const
    {
        return m_trackTarget5_Static_st;
    }

    QVariant trackTarget0_Static_ObjectType() const
    {
        return m_trackTarget0_Static_ObjectType;
    }

    QVariant trackTarget1_Static_ObjectType() const
    {
        return m_trackTarget1_Static_ObjectType;
    }

    QVariant trackTarget2_Static_ObjectType() const
    {
        return m_trackTarget2_Static_ObjectType;
    }

    QVariant trackTarget3_Static_ObjectType() const
    {
        return m_trackTarget3_Static_ObjectType;
    }

    QVariant trackTarget4_Static_ObjectType() const
    {
        return m_trackTarget4_Static_ObjectType;
    }

    QVariant trackTarget5_Static_ObjectType() const
    {
        return m_trackTarget5_Static_ObjectType;
    }

    QVariant trackTar0_Static_LATPO() const
    {
        return m_trackTar0_Static_LATPO;
    }

    QVariant trackTar0_Static_LGTP0() const
    {
        return m_trackTar0_Static_LGTP0;
    }

    QVariant trackTar1_Static_LATPO() const
    {
        return m_trackTar1_Static_LATPO;
    }

    QVariant trackTar1_Static_LGTP0() const
    {
        return m_trackTar1_Static_LGTP0;
    }

    QVariant trackTar2_Static_LATPO() const
    {
        return m_trackTar2_Static_LATPO;
    }

    QVariant trackTar2_Static_LGTP0() const
    {
        return m_trackTar2_Static_LGTP0;
    }

    QVariant trackTar3_Static_LATPO() const
    {
        return m_trackTar3_Static_LATPO;
    }

    QVariant trackTar3_Static_LGTP0() const
    {
        return m_trackTar3_Static_LGTP0;
    }

    QVariant trackTar4_Static_LATPO() const
    {
        return m_trackTar4_Static_LATPO;
    }

    QVariant trackTar4_Static_LGTP0() const
    {
        return m_trackTar4_Static_LGTP0;
    }

    QVariant trackTar5_Static_LATPO() const
    {
        return m_trackTar5_Static_LATPO;
    }

    QVariant trackTar5_Static_LGTP0() const
    {
        return m_trackTar5_Static_LGTP0;
    }

    QVariant prkgStsIndcr() const
    {
        return m_prkgStsIndcr;
    }

    QVariant prkgLeSlotTyp1() const
    {
        return m_prkgLeSlotTyp1;
    }

    QVariant prkgLeSlotTyp2() const
    {
        return m_prkgLeSlotTyp2;
    }

    QVariant prkgLeSlotTyp3() const
    {
        return m_prkgLeSlotTyp3;
    }

    QVariant PrkgRiSlotTyp1() const
    {
        return m_PrkgRiSlotTyp1;
    }

    QVariant PrkgRiSlotTyp2() const
    {
        return m_PrkgRiSlotTyp2;
    }

    QVariant PrkgRiSlotTyp3() const
    {
        return m_PrkgRiSlotTyp3;
    }

    QVariant fctaLeft() const
    {
        return m_fctaLeft;
    }

    QVariant parkUpDistance() const
    {
        return m_parkUpDistance;
    }

    QVariant parkDownDistance() const
    {
        return m_parkDownDistance;
    }

    QVariant parkUpDistanceColor() const
    {
        return m_parkUpDistanceColor;
    }

    QVariant parkDownDistanceColor() const
    {
        return m_parkDownDistanceColor;
    }

    QVariant parkLeftDistanceColor() const
    {
        return m_parkLeftDistanceColor;
    }

    QVariant parkRightDistanceColor() const
    {
        return m_parkRightistanceColor;
    }

    QVariant laneLine1_Curv() const
    {
        return m_laneLine1_Curv;
    }

    QVariant laneLine2_Curv() const
    {
        return m_laneLine2_Curv;
    }

    QVariant laneLine4_Curv() const
    {
        return m_laneLine4_Curv;
    }

    QVariant laneLine3_Curv() const
    {
        return m_laneLine3_Curv;
    }

    QVariant leftILC() const
    {
        return m_leftILC;
    }

    QVariant rightILC() const
    {
        return m_rightILC;
    }

    QVariant leftILCVisible() const
    {
        return m_leftILCVisible;
    }

    QVariant rightILCVisible() const
    {
        return m_rightILCVisible;
    }

    QVariant miniAdasVisible() const
    {
        return m_miniAdasVisible;
    }

    QVariant accTimeGap() const
    {
        return m_accTimeGap;
    }

    QVariant accTimeGapVisible() const
    {
        return m_accTimeGapVisible;
    }

signals:

    void adasEnumsObjectChanged(ADASEnums* adasEnumsObject);

    void ADAS_DOW_FLChanged(QVariant ADAS_DOW_FL);

    void ADAS_DOW_RLChanged(QVariant ADAS_DOW_RL);

    void ADAS_DOW_FRChanged(QVariant ADAS_DOW_FR);

    void ADAS_DOW_RRChanged(QVariant ADAS_DOW_RR);

    void RCW_WARNChanged(QVariant RCW_WARN);

    void FCW_WARNChanged(QVariant FCW_WARN);

    void RCTA_LEFT_WARNChanged(QVariant RCTA_LEFT_WARN);

    void RCTA_RIGHT_WARNChanged(QVariant RCTA_RIGHT_WARN);

    void LCA_LEFT_WARNChanged(QVariant LCA_LEFT_WARN);

    void LCA_RIGHT_WARNChanged(QVariant LCA_RIGHT_WARN);

    void laneLine3Changed(QVariant laneLine3_Color);

    void laneLine1Changed(QVariant laneLine1_Color);

    void laneLine2Changed(QVariant laneLine2_Color);

    void laneLine4Changed(QVariant laneLine4_Color);

    void laneLine3_DisplayChanged(QVariant laneLine3_Display);

    void laneLine1_DisplayChanged(QVariant laneLine1_Display);

    void laneLine2_DisplayChanged(QVariant laneLine2_Display);

    void laneLine4_DisplayChanged(QVariant laneLine4_Display);

    void laneLine3_TypeChanged(QVariant laneLine3_Type);

    void laneLine1_TypeChanged(QVariant laneLine1_Type);

    void laneLine2_TypeChanged(QVariant laneLine2_Type);

    void laneLine4_TypeChanged(QVariant laneLine4_Type);

    void fctaRightChanged(QVariant fctaRight);

    void objectCapturedStatusChanged(QVariant objectCapturedStatus);

    void trackTarget0_Static_stChanged(QVariant trackTarget0_Static_st);

    void trackTarget1_Static_stChanged(QVariant trackTarget1_Static_st);

    void trackTarget2_Static_stChanged(QVariant trackTarget2_Static_st);

    void trackTarget3_Static_stChanged(QVariant trackTarget3_Static_st);

    void trackTarget4_Static_stChanged(QVariant trackTarget4_Static_st);

    void trackTarget5_Static_stChanged(QVariant trackTarget5_Static_st);

    void trackTarget0_Static_ObjectTypeChanged(QVariant trackTarget0_Static_ObjectType);

    void trackTarget1_Static_ObjectTypeChanged(QVariant trackTarget1_Static_ObjectType);

    void trackTarget2_Static_ObjectTypeChanged(QVariant trackTarget2_Static_ObjectType);

    void trackTarget3_Static_ObjectTypeChanged(QVariant trackTarget3_Static_ObjectType);

    void trackTarget4_Static_ObjectTypeChanged(QVariant trackTarget4_Static_ObjectType);

    void trackTarget5_Static_ObjectTypeChanged(QVariant trackTarget5_Static_ObjectType);

    void trackTar0_Static_LATPOChanged(QVariant trackTar0_Static_LATPO);

    void trackTar0_Static_LGTP0Changed(QVariant trackTar0_Static_LGTP0);

    void trackTar1_Static_LATPOChanged(QVariant trackTar1_Static_LATPO);

    void trackTar1_Static_LGTP0Changed(QVariant trackTar1_Static_LGTP0);

    void trackTar2_Static_LATPOChanged(QVariant trackTar2_Static_LATPO);

    void trackTar2_Static_LGTP0Changed(QVariant trackTar2_Static_LGTP0);

    void trackTar3_Static_LATPOChanged(QVariant trackTar3_Static_LATPO);

    void trackTar3_Static_LGTP0Changed(QVariant trackTar3_Static_LGTP0);

    void trackTar4_Static_LATPOChanged(QVariant trackTar4_Static_LATPO);

    void trackTar4_Static_LGTP0Changed(QVariant trackTar4_Static_LGTP0);

    void trackTar5_Static_LATPOChanged(QVariant trackTar5_Static_LATPO);

    void trackTar5_Static_LGTP0Changed(QVariant trackTar5_Static_LGTP0);

    void prkgStsIndcrChanged(QVariant prkgStsIndcr);

    void prkgLeSlotTyp1Changed(QVariant prkgLeSlotTyp1);

    void prkgLeSlotTyp2Changed(QVariant prkgLeSlotTyp2);

    void prkgLeSlotTyp3Changed(QVariant prkgLeSlotTyp3);

    void prkgRiSlotTyp1Changed(QVariant PrkgRiSlotTyp1);

    void prkgRiSlotTyp2Changed(QVariant PrkgRiSlotTyp2);

    void prkgRiSlotTyp3Changed(QVariant PrkgRiSlotTyp3);

    void fctaLeftChanged(QVariant fctaLeft);

    void parkUpDistanceChanged(QVariant parkUpDistance);

    void parkDownDistanceChanged(QVariant parkDownDistance);

    void parkUpDistanceColorChanged(QVariant parkUpDistanceColor);

    void parkDownDistanceColorChanged(QVariant parkDownDistanceColor);

    void parkLeftDistanceColorChanged(QVariant parkLeftDistanceColor);

    void parkRightDistanceColorChanged(QVariant parkRightistanceColor);

    void laneLine1_CurvChanged(QVariant laneLine1_Curv);

    void laneLine2_CurvChanged(QVariant laneLine2_Curv);

    void laneLine4_CurvChanged(QVariant laneLine4_Curv);

    void laneLine3_CurvChanged(QVariant laneLine3_Curv);

    void leftILCChanged(QVariant leftILC);

    void rightILCChanged(QVariant rightILC);

    void leftILCVisibleChanged(QVariant leftILCVisible);

    void rightILCVisibleChanged(QVariant rightILCVisible);

    void miniAdasVisibleChanged(QVariant miniAdasVisible);

    void accTimeGapChanged(QVariant accTimeGap);

    void accTimeGapVisibleChanged(QVariant accTimeGapVisible);

public slots:
    void SetProperty(int index, const TargetData target);
    void SetProperty(int name, QVariant value);

    QList<QObject*> getTargetListAll(){
        return m_adasTargetList;
    }

    void setAdasEnumsObject(ADASEnums* adasEnumsObject)
    {
        if (m_adasEnumsObject == adasEnumsObject)
            return;

        m_adasEnumsObject = adasEnumsObject;
        emit adasEnumsObjectChanged(m_adasEnumsObject);
    }

    void setADAS_DOW_FL(QVariant ADAS_DOW_FL)
    {
        if (m_ADAS_DOW_FL == ADAS_DOW_FL)
            return;

        m_ADAS_DOW_FL = ADAS_DOW_FL;
        emit ADAS_DOW_FLChanged(m_ADAS_DOW_FL);
    }

    void setADAS_DOW_RL(QVariant ADAS_DOW_RL)
    {
        if (m_ADAS_DOW_RL == ADAS_DOW_RL)
            return;

        m_ADAS_DOW_RL = ADAS_DOW_RL;
        emit ADAS_DOW_RLChanged(m_ADAS_DOW_RL);
    }

    void setADAS_DOW_FR(QVariant ADAS_DOW_FR)
    {
        if (m_ADAS_DOW_FR == ADAS_DOW_FR)
            return;

        m_ADAS_DOW_FR = ADAS_DOW_FR;
        emit ADAS_DOW_FRChanged(m_ADAS_DOW_FR);
    }

    void setADAS_DOW_RR(QVariant ADAS_DOW_RR)
    {
        if (m_ADAS_DOW_RR == ADAS_DOW_RR)
            return;

        m_ADAS_DOW_RR = ADAS_DOW_RR;
        emit ADAS_DOW_RRChanged(m_ADAS_DOW_RR);
    }

    void setRCW_WARN(QVariant RCW_WARN)
    {
        if (m_RCW_WARN == RCW_WARN)
            return;

        m_RCW_WARN = RCW_WARN;
        emit RCW_WARNChanged(m_RCW_WARN);
    }

    void setFCW_WARN(QVariant FCW_WARN)
    {
        if (m_FCW_WARN == FCW_WARN)
            return;

        m_FCW_WARN = FCW_WARN;
        emit FCW_WARNChanged(m_FCW_WARN);
    }

    void setRCTA_LEFT_WARN(QVariant RCTA_LEFT_WARN)
    {
        if (m_RCTA_LEFT_WARN == RCTA_LEFT_WARN)
            return;

        m_RCTA_LEFT_WARN = RCTA_LEFT_WARN;
        emit RCTA_LEFT_WARNChanged(m_RCTA_LEFT_WARN);
    }

    void setRCTA_RIGHT_WARN(QVariant RCTA_RIGHT_WARN)
    {
        if (m_RCTA_RIGHT_WARN == RCTA_RIGHT_WARN)
            return;

        m_RCTA_RIGHT_WARN = RCTA_RIGHT_WARN;
        emit RCTA_RIGHT_WARNChanged(m_RCTA_RIGHT_WARN);
    }

    void setLCA_LEFT_WARN(QVariant LCA_LEFT_WARN)
    {
        if (m_LCA_LEFT_WARN == LCA_LEFT_WARN)
            return;

        m_LCA_LEFT_WARN = LCA_LEFT_WARN;
        emit LCA_LEFT_WARNChanged(m_LCA_LEFT_WARN);
    }

    void setLCA_RIGHT_WARN(QVariant LCA_RIGHT_WARN)
    {
        if (m_LCA_RIGHT_WARN == LCA_RIGHT_WARN)
            return;

        m_LCA_RIGHT_WARN = LCA_RIGHT_WARN;
        emit LCA_RIGHT_WARNChanged(m_LCA_RIGHT_WARN);
    }


    void setLaneLine3_Color(QVariant laneLine3_Color)
    {
        if (m_laneLine3_Color == laneLine3_Color)
            return;

        m_laneLine3_Color = laneLine3_Color;
        emit laneLine3Changed(m_laneLine3_Color);
    }

    void setLaneLine1_Color(QVariant laneLine1_Color)
    {
        if (m_laneLine1_Color == laneLine1_Color)
            return;

        m_laneLine1_Color = laneLine1_Color;
        emit laneLine1Changed(m_laneLine1_Color);
    }

    void setLaneLine2_Color(QVariant laneLine2_Color)
    {
        if (m_laneLine2_Color == laneLine2_Color)
            return;

        m_laneLine2_Color = laneLine2_Color;
        emit laneLine2Changed(m_laneLine2_Color);
    }

    void setLaneLine4_Color(QVariant laneLine4_Color)
    {
        if (m_laneLine4_Color == laneLine4_Color)
            return;

        m_laneLine4_Color = laneLine4_Color;
        emit laneLine4Changed(m_laneLine4_Color);
    }

    void setLaneLine3_Display(QVariant laneLine3_Display)
    {
        if (m_laneLine3_Display == laneLine3_Display)
            return;

        m_laneLine3_Display = laneLine3_Display;
        emit laneLine3_DisplayChanged(m_laneLine3_Display);
    }

    void setLaneLine1_Display(QVariant laneLine1_Display)
    {
        if (m_laneLine1_Display == laneLine1_Display)
            return;

        m_laneLine1_Display = laneLine1_Display;
        emit laneLine1_DisplayChanged(m_laneLine1_Display);
    }

    void setLaneLine2_Display(QVariant laneLine2_Display)
    {
        if (m_laneLine2_Display == laneLine2_Display)
            return;

        m_laneLine2_Display = laneLine2_Display;
        emit laneLine2_DisplayChanged(m_laneLine2_Display);
    }

    void setLaneLine4_Display(QVariant laneLine4_Display)
    {
        if (m_laneLine4_Display == laneLine4_Display)
            return;

        m_laneLine4_Display = laneLine4_Display;
        emit laneLine4_DisplayChanged(m_laneLine4_Display);
    }

    void setLaneLine3_Type(QVariant laneLine3_Type)
    {
        if (m_laneLine3_Type == laneLine3_Type)
            return;

        m_laneLine3_Type = laneLine3_Type;
        emit laneLine3_TypeChanged(m_laneLine3_Type);
    }

    void setLaneLine1_Type(QVariant laneLine1_Type)
    {
        if (m_laneLine1_Type == laneLine1_Type)
            return;

        m_laneLine1_Type = laneLine1_Type;
        emit laneLine1_TypeChanged(m_laneLine1_Type);
    }

    void setLaneLine2_Type(QVariant laneLine2_Type)
    {
        if (m_laneLine2_Type == laneLine2_Type)
            return;

        m_laneLine2_Type = laneLine2_Type;
        emit laneLine2_TypeChanged(m_laneLine2_Type);
    }

    void setLaneLine4_Type(QVariant laneLine4_Type)
    {
        if (m_laneLine4_Type == laneLine4_Type)
            return;

        m_laneLine4_Type = laneLine4_Type;
        emit laneLine4_TypeChanged(m_laneLine4_Type);
    }

    void setFctaRight(QVariant fctaRight)
    {
        if (m_fctaRight == fctaRight)
            return;

        m_fctaRight = fctaRight;
        emit fctaRightChanged(m_fctaRight);
    }

    void setObjectCapturedStatus(QVariant objectCapturedStatus)
    {
        if (m_objectCapturedStatus == objectCapturedStatus)
            return;

        m_objectCapturedStatus = objectCapturedStatus;
        emit objectCapturedStatusChanged(m_objectCapturedStatus);
    }

    void setTrackTarget0_Static_st(QVariant trackTarget0_Static_st)
    {
        if (m_trackTarget0_Static_st == trackTarget0_Static_st)
            return;

        m_trackTarget0_Static_st = trackTarget0_Static_st;
        emit trackTarget0_Static_stChanged(m_trackTarget0_Static_st);
    }

    void setTrackTarget1_Static_st(QVariant trackTarget1_Static_st)
    {
        if (m_trackTarget1_Static_st == trackTarget1_Static_st)
            return;

        m_trackTarget1_Static_st = trackTarget1_Static_st;
        emit trackTarget1_Static_stChanged(m_trackTarget1_Static_st);
    }

    void setTrackTarget2_Static_st(QVariant trackTarget2_Static_st)
    {
        if (m_trackTarget2_Static_st == trackTarget2_Static_st)
            return;

        m_trackTarget2_Static_st = trackTarget2_Static_st;
        emit trackTarget2_Static_stChanged(m_trackTarget2_Static_st);
    }

    void setTrackTarget3_Static_st(QVariant trackTarget3_Static_st)
    {
        if (m_trackTarget3_Static_st == trackTarget3_Static_st)
            return;

        m_trackTarget3_Static_st = trackTarget3_Static_st;
        emit trackTarget3_Static_stChanged(m_trackTarget3_Static_st);
    }

    void setTrackTarget4_Static_st(QVariant trackTarget4_Static_st)
    {
        if (m_trackTarget4_Static_st == trackTarget4_Static_st)
            return;

        m_trackTarget4_Static_st = trackTarget4_Static_st;
        emit trackTarget4_Static_stChanged(m_trackTarget4_Static_st);
    }

    void setTrackTarget5_Static_st(QVariant trackTarget5_Static_st)
    {
        if (m_trackTarget5_Static_st == trackTarget5_Static_st)
            return;

        m_trackTarget5_Static_st = trackTarget5_Static_st;
        emit trackTarget5_Static_stChanged(m_trackTarget5_Static_st);
    }

    void setTrackTarget0_Static_ObjectType(QVariant trackTarget0_Static_ObjectType)
    {
        if (m_trackTarget0_Static_ObjectType == trackTarget0_Static_ObjectType)
            return;

        m_trackTarget0_Static_ObjectType = trackTarget0_Static_ObjectType;
        emit trackTarget0_Static_ObjectTypeChanged(m_trackTarget0_Static_ObjectType);
    }

    void setTrackTarget1_Static_ObjectType(QVariant trackTarget1_Static_ObjectType)
    {
        if (m_trackTarget1_Static_ObjectType == trackTarget1_Static_ObjectType)
            return;

        m_trackTarget1_Static_ObjectType = trackTarget1_Static_ObjectType;
        emit trackTarget1_Static_ObjectTypeChanged(m_trackTarget1_Static_ObjectType);
    }

    void setTrackTarget2_Static_ObjectType(QVariant trackTarget2_Static_ObjectType)
    {
        if (m_trackTarget2_Static_ObjectType == trackTarget2_Static_ObjectType)
            return;

        m_trackTarget2_Static_ObjectType = trackTarget2_Static_ObjectType;
        emit trackTarget2_Static_ObjectTypeChanged(m_trackTarget2_Static_ObjectType);
    }

    void setTrackTarget3_Static_ObjectType(QVariant trackTarget3_Static_ObjectType)
    {
        if (m_trackTarget3_Static_ObjectType == trackTarget3_Static_ObjectType)
            return;

        m_trackTarget3_Static_ObjectType = trackTarget3_Static_ObjectType;
        emit trackTarget3_Static_ObjectTypeChanged(m_trackTarget3_Static_ObjectType);
    }

    void setTrackTarget4_Static_ObjectType(QVariant trackTarget4_Static_ObjectType)
    {
        if (m_trackTarget4_Static_ObjectType == trackTarget4_Static_ObjectType)
            return;

        m_trackTarget4_Static_ObjectType = trackTarget4_Static_ObjectType;
        emit trackTarget4_Static_ObjectTypeChanged(m_trackTarget4_Static_ObjectType);
    }

    void setTrackTarget5_Static_ObjectType(QVariant trackTarget5_Static_ObjectType)
    {
        if (m_trackTarget5_Static_ObjectType == trackTarget5_Static_ObjectType)
            return;

        m_trackTarget5_Static_ObjectType = trackTarget5_Static_ObjectType;
        emit trackTarget5_Static_ObjectTypeChanged(m_trackTarget5_Static_ObjectType);
    }
    void setTrackTar0_Static_LATPO(QVariant trackTar0_Static_LATPO)
    {
        if (m_trackTar0_Static_LATPO == trackTar0_Static_LATPO)
            return;

        m_trackTar0_Static_LATPO = trackTar0_Static_LATPO;
        emit trackTar0_Static_LATPOChanged(m_trackTar0_Static_LATPO);
    }

    void setTrackTar0_Static_LGTP0(QVariant trackTar0_Static_LGTP0)
    {
        if (m_trackTar0_Static_LGTP0 == trackTar0_Static_LGTP0)
            return;

        m_trackTar0_Static_LGTP0 = trackTar0_Static_LGTP0;
        emit trackTar0_Static_LGTP0Changed(m_trackTar0_Static_LGTP0);
    }

    void setTrackTar1_Static_LATPO(QVariant trackTar1_Static_LATPO)
    {
        if (m_trackTar1_Static_LATPO == trackTar1_Static_LATPO)
            return;

        m_trackTar1_Static_LATPO = trackTar1_Static_LATPO;
        emit trackTar1_Static_LATPOChanged(m_trackTar1_Static_LATPO);
    }

    void setTrackTar1_Static_LGTP0(QVariant trackTar1_Static_LGTP0)
    {
        if (m_trackTar1_Static_LGTP0 == trackTar1_Static_LGTP0)
            return;

        m_trackTar1_Static_LGTP0 = trackTar1_Static_LGTP0;
        emit trackTar1_Static_LGTP0Changed(m_trackTar1_Static_LGTP0);
    }

    void setTrackTar2_Static_LATPO(QVariant trackTar2_Static_LATPO)
    {
        if (m_trackTar2_Static_LATPO == trackTar2_Static_LATPO)
            return;

        m_trackTar2_Static_LATPO = trackTar2_Static_LATPO;
        emit trackTar2_Static_LATPOChanged(m_trackTar2_Static_LATPO);
    }

    void setTrackTar2_Static_LGTP0(QVariant trackTar2_Static_LGTP0)
    {
        if (m_trackTar2_Static_LGTP0 == trackTar2_Static_LGTP0)
            return;

        m_trackTar2_Static_LGTP0 = trackTar2_Static_LGTP0;
        emit trackTar2_Static_LGTP0Changed(m_trackTar2_Static_LGTP0);
    }

    void setTrackTar3_Static_LATPO(QVariant trackTar3_Static_LATPO)
    {
        if (m_trackTar3_Static_LATPO == trackTar3_Static_LATPO)
            return;

        m_trackTar3_Static_LATPO = trackTar3_Static_LATPO;
        emit trackTar3_Static_LATPOChanged(m_trackTar3_Static_LATPO);
    }

    void setTrackTar3_Static_LGTP0(QVariant trackTar3_Static_LGTP0)
    {
        if (m_trackTar3_Static_LGTP0 == trackTar3_Static_LGTP0)
            return;

        m_trackTar3_Static_LGTP0 = trackTar3_Static_LGTP0;
        emit trackTar3_Static_LGTP0Changed(m_trackTar3_Static_LGTP0);
    }

    void setTrackTar4_Static_LATPO(QVariant trackTar4_Static_LATPO)
    {
        if (m_trackTar4_Static_LATPO == trackTar4_Static_LATPO)
            return;

        m_trackTar4_Static_LATPO = trackTar4_Static_LATPO;
        emit trackTar4_Static_LATPOChanged(m_trackTar4_Static_LATPO);
    }

    void setTrackTar4_Static_LGTP0(QVariant trackTar4_Static_LGTP0)
    {
        if (m_trackTar4_Static_LGTP0 == trackTar4_Static_LGTP0)
            return;

        m_trackTar4_Static_LGTP0 = trackTar4_Static_LGTP0;
        emit trackTar4_Static_LGTP0Changed(m_trackTar4_Static_LGTP0);
    }

    void setTrackTar5_Static_LATPO(QVariant trackTar5_Static_LATPO)
    {
        if (m_trackTar5_Static_LATPO == trackTar5_Static_LATPO)
            return;

        m_trackTar5_Static_LATPO = trackTar5_Static_LATPO;
        emit trackTar5_Static_LATPOChanged(m_trackTar5_Static_LATPO);
    }

    void setTrackTar5_Static_LGTP0(QVariant trackTar5_Static_LGTP0)
    {
        if (m_trackTar5_Static_LGTP0 == trackTar5_Static_LGTP0)
            return;

        m_trackTar5_Static_LGTP0 = trackTar5_Static_LGTP0;
        emit trackTar5_Static_LGTP0Changed(m_trackTar5_Static_LGTP0);
    }

    void setPrkgStsIndcr(QVariant prkgStsIndcr)
    {
        if (m_prkgStsIndcr == prkgStsIndcr)
            return;

        m_prkgStsIndcr = prkgStsIndcr;
        emit prkgStsIndcrChanged(m_prkgStsIndcr);
    }

    void setPrkgLeSlotTyp1(QVariant prkgLeSlotTyp1)
    {
        if (m_prkgLeSlotTyp1 == prkgLeSlotTyp1)
            return;

        m_prkgLeSlotTyp1 = prkgLeSlotTyp1;
        emit prkgLeSlotTyp1Changed(m_prkgLeSlotTyp1);
    }

    void setPrkgLeSlotTyp2(QVariant prkgLeSlotTyp2)
    {
        if (m_prkgLeSlotTyp2 == prkgLeSlotTyp2)
            return;

        m_prkgLeSlotTyp2 = prkgLeSlotTyp2;
        emit prkgLeSlotTyp2Changed(m_prkgLeSlotTyp2);
    }

    void setPrkgLeSlotTyp3(QVariant prkgLeSlotTyp3)
    {
        if (m_prkgLeSlotTyp3 == prkgLeSlotTyp3)
            return;

        m_prkgLeSlotTyp3 = prkgLeSlotTyp3;
        emit prkgLeSlotTyp3Changed(m_prkgLeSlotTyp3);
    }

    void setPrkgRiSlotTyp1(QVariant PrkgRiSlotTyp1)
    {
        if (m_PrkgRiSlotTyp1 == PrkgRiSlotTyp1)
            return;

        m_PrkgRiSlotTyp1 = PrkgRiSlotTyp1;
        emit prkgRiSlotTyp1Changed(m_PrkgRiSlotTyp1);
    }

    void setPrkgRiSlotTyp2(QVariant PrkgRiSlotTyp2)
    {
        if (m_PrkgRiSlotTyp2 == PrkgRiSlotTyp2)
            return;

        m_PrkgRiSlotTyp2 = PrkgRiSlotTyp2;
        emit prkgRiSlotTyp2Changed(m_PrkgRiSlotTyp2);
    }

    void setPrkgRiSlotTyp3(QVariant PrkgRiSlotTyp3)
    {
        if (m_PrkgRiSlotTyp3 == PrkgRiSlotTyp3)
            return;

        m_PrkgRiSlotTyp3 = PrkgRiSlotTyp3;
        emit prkgRiSlotTyp3Changed(m_PrkgRiSlotTyp3);
    }

    void setFctaLeft(QVariant fctaLeft)
    {
        if (m_fctaLeft == fctaLeft)
            return;

        m_fctaLeft = fctaLeft;
        emit fctaLeftChanged(m_fctaLeft);
    }

    void setParkUpDistance(QVariant parkUpDistance)
    {
        if (m_parkUpDistance == parkUpDistance)
            return;

        m_parkUpDistance = parkUpDistance;
        emit parkUpDistanceChanged(m_parkUpDistance);
    }

    void setParkDownDistance(QVariant parkDownDistance)
    {
        if (m_parkDownDistance == parkDownDistance)
            return;

        m_parkDownDistance = parkDownDistance;
        emit parkDownDistanceChanged(m_parkDownDistance);
    }

    void setParkUpDistanceColor(QVariant parkUpDistanceColor)
    {
        if (m_parkUpDistanceColor == parkUpDistanceColor)
            return;

        m_parkUpDistanceColor = parkUpDistanceColor;
        emit parkUpDistanceColorChanged(m_parkUpDistanceColor);
    }

    void setParkDownDistanceColor(QVariant parkDownDistanceColor)
    {
        if (m_parkDownDistanceColor == parkDownDistanceColor)
            return;

        m_parkDownDistanceColor = parkDownDistanceColor;
        emit parkDownDistanceColorChanged(m_parkDownDistanceColor);
    }

    void setParkLeftDistanceColor(QVariant parkLeftDistanceColor)
    {
        if (m_parkLeftDistanceColor == parkLeftDistanceColor)
            return;

        m_parkLeftDistanceColor = parkLeftDistanceColor;
        emit parkLeftDistanceColorChanged(m_parkLeftDistanceColor);
    }

    void setParkRightDistanceColor(QVariant parkRightistanceColor)
    {
        if (m_parkRightistanceColor == parkRightistanceColor)
            return;

        m_parkRightistanceColor = parkRightistanceColor;
        emit parkRightDistanceColorChanged(m_parkRightistanceColor);
    }

    void setLaneLine1_Curv(QVariant laneLine1_Curv)
    {
        if (m_laneLine1_Curv == laneLine1_Curv)
            return;

        m_laneLine1_Curv = laneLine1_Curv;
        emit laneLine1_CurvChanged(m_laneLine1_Curv);
    }

    void setLaneLine2_Curv(QVariant laneLine2_Curv)
    {
        if (m_laneLine2_Curv == laneLine2_Curv)
            return;

        m_laneLine2_Curv = laneLine2_Curv;
        emit laneLine2_CurvChanged(m_laneLine2_Curv);
    }

    void setLaneLine4_Curv(QVariant laneLine4_Curv)
    {
        if (m_laneLine4_Curv == laneLine4_Curv)
            return;

        m_laneLine4_Curv = laneLine4_Curv;
        emit laneLine4_CurvChanged(m_laneLine4_Curv);
    }

    void setLaneLine3_Curv(QVariant laneLine3_Curv)
    {
        if (m_laneLine3_Curv == laneLine3_Curv)
            return;

        m_laneLine3_Curv = laneLine3_Curv;
        emit laneLine3_CurvChanged(m_laneLine3_Curv);
    }
    void setLeftILC(QVariant leftILC)
    {
        if (m_leftILC == leftILC)
            return;

        m_leftILC = leftILC;
        emit leftILCChanged(m_leftILC);
    }

    void setRightILC(QVariant rightILC)
    {
        if (m_rightILC == rightILC)
            return;

        m_rightILC = rightILC;
        emit rightILCChanged(m_rightILC);
    }

    void setLeftILCVisible(QVariant leftILCVisible)
    {
        if (m_leftILCVisible == leftILCVisible)
            return;

        m_leftILCVisible = leftILCVisible;
        emit leftILCVisibleChanged(m_leftILCVisible);
    }

    void setRightILCVisible(QVariant rightILCVisible)
    {
        if (m_rightILCVisible == rightILCVisible)
            return;

        m_rightILCVisible = rightILCVisible;
        emit rightILCVisibleChanged(m_rightILCVisible);
    }

    void setMiniAdasVisible(QVariant miniAdasVisible)
    {
        if (m_miniAdasVisible == miniAdasVisible)
            return;

        m_miniAdasVisible = miniAdasVisible;
        emit miniAdasVisibleChanged(m_miniAdasVisible);
    }

    void setAccTimeGap(QVariant accTimeGap)
    {
        if (m_accTimeGap == accTimeGap)
            return;

        m_accTimeGap = accTimeGap;
        emit accTimeGapChanged(m_accTimeGap);
    }

    void setAccTimeGapVisible(QVariant accTimeGapVisible)
    {
        if (m_accTimeGapVisible == accTimeGapVisible)
            return;

        m_accTimeGapVisible = accTimeGapVisible;
        emit accTimeGapVisibleChanged(m_accTimeGapVisible);
    }

private:

    QList<QObject*> m_adasTargetList;
    ADASEnums* m_adasEnumsObject;
    QVariant m_ADAS_DOW_FL;
    QVariant m_ADAS_DOW_RL;
    QVariant m_ADAS_DOW_FR;
    QVariant m_ADAS_DOW_RR;
    QVariant m_RCW_WARN;
    QVariant m_FCW_WARN;
    QVariant m_RCTA_LEFT_WARN;
    QVariant m_RCTA_RIGHT_WARN;
    QVariant m_LCA_LEFT_WARN;
    QVariant m_LCA_RIGHT_WARN;
    QVariant m_laneLine3;
    QVariant m_laneLine1;
    QVariant m_laneLine2;
    QVariant m_laneLine4;
    QVariant m_laneLine3_Color;
    QVariant m_laneLine1_Color;
    QVariant m_laneLine2_Color;
    QVariant m_laneLine4_Color;
    QVariant m_laneLine3_Display;
    QVariant m_laneLine1_Display;
    QVariant m_laneLine2_Display;
    QVariant m_laneLine4_Display;
    QVariant m_laneLine3_Type;
    QVariant m_laneLine1_Type;
    QVariant m_laneLine2_Type;
    QVariant m_laneLine4_Type;
    QVariant m_fctaLeft;
    QVariant m_fctaRight;
    QVariant m_objectCapturedStatus;
    QVariant m_trackTarget0_Static_st;
    QVariant m_trackTarget1_Static_st;
    QVariant m_trackTarget2_Static_st;
    QVariant m_trackTarget3_Static_st;
    QVariant m_trackTarget4_Static_st;
    QVariant m_trackTarget5_Static_st;
    QVariant m_trackTarget0_Static_ObjectType;
    QVariant m_trackTarget1_Static_ObjectType;
    QVariant m_trackTarget2_Static_ObjectType;
    QVariant m_trackTarget3_Static_ObjectType;
    QVariant m_trackTarget4_Static_ObjectType;
    QVariant m_trackTarget5_Static_ObjectType;
    QVariant m_trackTar0_Static_LATPO;
    QVariant m_trackTar0_Static_LGTP0;
    QVariant m_trackTar1_Static_LATPO;
    QVariant m_trackTar1_Static_LGTP0;
    QVariant m_trackTar2_Static_LATPO;
    QVariant m_trackTar2_Static_LGTP0;
    QVariant m_trackTar3_Static_LATPO;
    QVariant m_trackTar3_Static_LGTP0;
    QVariant m_trackTar4_Static_LATPO;
    QVariant m_trackTar4_Static_LGTP0;
    QVariant m_trackTar5_Static_LATPO;
    QVariant m_trackTar5_Static_LGTP0;
    QVariant m_prkgStsIndcr;
    QVariant m_prkgLeSlotTyp1;
    QVariant m_prkgLeSlotTyp2;
    QVariant m_prkgLeSlotTyp3;
    QVariant m_PrkgRiSlotTyp1;
    QVariant m_PrkgRiSlotTyp2;
    QVariant m_PrkgRiSlotTyp3;
    QVariant m_parkUpDistance;
    QVariant m_parkDownDistance;
    QVariant m_parkUpDistanceColor;
    QVariant m_parkDownDistanceColor;
    QVariant m_parkLeftDistanceColor;
    QVariant m_parkRightistanceColor;
    QVariant m_laneLine1_Curv;
    QVariant m_laneLine2_Curv;
    QVariant m_laneLine4_Curv;
    QVariant m_laneLine3_Curv;
    QVariant m_leftILC;
    QVariant m_rightILC;
    QVariant m_leftILCVisible;
    QVariant m_rightILCVisible;
    QVariant m_miniAdasVisible;
    QVariant m_accTimeGap;
    QVariant m_accTimeGapVisible;
};

#endif // ADASSCREEN_H
