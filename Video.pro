#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T21:50:30
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Video
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    videowidget.cpp \
    mainwindow.cpp

HEADERS  += widget.h \
    videowidget.h \
    mainwindow.h

RESOURCES += \
    img.qrc

DISTFILES += \
    Multimedia 1.ico
