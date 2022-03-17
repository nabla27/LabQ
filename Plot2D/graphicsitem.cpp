#include "graphicsitem.h"


GraphicsTextItem::GraphicsTextItem(const QString& text, QGraphicsItem *parent)
    : QGraphicsSimpleTextItem(text, parent)
{
    setAcceptHoverEvents(true);
}

void GraphicsTextItem::setItemTextSize(const int ps)
{
    QFont textFont = font();
    textFont.setPointSize(ps);
    setFont(textFont);
}

void GraphicsTextItem::setItemTextBold(const bool bold)
{
    QFont textFont = font();
    textFont.setBold(bold);
    setFont(textFont);
}

void GraphicsTextItem::setItemTextItaric(const bool itaric)
{
    QFont textFont = font();
    textFont.setItalic(itaric);
    setFont(textFont);
}

void GraphicsTextItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
        setRotation(rotation() - 2);
    else
        setRotation(rotation() + 2);
}

void GraphicsTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void GraphicsTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void GraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    emit itemSelected();
}

void GraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
}

void GraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    emit itemSelected();
}











GraphicsLineItem::GraphicsLineItem(const QLineF& line, QGraphicsItem *parent)
    : QGraphicsLineItem(line, parent)
{
    setAcceptHoverEvents(true);
}

void GraphicsLineItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
#if 0
    double theta = (2.0 / 180.0) * 3.1415; qDebug() << theta;
    if(event->delta() < 0) { theta = -theta; }

    const QPointF previousP1 = line().p1();
    const QPointF previousP2 = line().p2();

    setLine(QLineF(QPointF(previousP1.x() * cos(theta) - previousP1.y() * sin(theta), previousP1.y() * sin(theta) + previousP1.y() * cos(theta)),
                   QPointF(previousP2.x() * cos(theta) - previousP2.y() * sin(theta), previousP2.y() * sin(theta) + previousP2.y() * cos(theta))));
#endif
}

void GraphicsLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void GraphicsLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void GraphicsLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}

void GraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
}

void GraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}
























