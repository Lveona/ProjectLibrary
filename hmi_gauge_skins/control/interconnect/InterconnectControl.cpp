#include "InterconnectControl.h"
//#define INEOS_ON
#include <QMutex>

#define FORMAT_UTF8(str) (QString::fromUtf8(str))

//ivp
//static IVP_PhoneInfo  _IVP_phone_info_Backup;
//static IVP_sourceInfo  _IVP_source_info_Backup;
//static IVP_imageInfo  _IVP_image_info_Backup;
//static QString strImageUri_backup="";
//static QString strSourceImageUri_backup="";
//QByteArray phoneImageUri;
//QByteArray phoneImageData;

static QByteArray imageInfoUri;
static QByteArray imageInfoData;

//static int g_hungUp_count = -1;
//static int g_powermode = 0;

static QString addZero(int value)
{
    if(value<10)
        return '0'+QString::number(value);
    return QString::number(value);
}

static int global_groupId;
static int global_curVolume;
static int global_mapmode = -1;
static PhoneData::PhoneStatus global_phoneStatus = PhoneData::MAXPHONESTATUS;

static QMap<RpcMsgValueId, InterconnectControl::InterconnectFunctionParser > InterconnectControlFunc = {

};

QList<InterconnectControl::InterconnectVoidFunctionParser> InterconnectVoidControlFunc {

};

static QMap< quint32, InterconnectControl::FunctionParser > tableCtrl_Interconnect_IVP = {
    {IVP_CB_ID_VOLUME_INFO,       &InterconnectControl::handleVolume},//音量条
    {IVP_CB_ID_NAVI_INFO,       &InterconnectControl::handleNav},//导航互联状态
    {IVP_CB_ID_SOURCE_INFO,   &InterconnectControl::func_IVP_CB_ID_SOURCE_INFO},//多媒体
    {IVP_CB_ID_IMAGE_INFO, &InterconnectControl::func_IVP_CB_ID_IMAGE_INFO},//图片二次验证
    {IVP_CB_ID_PHONE_INFO, &InterconnectControl::func_IVP_CB_ID_PHONE_INFO}//手机
};

InterconnectControl::InterconnectControl()
{
    //start(QThread::NormalPriority);
    m_phoneData = new PhoneData;
    m_mediaData = new MediaData;

    volumeTimer = new HMICustomTimer(20, false);
    connect(volumeTimer, &HMICustomTimer::timeout, this, [=](){
        setPropertyValue(PROPERTYID_INTERCONNECT_VOLUME_VISIBLE, false);
    });
}

InterconnectControl::~InterconnectControl()
{
    delete m_phoneData;
    delete m_mediaData;
//    requestInterruption();
//    quit();
//    wait(100);
}

void InterconnectControl::handleIVPData(ivp_callback_id message_id, void *pData)
{
    //7 IVP收发改写
    if( pData != nullptr ){
        if(tableCtrl_Interconnect_IVP.value(message_id)){
            (this->*(tableCtrl_Interconnect_IVP.value(message_id)))((char*)pData);
        }
    }
}

//volume
void InterconnectControl::handleVolume(const char *pData)
{
    IVP_volume _volume;
    memmove(&_volume, pData, sizeof(IVP_volume));
    if(_volume.groupId != global_groupId ||
            _volume.currentValue != global_curVolume){
        volumeTimer->reset();
        setPropertyValue(PROPERTYID_INTERCONNECT_VOLUME_VISIBLE, true);
        emit sendToOtherCtrl(HMI_MSGNAME_VOLUME,0);
        emit sendToOtherCtrl(HMI_MSGNAME_VOLUME,1);
    }
    float fl = (float)_volume.currentValue / _volume.maxValue;
    int percent = fl * 100;
    setPropertyValue(PROPERTYID_INTERCONNECT_VOLUME_PERCENT, percent);
    global_groupId = _volume.groupId;
    global_curVolume = _volume.currentValue;
}

