#include "scene3d.h"

#include "custommesh/gridmesh.h"
#include "custommesh/linemesh.h"
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <Qt3DRender/QScreenRayCaster>
#include "custommesh/axisentity.h"

Scene3D::Scene3D()
    : rootEntity(new Qt3DCore::QEntity)
    , camController(new Qt3DExtras::QOrbitCameraController(rootEntity))
{
    cameraEntity = this->camera();
    setRootEntity(rootEntity);

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    cameraEntity->setPosition(QVector3D(0, 0, 40.0f));

    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(cameraEntity);

    //camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    //camController->setLinearSpeed(50.0f);
    //camController->setLookSpeed(180.0f);
    //camController->setCamera(cameraEntity);

    Qt3DCore::QEntity *gridEntity = new Qt3DCore::QEntity(rootEntity);
    GridMesh *gridMesh = new GridMesh(gridEntity);
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial(gridEntity);
    Qt3DCore::QTransform *gridTransform = new Qt3DCore::QTransform(gridEntity);
    Qt3DRender::QObjectPicker *picker = new Qt3DRender::QObjectPicker(gridEntity);
    Qt3DRender::QScreenRayCaster *ray = new Qt3DRender::QScreenRayCaster(gridEntity);
    gridEntity->addComponent(gridMesh);
    gridEntity->addComponent(material);
    gridEntity->addComponent(gridTransform);
    gridEntity->addComponent(picker);
    gridEntity->addComponent(ray);
    material->setAmbient(Qt::red);

    connect(picker, &Qt3DRender::QObjectPicker::pressed, [](Qt3DRender::QPickEvent*){ qDebug() << __LINE__; });
    connect(ray, &Qt3DRender::QScreenRayCaster::hitsChanged, [](const Qt3DRender::QAbstractRayCaster::Hits&){ qDebug() << __LINE__; });

    AxisEntity *axis = new AxisEntity(rootEntity);
    axis->setTransform(gridTransform);
}

Scene3D::~Scene3D()
{
    delete rootEntity;
}

void Scene3D::addObject(Qt3DCore::QEntity *entity)
{
    entity->setParent(rootEntity);
}





















