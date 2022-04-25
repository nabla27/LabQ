#include "axismesh.h"

AxisGeometry::AxisGeometry(Qt3DCore::QNode *parent)
    : Qt3DCore::QGeometry(parent)
    , positionAttribute(new Qt3DCore::QAttribute(this))
    , colorAttribute(new Qt3DCore::QAttribute(this))
    , indexAttribute(new Qt3DCore::QAttribute(this))
    , positionBuffer(new Qt3DCore::QBuffer(this))
    , indexBuffer(new Qt3DCore::QBuffer(this))
    , transform(nullptr)
{
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(positionBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setVertexSize(3); //(x,y,z)
    positionAttribute->setByteStride(3 * 2 * sizeof(float)); //position(x,y,z) + color(r,g,b)
    positionAttribute->setCount(3 * 2); //(x+y+z) * 2

    colorAttribute->setName(Qt3DCore::QAttribute::defaultColorAttributeName());
    colorAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    colorAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    colorAttribute->setBuffer(positionBuffer);
    colorAttribute->setByteOffset(3 * sizeof(float)); //position(x,y,z)
    colorAttribute->setVertexSize(3); //(r,g,b)
    colorAttribute->setByteStride(3 * 2 * sizeof(float)); //position(x,y,z) + color(r,g,b)
    colorAttribute->setCount(3 * 2); //(x+y+z) * 2

    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedShort);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setByteOffset(0);
    indexAttribute->setByteStride(0);
    indexAttribute->setCount(3 * 2 * 2);

    addAttribute(positionAttribute);
    addAttribute(indexAttribute);

    QByteArray indexArray;
    indexArray.resize(3 * 2 * 2 * sizeof(unsigned short)); //((x,y,z) + (r,g,b)) * 2
    unsigned short *indices = reinterpret_cast<unsigned short*>(indexArray.data());
    for(unsigned short i = 0; i < 12; ++i)
        *indices++ = i;
    indexBuffer->setData(indexArray);

    updateVertices();
}

void AxisGeometry::updateVertices()
{
    QByteArray vertexArray;
    vertexArray.resize(3 * 2 * 3 * 2 * sizeof(float)); //一軸当たり(x,y,z)と(r,g,b)の指定を始点と終点の2点
    float *data = reinterpret_cast<float*>(vertexArray.data());

    QVector3D axisX(centerPosition.x() + length, 0.0f, 0.0f);
    QVector3D axisY(0.0f, centerPosition.y() + length, 0.0f);
    QVector3D axisZ(0.0f, 0.0f, centerPosition.z() + length);

    QVector<QVector3D> vertexList;
    QVector<QVector3D> colorList;

    vertexList << axisX << axisY << axisZ;
    colorList << colorX << colorY << colorZ;

    for(size_t i = 0; i < 3; ++i)
    {
        *data++ = centerPosition.x();
        *data++ = centerPosition.y();
        *data++ = centerPosition.z();
        *data++ = vertexList.at(i).x();
        *data++ = vertexList.at(i).y();
        *data++ = vertexList.at(i).z();

        *data++ = colorList.at(i).x();
        *data++ = colorList.at(i).y();
        *data++ = colorList.at(i).z();
        *data++ = colorList.at(i).x();
        *data++ = colorList.at(i).y();
        *data++ = colorList.at(i).z();
    }

    positionBuffer->setData(vertexArray);
}

void AxisGeometry::setTarget(Qt3DCore::QTransform *transform)
{
    if(this->transform == transform) return;

    this->transform = transform;
    disconnect(connection);
    connection = connect(transform, &Qt3DCore::QTransform::translationChanged, this, &AxisGeometry::setCenterPosition);
}

void AxisGeometry::setLength(const float length)
{
    this->length = length;
    updateVertices();
}

void AxisGeometry::setCenterPosition(const QVector3D& vec)
{
    centerPosition = vec;
    updateVertices();
}






AxisMesh::AxisMesh(Qt3DCore::QNode *parent)
    : Qt3DRender::QGeometryRenderer(parent)
{
    setGeometry(new AxisGeometry(this));

    setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
}



