#include "scene3d.h"

Scene3D::Scene3D()
{
    rootEntity = new Qt3DCore::QEntity();

    cameraEntity = this->camera();
}

Scene3D::~Scene3D()
{
    delete rootEntity;
    delete cameraEntity;
}
