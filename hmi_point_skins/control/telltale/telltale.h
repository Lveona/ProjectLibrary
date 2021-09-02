#ifndef TELLTALE_H
#define TELLTALE_H
#include <QObject>

class Telltale
{
public:
    Telltale(char _powerMode,
              char _propertyIndex,
              char _targetValue,
              char _spangleType,
              char _colorType,
              char _enable=1):
        powerMode(_powerMode),
        propertyIndex(_propertyIndex),
        targetValue(_targetValue),
        spangleType(_spangleType),
        colorType(_colorType),
        enable(_enable)
    {
    }
    Telltale(){}
    Telltale & operator =(const Telltale&);
    char powerMode;               //电源模式
    char propertyIndex;          //ID
    char targetValue;           //亮灭闪
    char spangleType;             //闪烁频率
    char colorType;
    char enable;                //用于下线配置决定灯是否有效
};

class TellData: public QObject
{
    Q_OBJECT
    Q_PROPERTY(char targetValue READ targetValue WRITE setTargetValue NOTIFY targetValueChanged)
    Q_PROPERTY(char colorType READ colorType WRITE setColorType NOTIFY colorTypeChanged)

public:
    TellData(QObject* parent=0):QObject(parent){
        m_targetValue = 0;
        m_colorType = 0;
    }
    TellData(const TellData& tell, QObject* parent=0)
        :QObject(parent)
    {
        m_targetValue = tell.m_targetValue;
        m_colorType = tell.m_colorType;
    }
    TellData(char t, char c, QObject* parent=0):QObject(parent){
        m_targetValue = t;
        m_colorType = c;
    }
    ~TellData(){}
    TellData & operator =(const TellData& tell){
        m_targetValue = tell.m_targetValue;
        m_colorType = tell.m_colorType;
        return *this;
    }

    char targetValue() const
    {
        return m_targetValue;
    }
    char colorType() const
    {
        return m_colorType;
    }

    char m_targetValue;
    char m_colorType;

public slots:
    void setTargetValue(char targetValue)
    {
        if (m_targetValue == targetValue)
            return;

        m_targetValue = targetValue;
        emit targetValueChanged(m_targetValue);
    }
    void setColorType(char colorType)
    {
        if (m_colorType == colorType)
            return;

        m_colorType = colorType;
        emit colorTypeChanged(m_colorType);
    }

signals:
    void colorTypeChanged(char colorType);
    void targetValueChanged(char targetValue);

};

#endif // TELLTALE_H
