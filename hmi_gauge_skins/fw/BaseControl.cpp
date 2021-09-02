/*!
 * @file         baselib.cpp
 * @date         2018/05/15
 * @author       lxf
 * @version      0.1
 * @brief        Source code for Base Lib
 */
/*********************************************************************************
 * Revision History                                                              *
 * No    Date        Revised by        Description                               *
 * --    ----        ----------        -----------                               *
 * 01    18/05/15    lxf               New                                       *
 *********************************************************************************/
#include "./include/BaseControl.h"
#include <QDebug>
#include <QMap>
#include <QList>

CBaseControl::CBaseControl(QObject *parent) :QThread(parent)
{
}
CBaseControl::~CBaseControl()
{
    requestInterruption();
    quit();
    wait(100);
}

/*!
 *  @brief description for run()
 *  @param[in]     None
 *  @param[out]    None
 *  @return        None
 *  @return        None
 *  @author        Liuxf
 */
void CBaseControl::run()
{
    while(!isInterruptionRequested())
    {
        dataChange();
        msleep(10);
    }
}
/*!
 *  @brief	description for pushData()
 *  @param[in]     message:received from control
 *  @param[out]    Null
 *  @return        Null
 *  @return        Null
 *  @author        Liuxf
 */
void CBaseControl::pushData(SingleMessage &message)
{
    //lock()
    //qDebug()<<"CBaseControl::pushData"<<QThread::currentThreadId()<<QThread::currentThread();
   // qDebug()<< "Parent Thread Push Data: messageID is " << message.m_messageID << "message count" << m_messageList.count();
    QMutexLocker _locker(&mutex);
    Q_UNUSED(_locker)
    m_messageList.push_back(message);
}
