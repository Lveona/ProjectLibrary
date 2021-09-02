#include "adasControl.h"
#include <QMutex>
#include <math.h>

#define MAX_SIGNAL_Y 254 //y轴信号最大值
#define MAX_REAL_X 100 //x width -50 ~ 50
#define MAX_CUR (1.5 * 2)
#define GET_REAL_X(y, cur, value)   (y / MAX_SIGNAL_Y * (cur / MAX_CUR) * MAX_REAL_X + value)  //offset + x

#define PI 3.1415926
#define GET_RADIUS(x, y)    (sqrt(pow(x, 2) + pow(y, 2)) * 0.5)
#define GET_START_ANGLE(x, y)   (abs(atan2(y, x) * 180 / PI + 270))
static int g_powermode = 0;
static float line1Cur;
static float line2Cur;
static float line3Cur;
static float line4Cur;
static int lastILC = 0;
static int accTimeGapBackup = 0;
static QList<ADASEnums::qmlTargetObjectType> objectTypeList = {ADASEnums::ROADBLOCK, ADASEnums::CAR_MODEL, ADASEnums::TWO_WHEELER_MODEL, ADASEnums::TRUCK_MODEL,
                                                               ADASEnums::PEDESTRIAN_MODEL, ADASEnums::ROADBLOCK,ADASEnums::ROADBLOCK,ADASEnums::ROADBLOCK,
                                                               ADASEnums::ROADBLOCK,ADASEnums::TWO_WHEELER_MODEL,ADASEnums::CAR_MODEL};
/**
    propertyIndex,
    targetObjectType,
    positionX,
    positionY,
    arcRadius,
    arcStartAngle,
    arcColor,
    enable=1):
  */
static AdasTarget Target_T0 = {ADASTAEGET_T0, ADASEnums::MAXTARGETSTATICOBJECTTYPE, 0, 0, 0, 0, ADASEnums::PARKDISTANCE_NONE, false};
static AdasTarget Target_T1 = {ADASTAEGET_T1, ADASEnums::MAXTARGETSTATICOBJECTTYPE, 0, 0, 0, 0, ADASEnums::PARKDISTANCE_NONE, false};
static AdasTarget Target_T2 = {ADASTAEGET_T2, ADASEnums::MAXTARGETSTATICOBJECTTYPE, 0, 0, 0, 0, ADASEnums::PARKDISTANCE_NONE, false};
static AdasTarget Target_T3 = {ADASTAEGET_T3, ADASEnums::MAXTARGETSTATICOBJECTTYPE, 0, 0, 0, 0, ADASEnums::PARKDISTANCE_NONE, false};
static AdasTarget Target_T4 = {ADASTAEGET_T4, ADASEnums::MAXTARGETSTATICOBJECTTYPE, 0, 0, 0, 0, ADASEnums::PARKDISTANCE_NONE, false};
static AdasTarget Target_T5 = {ADASTAEGET_T5, ADASEnums::MAXTARGETSTATICOBJECTTYPE, 0, 0, 0, 0, ADASEnums::PARKDISTANCE_NONE, false};


QList<ADASControl::FunctionParser> adasControlFuncList {
    &ADASControl::handleDoorWarn,
    &ADASControl::handleRctaLeftWarn,
    &ADASControl::handleRctaRightWarn,
    &ADASControl::handleLcaLeftWarn,
    &ADASControl::handleLcaRightWarn,
    &ADASControl::handleHwaIlcSt,
    &ADASControl::handleL3Availablestatus,
    &ADASControl::handLaneLinesDisplay,
    &ADASControl::handLaneLinesType,
    &ADASControl::handLaneLine1CurVature,
    &ADASControl::handLaneLine2CurVature,
    &ADASControl::handLaneLine3CurVature,
    &ADASControl::handLaneLine4CurVature,
    &ADASControl::handFctaLeftWarn,
    &ADASControl::handFctaRightWarn,
    &ADASControl::handAccObjectCapturedStatus,
    &ADASControl::handTrackTar,
    &ADASControl::handTrackTarStaticObjectType,
    &ADASControl::handTrackTar_Static_LgtPo,
    &ADASControl::handTrackTar_Static_LatPo,
    &ADASControl::handAnrcPrkgStsIndcr,
    &ADASControl::handAnrcAnrcPrkgLeSlotTyp,
    &ADASControl::handLaneLinesColor,
    &ADASControl::handWarningMap,
    &ADASControl::handleTarget0Object,
    &ADASControl::handleTarget1Object,
    &ADASControl::handleTarget2Object,
    &ADASControl::handleTarget3Object,
    &ADASControl::handleTarget4Object,
    &ADASControl::handleTarget5Object,
    &ADASControl::handleACCTimeGap,
};


ADASControl::ADASControl()
{
    m_leftILCTime = new HMICustomTimer(6,false);
    connect(m_leftILCTime, &HMICustomTimer::timeout, this, [=](){
        setPropertyValue(PROPERTYID_ILC_LEFT_VISIBLE, false);
        m_leftILCTime->stop();
    });

    m_rightILCTime = new HMICustomTimer(6,false);
    connect(m_rightILCTime, &HMICustomTimer::timeout, this, [=](){
        setPropertyValue(PROPERTYID_ILC_RIGHT_VISIBLE, false);
        m_rightILCTime->stop();
    });
    m_gapTimer = new HMICustomTimer(10, false);
    connect(m_gapTimer, &HMICustomTimer::timeout, this, [=](){
        setPropertyValue(PROPERTYID_ACC_TIME_GAP_VISIBLE, false);
        m_gapTimer->stop();
    });
   miniAdasValue.fill(0,MINI_VISIBLE_MAX);
   start(QThread::NormalPriority);
}

ADASControl::~ADASControl()
{
    // Nothing
}

void ADASControl::handleDoorWarn()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ADAS_DOW_FL,msg)) {
        if(msg.value == 1 || msg.value == 2){
            miniAdasValue[CARDOOR_FL] = 1;
        }else{
            miniAdasValue[CARDOOR_FL] = 0;
        }
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL1_FL,AUDIO_INDEX_DOW_LEVEL1_FL,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL2_FL,AUDIO_INDEX_DOW_LEVEL2_FL,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
        setPropertyValue(PROPERTYID_ADAS_DOW_FL,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_DOW_RL,msg)) {
        if(msg.value == 1 || msg.value == 2){
            miniAdasValue[CARDOOR_RL] = 1;
        }else{
            miniAdasValue[CARDOOR_RL] =0;
        }
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL1_RL,AUDIO_INDEX_DOW_LEVEL1_RL,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL2_RL,AUDIO_INDEX_DOW_LEVEL2_RL,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
        setPropertyValue(PROPERTYID_ADAS_DOW_RL,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_DOW_FR,msg)) {
        if(msg.value == 1 || msg.value == 2){
            miniAdasValue[CARDOOR_FR] = 1;
        }else{
            miniAdasValue[CARDOOR_FR] = 0;
        }
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL1_FR,AUDIO_INDEX_DOW_LEVEL1_FR,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL2_FR,AUDIO_INDEX_DOW_LEVEL2_FR,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
        setPropertyValue(PROPERTYID_ADAS_DOW_FR,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_DOW_RR,msg)) {
        if(msg.value == 1 || msg.value == 2){
            miniAdasValue[CARDOOR_RR] = 1;
        }else{
            miniAdasValue[CARDOOR_RR] = 0;
        }
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL1_RR,AUDIO_INDEX_DOW_LEVEL1_RR,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_DOW_LEVEL2_RR,AUDIO_INDEX_DOW_LEVEL2_RR,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
        setPropertyValue(PROPERTYID_ADAS_DOW_RR,(int)msg.value);
    }
}

