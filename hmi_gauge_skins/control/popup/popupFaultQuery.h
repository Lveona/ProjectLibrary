#ifndef POPUPFAULTQUERY_H
#define POPUPFAULTQUERY_H

#include <QObject>

class PopupFaultQuery: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    PopupFaultQuery(QObject* parent=0):QObject (parent){
        m_name = "";
    }
    PopupFaultQuery(QString name, QObject* parent=0):QObject (parent){
        m_name = name;
    }
    PopupFaultQuery(const PopupFaultQuery &pop, QObject* parent=0);

    PopupFaultQuery & operator =(const PopupFaultQuery&);
    QString name() { return m_name; }
    void setName(QString v) {
        if (m_name == v)
            return;

        m_name = v;
        emit nameChanged();
    }

signals:
    void nameChanged();
private:
    QString m_name;
};
#endif // POPUPFAULTQUERY_H
