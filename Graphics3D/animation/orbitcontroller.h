#ifndef ORBITCONTROLLER_H
#define ORBITCONTROLLER_H

#include <QObject>
#include <QGroupBox>
#include <Qt3DCore/QTransform>
#include "layoutparts.h"
#include "property_animation_setting.h"

class OrbitController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)

public:
    explicit OrbitController(QObject *parent = nullptr);

    void setTarget(Qt3DCore::QTransform *target);
    void setRadius(const float radius);
    void setAngle(const float angle);

    Qt3DCore::QTransform *target() const { return _target; }
    float radius() const { return _radius; }
    float angle() const { return _angle; }

private:
    void updateMatrix();

private:
    Qt3DCore::QTransform *_target;
    QMatrix4x4 _matrix;
    float _radius;
    float _angle;

signals:
    void targetChanged();
    void radiusChanged();
    void angleChanged();
};





class OrbitAnimationSettingWidget : public QGroupBox
{
    Q_OBJECT
public:
    OrbitAnimationSettingWidget(PropertyAnimation *animation, Qt3DCore::QTransform *transform, QWidget *parent);

private:
    OrbitController *controller;
    PropertyAnimation *animation;
    void initAnimation();

signals:
    void indexChanged(const int index);
};





#endif // ORBITCONTROLLER_H