void InterconnectControl::handleNav(const char *pData)
{
    // 1 导航互联
    IVP_navigationInfo _nav;
    memset(&_nav, 0, sizeof(IVP_navigationInfo));
    memmove(&_nav, pData, sizeof(IVP_navigationInfo));

    //qInfo() << "导航准备状态:    " << _nav.navigationProjection;
    //qInfo() << "导航准备地图模式:    " <<_nav.navigationMapMode;
    //qInfo() << "导航常规模式:"  << _nav.navigationStatus;

    //导航准备好了 还是没准备好
    setPropertyValue(PROPERTYID_INTERCONNECT_NAVIGATION_PROJECTION, _nav.navigationProjection);
    //小地图 大地图 AR地图
    setPropertyValue(PROPERTYID_INTERCONNECT_NAVIGATION_MAPMODE, _nav.navigationMapMode);
    //就是上面的小地图S1 常规模式下才有 不管直接发 反正盖死了 //巡航状态 //导航状态 //路口放大图
    setPropertyValue(PROPERTYID_INTERCONNECT_NAVIGATION_STATUS, _nav.navigationStatus);
    sendToOtherProcess(HMI_SHREMEMORY_CMD_NAVMAPMOD,_nav.navigationMapMode);

    if(global_mapmode != _nav.navigationMapMode){
        sendToOtherCtrl(HMI_MSGNAME_MAP_MODE, _nav.navigationMapMode);
        global_mapmode = _nav.navigationMapMode;
    }
}

void InterconnectControl::handleImageInfo(QString &tagImageUri, const QString &defaultImage)
{
    if(tagImageUri.isEmpty()){
        tagImageUri = defaultImage;
    }
    else{
        if(imageInfoUri  != tagImageUri){
            //替换前要确认imageUri是否相同，以免发生错误。
            tagImageUri = defaultImage;
        }
    }
}

//phone
void InterconnectControl::func_IVP_CB_ID_PHONE_INFO(const char *pData)
{
    //8 电话
    IVP_PhoneInfo _ivpdata;
    memset(&_ivpdata, 0, sizeof(IVP_PhoneInfo));
    memcpy(&_ivpdata, pData, sizeof(IVP_PhoneInfo));

    const IVP_callInfo *callInfo_one = &_ivpdata.callInfo[0];
//    const IVP_callInfo *callInfo_two = &_ivpdata.callInfo[1];


    //qInfo() << "通话类型:" << _ivpdata.notifyReason;
    //qInfo() << "通话状态:" << callInfo_one->callStatus;
    //qInfo() << "联系人或电话号码:" << callInfo_one->displayName;
    //qInfo() << "电话号码:" << callInfo_one->phoneNumber;
    //qInfo() << "多路通话数组长度:" << _ivpdata.callInfoNum;
    //qInfo() << "电话会议:" << callInfo_one->isMultiParty;

    if(_ivpdata.callInfoNum <= 0) {
        //啥也没有我显示个毛毛
        m_phoneData->clear();
        emit PropertyChange(m_phoneData);
        return ;
    }

    switch (_ivpdata.notifyReason) {
    case PHONE_STATUS: //蓝牙电话
        m_phoneData->m_phoneMode = PhoneData::BTPHONE;
        break;
    case ECALL_STATUS:
        //紧急通话 TBOX 都是固定的
        //因为TBOX UI 没有 这个文言数组之类的先不放到 QML了
        m_phoneData->m_phoneMode = PhoneData::ECALL;
        m_phoneData->m_displayName = "紧急通话";
        m_phoneData->m_phoneNumber.clear();
        break;
    case BCALL_STATUS: //道路救援
        m_phoneData->m_phoneMode = PhoneData::BCALL;
        m_phoneData->m_displayName = "道路救援";
        m_phoneData->m_phoneNumber.clear();
        break;
    case CCALL_STATUS: //人工客服
        m_phoneData->m_phoneMode = PhoneData::CCALL;
        m_phoneData->m_displayName = "人工客服";
        m_phoneData->m_phoneNumber.clear();
        break;
    default:
        m_phoneData->clear();
        emit PropertyChange(m_phoneData);
        return;
    }

    //通话状态
    switch (callInfo_one->callStatus) {
        case DIALING: //拨号中
            global_phoneStatus = m_phoneData->m_phoneStatus = PhoneData::DIALING;
            break;
        case INCOMING: //来电中
            global_phoneStatus = m_phoneData->m_phoneStatus = PhoneData::INCOMING;
            break;
        case ACTIVE: //通话中
        case HOLDING: //通话保持中
            //通话时间 秒
            m_phoneData->m_elapseTime =
                    addZero(callInfo_one->elapseTimeSeconds / 60)
                    .append(":")
                    .append(addZero(callInfo_one->elapseTimeSeconds % 60));
            global_phoneStatus = m_phoneData->m_phoneStatus = PhoneData::ACTIVE;
            break;
        case HUNG_UP: //挂断
            if(global_phoneStatus == PhoneData::HUNG_UP) return ;
            global_phoneStatus = m_phoneData->m_phoneStatus = PhoneData::HUNG_UP;
            break;
        case IDLE:  //其他状态
        case WAITING: //第三方通话等待中
        default:
            m_phoneData->clear();
            global_phoneStatus = PhoneData::MAXPHONESTATUS;
            emit PropertyChange(m_phoneData);
            return;
    }

    //只有蓝牙电话会有的
    if(m_phoneData->m_phoneMode == PhoneData::BTPHONE) {
        //有数据为多路通话  而多路通话的具体UI么有 仅仅是一个状态而已
        bool isMultiCall = _ivpdata.callInfoNum > 1 ? true : false;
        if (callInfo_one->isMultiParty == MULTIPARTY &&
                   isMultiCall) {
            m_phoneData->m_displayName = "电话会议 等2个会话";
            m_phoneData->m_phoneNumber.clear();
        } else if(callInfo_one->isMultiParty == MULTIPARTY) {
            m_phoneData->m_displayName = "电话会议";
            m_phoneData->m_phoneNumber.clear();
        } else if (isMultiCall) {
            m_phoneData->m_displayName = "等2个通话";
            m_phoneData->m_phoneNumber.clear();
        } else {
            if(callInfo_one->displayName != NULL && callInfo_one->displayName[0] != '\0'
                    && strlen(callInfo_one->displayName) != 0) {
                m_phoneData->m_displayName = FORMAT_UTF8(callInfo_one->displayName);
            } else {
                m_phoneData->m_displayName = FORMAT_UTF8(callInfo_one->phoneNumber);
            }
        }
    }
    //图片uri 客户哪里说是没做 暂时不切图片
    //handleImageInfo(m_phoneData->m_headImage = callInfo_one->imageUri,"icon_areaD_phone_head.png");

    emit PropertyChange(m_phoneData);
}

