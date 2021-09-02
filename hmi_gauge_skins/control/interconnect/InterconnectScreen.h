#ifndef InterconnectSCREEN_H
#define InterconnectSCREEN_H

#include <QObject>
#include "InterconnectControl.h"

class PhoneDataObject;
class MediaDataObject;
class InterconnectScreen;

class InterconnectScreen:  public CBaseScreen, public CSingleton<InterconnectScreen>
{
    Q_OBJECT
    friend class CSingleton<InterconnectScreen>;

//    Q_ENUMS(qmlBTStatus)
//    Q_ENUMS(qmlCallMode)
//    Q_ENUMS(qmlCallStatus)

    Q_ENUMS(qmlNaviState)
    Q_ENUMS(qmlNaviMapMode)
    Q_ENUMS(qmlNaviProjection)

    Q_PROPERTY(PhoneDataObject* phoneDataObject READ getPhoneDataObject WRITE setPhoneDataObject NOTIFY phoneDataObjectChanged)
    Q_PROPERTY(MediaDataObject* mediaDataObject READ getMediaDataObject WRITE setMediaDataObject NOTIFY mediaDataObjectChanged)
    Q_PROPERTY(QVariant volumeVisible READ volumeVisible WRITE setVolumeVisible NOTIFY volumeVisibleChanged)
    Q_PROPERTY(QVariant volumePercent READ volumePercent WRITE setVolumePercent NOTIFY volumePercentChanged)

    Q_PROPERTY(QVariant navigationStatus READ navigationStatus WRITE setNavigationStatus NOTIFY navigationStatusChanged)
    Q_PROPERTY(QVariant navigationMapMod READ navigationMapMod WRITE setNavigationMapMod NOTIFY navigationMapModChanged)
    Q_PROPERTY(QVariant navigationProjection READ navigationProjection WRITE setNavigationProjection NOTIFY navigationProjectionChanged)

public:
    InterconnectScreen();
    ~InterconnectScreen();

    enum qmlNaviState{
        CRUISE_STATE = 0,   //巡航状态
        NAVIGATION_STATE,   //导航状态
        ROAD_CROSSING_ENLARGED_STATE, //路口放大图
        NAVI_STATE_MAX
    };

    enum qmlNaviMapMode{
        SMALL_MAP = 0,  //小地图
        BIG_MAP,        //大地图
        AR_MAP,         //AR地图
        MAP_MODE_MAX
    };

    enum qmlNaviProjection{
        NAVI_NO_READY = 0,
        NAVI_READY,
        NAVI_PROJECTION_MAX
    };

    enum PROPERTYID_INTERCONNECT
    {
        PROPERTYID_INTERCONNECT_VOLUME_VISIBLE,
        PROPERTYID_INTERCONNECT_VOLUME_PERCENT,
    };
//    typedef enum {
//        DISCONNECTED = 0,
//        CONNECTED
//    }qmlBTStatus;

//    typedef enum {
//        CALL_NONE = 0,
//        CALL_TWO_CALL,
//        CALL_THREE_CALL
//    }qmlCallMode;

//    typedef enum {
//        DIALING = 0,
//        ALERTING,
//        INCOMING,
//        ACTIVE,
//        HOLDING,
//        CALL_MAX
//    } qmlCallStatus;
//    ivp_connect_status_enum qmlBTStatus;
//    callMode qmlCallMode;
//    ivp_call_status_enum qmlCallStatus;

    virtual void startControl();
    void createCtrl(QQuickView *view);
    typedef void ( InterconnectScreen::* FunctionParser )(QVariant value);

    PhoneDataObject* getPhoneDataObject() const
    {
        return m_phoneDataObject;
    }

    MediaDataObject* getMediaDataObject() const
    {
        return m_mediaDataObject;
    }

    QVariant volumeVisible() const
    {
        return m_volumeVisible;
    }

    QVariant volumePercent() const
    {
        return m_volumePercent;
    }

    QVariant navigationStatus() const
    {
        return m_navigationStatus;
    }

    QVariant navigationMapMod() const
    {
        return m_navigationMapMod;
    }

    QVariant navigationProjection() const
    {
        return m_navigationProjection;
    }

private:
    PhoneDataObject * m_phoneDataObject;

    MediaDataObject * m_mediaDataObject;

    QVariant m_volumeVisible;

    QVariant m_volumePercent;

    QVariant m_navigationStatus;

