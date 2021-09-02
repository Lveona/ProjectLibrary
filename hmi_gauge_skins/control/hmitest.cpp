#include "hmitest.h"
#include "control/manager/manager.h"

static CarInfoControl* _CarInfoControl = CarInfoControl::instance();
static PopupControl* _PopupControl = PopupControl::instance();
static PopupStrategy* _PopupStrategy = PopupStrategy::instance();
static QList<char *> sources;

void HMITest::initTestCase()
{
    qRegisterMetaType<CarInfoControl*>("CarInfoControl*");
//    qRegisterMetaType<powerMode>("powerMode");
//    qRegisterMetaType<TargetValue>("TargetValue");
}

void HMITest::cleanupTestCase()
{
    foreach (char *msg, sources) {
        delete msg; msg = NULL;
    }
    sources.clear();
}

void HMITest::case_MCU_TRIP_A()
{
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(double, result);

    //set data

    const char * _msg = (char *)msg;
    _CarInfoControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    _CarInfoControl->func_MSG_MCU_1(_msg);

    QVariant value = _CarInfoControl->getPropertyValue(PROPERTYID_CARINFO_TRIPA);
    QCOMPARE(value.toDouble(), result);
}

void HMITest::case_MCU_TRIP_A_data()
{
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<double>("result");

    //test data
    QList<int> testMsgList = {0, 1, 999, 9999, 99999, 999999, 999999, 9999999, 99999991 };

    foreach (int value, testMsgList) {
        _c_MSG_MCU_1_msgType* msg = new _c_MSG_MCU_1_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.MCU_TRIP_A = value;
        sources.append((char *)msg);

        int pm = 1; //POWERMODE_D1

        double tmp = ((int)(value*0.01))*0.1;

        QTest::newRow("trip A")<<(void *)msg<<pm<<tmp;
    }
}

