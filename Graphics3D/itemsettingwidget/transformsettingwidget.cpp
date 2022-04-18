#include "transformsettingwidget.h"


TransformSettingWidget::TransformSettingWidget(Qt3DCore::QTransform *transform,
                                               QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::Layout3DParam *position = new mlayout::Layout3DParam("Position", this);
    mlayout::Layout3DParam *rotation = new mlayout::Layout3DParam("Rotation", this);
    mlayout::Layout3DParam *scale = new mlayout::Layout3DParam("Scale", this);
    mlayout::PushButtonLayout *matrixButton = new mlayout::PushButtonLayout("Matrix", this, 100);
    TransformMatrixWidget *matrixWidget = new TransformMatrixWidget(this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(position);
    vLayout->addLayout(rotation);
    vLayout->addLayout(scale);
    vLayout->addLayout(matrixButton);
    vLayout->addWidget(matrixWidget);
    vLayout->addItem(spacer);

    position->setV3Value(transform->translation());
    rotation->setQuaternionValue(transform->rotation());
    scale->setV3Value(transform->scale3D());
    matrixWidget->setMatrix(transform->matrix());
    matrixWidget->setVisible(false);

    connect(position, &mlayout::Layout3DParam::xyzEditedVector, transform, &Qt3DCore::QTransform::setTranslation);
    connect(rotation, &mlayout::Layout3DParam::xEdited, transform, &Qt3DCore::QTransform::setRotationX);
    connect(rotation, &mlayout::Layout3DParam::yEdited, transform, &Qt3DCore::QTransform::setRotationY);
    connect(rotation, &mlayout::Layout3DParam::zEdited, transform, &Qt3DCore::QTransform::setRotationZ);
    connect(scale, &mlayout::Layout3DParam::xyzEditedVector, transform, &Qt3DCore::QTransform::setScale3D);
    connect(matrixButton, &mlayout::PushButtonLayout::released, matrixWidget, &TransformMatrixWidget::changeVisible);
    connect(matrixWidget, &TransformMatrixWidget::matrixChanged, transform, &Qt3DCore::QTransform::setMatrix);

    connect(transform, &Qt3DCore::QTransform::rotationXChanged, rotation, &mlayout::Layout3DParam::setX);
    connect(transform, &Qt3DCore::QTransform::rotationYChanged, rotation, &mlayout::Layout3DParam::setY);
    connect(transform, &Qt3DCore::QTransform::rotationZChanged, rotation, &mlayout::Layout3DParam::setZ);
    connect(transform, &Qt3DCore::QTransform::scale3DChanged, scale, &mlayout::Layout3DParam::setV3Value);

    vLayout->setContentsMargins(0, 0, 0, 0);
}





TransformMatrixWidget::TransformMatrixWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);

    cell.resize(4);

    for(size_t i = 0; i < 4; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout;
        QLabel *label = new QLabel("", this);
        vLayout->addLayout(hLayout);
        hLayout->addWidget(label);

        cell[i].resize(4);

        for(size_t j = 0; j < 4; ++j)
        {
            cell[i][j] = new QLineEdit(this);
            hLayout->addWidget(cell.at(i).at(j));
            connect(cell[i][j], &QLineEdit::editingFinished, this, &TransformMatrixWidget::emitMatrixChanging);
        }

        label->setFixedWidth(100);
    }

    setLayout(vLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
}

void TransformMatrixWidget::setMatrix(const QMatrix4x4 &matrix)
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            cell.at(i).at(j)->setText(QString::number(matrix(i, j)));
}

void TransformMatrixWidget::emitMatrixChanging()
{
    QMatrix4x4 matrix;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            matrix(i, j) = cell.at(i).at(j)->text().toFloat();

    emit matrixChanged(matrix);
}








