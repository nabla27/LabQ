#ifndef GRAPH2D_H
#define GRAPH2D_H
#include <QChart>

#include <QBarCategoryAxis>
#include <QCategoryAxis>
#include <QColorAxis>
#include <QDateTimeAxis>
#include <QLogValueAxis>
#include <QValueAxis>

#include <QAbstractSeries>
#include <QLineSeries>
#include <QAreaSeries>
#include <QBarSeries>
#include <QStackedBarSeries>
#include <QPercentBarSeries>
#include <QPieSeries>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QHorizontalBarSeries>
#include <QHorizontalStackedBarSeries>
#include <QHorizontalPercentBarSeries>
#include <QBoxPlotSeries>
#include <QCandlestickSeries>

class Graph2D : private QObject
{
    Q_OBJECT

public:
    Graph2D();
    ~Graph2D();

    enum class AxisType { Value, BarCategory, Category, DateTime, LogValue, Color };
    enum class AxisAlign { Left, Right, Bottom, Top };
    enum class SeriesType { Line, Area, Bar, StackedBar, PercentBar, Pie, Scatter, Spline, HorizontalBar, HorizontalStackedBar, HorizontalPercentBar, BoxPlot, Candlestick };

    Q_ENUM(AxisType)
    Q_ENUM(AxisAlign)
    Q_ENUM(SeriesType)

public:
    QChart* getGraph() const { return this->graph; }
    void setAxis(const AxisType type, const AxisAlign align);
    void addSeries(const QList<QList<double>>& data, const SeriesType type);

private:
    void attachAxisToSeries(QAbstractAxis* axis);
    void attachSeriesToAxis(QAbstractSeries *series);

private:
    QChart *graph;
};

#endif // GRAPH2D_H
