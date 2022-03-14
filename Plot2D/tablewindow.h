#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H
#include <QWidget>
#include <QTableWidget>
#include <QShortcut>
#include <QKeySequence>
#include <QApplication>
#include <QClipboard>
#include <QScreen>
#include <QMenu>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTabWidget>
#include <QAbstractSeries>

#include <QLineSeries>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QAbstractBarSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QStackedBarSeries>
#include <QPercentBarSeries>
#include <QHorizontalBarSeries>
#include <QHorizontalStackedBarSeries>
#include <QHorizontalPercentBarSeries>
#include <QAreaSeries>
#include <QPieSeries>
#include <QBoxPlotSeries>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QBarCategoryAxis>

#include "utility.h"
#include "tablewidget.h"
#include "iofile.h"

class TableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = nullptr);

public slots:
    void readFile();

private:
    QTabWidget *tableTab;

signals:
    void seriesCreated(QAbstractSeries *series);
};




class Plot2DTable : public TableWidget
{
    Q_OBJECT

public:
    Plot2DTable(QWidget *parent);
    void initializeContextMenu();

private slots:
    void onCustomContextMenu(const QPoint& point);

    void createLineSeries();
    void createScatterSeries();
    void createSplineSeries();
    void createBarSeries();
    void createStackedBarSeries();
    void createPercentBarSeries();
    void createHorizontalBarSeries();
    void createHorizontalStackedBarSeries();
    void createHorizontalPercentBarSeries();
    void createLineAreaSeries();
    void createPieSeries();
    void createBoxPlotSeries();
    void createCandleStickSeries();

private:
    void setXYSeriesData(QXYSeries *series,  const QList<QTableWidgetSelectionRange>& ranges);
    void setBarSeriesData(QAbstractBarSeries *series, const QList<QTableWidgetSelectionRange>& ranges);
    void setAreaSeriesData(QLineSeries *upperSeries, QLineSeries *lowerSeries, const QList<QTableWidgetSelectionRange>& ranges);

private:
    QMenu *contextMenu = nullptr;
    QMenu *seriesMenu = nullptr;

signals:
    void seriesCreated(QAbstractSeries *series);
};





























#endif // TABLEWINDOW_H
