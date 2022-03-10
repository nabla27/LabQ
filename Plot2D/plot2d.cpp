#include "plot2d.h"

Plot2D::Plot2D(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.5f, 0.5f));

    initializeMenuBar();
    initializeLayout();
}

Plot2D::~Plot2D()
{
}

void Plot2D::initializeMenuBar()
{
    if(!menuBar()) delete menuBar();

    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = new QMenu("File", menuBar);
    menuBar->addMenu(fileMenu);

    QMenu *widgetMenu = new QMenu("Widget", menuBar);
    menuBar->addMenu(widgetMenu);

    setMenuBar(menuBar);
}

void Plot2D::initializeLayout()
{
    if(!centralWidget()) delete centralWidget();

    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *settingLayout = new QVBoxLayout;
    BlankSpaceLayout *topSpace = new BlankSpaceLayout(0, 9);
    QComboBox *settingItem = new QComboBox(centralWidget);
    BlankSpaceLayout *bottomSpace = new BlankSpaceLayout(0, 9);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    chart = new Graph2D;
    chartView = new ChartView(chart->getGraph(), centralWidget);
    graphSetting = new GraphSettingWidget(centralWidget);

    layout->addWidget(chartView);
    layout->addLayout(settingLayout);
    settingLayout->addLayout(topSpace);
    settingLayout->addWidget(settingItem);
    settingLayout->addWidget(graphSetting);
    settingLayout->addLayout(bottomSpace);

    QList<QList<double> > data =
    {
        {0, 1},
        {1, 3},
        {2, 2},
        {3, 5},
        {4, 4}
    };
    chart->addSeries(data, Graph2D::SeriesType::Line);
    chart->setAxis(Graph2D::AxisType::Color, Graph2D::AxisAlign::Bottom);
    chart->setAxis(Graph2D::AxisType::Value, Graph2D::AxisAlign::Bottom);

    layout->setContentsMargins(0, 0, 9, 0);
    chart->getGraph()->setMargins(QMargins(0, 0, 0, 0));
    graphSetting->setMaximumWidth(260);
    graphSetting->setMinimumWidth(260);
    graphSetting->setFrameShape(QFrame::Shape::Box);
}
























