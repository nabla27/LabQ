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
    : QScrollArea(parent)
    , meshSettingWidget(meshSettingWidget)
{
    meshSettingWidget->setParent(this);

    QWidget *contents = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(contents);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    transformButton = new QPushButton("Transform", contents);
    transformSettingWidget = new TransformSettingWidget(transform, contents);
    meshButton = new QPushButton("Mesh", contents);
    materialButton = new QPushButton("Material", contents);
    materialSettingWidget = new MaterialSettingWidget(material, contents);
    animationButton = new QPushButton("Animation", contents);
    animationSettingWidget = new AnimationSettingWidget(transform, contents);

    setWidget(contents);
    contents->setLayout(vLayout);
    vLayout->addWidget(transformButton);
    vLayout->addWidget(transformSettingWidget);
    vLayout->addWidget(meshButton);
    vLayout->addWidget(meshSettingWidget);
    vLayout->addWidget(materialButton);
    vLayout->addWidget(materialSettingWidget);
    vLayout->addWidget(animationButton);
    vLayout->addWidget(animationSettingWidget);
    vLayout->addItem(spacer);

    setWidgetResizable(true);
    contents->setFixedWidth(300);

    connect(transformButton, &QPushButton::released, transformSettingWidget, &TransformSettingWidget::changeVisible);
    connect(meshButton, &QPushButton::released, this, &BasicShapeSettingWidget::changeMeshWidgetVisible);
    connect(materialButton, &QPushButton::released, materialSettingWidget, &MaterialSettingWidget::changeVisible);
    connect(animationButton, &QPushButton::released, animationSettingWidget, &AnimationSettingWidget::changeVisible);
}

void BasicShapeSettingWidget::changeMeshWidgetVisible()
{
    meshSettingWidget->setVisible(!meshSettingWidget->isVisible());
}
