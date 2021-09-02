/*
 * =====================================================================================
 *
 *       Filename:  Update_proxy.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/07/2018 13:33:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guoyw, guo_yw@neusoft.com
 *   Organization:  www.neusoft.com
 *
 * =====================================================================================
 */
#ifndef LIB_UPDATE_H
#define LIB_UPDATE_H
#ifdef __cplusplus
extern "C"
{
#endif

//#include <cls/cls_common.h>

#define UPDATE_FILE_TOTAL               4

#define UPD_PPS_ATTR_KEY_STATE          "UpdateState"
#define UPD_PPS_ATTR_KEY_LOAD_RATE      "LoadRate"
#define UPD_PPS_ATTR_KEY_UPDATE_NO      "UpdateNo"
#define UPD_PPS_ATTR_KEY_UPDATE_RATE    "UpdateRate"
#define UPD_PPS_ATTR_KEY_ERRNO          "ErrNo"
#define UPD_PPS_ATTR_KEY_RES            "Response"
#define UPD_PPS_ATTR_KEY_NOTIFY         "Notify"

#define UPD_PROXY_PPS_OBJ_DIR           "/var/pps/update/"
#define UPD_PROXY_PPS_SERVER_OBJ_NAME   "/var/pps/update/server?wait,delta"
#define UPD_PROXY_PPS_PROXY_OBJ_NAME    "/var/pps/update/proxy?wait,delta"

#define PPS_ATTR_INIT                   CLS_PPS_ATTR_TYPE_INT
#define PPS_BUFF_MAX                    CLS_PPS_BF_MAX
#define PPS_PROXY_MAX                   CLS_PROXY_MAX_NUMS
#define PPS_INVALID                     0xff

typedef struct
{
    int upd_errno;
    char *upd_errdisc;
} upd_errno_transf_st;

/**
 * subscribe define
 */
typedef enum
{
    upd_subscribe_attr_state = 0,
    upd_subscribe_attr_load_rate,
    upd_subscribe_attr_update_no,
    upd_subscribe_attr_update_rate,
    upd_subscribe_attr_errno,
    upd_subscribe_attr_max,
} upd_subscribe_attr;

/**
 * publish define
 */
typedef enum
{
    upd_publish_attr_res = 0,
    upd_publish_attr_notify,
    upd_publish_attr_max,
} upd_publish_attr;

/**
 * subscribe state value define
 */
typedef enum
{
    upd_sub_st_val_invalid = 0,
    upd_sub_st_val_init,
    upd_sub_st_val_loading,
    upd_sub_st_val_load_finish,
    upd_sub_st_val_preparing,
    upd_sub_st_val_preupdate,
    upd_sub_st_val_updating,
    upd_sub_st_val_finished,
    upd_sub_st_val_err,
    upd_sub_st_val_max,
} upd_sub_st_val;

/**
 * subscribe errno value define
 */
typedef enum
{
    upd_sub_errno_val_0 = 0,    /* no update file */
    upd_sub_errno_val_1,
    upd_sub_errno_val_2,
    upd_sub_errno_val_max,
} upd_sub_errno_val;

/**
 * publish response value define
 */
typedef enum
{
    upd_pub_res_value_inited = 0,
    upd_pub_res_value_loading,
    upd_pub_res_value_load_finish,
    upd_pub_res_value_preparing,
    upd_pub_res_value_preupdate,
    upd_pub_res_value_updating,
    upd_pub_res_value_finished,
    upd_pub_res_value_err,
    upd_pub_res_value_max,
} upd_pub_res_value;

typedef enum
{
    upd_pub_notify_value_loading = 0,
    upd_pub_notify_value_flash_mcu,
    upd_pub_notify_value_reboot,
    upd_pub_notify_value_max,
} upd_pub_notify_value;

typedef enum
{
    FUNC_RET_OK = 0,
    FUNC_RET_NG = 1,
    FUNC_RET_BUSY = 2,
} FUNC_RET;

typedef void (*upd_sub_messg_callback)(unsigned char attribute_key,unsigned char attribute_value,void *puser_data);


/*
 * ===  FUNCTION  ======================================================================
 *  Name        : PM_proxy_init
 *  Description : init proxy pps object prepare for communication
 *  Return      : bool
 *  Example     : null
 * =====================================================================================
 */
extern bool upd_proxy_init();

/*
 * ===  FUNCTION  ======================================================================
 *  Name        : upd_proxy_register_callback
 *  Description : register callback function of attribute key in object witch proxy subscribe
 *  Return      : bool
 *  Example     : upd_proxy_register_callback(PowerState,pcallback,pdata)
 *                callback parameter is attribute key and attribute value,witch callback
 *                function will be ivoked when pps server publish attribute of PowerState.
 *                the third parameter is a pointer that point to user data witch may be
 *                used in callbackfunciton.if not use,it can be NULL.
 * =====================================================================================
 */
extern bool upd_proxy_register_callback(unsigned char attribute_key,upd_sub_messg_callback pfun,void *puser_data);

/*
 * ===  FUNCTION  ======================================================================
 *  Name        : upd_proxy_set_info
 *  Description : proxy publish message to server.
 *  Return      : uint8_t type return code,witch list in enum pm_proxy_funret_em
 *  Example     : ret_code = upd_proxy_set_info(HMIResponse,hmi_response_standby);
 *                this ivoke will publish hmi_response_standby to HMIResponse attribute
 *                in object,if more than one thread set info at the same time,the ret_code
 *                while return FILE_BUSY,ivoker should be retry by itsself,so the function
 *                will not block long time
 * =====================================================================================
 */
extern FUNC_RET upd_proxy_set_info(unsigned char attribute_key,unsigned char attribute_value);

#ifdef __cplusplus
}
#endif

#endif


