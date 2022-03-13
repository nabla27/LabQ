#include "tablewindow.h"

TableWindow::TableWindow(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.5, 0.5));

    QVBoxLayout *layout = new QVBoxLayout(this);
    tableTab = new QTabWidget(this);
    layout->addWidget(tableTab);
}

void TableWindow::readFile()
{
    const QString filePath = QFileDialog::getOpenFileName(this, "", "", "*.csv");

    /* ファイルが選択されなければ無効 */
    if(filePath.isEmpty()) return;

    const QString fileName = filePath.mid(filePath.lastIndexOf('/') + 1);

    /* 追加するTable */
    Plot2DTable *table = new Plot2DTable(tableTab);
    connect(table, &Plot2DTable::seriesCreated, this, &TableWindow::seriesCreated);

    /* ファイルを読み込み、Tableにデータをセットする */
    if(filePath.endsWith(".csv"))
        table->setData(readFileCsv(filePath));

    /* Tableを追加 */
    tableTab->addTab(table, fileName);

    this->show();
}




















Plot2DTable::Plot2DTable(QWidget *parent)
    : TableWidget(parent)
{
    /* contextMenuの設定 */
    setContextMenuPolicy(Qt::CustomContextMenu);
    initializeContextMenu();
    connect(this, &Plot2DTable::customContextMenuRequested, this, &Plot2DTable::onCustomContextMenu);
}

void Plot2DTable::initializeContextMenu()
{
    if(!contextMenu) delete contextMenu;

    contextMenu = new QMenu(this);

    /* copy */
    QAction *actCopy = new QAction("Copy", contextMenu);
    contextMenu->addAction(actCopy);
    connect(actCopy, &QAction::triggered, this, &Plot2DTable::copyCell);
    /* cut */
    QAction *actCut = new QAction("Cut", contextMenu);
    contextMenu->addAction(actCut);
    connect(actCut, &QAction::triggered, this, &Plot2DTable::cutCell);
    /* paste */
    QAction *actPaste = new QAction("Paste", contextMenu);
    contextMenu->addAction(actPaste);
    connect(actPaste, &QAction::triggered, this, &Plot2DTable::pasteCell);
    /* clear */
    QAction *actClear = new QAction("Clear", contextMenu);
    contextMenu->addAction(actClear);
    connect(actClear, &QAction::triggered, this, &Plot2DTable::clearCell);
    /* insert */
    QMenu *insertMenu = new QMenu("Insert", contextMenu);
    QAction *actInsertRowUp = new QAction("row (up)", insertMenu);
    QAction *actInsertRowDown = new QAction("row (down)", insertMenu);
    QAction *actInsertColLeft = new QAction("col (left)", insertMenu);
    QAction *actInsertColRight = new QAction("col (right)", insertMenu);
    insertMenu->addAction(actInsertRowUp);
    insertMenu->addAction(actInsertRowDown);
    insertMenu->addAction(actInsertColLeft);
    insertMenu->addAction(actInsertColRight);
    connect(actInsertRowUp, &QAction::triggered, this, &Plot2DTable::insertRowUp);
    connect(actInsertRowDown, &QAction::triggered, this, &Plot2DTable::insertRowDown);
    connect(actInsertColLeft, &QAction::triggered, this, &Plot2DTable::insertColLeft);
    connect(actInsertColRight, &QAction::triggered, this, &Plot2DTable::insertColRight);
    contextMenu->addMenu(insertMenu);
    /* placement */
    QMenu *placementMenu = new QMenu("Placement", contextMenu);
    QAction *actReverseRow = new QAction("reverse row", placementMenu);
    QAction *actReverseCol = new QAction("reverse col", placementMenu);
    placementMenu->addAction(actReverseRow);
    placementMenu->addAction(actReverseCol);
    connect(actReverseRow, &QAction::triggered, this, &Plot2DTable::reverseRow);
    connect(actReverseCol, &QAction::triggered, this, &Plot2DTable::reverseCol);
    contextMenu->addMenu(placementMenu);
    /* add series */
    seriesMenu = new QMenu("Add series", contextMenu);
    contextMenu->addMenu(seriesMenu);
}

