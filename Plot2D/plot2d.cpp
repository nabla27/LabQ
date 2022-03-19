#include "plot2d.h"

Plot2D::Plot2D(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.5f, 0.5f));

    table = new TableWindow(nullptr);

    initializeLayout();
    initializeMenuBar();
}

Plot2D::~Plot2D()
{
    delete table;
}

void Plot2D::initializeMenuBar()
{
    if(!menuBar()) delete menuBar();

    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *importProject = new QAction("Import project", fileMenu);
    QAction *saveProject = new QAction("Save project", fileMenu);
    QAction *importDataFile = new QAction("Import data file", fileMenu);
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(importProject);
    fileMenu->addAction(saveProject);
    fileMenu->addAction(importDataFile);
    connect(importDataFile, &QAction::triggered, table, &TableWindow::readFile);

    QAction *tableAct = new QAction("Table", menuBar);
    menuBar->addAction(tableAct);
    connect(tableAct, &QAction::triggered, table, &TableWindow::show);

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
    graphSetting = new GraphSettingWidget(centralWidget, chart);

    layout->addWidget(chartView);
    layout->addLayout(settingLayout);
    settingLayout->addLayout(topSpace);
    settingLayout->addWidget(settingItem);
    settingLayout->addWidget(graphSetting);
    settingLayout->addLayout(bottomSpace);

    settingItem->addItems(QStringList() << "General" << "Legend" << "Axis" << "Series" << "GraphicsItem");
    layout->setContentsMargins(0, 0, 9, 0);
    chart->getGraph()->setMargins(QMargins(0, 0, 0, 0));
    graphSetting->setMaximumWidth(280);
    graphSetting->setMinimumWidth(280);
    graphSetting->setFrameShape(QFrame::Shape::Box);

    connect(settingItem, &QComboBox::currentIndexChanged, graphSetting, &GraphSettingWidget::setCurrentIndex);
    connect(graphSetting->axisSetting, &AxisSetting::axisCreated, chart, &Graph2D::addAxis);
    connect(graphSetting->axisSetting, &AxisSetting::removeAxisRequested, chart, &Graph2D::removeAxis);
    connect(graphSetting->seriesSetting, &SeriesSetting::removeSeriesRequested, chart, &Graph2D::removeSeries);
    connect(table, &TableWindow::seriesCreated, chart, &Graph2D::addSeries);
    connect(table, &TableWindow::seriesCreated, graphSetting->seriesSetting, &SeriesSetting::addSeries);
    connect(chartView, &ChartView::textItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addTextItemSettingWidget);
    connect(chartView, &ChartView::lineItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addLineItemSettingWidget);
    connect(chartView, &ChartView::rectItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addRectItemSettingWidget);
    connect(chartView, &ChartView::ellipseItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addEllipseItemSettingWidget);
    connect(chartView, &ChartView::polygonItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addPolygonItemSettingWidget);
    connect(chartView, &ChartView::pixmapItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addPixmapItemSettingWidget);
}
