//Image
void InterconnectControl::func_IVP_CB_ID_IMAGE_INFO(const char *data)
{
    (void)data;
     IVP_imageInfo _ivpImageData;
     memset(&_ivpImageData, 0, sizeof(IVP_imageInfo));
     memmove(&_ivpImageData, data, sizeof(IVP_imageInfo));

     imageInfoUri = QByteArray(((IVP_imageInfo*)data)->imageUri);
     imageInfoData = "file:///"+QByteArray(((IVP_imageInfo*)data)->fileData);

     //qInfo() << "获取IMAGE_INFO" << imageInfoUri;
//       LOGPRINTVALUE("phoneImageData:",QString(phoneImageData));
//       LOGPRINTVALUE("phoneImageUri:",QString(phoneImageUri));
//      memcpy(&_IVP_image_info_Backup, data, sizeof(IVP_imageInfo));

}

//media
void InterconnectControl::func_IVP_CB_ID_SOURCE_INFO(const char *data)
{
    //4 媒体
    IVP_sourceInfo _ivpSourceData;
    memmove(&_ivpSourceData, data, sizeof(IVP_sourceInfo));

    //qInfo() << "多媒体类型: " << _ivpSourceData.sourceName;
    //qInfo() << "播放状态:   " << _ivpSourceData.playState;
    //qInfo() << "歌名节目名: " << m_mediaData->m_title;
    //qInfo() << "作者歌手名: " << m_mediaData->m_artist;

    switch (_ivpSourceData.sourceName) {
        case SOURCE_TYPE_USB1_AUDIO://USB 音频
        case SOURCE_TYPE_USB2_AUDIO://USB 音频
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_USB_AUDIO;
            break;
        case SOURCE_TYPE_BT_AUDIO://蓝牙
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_BT_AUDIO;
            break;
        case SOURCE_TYPE_FM://FM 俩收音机
            m_mediaData->m_mediaVisibleState = MediaData::RADIOSHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_FM;
            m_mediaData->m_frequency = QString::number(_ivpSourceData.frequency / 1000.0,'f',1); //收音机频率
            break;
        case SOURCE_TYPE_AM://AM 俩收音机
            m_mediaData->m_mediaVisibleState = MediaData::RADIOSHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_AM;
            m_mediaData->m_frequency = QString::number(_ivpSourceData.frequency); //收音机频率
            break;
        case SOURCE_TYPE_AI_RADIO_STATION://AI电台
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_AI_RADIO_STATION;
            break;
        case SOURCE_TYPE_QQ_MUSIC://QQ音乐
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_QQ_MUSIC;
            break;
        case SOURCE_TYPE_AUDIO_BOOK://有声书   喜马拉雅听书
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_AUDIO_BOOK;
            break;
        case SOURCE_TYPE_ONLINE_RADIO_STATION://喜马拉雅 网络电台
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_ONLINE_RADIO_STATION;
            break;
        case SOURCE_TYPE_NEWS://新闻咨询
            m_mediaData->m_mediaVisibleState = MediaData::MEDIASHOW;
            m_mediaData->m_sourceType = MediaData::TYPE_NEWS;
            break;
        case SOURCE_TYPE_NULL://NULL
    default:
        m_mediaData->clear();
        emit PropertyChange(m_mediaData);
        return ;
    }


    //播放状态
    switch (_ivpSourceData.playState) {
        case STATE_PLAYING: //播放
            m_mediaData->m_playState = MediaData::PLAYING;
            break;
        case STATE_PAUSE: //暂停
            m_mediaData->m_playState = MediaData::PAUSE;
            break;
        case STATE_SEARCHING://收音机搜台中
            m_mediaData->m_playState = MediaData::SEARCHING;
            break;
        case STATE_SEEKING: //收音机搜上下一台中
            m_mediaData->m_playState = MediaData::SEEKING;
            break;
        case STATE_STREAMING_LOADING://流媒体加载中
            m_mediaData->m_playState = MediaData::STREAMING_LOADING;
            break;
        case STATE_STREAMING_LOADED://流媒体加载完毕
            m_mediaData->m_playState = MediaData::STREAMING_LOADED;
            break;
    case STATE_ERROR://错误状态
        //非空是错误
            m_mediaData->m_playState = MediaData::PLAYERROR;
            m_mediaData->m_errorString = FORMAT_UTF8(_ivpSourceData.errorState);
        break;
    default:
        m_mediaData->clear();
        emit PropertyChange(m_mediaData);
        return;
    }

    m_mediaData->m_title = FORMAT_UTF8(_ivpSourceData.title);//歌名节目名
    m_mediaData->m_artist = FORMAT_UTF8(_ivpSourceData.artist); //作者歌手名

    //专辑图片
    handleImageInfo(m_mediaData->m_imageUri = _ivpSourceData.imageUri,"icon_areaD_music_cover1.png");

//    m_mediaData->m_sourceName = _ivpSourceData.sourceName;
//    m_mediaData->m_title = _ivpSourceData.title; //歌名节目名
//    m_mediaData->m_artist = _ivpSourceData.artist; //作者歌手名
//    m_mediaData->m_playState = _ivpSourceData.playState; //播放状态  == 2 时候需不要与收音机联动
//    m_mediaData->m_imageUri = _ivpSourceData.imageUri; //专辑图片

//    //缺UI
//    m_mediaData->m_loadState = _ivpSourceData.loadState;//加载状态 流媒体加载中加载完成
//    m_mediaData->m_scanState = _ivpSourceData.scanState; //本地收音机扫描状态
//    m_mediaData->m_elapseTimeMillis = _ivpSourceData.elapseTimeMillis;//当前播放时长
//    m_mediaData->m_totalTimeMillis = _ivpSourceData.totalTimeMillis; //总播放时长
//    //这部分暂时没用
//    m_mediaData->m_errorState = _ivpSourceData.errorState;//错误状态
//    m_mediaData->m_updateTimeMillis = _ivpSourceData.updateTimeMillis; //数据更新时的事件
//    m_mediaData->m_album = _ivpSourceData.album;  //专辑名 文档中给勾了 废弃

    emit PropertyChange(m_mediaData);
}

