#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <QScrollArea>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenu>
#include <Qt3DCore/QEntity>
#include "itemsettingwidget/basicmeshsettingwidget.h"
#include "itemsettingwidget/basicshapesettingwidget.h"

class ComponentManager : public QScrollArea
{
    Q_OBJECT
public:
    explicit ComponentManager(QWidget *parent = nullptr);

private:
    void initializeAddComponentMenu();

private slots:
    void requestBasicShape(Qt3DRender::QGeometryRenderer *mesh, QWidget *meshWidget);
    void requestBasicShapeTorus();
    void requestBasicShapePlane();

private:
    QPushButton *addComponentButton;
    QMenu *addComponentMenu;
    QStackedWidget *stackedWidget;

signals:
    void componentAdded(Qt3DCore::QEntity *entity);
};

#endif // COMPONENTMANAGER_H
