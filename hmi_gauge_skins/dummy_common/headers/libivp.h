/*
 * Copyright (C) 2016-2017 Neusoft, Inc.
 * All Rights Reserved.
 *
 * The following programs are the sole property of Neusoft Inc.,
 * and contain its proprietary and confidential information.
 */
/* --------------------------------------------------------------------------*/
/**
* @file libivp.h
*/
/* ----------------------------------------------------------------------------*/
#ifndef __LIBIVP_H__
#define __LIBIVP_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    PLAY = 0,
    PAUSE,
    SWITCH
} ivp_navi_status;

typedef enum
{
    AR_INVISIBLE = 0,
    AR_VISIBLE,
} ivp_navi_show;

typedef enum
{
    IVP_CONNECT_OK = 0,
    IVP_CONNECT_NG
} ivp_connect_status;

typedef enum {
    SOURCE_TYPE_LOCAL_AUDIO = 0,
    SOURCE_TYPE_USB1_AUDIO,
    SOURCE_TYPE_USB2_AUDIO,
    SOURCE_TYPE_BT_AUDIO,
    SOURCE_TYPE_ONLINE_MUSIC,
    SOURCE_TYPE_ONLINE_RADIO,
    //SOURCE_TYPE_AUDIO_BOOK,
    SOURCE_TYPE_FM,
    SOURCE_TYPE_AM,
    SOURCE_TYPE_AI_RADIO_STATION,
    SOURCE_TYPE_QQ_MUSIC,
    SOURCE_TYPE_AUDIO_BOOK,
    SOURCE_TYPE_ONLINE_RADIO_STATION,
    SOURCE_TYPE_NEWS,
    SOURCE_TYPE_OTHER,
    SOURCE_TYPE_NULL = 20,
    SOURCE_TYPE_MAX         /* 21 */
} ivp_cur_source_enum;

typedef enum {
    STATE_PLAYING = 0,
    STATE_PAUSE,
    STATE_SEARCHING,               //扫描搜台中
    STATE_SEEKING,                 //收音机搜上/下一台中
    STATE_STREAMING_LOADING,       //流媒体加载中
    STATE_STREAMING_LOADED,        //流媒体加载完成
    STATE_ERROR,
    PLAY_STATE_MAX
} ivp_play_state_enum;


typedef enum {
    DISCONNECTED = 0,
    CONNECTED
}ivp_connect_status_enum;

typedef enum {
    DRIVER_SCREEN_VER = 0,
    PASSENGER_SCREEN_VER,
    CLUSTER_SCREEN_VER,

    SCREEN_VER_MAX
}ivp_screen_ver;

typedef enum
{
    IVP_CB_ID_SOURCE_INFO = 0,
    IVP_CB_ID_IMAGE_INFO,
    IVP_CB_ID_PHONE_INFO,
    IVP_CB_ID_CALLS_INFO,
    IVP_CB_ID_COLLECS_INFO,
    IVP_CB_ID_VOLUME_INFO,
    IVP_CB_ID_NAVI_INFO,
    IVP_CB_ID_UPDATE,
    IVP_CB_ID_LOG,
    IVP_CB_ID_AR,

    IVP_CB_ID_UNCONNECT,

    //add by chenjd begin
    IVP_CB_ID_RECONNECT,
    //add by chenjd end

    IVP_CB_ID_LCD_UPDATE,

    IVP_CB_ID_SCREEN_VER,
    IVP_CB_ID_MAX
} ivp_callback_id;

typedef enum {
    DIALING = 0,
    ALERTING,
    INCOMING,
    ACTIVE,
    HOLDING,
    HUNG_UP,
    IDLE,
    WAITING,
    CALL_MAX
} ivp_call_status_enum;

typedef enum {
    HISTORIES = 0,
    COLLECTIONS,
    PHONE_STATUS,
    ECALL_STATUS,   //Tbox-eCall
    BCALL_STATUS,   //Tbox-BCall
    CCALL_STATUS,   //Tbox-CCall

    REA_MAX
}ivp_phone_notireason_enum;

typedef enum {
    INCOMING_TYPE = 0,
    OUTGOING_TYPE,
    MISSED_TYPE,
    REJECTED_TYPE,
    BLOCKED_TYPE,
    CALLS_TYPE_MAX
}ivp_calls_type_enum;

