/*
 * =====================================================================================
 *
 *       Filename :  libivs.h
 *
 *    Description :
 *
 *        Version :  1.0
 *        Created:  08/24/2016 09:15:29 AM
 *       Revision :  none
 *       Compiler :  gcc
 *
 *         Author :  luxuan (), luxuan@neusoft.com
 *   Organization :  www.neusoft.com
 *
 * =====================================================================================
 */
#ifndef __LIBIVS_H__
#define __LIBIVS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : id of feedback hardwire
*/
/* ----------------------------------------------------------------------------*/
typedef enum _IVS_FEEDBACK_HARDWIRE {
    IVS_FB_HARDWIRE_IGNEN,
    IVS_FB_HARDWIRE_WAKEUPEN
} IVS_FEEDBACK_HARDWIRE;

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : id of power-status hardwire
*/
/* ----------------------------------------------------------------------------*/
typedef enum _IVS_POWERSTATUS_HARDWIRE {
    IVS_PS_HARDWIRE_IGN,
    IVS_PS_HARDWIRE_WAKEUP
} IVS_POWERSTATUS_HARDWIRE;

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : A IVSMessageHandlerFunction function can be added to ivs_proxy_set_message_callback()
*           as a callback. Since RPC message is arriving from MCU on SPI bus, the corresponding
*           IVSMessageHandlerFunction will be called.
*
* @Param message_id : the id of message received by IVS.
* @Param pData : the payload of message received by IVS.
* @Param data_len : the payload length.
* @Param pUserData : data passed to this fuction set by ivs_proxy_set_message_callback().
*
* @Returns
*/
/* ----------------------------------------------------------------------------*/
typedef void (*IVSMessageHandlerFunction)(unsigned char message_id,const unsigned char * pData, unsigned char data_len, void * pUserData);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : A IVSHardwireHandlerFunction function can be added to ivs_proxy_set_hardwire_callback()
*            as a callback. Since the status of hardwire is changing, the corresponding IVSHardwireHandlerFunction
*            function will be called.
*
* @Param hardwire_id : the id of Power Manager's hardwires, 0 stand for ign hardwire, 1 stand for batt hardwire.
* @Param value : the electrical level of hardwire, 0 stand for low level, 1 stand fo high level
* @Param pUser_data : data passed to this fuction set by ivs_proxy_set_hardwire_callback().
*
* @Returns
*/
/* ----------------------------------------------------------------------------*/
typedef void (*IVSHardwireHandlerFunction)(IVS_POWERSTATUS_HARDWIRE hardwire_id, int value, void * pUser_data);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : A IVSProxyRequestCallback function can be add to ivs_proxy_send_request()
*            as a callback. Since respond feedback or timeout, the corresponding IVSProxyRequestCallback
*            function will be called.
*
* @Param status : true if the status of the respond is successful; false otherwise
* @Param pUser_data : data passed to this function set by ivs_proxy_send_request()
*
* @Returns
*/
/* ----------------------------------------------------------------------------*/
typedef void (*IVSProxyRequestCallback)(bool status, void * pUser_data);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : RPC request struct
*/
/* ----------------------------------------------------------------------------*/
typedef struct _IVSProxyRequest {
    unsigned char rw;
    unsigned short length;
    unsigned char control;
    unsigned short opecode;
    unsigned char data[25];
} __attribute__((packed)) IVSProxyRequest;

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : Initialize the libivs's context
*
* @Returns  : true if initialize successfully; false otherwise
*
* @Attention : Call ivs_proxy_init() to initialize the libivs's context, before
*             calling ivs_proxy_set_message_callback(), ivs_proxy_set_hardwire_callback()
*             ivs_proxy_send_request(), ivs_proxy_control_hardwire(), ivs_proxy_release().
*/
/* ----------------------------------------------------------------------------*/
bool ivs_client_init(void);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : Release the libivs's context
*
* @Attention : Call this function , after calling ivs_proxy_init() to initalize
*             the libivs's context
*/
/* ----------------------------------------------------------------------------*/
//void ivs_client_release(void);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis Set callback function to monitor In-Vehicle Signals on SPI bus from MCU
*
* @Param message_id : id of RPC Message.
* @Param pFunc : calling the function when receiving the RPC message
* @Param pUser_data : data passed to the callback function.
*
* @Returns : null
*
* @Attention : Call this function , after calling ivs_proxy_init() to initalize
*             the libivs's context
*/
/* ----------------------------------------------------------------------------*/
void ivs_client_set_message_callback(unsigned char message_id, IVSMessageHandlerFunction pFunc, void * pUser_data);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis Set callback function to monitor status of Power Manager's hardwire On MCU.
*
* @Param hardwire_id : id of Power Manager's hardwire, 0 stand for low level, 1 stand for high level.
* @Param pFunc : calling the function when status of Power Manager's hardwire is changed.
* @Param pUser_data : data passed to the callback function.
*
* @Returns : null
*/
/* ----------------------------------------------------------------------------*/
void ivs_client_set_hardwire_callback(IVS_POWERSTATUS_HARDWIRE hardwire_id, IVSHardwireHandlerFunction pFunc, void * pUser_data);

/* --------------------------------------------------------------------------*/
/**
* @Synopsis : Send RPC frame data to MCU on SPI bus
*
* @Param pRequest : RPC frame to be send.
* @Param pFunc : calling the function when request's result is feedback.
* @Param pUser_data : parameter is passed to callback function.
*
* @Returns :null
*
* @Attention : Call this function , after calling ivs_proxy_init() to initalize
*             the libivs's context
*/
/* ----------------------------------------------------------------------------*/
//bool ivs_client_send_request(IVSProxyRequest * pRequest, IVSProxyRequestCallback pFunc, void * pUser_data);
void ivs_client_send_request(IVSProxyRequest * pRequest, void * pUser_data);
/* --------------------------------------------------------------------------*/
/**
* @Synopsis : Control of feedback hardwire of Power Manager.
*
* @Param hardwire_id : feedback hardwire id. 0 stand for standby hardwire; 1 stand for ign_en hardwire.
* @Param level : electrical level of feedback hardwire. 0 stand for low level; 1 stand for high level.
*
* @Returns :null
*
* @Attention : Call this function , after calling ivs_proxy_init() to initalize
*             the libivs's context
*/
/* ----------------------------------------------------------------------------*/
void ivs_client_control_hardwire(IVS_FEEDBACK_HARDWIRE hardwire_id, bool level);

#ifdef __cplusplus
}
#endif

#endif