    QVariant m_navigationMapMod;

    QVariant m_navigationProjection;

public slots:
    void SetProperty(int, QVariant data);
    void SetProperty(PhoneData* data);
    void SetProperty(MediaData* data);

    void setPhoneDataObject(PhoneDataObject* phoneDataObject)
    {
        if (m_phoneDataObject == phoneDataObject)
            return;

        m_phoneDataObject = phoneDataObject;
        emit phoneDataObjectChanged(m_phoneDataObject);
    }
    void setMediaDataObject(MediaDataObject* mediaDataObject)
    {
        if (m_mediaDataObject == mediaDataObject)
            return;

        m_mediaDataObject = mediaDataObject;
        emit mediaDataObjectChanged(m_mediaDataObject);
    }

    void setVolumeVisible(QVariant volumeVisible)
    {
        if (m_volumeVisible == volumeVisible)
            return;

        m_volumeVisible = volumeVisible;
        emit volumeVisibleChanged(m_volumeVisible);
    }

    void setVolumePercent(QVariant volumePercent)
    {
        if (m_volumePercent == volumePercent)
            return;

        m_volumePercent = volumePercent;
        emit volumePercentChanged(m_volumePercent);
    }

    void setNavigationStatus(QVariant navigationStatus)
    {
        if (m_navigationStatus == navigationStatus)
            return;

        m_navigationStatus = navigationStatus;
        emit navigationStatusChanged(m_navigationStatus);
    }

    void setNavigationMapMod(QVariant navigationMapMod)
    {
        if (m_navigationMapMod == navigationMapMod)
            return;

        m_navigationMapMod = navigationMapMod;
        emit navigationMapModChanged(m_navigationMapMod);
    }

    void setNavigationProjection(QVariant navigationProjection)
    {
        if (m_navigationProjection == navigationProjection)
            return;

        m_navigationProjection = navigationProjection;
        emit navigationProjectionChanged(m_navigationProjection);
    }

signals:
    void phoneDataObjectChanged(PhoneDataObject* phoneDataObject);
    void mediaDataObjectChanged(MediaDataObject* mediaDataObject);
    void volumeVisibleChanged(QVariant volumeVisible);
    void volumePercentChanged(QVariant volumePercent);

    void navigationStatusChanged(QVariant navigationStatus);
    void navigationMapModChanged(QVariant navigationMapMod);
    void navigationProjectionChanged(QVariant navigationProjection);
};

class MediaDataObject : public QObject
{
    Q_OBJECT

    //转换后的显示状态 0 不显示 1 显示 2收音机(收音机参数等UI来了再说)
    Q_PROPERTY(QVariant mediaVisibleState READ mediaVisibleState WRITE setMediaVisibleState NOTIFY mediaVisibleStateChanged)
    //source经过转换过后的类型
    Q_PROPERTY(QVariant sourceType READ sourceType WRITE setSourceType NOTIFY sourceTypeChanged)
    //标题的ICon地址
    Q_PROPERTY(QVariant sourceIcon READ sourceIcon WRITE setSourceIcon NOTIFY sourceIconChanged)
    //标题名
    Q_PROPERTY(QVariant sourceTitle READ sourceTitle WRITE setSourceTitle NOTIFY sourceTitleChanged)
    //歌名项目名称
    Q_PROPERTY(QVariant title READ title WRITE setTitle NOTIFY titleChanged)
    //作者歌手名
    Q_PROPERTY(QVariant artist READ artist WRITE setArtist NOTIFY artistChanged)
    //播放状态
    Q_PROPERTY(QVariant playState READ playState WRITE setPlayState NOTIFY playStateChanged)
    //封面
    Q_PROPERTY(QVariant imageUri READ imageUri WRITE setImageUri NOTIFY imageUriChanged)
    //错误信息
    Q_PROPERTY(QVariant errorString READ errorString WRITE setErrorString NOTIFY errorStringChanged)
    //收音机频率
    Q_PROPERTY(QVariant frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)

    Q_ENUMS(qmlMediaPlayState)
    Q_ENUMS(qmlMediaVisibleState)
    Q_ENUMS(qmlSourceType)

    QVariant m_mediaVisibleState;

    QVariant m_sourceIcon;

    QVariant m_sourceTitle;

    QVariant m_title;

    QVariant m_artist;

    QVariant m_playState;

    QVariant m_imageUri;

