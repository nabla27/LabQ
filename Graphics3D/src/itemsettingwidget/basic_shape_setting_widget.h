#ifndef BASIC_SHAPE_SETTING_WIDGET_H
#define BASIC_SHAPE_SETTING_WIDGET_H
//#include <QWidget>
#include <Qt3DRender/QGeometryRenderer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QScrollArea>
#include "transform_setting_widget.h"
#include "material_setting_widget.h"
#include "animation_setting_widget.h"

class BasicShapeSettingWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit BasicShapeSettingWidget(Qt3DRender::QGeometryRenderer *mesh,
                                     Qt3DCore::QTransform *transform,
                                     Qt3DRender::QMaterial *material,
                                     QWidget *meshSettingWidget,
                                     QWidget *parent);
    SequentialAnimationGroup* animation() const { return animationSettingWidget->animation(); }

private slots:
    void changeMeshWidgetVisible();

private:
    QPushButton *transformButton;
    TransformSettingWidget *transformSettingWidget;
    QPushButton *meshButton;
    QWidget *meshSettingWidget;
    QPushButton *materialButton;
    MaterialSettingWidget *materialSettingWidget;
    QPushButton *animationButton;
    AnimationSettingWidget *animationSettingWidget;
};

#endif // BASIC_SHAPE_SETTING_WIDGET_H
