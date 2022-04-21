#include "scene3d.h"

#include "custommesh/gridmesh.h"

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

    Qt3DCore::QEntity *lineEntity = new Qt3DCore::QEntity(rootEntity);
    GridMesh *lineMesh = new GridMesh(lineEntity);
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial(lineEntity);
    Qt3DCore::QTransform *lineTransform = new Qt3DCore::QTransform(lineEntity);
    lineEntity->addComponent(lineMesh);
    lineEntity->addComponent(material);
    lineEntity->addComponent(lineTransform);
    material->setAmbient(Qt::red);
}

Scene3D::~Scene3D()
{
    delete rootEntity;
}

void Scene3D::addComponent(Qt3DCore::QEntity *entity)
{
    entity->setParent(rootEntity);
}





















