#ifndef GRAPH3D_H
#define GRAPH3D_H
#include <QObject>

#include <Q3DSurface>
#include <QValue3DAxis>
#include <QSurfaceDataProxy>
#include <QSurfaceDataArray>
#include <QSurfaceDataRow>
#include <QVector3D>

#include <QFileDialog>
#include <QFile>
#include "iofile.h"

/*
 * QValue3DAxis |--- QCategory3DAxis
 *              |--- QValue3DAxis
 *
 *
 *
 */

class Graph3D : public QObject
{
    Q_OBJECT
public:
    explicit Graph3D(Q3DSurface *graph, QObject *parent = nullptr);

public slots:
    void readCsvStaticData();

private:
    Q3DSurface *graph;
    QValue3DAxis *axisX;
    QValue3DAxis *axisY;
    QValue3DAxis *axisZ;

signals:

};

#endif // GRAPH3D_H
