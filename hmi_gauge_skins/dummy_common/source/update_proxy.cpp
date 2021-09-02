//#include "update_proxy.h"
//#include "libivs.h"
#include "update_proxy.h"

#ifdef TEMPFUNC
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
static QMap<unsigned char, upd_sub_messg_callback> mymap;

class MyTestUP: public QThread
{
public:
    MyTestUP(){}
    ~MyTestUP(){}
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

    void send( QString name, unsigned char attribute_value,QString puser_data)
    {
        upd_sub_messg_callback pFunc = nullptr;
        unsigned char attribute_key;

        if(name == "upd_subscribe_attr_state"){
            attribute_key = upd_subscribe_attr_state;
            pFunc = (upd_sub_messg_callback)mymap.value(upd_subscribe_attr_state);
        }
        else if(name == "upd_subscribe_attr_load_rate"){
            attribute_key = upd_subscribe_attr_load_rate;
            pFunc = (upd_sub_messg_callback)mymap.value(upd_subscribe_attr_load_rate);
        }
        else if(name == "upd_subscribe_attr_update_no"){
            attribute_key = upd_subscribe_attr_update_no;
            pFunc = (upd_sub_messg_callback)mymap.value(upd_subscribe_attr_update_no);
        }
        else if(name == "upd_subscribe_attr_update_rate"){
            attribute_key = upd_subscribe_attr_update_rate;
            pFunc = (upd_sub_messg_callback)mymap.value(upd_subscribe_attr_update_rate);
        }
        else if(name == "upd_subscribe_attr_errno"){
            attribute_key = upd_subscribe_attr_errno;
            pFunc = (upd_sub_messg_callback)mymap.value(upd_subscribe_attr_errno);
        }

        if(pFunc)
        {
            pFunc(attribute_key, attribute_value, (void *)puser_data.toUtf8().data());
        }

    }
    void run()
    {
        while(!isInterruptionRequested() )
        {
            data = readFile("../../HMIControlBox/bin/dataUP.txt");
//            qInfo()<<data;
            if(!data.isEmpty())
            {
                QStringList lines =  data.split("\n");

                int len = lines.length();

                for(int i=0; i<len; i++){

                    QStringList list =  lines.at(i).split(":");
                    if(list.length() == 2)
                    {
                        QString attribute_name = QString(list.at(0));
                        char attribute_value = QString(list.at(1)).toInt();
//                        qInfo()<<attribute_name<<attribute_key<<attribute_value;
                        send(attribute_name,(unsigned char) attribute_value, 0);
                    }
                }

            }
            msleep(1000);
        }
    }

};
static MyTestUP* myTestUP = new MyTestUP();

//#ifdef __cplusplus
//extern "C"
//{
//#endif

bool upd_proxy_init(){
//#ifdef HMIUPDATE
    myTestUP->start();
//#endif
    return true;}
bool upd_proxy_register_callback(unsigned char attribute_key,upd_sub_messg_callback pfun,void *puser_data){
    mymap.insert(attribute_key, pfun);
    (void)puser_data;
    return true;
}
//char upd_proxy_set_info(unsigned char attribute_key,unsigned char attribute_value)
//{char test = 5;return test;}
//bool upd_proxy_errno_transf(upd_notify_errno_em errno,char *err_disc)
//{return true;}
//void ivs_client_set_message_callback(unsigned char message_id, IVSMessageHandlerFunction pFunc, void * pUser_data){}
//void ivs_client_set_hardwire_callback(IVS_POWERSTATUS_HARDWIRE hardwire_id, IVSHardwireHandlerFunction pFunc, void * pUser_data){}
//void ivs_client_send_request(IVSProxyRequest * pRequest, void * pUser_data){}
//void ivs_client_control_hardwire(IVS_FEEDBACK_HARDWIRE hardwire_id, bool level){}
//bool ivs_client_init(void){}
//#ifdef __cplusplus
//}
//#endif
#endif

FUNC_RET upd_proxy_set_info(unsigned char attribute_key, unsigned char attribute_value)
{

}
