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

void GraphicsLineItem::setItemLineWidth(const int width)
{
    QPen pen = this->pen();
    pen.setWidth(width);
    setPen(pen);
}

void GraphicsLineItem::setItemLineLength(const qreal &length)
{
    QLineF line = this->line();
    line.setLength(length);
    setLine(line);
}

void GraphicsLineItem::setItemLineColor(const QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    setPen(pen);
}

void GraphicsLineItem::setItemLineStyle(const int index)
{
    QPen pen = this->pen();
    pen.setStyle(Qt::PenStyle(index));
    setPen(pen);
}

void GraphicsLineItem::setItemLineStyleCustom(const QString &style)
{
    /* 文字列QStringをダッシュパターンQList<qreal>に変換 */
    const QStringList strDashPattern = style.split(',', Qt::SplitBehaviorFlags::SkipEmptyParts);
    QList<qreal> dashPattern;
    for(const QString& val : strDashPattern) dashPattern << val.toDouble();

    /* ダッシュパターンを設定 */
    QPen pen = this->pen();
    pen.setDashPattern(dashPattern);
    setPen(pen);
}

void GraphicsLineItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
        setRotation(rotation() - 2);
    else
        setRotation(rotation() + 2);
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
    emit itemSelected();
}

void GraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
}

void GraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    emit itemSelected();
}











GraphicsRectItem::GraphicsRectItem(const QRectF& rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    setAcceptHoverEvents(true);
}

void GraphicsRectItem::setItemWidth(const qreal &width)
{
    QRectF rect = this->rect();
    rect.setWidth(width);
    setRect(rect);
}

void GraphicsRectItem::setItemHeight(const qreal &height)
{
    QRectF rect = this->rect();
    rect.setHeight(height);
    setRect(rect);
}

void GraphicsRectItem::setItemBorderWidth(const int width)
{
    QPen pen = this->pen();
    pen.setWidth(width);
    setPen(pen);
}

void GraphicsRectItem::setItemBorderColor(const QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    setPen(pen);
}

void GraphicsRectItem::setItemBorderStyle(const int index)
{
    QPen pen = this->pen();
    pen.setStyle(Qt::PenStyle(index));
    setPen(pen);
}

void GraphicsRectItem::setItemBorderStyleCustom(const QString &style)
{
    /* 文字列QStringをダッシュパターンQList<qreal>に変換 */
    const QStringList strDashPattern = style.split(',', Qt::SplitBehaviorFlags::SkipEmptyParts);
    QList<qreal> dashPattern;
    for(const QString& val : strDashPattern) dashPattern << val.toDouble();

    /* ダッシュパターンを設定 */
    QPen pen = this->pen();
    pen.setDashPattern(dashPattern);
    setPen(pen);
}

void GraphicsRectItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
        setRotation(rotation() - 2);
    else
        setRotation(rotation() + 2);
}

void GraphicsRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void GraphicsRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void GraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    emit itemSelected();
}

void GraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
}

void GraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    emit itemSelected();
}













GraphicsEllipseItem::GraphicsEllipseItem(const QRectF& rect, QGraphicsItem *parent)
    : QGraphicsEllipseItem(rect, parent)
{
    setAcceptHoverEvents(true);
}

void GraphicsEllipseItem::setItemWidth(const qreal &width)
{
    QRectF rect = this->rect();
    rect.setWidth(width);
    setRect(rect);
}

void GraphicsEllipseItem::setItemHeight(const qreal &height)
{
    QRectF rect = this->rect();
    rect.setHeight(height);
    setRect(rect);
}

void GraphicsEllipseItem::setItemBorderWidth(const int width)
{
    QPen pen = this->pen();
    pen.setWidth(width);
    setPen(pen);
}

void GraphicsEllipseItem::setItemBorderColor(const QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    setPen(pen);
}

void GraphicsEllipseItem::setItemBorderStyle(const int index)
{
    QPen pen = this->pen();
    pen.setStyle(Qt::PenStyle(index));
    setPen(pen);
}

void GraphicsEllipseItem::setItemBorderStyleCustom(const QString &style)
{
    /* 文字列QStringをダッシュパターンQList<qreal>に変換 */
    const QStringList strDashPattern = style.split(',', Qt::SplitBehaviorFlags::SkipEmptyParts);
    QList<qreal> dashPattern;
    for(const QString& val : strDashPattern) dashPattern << val.toDouble();

    /* ダッシュパターンを設定 */
    QPen pen = this->pen();
    pen.setDashPattern(dashPattern);
    setPen(pen);
}

void GraphicsEllipseItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
        setRotation(rotation() - 2);
    else
        setRotation(rotation() + 2);
}

void GraphicsEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void GraphicsEllipseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void GraphicsEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    emit itemSelected();
}

void GraphicsEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
}

void GraphicsEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    emit itemSelected();
}






















