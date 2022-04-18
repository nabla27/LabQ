#ifndef BASICSHAPESETTINGWIDGET_H
#define BASICSHAPESETTINGWIDGET_H
#include <QWidget>
#include <Qt3DRender/QGeometryRenderer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include "transformsettingwidget.h"
#include "materialsettingwidget.h"

class BasicShapeSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BasicShapeSettingWidget(Qt3DRender::QGeometryRenderer *mesh,
                                     Qt3DCore::QTransform *transform,
                                     Qt3DRender::QMaterial *material,
                                     QWidget *meshSettingWidget,
                                     QWidget *parent);

private slots:
    void changeMeshWidgetVisible();

private:
    QPushButton *transformButton;
    TransformSettingWidget *transformSettingWidget;
    QPushButton *meshButton;
    QWidget *meshSettingWidget;
    QPushButton *materialButton;
    MaterialSettingWidget *materialSettingWidget;
};

#endif // BASICSHAPESETTINGWIDGET_H
