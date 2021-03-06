#include "layoutparts.h"
#include "utility.h"



RGBEditLayout::RGBEditLayout(QWidget *parent, const int labelWidth)
{
    label = new QLabel(parent);
    rEdit = new QLineEdit(parent);
    gEdit = new QLineEdit(parent);
    bEdit = new QLineEdit(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(rEdit);
    addWidget(gEdit);
    addWidget(bEdit);
    addItem(spacer);

    setEditMaximumWidth(25);
    setLabelMinimumWidth(labelWidth);

    connect(rEdit, &QLineEdit::textEdited, [this](){ emit colorEdited(getColor()); });
    connect(gEdit, &QLineEdit::textEdited, [this](){ emit colorEdited(getColor()); });
    connect(bEdit, &QLineEdit::textEdited, [this](){ emit colorEdited(getColor()); });
}

void RGBEditLayout::setColor(const QColor& color)
{
    rEdit->setText(QString::number(color.red()));
    gEdit->setText(QString::number(color.green()));
    bEdit->setText(QString::number(color.blue()));

    emit colorEdited(color);
}

void RGBEditLayout::setColor(int eNum)
{
    QColor color = Qt::GlobalColor(eNum);
    rEdit->setText(QString::number(color.red()));
    gEdit->setText(QString::number(color.green()));
    bEdit->setText(QString::number(color.blue()));

    emit colorEdited(QColor(Qt::GlobalColor(eNum)));
}

void RGBEditLayout::setVisible(bool visible)
{
    label->setVisible(visible);
    rEdit->setVisible(visible);
    gEdit->setVisible(visible);
    bEdit->setVisible(visible);
}

void RGBEditLayout::setReadOnly(bool readOnly)
{
    rEdit->setReadOnly(readOnly);
    gEdit->setReadOnly(readOnly);
    bEdit->setReadOnly(readOnly);
}

void RGBEditLayout::setColorAndEditable(const int index)
{
    if(index > QT_GLOBAL_COLOR_COUNT){
        setReadOnly(false); return;
    }

    setReadOnly(true);
    setColor(index);
}


ComboEditLayout::ComboEditLayout(QWidget *parent, const QString& text, const int labelWidth)
{
    label = new QLabel(text, parent);
    combo = new QComboBox(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(combo);
    addItem(spacer);

    setLabelMinimumWidth(labelWidth);
    setComboMinimumWidth(SETTING_EDIT_LWIDTH);

    connect(combo, &QComboBox::currentIndexChanged, [this](){ emit currentComboIndexChanged(combo->currentIndex()); });
}

void ComboEditLayout::setVisible(bool visible)
{
    label->setVisible(visible);
    combo->setVisible(visible);
}


LineEditLayout::LineEditLayout(QWidget *parent, const QString& text, const int labelWidth, const int editWidth)
{
    label = new QLabel(text, parent);
    lineEdit = new QLineEdit(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(lineEdit);
    addItem(spacer);

    setLabelMinimumWidth(labelWidth);
    setLineEditMaximumWidth(editWidth);

    //connect(lineEdit, &QLineEdit::textEdited, [this](){ emit lineTextEdited(lineEdit->text()); });
    connect(lineEdit, &QLineEdit::textEdited, this, &LineEditLayout::lineTextEdited);
    connect(lineEdit, &QLineEdit::textEdited, this, &LineEditLayout::lineStrToDouble);
    connect(lineEdit, &QLineEdit::textEdited, this, &LineEditLayout::lineStrToDate);

}

void LineEditLayout::setVisible(bool visible)
{
    label->setVisible(visible);
    lineEdit->setVisible(visible);
}

void LineEditLayout::lineStrToDouble(const QString &text)
{
    emit lineValueEdited(text.toDouble());
}

void LineEditLayout::lineStrToDate(const QString &text)
{
    emit lineDateEdited(QDateTime::fromString(text));
}


SpinBoxEditLayout::SpinBoxEditLayout(QWidget *parent, const QString& text, const int labelWidth)
{
    label = new QLabel(text, parent);
    spinBox = new QSpinBox(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(spinBox);
    addItem(spacer);

    setLabelMinimumWidth(labelWidth);
    setSpinBoxMaximumWidth(SETTING_EDIT_LWIDTH);

    connect(spinBox, &QSpinBox::valueChanged, [this](){ emit spinBoxValueChanged(spinBox->value()); });
}

void SpinBoxEditLayout::setVisible(bool visible)
{
    label->setVisible(visible);
    spinBox->setVisible(visible);
}

CheckBoxLayout::CheckBoxLayout(QWidget *parent, const QString& text, const int labelWidth)
{
    label = new QLabel(text, parent);
    checkBox = new QCheckBox(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(checkBox);
    addItem(spacer);

    setLabelMinimumWidth(labelWidth);

    connect(checkBox, &QCheckBox::toggled, this, &CheckBoxLayout::checkBoxToggled);
}

void CheckBoxLayout::setVisible(const bool visible)
{
    label->setVisible(visible);
    checkBox->setVisible(visible);
}







HorizontalDragBar::HorizontalDragBar(QWidget *parent)
    : QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setMaximumHeight(5);
    setCursor(Qt::CursorShape::SplitVCursor);
}

void HorizontalDragBar::mousePressEvent(QMouseEvent *event)
{
    dragStartPoint = event->pos();
    QPushButton::mousePressEvent(event);
}

void HorizontalDragBar::mouseMoveEvent(QMouseEvent *event)
{
    emit barDraged((dragStartPoint - event->pos()).y());
    QPushButton::mouseMoveEvent(event);
}




VerticalDragBar::VerticalDragBar(QWidget *parent)
    : QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    setMaximumWidth(5);
    setCursor(Qt::CursorShape::SplitHCursor);
}

void VerticalDragBar::mousePressEvent(QMouseEvent *event)
{
    dragStartPoint = event->pos();
    QPushButton::mousePressEvent(event);
}

void VerticalDragBar::mouseMoveEvent(QMouseEvent *event)
{
    emit barDraged((dragStartPoint - event->pos()).x());
    QPushButton::mouseMoveEvent(event);
}





namespace mlayout
{
#if 0
Layout3DParam::Layout3DParam(const QString& name, QWidget *parent, const int labelWidth)
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

    connect(editX, &QLineEdit::editingFinished, this, &Layout3DParam::emitXEdited);
    connect(editY, &QLineEdit::editingFinished, this, &Layout3DParam::emitYEdited);
    connect(editZ, &QLineEdit::editingFinished, this, &Layout3DParam::emitZEdited);
}

void Layout3DParam::setV3Value(const QVector3D& vec)
{
    editX->setText(QString::number(vec.x()));
    editY->setText(QString::number(vec.y()));
    editZ->setText(QString::number(vec.z()));
}

void Layout3DParam::setQuaternionValue(const QQuaternion& qut)
{
    editX->setText(QString::number(qut.x()));
    editY->setText(QString::number(qut.y()));
    editZ->setText(QString::number(qut.z()));
}

void Layout3DParam::emitXEdited()
{
    emit xEdited(editX->text().toFloat());
    emit xyzEditedVector(QVector3D(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat()));
    QQuaternion quaternion;
    quaternion.setVector(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat());
    emit xyzEditedQuaternion(quaternion);
}
void Layout3DParam::emitYEdited()
{
    emit yEdited(editY->text().toFloat());
    emit xyzEditedVector(QVector3D(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat()));
    QQuaternion quaternion;
    quaternion.setVector(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat());
    emit xyzEditedQuaternion(quaternion);
}
void Layout3DParam::emitZEdited()
{
    emit zEdited(editZ->text().toFloat());
    emit xyzEditedVector(QVector3D(editX->text().toFloat(), editY->text().toFloat(), editZ->text().toFloat()));
    QQuaternion quaternion;
    quaternion.setVector(editX->text().toFloat(), editZ->text().toFloat(),  editZ->text().toFloat());
    emit xyzEditedQuaternion(quaternion);
}
#else
Layout3DParam::Layout3DParam(QWidget *parent)
{
    QLabel *labelX = new QLabel("x", parent);
    QLabel *labelY = new QLabel("y", parent);
    QLabel *labelZ = new QLabel("z", parent);
    editX = new QDoubleSpinBox(parent);
    editY = new QDoubleSpinBox(parent);
    editZ = new QDoubleSpinBox(parent);

    addWidget(labelX);
    addWidget(editX);
    addWidget(labelY);
    addWidget(editY);
    addWidget(labelZ);
    addWidget(editZ);


    labelX->setMaximumWidth(8); //'X'??????????????????
    labelY->setMaximumWidth(8);
    labelZ->setMaximumWidth(8);

    /* ??????????????????/????????? */
    constexpr double max_spinbox_value = 1e+9;
    constexpr double min_spinbox_value = -1e+8;
    editX->setRange(min_spinbox_value, max_spinbox_value);
    editY->setRange(min_spinbox_value, max_spinbox_value);
    editZ->setRange(min_spinbox_value, max_spinbox_value);

    /* ???????????????4???????????? */
    editX->setDecimals(4);
    editY->setDecimals(4);
    editZ->setDecimals(4);

    connect(editX, &QDoubleSpinBox::valueChanged, this, &Layout3DParam::emitXEdited);
    connect(editY, &QDoubleSpinBox::valueChanged, this, &Layout3DParam::emitYEdited);
    connect(editZ, &QDoubleSpinBox::valueChanged, this, &Layout3DParam::emitZEdited);
}

void Layout3DParam::setV3Value(const QVector3D& vec)
{
    editX->setValue(vec.x());
    editY->setValue(vec.y());
    editZ->setValue(vec.z());
}

void Layout3DParam::setQuaternionValue(const QQuaternion& qut)
{
    editX->setValue(qut.x());
    editY->setValue(qut.y());
    editZ->setValue(qut.z());
}

void Layout3DParam::emitXEdited()
{
    const double x = editX->value();
    const double y = editY->value();
    const double z = editZ->value();

    emit xEdited(x);
    emit xyzEditedVector(QVector3D(x, y, z));
    emit xyzEditedQuaternion(QQuaternion(0, x, y, z));
}

void Layout3DParam::emitYEdited()
{
    const double x = editX->value();
    const double y = editY->value();
    const double z = editZ->value();

    emit yEdited(y);
    emit xyzEditedVector(QVector3D(x, y, z));
    emit xyzEditedQuaternion(QQuaternion(0, x, y, z));
}

void Layout3DParam::emitZEdited()
{
    const double x = editX->value();
    const double y = editY->value();
    const double z = editZ->value();

    emit zEdited(z);
    emit xyzEditedVector(QVector3D(x, y, z));
    emit xyzEditedQuaternion(QQuaternion(0, x, y, z));
}

#endif



Layout1DParam::Layout1DParam(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    editor = new QLineEdit(parent);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(editor);
    addItem(spacer);

    label->setFixedWidth(labelWidth);

    editor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(editor, &QLineEdit::editingFinished, this, &Layout1DParam::emitEdited);
}


ColorButtonLayout::ColorButtonLayout(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    button = new QPushButton(parent);

    addWidget(label);
    addWidget(button);

    label->setFixedWidth(labelWidth);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setAutoFillBackground(true);

    dialog = new QColorDialog(parent);

    connect(button, &QPushButton::released, dialog, &QColorDialog::exec);
    connect(dialog, &QColorDialog::currentColorChanged, this, &ColorButtonLayout::emitColorChanging);
}

void ColorButtonLayout::emitColorChanging(const QColor& color)
{
    button->setText(color.name());

    QPalette palette = button->palette();
    palette.setColor(QPalette::ColorRole::Button, color);
    button->setPalette(palette);

    emit colorChanged(color);
}




DoubleSbLayout::DoubleSbLayout(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    spinBox = new QDoubleSpinBox(parent);

    addWidget(label);
    addWidget(spinBox);

    label->setFixedWidth(labelWidth);
    spinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(spinBox, &QDoubleSpinBox::valueChanged, this, &DoubleSbLayout::valueChanged);
}

void DoubleSbLayout::setTextColor(const QColor &color)
{
    QPalette p = spinBox->palette();
    p.setColor(QPalette::Text, color);
    spinBox->setPalette(p);
}

void DoubleSbLayout::setBackColor(const QColor &color)
{
    QPalette p = spinBox->palette();
    p.setColor(QPalette::Base, color);
    spinBox->setPalette(p);
}






IntSbLayout::IntSbLayout(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    spinBox = new QSpinBox(parent);

    addWidget(label);
    addWidget(spinBox);

    label->setFixedWidth(labelWidth);
    spinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(spinBox, &QSpinBox::valueChanged, this, &IntSbLayout::valueChanged);
}







ComboBoxLayout::ComboBoxLayout(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    combo = new QComboBox(parent);

    addWidget(label);
    addWidget(combo);

    label->setFixedWidth(labelWidth);
    combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(combo, &QComboBox::currentIndexChanged, this, &ComboBoxLayout::currentIndexChanged);
}






PushButtonLayout::PushButtonLayout(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    button = new QPushButton(parent);

    addWidget(label);
    addWidget(button);

    label->setFixedWidth(labelWidth);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(button, &QPushButton::released, this, &PushButtonLayout::released);
}






CheckBoxLayout::CheckBoxLayout(const QString& name, QWidget *parent, const int labelWidth)
{
    QLabel *label = new QLabel(name, parent);
    checkBox = new QCheckBox(parent);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    addWidget(label);
    addWidget(checkBox);
    addItem(spacer);

    label->setFixedWidth(labelWidth);

    connect(checkBox, &QCheckBox::clicked, this, &CheckBoxLayout::clicked);
}







IconLabel::IconLabel(const QString& text, QWidget *parent) : QLabel(text, parent)
{
    normalPalette = this->palette();
    normalFrameShape = this->frameShape();
    hoveredPalette = normalPalette;
    hoveredFrameShape = normalFrameShape;
}
IconLabel::IconLabel(QWidget *parent) : QLabel(parent)
{
    normalPalette = this->palette();
    normalFrameShape = this->frameShape();
    hoveredPalette = normalPalette;
    hoveredFrameShape = normalFrameShape;
}

void IconLabel::enterEvent(QEnterEvent *event)
{
    normalPalette = palette();
    normalFrameShape = frameShape();

    setPalette(hoveredPalette);
    setFrameShape(hoveredFrameShape);

    QLabel::enterEvent(event);
}

void IconLabel::leaveEvent(QEvent *event)
{
    setPalette(normalPalette);
    setFrameShape(normalFrameShape);

    QLabel::leaveEvent(event);
}

void IconLabel::mousePressEvent(QMouseEvent*)
{
    setPalette(normalPalette);
    setFrameShape(normalFrameShape);
}

void IconLabel::mouseReleaseEvent(QMouseEvent *event)
{
    setPalette(hoveredPalette);
    setFrameShape(hoveredFrameShape);

    emit released();

    QLabel::mousePressEvent(event);
}




}// namespace mlayout









