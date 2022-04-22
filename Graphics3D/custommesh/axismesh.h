#ifndef AXISMESH_H
#define AXISMESH_H

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QGeometry>
#include <Qt3DCore/QTransform>

class AxisGeometry : public Qt3DCore::QGeometry
{
    Q_OBJECT
public:
    AxisGeometry(Qt3DCore::QNode *parent = nullptr);

public:
    void updateVertices();
    float axisLength() const { return length; }

    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QAttribute *colorAttribute;
    Qt3DCore::QAttribute *indexAttribute;
    Qt3DCore::QBuffer *positionBuffer;
    Qt3DCore::QBuffer *indexBuffer;

public slots:
    void setTarget(Qt3DCore::QTransform *transform);
    void setLength(const float length);
    void setCenterPosition(const QVector3D& vec);

private:
    Qt3DCore::QTransform *transform;
    QMetaObject::Connection connection;
    float length = 100.0f;
    QVector3D centerPosition = {0.0f, 0.0f, 0.0f};
    QVector3D colorX = {1.0f, 0.0f, 0.0f}; //red
    QVector3D colorY = {0.0f, 1.0f, 0.0f}; //green
    QVector3D colorZ = {0.0f, 0.0f, 1.0f}; //blue
};






class AxisMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
public:
    AxisMesh(Qt3DCore::QNode *parent = nullptr);

public:
    float length() const { return static_cast<AxisGeometry*>(geometry())->axisLength(); }

public slots:
    void setLength(const float length) { static_cast<AxisGeometry*>(geometry())->setLength(length); }
    void setTarget(Qt3DCore::QTransform *transform) { static_cast<AxisGeometry*>(geometry())->setTarget(transform); }
    void setCentarPosition(const QVector3D& vec) { static_cast<AxisGeometry*>(geometry())->setCenterPosition(vec); }
};







#endif // AXISMESH_H
