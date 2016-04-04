#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T14:55:11
#
#-------------------------------------------------

QT       +=  core widgets serialport

TARGET = interface
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    serialwaiterdialog.cpp \
    melody.cpp

HEADERS  += widget.h \
    serialwaiterdialog.h \
    melody.h

FORMS    += widget.ui \
    serialreaderdialog.ui

RESOURCES += \
    resources.qrc

