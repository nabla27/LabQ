#include "serialplot1d.h"

/*
 * QThreadのメモ
 * QWidgetクラスなどGUIを伴うObjectはmoveToThreadできない。常にメインのスレッドで行われる。
 * 親Objectがある状態でそのインスタンスをmoveToThreadできない。親と子を別スレッドにすることはできない。 --> ThreadAffnity
 * setParent()で別スレッドのインスタンスを親に指定することはできない。 --> ThreadAffinity
 */

SerialPlot1D::SerialPlot1D(QSerialPort *serialPort, QWidget *parent)
    : QWidget(parent), serialPort(serialPort)
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.3f, 0.4f));

    //graph = new QChart;
    //graphView = new QChartView(graph);
    //series = new QLineSeries;
    //graph->addSeries(series);
    //axisX = new QValueAxis;
    //axisY = new QValueAxis;
    //graph->addAxis(axisX, Qt::Alignment(Qt::AlignmentFlag::AlignBottom));
    //graph->addAxis(axisY, Qt::Alignment(Qt::AlignmentFlag::AlignLeft));
    //series->attachAxis(axisX);
    //series->attachAxis(axisY);

    graph = new SerialGraph1D(serialPort);
    serialGraphThread = new QThread(this);
    graph->moveToThread(serialGraphThread);
    connect(serialPort, &QSerialPort::readyRead, graph, &SerialGraph1D::readSerial);
    serialGraphThread->start();
    qDebug() << "monitor" << this->thread();
    qDebug() << "graph" << graph->thread();
    graph->moveThread();
    graph->showThread();

    initializeLayout();


}

SerialPlot1D::~SerialPlot1D()
{
    //delete graph;
    //delete series;
    //delete axisX;
    //delete axisY;
}

void SerialPlot1D::initializeLayout()
{
    if(layout()) delete layout();

    QHBoxLayout *layout = new QHBoxLayout(this);
    QWidget *optionWidget = new QWidget(this);
    QVBoxLayout *optionLayout = new QVBoxLayout;

    setLayout(layout);
    layout->addWidget(graph->graphViewer());
    layout->addWidget(optionWidget);
    optionWidget->setLayout(optionLayout);
    optionWidget->setMaximumWidth(200);

    LineEditLayout *minY = new LineEditLayout(optionWidget, "MinY");
    LineEditLayout *maxY = new LineEditLayout(optionWidget, "MaxY");
    LineEditLayout *rangeX = new LineEditLayout(optionWidget, "RangeX");
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    optionLayout->addLayout(minY);
    optionLayout->addLayout(maxY);
    optionLayout->addLayout(rangeX);
    optionLayout->addItem(spacer);

    connect(minY, &LineEditLayout::lineValueEdited, graph, &SerialGraph1D::setMinY);
    connect(maxY, &LineEditLayout::lineValueEdited, graph, &SerialGraph1D::setMaxY);
    connect(rangeX, &LineEditLayout::lineValueEdited, graph, &SerialGraph1D::setHorizontalRange);

    //connect(minY, &LineEditLayout::lineValueEdited, axisY, &QValueAxis::setMin);
    //connect(maxY, &LineEditLayout::lineValueEdited, axisY, &QValueAxis::setMax);
    //connect(rangeX, &LineEditLayout::lineValueEdited, this, &SerialPlot1D::setRangeX);
    //connect(rangeX, &LineEditLayout::lineValueEdited, serialParser, &SerialParser1D::setHorizontalRange);
}
#if 0
void SerialPlot1D::setGraphRangeX()
{
    if(dataCount <= rangeX)
    {
        axisX->setMin(0);
        axisX->setMax(rangeX);
    }
    else
    {
        axisX->setMin(dataCount - rangeX);
        axisX->setMax(dataCount);
    }
}

void SerialPlot1D::readSerial()
{
    serialBuffer.append(serialPort->readAll());

    if(serialBuffer.contains(','))
    {
        const QStringList& dataSepalated = serialBuffer.split(',');
        for(const QString& value : dataSepalated)
        {
            if(!value.isEmpty())
            {
                series->append(dataCount, value.toDouble());
                setGraphRangeX();
                dataCount++;
            }
        }
        serialBuffer.clear();
    }
    if(series->count() > 5000) { series->clear(); }
}

#endif










SerialGraph1D::SerialGraph1D(QSerialPort *serialPort)
    : serialPort(serialPort)
{
    graph = new QChart;
    graphView = new QChartView(graph);
    series = new QLineSeries(this);
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);

    graph->addSeries(series);
    graph->addAxis(axisX, Qt::AlignmentFlag::AlignBottom);
    graph->addAxis(axisY, Qt::AlignmentFlag::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    qDebug() << "SerialGraph1D" << this;
    qDebug() << "graph" << graph;
    qDebug() << "graphView" << graphView;
    qDebug() << "series" << series;
    qDebug() << "axisX" << axisX;
    qDebug() << "graph parent" << graph->parent();
    qDebug() << "graphView parent" << graphView->parent();
    qDebug() << "series parent" << series->parent();
    qDebug() << "axisX parent" << axisX->parent();
}

void SerialGraph1D::showThread()
{
    qDebug() << "graph" << graph->thread();
    qDebug() << "graphView" << graphView->thread();
    qDebug() << "series" << series->thread();
    qDebug() << "axisX" << axisX->thread();
    qDebug() << "axisY" << axisY->thread();
}

void SerialGraph1D::moveThread()
{
    graph->moveToThread(thread());
    graphView->moveToThread(thread());
    series->moveToThread(thread());
    axisX->moveToThread(thread());
    axisY->moveToThread(thread());
}

SerialGraph1D::~SerialGraph1D()
{
    delete graph;
    delete graphView;
    delete series;
    delete axisX;
    delete axisY;
}

void SerialGraph1D::readSerial()
{
    serialBuffer.append(serialPort->readAll());

    if(serialBuffer.contains(','))
    {
        const QStringList& dataSepalated = serialBuffer.split(',');
        for(const QString& value : dataSepalated)
        {
            if(!value.isEmpty())
            {
                //series->append(dataCount, value.toDouble());
                emit appended(dataCount, value.toDouble());

                setGraphRange();
                dataCount++;
                //QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
        serialBuffer.clear();
    }
}

void SerialGraph1D::setGraphRange()
{
    if(dataCount <= rangeX)
    {
        //axisX->setMin(0);
        //axisX->setMax(rangeX);
        emit MinXSet(0);
        emit MaxXSet(rangeX);
    }
    else
    {
        //axisX->setMin(dataCount - rangeX);
        //axisX->setMax(dataCount);
        emit MinXSet(dataCount - rangeX);
        emit MaxXSet(dataCount);
    }
}























