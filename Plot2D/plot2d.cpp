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
    menuBar->addMenu(fileMenu);

    QMenu *widgetMenu = new QMenu("Widget", menuBar);
    menuBar->addMenu(widgetMenu);

    QMenu *addTable = new QMenu("Table", menuBar);
    QAction *readFile = new QAction("File", addTable);
    QAction *showTable = new QAction("Table", addTable);
    menuBar->addMenu(addTable);
    addTable->addAction(readFile);
    addTable->addAction(showTable);
    connect(readFile, &QAction::triggered, table, &TableWindow::readFile);
    connect(showTable, &QAction::triggered, table, &TableWindow::show);

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
    graphSetting = new GraphSettingWidget(centralWidget, chart->getGraph());

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
    connect(graphSetting->generalSetting, &GeneralSetting::marginLeftSet, chart, &Graph2D::setMarginLeft);
    connect(graphSetting->generalSetting, &GeneralSetting::marginRightSet, chart, &Graph2D::setMarginRight);
    connect(graphSetting->generalSetting, &GeneralSetting::marginBottomSet, chart, &Graph2D::setMarginBottom);
    connect(graphSetting->generalSetting, &GeneralSetting::marginTopSet, chart, &Graph2D::setMarginTop);
    connect(graphSetting->generalSetting, &GeneralSetting::graphTitleSet, chart, &Graph2D::setGraphTitle);
    connect(graphSetting->generalSetting, &GeneralSetting::graphTitleSizeSet, chart, &Graph2D::setGraphTitleSize);
    connect(graphSetting->generalSetting, &GeneralSetting::graphThemeSet, chart, &Graph2D::setGraphTheme);
    connect(graphSetting->seriesSetting, &SeriesSetting::removeSeriesRequested, chart, &Graph2D::removeSeries);
    connect(table, &TableWindow::seriesCreated, chart, &Graph2D::addSeries);
    connect(table, &TableWindow::seriesCreated, graphSetting->seriesSetting, &SeriesSetting::addSeries);
    connect(chartView, &ChartView::textItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addTextItemSettingWidget);
    connect(chartView, &ChartView::lineItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addLineItemSettingWidget);
    connect(chartView, &ChartView::rectItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addRectItemSettingWidget);
    connect(chartView, &ChartView::ellipseItemAdded, graphSetting->graphicsItemSetting, &GraphicsItemSetting::addEllipseItemSettingWidget);
}
























