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
    QAction *actTranspose = new QAction("transpose", placementMenu);
    placementMenu->addAction(actReverseRow);
    placementMenu->addAction(actReverseCol);
    placementMenu->addAction(actTranspose);
    connect(actReverseRow, &QAction::triggered, this, &Plot2DTable::reverseRow);
    connect(actReverseCol, &QAction::triggered, this, &Plot2DTable::reverseCol);
    connect(actTranspose, &QAction::triggered, this, &Plot2DTable::transpose);
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
        if((colCount == 3 && rangeCount == 1) ||
           (colCount == 2 && rangeCount == 2))
        {
            QAction *llArea = new QAction("Line area", seriesMenu);
            seriesMenu->addAction(llArea);
            connect(llArea, &QAction::triggered, this, &Plot2DTable::createLineAreaSeries);
        }
        if((colCount == 2 && rangeCount == 1) ||
           (colCount == 1 && rangeCount == 2))
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

void Plot2DTable::setXYSeriesData(QXYSeries *series, const QList<QTableWidgetSelectionRange>& ranges)
{
    const int colCount = ranges.constFirst().columnCount();
    const int rangeCount = ranges.count();

    if(colCount == 2)
    {
        const int colX = ranges.constFirst().leftColumn();
        const int colY = colX + 1;
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();

        for(int index = startRow; index <= endRow; ++index)
        {
            if(item(index, colX) && item(index, colY))
                series->append(item(index, colX)->text().toDouble(),
                               item(index, colY)->text().toDouble());
        }
    }
    else if(rangeCount == 1)
    {
        const int colY = ranges.constFirst().leftColumn();
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();

        for(int index = startRow; index <= endRow; ++index)
        {
            if(item(index, colY))
                series->append(index, item(index, colY)->text().toDouble());
        }
    }
    else if(rangeCount == 2)
    {
        const int colX = ranges.constFirst().leftColumn();
        const int colY = ranges.constLast().rightColumn();
        const int startRowX = ranges.constFirst().topRow();
        const int endRowX = ranges.constFirst().bottomRow();
        const int startRowY = ranges.constLast().topRow();

        for(int index = 0; index < endRowX - startRowX; ++index)
        {
            if(item(startRowX + index, colX) && item(startRowY + index, colY))
                series->append(item(startRowX + index, colX)->text().toDouble(),
                               item(startRowY + index, colY)->text().toDouble());
        }
    }
}

void Plot2DTable::setBarSeriesData(QAbstractBarSeries *series, const QList<QTableWidgetSelectionRange> &ranges)
{
    const int colCount = ranges.constFirst().columnCount();

    if(colCount >= 2)
    {
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();
        const int startCol = ranges.constFirst().leftColumn();
        const int endCol = ranges.constFirst().rightColumn();

        for(int row = startRow; row <= endRow; ++row)
        {
            const QString label = (item(row, startCol)) ? item(row, startCol)->text() : "";
            QBarSet *set = new QBarSet(label);

            for(int col = startCol + 1; col <= endCol; ++col)
            {
                if(item(row, col))
                    *set << item(row, col)->text().toDouble();
                else
                    *set << 0;
            }

            series->append(set);
        }
    }
    else
    {
        for(const QTableWidgetSelectionRange& range : ranges)
        {
            const int col = range.leftColumn();
            const int startRow = range.topRow();
            const int endRow = range.bottomRow();

            const QString label = (item(startRow, col)) ? item(startRow, col)->text() : "";
            QBarSet *set = new QBarSet(label);

            for(int row = startRow; row <= endRow; ++row)
            {
                if(item(row, col))
                    *set << item(row, col)->text().toDouble();
                else
                    *set << 0;
            }

            series->append(set);
        }
    }
}

