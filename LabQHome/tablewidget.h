#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QTableWidget>
#include <QShortcut>
#include <QKeySequence>
#include <QApplication>
#include <QClipboard>
#include <QScreen>

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent);

public:
    template <class T> void setData(const QList<QList<T> >& data);
    template <class T> QList<QList<T> > getData() const;

public slots:
    void appendRowLast() { insertRow(rowCount()); }
    void removeLastRow() { removeRow(rowCount() - 1); }
    void appendColLast() { insertColumn(columnCount()); }
    void removeLastCol() { removeColumn(columnCount() - 1); }

protected slots:
    void copyCell();
    void cutCell();
    void pasteCell();
    void clearCell();
    void insertRowUp();
    void insertRowDown();
    void insertColLeft();
    void insertColRight();
    void reverseRow();
    void reverseCol();
    void transposeCell();
};



















#endif // TABLEWIDGET_H