/*
void HMITest::case_Left_Turn()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_281h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_LEFT_TURN);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Left_Turn_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_281h_IP_msgType *msg = new _c_ICGM_IBDU_281h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.TurnLampLeftStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Right_Turn()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_281h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_RIGHT_TURN);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Right_Turn_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_281h_IP_msgType *msg = new _c_ICGM_IBDU_281h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.TurnLampRightStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_EPB()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_EPB = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_245h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_EPB);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_EPB_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_spangle,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_ESC_245h_IP_msgType *msg = new _c_ICGM_ESC_245h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.Parkinglamp = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Temp()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_5E1h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_TEMP);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Temp_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_5E1h_IP_msgType *msg = new _c_ICGM_IBDU_5E1h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.TPMSLampStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}
void HMITest::case_Position_Light()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_375h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_POSITION_LIGHT);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Position_Light_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_375h_IP_msgType *msg = new _c_ICGM_IBDU_375h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.PositionLampStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Far_Beam()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_375h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_FAR_BEAM);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Far_Beam_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_375h_IP_msgType *msg = new _c_ICGM_IBDU_375h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.MainBeamStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Rear_Fog()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_Rear_fog = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_375h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_REAR_FOG);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Rear_Fog_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_375h_IP_msgType *msg = new _c_ICGM_IBDU_375h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.RearFogLightStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_ABS()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_269h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_ABS);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_ABS_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_ESC_269h_IP_msgType *msg = new _c_ICGM_ESC_269h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.ABSFault = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_AirBag()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_SRS_355h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_AIR_BAG);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_AirBag_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_SRS_355h_IP_msgType *msg = new _c_ICGM_SRS_355h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.AirbagSystemError = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Engine_Anti_Theft()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
//    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_IBDU_281h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_ENGINE_ANTI_THEFT);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Engine_Anti_Theft_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_spangle,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_spangle,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_IBDU_281h_IP_msgType *msg = new _c_ICGM_IBDU_281h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.IMMOIndicator = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_EBD()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
//    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_269h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_EBD);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_EBD_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_ESC_269h_IP_msgType *msg = new _c_ICGM_ESC_269h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.EBDFault = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_MIL()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
//    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_322h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_MIL);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_MIL_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_EMS_322h_IP_msgType *msg = new _c_ICGM_EMS_322h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.EngineMILOn = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Engine_Fault()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
//    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_322h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_ENGINE_FAULT);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Engine_Fault_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_EMS_322h_IP_msgType *msg = new _c_ICGM_EMS_322h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.EngineFault = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Glow()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_Glow = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_322h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_GLOW);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Glow_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_EMS_322h_IP_msgType *msg = new _c_ICGM_EMS_322h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.GlowTimeIndicator = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_WaterInFuel()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_WaterInfuel = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_322h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_WATERINFUEL);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_WaterInFuel_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_EMS_322h_IP_msgType *msg = new _c_ICGM_EMS_322h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.WaterInFuelIndicator = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_ESP()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_ESP = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_1E9h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_ESP);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_ESP_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};
    QList<int> testMsg2List = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][2][4] = { //4表示电源状态
        {
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
        {
            {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex2 = 0;
    foreach (int value2, testMsg2List) {
        int msgIndex = 0;
        foreach (int value, testMsgList) {
            _c_ICGM_ESC_1E9h_IP_msgType *msg = new _c_ICGM_ESC_1E9h_IP_msgType();
            memset((char *)msg, 0, sizeof(*msg));
            msg->Signals.ESPFault = value;
            msg->Signals.ESPActive = value2;
            sources.append((char *)msg);

            commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList[msgIndex2]);
            msgIndex++;
        }
        msgIndex2++;
    }
}


void HMITest::case_ESP_OFF()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_ESP = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_1E9h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_ESP_OFF);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_ESP_OFF_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_ESC_1E9h_IP_msgType *msg = new _c_ICGM_ESC_1E9h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.ESPOffLampStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_ESP_Fail()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_ESP = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EPS_335h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_ESP_FAULT);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_ESP_Fail_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_EPS_335h_IP_msgType *msg = new _c_ICGM_EPS_335h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.EPSFail_WL = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Cruise()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    1 = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_210h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_CRUISE);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Cruise_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};
    QList<int> testMsg2List = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][2][4] = { //4表示电源状态
        {
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
        {
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex2 = 0;
    foreach (int value2, testMsg2List) {
        int msgIndex = 0;
        foreach (int value, testMsgList) {
            _c_ICGM_EMS_210h_IP_msgType *msg = new _c_ICGM_EMS_210h_IP_msgType();
            memset((char *)msg, 0, sizeof(*msg));
            msg->Signals.CruiseControlStandBy = value;
            msg->Signals.CruiseControlActive = value2;
            sources.append((char *)msg);

            commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList[msgIndex2]);
            msgIndex++;
        }
        msgIndex2++;
    }
}

void HMITest::case_EPB_Fault()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_EPB = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_245h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_EPB_FAULT);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_EPB_Fault_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_true,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_spangle,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_ESC_245h_IP_msgType *msg = new _c_ICGM_ESC_245h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.Failurelamp = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_Auto_Hold()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_EPB = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_1E9h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_AUTO_HOLD);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_Auto_Hold_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1};
    QList<int> testMsg2List = {0, 1};
    QList<int> testMsg3List = {0, 1};

    int testCFGtList[] = {0, 1};
    int testResultList[][2][2][4] = { //4表示电源状态
        {
            {
                {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
                {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            },
            {
                {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
                {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            }
         },
          {
              {
                  {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
                  {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
              },
              {
                  {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
                  {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
              }
           },
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex3 = 0;
    foreach (int value3, testMsg3List) {
        int msgIndex2 = 0;
        foreach (int value2, testMsg2List) {
            int msgIndex = 0;
            foreach (int value, testMsgList) {
                _c_ICGM_ESC_1E9h_IP_msgType *msg = new _c_ICGM_ESC_1E9h_IP_msgType();
                memset((char *)msg, 0, sizeof(*msg));
                msg->Signals.AvhStandy = value;
                msg->Signals.AvhActive = value2;
                msg->Signals.AvhAvaliable = value3;
                sources.append((char *)msg);

                commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList[msgIndex3][msgIndex2]);
                msgIndex++;
            }
            msgIndex2++;
        }
        msgIndex3++;
    }
}

void HMITest::case_HDC()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_ESP = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_ESC_1E9h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_HDC);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_HDC_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_ESC_1E9h_IP_msgType *msg = new _c_ICGM_ESC_1E9h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.HDCControlStatus = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_SCR()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_SCR = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_323h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_SCR);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_SCR_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3, 4, 5, 6, 7};  //AdBlueLevelWarning_LD
    QList<int> testMsg2List = {0, 1, 2, 3}; //AdBlueSystemErrorLevel_LD

    int testCFGtList[] = {0, 1};
    int testResultList[][8][4] = { //4表示电源状态
        {
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        },
        {
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
        {
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
        {
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
            {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        },
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex2 = 0;
    foreach (int value2, testMsg2List) {
        int msgIndex = 0;
        foreach (int value, testMsgList) {
            _c_ICGM_EMS_323h_IP_msgType *msg = new _c_ICGM_EMS_323h_IP_msgType();
            memset((char *)msg, 0, sizeof(*msg));
            msg->Signals.AdBlueLevelWarning_LD = value;
            msg->Signals.AdBlueSystemErrorLevel_LD = value2;
            sources.append((char *)msg);

            commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList[msgIndex2]);
            msgIndex++;
        }
        msgIndex2++;
    }
}

void HMITest::case_DPF()
{
    QFETCH(int, cfg);
    QFETCH(void *, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    CFG_DPF = cfg;
    _TelltalesControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    const char * _msg = (char *)msg;
    _TelltalesControl->func_MSG_ICGM_EMS_227h(_msg);

    Telltales *tell = _TelltalesControl->getTellById(PROPERTYID_DPF);
    QCOMPARE(int(tell->targetvalue), result);
}

void HMITest::case_DPF_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<void *>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

    //test data
    QList<int> testMsgList = {0, 1, 2, 3, 4, 5, 6, 7};

    int testCFGtList[] = {0, 1};
    int testResultList[][4] = { //4表示电源状态
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_true,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_spangle,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
        {VISIBLE_false,VISIBLE_false,VISIBLE_false,VISIBLE_false},
    };
    int cfgLen =  sizeof(testCFGtList)/sizeof(int);

    //add column
    int msgIndex = 0;
    foreach (int value, testMsgList) {
        _c_ICGM_EMS_227h_IP_msgType *msg = new _c_ICGM_EMS_227h_IP_msgType();
        memset((char *)msg, 0, sizeof(*msg));
        msg->Signals.DpfWarningInf = value;
        sources.append((char *)msg);

        commonAddColumns(msgIndex, (const char *)msg, value, testCFGtList, cfgLen, testResultList);
        msgIndex++;
    }
}

void HMITest::case_overspeed()
{
    QFETCH(int, cfg);
    QFETCH(int, msg);
    QFETCH(int, pm);
    QFETCH(int, result);

    //set data
    _PopupControl->getFromOtherCtrl(HMI_MSGNAME_POWER_MODE, pm);
    _PopupControl->getFromOtherCtrl(HMI_MSGNAME_OVERSPEED, msg);

    Type_uByte operation = _PopupStrategy->getPopById(POP_WMSG_CATEGORY_A, 14);

    QCOMPARE((int)operation, result);
}

void HMITest::case_overspeed_data()
{
    QTest::addColumn<int>("cfg");
    QTest::addColumn<int>("msg");
    QTest::addColumn<int>("pm");
    QTest::addColumn<int>("result");

//    QList<int> testPMList = {POWERMODE_ANIMATION, POWERMODE_D1, POWERMODE_D2, POWERMODE_D3};

//    foreach (int pm, testPMList){
//        QString tag = QString("cfg:%2 msg:%3 pm:%4").arg(QString::number(0)).arg( QString::number(0)).arg( QString::number(pm));

//        char * tagTip = tag.toUtf8().data();
//        QTest::newRow(tagTip)<<0<<0<<int(POWERMODE_D1)<<POP_ALARM_OFF;
//        QTest::newRow(tagTip)<<0<<1<<pm<<POP_ALARM_ON;
//    }
    QTest::newRow("tagTip")<<0<<0<<int(POWERMODE_D1)<<(int)POP_ALARM_OFF;
    QTest::newRow("tagTip")<<0<<1<<int(POWERMODE_D1)<<(int)POP_ALARM_ON;
}
*/

void HMITest::commonAddColumns(int msgIndex, const char *msg, int value, int testCFGtList[], int cfgLen, int testResultList[][4])
{
//    QList<int> testPMList = {POWERMODE_ANIMATION, POWERMODE_D1, POWERMODE_D2, POWERMODE_D3};

//    for(int a = 0; a < cfgLen; a++)
//    {
//        int cfg = testCFGtList[a];
//        int pmIndex = 0;
//        foreach (int pm, testPMList)
//        {
//            QString tag = QString("cfg:%2 msg:%3 pm:%4").arg(QString::number(cfg)).arg( QString::number(value)).arg( QString::number(pm));

//            char * tagTip = tag.toUtf8().data();
//            if(1 == cfg)
//                QTest::newRow(tagTip)<<cfg<<(void *)msg<<pm<<testResultList[msgIndex][pmIndex];
//            else
//                QTest::newRow(tagTip)<<cfg<<(void *)msg<<pm<<(int)VISIBLE_false;
//            pmIndex++;
//        }
//    }
}
