#include "basicmeshsettingwidget.h"




TorusMeshSettingWidget::TorusMeshSettingWidget(Qt3DExtras::QTorusMesh *mesh)
{
    mesh->setRadius(5);
    mesh->setMinorRadius(1);
    mesh->setRings(100);
    mesh->setSlices(20);

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






PlaneMeshSettingWidget::PlaneMeshSettingWidget(Qt3DExtras::QPlaneMesh *mesh)
{
    mesh->setHeight(100);
    mesh->setWidth(100);
}






