typedef enum {
    NO_MULTIPARTY = 0,
    MULTIPARTY,

    MULTIPARTY_MAX
}ivp_multiparty_enum;

typedef enum {
    NO_MULTICALL = 0,
    MULTICALL,

    MULTICALL_MAX
}ivp_multicall_enum;

typedef enum {
    CRUISE_STATE = 0,   //巡航状态
    NAVIGATION_STATE,   //导航状态
    ROAD_CROSSING_ENLARGED_STATE, //路口放大图

    NAVI_STATE_MAX
}ivp_navi_state_enum;

typedef enum {
    SMALL_MAP = 0,  //小地图
    BIG_MAP,        //大地图
    AR_MAP,         //AR地图

    MAP_MODE_MAX
}ivp_mapmode_enum;

typedef enum {
    NAVI_NONE = 0,
    NAVI_READY,

    NAVI_PROJECTION_MAX
}ivp_navi_projection_enum;


typedef void (*IVP_CallBackFunction)(ivp_callback_id id, void *pData);

#define  IVP_CALLBCAK_MAX 3
typedef struct
{
    ivp_callback_id id;
    IVP_CallBackFunction handle[IVP_CALLBCAK_MAX];
} Ivp_Id2Callback_st;

typedef struct {
    ivp_cur_source_enum  sourceName;
    int frequency;
    char * title;
    char * artist;
    char * album;
    long long elapseTimeMillis;
    long long totalTimeMillis;
    long long updateTimeMillis;
    ivp_play_state_enum playState;
    char * errorState;
    char * imageUri;
} IVP_sourceInfo;

typedef struct{
    char *imageType;
    char *transType;
    char *fileName;
    char *fileData;
    char *imageUri;
}IVP_imageInfo;

typedef struct{
    ivp_call_status_enum callStatus;
    ivp_multiparty_enum isMultiParty;
    char *displayName;
    char *phoneNumber;
    long long elapseTimeSeconds;
    char *imageUri;
}IVP_callInfo;

typedef struct{
    ivp_navi_state_enum navigationStatus;
    ivp_mapmode_enum navigationMapMode;
    ivp_navi_projection_enum navigationProjection;
}IVP_navigationInfo;

typedef struct{
    ivp_connect_status_enum connectStatus;
    ivp_phone_notireason_enum notifyReason;
    IVP_callInfo callInfo[2];
    int callInfoNum;
}IVP_PhoneInfo;

typedef struct{
    char *id;
    ivp_calls_type_enum type;
    char *displayName;
    char *number;
    int count;
    long long dateTimeMillis;
}IVP_calls;

typedef struct{
    long long currentTimeMillis;
    IVP_calls calls[60];
}IVP_callLogs;

typedef struct{
    char *id;
    char *displayName;
}IVP_collections;

typedef struct{
    int groupId;
    int currentValue;
    int maxValue;
}IVP_volume;

/*
 *  Name:  libivp_connect
 *  Description:  Request ivplib(client) to connect ivp.
 *	Return:	IVP_CONNECT_OK Connect success
 *			IVP_CONNECT_NG Connect fail  please retry until Connection success
 */
int libivp_connect(void);

/* request ivplib(client) to set callback. */
void libivp_Set_callback(ivp_callback_id id, IVP_CallBackFunction pFunc);

void libivp_send_request(ivp_callback_id id);

/* HMI change the state of navi. PLAY, PAUSE or SWITCH. */
void libivp_set_navi_state(ivp_navi_status state);

/* HMI query the calls or collections */
void libivp_send_query_dial(ivp_callback_id id);

/* HMI dial one of the id of calls or collections */
void libivp_send_operate_dial(ivp_callback_id id, char *dial_id);

/* UPDATE transfer the progress of updating, with the updating status and SOC version */
void libivp_Notify_Update_status(char* status, char *version);

/* UPDATE transfer the progress of updating, with the lcd updating status */
void libivp_Notify_Lcd_Update_status(char* status);

/* LOG transfer the progress of cluster log, with the trans status */
void libivp_notify_log_status(char* status);

/* Notify Screen version */
void libivp_Notify_Screen_Version(ivp_screen_ver screenVer, char *version);
#ifdef __cplusplus
}
#endif

#endif
