TEMPLATE = app
QT       += core quick qml

DESTDIR = $$PWD/bin

TARGET = NewDBC_H

SOURCES += \
    hmibox.cpp \
    main.cpp

RESOURCES += \
    qml.qrc

HEADERS += \
    hmibox.h
