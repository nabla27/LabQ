QT       += core gui \
            datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LabQHome/layoutparts.cpp \
    ../LabQHome/utility.cpp \
    controllerpanel.cpp \
    graph3d.cpp \
    main.cpp \
    plot3d.cpp \
    settingpanel.cpp \
    settingwidget.cpp

HEADERS += \
    ../LabQHome/iofile.h \
    ../LabQHome/layoutparts.h \
    ../LabQHome/utility.h \
    controllerpanel.h \
    graph3d.h \
    plot3d.h \
    settingpanel.h \
    settingwidget.h

FORMS +=

INCLUDEPATH += E:/repos/qt_project/LabQ/LabQHome

RESOURCES += icon/icon_play.png \
             icon/icon_stop.png

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
