#include "worker.h"
#include <QTimer>

void Worker::run()
{
    m_timer500msec = new QTimer;
    m_timer500msec->setInterval(500);
    connect(m_timer500msec, &QTimer::timeout, this, &Worker::notify500ms, Qt::DirectConnection);
    m_timer500msec->start();


    m_timer100msec = new QTimer;
    m_timer100msec->setInterval(100);
    connect(m_timer100msec, &QTimer::timeout, this, &Worker::notify100ms, Qt::DirectConnection);
    m_timer100msec->start();

    m_timer10msec = new QTimer;
    m_timer10msec->setInterval(10);
    connect(m_timer10msec, &QTimer::timeout, this, &Worker::notify10ms, Qt::DirectConnection);
    m_timer10msec->start();

    m_timer250msec = new QTimer;
    m_timer250msec->setInterval(250);
    connect(m_timer250msec, &QTimer::timeout, this, &Worker::notify250ms, Qt::DirectConnection);
    m_timer250msec->start();

    QThread::exec();
}
