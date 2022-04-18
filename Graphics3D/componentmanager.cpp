#include "componentmanager.h"

/* component ---|--- BasicShape ---> BasicShapeSettingWidget
 *
 *
 *
 *
 *
 */

ComponentManager::ComponentManager(QWidget *parent)
    : QScrollArea(parent)
{
    QWidget *contents = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(contents);
    addComponentButton = new QPushButton(contents);
    stackedWidget = new QStackedWidget(contents);
    QSpacerItem *item = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setWidget(contents);
    contents->setLayout(vLayout);
    vLayout->addWidget(addComponentButton);
    vLayout->addWidget(stackedWidget);
    vLayout->addItem(item);

    setWidgetResizable(true);
    contents->setFixedWidth(300);
    initializeAddComponentMenu();
}

void ComponentManager::initializeAddComponentMenu()
{
    addComponentMenu = new QMenu("Add Component", addComponentButton);

    QMenu *basicShape = new QMenu("Basic shape", addComponentMenu);
        QAction *cone = new QAction("cone", basicShape);
        QAction *cuboid = new QAction("cuboid", basicShape);
        QAction *cylinder = new QAction("cylinder", basicShape);
        QAction *plane = new QAction("plane", basicShape);
        QAction *sphere = new QAction("sphere", basicShape);
        QAction *torus = new QAction("torus", basicShape);

    addComponentMenu->addMenu(basicShape);
        basicShape->addAction(cone);
        basicShape->addAction(cuboid);
        basicShape->addAction(cylinder);
        basicShape->addAction(plane);
        basicShape->addAction(sphere);
        basicShape->addAction(torus);

    connect(torus, &QAction::triggered, this, &ComponentManager::requestBasicShapeTorus);
    connect(plane, &QAction::triggered, this, &ComponentManager::requestBasicShapePlane);

    addComponentButton->setMenu(addComponentMenu);
}

void ComponentManager::requestBasicShape(Qt3DRender::QGeometryRenderer *mesh, QWidget *meshWidget)
{
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity();
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(entity);
    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform(entity);
    mesh->setParent(entity);

    entity->addComponent(mesh);
    entity->addComponent(material);
    entity->addComponent(transform);

    BasicShapeSettingWidget *widget = new BasicShapeSettingWidget(mesh, transform, material, meshWidget, this);
    stackedWidget->addWidget(widget);

    emit componentAdded(entity);
}

void ComponentManager::requestBasicShapeTorus()
{
    Qt3DExtras::QTorusMesh *mesh = new Qt3DExtras::QTorusMesh();
    requestBasicShape(mesh, new TorusMeshSettingWidget(mesh));
}

void ComponentManager::requestBasicShapePlane()
{
    Qt3DExtras::QPlaneMesh *mesh = new Qt3DExtras::QPlaneMesh();
    requestBasicShape(mesh, new PlaneMeshSettingWidget(mesh));
}
