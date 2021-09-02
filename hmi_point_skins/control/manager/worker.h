#ifndef WORKER_H
#define WORKER_H

#include <QThread>
class QTimer;

class Worker: public QThread
{
    Q_OBJECT
    void run();

signals:
    void notify500ms();
    void notify100ms();
    void notify10ms();

private:
    QTimer * m_timer500msec;
    QTimer * m_timer100msec;
    QTimer * m_timer10msec;
};

#endif // WORKER_H
