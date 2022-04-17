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
    meshSettingWidget = new TorusMeshSettingWidget(mesh, this);
    materialButton = new QPushButton("Material", this);
    materialSettingWidget = new MaterialSettingWidget(material, this);

    setLayout(layout);
    layout->addWidget(transformButton);
    layout->addWidget(transformSettingWidget);
    layout->addWidget(meshButton);
    layout->addWidget(meshSettingWidget);
    layout->addWidget(materialButton);
    layout->addWidget(materialSettingWidget);
    layout->addItem(spacer);

    connect(transformButton, &QPushButton::released, transformSettingWidget, &TransformSettingWidget::changeVisible);
    connect(meshButton, &QPushButton::released, meshSettingWidget, &TorusMeshSettingWidget::changeVisible);
}



TorusMeshSettingWidget::TorusMeshSettingWidget(Qt3DExtras::QTorusMesh *mesh, QWidget *parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::Layout1DParam *minorRadius = new mlayout::Layout1DParam("Minor radius", this);
    mlayout::Layout1DParam *radius = new mlayout::Layout1DParam("Radius", this);
    SpinBoxEditLayout *rings = new SpinBoxEditLayout(this, "Rings", 100);
    SpinBoxEditLayout *slices = new SpinBoxEditLayout(this, "Slices", 100);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(minorRadius);
    vLayout->addLayout(radius);
    vLayout->addLayout(rings);
    vLayout->addLayout(slices);
    vLayout->addItem(spacer);

    minorRadius->setValue(mesh->minorRadius());
    radius->setValue(mesh->radius());
    rings->setSpinBoxMaxValue(1000);
    rings->setSpinBoxValue(mesh->rings());
    slices->setSpinBoxMaxValue(1000);
    slices->setSpinBoxValue(mesh->slices());

    connect(minorRadius, &mlayout::Layout1DParam::edited, mesh, &Qt3DExtras::QTorusMesh::setMinorRadius);
    connect(radius, &mlayout::Layout1DParam::edited, mesh, &Qt3DExtras::QTorusMesh::setRadius);
    connect(rings, &SpinBoxEditLayout::spinBoxValueChanged, mesh, &Qt3DExtras::QTorusMesh::setRings);
    connect(slices, &SpinBoxEditLayout::spinBoxValueChanged, mesh, &Qt3DExtras::QTorusMesh::setSlices);

    connect(mesh, &Qt3DExtras::QTorusMesh::minorRadiusChanged, minorRadius, &mlayout::Layout1DParam::setValue);
    connect(mesh, &Qt3DExtras::QTorusMesh::radiusChanged, radius, &mlayout::Layout1DParam::setValue);
    connect(mesh, &Qt3DExtras::QTorusMesh::ringsChanged, rings, &SpinBoxEditLayout::setSpinBoxValue);
    connect(mesh, &Qt3DExtras::QTorusMesh::slicesChanged, slices, &SpinBoxEditLayout::setSpinBoxValue);

    vLayout->setContentsMargins(0, 0, 0, 0);
}






