void InterconnectControl::dataChange()
{
//    QMapIterator<unsigned char, InterconnectControl::InterconnectFunctionParser> i(InterconnectControlFunc);
//    while (i.hasNext()) {
//        i.next();
//        SingleMessage messages;
//        if(getMsgValue(RpcMsgValueId(i.key()),messages))
//        {
//            (this->*(i.value()))(messages);
//        }
//    }

//    foreach (InterconnectControl::InterconnectVoidFunctionParser func, InterconnectVoidControlFunc) {
//        (this->*(func))();
//    }
}

void InterconnectControl::getFromOtherCtrl(QString message_key, QVariant message_value)
{
    (void)message_key;
    (void)message_value;
//    if ( HMI_MSGNAME_POWER_MODE == message_key ) {
//        g_powermode = message_value.toInt();
//    } else {
//        // Nothing
//    }
}

void InterconnectControl::get_timeout500ms()
{

}

void InterconnectControl::get_timeout100ms()
{
    volumeTimer->update();
//    if(g_hungUp_count >= 0){
//        g_hungUp_count++;
//        qInfo()<<"count"<<g_hungUp_count;
//        if(g_hungUp_count >= 10){
//            //暂定2s的信号检测时间
//            m_phoneData->m_isBluetooth = 0;
//            g_hungUp_count = -1;
//            emit PropertyChange(m_phoneData);
//            //hold off
//        }
//    }
}

void InterconnectControl::receiveDateFromOtherProcess(QString name, int value)
{
    Q_UNUSED(name)
    Q_UNUSED(value)
}
