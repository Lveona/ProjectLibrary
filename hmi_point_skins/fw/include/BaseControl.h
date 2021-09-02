/*!
 * @file         baselib.h
 * @date         2018/05/15
 * @author       Lxf
 * @version      0.1
 * @brief        Header file for Base Lib
 */
/*********************************************************************************
 * Revision History                                                              *
 * No    Date        Revised by        Description                               *
 * --    ----        ----------        -----------                               *
 * 01    2018/05/15    lxf             New                                       *
 *********************************************************************************/
#ifndef BASELIB_H
#define BASELIB_H

#include <QMutex>
#include <QByteArray>
#include <QThread>
#include <QVariant>

typedef struct {
    int		m_messageID;
    QByteArray  m_messageData;
} Message;

typedef struct {
    int id;
    unsigned long int value;
    unsigned char isTimeout;
    operator QString() const {
        return QString("id=[%1] timeout=[%2] value=[%3]")
                .arg(this->id).arg(this->isTimeout).arg(this->value);
    }
} SingleMessage;

class CBaseControl : public QThread
{
    Q_OBJECT
public:
    explicit CBaseControl(QObject *parent = nullptr);
    ~CBaseControl() Q_DECL_OVERRIDE;

    void pushData(SingleMessage &message);

    QVariant getPropertyValue(int propertyId){
        return _signalMap.value(propertyId);
    }
protected:
    QList< SingleMessage > m_messageList;
    virtual void dataChange() = 0;

    void run() Q_DECL_OVERRIDE;

    void handleProperty(int propertyId, QVariant value){
        emit PropertyChange(propertyId, value);
    }

    void setPropertyValue(int propertyId, QVariant value){
        QVariant c_value = _signalMap.value(propertyId, -1);

        if(c_value != value){
            _signalMap.insert(propertyId, value);
            handleProperty(propertyId, value);
        }
    }

private:
    QMutex mutex;
    QMap<int, QVariant> _signalMap;

signals:
    void PropertyChange(int name,QVariant value);
    void sendToOtherCtrl(QString name, QVariant value);
    void sendToOtherProcess(QString name, int value);

public slots:

};
#endif // BASELIB_H
