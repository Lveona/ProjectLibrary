#ifndef HMIBOX_H
#define HMIBOX_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QVariant>

class HMIBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorText READ errorText WRITE setErrorText NOTIFY errorTextChange)

public:
    explicit HMIBox(QObject *parent = nullptr);


    QString errorText() const
    {
        return m_errorText;
    }

signals:
    void errorTextChange(QString errorText);
    void updateData();
    void newFileFinished();

public slots:
    void init();
    void newDBC(QVariantList list);
    QVariantList getHeadMsgList() { return _parseHeadMsgList; }
    QVariantList getIdList() { return _nameToIdList; }

    void setErrorText(QString errorText)
    {
        if (m_errorText == errorText)
            return;

        m_errorText = errorText;
        emit errorTextChange(m_errorText);
    }

private:
    QString readFile(QString path);
    void writeFile(QString data, QString path);
    QString m_errorText;

    void process_line(QString line);
    void parseInFile(QString path);
    void autoMerge();

    QVariantList _parseHeadMsgList;     //解析头文件得到结构体列表
    QVariantList _nameToIdList;              //结构体名映射id，提取enum的名称和对应的id值
    int _value;
    QString _enumEndFlag;
    QString _start_flag;
    QVariantMap _msg;
    QVariantList _msgList;

};

#endif // HMIBOX_H
