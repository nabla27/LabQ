#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QImageReader>
#include <QImage>
#include <QLabel>
#include "graph2d.h"
#include "graphicsitem.h"

class ChartView : public QChartView
{
    Q_OBJECT

public:
    ChartView(QChart *chart, QWidget *parent);

public:
    void onContextMenuRequest(const QPoint& point);
    void initializeContextMenu();

private slots:
    void addTextItem();
    void addLineItem();
    void addRectItem();
    void addEllipseItem();
    void addPolygonItem();
    void addPixmapItem();

private:
    QMenu *contextMenu;

signals:
    void textItemAdded(GraphicsTextItem *item);
    void lineItemAdded(GraphicsLineItem *item);
    void rectItemAdded(GraphicsRectItem *item);
    void ellipseItemAdded(GraphicsEllipseItem *item);
    void polygonItemAdded(GraphicsPolygonItem *item);
    void pixmapItemAdded(GraphicsPixmapItem *item);
};

#endif // CHARTVIEW_H
