#include "basic_mesh_setting_widget.h"

static const int label_width_mesh = 100;


TorusMeshSettingWidget::TorusMeshSettingWidget(Qt3DExtras::QTorusMesh *mesh)
{
    setObjectName("Torus");

    mesh->setRadius(5);
    mesh->setMinorRadius(1);
    mesh->setRings(100);
    mesh->setSlices(20);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::DoubleSbLayout *minorRadius = new mlayout::DoubleSbLayout("Minor radius", this, label_width_mesh);
    mlayout::DoubleSbLayout *radius = new mlayout::DoubleSbLayout("Radius", this, label_width_mesh);
    mlayout::IntSbLayout *rings = new mlayout::IntSbLayout("Rings", this, label_width_mesh);
    mlayout::IntSbLayout *slices = new mlayout::IntSbLayout("Slices", this, label_width_mesh);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(minorRadius);
    vLayout->addLayout(radius);
    vLayout->addLayout(rings);
    vLayout->addLayout(slices);
    vLayout->addItem(spacer);

    minorRadius->setValue(mesh->minorRadius());
    radius->setValue(mesh->radius());
    rings->setSpinBoxMaxValue(100000);
    rings->setValue(mesh->rings());
    slices->setSpinBoxMaxValue(100000);
    slices->setValue(mesh->slices());

    minorRadius->setDecimals(4);
    radius->setDecimals(4);

    connect(minorRadius, &mlayout::DoubleSbLayout::valueChanged, mesh, &Qt3DExtras::QTorusMesh::setMinorRadius);
    connect(radius, &mlayout::DoubleSbLayout::valueChanged, mesh, &Qt3DExtras::QTorusMesh::setRadius);
    connect(rings, &mlayout::IntSbLayout::valueChanged, mesh, &Qt3DExtras::QTorusMesh::setRings);
    connect(slices, &mlayout::IntSbLayout::valueChanged, mesh, &Qt3DExtras::QTorusMesh::setSlices);

    connect(mesh, &Qt3DExtras::QTorusMesh::minorRadiusChanged, minorRadius, &mlayout::DoubleSbLayout::setValue);
    connect(mesh, &Qt3DExtras::QTorusMesh::radiusChanged, radius, &mlayout::DoubleSbLayout::setValue);
    connect(mesh, &Qt3DExtras::QTorusMesh::ringsChanged, rings, &mlayout::IntSbLayout::setValue);
    connect(mesh, &Qt3DExtras::QTorusMesh::slicesChanged, slices, &mlayout::IntSbLayout::setValue);

    vLayout->setContentsMargins(0, 0, 0, 0);
}






PlaneMeshSettingWidget::PlaneMeshSettingWidget(Qt3DExtras::QPlaneMesh *mesh)
{
    setObjectName("Plane");

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






















