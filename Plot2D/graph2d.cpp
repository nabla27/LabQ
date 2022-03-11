#include "graph2d.h"

Graph2D::Graph2D()
{
    graph = new QChart;

    QLineSeries *series = new QLineSeries;
    QList<QPointF> data =
    {
        {1, 2},
        {2, 3},
        {3, 1},
        {4, 2},
        {5, 3},
        {6, 6},
        {7, 5},
    };

    series->append(data);
    graph->addSeries(series);
}

Graph2D::~Graph2D()
{

}

void Graph2D::addAxis(QAbstractAxis *axis, const AxisAlign align)
{
    switch (align)
    {
    case AxisAlign::Left:
        graph->addAxis(axis, Qt::AlignLeft); break;
    case AxisAlign::Bottom:
        graph->addAxis(axis, Qt::AlignBottom); break;
    case AxisAlign::Right:
        graph->addAxis(axis, Qt::AlignRight); break;
    case AxisAlign::Top:
        graph->addAxis(axis, Qt::AlignTop); break;
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "Invalid enum index of AxisAlign";
        return;
    }
}















