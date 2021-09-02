#ifndef HMITEST_H
#define HMITEST_H
#include <QtTest/QtTest>

class HMITest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    //carinfo
    void case_MCU_TRIP_A();
    void case_MCU_TRIP_A_data();
    //tell
    /*void case_Left_Turn();
    void case_Left_Turn_data();
    void case_Right_Turn();
    void case_Right_Turn_data();
    void case_EPB();
    void case_EPB_data();
    void case_Temp();
    void case_Temp_data();
    void case_Position_Light();
    void case_Position_Light_data();
    void case_Far_Beam();
    void case_Far_Beam_data();
    void case_Rear_Fog();
    void case_Rear_Fog_data();
    void case_ABS();
    void case_ABS_data();
    void case_AirBag();
    void case_AirBag_data();
    void case_Engine_Anti_Theft();
    void case_Engine_Anti_Theft_data();
    void case_EBD();
    void case_EBD_data();
    void case_MIL();
    void case_MIL_data();
    void case_Engine_Fault();
    void case_Engine_Fault_data();
    void case_Glow();
    void case_Glow_data();
    void case_WaterInFuel();
    void case_WaterInFuel_data();
    void case_ESP();
    void case_ESP_data();
    void case_ESP_OFF();
    void case_ESP_OFF_data();
    void case_ESP_Fail();
    void case_ESP_Fail_data();
    void case_Cruise();
    void case_Cruise_data();
    void case_EPB_Fault();
    void case_EPB_Fault_data();
    void case_Auto_Hold();
    void case_Auto_Hold_data();
    void case_HDC();
    void case_HDC_data();
    void case_SCR();
    void case_SCR_data();
    void case_DPF();
    void case_DPF_data();

    //pop
    void case_overspeed();
    void case_overspeed_data();
*/

private:
    void commonAddColumns(int msgIndex, const char *msg, int value, int testCFGtList[], int cfgLen, int testResultList[][4]);   //统一格式,生成测试数据
};

#endif // HMITEST_H
