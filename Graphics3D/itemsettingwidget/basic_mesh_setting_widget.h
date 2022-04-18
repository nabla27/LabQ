#ifndef BASIC_MESH_SETTING_WIDGET_H
#define BASIC_MESH_SETTING_WIDGET_H
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPhongMaterial>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPlaneMesh>

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include "transform_setting_widget.h"
#include "material_setting_widget.h"


class TorusMeshSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TorusMeshSettingWidget(Qt3DExtras::QTorusMesh *mesh);
};





class PlaneMeshSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaneMeshSettingWidget(Qt3DExtras::QPlaneMesh *mesh);
};

#endif // BASIC_MESH_SETTING_WIDGET_H
