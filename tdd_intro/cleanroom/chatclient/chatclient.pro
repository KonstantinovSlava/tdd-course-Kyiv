include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../chatclientstatic/

SOURCES += \
    test.cpp \
    socketwrappertest.cpp

LIBS += \
    Ws2_32.lib \
    Mswsock.lib \
    AdvApi32.lib \
    -L../chatclientstatic/debug -lchatclientstatic

HEADERS += \
    mocks.h