void ADASControl::handleRctaLeftWarn()
{
        /*
         * 电源状态:ON
输入信号:
ADAS_RCTA_left_Warn_St
输出信号：
0x0: Inactive 不显示
0x1: FCTA_LV1_Warning 黄色提示，
持续闪烁500ms On 500ms Off
0x2: FCTA_LV2_Warning 红色提示
持续闪烁 250ms On 250ms Off
0x3: Reserved 不显示
0x4: Reserved 不显示
0x5: Reserved 不显示
0x6: Reserved 不显示
0x7: Reserved 不显示*/

    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RCTA_LEFT_WARN,msg)
     if(msg.value == 1 || msg.value == 2){
        miniAdasValue[RCTA_LEFT] = 1;
    }else{
        miniAdasValue[RCTA_LEFT] = 0;
    }
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCTA_LEVEL1_RL,AUDIO_INDEX_RCTA_LEVEL1_RL,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCTA_LEVEL2_RL,AUDIO_INDEX_RCTA_LEVEL2_RL,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    switch(msg.value){
    case 0x1:
        m_WarningMap.insert(PROPERTYID_RCTA_LEFT_WARN,ADASEnums::LV1WARNING);
        setPropertyValue(PROPERTYID_RCTA_LEFT_WARN_F,ADASEnums::LV1WARNING);
        break;
    case 0x2:
        m_WarningMap.insert(PROPERTYID_RCTA_LEFT_WARN,ADASEnums::LV2WARNING);
        setPropertyValue(PROPERTYID_RCTA_LEFT_WARN_F,ADASEnums::LV2WARNING);
        break;
    default:
        m_WarningMap.insert(PROPERTYID_RCTA_LEFT_WARN,ADASEnums::NOWARNING);
        setPropertyValue(PROPERTYID_RCTA_LEFT_WARN_F,ADASEnums::NOWARNING);
    }
}

void ADASControl::handleRctaRightWarn()
{
    /*
     * 电源状态:ON
输入信号:
ADAS_RCTA_Right_Warn_St
输出信号：
0x0: Inactive 不显示
0x1: FCTA_LV1_Warning 黄色提示，
持续闪烁500ms On 500ms Off
0x2: FCTA_LV2_Warning 红色提示
持续闪烁 250ms On 250ms Off
0x3: Reserved 不显示
0x4: Reserved 不显示
0x5: Reserved 不显示
0x6: Reserved 不显示
0x7: Reserved 不显示*/
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_RCTA_RIGHT_WARN,msg)
   if(msg.value == 1 || msg.value == 2){
         miniAdasValue[RCTA_RIGHT] = 1;
   }else{
         miniAdasValue[RCTA_RIGHT] = 0;
   }
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCTA_LEVEL1_RR,AUDIO_INDEX_RCTA_LEVEL1_RR,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCTA_LEVEL2_RR,AUDIO_INDEX_RCTA_LEVEL2_RR,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    switch(msg.value){
    case 0x1:
        m_WarningMap.insert(PROPERTYID_RCTA_RIGHT_WARN,ADASEnums::LV1WARNING);
        setPropertyValue(PROPERTYID_RCTA_RIGHT_WARN_F,ADASEnums::LV1WARNING);
        break;
    case 0x2:
        m_WarningMap.insert(PROPERTYID_RCTA_RIGHT_WARN,ADASEnums::LV2WARNING);
        setPropertyValue(PROPERTYID_RCTA_RIGHT_WARN_F,ADASEnums::LV2WARNING);
        break;
    default:
        m_WarningMap.insert(PROPERTYID_RCTA_RIGHT_WARN,ADASEnums::NOWARNING);
        setPropertyValue(PROPERTYID_RCTA_RIGHT_WARN_F,ADASEnums::NOWARNING);
    }
}

void ADASControl::handleLcaLeftWarn()
{
/**
电源状态:ON
输入信号:
ADAS_LCA_Left_Warn_St
输出:
0x0： No warning 无提示
0x1： LV1 Warning 黄色提示，
持续闪烁500ms On 500ms Off
0x2： LV2 Warning 红色提示
持续闪烁250ms On 250ms Off
0x3： Reserved 无提示
声音报警:
BSD提示2级 ADAS_LCA_Left_Warn_St=2
  */
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCA_LEFT_WARN,msg)
    if(msg.value == 1 || msg.value == 2){
       miniAdasValue[LCA_LEFT] = 1;
    }else{
        miniAdasValue[LCA_LEFT] = 0;
    }
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_BSD_LEVEL2_RL,AUDIO_INDEX_BSD_LEVEL2_RL,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    switch(msg.value){
    case 0x1:
        m_WarningMap.insert(PROPERTYID_LCA_LEFT_WARN,ADASEnums::LV1WARNING);
        setPropertyValue(PROPERTYID_LCA_LEFT_WARN_F,ADASEnums::NOWARNING);
        break;
    case 0x2:
        m_WarningMap.insert(PROPERTYID_LCA_LEFT_WARN,ADASEnums::LV2WARNING);
        setPropertyValue(PROPERTYID_LCA_LEFT_WARN_F,ADASEnums::NOWARNING);
        break;
    default:
        m_WarningMap.insert(PROPERTYID_LCA_LEFT_WARN,ADASEnums::NOWARNING);
        setPropertyValue(PROPERTYID_LCA_LEFT_WARN_F,ADASEnums::NOWARNING);
    }
}

void ADASControl::handleLcaRightWarn()
{
    /**
电源状态:ON
输入信号:
ADAS_LCA_Right_Warn_St
输出:
0x0： No warning 无提示
0x1： LV1 Warning 黄色提示，
持续闪烁500ms On 500ms Off
0x2： LV2 Warning 红色提示
持续闪烁250ms On 250ms Off
0x3： Reserved 无提示
声音报警:
BSD提示2级 ADAS_LCA_Right_Warn_St
      */
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_LCA_RIGHT_WARN,msg)
    if(msg.value == 1 || msg.value == 2){
       miniAdasValue[LCA_RIGHT] = 1;
    }else{
        miniAdasValue[LCA_RIGHT] = 0;
    }
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_BSD_LEVEL2_RR,AUDIO_INDEX_BSD_LEVEL2_RR,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    switch(msg.value){
    case 0x1:
        m_WarningMap.insert(PROPERTYID_LCA_RIGHT_WARN,ADASEnums::LV1WARNING);
        setPropertyValue(PROPERTYID_LCA_RIGHT_WARN_F,ADASEnums::LV1WARNING);
        break;
    case 0x2:
        m_WarningMap.insert(PROPERTYID_LCA_RIGHT_WARN,ADASEnums::LV2WARNING);
        setPropertyValue(PROPERTYID_LCA_RIGHT_WARN_F,ADASEnums::LV2WARNING);
        break;
    default:
        m_WarningMap.insert(PROPERTYID_LCA_RIGHT_WARN,ADASEnums::NOWARNING);
        setPropertyValue(PROPERTYID_LCA_RIGHT_WARN_F,ADASEnums::NOWARNING);
    }
}

