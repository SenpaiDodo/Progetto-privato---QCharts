#-------------------------------------------------
#
# Project created by QtCreator 2021-12-27T13:14:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = progetto
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    videogame.cpp \
    maintitle.cpp \
    expansion.cpp \
    data.cpp \
    pricedata.cpp \
    pricedatanorm.cpp \
    chart.cpp \
    barchart.cpp \
    linechart.cpp \
    pointchart.cpp \
    inputline.cpp \
    canvas.cpp \
    elementrow.cpp \
    table.cpp \
    tab.cpp \
    input.cpp \
    newwindow.cpp \

HEADERS += \
        mainwindow.h \
    videogame.h \
    maintitle.h \
    expansion.h \
    data.h \
    pricedata.h \
    pricedatanorm.h \
    chart.h \
    barchart.h \
    linechart.h \
    pointchart.h \
    inputline.h \
    canvas.h \
    elementrow.h \
    table.h \
    tab.h \
    error.h \
    input.h \
    newwindow.h \

RESOURCES += \
    resources.qrc
