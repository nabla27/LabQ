#include "graphics3d.h"

Graphics3D::Graphics3D(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.5, 0.5));

    initializeLayout();
}

void Graphics3D::initializeLayout()
{
    if(centralWidget()) delete centralWidget();

    QWidget *widget = new QWidget(this);
    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;

    controllerPanel = new ControllerPanel(widget);
    scene3d = new Scene3D();
    scene3dWidget = QWidget::createWindowContainer(scene3d);
    managerWidget = new QTabWidget(widget);
    sceneManager = new SceneManager(managerWidget);
    componentManager = new ComponentManager(managerWidget);

    setCentralWidget(widget);
    widget->setLayout(hLayout);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(managerWidget);
    vLayout->addWidget(controllerPanel);
    vLayout->addWidget(scene3dWidget);
    managerWidget->addTab(sceneManager, "Scene");
    managerWidget->addTab(componentManager, "Component");

    managerWidget->setFixedWidth(330);

    connect(componentManager, &ComponentManager::objectAdded, scene3d, &Scene3D::addObject);
    connect(componentManager, &ComponentManager::animationAdded, controllerPanel, &ControllerPanel::addAnimation);
}








