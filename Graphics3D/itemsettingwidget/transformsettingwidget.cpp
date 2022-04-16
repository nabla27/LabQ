#include "transformsettingwidget.h"



Layout3Dparam::Layout3Dparam(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    QLabel *labelX = new QLabel("X", parent);
    QLabel *labelY = new QLabel("Y", parent);
    QLabel *labelZ = new QLabel("Z", parent);
    editX = new QLineEdit(parent);
    editY = new QLineEdit(parent);
    editZ = new QLineEdit(parent);

    addWidget(label);
    addWidget(labelX);
    addWidget(editX);
    addWidget(labelY);
    addWidget(editY);
    addWidget(labelZ);
    addWidget(editZ);

    label->setFixedWidth(labelWidth);
    const int editorWidth = 40;
    editX->setFixedWidth(editorWidth);
    editY->setFixedWidth(editorWidth);
    editZ->setFixedWidth(editorWidth);

    connect(editX, &QLineEdit::editingFinished, this, &Layout3Dparam::emitXEdited);
    connect(editY, &QLineEdit::editingFinished, this, &Layout3Dparam::emitYEdited);
    connect(editZ, &QLineEdit::editingFinished, this, &Layout3Dparam::emitZEdited);
}

void Layout3Dparam::setV3Value(const QVector3D& vec)
{
    editX->setText(QString::number(vec.x()));
    editY->setText(QString::number(vec.y()));
    editZ->setText(QString::number(vec.z()));
}

void Layout3Dparam::setQuaternionValue(const QQuaternion& qut)
{
    editX->setText(QString::number(qut.x()));
    editY->setText(QString::number(qut.y()));
    editZ->setText(QString::number(qut.z()));
}

void Layout3Dparam::emitXEdited()
{
    emit xEdited(editX->text().toFloat());
    emit xyzEditedVector(QVector3D(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat()));
    QQuaternion quaternion;
    quaternion.setVector(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat());
    emit xyzEditedQuaternion(quaternion);
}
void Layout3Dparam::emitYEdited()
{
    emit yEdited(editY->text().toFloat());
    emit xyzEditedVector(QVector3D(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat()));
    QQuaternion quaternion;
    quaternion.setVector(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat());
    emit xyzEditedQuaternion(quaternion);
}
void Layout3Dparam::emitZEdited()
{
    emit zEdited(editZ->text().toFloat());
    emit xyzEditedVector(QVector3D(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat()));
    QQuaternion quaternion;
    quaternion.setVector(editX->text().toFloat(), editZ->text().toFloat(),  editZ->text().toFloat());
    emit xyzEditedQuaternion(quaternion);
}




TransformSettingWidget::TransformSettingWidget(Qt3DCore::QTransform *transform,
                                               QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    Layout3Dparam *position = new Layout3Dparam("Position", this);
    Layout3Dparam *rotation = new Layout3Dparam("Rotation", this);
    Layout3Dparam *scale = new Layout3Dparam("Scale", this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(position);
    vLayout->addLayout(rotation);
    vLayout->addLayout(scale);
    vLayout->addItem(spacer);

    rotation->setQuaternionValue(transform->rotation());
    scale->setV3Value(transform->scale3D());

    connect(rotation, &Layout3Dparam::xEdited, transform, &Qt3DCore::QTransform::setRotationX);
    connect(rotation, &Layout3Dparam::yEdited, transform, &Qt3DCore::QTransform::setRotationY);
    connect(rotation, &Layout3Dparam::zEdited, transform, &Qt3DCore::QTransform::setRotationZ);
    connect(scale, &Layout3Dparam::xyzEditedVector, transform, &Qt3DCore::QTransform::setScale3D);
    connect(transform, &Qt3DCore::QTransform::rotationXChanged, rotation, &Layout3Dparam::setX);
    connect(transform, &Qt3DCore::QTransform::rotationYChanged, rotation, &Layout3Dparam::setY);
    connect(transform, &Qt3DCore::QTransform::rotationZChanged, rotation, &Layout3Dparam::setZ);
    connect(transform, &Qt3DCore::QTransform::scale3DChanged, scale, &Layout3Dparam::setV3Value);

    vLayout->setContentsMargins(0, 0, 0, 0);
}


