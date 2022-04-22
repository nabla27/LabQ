#ifndef SURFACESQUAREMESH_H
#define SURFACESQUAREMESH_H

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QGeometry>

class SurfaceSquareGeometry : public Qt3DCore::QGeometry
{
    Q_OBJECT
public:
    SurfaceSquareGeometry(Qt3DCore::QNode *parent);

public:
    void updateVertices();

    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QAttribute *indexAttribute;
    Qt3DCore::QBuffer *positionBuffer;
    Qt3DCore::QBuffer *indexBuffer;


};

#endif // SURFACESQUAREMESH_H
