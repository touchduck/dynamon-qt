#-------------------------------------------------
#
# Project created by QtCreator 2016-02-28T23:02:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dynamon

macx: ICON = resource/app.icns

TEMPLATE = app

CONFIG += c++11

DEFINES += AWS_CUSTOM_MEMORY_MANAGEMENT

SOURCES += main.cpp\
    CDynamoItem.cpp \
    CDynamo.cpp \
    Common.cpp \
    DataWindow.cpp \
    CdynamoItemType.cpp

HEADERS  += \
    CDynamoItem.h \
    Common.h \
    CDynamo.h \
    DataWindow.h \
    CdynamoItemType.h

FORMS    += \
    DataWindow.ui

macx: LIBS += -lcurl
macx: LIBS += -L/usr/local/lib/ -laws-cpp-sdk-core -laws-cpp-sdk-dynamodb
macx: INCLUDEPATH += /usr/local/include

