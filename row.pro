QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwin/mainwindow.cpp \
    member/memberwindow.cpp \
    member/memberdialog.cpp \
    mitglied/mitgliedwindow.cpp \
    mitglied/mitglieddialog.cpp \
    boat/boatwindow.cpp \
    boat/boatdialog.cpp

HEADERS += \
    db/connection.h \
    mainwin/mainwindow.h \
    member/memberwindow.h \
    member/memberdialog.h \
    mitglied/mitgliedwindow.h \
    mitglied/mitglieddialog.h \
    boat/boatwindow.h \
    boat/boatdialog.h

FORMS += \
    mainwin/mainwindow.ui \
    member/memberwindow.ui \
    member/memberdialog.ui \
    mitglied/mitgliedwindow.ui \
    mitglied/mitglieddialog.ui \
    boat/boatwindow.ui \
    boat/boatdialog.ui

#SOURCES = $$files(*.cpp, true)
#HEADERS = $$files(*.h, true)
#FORMS   = $$files(*.ui, true)



# TEMPLATE = subdirs

# SUBDIRS = member mitglied boat

OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

TARGET      = viena

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
