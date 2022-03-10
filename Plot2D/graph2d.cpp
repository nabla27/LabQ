#include "graph2d.h"

Graph2D::Graph2D()
{
    graph = new QChart;
}

Graph2D::~Graph2D()
{

}

void Graph2D::setAxis(const AxisType type, const AxisAlign align)
{
    QAbstractAxis *axis;

    switch(type)
    {
    case AxisType::Value:
        axis = new QValueAxis;
        break;
    case AxisType::BarCategory:
        axis = new QBarCategoryAxis;
        break;
    case AxisType::Category:
        axis = new QCategoryAxis;
        break;
    case AxisType::DateTime:
        axis = new QDateTimeAxis;
        break;
    case AxisType::LogValue:
        axis = new QLogValueAxis;
        break;
    case AxisType::Color:
        axis = new QColorAxis;
        break;
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "invalid enum number of AxisType.";
        return;
    }

    switch(align)
    {
    case AxisAlign::Left:
        graph->addAxis(axis, Qt::AlignLeft);
        break;
    case AxisAlign::Right:
        graph->addAxis(axis, Qt::AlignRight);
        break;
    case AxisAlign::Bottom:
        graph->addAxis(axis, Qt::AlignBottom);
        break;
    case AxisAlign::Top:
        graph->addAxis(axis, Qt::AlignTop);
        break;
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "invalid enum number of AxisAlign";
        return;
    }

    attachAxisToSeries(axis);
}

void Graph2D::addSeries(const QList<QList<double>>& data, const SeriesType type)
{
    QAbstractSeries *series;

    switch(type)
    {
    case SeriesType::Line:
    {
        series = new QLineSeries;

        for(const QList<double>& row : data){
            if(row.size() < 2)  continue;
            qobject_cast<QLineSeries*>(series)->append(row.at(0), row.at(1));
        }
        break;
    }
    case SeriesType::Area:
    {
        QLineSeries *lower = new QLineSeries;
        QLineSeries *upper = new QLineSeries;

        for(const QList<double>& row : data){
            if(row.size() > 1) upper->append(row.at(0), row.at(1));
            if(row.size() > 2) lower->append(row.at(0), row.at(2));
            else lower->append(row.at(0), 0);
        }
        series = new QAreaSeries(upper, lower);

        break;
    }
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "invalid enum number of SeriesType";
        return;
    }

    graph->addSeries(series);
    attachSeriesToAxis(series);
}


void Graph2D::attachAxisToSeries(QAbstractAxis *axis)
{
    for(QAbstractSeries *series : graph->series())
        series->attachAxis(axis);
}

void Graph2D::attachSeriesToAxis(QAbstractSeries *series)
{
    for(QAbstractAxis *axis : graph->axes(Qt::Horizontal))
        series->attachAxis(axis);
    for(QAbstractAxis *axis : graph->axes(Qt::Vertical))
        series->attachAxis(axis);
}
















