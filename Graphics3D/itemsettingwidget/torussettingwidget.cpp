#include "torussettingwidget.h"

TorusSettingWidget::TorusSettingWidget(Qt3DExtras::QTorusMesh *mesh,
                                       Qt3DCore::QTransform *transform,
                                       Qt3DRender::QMaterial *material,
                                       QWidget *parent)
    : QWidget(parent), mesh(mesh), transform(transform), material(material)
{
    mesh->setRadius(5);
    mesh->setMinorRadius(1);
    mesh->setRings(100);
    mesh->setSlices(20);

    QVBoxLayout *layout = new QVBoxLayout;
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    transformButton = new QPushButton("Transform", this);
    transformSettingWidget = new TransformSettingWidget(transform, this);
    meshButton = new QPushButton("Mesh", this);
    meshSettingWidget = new QWidget(this);
    materialButton = new QPushButton("Material", this);
    materialSettingWidget = new MaterialSettingWidget(this);

    setLayout(layout);
    layout->addWidget(transformButton);
    layout->addWidget(transformSettingWidget);
    layout->addWidget(meshButton);
    layout->addWidget(meshSettingWidget);
    layout->addWidget(materialButton);
    layout->addWidget(materialSettingWidget);
    layout->addItem(spacer);

    connect(transformButton, &QPushButton::released, transformSettingWidget, &TransformSettingWidget::changeVisible);
}


























