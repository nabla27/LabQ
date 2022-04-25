SUBDIRS += \
    $$PWD/Graphics3D.pro

HEADERS += \
    $$PWD/componentmanager.h \
    $$PWD/controllerpanel.h \
    $$PWD/graphics3d.h \
    $$PWD/managerwidget.h \
    $$PWD/scene3d.h \
    $$PWD/scenemanager.h

SOURCES += \
    $$PWD/componentmanager.cpp \
    $$PWD/controllerpanel.cpp \
    $$PWD/graphics3d.cpp \
    $$PWD/main.cpp \
    $$PWD/managerwidget.cpp \
    $$PWD/scene3d.cpp \
    $$PWD/scenemanager.cpp


include(numeric/numeric.pri)
include(itemsettingwidget/itemsettingwidget.pri)
include(custommesh/custommesh.pri)
include(animation/animation.pri)

RESOURCES += \
    $$PWD/equation.qrc
