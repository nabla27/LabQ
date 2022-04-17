#include "transformsettingwidget.h"


TransformSettingWidget::TransformSettingWidget(Qt3DCore::QTransform *transform,
                                               QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::Layout3DParam *position = new mlayout::Layout3DParam("Position", this);
    mlayout::Layout3DParam *rotation = new mlayout::Layout3DParam("Rotation", this);
    mlayout::Layout3DParam *scale = new mlayout::Layout3DParam("Scale", this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(position);
    vLayout->addLayout(rotation);
    vLayout->addLayout(scale);
    vLayout->addItem(spacer);

    rotation->setQuaternionValue(transform->rotation());
    scale->setV3Value(transform->scale3D());

    connect(rotation, &mlayout::Layout3DParam::xEdited, transform, &Qt3DCore::QTransform::setRotationX);
    connect(rotation, &mlayout::Layout3DParam::yEdited, transform, &Qt3DCore::QTransform::setRotationY);
    connect(rotation, &mlayout::Layout3DParam::zEdited, transform, &Qt3DCore::QTransform::setRotationZ);
    connect(scale, &mlayout::Layout3DParam::xyzEditedVector, transform, &Qt3DCore::QTransform::setScale3D);
    connect(transform, &Qt3DCore::QTransform::rotationXChanged, rotation, &mlayout::Layout3DParam::setX);
    connect(transform, &Qt3DCore::QTransform::rotationYChanged, rotation, &mlayout::Layout3DParam::setY);
    connect(transform, &Qt3DCore::QTransform::rotationZChanged, rotation, &mlayout::Layout3DParam::setZ);
    connect(transform, &Qt3DCore::QTransform::scale3DChanged, scale, &mlayout::Layout3DParam::setV3Value);

    vLayout->setContentsMargins(0, 0, 0, 0);
}


