#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QJsonDocument>
#include "dynamic_create.h"
#include <QTimer>
#include <QQuickView>

#define MAX(a, b) a>b?a:b

typedef struct
{
    QString name;
    int bit;
    int value;
}CustomSignal;

typedef struct
{
    QString idName;
    int idValue;
    QString structName;
    int isChecked;
    QList<CustomSignal*> signales;
}CustomMsg;


class HMIBox : public QObject
{
    Q_OBJECT
public:    
    static HMIBox* instance()
    {
        if(m_instance == nullptr)
            m_instance = new HMIBox();
        return m_instance;
    }

    void init(QQuickView* v);

    QList<CustomMsg*> m_datas;

    QVariantList m_qml_datas;

    QVariantList m_qml_datas_search;

public slots:
    void timeout();
    QVariantList getQmlDatas() { return m_qml_datas_search; }

    void setValue(QString _idName, QString _strucZiDuantName, QString value);
    void setSend(QString _idName, int checked); // 发送状态

    void setPow(QString v);
    void setSearch(QString flag);

signals:
    void updateDatas();
    void updateDatasSearch();

protected:
    HMIBox(){}
    virtual ~HMIBox(){}

    QString readFile(QString path);
    void writeFile(QString data, QString path);

    void readDBC(QString data);

    void handleSearch();

private:
    static HMIBox* m_instance;
    QQuickView* m_view;
    QString _search;

};

#endif // MAINWINDOW_H