void ADASControl::handleHwaIlcSt()
{
    /**
电源状态:ON
输入信号:
ADAS_HWA_ILC_St ELK
输出:
0x0： Off 不提示
0x1： Inhibited left 不提示
0x2： Enabled left 不提示
0x3： Wait left 显示向左的待转弯箭头
0x4： Lane Changing left 不提示
0x5： Lane Changed left 不提示
0x6： Abort left 当从等待转向跳转到中止时，箭头闪烁3s后消失；
若从其他状态跳转到中止，则不显示；
0x7： Failure left 不提示
0x8： Inhibited right 不提示
0x9： Enabled right 不提示
0xA： Wait right 显示向右的待转弯箭头
0xB： Lane Changing right 不提示
0xC： Lane Changed right 不提示
0xD： Abort right 当从等待转向跳转到中止时，箭头闪烁3s后消失；
若从其他状态跳转到中止，则不显示；
*/
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_HWA_ST, msg);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_AUTOLANE_FINISHED_LEFT,AUDIO_INDEX_AUTOLANE_FINISHED_LEFT,msg.value==0x6?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_AUTOLANE_FINISHED_RIGHT,AUDIO_INDEX_AUTOLANE_FINISHED_RIGHT,msg.value==0xD?AUDIO_PLAY:AUDIO_STOP);
    if(lastILC != msg.value){
        if(lastILC == 3 && msg.value == 6){
            m_WarningMap.insert(PROPERTYID_ILC_LEFT, ADASEnums::LV1WARNING);
            setPropertyValue(PROPERTYID_ILC_LEFT_VISIBLE, true);
            setPropertyValue(PROPERTYID_ILC_LEFT_F,ADASEnums::LV1WARNING);
            m_leftILCTime->reset();
            miniAdasValue[ILC_ACTIVE] = 1;
        }else if(lastILC == 10 && msg.value == 13){
            m_WarningMap.insert(PROPERTYID_ILC_RIGHT, ADASEnums::LV1WARNING);
            setPropertyValue(PROPERTYID_ILC_RIGHT_VISIBLE, true);
            setPropertyValue(PROPERTYID_ILC_RIGHT_F,ADASEnums::LV1WARNING);
            m_rightILCTime->reset();
            miniAdasValue[ILC_ACTIVE] = 1;
        }else{
            m_WarningMap.insert(PROPERTYID_ILC_LEFT, ADASEnums::NOWARNING);
            m_WarningMap.insert(PROPERTYID_ILC_RIGHT, ADASEnums::NOWARNING);
            setPropertyValue(PROPERTYID_ILC_LEFT_F,ADASEnums::NOWARNING);
            setPropertyValue(PROPERTYID_ILC_RIGHT_F,ADASEnums::NOWARNING);
            miniAdasValue[ILC_ACTIVE] = 0;
        }
        lastILC = (int)msg.value;
    }


}

void ADASControl::handleL3Availablestatus()
{
    /**
电源状态:ON
输入信号:
ADAS_L3availablestatus
输出:
0x0：Not Available 界面无变化
0x1：HWA Available 界面变化    界面变化主要是界面效果变化 具体还要与UI对应 此处理解为开关
0x2~0x7：Reserved 界面无变化
*/
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_L3AVAILABLESTATUS,msg)
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HANDSFREE_ACTION,AUDIO_INDEX_HANDSFREE_ACTION,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
    if(msg.value == 0x1) {
        this->setPropertyValue(PROPERTYID_L3AVAILABLESTATUS,true);
    } else {
        this->setPropertyValue(PROPERTYID_L3AVAILABLESTATUS,false);
    }
}

void ADASControl::handWarningMap()
{
    SingleMessage msg;
    //默认值要改的
    ADASEnums::qmlWarnLevel level = ADASEnums::NOWARNING;
    //FCW报警
    if(msg.value == 1 || msg.value == 2){
        miniAdasValue[FCW_ACTIVE]= 1;
    }else{
        miniAdasValue[FCW_ACTIVE] = 0;
    }
    if(getMsgValue(MSG_ADAS_FCWRequest,msg)){
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCW_LEVEL1,AUDIO_INDEX_FCW_LEVEL1,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCW_LEVEL2,AUDIO_INDEX_FCW_LEVEL2,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCW_KEEP_DISTANCE,AUDIO_INDEX_FCW_KEEP_DISTANCE,msg.value==0x3?AUDIO_PLAY:AUDIO_STOP);
    }

    if(getMsgValue(MSG_ADAS_FCW_WARN,msg)) {
         switch(msg.value){
        case 0x1:
            level = ADASEnums::LV1WARNING;
            break;
        case 0x2:
        case 0x3:
            level = ADASEnums::LV2WARNING;
            break;
        default:
            level = ADASEnums::NOWARNING;
            break;
        }
    }

    if(getMsgValue(MSG_ADAS_ADASEBREQTYP,msg)) {
        switch(msg.value){
            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
                level = ADASEnums::LV2WARNING;
            break;
        default:
            break;
        }
    }

    if(getMsgValue(MSG_ADAS_ADASBRKJERKREQ,msg)) {
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_BARKE_SHORT,AUDIO_INDEX_BARKE_SHORT,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        if(msg.value == 0x1){
            level = ADASEnums::LV2WARNING;
        }
    }
    m_WarningMap.insert(PROPERTYID_ADAS_FCW_WARN,level);
    setPropertyValue(PROPERTYID_ADAS_FCW_WARN_F,level);

    //RCW报警
    level = ADASEnums::NOWARNING;
    if(getMsgValue(MSG_ADAS_RCW_WARN,msg)) {
        if(msg.value == 1 ||msg.value ==2){
            miniAdasValue[RCW_ACTIVE] = 1;
        }else{
            miniAdasValue[RCW_ACTIVE] = 0;
        }
      HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCW_LEVEL1,AUDIO_INDEX_RCW_LEVEL1,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
      HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCW_LEVEL2,AUDIO_INDEX_RCW_LEVEL2,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
        switch(msg.value){
        case 0x1:
            level = ADASEnums::LV1WARNING;
            break;
        case 0x2:
            level = ADASEnums::LV2WARNING;
            break;
        default:
            level = ADASEnums::NOWARNING;
            break;
        }
    }

    if(getMsgValue(MSG_ADAS_ADASEBREQTYP,msg)) {
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTB_WARNING,AUDIO_INDEX_FCTB_WARNING,msg.value==0x4?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_RCTB_WARNING,AUDIO_INDEX_RCTB_WARNING,msg.value==0x5?AUDIO_PLAY:AUDIO_STOP);
        if(msg.value == 0x5){
            level = ADASEnums::LV2WARNING;
        }
    }
    m_WarningMap.insert(PROPERTYID_ADAS_RCW_WARN,level);
    setPropertyValue(PROPERTYID_ADAS_RCW_WARN_F,level);

}

void ADASControl::handLaneLinesColor()
{
    SingleMessage msg;
    //所有颜色的背景色
    //Qt::gray Qt::yellow Qt::blue Qt::red
    //我是背景色  对应 左一 左二 左三 左四  根据文档来
    INIT_SINGLEMESSAGE_VALUE(MSG_ADSS_HWA_STATUS,msg)
    static int laneLine3,laneLine1,laneLine2,laneLine4
            = ADASEnums::ADAS_GRAY;
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_HWA_ACTION,AUDIO_INDEX_HWA_ACTION,msg.value==0x3?AUDIO_PLAY:AUDIO_STOP);

    switch (msg.value) {
    case 0x0:
    case 0x1:
    case 0x2:
        laneLine3 = laneLine1 = laneLine2 = laneLine4 = ADASEnums::ADAS_GRAY;
        break;
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
        laneLine3 = laneLine1 = laneLine2 = laneLine4 = ADASEnums::ADAS_BLUE;
        break;
    case 0x7:
        laneLine3 = laneLine1 = laneLine2 = laneLine4 = ADASEnums::ADAS_GRAY;
        break;
    default:
        laneLine3 = laneLine1 = laneLine2 = laneLine4 = ADASEnums::ADAS_GRAY;
        return ;
    }
    if(getMsgValue(MSG_ADAS_LKS_ACTIVE,msg)) {
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_LDW_LEFT,AUDIO_INDEX_LDW_LEFT,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_LKA_RIGHT,AUDIO_INDEX_LKA_RIGHT,msg.value==0x3?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_LDW_RIGHT,AUDIO_INDEX_LDW_RIGHT,msg.value==0x4?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_LKA_LEFT,AUDIO_INDEX_LKA_LEFT,msg.value==0x6?AUDIO_PLAY:AUDIO_STOP);
    }

    if(getMsgValue(MSG_ADAS_LKS_ACTIVE,msg)) {
        if(msg.value == 1 || msg.value == 2 || msg.value == 3 || msg.value ==4
                || msg.value ==5 || msg.value ==6){
            miniAdasValue[LKS_ACTIVE] = 1;
        }else{
            miniAdasValue[LKS_ACTIVE] = 0;
        }
        switch (msg.value) {
            case 0x1:
                laneLine1 = ADASEnums::ADAS_RED;
                break;
            case 0x2:
                laneLine1 = ADASEnums::ADAS_YELLOW;
                break;
            case 0x3:
                laneLine1 = ADASEnums::ADAS_RED;
                break;
            case 0x4:
                laneLine2 = ADASEnums::ADAS_RED;
                break;
            case 0x5:
                laneLine2 = ADASEnums::ADAS_YELLOW;
                break;
            case 0x6:
                laneLine2 = ADASEnums::ADAS_RED;
                break;
            case 0x7:
            default:
                break;
        }
    }

    if(getMsgValue(MSG_ADAS_ELK_ACTIVE,msg)) {
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_ELK_ACTIVE_LEFT,AUDIO_INDEX_ELK_ACTIVE_LEFT,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
        HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_ELK_ACTIVE_RIGHT,AUDIO_INDEX_ELK_ACTIVE_RIGHT,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    }

    if(getMsgValue(MSG_ADAS_ELK_ACTIVE,msg)) {
        switch (msg.value) {
        if(msg.value == 1 || msg.value == 2){
            miniAdasValue[ELK_ACTIVE] = 1;
        }else{
            miniAdasValue[ELK_ACTIVE] = 0;
        }
        case 0x1:
            laneLine1 = ADASEnums::ADAS_RED;
            break;
        case 0x2:
            laneLine2 = ADASEnums::ADAS_RED;
            break;
        default:
            break;
        }
    }

    this->setPropertyValue(PROPERTYID_LANELINE3_COLOR,laneLine3);
    this->setPropertyValue(PROPERTYID_LANELINE1_COLOR,laneLine1);
    this->setPropertyValue(PROPERTYID_LANELINE2_COLOR,laneLine2);
    this->setPropertyValue(PROPERTYID_LANELINE4_COLOR,laneLine4);
}

