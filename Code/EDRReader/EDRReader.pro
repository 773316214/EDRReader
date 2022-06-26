QT       += core gui printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION = 1.0.0

SOURCES += \
    CenterWindow/centerwindow.cpp \
    Log/flog.cpp \
    Log/src/easylogging++.cc \
    QCustomPlot/fcustomplot.cpp \
    QCustomPlot/qcustomplot.cpp \
    Serial/masterthread.cpp \
    Serial/slavethread.cpp \
    Universal/universal.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CenterWindow/centerwindow.h \
    CenterWindow/dataconfiguration.h \
    Log/flog.h \
    Log/src/easylogging++.h \
    QCustomPlot/fcustomplot.h \
    QCustomPlot/qcustomplot.h \
    Serial/masterthread.h \
    Serial/slavethread.h \
    Universal/universal.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/StytleSheet.qrc

DISTFILES += \
    Test/0216.zudslog \
    Test/0217.zudslog \
    Test/0218.zudslog \
    Test/0219.zudslog \
    Test/FA13.zudslog \
    Test/FA14.zudslog \
    Test/FA15.zudslog
