#ifndef PLOT2D_H
#define PLOT2D_H

#include <QMainWindow>
#include <QMenuBar>
#include <QScreen>
#include <QHBoxLayout>
#include <QChart>
#include "chartview.h"
#include "graph2d.h"
#include "graphsettingwidget.h"
#include "utility.h"
#include "tablewindow.h"

class Plot2D : public QMainWindow
{
    Q_OBJECT

public:
    Plot2D(QWidget *parent = nullptr);
    ~Plot2D();

private:
    void initializeMenuBar();
    void initializeLayout();

private:
    Graph2D *chart;
    ChartView *chartView;
    GraphSettingWidget *graphSetting;
    TableWindow *table;
};
#endif // PLOT2D_H
