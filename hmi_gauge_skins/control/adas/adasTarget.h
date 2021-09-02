#ifndef ADASTARGET_H
#define ADASTARGET_H

#include <QObject>
class AdasTarget
{

public:
    AdasTarget(
              char _propertyIndex,
              char _targetObjectType,
              char _positionX,
              char _positionY,
              char _arcRadius,
              char _arcStartAngle,
              char _arcColor,
              char _enable=1):
        propertyIndex(_propertyIndex),
        targetObjectType(_targetObjectType),
        positionX(_positionX),
        positionY(_positionY),
        arcRadius(_arcRadius),
        arcStartAngle(_arcStartAngle),
        arcColor(_arcColor),
        enable(_enable)
    {
    }
    AdasTarget(){}
    AdasTarget & operator =(const AdasTarget&);
    char propertyIndex;
    char targetObjectType;
    char positionX;
    char positionY;
    char arcRadius;
    char arcStartAngle;
    char arcColor;
    char enable;
};
class TargetData: public QObject
{
    Q_OBJECT
    //目标类型
    Q_PROPERTY(char targetObjectType READ targetObjectType WRITE setTargetObjectType NOTIFY targetObjectTypeChanged)
    //x坐标
    Q_PROPERTY(char positionX READ positionX WRITE setPositionX NOTIFY positionXChanged)
    //y坐标
    Q_PROPERTY(char positionY READ positionY WRITE setpositionY NOTIFY positionYChanged)
    //半径
    Q_PROPERTY(char arcRadius READ arcRadius WRITE setArcRadius NOTIFY arcRadiusChanged)
    //起始角度
    Q_PROPERTY(char arcStartAngle READ arcStartAngle WRITE setArcStartAngle NOTIFY arcStartAngleChanged)
    //弧线颜色
    Q_PROPERTY(char arcColor READ arcColor WRITE setArcColor NOTIFY arcColorChanged)
    //目标是否显示
    Q_PROPERTY(char enable READ enable WRITE setEnable NOTIFY enableChanged)

public:
    TargetData(QObject* parent=0):QObject(parent){
        m_targetObjectType = 0;
        m_positionX = 0;
        m_positionY = 0;
        m_arcRadius = 0;
        m_arcStartAngle = 0;
        m_arcColor = 0;
        m_enable = 0;
    }
    TargetData(const TargetData& tar, QObject* parent=0)
        :QObject(parent)
    {
        m_targetObjectType = tar.m_targetObjectType;
        m_positionX = tar.m_targetObjectType;
        m_positionY = tar.m_positionY;
        m_arcRadius = tar.m_arcRadius;
        m_arcStartAngle = tar.m_arcStartAngle;
        m_arcColor = tar.m_arcColor;
        m_enable = tar.m_enable;
    }
    TargetData(char t, char px, char py, char r, char a, char c, char e, QObject* parent=0):QObject(parent){
        m_targetObjectType = t;
        m_positionX = px;
        m_positionY = py;
        m_arcRadius = r;
        m_arcStartAngle = a;
        m_arcColor = c;
        m_enable = e;
    }
    ~TargetData(){}
    TargetData & operator =(const TargetData& tar){
        m_targetObjectType = tar.m_targetObjectType;
        m_positionX = tar.m_targetObjectType;
        m_positionY = tar.m_positionY;
        m_arcRadius = tar.m_arcRadius;
        m_arcStartAngle = tar.m_arcStartAngle;
        m_arcColor = tar.m_arcColor;
        m_enable = tar.m_enable;
        return *this;
    }

    char m_targetObjectType;
    char m_positionX;
    char m_positionY;
    char m_arcRadius;
    char m_arcStartAngle;
    char m_arcColor;
    char m_enable;
    char targetObjectType() const
    {
        return m_targetObjectType;
    }

    char positionX() const
    {
        return m_positionX;
    }

    char positionY() const
    {
        return m_positionY;
    }

    char arcRadius() const
    {
        return m_arcRadius;
    }

    char arcStartAngle() const
    {
        return m_arcStartAngle;
    }

    char arcColor() const
    {
        return m_arcColor;
    }

    char enable() const
    {
        return m_enable;
    }

public slots:
    void setTargetObjectType(char targetObjectType)
    {
        if (m_targetObjectType == targetObjectType)
            return;

        m_targetObjectType = targetObjectType;
        emit targetObjectTypeChanged(m_targetObjectType);
    }

    void setPositionX(char positionX)
    {
        if (m_positionX == positionX)
            return;

        m_positionX = positionX;
        emit positionXChanged(m_positionX);
    }

    void setpositionY(char positionY)
    {
        if (m_positionY == positionY)
            return;

        m_positionY = positionY;
        emit positionYChanged(m_positionY);
    }

    void setArcRadius(char arcRadius)
    {
        if (m_arcRadius == arcRadius)
            return;

        m_arcRadius = arcRadius;
        emit arcRadiusChanged(m_arcRadius);
    }

    void setArcStartAngle(char arcStartAngle)
    {
        if (m_arcStartAngle == arcStartAngle)
            return;

        m_arcStartAngle = arcStartAngle;
        emit arcStartAngleChanged(m_arcStartAngle);
    }

    void setArcColor(char arcColor)
    {
        if (m_arcColor == arcColor)
            return;

        m_arcColor = arcColor;
        emit arcColorChanged(m_arcColor);
    }

    void setEnable(char enable)
    {
        if (m_enable == enable)
            return;

        m_enable = enable;
        emit enableChanged(m_enable);
    }

signals:
    void targetObjectTypeChanged(char targetObjectType);
    void positionXChanged(char positionX);
    void positionYChanged(char positionY);
    void arcRadiusChanged(char arcRadius);
    void arcStartAngleChanged(char arcStartAngle);
    void arcColorChanged(char arcColor);
    void enableChanged(char enable);
};


#endif // ADASTARGET_H