//车道线是否显示
void ADASControl::handLaneLinesDisplay()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ADAS_LINE_1_DISPLAY,msg)) {
        setPropertyValue(PROPERTYID_LANELINE1_DISPLAY,msg.value == 0x2 ? true : false);
    }

    if(getMsgValue(MSG_ADAS_LINE_2_DISPLAY,msg)) {
        setPropertyValue(PROPERTYID_LANELINE2_DISPLAY,msg.value == 0x2 ? true : false);
    }

    if(getMsgValue(MSG_ADAS_LINE_3_DISPLAY,msg)) {
        setPropertyValue(PROPERTYID_LANELINE3_DISPLAY,msg.value == 0x2 ? true : false);
    }

    if(getMsgValue(MSG_ADAS_LINE_4_DISPLAY,msg)) {
        setPropertyValue(PROPERTYID_LANELINE4_DISPLAY,msg.value == 0x2 ? true : false);
    }
}

//车道线类型 虚线和实线
void ADASControl::handLaneLinesType()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ADAS_LINE_1_TYPE,msg)) {
        setPropertyValue(PROPERTYID_LANELINE1_TYPE,msg.value == 0x0 ? (int)Qt::DashLine : (int)Qt::SolidLine);
    }

    if(getMsgValue(MSG_ADAS_LINE_2_TYPE,msg)) {
        setPropertyValue(PROPERTYID_LANELINE2_TYPE,msg.value == 0x0 ? (int)Qt::DashLine : (int)Qt::SolidLine);
    }

    if(getMsgValue(MSG_ADAS_LINE_3_TYPE,msg)) {
        setPropertyValue(PROPERTYID_LANELINE3_TYPE,msg.value == 0x0 ? (int)Qt::DashLine : (int)Qt::SolidLine);
    }

    if(getMsgValue(MSG_ADAS_LINE_4_TYPE,msg)) {
        setPropertyValue(PROPERTYID_LANELINE4_TYPE,msg.value == 0x0 ? (int)Qt::DashLine : (int)Qt::SolidLine);
    }

}


#define LINE_A0(val) val * 0.01 - 10.23
#define LINE_A1(val) val * 0.001 - 1.023
#define LINE_A2(val) val * 0.00001 - 0.01023
#define LINE_A3(val) val * 0.00000001 - 0.00032768
#define LINE_CURVATURE(a0, a1, a2, a3) MAX_CUR * (a0 + a1 + a2 + a3) / (10.23 + 1.023 -0.01)
void ADASControl::handLaneLine1CurVature()
{
    SingleMessage msg;
    float a0, a1, a2, a3;
    if(getMsgValue(MSG_ADAS_LINE_1_A0, msg)){
        a0 = LINE_A0(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_1_A1, msg)){
        a1 = LINE_A1(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_1_A2, msg)){
        a2 = LINE_A2(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_1_A3, msg)){
        a3 = LINE_A3(msg.value);
    }

    line1Cur = LINE_CURVATURE(a0, a1, a2, a3);
    setPropertyValue(PROPERTYID_LANELINE1_CURVATURE, line1Cur);
}

void ADASControl::handLaneLine2CurVature()
{
    SingleMessage msg;
    float a0, a1, a2, a3;
    if(getMsgValue(MSG_ADAS_LINE_2_A0, msg)){
        a0 = LINE_A0(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_2_A1, msg)){
        a1 = LINE_A1(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_2_A2, msg)){
        a2 = LINE_A2(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_2_A3, msg)){
        a3 = LINE_A3(msg.value);
    }

    line2Cur = LINE_CURVATURE(a0, a1, a2, a3);
    setPropertyValue(PROPERTYID_LANELINE2_CURVATURE, line2Cur);
}

void ADASControl::handLaneLine3CurVature()
{
    SingleMessage msg;
    float a0, a1, a2, a3;
    if(getMsgValue(MSG_ADAS_LINE_3_A0, msg)){
        a0 = LINE_A0(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_3_A1, msg)){
        a1 = LINE_A1(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_3_A2, msg)){
        a2 = LINE_A2(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_3_A3, msg)){
        a3 = LINE_A3(msg.value);
    }

    line3Cur = LINE_CURVATURE(a0, a1, a2, a3);
    setPropertyValue(PROPERTYID_LANELINE3_CURVATURE, line3Cur);
}

void ADASControl::handLaneLine4CurVature()
{
    SingleMessage msg;
    float a0, a1, a2, a3;
    if(getMsgValue(MSG_ADAS_LINE_4_A0, msg)){
        a0 = LINE_A0(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_4_A1, msg)){
        a1 = LINE_A1(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_4_A2, msg)){
        a2 = LINE_A2(msg.value);
    }
    if(getMsgValue(MSG_ADAS_LINE_4_A3, msg)){
        a3 = LINE_A3(msg.value);
    }

    line4Cur = LINE_CURVATURE(a0, a1, a2, a3);
    setPropertyValue(PROPERTYID_LANELINE4_CURVATURE, line4Cur);
}

