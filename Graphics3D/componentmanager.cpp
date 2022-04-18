#include "componentmanager.h"

ComponentManager::ComponentManager(QWidget *parent)
    : QScrollArea(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout;
    addComponentButton = new QPushButton(this);
    stackedWidget = new QStackedWidget(this);

    setLayout(vLayout);
    vLayout->addWidget(addComponentButton);
    vLayout->addWidget(stackedWidget);

    initializeAddComponentMenu();
}

void ComponentManager::initializeAddComponentMenu()
{
    addComponentMenu = new QMenu("Add Component", addComponentButton);

    QMenu *basicShape = new QMenu("Basic shape", addComponentMenu);
        QAction *cone = new QAction("cone", basicShape);
        QAction *cuboid = new QAction("cuboid", basicShape);
        QAction *cylinder = new QAction("cylinder", basicShape);
        QAction *plain = new QAction("plain", basicShape);
        QAction *sphere = new QAction("sphere", basicShape);
        QAction *torus = new QAction("torus", basicShape);

    addComponentMenu->addMenu(basicShape);
        basicShape->addAction(cone);
        basicShape->addAction(cuboid);
        basicShape->addAction(cylinder);
        basicShape->addAction(plain);
        basicShape->addAction(sphere);
        basicShape->addAction(torus);

    connect(torus, &QAction::triggered, this, &ComponentManager::requestBasicShapeTorus);

    addComponentButton->setMenu(addComponentMenu);
}

void ComponentManager::requestBasicShapeTorus()
{
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity();
    Qt3DExtras::QTorusMesh *mesh = new Qt3DExtras::QTorusMesh(entity);
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(entity);
    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform(entity);

    entity->addComponent(mesh);
    entity->addComponent(material);
    entity->addComponent(transform);

    TorusSettingWidget *widget = new TorusSettingWidget(mesh, transform, material, stackedWidget);
    stackedWidget->addWidget(widget);
    emit componentAdded(entity);
}
