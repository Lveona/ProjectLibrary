#ifdef TEMPFUNC
#include "pm_proxy.h"
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
static QMap<unsigned char, PM_sub_messg_callback> mymap;
static QMap<unsigned char, PM_sub_messg_callback> mymap_lcd;

class MyTestPM: public QThread
{
public:
    MyTestPM(){}
    ~MyTestPM(){}
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
        PM_sub_messg_callback pFunc = (PM_sub_messg_callback)mymap.value(attribute_key);
        if(pFunc)
        {
            pFunc(attribute_key, attribute_value, pUserData);
        }
    }
    void sendlcd( unsigned char attribute_key, unsigned char attribute_value, int pUserData)
    {
        PM_sub_messg_callback pFunc = (PM_sub_messg_callback)mymap_lcd.value(attribute_key);
        if(pFunc)
        {
            pFunc(attribute_key, attribute_value, (void *)&pUserData);
        }
    }
    void run()
    {
        while(!isInterruptionRequested() )
        {
            data = readFile("../../HMIControlBox/bin/dataPM.txt");
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
            //lcd
            data = readFile("../../HMIControlBox/bin/dataPMLCD.txt");
            if(!data.isEmpty())
            {
                QStringList list =  data.split(":");
                if(list.length() == 3)
                {
                    char attribute_key = QString(list.at(0)).toInt();
                    char attribute_value = QString(list.at(1)).toInt();
                    int pUserData = QString(list.at(2)).toInt();
                    //防止PC调试时log一直刷新，取消发送
//                    sendlcd((unsigned char) attribute_key,(unsigned char) attribute_value, pUserData);
                }
            }
//            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//            unsigned char attribute_key = PowerState;
//            unsigned char attribute_value = pm_notify_operation;    //qrand() % pm_notify_state_max;

//            send((unsigned char) attribute_key,(unsigned char) attribute_value, nullptr);
            msleep(500);
        }
    }

};
static MyTestPM* myTestpm = new MyTestPM();

bool PM_proxy_init(){

    myTestpm->start();

    return true;
}

bool PM_proxy_register_callback(unsigned char attribute_key,PM_sub_messg_callback pfun,void *puser_data) {
    mymap.insert(attribute_key, pfun);
    (void)puser_data;
    return true;
}

bool PM_proxy_register_lcd_callback(unsigned char attribute_key, PM_sub_messg_callback pfun, void * puser_data){
    mymap_lcd.insert(attribute_key, pfun);
    (void)puser_data;
    return true;
}

bool PM_proxy_set_info(unsigned char attribute_key, unsigned char attribute_value)
{
    (void)attribute_key;
    (void)attribute_value;
    return true;
}
#else
#endif


