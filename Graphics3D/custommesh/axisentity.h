#ifndef AXISENTITY_H
#define AXISENTITY_H

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>

class AxisEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    AxisEntity(Qt3DCore::QNode *parent = nullptr);

public:
    void setRadius(const float& radius);
    void setLength(const float& length);
    void setTransform(Qt3DCore::QTransform *transform) { this->transform = transform;
                                                         addComponent(transform); }
    void removeTransform() { removeComponent(transform);
                             transform = nullptr; }

private:
    Qt3DExtras::QConeMesh *xcone;
    Qt3DExtras::QConeMesh *ycone;
    Qt3DExtras::QConeMesh *zcone;
    Qt3DExtras::QCylinderMesh *xpole;
    Qt3DExtras::QCylinderMesh *ypole;
    Qt3DExtras::QCylinderMesh *zpole;
    Qt3DCore::QTransform *xconetransform;
    Qt3DCore::QTransform *yconetransform;
    Qt3DCore::QTransform *zconetransform;
    Qt3DCore::QTransform *xpoletransform;
    Qt3DCore::QTransform *ypoletransform;
    Qt3DCore::QTransform *zpoletransform;

    void updateShape();
    float coneLength() const { return radius * 5.3f; }
    float coneDiff() const { return radius * 0.6f; }

    float length = 10.0f;
    float radius = 0.2f;

    Qt3DCore::QTransform *transform;
};

#endif // AXISENTITY_H
