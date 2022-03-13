#include "graph2d.h"

Graph2D::Graph2D()
{
    graph = new QChart;
#if 0
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
#endif
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

void Graph2D::setMarginLeft(const QString& lw)
{
    QMargins margin = graph->margins();
    margin.setLeft(lw.toInt());
    graph->setMargins(margin);
}

void Graph2D::setMarginRight(const QString& rw)
{
    QMargins margin = graph->margins();
    margin.setRight(rw.toInt());
    graph->setMargins(margin);
}

void Graph2D::setMarginBottom(const QString& bh)
{
    QMargins margin = graph->margins();
    margin.setBottom(bh.toInt());
    graph->setMargins(margin);
}

void Graph2D::setMarginTop(const QString& th)
{
    QMargins margin = graph->margins();
    margin.setTop(th.toInt());
    graph->setMargins(margin);
}

void Graph2D::setGraphTitle(const QString& title)
{
    graph->setTitle(title);
}

void Graph2D::setGraphTitleSize(const int ps)
{
    QFont font = graph->titleFont();
    font.setPointSize(ps);
    graph->setTitleFont(font);
}

void Graph2D::setGraphTheme(const int index)
{
    graph->setTheme(QChart::ChartTheme(index));
}













