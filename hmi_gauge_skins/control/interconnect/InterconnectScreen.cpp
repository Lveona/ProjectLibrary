#include "InterconnectScreen.h"
//2 导航互联
static QMap< quint32, InterconnectScreen::FunctionParser > tableScreen_Interconnect = {
    {PROPERTYID_INTERCONNECT_VOLUME_VISIBLE,       &InterconnectScreen::setVolumeVisible},
    {PROPERTYID_INTERCONNECT_VOLUME_PERCENT,       &InterconnectScreen::setVolumePercent},
    {PROPERTYID_INTERCONNECT_NAVIGATION_STATUS,   &InterconnectScreen::setNavigationStatus},
    {PROPERTYID_INTERCONNECT_NAVIGATION_MAPMODE, &InterconnectScreen::setNavigationMapMod},
    {PROPERTYID_INTERCONNECT_NAVIGATION_PROJECTION,&InterconnectScreen::setNavigationProjection}
};

//[0]
InterconnectScreen::InterconnectScreen()
{
    m_volumeVisible = false;
    m_volumePercent = 0;
    m_phoneDataObject = new PhoneDataObject();
    m_mediaDataObject = new MediaDataObject();

    m_navigationStatus = NAVI_STATE_MAX;//小地图状态
    m_navigationMapMod = SMALL_MAP;//小地图 常规模式
    m_navigationProjection = NAVI_NO_READY;//初始值没有准备好

    qmlRegisterType<InterconnectScreen>("qmlEnums", 1, 0, "InterconnectScreenEnums");
}


InterconnectScreen::~InterconnectScreen()
{
    delete m_phoneDataObject;
    delete m_mediaDataObject;
    delete InterconnectControl::instance();
}

void InterconnectScreen::startControl()
{
    //qRegisterMetaType<PROPERTY_MEDIA_ID>("PROPERTY_MEDIA_ID");
    connect(InterconnectControl::instance(), SIGNAL(PropertyChange(int , QVariant)), this, SLOT(SetProperty(int , QVariant)), Qt::QueuedConnection);

    qRegisterMetaType<PhoneData*>("PhoneData*");
    connect(InterconnectControl::instance(), SIGNAL(PropertyChange(PhoneData*)), this, SLOT(SetProperty(PhoneData*)), Qt::QueuedConnection);

    qRegisterMetaType<MediaData*>("MediaData*");
    connect(InterconnectControl::instance(), SIGNAL(PropertyChange(MediaData*)), this, SLOT(SetProperty(MediaData*)), Qt::QueuedConnection);
}

void InterconnectScreen::createCtrl(QQuickView *view)
{
    createAppControl(view->rootContext(), "InterconnectScreen");
    return;
}


void InterconnectScreen::SetProperty(int msgId, QVariant data)
{
    if(tableScreen_Interconnect.value(msgId)){
        (this->*(tableScreen_Interconnect.value(msgId)))(data);
    }else{
    }
}

void InterconnectScreen::SetProperty(PhoneData *data)
{
    m_phoneDataObject->setPhoneMode(data->m_phoneMode);
    m_phoneDataObject->setPhoneStatus(data->m_phoneStatus);
    m_phoneDataObject->setDisplayName(data->m_displayName);
    m_phoneDataObject->setPhoneNumber(data->m_phoneNumber);
    m_phoneDataObject->setElapseTime(data->m_elapseTime);
    m_phoneDataObject->setHeadImage(data->m_headImage);
}

void InterconnectScreen::SetProperty(MediaData *data)
{
    //5 多媒体
    m_mediaDataObject->setSourceType(data->m_sourceType);
    //转换后的显示状态 0 不显示 1 显示 2收音机(收音机参数等UI来了再说)
    m_mediaDataObject->setMediaVisibleState(data->m_mediaVisibleState);
    //标题的ICon地址
    //m_mediaDataObject->setSourceIcon(data->m_sourceIcon);
    //标题名
    //m_mediaDataObject->setSourceTitle(data->m_sourceTitle);
    //歌名项目名称
    m_mediaDataObject->setTitle(data->m_title);
    //作者歌手名
    m_mediaDataObject->setArtist(data->m_artist);
    //播放状态
    m_mediaDataObject->setPlayState(data->m_playState);
    //封面
    m_mediaDataObject->setImageUri(data->m_imageUri);
    //错误信息
    m_mediaDataObject->setErrorString(data->m_errorString);
    //收音机频率
    m_mediaDataObject->setFrequency(data->m_frequency);
}

