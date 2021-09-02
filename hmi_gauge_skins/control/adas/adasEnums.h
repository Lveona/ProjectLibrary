#ifndef ADASENUMS_H
#define ADASENUMS_H

#include <QObject>
#include <QQuickView>

//#define ADAS_GRAY "#b19d78"
//#define ADAS_BLUE "#45abf2"
//#define ADAS_YELLOW "#fcc338"
//#define ADAS_RED "#e76e66"

class ADASEnums : public QObject
{
    Q_OBJECT

    Q_ENUMS(qmlWarnLevel)
    Q_ENUMS(qmlTargetObjectType)
    Q_ENUMS(qmlParkDistance)
public:
    ADASEnums(){
        qmlRegisterType<ADASEnums>("qmlEnums", 1, 0, "ADASEnums");
    }

    enum qmlLaneLineColor {
        ADAS_GRAY,
        ADAS_BLUE,
        ADAS_YELLOW,
        ADAS_RED,
    };

    enum qmlWarnLevel {//报警等级
        NOWARNING,//不显示
        LV1WARNING,//黄色提示
        LV2WARNING,//红色提示
    };

    enum qmlTargetObjectType { //动态目标类型
        ROADBLOCK = 0X0 ,// 路障模型（雪糕筒）
        CAR_MODEL,// 小车模型
        TWO_WHEELER_MODEL,// 两轮车模型
        TRUCK_MODEL,// 卡车模型
        PEDESTRIAN_MODEL,// 行人模型
        MAXTARGETSTATICOBJECTTYPE
    };

    enum qmlParkDistance { //泊车距离颜色
        PARKDISTANCE_NONE,
        PARKDISTANCE_RED,
        PARKDISTANCE_ORANGE,
        PARKDISTANCE_YELLOW,
        PARKDISTANCE_GREEN
    };

    enum qmlTargetObjectDistColor {
        DISTANCE_RED,
        DISTANCE_YELLOW,
        DISTANCE_GRAY
    };
};

#endif // ADASENUMS_H