void Plot2DTable::onCustomContextMenu(const QPoint& point)
{
    if(!contextMenu) return;
    if(!seriesMenu) return;

    seriesMenu->clear();

    /* 選択範囲の情報 */
    const QList<QTableWidgetSelectionRange> ranges = selectedRanges(); //選択されているセル情報
    const int rangeCount = ranges.size();                              //選択された数

    if(rangeCount > 0)
    {
        const int colCount = ranges.constFirst().columnCount();        //選択されたセルの列幅

        /* 選択範囲に応じて指定可能な配列をメニューに追加 */
        if((colCount == 1 && (rangeCount == 1 || rangeCount == 2)) ||
           (colCount == 2 && rangeCount == 1))
        {
            QAction *line = new QAction("Line", seriesMenu);
            QAction *scatter = new QAction("Scatter", seriesMenu);
            QAction *spline = new QAction("Spline", seriesMenu);
            seriesMenu->addAction(line);
            seriesMenu->addAction(scatter);
            seriesMenu->addAction(spline);
            connect(line, &QAction::triggered, this, &Plot2DTable::createLineSeries);
            connect(scatter, &QAction::triggered, this, &Plot2DTable::createScatterSeries);
            connect(spline, &QAction::triggered, this, &Plot2DTable::createSplineSeries);
        }
        if((colCount >= 2 && rangeCount == 1) ||
           (colCount == 1 && rangeCount >= 2))
        {
            QAction *bar = new QAction("Bar", seriesMenu);
            QAction *stackedBar = new QAction("Stacked bar", seriesMenu);
            QAction *percentBar = new QAction("Percent bar", seriesMenu);
            QAction *horizontalBar = new QAction("Horizontal bar", seriesMenu);
            QAction *horizontalStackedBar = new QAction("Horizontal stacked bar", seriesMenu);
            QAction *horizontalPercentBar = new QAction("Horizontal percent bar", seriesMenu);
            seriesMenu->addAction(bar);
            seriesMenu->addAction(stackedBar);
            seriesMenu->addAction(percentBar);
            seriesMenu->addAction(horizontalBar);
            seriesMenu->addAction(horizontalStackedBar);
            seriesMenu->addAction(horizontalPercentBar);
            connect(bar, &QAction::triggered, this, &Plot2DTable::createBarSeries);
            connect(stackedBar, &QAction::triggered, this, &Plot2DTable::createStackedBarSeries);
            connect(percentBar, &QAction::triggered, this, &Plot2DTable::createPercentBarSeries);
            connect(horizontalBar, &QAction::triggered, this, &Plot2DTable::createHorizontalBarSeries);
            connect(horizontalStackedBar, &QAction::triggered, this, &Plot2DTable::createHorizontalStackedBarSeries);
            connect(horizontalPercentBar, &QAction::triggered, this, &Plot2DTable::createHorizontalPercentBarSeries);
        }
        if((colCount == 1 && (rangeCount == 3 || rangeCount == 4)) ||
           (colCount == 2 && rangeCount == 2))
        {
            QAction *area = new QAction("Area", seriesMenu);
            seriesMenu->addAction(area);
            connect(area, &QAction::triggered, this, &Plot2DTable::createAreaSeries);
        }
        if(colCount == 1 && rangeCount == 1)
        {
            QAction *pie = new QAction("Pie", seriesMenu);
            seriesMenu->addAction(pie);
            connect(pie, &QAction::triggered, this, &Plot2DTable::createPieSeries);
        }
        if((colCount == 5 && rangeCount == 1) ||
           (colCount == 1 && rangeCount >= 2))
        {
            QAction *boxPlot = new QAction("Box plot", seriesMenu);
            seriesMenu->addAction(boxPlot);
            connect(boxPlot, &QAction::triggered, this, &Plot2DTable::createBoxPlotSeries);
        }
        if((colCount == 4 && rangeCount == 1) ||
           (colCount == 1 && rangeCount >= 2))
        {
            QAction *candleStick = new QAction("Candle stick", seriesMenu);
            seriesMenu->addAction(candleStick);
            connect(candleStick, &QAction::triggered, this, &Plot2DTable::createCandleStickSeries);
        }
    }

    contextMenu->exec(viewport()->mapToGlobal(point));
}

void Plot2DTable::createLineSeries()
{
    QScatterSeries *series = new QScatterSeries;
    QList<QPointF> data =
    {
        {1, 2},
        {2, 3},
        {3, 1},
        {4, 2},
        {5, 3},
        {6, 6},
        {7, 5},
    };

    series->append(data);

    emit seriesCreated(series);
}

void Plot2DTable::createScatterSeries()
{

}

void Plot2DTable::createSplineSeries()
{

}

void Plot2DTable::createBarSeries()
{

}

void Plot2DTable::createStackedBarSeries()
{

}

void Plot2DTable::createPercentBarSeries()
{

}

void Plot2DTable::createHorizontalBarSeries()
{

}

void Plot2DTable::createHorizontalStackedBarSeries()
{

}

void Plot2DTable::createHorizontalPercentBarSeries()
{

}

void Plot2DTable::createAreaSeries()
{

}

void Plot2DTable::createPieSeries()
{

}

void Plot2DTable::createBoxPlotSeries()
{

}

void Plot2DTable::createCandleStickSeries()
{

}
















