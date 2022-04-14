#ifndef SCENE3D_H
#define SCENE3D_H
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>


class Scene3D : public Qt3DExtras::Qt3DWindow
{
public:
    Scene3D();
    ~Scene3D();

private:
    Qt3DCore::QEntity *rootEntity;
    Qt3DRender::QCamera *cameraEntity;
};

#endif // SCENE3D_H
