/*!
 * @file         InterconnectControl.h
 * @date         2019/04/23
 * @author       anliankang
 * @version      0.1
 * @brief        Source code for Media Info Lib
 */
/*********************************************************************************
 * Revision History                                                              *
 * No    Date        Revised by        Description                               *
 * --    ----        ----------        -----------                               *
 * 01    18/04/23    anliankang        New                                       *
 *********************************************************************************/

#ifndef InterconnectCONTROL_H
#define InterconnectCONTROL_H

#include <hmi_share.h>

#include<iostream>
#include<cstdlib>
#include<ctime>
#include <unordered_map>
#include <math.h>

#define PREFIX_DEBUG_MEDIAINFO "MediaInfo>>>>>>>>>>>>>>>>>>>"

class QMutex;
class MediaData;
class InterconnectControl;

/***********************************ENUM*****************************************/

enum PROPERTYID_INTERCONNECT
{
    PROPERTYID_INTERCONNECT_VOLUME_VISIBLE,
    PROPERTYID_INTERCONNECT_VOLUME_PERCENT,
    PROPERTYID_INTERCONNECT_NAVIGATION_STATUS,
    PROPERTYID_INTERCONNECT_NAVIGATION_MAPMODE,
    PROPERTYID_INTERCONNECT_NAVIGATION_PROJECTION
};

//enum PROPERTY_MEDIA_ID
//{
//    /*Radio*/
//    PROPERTY_ID_RADIOSATION,     //FM OR AM
//    /*Media*/
//    PROPERTY_ID_SONG_NAME,
//    PROPERTY_ID_ARTIST_NAME,
//    PROPERTY_ID_ALBUM_NAME,
//    PROPERTY_ID_ALBUM_WORK_PATH,
//    PROPERTY_ID_ELAPSED_TIME,
//    PROPERTY_ID_TOTAL_TIME,
//    PROPERTY_ID_UPDATE_TIME,
//    /*BTPhone*/
//    PROPERTY_ID_BT_CONNECT_STATUS,
//    PROPERTY_ID_CALL_MODE,
//    /*BTPhone two call*/
//    PROPERTY_ID_CALL_ONE_NAME,
//    PROPERTY_ID_CALL_ONE_NUM,
//    PROPERTY_ID_CALL_ONE_TIME,
//    /*BTPhone three call*/
//    PROPERTY_ID_CALL_TWO_NAME,
//    PROPERTY_ID_CALL_TWO_NUM,
//    PROPERTY_ID_CALL_TWO_TIME,

//};

//typedef enum {
//    CALL_NONE = 0,
//    CALL_TWO_CALL,
//    CALL_THREE_CALL
//}callMode;

class PhoneData
{
public:
    PhoneData(){clear();}
    ~PhoneData() {}

    void clear() {
        m_phoneMode = NONE;
        m_phoneStatus = DIALING;
        m_displayName.clear();
        m_phoneNumber.clear();
        m_elapseTime.clear();
        m_headImage.clear();
    }

    enum PhoneMode {
        NONE,
        BTPHONE,
        ECALL,
        BCALL,
        CCALL,

        MAXPHONEMODE
    };

    enum PhoneStatus {
        DIALING,//拨号中
        INCOMING,//来电中
        ACTIVE,//通话中
        HUNG_UP,//挂断

        MAXPHONESTATUS
    };

    PhoneMode m_phoneMode;
    PhoneStatus m_phoneStatus;
    QString m_displayName;
    QString m_phoneNumber;
    QString m_elapseTime;
    QString m_headImage;
};

class MediaData{
public:
    MediaData() { this->clear(); }
    ~MediaData() {}

    void clear() {
        m_mediaVisibleState = NONE;
        m_playState = STOPPED;
        m_sourceType = TYPE_NULL;
        m_sourceIcon.clear();
        m_sourceTitle.clear();
        m_title.clear();
        m_artist.clear();
        m_imageUri.clear();
        m_errorString.clear();
        m_frequency.clear();
    }

    enum MediaPlayState {
        PLAYING = 0,//播放中 收音机收音中
        PAUSE, //暂停
        STOPPED,//停止
        SEARCHING,//收音机搜台中
        SEEKING, //  收音机上下切台
        STREAMING_LOADING,//流媒体加载中
        STREAMING_LOADED,//流媒体加载完毕
        PLAYERROR //错误   收音机没有
    };

    enum MediaVisibleState {
        NONE, //没有不显示
        MEDIASHOW,//显示媒体
        RADIOSHOW,//显示收音机
    };

    enum SourceType {
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

    SourceType m_sourceType;

    MediaVisibleState m_mediaVisibleState;

    QString m_sourceIcon;

    QString m_sourceTitle;

    QString m_title;

    QString m_artist;

    MediaPlayState m_playState;

    QString m_imageUri;

    QString m_errorString;

    QString m_frequency;
};

class InterconnectControl: public CBaseControl, public CSingleton<InterconnectControl>
{
    Q_OBJECT
    friend class CSingleton<InterconnectControl>;

public:
    InterconnectControl();
    ~InterconnectControl();
    typedef void (InterconnectControl::* FunctionParser )( const char * data );
    typedef void (InterconnectControl::*InterconnectFunctionParser)(SingleMessage& msg);
    typedef void (InterconnectControl::*InterconnectVoidFunctionParser)();

    void handleIVPData(ivp_callback_id message_id,  void *pData);
    void func_IVP_CB_ID_PHONE_INFO(const char *data);
    void func_IVP_CB_ID_IMAGE_INFO(const char *data);
    void func_IVP_CB_ID_SOURCE_INFO(const char *data);
    void handleVolume(const char *pData);

    void handleNav(const char *pData);

    void handleImageInfo(QString& tagImageUri,const QString& defaultImage);
signals:
//    void PropertyChange(PROPERTY_MEDIA_ID,QVariant);
//    void notifyNaviState(bool state);       //是否有Navi
//    void notifyPhoneState(bool state);      //是否有phone
//	void sendToOtherProcess(QString name, QVariant value);
    void sendToOtherCtrl(QString name, QVariant value);
    void PropertyChange(PhoneData*);
    void PropertyChange(MediaData*);
public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void get_timeout500ms();
    void get_timeout100ms();
    void receiveDateFromOtherProcess(QString name, int value);

protected:
    void dataChange();
private:
    QMutex mutex;
    PhoneData* m_phoneData;
    MediaData* m_mediaData;
    HMICustomTimer* volumeTimer;
};

#endif // InterconnectCONTROL_H
