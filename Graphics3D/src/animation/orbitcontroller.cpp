#include "orbitcontroller.h"

static const int label_width = 100;

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












OrbitAnimationSettingWidget::OrbitAnimationSettingWidget(PropertyAnimation *animation, Qt3DCore::QTransform *transform, QWidget *parent)
    : QGroupBox(parent)
    , controller(new OrbitController(transform))
    , animation(animation)
{
    controller->setTarget(transform);
    animation->setTargetObject(controller);
    animation->setPropertyName("angle");

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    PropertyControllerLayout *cLayout = new PropertyControllerLayout(animation, this);
    mlayout::DoubleSbLayout *radius = new mlayout::DoubleSbLayout("Radius", this, label_width);
    PropertyAnimationSettingLayout *pLayout = new PropertyAnimationSettingLayout(animation, this, "angle", label_width);

    setLayout(vLayout);
    vLayout->addLayout(cLayout);
    vLayout->addLayout(radius);
    vLayout->addLayout(pLayout);

    radius->setSpinBoxMaxValue(100000);
    radius->setSpinBoxMinValue(0.00);

    radius->setValue(controller->radius());

    connect(radius, &mlayout::DoubleSbLayout::valueChanged, controller, &OrbitController::setRadius);
}





