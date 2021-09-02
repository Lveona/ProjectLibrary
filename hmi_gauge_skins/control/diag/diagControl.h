#ifndef DiagCONTROL_H
#define DiagCONTROL_H

#include <hmi_share.h>

//#define MID     HMI_MID_DIAG

#define DIAG_INFO_MCU_SOFTWARE_VERSION_LENGTH   6 //不包含'/0'的结束符
#define DIAG_INFO_MCU_HARDWARE_VERSION_LENGTH   4 //不包含'/0'的结束符
#define DIAG_INFO_MCU_MANUFACTURING_ID_LENGTH   6 //不包含'/0'的结束符
#define DIAG_INFO_MCU_SUPPLYER_CODE_LENGTH      4 //不包含'/0'的结束符

class DiagCustomTimer;

enum DIAGSENDMSGID{
  DIAG_SEND_MSG_ID_GETLOG = 0x00,
  DIAG_SEND_MSG_ID_MILEAGE_CLEAR,
  DIAG_SEND_MSG_ID_RESUME_FACTORY,
  DIAG_SEND_MSG_ID_VEHICLE_CONFIG_EV,
  DIAG_SEND_MSG_ID_VEHICLE_CONFIG_HEV,
};

enum DIAGRECEIVEMSGID{
  DIAG_RECEIVE_MSG_ID_GETLOG_CONEECT_OK = 0x00,
  DIAG_RECEIVE_MSG_ID_GETLOG_CONEECT_NG,
  DIAG_RECEIVE_MSG_ID_GETLOG_COMPLETE,
  DIAG_RECEIVE_MSG_ID_MILEAGE_CLEAR_ITEM_DISABLE,
  DIAG_RECEIVE_MSG_ID_MILEAGE_CLEAR_ITEM_ENABLE,
  DIAG_RECEIVE_MSG_ID_RESUME_FACTORY_ITEM_DISABLE,
  DIAG_RECEIVE_MSG_ID_RESUME_FACTORY_ITEM_ENABLE,
};

enum DIAGLOGOUTPUT{
    DIAG_LOGOUTPUT = 0X00,
    DIAG_LOGCONNCTING,
    DIAG_LOGOUTPUTING,
};

enum DIAGPOPOUTPUT{
    DIAGPOP_NONE = 0,
    DIAGPOP_LOGOUTPUTSUCCESS = 111,         //pop：Log数据传输完成
    DIAGPOP_LOGOUTPUTING = 112,             //pop：正在传输log数据
    DIAGPOP_LOGOUTPUTFIAL = 114,            //pop：Log数据传输失败
    DIAGPOP_CLEARTOTALMILESUCCESS = 211,    //pop：总里程清零完成
    DIAGPOP_CLEARTOTALMILEING = 212,        //pop：正在清除总里程
};

typedef struct
{
    Type_uByte    powerMode;                // PowerMode(Openning/IG_ON/IG_OFF)
} _stDiagControlInfo;

class DiagControl: public CBaseControl, public CSingleton<DiagControl>
{
    Q_OBJECT
    friend class CSingleton<DiagControl>;
public:
    DiagControl();
    ~DiagControl();
    typedef void (DiagControl::*DiagFunctionParser)();
    //typedef void (DiagControl::*DiagVoidFunctionParser)();
    void triggerPowerMode(Type_uByte sts);
    void clearTotalMile();  //清除总计里程
    void func_ODO_CLEAR_TIME();
    void func_MSG_EEPROM_4(const char * data);
    void logOutput();   //log输出
    void diagReset();   //恢复出厂设置
    void diagSetPopTimer(bool status);
signals:
    void PropertyChange(bool condFlg);  // for diagControl
    void PropertyChange(QString name, QVariant value);  // for diagControl(里程清0选项 无效/有效  恢复出厂设置 无效/有效)
    void eventNotify(DIAGRECEIVEMSGID event);


public slots:
    void getFromOtherCtrl(QString message_key, QVariant message_value);
    void get_timeout500ms();
protected:
    void dataChange();

private:
    int get16To10(int value);
private:
    QMutex mutex;
public:
    _stDiagControlInfo m_DiagCtrlInfo;
};


#endif // DiagCONTROL_H
