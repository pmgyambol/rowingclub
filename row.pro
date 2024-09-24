QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwin/mainwindow.cpp \
    mitglied/mitgliedwindow.cpp \
    mitglied/mitglieddialog.cpp \
    mitglied/planentrainingdialog.cpp \
    boat/boatwindow.cpp \
    boat/boatdialog.cpp \
    gym/gymwindow.cpp \
    gym/gymdialog.cpp \
    cardio/cardiowindow.cpp \
    cardio/cardiodialog.cpp \
    einkommen/einkommenwindow.cpp \
    einkommen/einkommendialog.cpp \
    aufwand/aufwandwindow.cpp \
    aufwand/aufwanddialog.cpp \
    gleichgewicht/gleichgewichtwindow.cpp

HEADERS += \
    db/connection.h \
    mainwin/mainwindow.h \
    mitglied/mitgliedwindow.h \
    mitglied/mitglieddialog.h \
    mitglied/planentrainingdialog.h \
    boat/boatwindow.h \
    boat/boatdialog.h \
    gym/gymwindow.h \
    gym/gymdialog.h \
    cardio/cardiowindow.h \
    cardio/cardiodialog.h \
    einkommen/einkommenwindow.h \
    einkommen/einkommendialog.h \
    aufwand/aufwandwindow.h \
    aufwand/aufwanddialog.h \
    gleichgewicht/gleichgewichtwindow.h

FORMS += \
    mainwin/mainwindow.ui \
    mitglied/mitgliedwindow.ui \
    mitglied/mitglieddialog.ui \
    mitglied/planentrainingdialog.ui \
    boat/boatwindow.ui \
    boat/boatdialog.ui \
    gym/gymwindow.ui \
    gym/gymdialog.ui \
    cardio/cardiowindow.ui \
    cardio/cardiodialog.ui \
    einkommen/einkommenwindow.ui \
    einkommen/einkommendialog.ui \
    aufwand/aufwandwindow.ui \
    aufwand/aufwanddialog.ui \
    gleichgewicht/gleichgewichtwindow.ui


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
