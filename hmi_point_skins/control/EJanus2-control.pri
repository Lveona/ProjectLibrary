
HEADERS += \
    $$PWD/manager/manager.h \
    $$PWD/gauge/GaugeControl.h \
    $$PWD/gauge/GaugeScreen.h \
    $$PWD/telltale/telltale.h \
    $$PWD/telltale/telltaleflash.h \
    $$PWD/telltale/telltalesControl.h \
    $$PWD/telltale/telltalesScreen.h \
    $$PWD/telltale/telltalesStrategy.h \
    $$PWD/manager/worker.h


SOURCES += \
    $$PWD/manager/manager.cpp \
    $$PWD/gauge/GaugeControl.cpp \
    $$PWD/gauge/GaugeScreen.cpp \
    $$PWD/telltale/telltaleflash.cpp \
    $$PWD/telltale/telltalesControl.cpp \
    $$PWD/telltale/telltalesScreen.cpp \
    $$PWD/telltale/telltalesStrategy.cpp \
    $$PWD/manager/worker.cpp


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
               $$(NEU_CLS_RELEASE_DIR)/include/libclsmgrd.h \
               $$(NEU_CLS_RELEASE_DIR)/include/libaudio.h \
               $$(NEU_CLS_RELEASE_DIR)/include/pm_proxy.h

}

temp{
    DEFINES += TEMPFUNC
    INCLUDEPATH += $$PWD/../dummy_common/headers
    HEADERS +=  $$PWD/../dummy_common/headers/PF_Common.h \
                $$PWD/../dummy_common/headers/libivs.h \
                $$PWD/../dummy_common/headers/libaudio.h


    SOURCES +=  $$PWD/../dummy_common/source/libivs.cpp \
                $$PWD/../dummy_common/source/libaudio.cpp

}
hmibox{
    DEFINES += HMIBOX
}
test{
    DEFINES += TESTFUNC
    QT += testlib

    HEADERS += $$PWD/hmitest.h
    SOURCES += $$PWD/hmitest.cpp
}
INCLUDEPATH += $$PWD/../fw/include
