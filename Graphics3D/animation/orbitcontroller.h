#ifndef ORBITCONTROLLER_H
#define ORBITCONTROLLER_H

#include <QObject>
#include <Qt3DCore/QTransform>

class OrbitController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)

public:
    explicit OrbitController(QObject *parent = nullptr);

    void setTarget(Qt3DCore::QTransform *target);
    Qt3DCore::QTransform *target() const;

    void setRadius(const float radius);
    float radius() const;

    void setAngle(const float angle);
    float angle() const;

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

#endif // ORBITCONTROLLER_H
