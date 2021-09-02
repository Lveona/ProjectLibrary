/*
 * =====================================================================================
 *
 *       Filename:  pm_proxy.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/16/2020
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  neusoft 
 *   Organization:  Neusoft
 *
 * =====================================================================================
 */
#ifndef LIB_POWERMANAGER_H
#define LIB_POWERMANAGER_H
#ifdef __cplusplus
extern "C"
{
#endif
#ifdef _TYPE_DEF
#include "pm_config.h"
#endif
#define PM_PROXY_MAX_NUMS       (unsigned char)0x01   /*in one process ,registre max nums*/


/*
** PowerManager to HMI
*/
/* attribute key*/
typedef enum{
	POWER_STATE = 0,

	SERVER_ATTR_MAX,
}pm_proxysub_em;

typedef enum{
	LCP_UPDATE_PROCESS = 0,
	LCP_UPDATE_RESULT,

	SERVER_ATTR_LCD_MAX,
}pm_proxylcd_em;

/* value of attribute key*/
typedef enum{
	PM_NOTIFY_ANIMATION = 0,
	PM_NOTIFY_D1,
	PM_NOTIFY_D2,
	PM_NOTIFY_INIT,

	PM_NOTIFY_MAX,
}pm_power_state_em;

/* value of attribute key*/
typedef enum{
	PM_LCD_RESULT_OK = 0,
	PM_LCD_RESULT_NG,

	PM_LCD_RESULT_MAX,
}pm_power_lcd_result_em;
/*
**HMI to PowerManager
*/
/*attribute key*/
typedef enum{
	HMINOTIFY = 0,

	PROXY_ATTR_MAX,
}pm_proxypub_em;

/* value of attribute key*/
typedef enum{
	HMI_NOTIFY_NORMAL=0x00,
	HMI_NOTIFY_ALAM,
	HMI_NOTIFY_READY,

	HMI_NOTIFY_D1		= 0x10,
	HMI_NOTIFY_D2,
	
	HMI_NOTIFY_LCDUPDATE	= 0x20,

	HMI_NOTIFY_MAX,
}pm_hmi_notify_em;


typedef void (*PM_sub_messg_callback)(unsigned char attribute_key,unsigned char attribute_value,void *puser_data);


bool PM_proxy_init();
bool PM_proxy_register_callback(unsigned char attribute_key,PM_sub_messg_callback pfun,void *puser_data);
bool PM_proxy_set_info(unsigned char attribute_key,unsigned char attribute_value);
bool PM_proxy_register_lcd_callback(unsigned char attribute_key, PM_sub_messg_callback pfun, void * puser_data);

#ifdef __cplusplus
}
#endif

#endif


