TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib
CONFIG -= qt

SOURCES += \
    stdafx.cpp \
    socketwrapper.cpp \
    utils.cpp \
    connecionwrapper.cpp \
    chatapp.cpp \
    gui.cpp

LIBS += \
    Ws2_32.lib \
    AdvApi32.lib


HEADERS += \
    socketwrapper.h \
    isocketwrapper.h \
    igui.h \
    utils.h \
    stdafx.h \
    connecionwrapper.h \
    chatapp.h \
    gui.h
