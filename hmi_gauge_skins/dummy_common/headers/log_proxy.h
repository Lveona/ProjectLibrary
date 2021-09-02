#ifndef _LOG_PROXY_H_
#define _LOG_PROXY_H_
#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************************************/
/*							Include File Section											*/
/********************************************************************************************/


/********************************************************************************************/
/*							Macro Definition Section										*/
/********************************************************************************************/
#define LOG_PROXY_MAX_NUMS       (unsigned char)0x01   /*in one process ,registre max nums*/


typedef void (*log_sub_messg_callback)(unsigned char attribute_key,unsigned char attribute_value,void *puser_data);

/********************************************************************************************/
/*							structure Type Definition Section								*/
/********************************************************************************************/

/********************************************************************************************/
/*							Enumeration Type Definition Section								*/
/********************************************************************************************/
typedef enum{
	log_tcp_connect_sta,
	log_file_trans_pro,
	log_file_trans_errno,

	log_server_attr_max,
}LogServerAttr;

typedef enum{
	log_proxy_notify,

	log_proxy_attr_max,
}LogProxyAttr;

/* value of key log_tcp_connect_sta */
typedef enum{
	log_tcp_connect_ok,
	log_tcp_connect_ng,

	log_tcp_connect_sta_max,
}LogTcpConSta;

/* value of key log_file_trans_errno */
typedef enum{
    log_trans_ok,
	log_trans_err,
	
	log_trans_err_max,
}LogTransErrNo;

/* value of key log_proxy_notify */
typedef enum{
	log_trans_file_req,

	log_proxy_notify_max,
}LogProxyNotify;

//defined in pm_proxy.h
#if 0
/*
**function return code enum
*/
typedef enum{
    RET_OK,
    RET_NG,
    FILE_BUSY,
}log_proxy_funret_em;
#endif

/********************************************************************************************/
/*							Extern Declaration												*/
/********************************************************************************************/

/********************************************************************************************/
/*                      	Global Function Prototype Declaration                           */
/********************************************************************************************/
/* 
 * ===  FUNCTION  ======================================================================
 *         Name :   
 *  Description :   
 *	Return      :   
 *	Example     :   
 * =====================================================================================
 */
extern bool log_proxy_init();
/* 
 * ===  FUNCTION  ======================================================================
 *         Name :   
 *  Description :   
 *	Return      :	
 *	Example     :	
 *                  
 *                  
 *                  
 *                  
 * =====================================================================================
 */
extern bool log_proxy_register_callback(unsigned char attribute_key,log_sub_messg_callback pfun,void *puser_data);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name :   
 *  Description :   
 *	Return      :	
 *	Example     :	
 *                  
 *                  
 *                  
 *                  
 * =====================================================================================
 */
extern char log_proxy_set_info(unsigned char attribute_key,unsigned char attribute_value);
#ifdef __cplusplus
}
#endif

#endif /* _LOG_PROXY_H_ */
