#include "linemesh.h"


LineGeometry::LineGeometry(Qt3DCore::QNode *parent)
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
    positionAttribute->setVertexSize(3);  //(x, y, z)
    positionAttribute->setByteStride(3 * sizeof(float)); //(x,y,z) x float
    positionAttribute->setCount(2); //start to end

    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedShort);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setCount(2);

    addAttribute(positionAttribute);
    addAttribute(indexAttribute);

    QByteArray indexArray;
    indexArray.resize(2 * sizeof(unsigned short));
    unsigned short *indices = reinterpret_cast<unsigned short*>(indexArray.data());
    *indices++ = 0;
    *indices++ = 1;
    indexBuffer->setData(indexArray);

    updateVertices();
}

void LineGeometry::setStartPosition(const QVector3D& start)
{
    this->start = start;
    updateVertices();
}

void LineGeometry::setEndPosition(const QVector3D& end)
{
    this->end = end;
    updateVertices();
}

void LineGeometry::setPosition(const QVector3D& start, const QVector3D& end)
{
    this->start = start;
    this->end = end;
    updateVertices();
}

void LineGeometry::updateVertices()
{
    QByteArray positionArray;
    positionArray.resize(3 * 2 * sizeof(float)); //start(x,y,z), end(x,y,z)
    float *position = reinterpret_cast<float*>(positionArray.data());

    *position++ = start.x();
    *position++ = start.y();
    *position++ = start.z();
    *position++ = end.x();
    *position++ = end.y();
    *position++ = end.z();

    positionBuffer->setData(positionArray);
}





LineMesh::LineMesh(Qt3DCore::QNode *parent)
    : Qt3DRender::QGeometryRenderer(parent)
{
    setGeometry(new LineGeometry(this));

    setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
}











