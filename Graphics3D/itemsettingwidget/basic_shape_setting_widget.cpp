#include "basic_shape_setting_widget.h"

/* BasicShapeSettingWidget ---|--- TransformSettingWidget   ---> transform_setting_widget.h
 *                            |--- (    )MeshSettingWidget  ---> basic_mesh_setting_widget.h
 *                            |--- MaterialSettingWidget    ---> material_setting_widget.h
 *                            |--- AnimationSettingWidget   ---> animation_setting_widget.h
 */

BasicShapeSettingWidget::BasicShapeSettingWidget(Qt3DRender::QGeometryRenderer *mesh,
                                                 Qt3DCore::QTransform *transform,
                                                 Qt3DRender::QMaterial *material,
                                                 QWidget *meshSettingWidget,
                                                 QWidget *parent)
    : QWidget(parent)
    , meshSettingWidget(meshSettingWidget)
{
    meshSettingWidget->setParent(this);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    transformButton = new QPushButton("Transform", this);
    transformSettingWidget = new TransformSettingWidget(transform, this);
    meshButton = new QPushButton("Mesh", this);
    materialButton = new QPushButton("Material", this);
    materialSettingWidget = new MaterialSettingWidget(material, this);
    animationButton = new QPushButton("Animation", this);
    animationSettingWidget = new AnimationSettingWidget(transform, this);

    setLayout(vLayout);
    vLayout->addWidget(transformButton);
    vLayout->addWidget(transformSettingWidget);
    vLayout->addWidget(meshButton);
    vLayout->addWidget(meshSettingWidget);
    vLayout->addWidget(materialButton);
    vLayout->addWidget(materialSettingWidget);
    vLayout->addWidget(animationButton);
    vLayout->addWidget(animationSettingWidget);
    vLayout->addItem(spacer);

    connect(transformButton, &QPushButton::released, transformSettingWidget, &TransformSettingWidget::changeVisible);
    connect(meshButton, &QPushButton::released, this, &BasicShapeSettingWidget::changeMeshWidgetVisible);
    connect(materialButton, &QPushButton::released, materialSettingWidget, &MaterialSettingWidget::changeVisible);
    connect(animationButton, &QPushButton::released, animationSettingWidget, &AnimationSettingWidget::changeVisible);
}

void BasicShapeSettingWidget::changeMeshWidgetVisible()
{
    meshSettingWidget->setVisible(!meshSettingWidget->isVisible());
}
