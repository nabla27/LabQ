#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QObject>
#include <QFont>
#include <QBrush>
#include <QPen>

class GraphicsTextItem : public QObject, public QGraphicsSimpleTextItem
{
    Q_OBJECT

public:
    GraphicsTextItem(const QString& text, QGraphicsItem *parent = nullptr);

public:
    void setItemText(const QString& text) { setText(text); }
    void setItemTextSize(const int ps);
    void setItemTextBold(const bool bold);
    void setItemTextItaric(const bool itaric);
    void setItemRotation(const qreal angle) { setRotation(angle); }
    void setItemTextColor(const QColor& color) { setBrush(QBrush(color)); }

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void itemSelected();
};










class GraphicsLineItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    GraphicsLineItem(const QLineF& line, QGraphicsItem *parent = nullptr);

public:
    void setItemLineWidth(const int width);
    void setItemLineLength(const qreal& length);
    void setItemLineAngle(const qreal& angle) { setRotation(angle); }
    void setItemLineColor(const QColor& color);
    void setItemLineStyle(const int index);
    void setItemLineStyleCustom(const QString& style);

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void itemSelected();
};








class GraphicsRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    GraphicsRectItem(const QRectF& rect, QGraphicsItem *parent = nullptr);

public:
    void setItemWidth(const qreal& width);
    void setItemHeight(const qreal& height);
    void setItemAngle(const qreal& angle) { setRotation(angle); }
    void setItemBorderWidth(const int width);
    void setItemBorderColor(const QColor& color);
    void setItemBorderStyle(const int index);
    void setItemBorderStyleCustom(const QString& style);
    void setItemFillColor(const QColor& color) { setBrush(color); }

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void itemSelected();
};








class GraphicsEllipseItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    GraphicsEllipseItem(const QRectF& rect, QGraphicsItem *parent = nullptr);

public:
    void setItemWidth(const qreal& width);
    void setItemHeight(const qreal& height);
    void setItemSpanAngle(const int angle) { setSpanAngle(angle); }
    void setItemStartAngle(const int angle) { setStartAngle(angle); }
    void setItemAngle(const qreal& angle) { setRotation(angle); }
    void setItemBorderWidth(const int width);
    void setItemBorderColor(const QColor& color);
    void setItemBorderStyle(const int index);
    void setItemBorderStyleCustom(const QString& style);
    void setItemFillColor(const QColor& color) { setBrush(color); }

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void itemSelected();
};








class GraphicsPolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    GraphicsPolygonItem(const QPolygonF& polygon, QGraphicsItem *parent = nullptr);

public:
    void setItemRotation(const qreal& angle) { setRotation(angle); }
    void setItemBorderWidth(const int width);
    void setItemBorderColor(const QColor& color);
    void setItemBorderStyle(const int index);
    void setItemBorderStyleCustom(const QString& style);
    void setItemFillColor(const QColor& color) { setBrush(color); }

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void itemSelected();
};










class GraphicsPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    GraphicsPixmapItem(const QPixmap& pixmap, QGraphicsItem *parent = nullptr);

public slots:
    void setItemScale(const qreal& scale) { setScale(scale); }
    void setItemRotation(const qreal& angle) { setRotation(angle); }


protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void itemSelected();
};

























#endif // GRAPHICSITEM_H
