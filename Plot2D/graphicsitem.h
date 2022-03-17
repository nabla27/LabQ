#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QObject>
#include <QFont>
#include <QBrush>

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


class GraphicsLineItem : public QGraphicsLineItem
{
public:
    GraphicsLineItem(const QLineF& line, QGraphicsItem *parent = nullptr);

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};









#endif // GRAPHICSITEM_H
