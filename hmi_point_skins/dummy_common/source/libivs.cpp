#ifdef TEMPFUNC
#include "libivs.h"
#include <QtGlobal>
#include <QTime>
#include "PF_Common.h"
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

#include "../../bin/mainwindow.h"
#include <QQmlContext>

#include <QDebug>
#include <QDateTime>

static QString filePathpmOutput = "dataPM.txt";
static QString filePathInput = "common.json";


static QMap<unsigned char, QList<IVSMessageHandlerFunction>> mymap;

void SendMsg(unsigned char message_id, const unsigned char * msg, unsigned char data_len, void * pUserData)
{
    QList<IVSMessageHandlerFunction> pFunc = (QList<IVSMessageHandlerFunction>)mymap.value(message_id);
    foreach (IVSMessageHandlerFunction pf, pFunc) {
        if(pf)
        {
            pf(message_id, msg, data_len, pUserData);
        }
    }
}

bool ivs_client_init(void){
    return true;
}
void ivs_client_set_message_callback(unsigned char message_id, IVSMessageHandlerFunction pFunc, void * pUser_data){
    (void)pUser_data;
    QList<IVSMessageHandlerFunction> pFuncList = (QList<IVSMessageHandlerFunction>)mymap.value(message_id);
    if(!pFuncList.isEmpty())
    {
        pFuncList.append(pFunc);
        mymap.insert(message_id, pFuncList);
    }
    else{
        QList<IVSMessageHandlerFunction> pFuncList1;
        pFuncList1.append(pFunc);
        mymap.insert(message_id, pFuncList1);
    }
}
void ivs_client_set_hardwire_callback(IVS_POWERSTATUS_HARDWIRE hardwire_id, IVSHardwireHandlerFunction pFunc, void * pUser_data){
}
void ivs_client_send_request(IVSProxyRequest * pRequest, void * pUser_data){
}
void ivs_client_control_hardwire(IVS_FEEDBACK_HARDWIRE hardwire_id, bool level){
}


// hmibox3.0
HMIBox* HMIBox::m_instance = nullptr;
void HMIBox::init(QQuickView* v)
{
    m_view = v;
    // read dbc
    QString datas = readFile("../../hmi_point_skins/bin/DBCData");

    if(datas.isEmpty())
    {
        return;
    }

    readDBC(datas);

//    emit updateDatas();

//    m_view->rootContext()->setContextProperty("m_qml_datas", QVariant::fromValue(m_qml_datas));

    QTimer* timer = new QTimer;
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &HMIBox::timeout);
    timer->start();
}

void HMIBox::timeout()
{
    int len = m_qml_datas.length();
    for(int i = 0; i < len; i++)
    {
        QVariantMap map = m_qml_datas[i].toMap();
        if(map.value("isChecked") != 0)
        {
            // checked
            int message_id = map.value("idValue").toInt();
            int data_len;
            QByteArray msg = changeToba(message_id, map.value("signales").toList(), data_len);
            if(msg.isEmpty()) continue;
            SendMsg(message_id, (const unsigned char * )msg.constData(), data_len, nullptr);
        }
    }
}


void HMIBox::writeFile(QString data, QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning()<<"无法写入文件!!!"<<path;
        return;
    }
    QTextStream out(&file);
    out << data;
    out.flush();
    file.close();
}

QString HMIBox::readFile(QString path)
{
    QFile file(path);
    QString fileData;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileData = "";
        qInfo()<<"找不到文件或打不开文件:"<<path;
        return fileData;
    }
    fileData = QString(file.readAll());
    file.close();

    return fileData;
}

void HMIBox::readDBC(QString data)
{
    QStringList list = data.trimmed().split("\n");

    for(int i = 0; i< list.length(); ++i)
    {
//        MSG_MCU_2_ID 34 _c_MSG_MCU_2_msgType:MCU_Hand_brake_Pin6 8 1 MCU_Brake_fluid_Pin7 8 1 MCU_Charge_Indicator_Pin8 8 1 reserved 8 5
        QStringList list2 = QString(list.at(i)).split(":");
        QStringList listFront = QString(list2.at(0)).split(" ");
        QStringList listBack = QString(list2.at(1).trimmed()).split(" ");

        QVariantMap map;
        map.insert("idName", listFront.at(0));
        map.insert("idValue", QString(listFront.at(1)).toInt());
        map.insert("structName", listFront.at(2));
        map.insert("isChecked", 0);

        QVariantList customSignals;

        for(int j = 0; j < listBack.length(); j+=2)
        {
            QVariantMap csMap;
            csMap.insert("name", listBack.at(j));
            csMap.insert("bit", QString(listBack.at(j+1)).toInt());
            csMap.insert("value", 0);
            customSignals.append(csMap);
        }

        map.insert("signales", customSignals);

        m_qml_datas.append(map);
    }
}

void HMIBox::setSend(QString _idName, int checked)
{
    int ai = 0;
    foreach(QVariant a, m_qml_datas)
    {
        QVariantMap ma = a.toMap();
        if(ma.value("idName").toString() == _idName)
        {
            ma.insert("isChecked", checked);
            m_qml_datas[ai] = ma;
            break;
        }
        ai++;
    }
//    emit updateDatas();
}

void HMIBox::setPow(QString v)
{
    writeFile(QString("0:%1").arg(v), "../../hmi_point_skins/bin/dataPM.txt");
}

void HMIBox::setValue(QString _idName, QString _strucZiDuantName, QString value)
{
    qInfo()<<_idName<<_strucZiDuantName<<QString(value).toInt();

    int ai = 0;
    foreach(QVariant a, m_qml_datas)
    {
        QVariantMap ma = a.toMap();
        if(ma.value("idName").toString() == _idName)
        {
            QVariantList signales = ma.value("signales").toList();

            int bi = 0;
            foreach (QVariant b, signales) {
                QVariantMap mb = b.toMap();
                if(mb.value("name").toString() == _strucZiDuantName)
                {
                    mb.insert("value", QString(value).toInt());
                    signales[bi] = mb;
                    break;
                }
                bi++;
            }


            ma.insert("signales", signales);

            m_qml_datas[ai] = ma;

            break;
        }
        ai++;
    }
//    emit updateDatas();

}

#else
#endif
