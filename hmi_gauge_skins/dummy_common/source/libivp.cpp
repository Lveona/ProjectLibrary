#ifdef TEMPFUNC
#include "libivp.h"
#include <QtGlobal>
#include <QTime>
//#include "PF_Common.h"
#include <qglobal.h>
#include <QDebug>
#include <QThread>
#include <QMap>
#include <QList>
#include <QJsonDocument>
#include <QFile>
#else
#endif

#ifdef TEMPFUNC
static QMap<unsigned char, IVP_CallBackFunction> mymap;

class MyTestIVP: public QThread
{
public:
    MyTestIVP(){}
    ~MyTestIVP(){}
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

    void send(ivp_callback_id id, void *pData)
    {
        IVP_CallBackFunction pFunc = (IVP_CallBackFunction)mymap.value(id);
        if(pFunc)
        {
            pFunc(id, pData);
        }
    }
    void run()
    {
        while(!isInterruptionRequested() )
        {
            data = readFile("../../HMIControlBox/bin/dataIVP.txt");
            if(!data.isEmpty())
            {
                QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
                QVariantMap dataMap = document.toVariant().toMap();

                //IVP_CB_ID_VOLUME_INFO
                if(dataMap.value("IVP_CB_ID_VOLUME_INFO").isValid()){
                    QVariantMap _IVP_VOLUME_INFO_MAP = dataMap.value("IVP_CB_ID_VOLUME_INFO").toMap();
                    IVP_volume volumeInfo;
                    volumeInfo.currentValue = _IVP_VOLUME_INFO_MAP.value("currentValue").toInt();
                    volumeInfo.groupId = _IVP_VOLUME_INFO_MAP.value("groupId").toInt();
                    volumeInfo.maxValue = _IVP_VOLUME_INFO_MAP.value("maxValue").toInt();
                    send(IVP_CB_ID_VOLUME_INFO, (void *)&volumeInfo);
                }

                //IVP_CB_ID_PHONE_INFO
                if(dataMap.value("IVP_CB_ID_PHONE_INFO").isValid()){
                    QVariantMap _map_IVP_CB_ID_PHONE_INFO = dataMap.value("IVP_CB_ID_PHONE_INFO").toMap();

                    IVP_PhoneInfo _IVP_PhoneInfo;
                    _IVP_PhoneInfo.connectStatus = (ivp_connect_status_enum)_map_IVP_CB_ID_PHONE_INFO.value("connectStatus").toInt();
                    _IVP_PhoneInfo.notifyReason = (ivp_phone_notireason_enum)_map_IVP_CB_ID_PHONE_INFO.value("notifyReason").toInt();
                    _IVP_PhoneInfo.callInfoNum = _map_IVP_CB_ID_PHONE_INFO.value("callInfoNum").toInt();
                    QVariantList _list_callInfo = _map_IVP_CB_ID_PHONE_INFO.value("callInfo").toList();
                    QList<QByteArray> bl_phoneNum;
                    QList<QByteArray> bl_displayName;
                    QList<QByteArray> bl_imageUri;
                    IVP_callInfo _IVP_callInfo[2];

                    for(int i=0; i<_list_callInfo.length(); i++){
                       _IVP_callInfo[i].callStatus = (ivp_call_status_enum)_list_callInfo.at(i).toMap().value("callStatus").toInt();
                        QString phoneNum = _list_callInfo.at(i).toMap().value("phoneNumber").toString();
                        QString displayName = _list_callInfo.at(i).toMap().value("displayName").toString();
                        QString imageUri = _list_callInfo.at(i).toMap().value("imageUri").toString();
                        _IVP_callInfo[i].elapseTimeSeconds = _list_callInfo.at(i).toMap().value("elapseTimeSeconds").toLongLong();

                        bl_phoneNum.append(QByteArray(phoneNum.toUtf8()));
                        bl_displayName.append(QByteArray(displayName.toUtf8()));
                        bl_imageUri.append(QByteArray(imageUri.toUtf8()));

                        if(phoneNum.isEmpty()){
                            _IVP_callInfo[i].phoneNumber = nullptr;
                        }
                        else{
                            _IVP_callInfo[i].phoneNumber = (char*)(bl_phoneNum.at(i).data());

                        }
                        _IVP_callInfo[i].displayName = (char*)(bl_displayName.at(i).data());
                        _IVP_callInfo[i].imageUri = (char*)(bl_imageUri.at(i).data());

                        _IVP_PhoneInfo.callInfo[i] = _IVP_callInfo[i];
                    }
//                     qInfo()<<"+++++++++++++++++++"<<_IVP_callInfo[0].phoneNumber;
                     send(IVP_CB_ID_PHONE_INFO, (void *)&_IVP_PhoneInfo);
                }



                //IVP_imageInfo
                if(dataMap.value("IVP_imageInfo").isValid()){
                    QVariantMap _map_IVP_imageInfo = dataMap.value("IVP_imageInfo").toMap();
                    IVP_imageInfo _IVP_imageInfo;
                    QByteArray imageUriBy = _map_IVP_imageInfo.value("imageUri").toString().toUtf8();
                    QByteArray imageTypeBy = _map_IVP_imageInfo.value("imageTyp").toString().toUtf8();
                    QByteArray transTypeBy = _map_IVP_imageInfo.value("transType").toString().toUtf8();
                    QByteArray fileNameBy = _map_IVP_imageInfo.value("fileName").toString().toUtf8();
                    QByteArray fileDataBy = _map_IVP_imageInfo.value("fileData").toString().toUtf8();
                    _IVP_imageInfo.imageType    =(char*)imageTypeBy.data();
                    _IVP_imageInfo.transType    =(char*)transTypeBy.data();
                    _IVP_imageInfo.fileName     = (char*)fileNameBy.data();
                    _IVP_imageInfo.fileData     = (char*)fileDataBy.data();
                    _IVP_imageInfo.imageUri     =(char*)imageUriBy.data();

                    send(IVP_CB_ID_IMAGE_INFO, (void *)&_IVP_imageInfo);
                }


                //IVP_sourceInfo
                if(dataMap.value("IVP_sourceInfo").isValid()){
                    QVariantMap _map_IVP_sourceInfo = dataMap.value("IVP_sourceInfo").toMap();
                    IVP_sourceInfo _IVP_sourceInfo;
                    _IVP_sourceInfo.sourceName = (ivp_cur_source_enum)_map_IVP_sourceInfo.value("sourceName").toInt();
                    _IVP_sourceInfo.playState = (ivp_play_state_enum)_map_IVP_sourceInfo.value("playState").toInt();
                    _IVP_sourceInfo.frequency = _map_IVP_sourceInfo.value("frequency").toInt();
                    _IVP_sourceInfo.elapseTimeMillis = _map_IVP_sourceInfo.value("elapseTimeMillis").toInt();
                    _IVP_sourceInfo.totalTimeMillis = _map_IVP_sourceInfo.value("totalTimeMillis").toInt();
                    _IVP_sourceInfo.updateTimeMillis = _map_IVP_sourceInfo.value("updateTimeMillis").toLongLong();

                    QByteArray titleBy = _map_IVP_sourceInfo.value("title").toString().toUtf8();
                    QByteArray artistBy = _map_IVP_sourceInfo.value("artist").toString().toUtf8();
                    QByteArray albumBy = _map_IVP_sourceInfo.value("album").toString().toUtf8();
                    QByteArray mediaImageUriBy = _map_IVP_sourceInfo.value("imageUri").toString().toUtf8();

                    _IVP_sourceInfo.title = (char*)titleBy.data();
                    _IVP_sourceInfo.artist = (char*)artistBy.data();
                    _IVP_sourceInfo.album = (char*)albumBy.data();
                    _IVP_sourceInfo.imageUri = (char*)mediaImageUriBy.data();

                    send(IVP_CB_ID_SOURCE_INFO,(void *)&_IVP_sourceInfo);
                }

                //IVP_navigationInfo 导航
                if(dataMap.value("IVP_navigationInfo").isValid()) {
                    QVariantMap _map_IVP_navigationInfo = dataMap.value("IVP_navigationInfo").toMap();

                    IVP_navigationInfo _IVP_navigationInfo;
                    _IVP_navigationInfo.navigationStatus
                            = (ivp_navi_state_enum)_map_IVP_navigationInfo.value("navigationStatus").toInt();
                    _IVP_navigationInfo.navigationMapMode
                            = (ivp_mapmode_enum)_map_IVP_navigationInfo.value("navigationMapMode").toInt();
                    _IVP_navigationInfo.navigationProjection
                            = (ivp_navi_projection_enum)_map_IVP_navigationInfo.value("navigationProjection").toInt();

                    send(IVP_CB_ID_NAVI_INFO,(void *)&_IVP_navigationInfo);
                }



            }
            msleep(500);
        }
    }

};
static MyTestIVP* myTestIVP = new MyTestIVP();


int libivp_connect(void){
#ifdef HMIBOX
    myTestIVP->start();
#endif
    return 0;
}
void libivp_Set_callback(ivp_callback_id id, IVP_CallBackFunction pFunc){
    mymap.insert(id, pFunc);
    Q_UNUSED(id);
    Q_UNUSED(pFunc);
}


void libivp_set_navi_state(ivp_navi_status state)
{
    Q_UNUSED(state);
}

void libivp_send_query_dial(ivp_callback_id  id){
    Q_UNUSED(id);
}

void libivp_send_operate_dial(ivp_callback_id  id, char* dail_id){
    Q_UNUSED(id);
    Q_UNUSED(dail_id);
}

void libivp_send_request(ivp_callback_id  Request){
    Q_UNUSED(Request);
}

void libivp_Notify_Update_status(char* status, char *version){
    Q_UNUSED(status);
    Q_UNUSED(version);
}

#else
#endif

