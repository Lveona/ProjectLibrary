#include "./include/mysharememory.h"
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QDebug>

ShareMemoryThreadA::ShareMemoryThreadA()
    :m_maxSize(500)
{
}

ShareMemoryThreadA::~ShareMemoryThreadA()
{
}

void ShareMemoryThreadA::sendData(QString key, QVariant data)
{
    QMutexLocker _locker(&mutex);
    m_sendMap.insert(key, data);
    _locker.unlock();
}

void ShareMemoryThreadA::setKey(QString str)
{    
    m_shareMemory.setKey(str);
}

void ShareMemoryThreadA::run()
{
    while(!isInterruptionRequested())
    {
        //send

        QMutexLocker _locker(&mutex);

        QString data = "";

        QStringList keys = m_sendMap.keys();
        foreach(QString key, keys)
        {
            data += key + ":" + m_sendMap.value(key).toString() + "&";
        }

        _locker.unlock();   //防止线程锁在长时间占用

        QByteArray ba = data.toUtf8();
        if(m_shareMemory.isAttached())
        {
            m_shareMemory.detach();//将该进程与共享内存段分离
        }
        else{
        }

        QBuffer buffer;
        buffer.setBuffer(&ba);

        int size = static_cast<const int>(buffer.size());

        if(size > m_maxSize)
        {
            m_maxSize = size;
        }

        if(m_shareMemory.create(m_maxSize))
        {
            m_shareMemory.lock();
            char *to = static_cast<char*>(m_shareMemory.data());
            const char *from = static_cast<const char*>(buffer.data().data());

            int shareSize = static_cast<int>(m_shareMemory.size());
            memset(to,0,static_cast<size_t>(shareSize)); //clear
            memcpy(to,from,qMin(shareSize, size));//数据从该进程中拷贝到共享数据内存中
            m_shareMemory.unlock();//共享内层解锁
        }
        else{}

        msleep(20);
    }

}


ShareMemoryThreadB::ShareMemoryThreadB()
{
    m_lastTime_receiveData = "";
}

ShareMemoryThreadB::~ShareMemoryThreadB()
{
}

void ShareMemoryThreadB::setKey(QString str)
{
    m_shareMemory.setKey(str);
}

void ShareMemoryThreadB::run()
{

    while(!isInterruptionRequested())
    {
        //receive
        if(m_shareMemory.attach()){
            //qWarning()<<tr("ShareMemoryThreadB m_shareMemory detach")<<m_shareMemory.nativeKey()<<m_shareMemory.key();
            m_shareMemory.lock();
            QBuffer buffer;
            QString saveData = "";
            buffer.setData(static_cast<const char*>(m_shareMemory.constData()),m_shareMemory.size());//将shareMemeory里的数据放到buffer里
            m_shareMemory.unlock();
            m_shareMemory.detach();//将shareMemeory与该进程分离

            if(m_lastTime_receiveData != QString(buffer.data())){
                if(!QString(buffer.data()).isEmpty())
                {
                    saveData = QString(buffer.data());
                    emit receiveDateFromOtherProcess(saveData);
                    m_lastTime_receiveData = saveData;
                }
            }
        }
        msleep(10);
    }
}

MyShareMemory::MyShareMemory()
{
    m_ShareMemoryThreadA = new ShareMemoryThreadA;
    m_ShareMemoryThreadB = new ShareMemoryThreadB;
    connect(m_ShareMemoryThreadB, &ShareMemoryThreadB::receiveDateFromOtherProcess, this, &MyShareMemory::receiveDateFromOtherProcess, Qt::AutoConnection);

}

MyShareMemory::~MyShareMemory()
{
    m_ShareMemoryThreadA->requestInterruption();
    m_ShareMemoryThreadA->quit();
    m_ShareMemoryThreadA->wait(100);
    delete m_ShareMemoryThreadA;

    m_ShareMemoryThreadB->requestInterruption();
    m_ShareMemoryThreadB->quit();
    m_ShareMemoryThreadB->wait(100);
    delete m_ShareMemoryThreadB;
}

void MyShareMemory::sendData(QString key, QVariant data)
{
    m_ShareMemoryThreadA->sendData(key, data);
}

void MyShareMemory::setSendKeyA(QString str)
{
    m_ShareMemoryThreadA->setKey(str);
    m_ShareMemoryThreadA->start(QThread::NormalPriority);
}
void MyShareMemory::setSendKeyB(QString str)
{
    m_ShareMemoryThreadB->setKey(str);
    m_ShareMemoryThreadB->start(QThread::NormalPriority);
}
