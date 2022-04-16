#ifndef SCENE3D_H
#define SCENE3D_H
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QConeGeometry>

#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QOrbitCameraController>

class Scene3D : public Qt3DExtras::Qt3DWindow
{
public:
    Scene3D();
    ~Scene3D();

public:
    void addComponent(Qt3DCore::QEntity *entity) { entity->setParent(rootEntity); }

private:
    Qt3DCore::QEntity *rootEntity;
    Qt3DRender::QCamera *cameraEntity;
    Qt3DExtras::QOrbitCameraController *camController;
};

#endif // SCENE3D_H
