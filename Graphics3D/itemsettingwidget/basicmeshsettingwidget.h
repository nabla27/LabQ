#ifndef BASICMESHSETTINGWIDGET_H
#define BASICMESHSETTINGWIDGET_H
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPhongMaterial>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPlaneMesh>

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include "transformsettingwidget.h"
#include "materialsettingwidget.h"


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

#endif // BASICMESHSETTINGWIDGET_H
