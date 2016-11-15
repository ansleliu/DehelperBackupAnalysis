#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T23:30:35
#
#-------------------------------------------------

QT       += core gui

TARGET = DehelperBackupAnalysis
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    pathmanage.cpp \
    MySQLite.cpp \
    CreatWordListDB.cpp \
    StartDialog.cpp

HEADERS  += MainWindow.h \
    pathmanage.h \
    MySQLite.h \
    CreatWordListDB.h \
    StartDialog.h

FORMS    += MainWindow.ui \
    StartDialog.ui

UI_DIR = ./ui
MOC_DIR = TEMP/moc
RCC_DIR = TEMP/rcc
OBJECTS_DIR = TEMP/obj

RESOURCES += \
    rc.qrc

OTHER_FILES += \
    myapp.rc

RC_FILE = myapp.rc
