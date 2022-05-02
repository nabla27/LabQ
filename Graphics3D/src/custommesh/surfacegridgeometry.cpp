#include "surfacegridgeometry.h"

SurfaceGridGeometry::SurfaceGridGeometry(Qt3DCore::QNode *parent)
    : Qt3DCore::QGeometry(parent)
    , positionAttribute(new Qt3DCore::QAttribute(this))
    , indexAttribute(new Qt3DCore::QAttribute(this))
    , positionBuffer(new Qt3DCore::QBuffer(this))
    , indexBuffer(new Qt3DCore::QBuffer(this))
{
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(positionBuffer);
    positionAttribute->setVertexSize(3); //(x,y,z)
    positionAttribute->setByteStride(3 * sizeof(float)); //(x,y,z)

    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);

    addAttribute(positionAttribute);
    addAttribute(indexAttribute);
}

void SurfaceGridGeometry::setSurface(const QVector<float>& data/*, const unsigned int row, const unsigned int col*/)
{
    const qsizetype dataSize = rowCount * colCount;

    QByteArray positionArray;
    positionArray.resize(3 * dataSize * sizeof(float)); //(x,y,z) * 格子数 * float
    float *position = reinterpret_cast<float*>(positionArray.data());

    //xy平面の角
    const float originX = - ((rowCount - 1.0f) / 2.0f) * stride;
    const float originY = - ((colCount - 1.0f) / 2.0f) * stride;

    for(unsigned int i = 0; i < rowCount; ++i) {
        for(unsigned int j = 0; j < colCount; ++j)
        {
            const float x = stride * i + originX;
            const float y = stride * j + originY;
            const qsizetype index = colCount * i + j;

            *position++ = x;
            *position++ = data.at(index);
            *position++ = y;
        }
    }

    positionBuffer->setData(positionArray);
    positionAttribute->setCount(dataSize);
}

void SurfaceGridGeometry::setStride(const float stride)
{
    if(qFuzzyCompare(this->stride, stride)) return;

    this->stride = stride;
}

void SurfaceGridGeometry::setInitState(const unsigned int row, const unsigned int col, const QVector<float> &state)
{
    rowCount = row;
    colCount = col;
    setSurface(state);
    updateIndices();
}

void SurfaceGridGeometry::updateIndices()
{
    //頂点インデックスの数 = 2*(2*(row*col) - (row+col))
    const unsigned int vertexIndexCount = 2 * (2 * rowCount * colCount - rowCount - colCount);

    QByteArray indexArray;
    indexArray.resize(vertexIndexCount * sizeof(unsigned int));
    unsigned int *index = reinterpret_cast<unsigned int*>(indexArray.data());


    /*
     *  row-1行,col-1列までの各頂点を起点に、それぞれ行方向、列方向のとなりのインデックスと結んでいく。
     *
     *  起点 ------->
     *      |   ____ ____ ____  col
     *      |  |    |    |
     *      |  |____|____|____
     *      v  |    |    |
     *         |    |    |
     *
     *       row
     */
    const unsigned int row_1 = rowCount - 1;
    const unsigned int col_1 = colCount - 1;

    for(unsigned int i = 0; i < row_1; ++i)
        for(unsigned int j = 0; j < col_1; ++j)
        {
            const unsigned int k = colCount * i + j;
            //kを起点に右(列方向)隣のインデックスと結ぶ
            *index++ = k;
            *index++ = k + 1;
            //kを起点に下(行方向)隣のインデックスと結ぶ
            *index++ = k;
            *index++ = k + colCount;
        }


    /* 余った下端(最終行)のインデックスを結ぶ */
    for(qsizetype j = 0; j < col_1; ++j)
    {
        const unsigned int i = colCount * row_1 + j; //j=0の場合、左下角のインデックス
        *index++ = i;
        *index++ = i + 1;
    }

    /* 余った右端(最終列)のインデックスを結ぶ */
    for(qsizetype i = 0; i < row_1; ++i)
    {
        const unsigned int j = colCount * (i + 1) - 1;
        *index++ = j;
        *index++ = j + colCount;
    }

    indexBuffer->setData(indexArray);
    indexAttribute->setCount(vertexIndexCount);
}











SurfaceGridMesh::SurfaceGridMesh(Qt3DCore::QNode *parent)
    : Qt3DRender::QGeometryRenderer(parent)
{
    setGeometry(new SurfaceGridGeometry(this));

    setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
}