void Plot2DTable::setAreaSeriesData(QLineSeries *upperSeries, QLineSeries *lowerSeries, const QList<QTableWidgetSelectionRange> &ranges)
{
    const int colCount = ranges.constFirst().columnCount();
    const int rangeCount = ranges.count();

    if(rangeCount == 2)
    {
        setXYSeriesData(upperSeries, QList<QTableWidgetSelectionRange>() << ranges.constFirst());
        setXYSeriesData(lowerSeries, QList<QTableWidgetSelectionRange>() << ranges.constLast());
    }
    else if(colCount == 3)
    {
        const int colX = ranges.constFirst().leftColumn();
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();

        for(int row = startRow; row <= endRow; ++row)
        {
            const double x = (item(row, colX)) ? item(row, colX)->text().toDouble() : 0;
            const double uy = (item(row, colX + 1)) ? item(row, colX + 1)->text().toDouble() : 0;
            const double ly = (item(row, colX + 2)) ? item(row, colX + 2)->text().toDouble() : 0;
            upperSeries->append(x, uy);
            lowerSeries->append(x, ly);
        }
    }
}

void Plot2DTable::createLineSeries()
{
    QLineSeries *series = new QLineSeries;

    setXYSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createScatterSeries()
{
    QScatterSeries *series = new QScatterSeries;

    setXYSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createSplineSeries()
{
    QSplineSeries *series = new QSplineSeries;

    setXYSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createBarSeries()
{
    QBarSeries *series = new QBarSeries;

    setBarSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createStackedBarSeries()
{
    QStackedBarSeries *series = new QStackedBarSeries;

    setBarSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createPercentBarSeries()
{
    QPercentBarSeries *series = new QPercentBarSeries;

    setBarSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createHorizontalBarSeries()
{
    QHorizontalBarSeries *series = new QHorizontalBarSeries;

    setBarSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createHorizontalStackedBarSeries()
{
    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries;

    setBarSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createHorizontalPercentBarSeries()
{
    QHorizontalPercentBarSeries *series = new QHorizontalPercentBarSeries;

    setBarSeriesData(series, selectedRanges());

    emit seriesCreated(series);
}

void Plot2DTable::createLineAreaSeries()
{
    QLineSeries *upperSeries = new QLineSeries;
    QLineSeries *lowerSeries = new QLineSeries;

    setAreaSeriesData(upperSeries, lowerSeries, selectedRanges());

    QAreaSeries *series = new QAreaSeries(upperSeries, lowerSeries);

    emit seriesCreated(series);
}


void Plot2DTable::createPieSeries()
{
    const QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    const int colCount = ranges.constFirst().columnCount();

    QPieSeries *series = new QPieSeries;

    if(colCount == 1)
    {
        const int labelCol = ranges.constFirst().leftColumn();
        const int valueCol = ranges.constLast().leftColumn();
        const int labelStartRow = ranges.constFirst().topRow();
        const int labelEndRow = ranges.constFirst().bottomRow();
        const int valueStartRow = ranges.constLast().topRow();

        for(int index = 0; index < labelEndRow - labelStartRow; ++index)
        {
            const QString label = (item(labelStartRow + index, labelCol)) ? item(labelStartRow + index, labelCol)->text() : "";
            const double value = (item(valueStartRow + index, valueCol)) ? item(valueStartRow + index, valueCol)->text().toDouble() : 0;

            QPieSlice *slice = new QPieSlice(label, value);
            series->append(slice);
        }
    }
    else
    {
        const int labelCol = ranges.constFirst().leftColumn();
        const int valueCol = labelCol + 1;
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();

        for(int row = startRow; row <= endRow; ++row)
        {
            const QString label = (item(row, labelCol)) ? item(row, labelCol)->text() : "";
            const double value = (item(row, valueCol)) ? item(row, valueCol)->text().toDouble() : 0;

            QPieSlice *slice = new QPieSlice(label, value);
            series->append(slice);
        }
    }

    emit seriesCreated(series);
}

void Plot2DTable::createBoxPlotSeries()
{
    const QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    const int colCount = ranges.constFirst().columnCount();

    QBoxPlotSeries *series = new QBoxPlotSeries;

    if(colCount == 5)
    {
        const int leCol = ranges.constFirst().leftColumn(); //最小値 lowerExtream
        const int lqCol = leCol + 1;                        //第一四分位点 lowerQuartile
        const int mCol = leCol + 2;                         //中央値 median
        const int uqCol = leCol + 3;                        //第三四分位点 upperQuartile
        const int ueCol = leCol + 4;                        //最大値 upperExtream
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();

        for(int row = startRow; row <= endRow; ++row)
        {
            const double lowerExtream = (item(row, leCol)) ? item(row, leCol)->text().toDouble() : 0;
            const double lowerQuartile = (item(row, lqCol)) ? item(row, lqCol)->text().toDouble() : 0;
            const double median = (item(row, mCol)) ? item(row, mCol)->text().toDouble() : 0;
            const double upperQuartile = (item(row, uqCol)) ? item(row, uqCol)->text().toDouble() : 0;
            const double upperExtream = (item(row, ueCol)) ? item(row, ueCol)->text().toDouble() : 0;

            QBoxSet *set = new QBoxSet(lowerExtream, lowerQuartile, median, upperQuartile, upperExtream);
            series->append(set);
        }
    }
    else
    {
        for(const QTableWidgetSelectionRange& range : ranges)
        {
            const int col = range.leftColumn();
            const int startRow = range.topRow();
            const int endRow = range.bottomRow();

            QList<double> data;

            //データを取得
            for(int row = startRow; row <= endRow; ++row)
                data << ((item(row, col)) ? item(row, col)->text().toDouble() : 0);

            //データを小さい順に並び変える
            std::sort(data.begin(), data.end());

            //中央値を求める関数
            auto findMedian = [&data](const int begin, const int end) -> double
            {
                const int count = end - begin;
                if(count % 2)
                    return data.at(count / 2 + begin);
                else
                {
                    const double right = data.at(count / 2 + begin);
                    const double left = data.at(count / 2 - 1 + begin);
                    return (right + left) / 2.0;
                }
            };

            //五数をセット
            const int count = data.count();
            QBoxSet *set = new QBoxSet;
            set->setValue(QBoxSet::LowerExtreme, data.first());
            set->setValue(QBoxSet::UpperExtreme, data.last());
            set->setValue(QBoxSet::Median, findMedian(0, count));
            set->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
            set->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + (count % 2), count));

            series->append(set);
        }
    }

    emit seriesCreated(series);
}

void Plot2DTable::createCandleStickSeries()
{
    const QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    const int colCount = ranges.constFirst().columnCount();

    QCandlestickSeries *series = new QCandlestickSeries;

    if(colCount == 4)
    {
        const int openCol = ranges.constFirst().leftColumn();
        const int highCol = openCol + 1;
        const int lowCol = openCol + 2;
        const int closeCol = openCol + 3;
        const int startRow = ranges.constFirst().topRow();
        const int endRow = ranges.constFirst().bottomRow();

        for(int row = startRow; row <= endRow; ++row)
        {
            const double open = (item(row, openCol)) ? item(row, openCol)->text().toDouble() : 0;
            const double high = (item(row, highCol)) ? item(row, highCol)->text().toDouble() : 0;
            const double low = (item(row, lowCol)) ? item(row, lowCol)->text().toDouble() : 0;
            const double close = (item(row, closeCol)) ? item(row, closeCol)->text().toDouble() : 0;

            QCandlestickSet *set = new QCandlestickSet(open, high, low, close);

            series->append(set);
        }

    }
    else
    {
        for(const QTableWidgetSelectionRange& range : ranges)
        {
            const int col = range.leftColumn();
            const int startRow = range.topRow();
            const int endRow = range.bottomRow();

            const double open = (item(startRow, col)) ? item(startRow, col)->text().toDouble() : 0;
            double high = open;
            double low = open;

            for(int row = startRow + 1; row <= endRow; ++row)
            {
                if(!item(row, col)) continue;

                const double value = item(row, col)->text().toDouble();
                if(high < value) high = value;     //最大値の更新
                else if(low > value) low = value;  //最小値の更新
            }

            const double close = (item(endRow, col)) ? (item(endRow, col))->text().toDouble() : 0;

            QCandlestickSet *set = new QCandlestickSet(open, high, low, close);
            series->append(set);
        }
    }

    emit seriesCreated(series);
}
















