#-------------------------------------------------
#
# Project created by QtCreator 2018-10-03T17:51:24
#
#-------------------------------------------------

QT       += widgets

TARGET = table_project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    zes_hoek.cpp \
    playingfield.cpp \
    docks.cpp \
    resource_tyle.cpp \
    field_number.cpp \
    key_press.cpp \
    gamestate.cpp \
    player.cpp \
    gamewindow.cpp

HEADERS += \
    zes_hoek.h \
    playingfield.h \
    docks.h \
    resource_tyle.h \
    field_number.h \
    key_press.h \
    gamestate.h \
    player.h \
    gamewindow.h

FORMS += \
        main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
