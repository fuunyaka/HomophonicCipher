
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Program
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -Wall -pedantic



SOURCES += \
        main.cpp \
        mainwindow.cpp \
    homo_cipher.cpp

HEADERS += \
        mainwindow.h \
    homo_cipher.h

FORMS += \
        mainwindow.ui
