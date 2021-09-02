#ifdef TEMPFUNC
#include "log_proxy.h"
#include <QtGlobal>
#include <QTime>
//#include "PF_Common.h"
#include <qglobal.h>
#include <QDebug>
#include <QThread>
#include <QMap>
#include <QList>
#include <QDebug>
#include <QFile>
#else
#endif

#ifdef TEMPFUNC
static QMap<unsigned char, log_sub_messg_callback> mymap;

class MyTestLOG: public QThread
{
public:
    MyTestLOG(){}
    ~MyTestLOG(){}
    QString data;

    QString readFile(QString path)
    {
        QString dataTemp;
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            dataTemp = "";
            return dataTemp;
        }
        dataTemp = QString(file.readAll());
        file.close();
        return dataTemp;
    }

    void send( unsigned char attribute_key, unsigned char attribute_value, void * pUserData)
    {
        log_sub_messg_callback pFunc = (log_sub_messg_callback)mymap.value(attribute_key);
        if(pFunc)
        {
            pFunc(attribute_key, attribute_value, pUserData);
        }
    }
    void run()
    {
        while(!isInterruptionRequested() )
        {
            data = readFile("../../HMIControlBox/bin/dataLOG.txt");
            if(!data.isEmpty())
            {
                QStringList list =  data.split(":");
                if(list.length() == 2)
                {
                    char attribute_key = QString(list.at(0)).toInt();
                    char attribute_value = QString(list.at(1)).toInt();
                    send((unsigned char) attribute_key,(unsigned char) attribute_value, nullptr);
                }
            }
            msleep(5000);
        }
    }

};
static MyTestLOG* myTestlog = new MyTestLOG();

bool log_proxy_init(){
#ifdef HMIUPDATE
    myTestlog->start();
#endif
    return true;
}

bool log_proxy_register_callback(unsigned char attribute_key,log_sub_messg_callback pfun,void *puser_data) {
    mymap.insert(attribute_key, pfun);
    (void)puser_data;
    return true;
}

char log_proxy_set_info(unsigned char attribute_key,unsigned char attribute_value)
{
    (void)attribute_key;
    (void)attribute_value;
    return true;
}
#else
#endif


