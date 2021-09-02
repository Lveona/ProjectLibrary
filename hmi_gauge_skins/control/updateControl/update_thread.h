#ifndef UPDATE_THREAD_H
#define UPDATE_THREAD_H

#include <QThread>

#define HMI_UPDATE_FILE_NUM 3

enum HMI_UPDATE_PROCESS_STATE{
  UPDATE_STS_ERROR = 0x00,
  UPDATE_STS_LOADFILE,
  UPDATE_STS_CHECKSUM,
  UPDATE_STS_UPDATE,
  UPDATE_STS_UPDATE_END,
};

typedef struct {
    unsigned char  m_messageID;
    unsigned char  m_messageData;
} Message1;

class QTimer;
#include <QMutex>
class Update_Thread : public QThread
{
    Q_OBJECT

public:
    Update_Thread(QObject* parent=nullptr);
    ~Update_Thread();
    void run();
    static Update_Thread& instance(){
        static Update_Thread instance;
        return instance;
    }

    Q_PROPERTY(int messageType READ getMessageType WRITE setMessageType NOTIFY messageTypeChanged)
    void setMessageType(int currentType);
    int getMessageType() const{
        return m_messageType;
    }

    Q_PROPERTY(int processStep READ getProcessStep WRITE setProcessStep NOTIFY processStepChanged)
    void setProcessStep(int v);
    int getProcessStep() const{
        return m_processStep;
    }

    Q_PROPERTY(QString fileNum READ fileNum WRITE setFileNum NOTIFY fileNumChanged)
    void setFileNum(QString v);
    QString fileNum() const{
        return m_fileNum;
    }

    void pushDataLib(unsigned char attribute_key, unsigned char attribute_value);

protected:
    QList< Message1 > m_messageList;

    void pushData(Message1 &changeMessage);
    void dataChange(Message1 &changeMessage);

private:
    HMI_UPDATE_PROCESS_STATE m_updateState;
    unsigned char m_updateFile;     // File No: 0,1,2,3,4,5
    int m_messageType  ;    // 0:[升级读取中…]
                            // 1:["升级中… 请耐心等待，请勿断电! "]
                            // 2:["升级成功！系统2秒后将自动重启！"]
                            // 3:[悬浮弹窗："没有可用的升级文件"]
                            // 4:消隐升级画面
                            // 5:升级校验中
                            // 6:升级校验成功
                            // 7:[悬浮弹窗："升级失败"]

    int m_processStep;
    QString m_fileNum;

    Update_Thread& operator =(Update_Thread const &);
    QMutex mutex;
    QTimer * m_timerInit;
    QTimer* timer100ms;

signals:
    void messageTypeChanged();
    void processStepChanged();
    void fileNumChanged();

    void sendStopTimer100ms();
    void sendStartTimer100ms();

public slots:
    void registeUpdate();
    void get_timeout100ms(void);

};

#endif // UPDATE_THREAD_H