void ADASControl::handFctaLeftWarn()
{
    /*电源状态:ON
输入信号:
ADAS_FCTA_Left_Warn_St
输出信号：
0x0: Inactive 不显示
0x1: FCTA_LV1_Warning 黄色提示，
持续闪烁500ms On 500ms Off
0x2: FCTA_LV2_Warning 红色提示
持续闪烁 250ms On 250ms Off
0x3: Reserved 不显示
0x4: Reserved 不显示
0x5: Reserved 不显示
0x6: Reserved 不显示
0x7: Reserved 不显示
声音：
FCTA报警1级 ADAS_FCTA_Left_Warn_St=1 S2B
FCTA报警2级 ADAS_FCTA_Left_Warn_St=1 S2B
*/
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCTA_LEFT_WARN,msg)
     if(msg.value == 1 || msg.value == 2){
      miniAdasValue[FCTA_LEFT] = 1;
    }else{
        miniAdasValue[FCTA_LEFT] = 0;
    }
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTA_LEVEL1_FL,AUDIO_INDEX_FCTA_LEVEL1_FL,msg.value==0x1?AUDIO_PLAY:AUDIO_STOP);
    HMIAudioCtrl::setAudioStatByPower(HMIAudioCtrl::WARNING_STATE_POP_FCTA_LEVEL2_FL,AUDIO_INDEX_FCTA_LEVEL2_FL,msg.value==0x2?AUDIO_PLAY:AUDIO_STOP);
    switch(msg.value){
    case 0x1:
        m_WarningMap.insert(PROPERTYID_FCTA_LEFT_WARN,ADASEnums::LV1WARNING);
        setPropertyValue(PROPERTYID_FCTA_LEFT_WARN_F,ADASEnums::LV1WARNING);
        break;
    case 0x2:
        m_WarningMap.insert(PROPERTYID_FCTA_LEFT_WARN,ADASEnums::LV2WARNING);
        setPropertyValue(PROPERTYID_FCTA_LEFT_WARN_F,ADASEnums::LV2WARNING);
        break;
    default:
        m_WarningMap.insert(PROPERTYID_FCTA_LEFT_WARN,ADASEnums::NOWARNING);
        setPropertyValue(PROPERTYID_FCTA_LEFT_WARN_F,ADASEnums::NOWARNING);
    }

}

void ADASControl::handFctaRightWarn()
{
/*
 * 电源状态:ON
输入信号:
ADAS_FCTA_Right_Warn_St
输出信号：
0x0: Inactive 不显示
0x1: FCTA_LV1_Warning 黄色提示
0x2: FCTA_LV2_Warning 红色提示
0x3: Reserved 不显示
0x4: Reserved 不显示
0x5: Reserved 不显示
0x6: Reserved 不显示
0x7: Reserved 不显示
声音:
FCTA报警1级 ADAS_FCTA_Right_Warn_St=1 S2B
FCTA报警2级 ADAS_FCTA_Right_Warn_St=2 S2B
*/
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_FCTA_RIGHT_WARN,msg)
    if(msg.value == 1 || msg.value == 2){
        miniAdasValue[FCTA_RIGHT]= 1;
    }else{
        miniAdasValue[FCTA_RIGHT] = 0;
    }
    switch(msg.value){
    case 0x1:
        m_WarningMap.insert(PROPERTYID_FCTA_RIGHT_WARN,ADASEnums::LV1WARNING);
        setPropertyValue(PROPERTYID_FCTA_RIGHT_WARN_F,ADASEnums::LV1WARNING);
        break;
    case 0x2:
        m_WarningMap.insert(PROPERTYID_FCTA_RIGHT_WARN,ADASEnums::LV2WARNING);
        setPropertyValue(PROPERTYID_FCTA_RIGHT_WARN_F,ADASEnums::LV2WARNING);
        break;
    default:
        m_WarningMap.insert(PROPERTYID_FCTA_RIGHT_WARN,ADASEnums::NOWARNING);
        setPropertyValue(PROPERTYID_FCTA_RIGHT_WARN_F,ADASEnums::NOWARNING);
    }
}

void ADASControl::handAccObjectCapturedStatus()
{
/*
电源状态:ON
输入信号:
ACC_ObjectCapturedStatus  仅目标物0有高亮
输出信号
0x0：No ACC target 不高亮
0x1：Has ACC target 高亮显示
*/
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ACC_OBJECTCAPTUREDSTATUS,msg)
    switch (msg.value) {
    case 0x1:
        setPropertyValue(PROPERTYID_ACC_OBJECTCAPTUREDSTATUS,true);
    default:
        setPropertyValue(PROPERTYID_ACC_OBJECTCAPTUREDSTATUS,false);
        break;
    }

}

ADASEnums::qmlTargetObjectType ADASControl::getTrackTargetObjectType(const PROPERTYID_ADAS &propertyId, const int &value)
{
    ADASEnums::qmlTargetObjectType objType;
    objType = value > objectTypeList.length() ? ADASEnums::ROADBLOCK : objectTypeList.at(value);
    return objType;
//    setPropertyValue(propertyId, objType);
}

//静态目标 是否显示
void ADASControl::handTrackTar()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ADAS_TRACKTAR0_STATIC_ST,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR0_STATIC_ST,msg.value == 0x1 ? true : false );
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR1_STATIC_ST,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR1_STATIC_ST,msg.value == 0x1 ? true : false );
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR2_STATIC_ST,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR2_STATIC_ST,msg.value == 0x1 ? true : false );
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR3_STATIC_ST,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR3_STATIC_ST,msg.value == 0x1 ? true : false );
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR4_STATIC_ST,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR4_STATIC_ST,msg.value == 0x1 ? true : false );
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR5_STATIC_ST,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR5_STATIC_ST,msg.value == 0x1 ? true : false );
    }

}

//静态目标类型
void ADASControl::handTrackTarStaticObjectType()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ADAS_TRACKTAR0_STATIC_ST,msg)) {
        getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET0_STATIC_OBJECTTYPE,msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR1_STATIC_ST,msg)) {
        getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET1_STATIC_OBJECTTYPE,msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR2_STATIC_ST,msg)) {
        getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET2_STATIC_OBJECTTYPE,msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR3_STATIC_ST,msg)) {
        getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET3_STATIC_OBJECTTYPE,msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR4_STATIC_ST,msg)) {
        getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET4_STATIC_OBJECTTYPE,msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR5_STATIC_ST,msg)) {
        getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET5_STATIC_OBJECTTYPE,msg.value);
    }
}

void ADASControl::handTrackTar_Static_LgtPo()
{
    SingleMessage msg;

    if(getMsgValue(MSG_ADAS_TRACKTAR0_STATIC_LGTPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR0_STATIC_LGTPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR1_STATIC_LGTPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR1_STATIC_LGTPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR2_STATIC_LGTPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR2_STATIC_LGTPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR3_STATIC_LGTPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR3_STATIC_LGTPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR4_STATIC_LGTPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR4_STATIC_LGTPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR5_STATIC_LGTPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR5_STATIC_LGTPO,(int)msg.value);
    }

}

void ADASControl::handTrackTar_Static_LatPo()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ADAS_TRACKTAR0_STATIC_LATPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR0_STATIC_LATPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR1_STATIC_LATPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR1_STATIC_LATPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR2_STATIC_LATPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR2_STATIC_LATPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR3_STATIC_LATPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR3_STATIC_LATPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR4_STATIC_LATPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR4_STATIC_LATPO,(int)msg.value);
    }

    if(getMsgValue(MSG_ADAS_TRACKTAR5_STATIC_LATPO,msg)) {
        setPropertyValue(PROPERTYID_ADAS_TRACKTAR5_STATIC_LATPO,(int)msg.value);
    }
}

void ADASControl::handAnrcPrkgStsIndcr()
{
    SingleMessage msg;
    INIT_SINGLEMESSAGE_VALUE(MSG_ANRC_PRKGSTSINDCR,msg)
    switch (msg.value) {
    case 0x1:
        setPropertyValue(PROPERTYID_ANRC_PRKGSTSINDCR,true);
        break;
    default:
        setPropertyValue(PROPERTYID_ANRC_PRKGSTSINDCR,false);
        break;
    }
}

void ADASControl::handAnrcAnrcPrkgLeSlotTyp()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ANRC_PRKGLESLOTTYP1,msg)) {
        setPropertyValue(PROPERTYID_ANRC_PRKGLESLOTTYP1,msg.value >= 0x1 && msg.value <= 0x4 ? true : false );
    }

    if(getMsgValue(MSG_ANRC_PRKGLESLOTTYP2,msg)) {
        setPropertyValue(PROPERTYID_ANRC_PRKGLESLOTTYP2,msg.value >= 0x1 && msg.value <= 0x4 ? true : false );
    }

    if(getMsgValue(MSG_ANRC_PRKGLESLOTTYP3,msg)) {
        setPropertyValue(PROPERTYID_ANRC_PRKGLESLOTTYP3,msg.value >= 0x1 && msg.value <= 0x4 ? true : false );
    }
}

