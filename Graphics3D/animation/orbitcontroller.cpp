#include "orbitcontroller.h"

OrbitController::OrbitController(QObject *parent)
    : QObject(parent)
    , _target(nullptr)
    , _matrix()
    , _radius(1.0f)
    , _angle(0.0f)
{
}

void OrbitController::setTarget(Qt3DCore::QTransform *target)
{
    if(_target == target) return;

    _target = target;
    emit targetChanged();
}

void OrbitController::setRadius(const float radius)
{
    if(qFuzzyCompare(_radius, radius)) return;

    _radius = radius;
    updateMatrix();
    emit radiusChanged();
}

void OrbitController::setAngle(const float angle)
{
    if(qFuzzyCompare(_angle, angle)) return;

    _angle = angle;
    updateMatrix();
    emit angleChanged();
}

void OrbitController::updateMatrix()
{
    _matrix.setToIdentity();
    _matrix.rotate(_angle, QVector3D(0.0f, 1.0f, 0.0f));
    _matrix.translate(_radius, 0, 0);
    _target->setMatrix(_matrix);
}
