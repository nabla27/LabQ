QT       += core gui \
            charts \
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LabQHome/layoutparts.cpp \
    ../LabQHome/utility.cpp \
    main.cpp \
    serialmenubar.cpp \
    serialmonitor.cpp \
    serialplot1d.cpp \
    serialsettingwidget.cpp \
    serialtextbrowser.cpp \
    serialviewtab.cpp

HEADERS += \
    ../LabQHome/iofile.h \
    ../LabQHome/layoutparts.h \
    ../LabQHome/utility.h \
    serialmenubar.h \
    serialmonitor.h \
    serialplot1d.h \
    serialsettingwidget.h \
    serialtextbrowser.h \
    serialviewtab.h

INCLUDEPATH += E:/boost_1_76_0/boost_1_76_0 \
               E:/repos/qt_project/LabQ/LabQHome \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
