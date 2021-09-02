#ifndef LANGUGEMANAGE_H
#define LANGUGEMANAGE_H

#include <QTranslator>
#include <QGuiApplication>
#include "../../../fw/include/hmi_share.h"
class LangugeManage : public QObject,public CSingleton<LangugeManage>
{
    Q_OBJECT
public:
    explicit LangugeManage(QObject *parent = nullptr);
    ~LangugeManage();

//    static LangugeManage * instance()
//    {
//        if(m_instance1 == nullptr)
//            m_instance1 = new LangugeManage(nullptr);

//        return m_instance1;
//    }

    Q_PROPERTY(QString langugeChengeSW READ getLangugeChengeSW WRITE setLangugeChengeSW NOTIFY langugeChengeSWChanged)
    QString m_langugeChengeSW;
    void setLangugeChengeSW( QString currentLanguge );
    QString getLangugeChengeSW() {
        return m_langugeChengeSW;
    }

signals:
    void langugeChengeSWChanged();

public slots:
     Q_INVOKABLE void setLang(QString setLanguge);         // 语言发生变更

private:
//    static LangugeManage *m_instance1;
    QTranslator *m_translator;
};

#endif // LANGUGEMANAGE_H
