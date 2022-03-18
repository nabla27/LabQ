#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent)
{
    initializeContextMenu();
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ChartView::customContextMenuRequested, this, &ChartView::onContextMenuRequest);
}

void ChartView::initializeContextMenu()
{
    if(!contextMenu) delete contextMenu;

    contextMenu = new QMenu(this);

    QAction *addTextItem = new QAction("Text", contextMenu);
    contextMenu->addAction(addTextItem);
    connect(addTextItem, &QAction::triggered, this, &ChartView::addTextItem);

    QAction *addLineItem = new QAction("Line", contextMenu);
    contextMenu->addAction(addLineItem);
    connect(addLineItem, &QAction::triggered, this, &ChartView::addLineItem);

    QAction *addRectItem = new QAction("Rectangle", contextMenu);
    contextMenu->addAction(addRectItem);
    connect(addRectItem, &QAction::triggered, this, &ChartView::addRectItem);

    QAction *addEllipseItem = new QAction("Ellipse", contextMenu);
    contextMenu->addAction(addEllipseItem);
    connect(addEllipseItem, &QAction::triggered, this, &ChartView::addEllipseItem);
}

void ChartView::onContextMenuRequest(const QPoint &point)
{
    contextMenu->exec(viewport()->mapToGlobal(point));
}

void ChartView::addTextItem()
{
    GraphicsTextItem *textItem = new GraphicsTextItem("text", chart());
    textItem->setPos(mapFromGlobal(cursor().pos()));

    emit textItemAdded(textItem);
}

void ChartView::addLineItem()
{
    GraphicsLineItem *lineItem = new GraphicsLineItem(QLineF(-25, 0, 25, 0), chart());
    QPen linePen = lineItem->pen();
    linePen.setWidth(2);
    lineItem->setPen(linePen);
    lineItem->setPos(mapFromGlobal(cursor().pos()));

    emit lineItemAdded(lineItem);
}

void ChartView::addRectItem()
{
    GraphicsRectItem *rectItem = new GraphicsRectItem(QRectF(0, 0, 100, 50), chart());
    rectItem->setPos(mapFromGlobal(cursor().pos()));

    emit rectItemAdded(rectItem);
}

void ChartView::addEllipseItem()
{
    GraphicsEllipseItem *ellipseItem = new GraphicsEllipseItem(QRectF(0, 0, 100, 50), chart());
    ellipseItem->setPos(mapFromGlobal(cursor().pos()));

    emit ellipseItemAdded(ellipseItem);
}
















