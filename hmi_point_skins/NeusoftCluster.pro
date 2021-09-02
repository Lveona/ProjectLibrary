QT += quick core
CONFIG += c++11
CONFIG -= import_plugins
TARGET= EJanus2-hmi-point

CONFIG += resources_big qtquickcompiler

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
DEFINES += QT_NO_WARNING_OUTPUT

SOURCES += main.cpp \
    skinmanager.cpp

HEADERS += \
    skinmanager.h
   
!temp{
    DESTDIR = $$(NEU_CLS_RELEASE_DIR)/bin
    LIBS += $$(QNX_QTBASE_PREFIX)usr/plugins/platforms/libqnx_ponit/libqqnx.a
    LIBS += $$(QNX_QTBASE_PREFIX)usr/qml/QtQuick.2/libqtquick2plugin.a
    LIBS += $$(QNX_QTBASE_PREFIX)usr/qml/QtQuick/Window.2/libwindowplugin.a
    LIBS += $$(QNX_QTBASE_PREFIX)usr/qml/QtQuick/Shapes/libqmlshapesplugin.a
    LIBS += $$(QNX_QTBASE_PREFIX)usr/qml/QtGraphicalEffects/libqtgraphicaleffectsplugin.a
    LIBS += $$(QNX_QTBASE_PREFIX)usr/qml/QtGraphicalEffects/private/libqtgraphicaleffectsprivate.a
    LIBS += $$(QNX_QTBASE_PREFIX)usr/plugins/imageformats/libqjpeg.a
    #中间件库引用
    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libaudio.so
#    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libivp.so
    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libivs.so
#    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/liblog_proxy.a
    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libPowerManager.a
#    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libproxyupdate.a
    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libclscommon.a
    LIBS += $$(NEU_CLS_RELEASE_DIR)/lib/libneu-clsmgrd-proxy.a

    SOURCES += ejanus2-hmi_plugin_import.cpp \
        ejanus2-hmi_qml_plugin_import.cpp
}
temp{
    DEFINES += TEMPFUNC
    DEFINES += DESKTOP


    CONFIG(release, debug|release){
        message("release")
        DESTDIR = ./release
    }else{
        message("debug")
        DESTDIR = ./debug
    }


    HEADERS += $$PWD/bin/mainwindow.h \
                $$PWD/bin/dynamic_create.h

    RESOURCES += $$PWD/bin/qmlbox.qrc \
                qml_skins.qrc \
                skin/comfort/qml.qrc \
                skin/comfort/image/image.qrc

}

!temp{
    RESOURCES += qml_skins.qrc
}

include("./control/EJanus2-control.pri")