    QVariant m_errorString;

    QVariant m_sourceType;

    QVariant m_frequency;

public:
    MediaDataObject(){
        qmlRegisterType<MediaDataObject>("qmlEnums", 1, 0, "MediaDataObjectEnums");

        m_mediaVisibleState = NONE;
        m_playState = STOPPED;
        m_sourceType = TYPE_NULL;
        m_sourceIcon = "";
        m_sourceTitle = "";
        m_title = "";
        m_artist = "";
        m_imageUri = "";
        m_errorString = "";
        m_frequency = "";
    }

    ~MediaDataObject() {}

    enum qmlMediaVisibleState {
        NONE,
        MEDIASHOW,
        RADIOSHOW,
    };

    enum qmlMediaPlayState {
        PLAYING = 0,//播放中 收音机收音中
        PAUSE, //暂停
        STOPPED,//停止
        SEARCHING,//收音机搜台中
        SEEKING, //  收音机上下切台
        STREAMING_LOADING,//流媒体加载中
        STREAMING_LOADED,//流媒体加载完毕
        PLAYERROR //错误   收音机没有
    };

    enum qmlSourceType {
        TYPE_NULL,//NULL
        TYPE_USB_AUDIO,//USB 音频
        TYPE_BT_AUDIO,//蓝牙电话
        TYPE_FM,//FM 俩收音机
        TYPE_AM,//AM 俩收音机
        TYPE_AI_RADIO_STATION,//AI电台
        TYPE_QQ_MUSIC,//QQ音乐
        TYPE_AUDIO_BOOK,//有声书   喜马拉雅听书
        TYPE_ONLINE_RADIO_STATION,//喜马拉雅 网络电台
        TYPE_NEWS,//新闻咨询
        MAXTYPE
    };

    QVariant mediaVisibleState() const
    {
        return m_mediaVisibleState;
    }

    QVariant sourceIcon() const
    {
        return m_sourceIcon;
    }

    QVariant sourceTitle() const
    {
        return m_sourceTitle;
    }

    QVariant title() const
    {
        return m_title;
    }

    QVariant artist() const
    {
        return m_artist;
    }

    QVariant playState() const
    {
        return m_playState;
    }

    QVariant imageUri() const
    {
        return m_imageUri;
    }

    QVariant errorString() const
    {
        return m_errorString;
    }

    QVariant sourceType() const
    {
        return m_sourceType;
    }

    QVariant frequency() const
    {
        return m_frequency;
    }

public slots:

    void setMediaVisibleState(QVariant mediaVisibleState)
    {
        if (m_mediaVisibleState == mediaVisibleState)
            return;

        m_mediaVisibleState = mediaVisibleState;
        emit mediaVisibleStateChanged(m_mediaVisibleState);
    }

    void setSourceIcon(QVariant sourceIcon)
    {
        if (m_sourceIcon == sourceIcon)
            return;

        m_sourceIcon = sourceIcon;
        emit sourceIconChanged(m_sourceIcon);
    }

    void setSourceTitle(QVariant sourceTitle)
    {
        if (m_sourceTitle == sourceTitle)
            return;

        m_sourceTitle = sourceTitle;
        emit sourceTitleChanged(m_sourceTitle);
    }

    void setTitle(QVariant title)
    {
        if (m_title == title)
            return;

        m_title = title;
        emit titleChanged(m_title);
    }

    void setArtist(QVariant artist)
    {
        if (m_artist == artist)
            return;

        m_artist = artist;
        emit artistChanged(m_artist);
    }

    void setPlayState(QVariant playState)
    {
        if (m_playState == playState)
            return;

        m_playState = playState;
        emit playStateChanged(m_playState);
    }

    void setImageUri(QVariant imageUri)
    {
        if (m_imageUri == imageUri)
            return;

        m_imageUri = imageUri;
        emit imageUriChanged(m_imageUri);
    }

    void setErrorString(QVariant errorString)
    {
        if (m_errorString == errorString)
            return;

        m_errorString = errorString;
        emit errorStringChanged(m_errorString);
    }

    void setSourceType(QVariant sourceType)
    {
        if (m_sourceType == sourceType)
            return;

        m_sourceType = sourceType;
        emit sourceTypeChanged(m_sourceType);
    }

