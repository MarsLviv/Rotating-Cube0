QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl
TARGET = rotating_cube
TEMPLATE = app
LIBS += -lglut -lGLU
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    geometry.cpp \
    positions.cpp \
    mb22.cpp

HEADERS  += mainwindow.h \
    geometry.h \
    positions.h \
    mb22.h

RESOURCES += \
    shaders.qrc
