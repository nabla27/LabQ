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
#include <QBoxSet>
#include <QCandlestickSeries>

class Graph2D : public QObject
{
    Q_OBJECT

public:
    Graph2D();
    ~Graph2D();

    enum class AxisType { Value, BarCategory, Category, DateTime, LogValue, Color };
    enum class AxisAlign { Left, Right, Bottom, Top };
    enum class SeriesType { Line, Area, Bar, StackedBar, PercentBar, Pie, Scatter, Spline, HorizontalBar, HorizontalStackedBar, HorizontalPercentBar, BoxPlot, Candlestick };
    enum class Theme { Light, BlueCerulean, Dark, BrownSand, BlueNcs, HighContrast, BlueIcy, Qt };
    enum class MarkerShape { Circle, Rectangle, RotRectangle, Triangle, Star, Pentagon };
    enum class BarLabelPosition { Center, InsideEnd, InsideBase, OutsideEnd };
    enum class PieLabelPosition { Outsize, InsideHorizontal, InsideTangential, InsizeNormal };
    enum class LegendAlign { Top, Bottom, Left, Right };
    enum class LegendMarkerShape { Default, Rectangle, Circle, FromSeries, RotRectangle, Triangle, Star, Pentagon };
    enum class GraphicsItemType { Text, Line };
    enum class PenStyle { No, Solid, Dash, Dot, DashDot, DashDotDot, CustomDash };

    Q_ENUM(AxisType)
    Q_ENUM(AxisAlign)
    Q_ENUM(SeriesType)
    Q_ENUM(Theme)
    Q_ENUM(MarkerShape)
    Q_ENUM(BarLabelPosition)
    Q_ENUM(PieLabelPosition)
    Q_ENUM(LegendAlign)
    Q_ENUM(LegendMarkerShape)
    Q_ENUM(GraphicsItemType)
    Q_ENUM(PenStyle)

public:
    QChart* getGraph() const { return this->graph; }

public slots:
    void addAxis(QAbstractAxis *axis, const Graph2D::AxisAlign align);
    void removeAxis(QAbstractAxis *axis) { graph->removeAxis(axis); }
    void addSeries(QAbstractSeries *series) { graph->addSeries(series); }
    void removeSeries(QAbstractSeries *series) { graph->removeSeries(series); }
    void setMarginLeft(const QString& lw);
    void setMarginRight(const QString& rw);
    void setMarginBottom(const QString& bh);
    void setMarginTop(const QString& th);
    void setGraphTitle(const QString& title);
    void setGraphTitleSize(const int ps);
    void setGraphTheme(const int index);

private:
    QChart *graph;
};

#endif // GRAPH2D_H
