#include "gridmesh.h"


GridGeometry::GridGeometry(Qt3DCore::QNode *parent)
    : Qt3DCore::QGeometry(parent)
{
    positionAttribute = new Qt3DCore::QAttribute(this);
    indexAttribute = new Qt3DCore::QAttribute(this);
    positionBuffer = new Qt3DCore::QBuffer(this);
    indexBuffer = new Qt3DCore::QBuffer(this);

    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(positionBuffer);
    positionAttribute->setVertexSize(3); //(x, y, z)
    positionAttribute->setByteStride(3 * sizeof(float));

    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setVertexSize(3);                    //無くてもよい 合ってる?
    indexAttribute->setByteStride(3 * sizeof(float));    //無くてもよい 合ってる?

    addAttribute(positionAttribute);
    addAttribute(indexAttribute);

    updateVertices();
    updateIndices();
}

void GridGeometry::setGridWidth(const float& width)
{
    this->width = width;
    updateVertices();
    updateIndices();
}

void GridGeometry::setGridHeight(const float& height)
{
    this->height = height;
    updateVertices();
    updateIndices();
}

void GridGeometry::setGridStride(const float& stride)
{
    this->stride = stride;
    updateVertices();
    updateIndices();
}

void GridGeometry::updateVertices()
{
    //const unsigned int widthLineCount = width / stride * 2 + 1;

    QByteArray positionArray;
    positionArray.resize(3 * 4 * sizeof(float));
    float *position = reinterpret_cast<float*>(positionArray.data());

    *position++ = 0;
    *position++ = 0;
    *position++ = -50;
    *position++ = 0;
    *position++ = 0;
    *position++ = 50;
    *position++ = 50;
    *position++ = 0;
    *position++ = 0;
    *position++ = -50;
    *position++ = 0;
    *position++ = 0;

    positionBuffer->setData(positionArray);
    positionAttribute->setCount(4);
}

void GridGeometry::updateIndices()
{
#if 1
    QByteArray indexArray;
    indexArray.resize(4 * sizeof(unsigned int));
    unsigned int *index = reinterpret_cast<unsigned int*>(indexArray.data());

    *index++ = 0;
    *index++ = 1;
    *index++ = 2;
    *index++ = 3;

    indexBuffer->setData(indexArray);
    indexAttribute->setCount(4);
#endif
}





GridMesh::GridMesh(Qt3DCore::QNode *parent)
    : Qt3DRender::QGeometryRenderer(parent)
{
    setGeometry(new GridGeometry(this));

    setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
}





