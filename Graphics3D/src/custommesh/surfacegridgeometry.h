#ifndef SURFACEGRIDGEOMETRY_H
#define SURFACEGRIDGEOMETRY_H

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QGeometry>


class SurfaceGridGeometry : public  Qt3DCore::QGeometry
{
    Q_OBJECT
public:
    SurfaceGridGeometry(Qt3DCore::QNode *parent = nullptr);

public:
    void setStride(const float stride);
    void setSurface(const QVector<float>& data);
    void setInitState(const unsigned int row, const unsigned int col, const QVector<float>& state);

private:
    void updateIndices();

    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QAttribute *indexAttribute;
    Qt3DCore::QBuffer *positionBuffer;
    Qt3DCore::QBuffer *indexBuffer;

    unsigned int rowCount = 0;
    unsigned int colCount = 0;
    float stride = 0.5f;
};






class SurfaceGridMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
public:
    SurfaceGridMesh(Qt3DCore::QNode *parent = nullptr);

public slots:

    void setStride(const float stride)
    { static_cast<SurfaceGridGeometry*>(geometry())->setStride(stride); }

    void setSurface(const QVector<float>& data)
    { static_cast<SurfaceGridGeometry*>(geometry())->setSurface(data); }

    void setInitState(const unsigned int row, const unsigned int col, const QVector<float>& state)
    { static_cast<SurfaceGridGeometry*>(geometry())->setInitState(row, col, state); }
};

















#endif // SURFACEGRIDGEOMETRY_H
