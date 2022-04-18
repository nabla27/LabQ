#include "basicshapesettingwidget.h"

/* BasicShapeSettingWidget ---|--- TransformSettingWidget
 *                            |--- (    )MeshSettingWidget  ---> basicmeshsettingwidget.h
 *                            |--- MaterialSettingWidget
 */

BasicShapeSettingWidget::BasicShapeSettingWidget(Qt3DRender::QGeometryRenderer *mesh,
                                                 Qt3DCore::QTransform *transform,
                                                 Qt3DRender::QMaterial *material,
                                                 QWidget *meshSettingWidget,
                                                 QWidget *parent)
    : QWidget(parent), meshSettingWidget(meshSettingWidget)
{
    meshSettingWidget->setParent(this);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    transformButton = new QPushButton("Transform", this);
    transformSettingWidget = new TransformSettingWidget(transform, this);
    meshButton = new QPushButton("Mesh", this);
    materialButton = new QPushButton("Material", this);
    materialSettingWidget = new MaterialSettingWidget(material, this);

    setLayout(vLayout);
    vLayout->addWidget(transformButton);
    vLayout->addWidget(transformSettingWidget);
    vLayout->addWidget(meshButton);
    vLayout->addWidget(meshSettingWidget);
    vLayout->addWidget(materialButton);
    vLayout->addWidget(materialSettingWidget);
    vLayout->addItem(spacer);

    connect(transformButton, &QPushButton::released, transformSettingWidget, &TransformSettingWidget::changeVisible);
    connect(meshButton, &QPushButton::released, this, &BasicShapeSettingWidget::changeMeshWidgetVisible);
    connect(materialButton, &QPushButton::released, materialSettingWidget, &MaterialSettingWidget::changeVisible);
}

void BasicShapeSettingWidget::changeMeshWidgetVisible()
{
    meshSettingWidget->setVisible(!meshSettingWidget->isVisible());
}
