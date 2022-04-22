#include "axisentity.h"

AxisEntity::AxisEntity(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , transform(nullptr)
{
    Qt3DCore::QEntity *xconeEntity = new Qt3DCore::QEntity(this);
    Qt3DCore::QEntity *yconeEntity = new Qt3DCore::QEntity(this);
    Qt3DCore::QEntity *zconeEntity = new Qt3DCore::QEntity(this);
    Qt3DCore::QEntity *xpoleEntity = new Qt3DCore::QEntity(this);
    Qt3DCore::QEntity *ypoleEntity = new Qt3DCore::QEntity(this);
    Qt3DCore::QEntity *zpoleEntity = new Qt3DCore::QEntity(this);

    xcone = new Qt3DExtras::QConeMesh(xconeEntity);
    ycone = new Qt3DExtras::QConeMesh(yconeEntity);
    zcone = new Qt3DExtras::QConeMesh(zconeEntity);;
    xpole = new Qt3DExtras::QCylinderMesh(xpoleEntity);
    ypole = new Qt3DExtras::QCylinderMesh(ypoleEntity);;
    zpole = new Qt3DExtras::QCylinderMesh(zpoleEntity);;

    Qt3DExtras::QPhongMaterial *xmaterial = new Qt3DExtras::QPhongMaterial;
    Qt3DExtras::QPhongMaterial *ymaterial = new Qt3DExtras::QPhongMaterial;
    Qt3DExtras::QPhongMaterial *zmaterial = new Qt3DExtras::QPhongMaterial;

    xconetransform = new Qt3DCore::QTransform(xconeEntity);
    yconetransform = new Qt3DCore::QTransform(yconeEntity);
    zconetransform = new Qt3DCore::QTransform(zconeEntity);
    xpoletransform = new Qt3DCore::QTransform(xpoleEntity);
    ypoletransform = new Qt3DCore::QTransform(ypoleEntity);
    zpoletransform = new Qt3DCore::QTransform(zpoleEntity);

    xconeEntity->addComponent(xcone);
    xconeEntity->addComponent(xmaterial);
    xconeEntity->addComponent(xconetransform);

    yconeEntity->addComponent(ycone);
    yconeEntity->addComponent(ymaterial);
    yconeEntity->addComponent(yconetransform);

    zconeEntity->addComponent(zcone);
    zconeEntity->addComponent(zmaterial);
    zconeEntity->addComponent(zconetransform);

    xpoleEntity->addComponent(xpole);
    xpoleEntity->addComponent(xmaterial);
    xpoleEntity->addComponent(xpoletransform);

    ypoleEntity->addComponent(ypole);
    ypoleEntity->addComponent(ymaterial);
    ypoleEntity->addComponent(ypoletransform);

    zpoleEntity->addComponent(zpole);
    zpoleEntity->addComponent(zmaterial);
    zpoleEntity->addComponent(zpoletransform);

    xconetransform->setRotationZ(-90.0f);
    zconetransform->setRotationX(90.0f);
    xpoletransform->setRotationZ(90.0f);
    zpoletransform->setRotationX(90.0f);

    xmaterial->setAmbient(Qt::red);
    ymaterial->setAmbient(Qt::green);
    zmaterial->setAmbient(Qt::blue);

    updateShape();
}

void AxisEntity::updateShape()
{
    xconetransform->setTranslation(QVector3D(length + coneLength() * 0.5f, 0, 0));
    yconetransform->setTranslation(QVector3D(0, length + coneLength() * 0.5f, 0));
    zconetransform->setTranslation(QVector3D(0, 0, length + coneLength() * 0.5f));

    xpoletransform->setTranslation(QVector3D(length / 2.0f, 0, 0));
    ypoletransform->setTranslation(QVector3D(0, length / 2.0f, 0));
    zpoletransform->setTranslation(QVector3D(0, 0, length / 2.0f));

    xpole->setLength(length);
    ypole->setLength(length);
    zpole->setLength(length);

    xpole->setRadius(radius);
    ypole->setRadius(radius);
    zpole->setRadius(radius);

    xcone->setBottomRadius(radius + coneDiff());
    ycone->setBottomRadius(radius + coneDiff());
    zcone->setBottomRadius(radius + coneDiff());

    xcone->setLength(coneLength());
    ycone->setLength(coneLength());
    zcone->setLength(coneLength());
}


void AxisEntity::setRadius(const float &radius)
{
    this->radius = radius;
    updateShape();
}


void AxisEntity::setLength(const float &length)
{
    this->length = length;
    updateShape();
}



