#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>

class ChartView : public QChartView
{
    Q_OBJECT

public:
    ChartView(QChart *chart, QWidget *parent);
};

#endif // CHARTVIEW_H