    void setFrequency(QVariant frequency)
    {
        if (m_frequency == frequency)
            return;

        m_frequency = frequency;
        emit frequencyChanged(m_frequency);
    }

signals:
    void mediaVisibleStateChanged(QVariant mediaVisibleState);
    void sourceIconChanged(QVariant sourceIcon);
    void sourceTitleChanged(QVariant sourceTitle);
    void titleChanged(QVariant title);
    void artistChanged(QVariant artist);
    void playStateChanged(QVariant playState);
    void imageUriChanged(QVariant imageUri);
    void errorStringChanged(QVariant errorString);
    void sourceTypeChanged(QVariant sourceType);
    void frequencyChanged(QVariant frequency);
};

class PhoneDataObject: public QObject
{
    Q_OBJECT
    /*Q_PROPERTY*/
    Q_PROPERTY(QVariant phoneMode READ phoneMode WRITE setPhoneMode NOTIFY phoneModeChanged)
    Q_PROPERTY(QVariant phoneStatus READ phoneStatus WRITE setPhoneStatus NOTIFY phoneStatusChanged)
    Q_PROPERTY(QVariant displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QVariant phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QVariant elapseTime READ elapseTime WRITE setElapseTime NOTIFY elapseTimeChanged)
    Q_PROPERTY(QVariant headImage READ headImage WRITE setHeadImage NOTIFY headImageChanged)
    Q_ENUMS(qmlPhoneMode)
    Q_ENUMS(qmlPhoneStatus)

    QVariant m_phoneMode;

    QVariant m_phoneStatus;

    QVariant m_displayName;

    QVariant m_phoneNumber;

    QVariant m_elapseTime;

    QVariant m_headImage;

public:
    enum qmlPhoneMode {
        NONE,
        BTPHONE,
        ECALL,
        BCALL,
        CCALL,

        MAXPHONEMODE
    };

    enum qmlPhoneStatus {
        DIALING,//拨号中
        INCOMING,//来电中
        ACTIVE,//通话中
        HUNG_UP,//挂断

        MAXPHONESTATUS
    };

    PhoneDataObject(){
        qmlRegisterType<PhoneDataObject>("qmlEnums", 1, 0, "PhoneDataObjectEnums");

        m_phoneMode = NONE;
        m_phoneStatus = DIALING;
        m_displayName = "";
        m_phoneNumber = "";
        m_elapseTime = "";
        m_headImage = "";
    }


    QVariant phoneMode() const
    {
        return m_phoneMode;
    }

    QVariant phoneStatus() const
    {
        return m_phoneStatus;
    }

    QVariant displayName() const
    {
        return m_displayName;
    }

    QVariant phoneNumber() const
    {
        return m_phoneNumber;
    }

    QVariant elapseTime() const
    {
        return m_elapseTime;
    }

    QVariant headImage() const
    {
        return m_headImage;
    }

public slots:


    void setPhoneMode(QVariant phoneMode)
    {
        if (m_phoneMode == phoneMode)
            return;

        m_phoneMode = phoneMode;
        emit phoneModeChanged(m_phoneMode);
    }

    void setPhoneStatus(QVariant phoneStatus)
    {
        if (m_phoneStatus == phoneStatus)
            return;

        m_phoneStatus = phoneStatus;
        emit phoneStatusChanged(m_phoneStatus);
    }

    void setDisplayName(QVariant displayName)
    {
        if (m_displayName == displayName)
            return;

        m_displayName = displayName;
        emit displayNameChanged(m_displayName);
    }

    void setPhoneNumber(QVariant phoneNumber)
    {
        if (m_phoneNumber == phoneNumber)
            return;

        m_phoneNumber = phoneNumber;
        emit phoneNumberChanged(m_phoneNumber);
    }

    void setElapseTime(QVariant elapseTime)
    {
        if (m_elapseTime == elapseTime)
            return;

        m_elapseTime = elapseTime;
        emit elapseTimeChanged(m_elapseTime);
    }

    void setHeadImage(QVariant headImage)
    {
        if (m_headImage == headImage)
            return;

        m_headImage = headImage;
        emit headImageChanged(m_headImage);
    }

signals:

    void phoneModeChanged(QVariant phoneMode);
    void phoneStatusChanged(QVariant phoneStatus);
    void displayNameChanged(QVariant displayName);
    void phoneNumberChanged(QVariant phoneNumber);
    void elapseTimeChanged(QVariant elapseTime);
    void headImageChanged(QVariant headImage);
};

#endif // InterconnectSCREEN_H
