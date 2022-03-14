#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    /* ショートカットキーの登録 */
    QShortcut *scCtrC = new QShortcut(QKeySequence("Ctrl+C"), this);
    QShortcut *scCtrV = new QShortcut(QKeySequence("Ctrl+V"), this);
    QShortcut *scCtrX = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(scCtrC, &QShortcut::activated, this, &TableWidget::copyCell);
    connect(scCtrV, &QShortcut::activated, this, &TableWidget::pasteCell);
    connect(scCtrX, &QShortcut::activated, this, &TableWidget::cutCell);
}

template <>
void TableWidget::setData(const QList<QList<QString> >& data)
{
    this->clear();

    for(int row = 0; row < data.size(); ++row)
    {
        if(row >= rowCount()) { insertRow(rowCount()); }                         //行が足りなかったら足す
        for(int col = 0; col < data.at(row).size(); ++col)
        {
            if(col >= columnCount()) { insertColumn(columnCount()); }            //列が足りなかったら足す
            QTableWidgetItem *item = new QTableWidgetItem(data.at(row).at(col));
            setItem(row, col, item);                                             //アイテムをセット
        }
    }
}

template <>
QList<QList<QString> > TableWidget::getData() const
{
    const int rows = rowCount();
    const int cols = columnCount();
    QList<QList<QString> > data(rows, QList<QString>(cols));

    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < cols; ++col){
            //item()はQTableWidgetItem*がセットされていなかったり、インデックスが範囲外であればエラー(nullptr)
            data[row][col] = (item(row, col) != nullptr) ? item(row, col)->text() : "";
        }
    }

    return data;
}

void TableWidget::copyCell()
{
    /* tableの情報を取得 */
    const QAbstractItemModel *model = this->model();                //table全体の値の情報
    const QItemSelectionModel *selection = this->selectionModel();  //選択された部分の情報

    QModelIndexList indexes = selection->selectedIndexes();         //選択されたセルのインデックス

    if(indexes.count() == 0) { return; }                            //選択されたインデックスがなければ何もしない

    std::sort(indexes.begin(), indexes.end());                      //並び替え

    QString clip;
    QModelIndex previous = indexes.first();
    indexes.removeFirst();
    clip.append(model->data(previous).toString());

    foreach(const QModelIndex &current, indexes)                    //行、列と捜査していく
    {
        if(current.row() != previous.row())
            clip.append("\n");
        else
            clip.append("\t");                                      //列の区切りはタブ幅にする

        clip.append(model->data(current).toString());
        previous = current;
    }

    QApplication::clipboard()->setText(clip);                       //クリップボードに貼り付ける
}

void TableWidget::cutCell()
{
    this->copyCell();
    this->clearCell();
}

void TableWidget::pasteCell()
{
    /* 選択された行と列のインデックスを取得 */
    const QList<QTableWidgetSelectionRange> selectedRangeList = selectedRanges();

    /* クリップボードを読み取る */
    const QStringList rowStrList = QApplication::clipboard()->text().split("\n");

    /* 各選択範囲にペースト */
    for(const QTableWidgetSelectionRange& selected : selectedRangeList)
    {
        const int pasteRow = selected.topRow();            //ペースト開始点の行数
        const int pasteCol = selected.leftColumn();        //ペースト開始点の列数

        for(int row = 0; row < rowStrList.size(); ++row)
        {
            const QStringList colStrList = rowStrList.at(row).split(QRegularExpression("\\t| ")); //タブまたは空白区切りでセルにペースト
            if(pasteRow + row >= rowCount()) { insertRow(rowCount()); }                           //行数が足りない場合は追加

            for(int col = 0; col < colStrList.size(); ++col)
            {
                if(pasteCol + col >= columnCount()) { insertColumn(columnCount()); }              //列数が足りない場合は追加
                if(item(pasteRow + row, pasteCol + col) == nullptr){                              //QTableWidgetItemがセットされているか確認
                    QTableWidgetItem *item = new QTableWidgetItem(colStrList.at(col));
                    setItem(pasteRow + row, pasteCol + col, item);
                }
                else
                    item(pasteRow + row, pasteCol + col)->setText(colStrList.at(col));
            }
        }
    }
}

void TableWidget::clearCell()
{
    /* 選択された範囲を取得 */
    const QList<QTableWidgetSelectionRange> selectedRangeList = selectedRanges();

    /* 各選択された範囲を削除 */
    for(const QTableWidgetSelectionRange& selected : selectedRangeList)
    {
        const int startRow = selected.topRow();         //選択されたセルの開始行
        const int startCol = selected.leftColumn();     //選択されたセルの開始列
        const int endRow = selected.bottomRow();        //選択されたセルの終了行
        const int endCol = selected.rightColumn();      //選択されたセルの終了列

        for(int row = startRow; row <= endRow; ++row){
            for(int col = startCol; col <= endCol; ++col)
            {
                if(item(row, col) != nullptr)           //QTableWidgetItem*がセットされているか
                    item(row, col)->setText("");
            }
        }
    }
}

