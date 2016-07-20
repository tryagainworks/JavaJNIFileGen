#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T11:28:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JavaJNIFileGen
TEMPLATE = app


#INCLUDEPATH += "/usr/include/c++/4.8/"

#INCLUDEPATH += "/usr/include/"

SOURCES += main.cpp\
        frmmain.cpp \
    ClsCreateHeaderFile_CPP.cpp \
    MyLib/clsmyqtlib.cpp \
    MyLib/clsmystdlib.cpp \
    clsfilesettings.cpp \
    frmsettings.cpp

HEADERS  += frmmain.h \
    ClsCreateHeaderFile_CPP.h \
    MyLib/clsmyqtlib.h \
    MyLib/clsmystdlib.h \
    clsfilesettings.h \
    frmsettings.h

FORMS    += frmmain.ui \
    frmsettings.ui

CONFIG += c++11


unix:!macx: LIBS += -L$$PWD/../../../../../InstalledPgms/boost1610_devlib/lib/ -lboost_filesystem
unix:!macx: LIBS += -L$$PWD/../../../../../InstalledPgms/boost1610_devlib/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../../../../InstalledPgms/boost1610_devlib/include
DEPENDPATH += $$PWD/../../../../../InstalledPgms/boost1610_devlib/include