void ADASControl::handAnrcAnrcPrkgRiSlotTyp()
{
    SingleMessage msg;
    if(getMsgValue(MSG_ANRC_PRKGRISLOTTYP1,msg)) {
        setPropertyValue(PROPERTYID_ANRC_PRKGRISLOTTYP1,msg.value >= 0x1 && msg.value <= 0x4 ? true : false );
    }

    if(getMsgValue(MSG_ANRC_PRKGRISLOTTYP2,msg)) {
        setPropertyValue(PROPERTYID_ANRC_PRKGRISLOTTYP2,msg.value >= 0x1 && msg.value <= 0x4 ? true : false );
    }

    if(getMsgValue(MSG_ANRC_PRKGRISLOTTYP3,msg)) {
        setPropertyValue(PROPERTYID_ANRC_PRKGRISLOTTYP3,msg.value >= 0x1 && msg.value <= 0x4 ? true : false );
    }
}

void ADASControl::handParkUpDistance()
{
    SingleMessage msg;
    //SR场景中需要显示泊车雷达的距离，泊车雷达为前4后4探头，显示距离由10cm-150cm，精度10cm，制图时信号向下取整，即总共16个gap；
    //泊车雷达还有左右两侧各4个探头，显示为两个Gap；
    //泊车雷达线需增加颜色显示，并有颜色过渡效果，整体分为红橙黄绿4个颜色
    //前后雷达需显示具体的距离值
    static int distance = 0;
    if(getMsgValue(MSG_ANRC_PRKGFRNTLEDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGFRNTMIDLEDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGFRNTMIDRIDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGFRNTRIDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    setPropertyValue(PROPERTYID_PARK_UP_DISTANCE,distance);
    handPark_Up_Down_Distance_Color(PROPERTYID_PARK_UP_DISTANCE_COLOR,distance);
}

void ADASControl::handParkDownDistance()
{
    SingleMessage msg;
    static int distance = 0;
    if(getMsgValue(MSG_ANRC_PRKGREARLEDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGREARMIDLEDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGREARMIDRIDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGREARRIDSTTOOBSTCL,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    setPropertyValue(PROPERTYID_PARK_DOWN_DISTANCE,distance);
    handPark_Up_Down_Distance_Color(PROPERTYID_PARK_DOWN_DISTANCE_COLOR,distance);
}

void ADASControl::handParkLeftDistance()
{
    SingleMessage msg;
    static ADASEnums::qmlParkDistance distance = ADASEnums::PARKDISTANCE_NONE;
    distance = ADASEnums::PARKDISTANCE_NONE;
    if(getMsgValue(MSG_ANRC_PRKGSIDEFRNTLEOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGSIDEFRNTMIDLEOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGSIDEREARMIDLEOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGSIDEREARLEOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    setPropertyValue(PROPERTYID_PARK_LEFT_DISTANCE_COLOR,distance);
}

void ADASControl::handParkRightDistance()
{
    SingleMessage msg;
    static ADASEnums::qmlParkDistance distance = ADASEnums::PARKDISTANCE_NONE;
    distance = ADASEnums::PARKDISTANCE_NONE;
    if(getMsgValue(MSG_ANRC_PRKGSIDEFRNTRIOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGSIDEFRNTMIDRIOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGSIDEREARMIDRIOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    if(getMsgValue(MSG_ANRC_PRKGSIDEREARRIOBSTCLZON,msg)) {
        checkDistanceValue(msg.value,distance);
    }

    setPropertyValue(PROPERTYID_PARK_RIGHT_DISTANCE_COLOR,distance);
}

void ADASControl::checkDistanceValue(const int &value, int &distance)
{
    //有效范围 向下取整
    if(value != 0xff && value >= 10 && value <= 150) {
        distance = value < distance ? value : distance;
    }
}

void ADASControl::checkDistanceValue(const int &value, ADASEnums::qmlParkDistance &distance)
{
    switch (value) {
    case 0x1:
        distance = distance == ADASEnums::PARKDISTANCE_RED ? ADASEnums::PARKDISTANCE_RED : ADASEnums::PARKDISTANCE_YELLOW;
        break;
    case 0x2:
        distance = ADASEnums::PARKDISTANCE_RED;
        break;
    default:
        break;
    }
}

void ADASControl::handPark_Up_Down_Distance_Color(const PROPERTYID_ADAS &propertyId, const int &value)
{
    ADASEnums::qmlParkDistance color;
    if(value <= 30) {
        color = ADASEnums::PARKDISTANCE_RED;
    } else if(value <= 50) {
        color = ADASEnums::PARKDISTANCE_ORANGE;
    } else if(value <= 90) {
        color = ADASEnums::PARKDISTANCE_YELLOW;
    } else {
        color = ADASEnums::PARKDISTANCE_GREEN;
    }

    setPropertyValue(propertyId,color);
}

/**
    当前红色：
    距离>6m时，变成黄色
    当前黄色：
    距离<5m时，变成红色
    距离>11m时，变成灰色
    当前灰色：
    距离<10m时，变成黄色
*/
ADASEnums::qmlTargetObjectDistColor getLineColor(float dist){
    float realDist = dist / 0.5;
    if(realDist < 5){
        return ADASEnums::DISTANCE_RED;
    }else if(realDist > 6 && realDist < 10){
        return ADASEnums::DISTANCE_YELLOW;
    }else if(realDist > 11){
        return ADASEnums::DISTANCE_GRAY;
    }
}

//目标物0
void ADASControl::handleTarget0Object()
{
    SingleMessage msg;
    int tar0_y;
    int real_x;
    int timeout = 1;
    //是否显示
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET0_ST,msg);
    timeout = timeout << msg.isTimeout;
    Target_T0.enable = (int)msg.value;
    //目标物类型
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET0_OBJECTTYPE,msg);
    timeout = timeout << msg.isTimeout;
    Target_T0.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET0_OBJECTTYPE,msg.value);
    //y坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR0_LGTPO,msg);
    timeout = timeout << msg.isTimeout;
    tar0_y = (int)msg.value;
    Target_T0.positionY = tar0_y;
    //x坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR0_LATPO,msg);
    timeout = timeout << msg.isTimeout;
    real_x = GET_REAL_X(tar0_y, line1Cur, (int)msg.value);
    Target_T0.positionX = real_x;

    //超时不显示
    if(timeout > 1){
        Target_T0.enable = 0;
    }

    int timeout_static = 1;
    //静态目标物优先级低于动态目标物
    if(Target_T0.enable == 0)
    {
        //是否显示
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR0_STATIC_ST,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T0.enable = (int)msg.value;
        //目标物类型
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR0_STATIC_OBJECTTYPE,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T0.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET0_OBJECTTYPE,msg.value);
        //y坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR0_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        tar0_y = (int)msg.value;
        Target_T0.positionY = tar0_y;
        //x坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR0_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        real_x = GET_REAL_X(tar0_y, line1Cur, (int)msg.value);
        Target_T0.positionX = real_x;
    }
    if(timeout == 1 || timeout_static == 1){
        //半径
        int t0_radius = GET_RADIUS(real_x, tar0_y);
        Target_T0.arcRadius = t0_radius;
        //弧起始角度
        int t0_startAngle = GET_START_ANGLE(tar0_y, real_x);
        Target_T0.arcStartAngle = t0_startAngle;
        //弧线颜色
        Target_T0.arcColor = getLineColor(t0_radius);
        handleAdasTarget(&Target_T0);
    }
}

//目标物1
void ADASControl::handleTarget1Object()
{
    SingleMessage msg;
    int tar1_y;
    int real_x;
    int timeout = 1;
    //是否显示
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET1_ST,msg);
    timeout = timeout << msg.isTimeout;
    Target_T1.enable = (int)msg.value;
    //目标物类型
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET1_OBJECTTYPE,msg);
    timeout = timeout << msg.isTimeout;
    Target_T1.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET1_OBJECTTYPE,msg.value);
    //y坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR1_LGTPO,msg);
    timeout = timeout << msg.isTimeout;
    tar1_y = (int)msg.value;
    Target_T1.positionY = tar1_y;
    //x坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR1_LATPO,msg);
    timeout = timeout << msg.isTimeout;
    real_x = GET_REAL_X(tar1_y, line1Cur, (int)msg.value);
    Target_T1.positionX = real_x;

    //超时不显示
    if(timeout > 1){
        Target_T1.enable = 0;
    }

    int timeout_static = 1;
    //静态目标物优先级低于动态目标物
    if(Target_T1.enable == 0)
    {
        //是否显示
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR1_STATIC_ST,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T1.enable = (int)msg.value;
        //目标物类型
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR1_STATIC_OBJECTTYPE,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T1.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET1_OBJECTTYPE,msg.value);
        //y坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR1_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        tar1_y = (int)msg.value;
        Target_T1.positionY = tar1_y;
        //x坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR1_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        real_x = GET_REAL_X(tar1_y, line1Cur, (int)msg.value);
        Target_T1.positionX = real_x;
    }
    if(timeout == 1 || timeout_static == 1){
        //半径
        int t1_radius = GET_RADIUS(real_x, tar1_y);
        Target_T1.arcRadius = t1_radius;
        //弧起始角度
        int t1_startAngle = GET_START_ANGLE(tar1_y, real_x);
        Target_T1.arcStartAngle = t1_startAngle;
        //弧线颜色
        Target_T1.arcColor = getLineColor(t1_radius);
        handleAdasTarget(&Target_T1);
    }
}

