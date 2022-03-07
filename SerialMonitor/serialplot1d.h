#ifndef SERIALPLOT1D_H
#define SERIALPLOT1D_H
#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QLayout>
#include <QThread>
#include <QApplication>
#include <QEventLoop>
#include <QtSerialPort/QSerialPort>
#include "utility.h"
#include "layoutparts.h"

class SerialParser1D;
class SerialGraph1D;

class SerialPlot1D : public QWidget
{
    Q_OBJECT
public:
    explicit SerialPlot1D(QSerialPort *serialPort, QWidget *parent = nullptr);
    ~SerialPlot1D();

    void initializeLayout();
    //void readSerial();

private slots:
    //void setGraphRangeX();
    //void setRangeX(const double& rangeX) { this->rangeX = rangeX; }

private:
    //Chart *graph;
    //QChartView *graphView;
    //QXYSeries *series;
    //QValueAxis *axisX;
    //QValueAxis *axisY;

    //qsizetype dataCount = 0;
    //double rangeX = 100;

    //QString serialBuffer = "";
    QSerialPort *serialPort;

    QThread *serialGraphThread;
    SerialGraph1D *graph;

signals:

};







class SerialGraph1D : public QObject
{
    Q_OBJECT

public:
    SerialGraph1D(QSerialPort *serialPort);
    ~SerialGraph1D();

    QChartView* graphViewer() const { return graphView; }

public slots:
    void readSerial();
    void setMinY(const double& minY) { axisY->setMin(minY); }
    void setMaxY(const double& maxY) { axisY->setMax(maxY); }
    void setHorizontalRange(const double& rangeX) { this->rangeX = rangeX; setGraphRange(); }
    void showThread();
    void moveThread();

private:
    void setGraphRange();

private:
    QSerialPort *serialPort;
    QChart *graph;
    QChartView *graphView;

    QXYSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QString serialBuffer = "";
    double dataCount = 0;
    double rangeX = 100;

signals:
    void MinXSet(const double& val);
    void MaxXSet(const double& val);
    void appended(const double& x, const double& y);
};


#endif // SERIALPLOT1D_H
