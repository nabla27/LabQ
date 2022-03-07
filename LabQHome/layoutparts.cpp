#include "layoutparts.h"




RGBEditLayout::RGBEditLayout(QWidget *parent)
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
    setLabelMinimumWidth(SETTING_LABEL_WIDTH);

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


ComboEditLayout::ComboEditLayout(QWidget *parent, const QString& text)
{
    label = new QLabel(text, parent);
    combo = new QComboBox(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(combo);
    addItem(spacer);

    setLabelMinimumWidth(SETTING_LABEL_WIDTH);
    setComboMinimumWidth(SETTING_EDIT_LWIDTH);

    connect(combo, &QComboBox::currentIndexChanged, [this](){ emit currentComboIndexChanged(combo->currentIndex()); });
}

void ComboEditLayout::setVisible(bool visible)
{
    label->setVisible(visible);
    combo->setVisible(visible);
}


LineEditLayout::LineEditLayout(QWidget *parent, const QString& text)
{
    label = new QLabel(text, parent);
    lineEdit = new QLineEdit(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(lineEdit);
    addItem(spacer);

    setLabelMinimumWidth(SETTING_LABEL_WIDTH);
    setLineEditMaximumWidth(SETTING_EDIT_LWIDTH);

    connect(lineEdit, &QLineEdit::textEdited, [this](){ emit lineTextEdited(lineEdit->text()); });
    connect(lineEdit, &QLineEdit::textEdited, this, &LineEditLayout::lineStrToDouble);
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


SpinBoxEditLayout::SpinBoxEditLayout(QWidget *parent, const QString& text)
{
    label = new QLabel(text, parent);
    spinBox = new QSpinBox(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(spinBox);
    addItem(spacer);

    setLabelMinimumWidth(SETTING_LABEL_WIDTH);
    setSpinBoxMaximumWidth(SETTING_EDIT_LWIDTH);

    connect(spinBox, &QSpinBox::valueChanged, [this](){ emit spinBoxValueChanged(spinBox->value()); });
}

void SpinBoxEditLayout::setVisible(bool visible)
{
    label->setVisible(visible);
    spinBox->setVisible(visible);
}

CheckBoxLayout::CheckBoxLayout(QWidget *parent, const QString& text)
{
    label = new QLabel(text, parent);
    checkBox = new QCheckBox(parent);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(label);
    addWidget(checkBox);
    addItem(spacer);

    setLabelMinimumWidth(SETTING_LABEL_WIDTH);

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





