//目标物2
void ADASControl::handleTarget2Object()
{
    SingleMessage msg;
    int tar2_y;
    int real_x;
    int timeout = 1;
    //是否显示
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET2_ST,msg);
    timeout = timeout << msg.isTimeout;
    Target_T2.enable = (int)msg.value;
    //目标物类型
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET2_OBJECTTYPE,msg);
    timeout = timeout << msg.isTimeout;
    Target_T2.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET2_OBJECTTYPE,msg.value);
    //y坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR2_LGTPO,msg);
    timeout = timeout << msg.isTimeout;
    tar2_y = (int)msg.value;
    Target_T2.positionY = tar2_y;
    //x坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR2_LATPO,msg);
    timeout = timeout << msg.isTimeout;
    real_x = GET_REAL_X(tar2_y, line1Cur, (int)msg.value);
    Target_T2.positionX = real_x;

    //超时不显示
    if(timeout > 1){
        Target_T2.enable = 0;
    }

    int timeout_static = 1;
    //静态目标物优先级低于动态目标物
    if(Target_T2.enable == 0)
    {
        //是否显示
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR2_STATIC_ST,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T2.enable = (int)msg.value;
        //目标物类型
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR2_STATIC_OBJECTTYPE,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T2.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET2_OBJECTTYPE,msg.value);
        //y坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR2_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        tar2_y = (int)msg.value;
        Target_T2.positionY = tar2_y;
        //x坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR2_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        real_x = GET_REAL_X(tar2_y, line1Cur, (int)msg.value);
        Target_T2.positionX = real_x;
    }
    if(timeout == 1 || timeout_static == 1){
        //半径
        int t2_radius = GET_RADIUS(real_x, tar2_y);
        Target_T2.arcRadius = t2_radius;
        //弧起始角度
        int t2_startAngle = GET_START_ANGLE(tar2_y, real_x);
        Target_T2.arcStartAngle = t2_startAngle;
        //弧线颜色
        Target_T2.arcColor = getLineColor(t2_radius);
        handleAdasTarget(&Target_T2);
    }
}

//目标物3
void ADASControl::handleTarget3Object()
{
    SingleMessage msg;
    int tar3_y;
    int real_x;
    int timeout = 1;
    //是否显示
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET3_ST,msg);
    timeout = timeout << msg.isTimeout;
    Target_T3.enable = (int)msg.value;
    //目标物类型
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET3_OBJECTTYPE,msg);
    timeout = timeout << msg.isTimeout;
    Target_T3.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET3_OBJECTTYPE,msg.value);
    //y坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR3_LGTPO,msg);
    timeout = timeout << msg.isTimeout;
    tar3_y = (int)msg.value;
    Target_T3.positionY = tar3_y;
    //x坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR3_LATPO,msg);
    timeout = timeout << msg.isTimeout;
    real_x = GET_REAL_X(tar3_y, line1Cur, (int)msg.value);
    Target_T3.positionX = real_x;

    //超时不显示
    if(timeout > 1){
        Target_T3.enable = 0;
    }

    int timeout_static = 1;
    //静态目标物优先级低于动态目标物
    if(Target_T3.enable == 0)
    {
        //是否显示
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR3_STATIC_ST,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T3.enable = (int)msg.value;
        //目标物类型
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR3_STATIC_OBJECTTYPE,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T3.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET3_OBJECTTYPE,msg.value);
        //y坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR3_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        tar3_y = (int)msg.value;
        Target_T3.positionY = tar3_y;
        //x坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR3_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        real_x = GET_REAL_X(tar3_y, line1Cur, (int)msg.value);
        Target_T3.positionX = real_x;
    }
    if(timeout == 1 || timeout_static == 1){
        //半径
        int t3_radius = GET_RADIUS(real_x, tar3_y);
        Target_T3.arcRadius = t3_radius;
        //弧起始角度
        int t3_startAngle = GET_START_ANGLE(tar3_y, real_x);
        Target_T3.arcStartAngle = t3_startAngle;
        //弧线颜色
        Target_T3.arcColor = getLineColor(t3_radius);
        handleAdasTarget(&Target_T3);
    }
}

//目标物4
void ADASControl::handleTarget4Object()
{
    SingleMessage msg;
    int tar4_y;
    int real_x;
    int timeout = 1;
    //是否显示
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET4_ST,msg);
    timeout = timeout << msg.isTimeout;
    Target_T4.enable = (int)msg.value;
    //目标物类型
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET4_OBJECTTYPE,msg);
    timeout = timeout << msg.isTimeout;
    Target_T4.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET4_OBJECTTYPE,msg.value);
    //y坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR4_LGTPO,msg);
    timeout = timeout << msg.isTimeout;
    tar4_y = (int)msg.value;
    Target_T4.positionY = tar4_y;
    //x坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR4_LATPO,msg);
    timeout = timeout << msg.isTimeout;
    real_x = GET_REAL_X(tar4_y, line1Cur, (int)msg.value);
    Target_T4.positionX = real_x;

    //超时不显示
    if(timeout > 1){
        Target_T4.enable = 0;
    }

    int timeout_static = 1;
    //静态目标物优先级低于动态目标物
    if(Target_T4.enable == 0)
    {
        //是否显示
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR4_STATIC_ST,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T4.enable = (int)msg.value;
        //目标物类型
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR4_STATIC_OBJECTTYPE,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T4.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET4_OBJECTTYPE,msg.value);
        //y坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR4_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        tar4_y = (int)msg.value;
        Target_T4.positionY = tar4_y;
        //x坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR4_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        real_x = GET_REAL_X(tar4_y, line1Cur, (int)msg.value);
        Target_T4.positionX = real_x;
    }
    if(timeout == 1 || timeout_static == 1){
        //半径
        int t4_radius = GET_RADIUS(real_x, tar4_y);
        Target_T4.arcRadius = t4_radius;
        //弧起始角度
        int t4_startAngle = GET_START_ANGLE(tar4_y, real_x);
        Target_T4.arcStartAngle = t4_startAngle;
        //弧线颜色
        Target_T4.arcColor = getLineColor(t4_radius);
        handleAdasTarget(&Target_T4);
    }
}

