#ifndef TRANSFORMSETTINGWIDGET_H
#define TRANSFORMSETTINGWIDGET_H
#include <QWidget>
#include <Qt3DCore/QTransform>
#include "layoutparts.h"


class TransformSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransformSettingWidget(Qt3DCore::QTransform *transform,
                                    QWidget *parent = nullptr);
public:
    void changeVisible() { setVisible(!isVisible()); }

signals:
};

#endif // TRANSFORMSETTINGWIDGET_H
