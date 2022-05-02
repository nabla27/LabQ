#include "scene3d.h"

#include "custommesh/gridmesh.h"
#include "custommesh/linemesh.h"
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <Qt3DRender/QScreenRayCaster>
#include "custommesh/axisentity.h"
#include "custommesh/surfacegridgeometry.h"
#include "numeric/wave.h"
#include "numeric/equation.h"
#include "numeric/pde.h"
#include "animation/pdequationsettingwidget.h"

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

    //Qt3DCore::QEntity *gridEntity = new Qt3DCore::QEntity(rootEntity);
    //GridMesh *gridMesh = new GridMesh(gridEntity);
    //Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial(gridEntity);
    //Qt3DCore::QTransform *gridTransform = new Qt3DCore::QTransform(gridEntity);
    //Qt3DRender::QObjectPicker *picker = new Qt3DRender::QObjectPicker(gridEntity);
    //Qt3DRender::QScreenRayCaster *ray = new Qt3DRender::QScreenRayCaster(gridEntity);
    //gridEntity->addComponent(gridMesh);
    //gridEntity->addComponent(material);
    //gridEntity->addComponent(gridTransform);
    //gridEntity->addComponent(picker);
    //gridEntity->addComponent(ray);
    //material->setAmbient(Qt::red);

    //Qt3DCore::QEntity *testEntity = new Qt3DCore::QEntity(rootEntity);
    //SurfaceGridMesh *testMesh = new SurfaceGridMesh(testEntity);
    //Qt3DExtras::QPhongMaterial *testMaterial = new Qt3DExtras::QPhongMaterial(testEntity);

    //testEntity->addComponent(testMesh);
    //testEntity->addComponent(testMaterial);
    //testMaterial->setAmbient(Qt::blue);

    //const size_t grid_x = 500;
    //const size_t grid_y = 500;
    //const float c = 3.14f;
    //const float dx = 1.0f;
    //const float dt = 0.1f;
    //const float startT = 0.0f;
    //const float count = 50;

    //const float init_x = - float(grid_x - 1) * dx / 2.0f;
    //const float init_y = - float(grid_y - 1) * dx / 2.0f;

    //equation::SurfaceObserver observer;
    //equation::WaveStepper stepper(grid_x, grid_y, dx, dt, c);
    //QVector<float> init;

    //observer.setDataSize(50);
    //init.resize(grid_x * grid_y);

    //for(size_t i = 0; i < grid_x; ++i)
    //    for(size_t j = 0; j < grid_y; ++j)
    //        init[i * grid_y + j] = 10 * sin(((dx * i + init_x) / 50) * ((dx * i + init_x) / 50) + ((dx * j + init_y) / 50) * ((dx * j + init_y) / 50));

    //equation::pdEquation(stepper, observer, init, startT, dt, count);

    //testMesh->setSurface(observer.data->at(15), grid_y, grid_x);

    //QString formula = "3.14 * sin(x^2 / 100 + y^2 / 100)";
    //equation::InitWithFormulaExpCondition::Range range;

    //equation::InitWithFormulaExpCondition *init = new equation::InitWithFormulaExpCondition(nullptr);

    //init->calculate(QList<equation::InitWithFormulaExpCondition::Range>() << range,
    //               QStringList() << formula,
    //               200, 200, 0.5f);

    //PDEquationSettingWidget *w = new PDEquationSettingWidget(nullptr);
    //w->show();
}

Scene3D::~Scene3D()
{
    delete rootEntity;
}

void Scene3D::addObject(Qt3DCore::QEntity *entity)
{
    entity->setParent(rootEntity);
}





