//目标物5
void ADASControl::handleTarget5Object()
{
    SingleMessage msg;
    int tar5_y;
    int real_x;
    int timeout = 1;
    //是否显示
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET5_ST,msg);
    timeout = timeout << msg.isTimeout;
    Target_T5.enable = (int)msg.value;
    //目标物类型
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTARGET5_OBJECTTYPE,msg);
    timeout = timeout << msg.isTimeout;
    Target_T5.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET5_OBJECTTYPE,msg.value);
    //y坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR5_LGTPO,msg);
    timeout = timeout << msg.isTimeout;
    tar5_y = (int)msg.value;
    Target_T5.positionY = tar5_y;
    //x坐标
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR5_LATPO,msg);
    timeout = timeout << msg.isTimeout;
    real_x = GET_REAL_X(tar5_y, line1Cur, (int)msg.value);
    Target_T5.positionX = real_x;

    //超时不显示
    if(timeout > 1){
        Target_T5.enable = 0;
    }

    int timeout_static = 1;
    //静态目标物优先级低于动态目标物
    if(Target_T5.enable == 0)
    {
        //是否显示
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR5_STATIC_ST,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T5.enable = (int)msg.value;
        //目标物类型
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR5_STATIC_OBJECTTYPE,msg);
        timeout_static = timeout_static << msg.isTimeout;
        Target_T5.targetObjectType = getTrackTargetObjectType(PROPERTYID_ADAS_TRACKTARGET5_OBJECTTYPE,msg.value);
        //y坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR5_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        tar5_y = (int)msg.value;
        Target_T5.positionY = tar5_y;
        //x坐标
        INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_TRACKTAR5_STATIC_LGTPO,msg);
        timeout_static = timeout_static << msg.isTimeout;
        real_x = GET_REAL_X(tar5_y, line1Cur, (int)msg.value);
        Target_T5.positionX = real_x;
    }
    if(timeout == 1 || timeout_static == 1){
        //半径
        int t5_radius = GET_RADIUS(real_x, tar5_y);
        Target_T5.arcRadius = t5_radius;
        //弧起始角度
        int t5_startAngle = GET_START_ANGLE(tar5_y, real_x);
        Target_T5.arcStartAngle = t5_startAngle;
        //弧线颜色
        Target_T5.arcColor = getLineColor(t5_radius);
        handleAdasTarget(&Target_T5);
    }
}

void ADASControl::handleACCTimeGap()
{
    SingleMessage msg;
    int accTimeGap = 0;
    INIT_SINGLEMESSAGE_VALUE(MSG_ADAS_ACC_TIMEGAP,msg);
    if(msg.isTimeout){
        m_gapTimer->stop();
        setPropertyValue(PROPERTYID_ACC_TIME_GAP_VISIBLE, false);
    }
    else{
        if(msg.value <= 5) accTimeGap = msg.value;
        if(accTimeGapBackup != accTimeGap){
            if(accTimeGap){
                m_gapTimer->reset();
                setPropertyValue(PROPERTYID_ACC_TIME_GAP_VISIBLE, true);
            }else{
                m_gapTimer->stop();
                setPropertyValue(PROPERTYID_ACC_TIME_GAP_VISIBLE, false);
            }
        }
        accTimeGapBackup = accTimeGap;
    }
    setPropertyValue(PROPERTYID_ACC_TIME_GAP, accTimeGap);
}

void ADASControl::handleAdasTarget(AdasTarget * target)
{/* targetObjectType = t;
    positionX = px;
    positionY = py;
    arcRadius = r;
    arcStartAngle = a;
    arcColor = c;
    enable = e;      */
    emit PropertyChange(target->propertyIndex, TargetData(target->targetObjectType, target->positionX, target->positionY, target->arcRadius, target->arcStartAngle, target->arcColor, target->enable));
}

void ADASControl::func_adas_AudioPlay(Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd)
//adas报警音
{
    (void)audio_id;
    if(audio_Cmd == AUDIO_PLAY){
        if(POWERMODE_D1 == g_powermode){
            //D1以外的电源模式下不能play
//            hmi_lib_AudioPlay(HMI_MID_ADAS, 0, audio_id, audio_Cmd);
        }
    }
    else
    {
//        hmi_lib_AudioPlay(HMI_MID_ADAS, 0, audio_id, audio_Cmd);
    }
}


void ADASControl::dataChange()
{
    foreach (ADASControl::FunctionParser func, adasControlFuncList) {
        (this->*(func))();
    }
}

void ADASControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
//    if ( HMI_MSGNAME_POWER_MODE == message_key ) {
//        g_powermode = message_value.toInt();
//        if(POWERMODE_D1 != g_powermode){
//            //D1以外的电源模式下声音需要停止
//        }
//    } else {
//        // Nothing
//    }
}

void ADASControl::get_timeout500ms()
{
    //500ms 提示闪烁
    static bool LV1_Switch_500 = true;
    QMapIterator<PROPERTYID_ADAS,ADASEnums::qmlWarnLevel> i(m_WarningMap);
    while (i.hasNext()) {
        i.next();
        if(i.value() == ADASEnums::LV1WARNING) {
            setPropertyValue(i.key(),LV1_Switch_500 ? ADASEnums::LV1WARNING : ADASEnums::NOWARNING);
        } else if(i.value() == ADASEnums::NOWARNING) {
            setPropertyValue(i.key(),ADASEnums::NOWARNING);
        }
    }
    LV1_Switch_500 = !LV1_Switch_500;
    m_leftILCTime->update();
    m_rightILCTime->update();
    if(miniAdasValue.contains(1)){
        setPropertyValue(PROPERTYID_MINIADAS_VISIBLE, true);
    }else{
        setPropertyValue(PROPERTYID_MINIADAS_VISIBLE, false);
    }
    m_gapTimer->update();

}

void ADASControl::get_timeout10ms()
{
    M_ARDS_WORKING_STATE->update();
}

void ADASControl::get_timeout250ms()
{
    //250ms 提示闪烁
    static bool LV2_Switch_250 = true;
    QMapIterator<PROPERTYID_ADAS,ADASEnums::qmlWarnLevel> i(m_WarningMap);
    while (i.hasNext()) {
        i.next();
        if(i.value() == ADASEnums::LV2WARNING) {
            setPropertyValue(i.key(),LV2_Switch_250 ? ADASEnums::LV2WARNING : ADASEnums::NOWARNING);
        } else if(i.value() == ADASEnums::NOWARNING) {
            setPropertyValue(i.key(),ADASEnums::NOWARNING);
        }
    }
    LV2_Switch_250 = !LV2_Switch_250;

    /*

    方案2 只发 LV2_Switch_250

    QML中

    Image {
        //当 HW报警为真 250MS 为真显示
        visible:  LED && LV2_Switch_250
    }
*/
}

void ADASControl::iC_Can_Info_Send(int reqSendID)
{
    Q_UNUSED(reqSendID)
    //IVSProxyRequest _buffer;
    //void * pUser_data = NULL;
    //
    //memset(&_buffer, 0, sizeof(IVSProxyRequest));
    //_buffer.rw	    = 0x01;
    //_buffer.length  = 0x0020;
    //_buffer.control = 0x00;
    //_buffer.opecode = 0x075A;
    //switch (reqSendID) {
    //case ADAS_ic_PEBSVoiceWarningSetFeedback :
    //    _buffer.data[0] = 0X07;   //msg id
    //    _buffer.data[1] = 0x01;   //len
    //
    //    break;
    //case ADAS_ic_qDashACCFail:
    //    _buffer.data[0] = 0x06;   //msg id
    //    _buffer.data[1] = 0x01;   //len
    //    break;
    //default:
    //    return;
    //}
    //ivs_client_send_request(&_buffer, pUser_data);
}
