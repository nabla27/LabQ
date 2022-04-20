#include "gridmesh.h"

/*
 *        y
 *        |
 *        |
 *        |_______x
 *       /
 *      /     _ _ _ _ _ _ _ _ _      _____
 *     /    /_/_/_/_/_/_/_/_/_/      _____ stride
 *    z    /_/_/_/_/_/_/_/_/_/
 *        /_/_/_/_/_/_/_/_/_/
 *       /_/_/_/_/_/_/_/_/_/ height
 *      /_/_/_/_/_/_/_/_/_/
 *     /_/_/_/_/_/_/_/_/_/
 *    /_/_/_/_/_/_/_/_/_/
 *          width
 *
 */

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
    const unsigned int vertexCount = this->vertexCount();

    QByteArray positionArray;
    positionArray.resize(3 * vertexCount * sizeof(float)); //(x,y,z) * 端数 * float
    float *position = reinterpret_cast<float *>(positionArray.data());

    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;

    /* 中心(0,0)をクロスする軸 */
    //x軸に平行な軸
    *position++ = -halfWidth;
    *position++ = 0.0f;
    *position++ = 0.0f;
    *position++ = halfWidth;
    *position++ = 0.0f;
    *position++ = 0.0f;
    //z軸に平行な軸
    *position++ = 0.0f;
    *position++ = 0.0f;
    *position++ = -halfHeight;
    *position++ = 0.0f;
    *position++ = 0.0f;
    *position++ = halfHeight;

    /* 平面半分側の軸の数(中心軸を除く) */
    const unsigned int xGridHalfCount = height / stride / 2.0f;
    const unsigned int zGridHalfCount = width / stride / 2.0f;

    /* x軸に水平な軸。中心軸から左右に軸を生成していく */
    for(unsigned int i = 1; i <= xGridHalfCount; ++i)
    {
        const float z = i * stride;
        //+z側の軸
        *position++ = -halfWidth;
        *position++ = 0.0f;
        *position++ = z;
        *position++ = halfWidth;
        *position++ = 0.0f;
        *position++ = z;
        //-z側の軸
        *position++ = -halfWidth;
        *position++ = 0.0f;
        *position++ = -z;
        *position++ = halfWidth;
        *position++ = 0.0f;
        *position++ = -z;
    }

    /* z軸に平行な軸。中心軸から左右に軸を生成 */
    for(unsigned int i = 1; i <= zGridHalfCount; ++i)
    {
        const float x = i * stride;
        //+x方向
        *position++ = x;
        *position++ = 0.0f;
        *position++ = -halfHeight;
        *position++ = x;
        *position++ = 0.0f;
        *position++ = halfHeight;
        //-x方向
        *position++ = -x;
        *position++ = 0.0f;
        *position++ = -halfHeight;
        *position++ = -x;
        *position++ = 0.0f;
        *position++ = halfHeight;
    }

    positionBuffer->setData(positionArray);
    positionAttribute->setCount(vertexCount);
}

void GridGeometry::updateIndices()
{
    const unsigned int vertexCount = this->vertexCount();

    QByteArray indexArray;
    indexArray.resize(vertexCount * sizeof(unsigned int));
    unsigned int *index = reinterpret_cast<unsigned int*>(indexArray.data());

    for(unsigned int i = 0; i < vertexCount; ++i)
        *index++ = i;

    indexBuffer->setData(indexArray);
    indexAttribute->setCount(vertexCount);
}





GridMesh::GridMesh(Qt3DCore::QNode *parent)
    : Qt3DRender::QGeometryRenderer(parent)
{
    setGeometry(new GridGeometry(this));

    setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
}





