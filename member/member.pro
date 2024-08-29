QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    memberwindow.cpp \
    memberdialog.cpp

HEADERS += \
    ../db/connection.h \
    memberwindow.h \
    memberdialog.h

FORMS += \
    memberwindow.ui \
    memberdialog.ui

OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

TARGET      = exe

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
