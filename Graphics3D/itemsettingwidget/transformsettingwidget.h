#ifndef TRANSFORMSETTINGWIDGET_H
#define TRANSFORMSETTINGWIDGET_H
#include <QWidget>
#include <Qt3DCore/QTransform>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMatrix4x4>
#include "layoutparts.h"

class TransformMatrixWidget;

class TransformSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransformSettingWidget(Qt3DCore::QTransform *transform, QWidget *parent = nullptr);

public:
    void changeVisible() { setVisible(!isVisible()); }

signals:
};

class TransformMatrixWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransformMatrixWidget(QWidget *parent);
    void setMatrix(const QMatrix4x4& matrix);
    void changeVisible() { setVisible(!isVisible()); }

private:
    void emitMatrixChanging();

private:
    QList<QList<QLineEdit*> > cell;

signals:
    void matrixChanged(const QMatrix4x4& matrix);
};

#endif // TRANSFORMSETTINGWIDGET_H
