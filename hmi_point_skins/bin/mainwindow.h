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

public slots:
    void timeout();
    QVariantList getQmlDatas() { return m_qml_datas; }

    void setValue(QString _idName, QString _strucZiDuantName, QString value);
    void setSend(QString _idName, int checked);

    void setPow(QString v);

signals:
    void updateDatas();

protected:
    HMIBox(){}
    virtual ~HMIBox(){}

    QString readFile(QString path);
    void writeFile(QString data, QString path);

    void readDBC(QString data);

private:
    static HMIBox* m_instance;
    QQuickView* m_view;

};

#endif // MAINWINDOW_H
