#include "hmibox.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>



HMIBox::HMIBox(QObject *parent) : QObject(parent)
{
    m_errorText = "";
    _enumEndFlag = "RpcMsgId";
}

void HMIBox::init()
{
    // parse
    parseInFile("PF_Common.h");

    autoMerge();    // 自动匹配 id ~ msg

    // 按照id排序

    std::sort(_parseHeadMsgList.begin(), _parseHeadMsgList.end(),
              [=](QVariant x, QVariant y){
        return x.toMap().value("idValue").toInt() < y.toMap().value("idValue").toInt();
    });

    // 更新
    emit updateData();
}

void HMIBox::newDBC(QVariantList list)
{
    // 根据list修改_parseHeadMsgList数据
    int len = _parseHeadMsgList.length();
    for(int i = 0; i < len; i++)
    {
        QVariantMap map = _parseHeadMsgList.at(i).toMap();
        QString structName = map.value("name").toString();

        bool isFind = false;

        foreach(QVariant a, list)
        {
            QVariantMap qmlMap = a.toMap();
            QString qmlStructName = qmlMap.value("name").toString();

            if(structName == qmlStructName)
            {
                map.insert("idName", qmlMap.value("idName"));
                map.insert("idValue", qmlMap.value("idValue"));
                isFind = true;
                break;
            }
        }
        if(isFind)
        {
            _parseHeadMsgList[i] = map; // 更新id
        }
        else{
            // id=-1，需要删除这个结构体
            map.insert("idName", "-1");
            map.insert("idValue", -1);
            _parseHeadMsgList[i] = map; // 更新id
        }
    }

    // 保存dbcdata
    QString dbcdata;
    for(int i = 0; i < len; i++)
    {
        QVariantMap map = _parseHeadMsgList.at(i).toMap();
        QString idName = map.value("idName").toString();
        int idValue = map.value("idValue").toInt();
        QString structName = map.value("name").toString();

        if(idName == "-1" || idValue == -1) continue;

        dbcdata += QString("%1 %2 %3:")
                .arg(idName)
                .arg(QString::number(idValue))
                .arg(structName);

        QVariantList msgList = map.value("msgList").toList();
        foreach(QVariant msg, msgList)
        {
            dbcdata += QString("%1 %2 ")
                    .arg(msg.toMap().value("name").toString())
                    .arg(msg.toMap().value("bits").toString());
        }

        dbcdata += "\n";
    }

    writeFile(dbcdata, "DBCData");

    // 保存dynamic_create.h
    QString data;

    data += "#ifndef DYNAMIC_CREATE_H\n";
    data += "#define DYNAMIC_CREATE_H\n\n";

    data += "#include <QByteArray>\n";
    data += "#include <QVariant>\n";
    data += "#include \"PF_Common.h\"\n\n";

    data += "static QByteArray changeToba(int id, QVariant data, int& len){\n";
    data += "    QVariantList list = data.toList();\n";
    data += "    QByteArray byteArray;\n\n";

    data += "    switch (id) {\n";

    for(int i = 0; i < len; i++)
    {
        QVariantMap map = _parseHeadMsgList.at(i).toMap();
        QString idName = map.value("idName").toString();
        int idValue = map.value("idName").toInt();
        QString structName = map.value("name").toString();

        if(idName == "-1" || idValue == -1) continue;

        data += QString("    case %1:\n").arg(idName);
        data += QString("        %1 msg%2;\n").arg(structName).arg(i);
        data += QString("        len = sizeof(msg%1);\n").arg(i);

        QVariantList msgList = map.value("msgList").toList();
        int k = 0;
        foreach(QVariant msg, msgList)
        {
            data += QString("        msg%1.Signals.%2 = list.at(%3).toMap().value(\"value\").toUInt();\n")
                    .arg(i).arg(msgList.at(k).toMap().value("name").toString()).arg(k);
            k++;
        }
        data += "\n";
        data += QString("        byteArray = QByteArray((const char*)&msg%1, len);\n").arg(i);
        data += "        break;\n";


    }

    data += "    }\n";
    data += "\n";
    data += "    return byteArray;\n";
    data += "}\n";

    data += "#endif // DYNAMIC_CREATE_H";


    writeFile(data, "dynamic_create.h");
    emit newFileFinished();

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

void HMIBox::process_line(QString line)
{
    //    qInfo()<<__FUNCTION__<<line;

    //解析id枚举内容
    if(line.contains("typedef enum") && _start_flag != _enumEndFlag){
        _start_flag = "enum"; // 开始解析 id
    }
    if(_start_flag == "enum" && line.contains("MSG_")){
        if(line.trimmed().startsWith("//")) return; // 注释的 id 需要跳过
        QString _line = line.split(",")[0];
        QString name;
        if(_line.contains("=")){
            //有值
            QStringList l = _line.split("=");
            name = QString(l.at(0)).trimmed();
            _value = QString(l.at(1)).toInt(nullptr, 16);
        }
        else{
            _value += 1;
            name = _line.trimmed();
        }
        QVariantMap m;
        m.insert("name", name);
        m.insert("idValue", _value);
        _nameToIdList.append(m);

    }
    if(_start_flag == "enum" && line.contains(_enumEndFlag)){
        _start_flag = _enumEndFlag;
    }


    //解析结构体内容
    if(line.contains("typedef union")){
        //start 结构体解析
        _start_flag = "union";
        _msg.clear();
        _msgList.clear();
    }

    if(_start_flag == "union" && line.contains("struct")){
        _start_flag = "struct";
    }
    else if(_start_flag == "struct" && line.contains("Type_")){
        _start_flag = "struct";
        //正则
         if(line.trimmed().startsWith("//")) return; // 注释的 结构体字段 需要跳过
        QString _line = line.replace("\t", " ").trimmed();
        QRegExp rx("Type_.* (.*);");
        rx.setMinimal(true);
        QString result = "";

        rx.indexIn(_line.trimmed());
        result = rx.cap(1);

        //qInfo()<<"正则struct"<<_line<<result;
        if(result.isEmpty()){
            qInfo()<<("正则struct解析失败:") << line;
            exit(0);
        }

        QString name, bits;
        if(result.contains(":")){
            name = QString(result.split(":")[0]).trimmed();
            bits = QString(result.split(":")[1]).trimmed();
        }
        else{
            name = result.trimmed();
            if(line.contains("Type_uHWord"))
                bits = "16";
            else if(line.contains("Type_uWord"))
                bits = "32";
            else if(line.contains("Type_uDWord"))
                bits = "64";
            else
                bits = "8";
        }

        QVariantMap m;
        m.insert("name", name);
        m.insert("bits", bits.toInt());
        //            m.insert("value", 0);
        _msgList.append(m);

    }
    else if(_start_flag == "struct" && line.contains("Signals")){
        _start_flag = "Signals";
    }
    else if(_start_flag == "struct" && line.contains("Outdata")){
        _start_flag = "Signals";
    }
    else if(_start_flag == "Signals" && (line.contains("msgType") || line.contains("IPK"))){
        _start_flag = "msgType";
        //end
        QString result;
        if (line.contains("//"))
        {
            result = line.split("//")[0];
        }
        result = line.replace("}", "").replace(";", "").trimmed();

        //如果有,取后者
        if(result.contains(",")){
            QStringList _rList = result.split(",");
            result = _rList.at(1);
        }

        if(result.isEmpty()){
            qInfo()<<("正则struct name解析失败:")<<line;
            exit(0);
        }

        result = result.trimmed();
        _msg.insert("idName", "-1");      // 未匹配 id
        _msg.insert("idValue", -1);      // 未匹配 id
        _msg.insert("name", result); // 结构体名
        _msg.insert("msgList", _msgList); // Signals 数组

        _parseHeadMsgList.append(_msg);
    }
}

void HMIBox::parseInFile(QString path)
{

    QFile file(path);
    QString fileData;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileData = "";
        qInfo()<<"readFile faile. "<<path;
        setErrorText("找不到文件或打不开文件;请把PF_Common.h放到程序同级目录");
        return;
    }
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        process_line(line);
    }
    file.close();
}

