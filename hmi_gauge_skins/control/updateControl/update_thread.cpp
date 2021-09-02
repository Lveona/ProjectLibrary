#include "update_thread.h"
#include <QtDebug>

#include <hmi_share.h>
#include <update_proxy.h>
#include <QTimer>

static int g_count = -1;

extern "C"
{
    static void display_Msg_Update_IVP(unsigned char attribute_key, unsigned char attribute_value, void *puser_data)
    {
        Q_UNUSED(puser_data)
        Update_Thread::instance().pushDataLib(attribute_key, attribute_value);
    }
}

Update_Thread::Update_Thread(QObject *parent):QThread(parent)
{
    m_updateFile    = 0;
    m_messageType   = 4;
    m_processStep = 0;
    m_fileNum = "";
    m_timerInit = new QTimer();
    m_timerInit->setInterval(1000);
    connect(m_timerInit, SIGNAL(timeout()),this, SLOT(registeUpdate()));
    m_timerInit->start();

    timer100ms = new QTimer();
    timer100ms->setInterval(100);
    connect(timer100ms, SIGNAL(timeout()),this, SLOT(get_timeout100ms()));
    connect(this, SIGNAL(sendStartTimer100ms()), timer100ms, SLOT(start()), Qt::QueuedConnection);
    connect(this, SIGNAL(sendStopTimer100ms()), timer100ms, SLOT(stop()), Qt::QueuedConnection);

    this->start(QThread::NormalPriority);

}

Update_Thread::~Update_Thread()
{
    requestInterruption();
    this->quit();
    this->wait(100);
}

void Update_Thread::run()
{
    while(!isInterruptionRequested())
    {
        while(false == m_messageList.empty()) {
            QMutexLocker _locker(&mutex);
            Message1 _messageData = m_messageList.front();

            m_messageList.pop_front();  //delete list
            _locker.unlock();
            dataChange(_messageData);
        }
        msleep(100);
    }
}

void Update_Thread::setMessageType(int currentType)
{
    if ( m_messageType != currentType ) {
        m_messageType = currentType;
        qInfo()<<"setMessageType "<<currentType;
        emit messageTypeChanged();
    }
}

void Update_Thread::setProcessStep(int v)
{
    if( m_processStep != v ) {
        m_processStep = v;
        emit processStepChanged();
    }
}

void Update_Thread::setFileNum(QString v)
{
    if( m_fileNum != v ) {
        m_fileNum = v;
        emit fileNumChanged();
    }
}

void Update_Thread::pushDataLib(unsigned char messageID, unsigned char m_messageData)
{
    Message1 _message;
    _message.m_messageID   = messageID;
    _message.m_messageData = m_messageData;
    Update_Thread::instance().pushData(_message);
}

void Update_Thread::registeUpdate()
{
    bool r = upd_proxy_init();

    //Register IVP
    upd_proxy_register_callback( upd_subscribe_attr_state,      display_Msg_Update_IVP, nullptr );
    upd_proxy_register_callback( upd_subscribe_attr_load_rate, display_Msg_Update_IVP, nullptr );
    upd_proxy_register_callback( upd_subscribe_attr_update_no,   display_Msg_Update_IVP, nullptr );
    upd_proxy_register_callback( upd_subscribe_attr_update_rate,   display_Msg_Update_IVP, nullptr );
    upd_proxy_register_callback( upd_subscribe_attr_errno,      display_Msg_Update_IVP, nullptr );
    if(true != r){
        qWarning()<<"upd_proxy_init NG";
    }
    else{
        m_timerInit->stop();
    }
}

void Update_Thread::get_timeout100ms()
{
    if(g_count >= 0){
        g_count++;
        if(g_count >= 30){
            //3s
            g_count = -1;   //升级失败
            setMessageType(4);  // 消隐升级画面
            emit sendStopTimer100ms();
        }
    }
}

void Update_Thread::pushData(Message1 &changeMessage)
{
    QMutexLocker _locker(&mutex);
    m_messageList.push_back(changeMessage);
    _locker.unlock();
}

// Receive Msg
void Update_Thread::dataChange(Message1 &changeMessage)
{
    //qInfo()<<__FUNCTION__<<changeMessage.m_messageID<<changeMessage.m_messageData;
    switch (changeMessage.m_messageID) {
    case upd_subscribe_attr_state:
        upd_proxy_set_info(upd_publish_attr_res, qMax(0, changeMessage.m_messageData-1));
        break;
    case upd_subscribe_attr_load_rate:
        if(changeMessage.m_messageData == 101)  //防止上电显示升级
		{
			break;
        }
        setProcessStep(changeMessage.m_messageData & 0x7F); //111 1111

        if(changeMessage.m_messageData & 0x80){ //1000 0000
            setMessageType(5);//升级文件校验中
        }
        else{
            setMessageType(0);// 升级文件读取中
        }

        if((100 == (0x7F & changeMessage.m_messageData))
        && (HMI_UPDATE_FILE_NUM == m_updateFile)){
            setMessageType(6);  //升级校验成功
        }

        break;
    case upd_subscribe_attr_update_no:    // file Number
        m_updateFile = qMin(static_cast<int>(changeMessage.m_messageData), HMI_UPDATE_FILE_NUM);
        break;
    case upd_subscribe_attr_update_rate:    // Percentage
        if(changeMessage.m_messageData == 101)  //防止上电显示升级
		{
			break;
		}
        setMessageType(1);  //升级中… 请耐心等待，请勿断电
        setProcessStep(0x7F & changeMessage.m_messageData);  // 升级中，百分比
        if(m_updateFile == 0){
            setFileNum("");
        }else{
            setFileNum(QString::number(m_updateFile)+"/"+QString::number(HMI_UPDATE_FILE_NUM));
        }

        if((100 == (0x7F &changeMessage.m_messageData))
                && (HMI_UPDATE_FILE_NUM == m_updateFile)){
            setMessageType(2);  //升级成功！系统2秒后将自动重启
        }
        break;
    case upd_subscribe_attr_errno:
        if ( upd_sub_errno_val_0 == changeMessage.m_messageData ) {
            setMessageType(3);  //没有可用的升级文件
        } else{
            setMessageType(7);  //升级失败
            // 提示3Sec后消隐POP
            g_count = 0;
            emit sendStartTimer100ms();
        }
        break;
    default:
        break;
    }
}
