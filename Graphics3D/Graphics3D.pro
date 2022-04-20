QT       += core gui \
            3dcore \
            3dextras \
            3drender

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LabQHome/layoutparts.cpp \
    ../LabQHome/utility.cpp \
    componentmanager.cpp \
    contorollerpanel.cpp \
    graphics3d.cpp \
    main.cpp \
    scene3d.cpp \
    scenemanager.cpp

HEADERS += \
    ../LabQHome/layoutparts.h \
    ../LabQHome/utility.h \
    componentmanager.h \
    contorollerpanel.h \
    graphics3d.h \
    scene3d.h \
    scenemanager.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += E:/repos/qt_project/LabQ/LabQHome

include(itemsettingwidget/itemsettingwidget.pri)
include(custommesh/custommesh.pri)
include(animation/animation.pri)
