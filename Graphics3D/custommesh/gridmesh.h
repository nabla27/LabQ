#ifndef GRIDMESH_H
#define GRIDMESH_H

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QGeometry>

class GridGeometry : public Qt3DCore::QGeometry
{
    Q_OBJECT
public:
    GridGeometry(Qt3DCore::QNode *parent = nullptr);

public:
    void updateVertices();
    void updateIndices();

    float gridWidth() const { return width; }
    float gridHeight() const { return height; }
    float gridStride() const { return stride; }

    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QAttribute *indexAttribute;
    Qt3DCore::QBuffer *positionBuffer;
    Qt3DCore::QBuffer *indexBuffer;

public slots:
    void setGridWidth(const float& width);
    void setGridHeight(const float& height);
    void setGridStride(const float& stride);

private:
    unsigned int vertexCount() const { return 2 * (unsigned int)((height + width) / stride) + 4; }

private:
    float width = 100.0f;
    float height = 100.0f;
    float stride = 5.0f;
};



class GridMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
public:
    GridMesh(Qt3DCore::QNode *parent = nullptr);

public:
    float gridWidth() const { return static_cast<GridGeometry*>(geometry())->gridWidth(); }
    float gridHeight() const { return static_cast<GridGeometry*>(geometry())->gridHeight(); }
    float gridStride() const { return static_cast<GridGeometry*>(geometry())->gridStride(); }

public slots:
    void setGridWidth(const float& width) { static_cast<GridGeometry*>(geometry())->setGridWidth(width); }
    void setGridHeight(const float& height) { static_cast<GridGeometry*>(geometry())->setGridHeight(height); }
    void setGridStride(const float& stride) { static_cast<GridGeometry*>(geometry())->setGridStride(stride); }
};

#endif // GRIDMESH_H
