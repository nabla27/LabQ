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
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(position);
    vLayout->addLayout(rotation);
    vLayout->addLayout(scale);
    vLayout->addLayout(matrixButton);
    TransformMatrixWidget *w = new TransformMatrixWidget;
    vLayout->addWidget(w);
    w->hide();
    connect(matrixButton, &mlayout::PushButtonLayout::released, w, &TransformMatrixWidget::show);
    vLayout->addItem(spacer);

    position->setV3Value(transform->translation());
    rotation->setQuaternionValue(transform->rotation());
    scale->setV3Value(transform->scale3D());

    connect(position, &mlayout::Layout3DParam::xyzEditedVector, transform, &Qt3DCore::QTransform::setTranslation);
    connect(rotation, &mlayout::Layout3DParam::xEdited, transform, &Qt3DCore::QTransform::setRotationX);
    connect(rotation, &mlayout::Layout3DParam::yEdited, transform, &Qt3DCore::QTransform::setRotationY);
    connect(rotation, &mlayout::Layout3DParam::zEdited, transform, &Qt3DCore::QTransform::setRotationZ);
    connect(scale, &mlayout::Layout3DParam::xyzEditedVector, transform, &Qt3DCore::QTransform::setScale3D);

    connect(transform, &Qt3DCore::QTransform::rotationXChanged, rotation, &mlayout::Layout3DParam::setX);
    connect(transform, &Qt3DCore::QTransform::rotationYChanged, rotation, &mlayout::Layout3DParam::setY);
    connect(transform, &Qt3DCore::QTransform::rotationZChanged, rotation, &mlayout::Layout3DParam::setZ);
    connect(transform, &Qt3DCore::QTransform::scale3DChanged, scale, &mlayout::Layout3DParam::setV3Value);

    vLayout->setContentsMargins(0, 0, 0, 0);
}





TransformMatrixWidget::TransformMatrixWidget()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *r1Layout = new QHBoxLayout(this);
    QLabel *r1Label = new QLabel("", this);
    QLineEdit *c11 = new QLineEdit(this);
    QLineEdit *c12 = new QLineEdit(this);
    QLineEdit *c13 = new QLineEdit(this);
    QLineEdit *c14 = new QLineEdit(this);

    QHBoxLayout *r2Layout = new QHBoxLayout(this);
    QLabel *r2Label = new QLabel("", this);
    QLineEdit *c21 = new QLineEdit(this);
    QLineEdit *c22 = new QLineEdit(this);
    QLineEdit *c23 = new QLineEdit(this);
    QLineEdit *c24 = new QLineEdit(this);

    QHBoxLayout *r3Layout = new QHBoxLayout(this);
    QLabel *r3Label = new QLabel("", this);
    QLineEdit *c31 = new QLineEdit(this);
    QLineEdit *c32 = new QLineEdit(this);
    QLineEdit *c33 = new QLineEdit(this);
    QLineEdit *c34 = new QLineEdit(this);

    QHBoxLayout *r4Layout = new QHBoxLayout(this);
    QLabel *r4Label = new QLabel("", this);
    QLineEdit *c41 = new QLineEdit(this);
    QLineEdit *c42 = new QLineEdit(this);
    QLineEdit *c43 = new QLineEdit(this);
    QLineEdit *c44 = new QLineEdit(this);

    vLayout->addLayout(r1Layout);
    vLayout->addLayout(r2Layout);
    vLayout->addLayout(r3Layout);
    vLayout->addLayout(r4Layout);
    r1Layout->addWidget(r1Label);
    r1Layout->addWidget(c11);
    r1Layout->addWidget(c12);
    r1Layout->addWidget(c13);
    r1Layout->addWidget(c14);
    r2Layout->addWidget(r2Label);
    r2Layout->addWidget(c21);
    r2Layout->addWidget(c22);
    r2Layout->addWidget(c23);
    r2Layout->addWidget(c24);
    r3Layout->addWidget(r3Label);
    r3Layout->addWidget(c31);
    r3Layout->addWidget(c32);
    r3Layout->addWidget(c33);
    r3Layout->addWidget(c34);
    r4Layout->addWidget(r4Label);
    r4Layout->addWidget(c41);
    r4Layout->addWidget(c42);
    r4Layout->addWidget(c43);
    r4Layout->addWidget(c44);

    r1Label->setFixedWidth(100);
    r2Label->setFixedWidth(100);
    r3Label->setFixedWidth(100);
    r4Label->setFixedWidth(100);

    //r1Layout->setContentsMargins(0, 0, 0, 0);
    //r2Layout->setContentsMargins(0, 0, 0, 0);
    //r3Layout->setContentsMargins(0, 0, 0, 0);
    //r4Layout->setContentsMargins(0, 0, 0, 0);

    vLayout->setContentsMargins(0, 0, 0, 0);
    //connect(table, &QTableWidget::itemChanged, this, &TransformMatrixWidget::emitMatrixChanging);
}

void TransformMatrixWidget::setMatrix(const QMatrix4x4 &matrix)
{
    for(size_t i = 0; i < 4; ++i){
        for(size_t j = 0; j < 4; ++j)
        {
            QTableWidgetItem *item = table->item(i, j);
            if(item) item->setText(QString::number(matrix(i, j)));
            else
            {
                item = new QTableWidgetItem(QString::number(matrix(i, j)));
                table->setItem(i, j, item);
            }
        }
    }
}

void TransformMatrixWidget::emitMatrixChanging()
{
    QMatrix4x4 matrix;

    for(size_t i = 0; i < 4; ++i){
        for(size_t j = 0; j < 4; ++j)
        {
            QTableWidgetItem *item = table->item(i, j);
            if(item) matrix(i, j) = item->text().toFloat();
        }
    }

    emit matrixChanged(matrix);
}








