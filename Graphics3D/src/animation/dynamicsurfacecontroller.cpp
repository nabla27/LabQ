#include "dynamicsurfacecontroller.h"

DynamicSurfaceController::DynamicSurfaceController(QObject *parent)
    : QObject(parent)
    , _target(nullptr)
    , _step(0)
{
}

void DynamicSurfaceController::setTarget(SurfaceGridMesh *geometry)
{
    if(_target == geometry) return;

    _target = geometry;
    emit targetChanged();
}

void DynamicSurfaceController::setStep(const float step)
{
    if(_step == step) return;

    _target->setSurface(data.at(step));

    emit stepChanged();
}


