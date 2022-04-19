#ifndef LINEMESH_H
#define LINEMESH_H

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QGeometry>


class LineGeometry : public Qt3DCore::QGeometry
{
    Q_OBJECT
public:
    LineGeometry(Qt3DCore::QNode *parent = nullptr);

public:
    void updateVertices();

    QVector3D startPosition() const { return start; }
    QVector3D endPosition() const { return end; }

    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QAttribute *indexAttribute;
    Qt3DCore::QBuffer *positionBuffer;
    Qt3DCore::QBuffer *indexBuffer;

public slots:
    void setStartPosition(const QVector3D& start);
    void setEndPosition(const QVector3D& end);
    void setPosition(const QVector3D& start, const QVector3D& end);

private:
    QVector3D start = {10, 0, 0};
    QVector3D end = {0, 0, 0};
};



class LineMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
public:
    LineMesh(Qt3DCore::QNode *parent = nullptr);

public:
    QVector3D startPosition() const { return static_cast<LineGeometry*>(geometry())->startPosition(); }
    QVector3D endPosition() const { return static_cast<LineGeometry*>(geometry())->endPosition(); }

public slots:
    void setStartPosition(const QVector3D& start) { static_cast<LineGeometry*>(geometry())->setStartPosition(start); }
    void setEndPosition(const QVector3D& end) { static_cast<LineGeometry*>(geometry())->setEndPosition(end); }
    void setPosition(const QVector3D& start, const QVector3D& end) { static_cast<LineGeometry*>(geometry())->setPosition(start, end); }
};



#endif // LINEMESH_H
