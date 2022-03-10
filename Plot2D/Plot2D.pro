QT       += core gui \
            charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LabQHome/layoutparts.cpp \
    ../LabQHome/utility.cpp \
    chartview.cpp \
    graph2d.cpp \
    graphsettingwidget.cpp \
    main.cpp \
    plot2d.cpp

HEADERS += \
    ../LabQHome/layoutparts.h \
    ../LabQHome/utility.h \
    chartview.h \
    graph2d.h \
    graphsettingwidget.h \
    plot2d.h

INCLUDEPATH += E:/repos/qt_project/LabQ/LabQHome

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
