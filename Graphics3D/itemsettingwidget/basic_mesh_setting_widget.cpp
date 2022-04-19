#include "basic_mesh_setting_widget.h"

static const int label_width_mesh = 100;


TorusMeshSettingWidget::TorusMeshSettingWidget(Qt3DExtras::QTorusMesh *mesh)
{
    mesh->setRadius(5);
    mesh->setMinorRadius(1);
    mesh->setRings(100);
    mesh->setSlices(20);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::Layout1DParam *minorRadius = new mlayout::Layout1DParam("Minor radius", this);
    mlayout::Layout1DParam *radius = new mlayout::Layout1DParam("Radius", this);
    SpinBoxEditLayout *rings = new SpinBoxEditLayout(this, "Rings", label_width_mesh);
    SpinBoxEditLayout *slices = new SpinBoxEditLayout(this, "Slices", label_width_mesh);
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






PlaneMeshSettingWidget::PlaneMeshSettingWidget(Qt3DExtras::QPlaneMesh *mesh)
{
    mesh->setHeight(100);
    mesh->setWidth(100);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::DoubleSbLayout *height = new mlayout::DoubleSbLayout("Height", this, label_width_mesh);
    mlayout::DoubleSbLayout *width = new mlayout::DoubleSbLayout("Width", this, label_width_mesh);
    mlayout::CheckBoxLayout *mirrored = new mlayout::CheckBoxLayout("Mirrored", this, label_width_mesh);

    setLayout(vLayout);
    vLayout->addLayout(height);
    vLayout->addLayout(width);
    vLayout->addLayout(mirrored);

    height->setSpinBoxMaxValue(100000);
    height->setSpinBoxMinValue(0.01);   //0以下が指定されるとクラッシュする
    height->setValue(mesh->height());
    width->setSpinBoxMaxValue(100000);
    width->setSpinBoxMinValue(0.01);
    width->setValue(mesh->width());
    mirrored->setChecked(mesh->mirrored());

    connect(height, &mlayout::DoubleSbLayout::valueChanged, mesh, &Qt3DExtras::QPlaneMesh::setHeight);
    connect(width, &mlayout::DoubleSbLayout::valueChanged, mesh, &Qt3DExtras::QPlaneMesh::setWidth);
    connect(mirrored, &mlayout::CheckBoxLayout::clicked, mesh, &Qt3DExtras::QPlaneMesh::setMirrored);

    vLayout->setContentsMargins(0, 0, 0, 0);
}






















