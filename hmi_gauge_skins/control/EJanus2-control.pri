
HEADERS += \
    $$PWD/adas/adasControl.h \
    $$PWD/adas/adasScreen.h \
    $$PWD/adas/adasTarget.h \
    $$PWD/carInfo/carInfoControl.h \
    $$PWD/carInfo/carInfoScreen.h \
    $$PWD/diag/diagControl.h \
    $$PWD/diag/diagScreen.h \
    $$PWD/home/HomeControl.h \
    $$PWD/home/HomeScreen.h \
    $$PWD/interconnect/InterconnectControl.h \
    $$PWD/interconnect/InterconnectScreen.h \
    $$PWD/popup/popupControl.h \
    $$PWD/popup/popupScreen.h \
    $$PWD/manager/manager.h \
    $$PWD/setting/settingControl.h \
    $$PWD/setting/settingScreen.h \
    $$PWD/setting/languge/langugeManage.h \
    $$PWD/updateControl/update_thread.h \
    $$PWD/popup/popupFaultQuery.h \
    $$PWD/manager/worker.h \
    $$PWD/popup/popup.h \
    $$PWD/popup/popupStrategy.h \
    $$PWD/popup/uniqPopAddInfo.h \
    $$PWD/adas/adasEnums.h

SOURCES += \
    $$PWD/adas/adasControl.cpp \
    $$PWD/adas/adasScreen.cpp \
    $$PWD/carInfo/carInfoControl.cpp \
    $$PWD/carInfo/carInfoScreen.cpp \
    $$PWD/diag/diagControl.cpp \
    $$PWD/diag/diagScreen.cpp \
    $$PWD/home/HomeControl.cpp \
    $$PWD/home/HomeScreen.cpp \
    $$PWD/interconnect/InterconnectControl.cpp \
    $$PWD/interconnect/InterconnectScreen.cpp \
    $$PWD/popup/popupControl.cpp \
    $$PWD/popup/popupScreen.cpp \
    $$PWD/manager/manager.cpp \
    $$PWD/setting/settingControl.cpp \
    $$PWD/setting/settingScreen.cpp \
    $$PWD/setting/languge/langugeManage.cpp \
    $$PWD/updateControl/update_thread.cpp \
    $$PWD/popup/popupFaultQuery.cpp \
    $$PWD/manager/worker.cpp \
    $$PWD/popup/popupStrategy.cpp

HEADERS += \
    $$PWD/../fw/include/BaseControl.h \
    $$PWD/../fw/include/Singleton.h \
    $$PWD/../fw/include/BaseScreen.h \
    $$PWD/../fw/include/hmi_share.h \
    $$PWD/../fw/include/mysharememory.h \
    $$PWD/../fw/include/parsingData.h

SOURCES += \
    $$PWD/../fw/BaseControl.cpp \
    $$PWD/../fw/hmi_share.cpp \
    $$PWD/../fw/mysharememory.cpp \
    $$PWD/../fw/parsingData.cpp

!temp{
    INCLUDEPATH += $$(NEU_CLS_RELEASE_DIR)/include/
    INCLUDEPATH += $$(NEU_CLS_RELEASE_DIR)/include/RH850/
    HEADERS += $$(NEU_CLS_RELEASE_DIR)/include/RH850/PF_Common.h \
               $$(NEU_CLS_RELEASE_DIR)/include/libivs.h \
               $$(NEU_CLS_RELEASE_DIR)/include/log_proxy.h \
               $$(NEU_CLS_RELEASE_DIR)/include/libivp.h \
               $$(NEU_CLS_RELEASE_DIR)/include/libaudio.h \
               $$(NEU_CLS_RELEASE_DIR)/include/libclsmgrd.h \
               $$(NEU_CLS_RELEASE_DIR)/include/update_proxy.h \
               $$(NEU_CLS_RELEASE_DIR)/include/pm_proxy.h
}

temp{
    DEFINES += TEMPFUNC
    INCLUDEPATH += $$PWD/../dummy_common/headers
    HEADERS +=  $$PWD/../dummy_common/headers/PF_Common.h \
                $$PWD/../dummy_common/headers/libivs.h \
                $$PWD/../dummy_common/headers/libivp.h \
                $$PWD/../dummy_common/headers/libaudio.h \
                $$PWD/../dummy_common/headers/pm_proxy.h \
                $$PWD/../dummy_common/headers/log_proxy.h \
                $$PWD/../dummy_common/headers/PF_Common.h \
                $$PWD/../dummy_common/headers/update_proxy.h


    SOURCES +=  $$PWD/../dummy_common/source/libivs.cpp \
                $$PWD/../dummy_common/source/libivp.cpp \
                $$PWD/../dummy_common/source/libaudio.cpp \
                $$PWD/../dummy_common/source/pm_proxy.cpp \
                $$PWD/../dummy_common/source/update_proxy.cpp \
                $$PWD/../dummy_common/source/log_proxy.cpp


}

test{
    DEFINES += TESTFUNC
    QT += testlib

    HEADERS += $$PWD/hmitest.h
    SOURCES += $$PWD/hmitest.cpp
}

hmibox{
    DEFINES += HMIBOX
}
high{
    DEFINES += HMIHIGH
}
INCLUDEPATH += $$PWD/../fw/include