void TableWidget::insertRowUp()
{
    insertRow(currentIndex().row());
}

void TableWidget::insertRowDown()
{
    insertRow(currentIndex().row() + 1);
}

void TableWidget::insertColLeft()
{
    insertColumn(currentIndex().column());
}

void TableWidget::insertColRight()
{
    insertColumn(currentIndex().column() + 1);
}

void TableWidget::reverseRow()
{
    /* 選択された範囲を取得 */
    const QList<QTableWidgetSelectionRange> selectedRangeList = selectedRanges();

    /* 各選択された範囲 */
    for(const QTableWidgetSelectionRange& selected : selectedRangeList)
    {
        const int startRow = selected.topRow();      //選択された範囲の開始行
        const int startCol = selected.leftColumn();  //選択された範囲の開始列
        const int endRow = selected.bottomRow();     //選択された範囲の終了行
        const int endCol = selected.rightColumn();   //選択された範囲の終了列

        /* 選択された範囲の中央行 */
        const int middleRow = (endRow - startRow) / 2;

        /* 入れ替え */
        for(int row = 0; row <= middleRow; ++row){
            for(int col = startCol; col <= endCol; ++col)
            {
                if(item(startRow + row, col) == nullptr){                   //セルにQTableWidgetItem*がセットされていなかったらセット
                    QTableWidgetItem *topItem = new QTableWidgetItem("");
                    setItem(startRow + row, col, topItem);
                }
                if(item(endRow - row, col) == nullptr){                     //セルにQTableWidgetItem*がセットされていなかったらセット
                    QTableWidgetItem *btmItem = new QTableWidgetItem("");
                    setItem(endRow - row, col, btmItem);
                }

                const QString topText = item(startRow + row, col)->text();
                const QString btmText = item(endRow - row, col)->text();
                item(startRow + row, col)->setText(btmText);
                item(endRow - row, col)->setText(topText);
            }
        }
    }
}

void TableWidget::reverseCol()
{
    /* 選択された範囲を取得 */
    const QList<QTableWidgetSelectionRange> selectedRangeList = selectedRanges();

    /* 各選択された範囲 */
    for(const QTableWidgetSelectionRange& selected : selectedRangeList)
    {
        const int startRow = selected.topRow();      //選択された範囲の開始行
        const int startCol = selected.leftColumn();  //選択された範囲の開始列
        const int endRow = selected.bottomRow();     //選択された範囲の終了行
        const int endCol = selected.rightColumn();   //選択された範囲の終了列

        /* 選択された範囲の中央列 */
        const int middleCol = (endCol - startCol) / 2;

        /* 入れ替え */
        for(int row = startRow; row <= endRow; ++row){
            for(int col = 0; col <= middleCol; ++col)
            {
                if(item(row, startCol + col) == nullptr){
                    QTableWidgetItem *leftItem = new QTableWidgetItem("");
                    setItem(row, startCol + col, leftItem);
                }
                if(item(row, endCol - col) == nullptr){
                    QTableWidgetItem *rightItem = new QTableWidgetItem("");
                    setItem(row, endCol - col, rightItem);
                }

                const QString leftText = item(row, startCol + col)->text();
                const QString rightText = item(row, endCol - col)->text();
                item(row, startCol + col)->setText(rightText);
                item(row, endCol - col)->setText(leftText);
            }
        }
    }
}

void TableWidget::transpose()
{
    const QList<QTableWidgetSelectionRange> ranges = selectedRanges();

    //選択された行数、列数の大きい方の値に合わせてDim次正方行列で転置を行う
    for(const QTableWidgetSelectionRange& range : ranges)
    {
        const int startRow = range.topRow();
        const int startCol = range.leftColumn();
        const int Dim = std::max(range.bottomRow() - startRow, range.rightColumn() - startCol) + 1;

        //転置後の必要な分だけセルを増やす
        if(columnCount() < startRow + Dim) setColumnCount(startRow + Dim);
        if(rowCount() <= startCol + Dim) setRowCount(startCol + Dim);

        //データの入れ替え
        for(int i = 0; i < Dim; ++i){
            for(int j = i + 1; j < Dim; ++j)
            {
                //下三角成分Lと上三角成分を取得
                const QString dataL = (item(startRow + i, startCol + j)) ? item(startRow + i, startCol + j)->text() : "";
                const QString dataU = (item(startRow + j, startCol + i)) ? item(startRow + j, startCol + i)->text() : "";

                //上三角成分に下三角成分をセット
                if(item(startRow + i, startCol + j))
                    item(startRow + i, startCol + j)->setText(dataU);
                else
                {
                    QTableWidgetItem *item = new QTableWidgetItem(dataU);
                    setItem(startRow + i, startCol + j, item);
                }
                //下三角成分に上三角成分をセット
                if(item(startRow + j, startCol + i))
                    item(startRow + j, startCol + i)->setText(dataL);
                else
                {
                    QTableWidgetItem *item = new QTableWidgetItem(dataL);
                    setItem(startRow + j, startCol + i, item);
                }
            }
        }

    }
}





















