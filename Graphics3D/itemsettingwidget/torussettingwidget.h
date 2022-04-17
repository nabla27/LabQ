#ifndef TORUSSETTINGWIDGET_H
#define TORUSSETTINGWIDGET_H
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include "transformsettingwidget.h"
#include "materialsettingwidget.h"

class TorusMeshSettingWidget;

class TorusSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TorusSettingWidget(Qt3DExtras::QTorusMesh *mesh,
                                Qt3DCore::QTransform *transform,
                                Qt3DRender::QMaterial *material,
                                QWidget *parent = nullptr);

private:
    Qt3DExtras::QTorusMesh *mesh;
    Qt3DCore::QTransform *transform;
    Qt3DRender::QMaterial *material;

    QPushButton *transformButton;
    TransformSettingWidget *transformSettingWidget;
    QPushButton *meshButton;
    TorusMeshSettingWidget *meshSettingWidget;
    QPushButton *materialButton;
    MaterialSettingWidget *materialSettingWidget;

signals:

};


class TorusMeshSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TorusMeshSettingWidget(Qt3DExtras::QTorusMesh *mesh, QWidget *parent);
    void changeVisible() { setVisible(!isVisible()); }
};

#endif // TORUSSETTINGWIDGET_H
