#ifndef MYSHAREMEMORY_H
#define MYSHAREMEMORY_H

#include <QThread>
#include <QVariant>
#include <QSharedMemory>
#include "Singleton.h"

#include <QMutex>
//use to send data
class ShareMemoryThreadA: public QThread
{
    Q_OBJECT
public:
    ShareMemoryThreadA();
    ~ShareMemoryThreadA() override;
    void run() override;

    void sendData(QString key, QVariant data);
    void setKey(QString str);

public slots:


private:
    QMap<QString, QVariant> m_sendMap;
    QMutex mutex;
    QSharedMemory m_shareMemory;
    int m_maxSize;
};

//use to revceive data
class ShareMemoryThreadB: public QThread
{
    Q_OBJECT
public:
    ShareMemoryThreadB();
    ~ShareMemoryThreadB() override;
    void run() override;

    void setKey(QString str);

signals:
    void receiveDateFromOtherProcess(QString data);

public slots:


private:
    QString m_lastTime_receiveData;
    QStringList m_receiveList;
    QSharedMemory m_shareMemory;
};

class MyShareMemory:public QObject, public CSingleton<MyShareMemory>
{
    Q_OBJECT
    friend class CSingleton<MyShareMemory>;
public:
    MyShareMemory();
    ~MyShareMemory();
    void sendData(QString key, QVariant data);
    void setSendKeyA(QString str);
    void setSendKeyB(QString str);
private:
    ShareMemoryThreadA * m_ShareMemoryThreadA;
    ShareMemoryThreadB * m_ShareMemoryThreadB;
private slots:
signals:
    void receiveDateFromOtherProcess(QString data);
};

#endif // MYSHAREMEMORY_H
