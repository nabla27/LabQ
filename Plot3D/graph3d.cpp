#include "graph3d.h"

Graph3D::Graph3D(Q3DSurface *graph, QObject *parent)
    : QObject{parent}, graph(graph)
{
    axisX = new QValue3DAxis(graph);
    axisY = new QValue3DAxis(graph);
    axisZ = new QValue3DAxis(graph);

    graph->addAxis(axisX);
    graph->addAxis(axisY);
    graph->addAxis(axisZ);
}

void Graph3D::readCsvStaticData()
{
#if 0
    const QString filePath = QFileDialog::getOpenFileName(nullptr);
    QString data;
    readFileTxt(filePath, data);

    QSurfaceDataArray *array = new QSurfaceDataArray;
    QString stack;

    for(const QChar& c : data)
    {
        if(c == '\n')
        {

        }
        else if(c == ',')
        {

        }
        else
        {
            stack += c;
        }
    }
#endif

    QSurfaceDataArray *array = new QSurfaceDataArray;

    QSurfaceDataItem *item = new QSurfaceDataItem();

}