// 自动匹配 id ~ msg
void HMIBox::autoMerge()
{
    int len = _nameToIdList.length();
    for(int i = 0; i < len; i++)
    {
        QVariantMap map = _nameToIdList.at(i).toMap();
        QString name = map.value("name").toString();
        //        int id = map.value("id").toInt();

        // 把id名字切割后存储
        QStringList names = name.replace("MSG_", "")
                .replace("_ID", "").split("_");

        names.append(name.replace("MSG_", "").replace("_ID", ""));

        map.insert("names", names);
        _nameToIdList[i] = map;
    }

    len = _parseHeadMsgList.length();
    for(int i = 0; i < len; i++)
    {
        QVariantMap map = _parseHeadMsgList.at(i).toMap();
        QString name = map.value("name").toString();

        // 把结构体名字切割后存储
        QStringList names = name.replace("_c_", "")
                .replace("MSG_", "")
                .replace("_msgType", "")
                .replace("_IP", "").split("_");

        names.append(name.replace("_c_", "")
                     .replace("MSG_", "")
                     .replace("_msgType", "")
                     .replace("_IP", ""));
        map.insert("names", names);
        _parseHeadMsgList[i] = map;
    }

    // 计算权重,根据结构体名和id名的重合率
    for(int i = 0; i < len; i++)
    {
        QVariantMap map = _parseHeadMsgList.at(i).toMap();
        QVariantList names = map.value("names").toList();

        int lenid = _nameToIdList.length();

        QVariantList ids;   // {name, value, quanzhong}

        for(int j = 0; j < lenid; j++)
        {
            QVariantMap mapid = _nameToIdList.at(j).toMap();
            QVariantList namesid = mapid.value("names").toList();

            int quanzhong = 0;  // 权重

            for(int m = 0; m < names.length(); m++)
            {
                for(int n = 0; n < namesid.length(); n++)
                {
                    if(names.at(m).toString().length() > 1 &&
                            namesid.at(n).toString().length() > 1 &&
                            names.at(m) == namesid.at(n)) quanzhong++;
                }
            }
            QVariantMap m;
            m.insert("name", mapid.value("name"));
            m.insert("idValue", mapid.value("idValue"));
            m.insert("quanzhong", quanzhong);
            ids.append(m);
        }
        // 计算得到一共结构体名对应所有id的权重率，排序
        std::sort(ids.begin(), ids.end(), [=](QVariant x, QVariant y){
            return x.toMap().value("quanzhong").toInt() > y.toMap().value("quanzhong").toInt();
        });
        //        qInfo()<<"---------"<<ids;
        if ( ids.at(0).toMap().value("quanzhong").toInt() > 0 )
        {
            map.insert("idName", ids.at(0).toMap().value("name"));
            map.insert("idValue", ids.at(0).toMap().value("idValue"));
            _parseHeadMsgList[i] = map;
        }
    }
}

QString HMIBox::readFile(QString path)
{
    QFile file(path);
    QString fileData;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileData = "";
        qInfo()<<"找不到文件或打不开文件:"<<path;
        qInfo()<<"请把"<<path<<"放到程序同级目录";
        return fileData;
    }
    fileData = QString(file.readAll());
    file.close();

    return fileData;
}
