#ifndef LAYOUTPARTS_H
#define LAYOUTPARTS_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QToolBox>
#include <QLabel>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QComboBox>
#include <QSpacerItem>
#include <QSpinBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QDateTime>
#include <QQuaternion>
#include <QColorDialog>
#include <QDoubleSpinBox>

#define SETTING_EDIT_LWIDTH 110
#define SETTING_EDIT_SWIDTH 35
#define QT_GLOBAL_COLOR_COUNT 19
#define SETTING_LABEL_WIDTH 80


class RGBEditLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    RGBEditLayout(QWidget *parent, const int labelWidth = SETTING_LABEL_WIDTH);

public:
    void setLabelMinimumWidth(const int width) { label->setMinimumWidth(width); }
    void setEditMaximumWidth(const int width) { rEdit->setMaximumWidth(width);
                                                gEdit->setMaximumWidth(width);
                                                bEdit->setMaximumWidth(width); }
    int getColorR() const { return rEdit->text().toInt(); }
    int getColorG() const { return gEdit->text().toInt(); }
    int getColorB() const { return bEdit->text().toInt(); }
    QColor getColor() const { return QColor(rEdit->text().toInt(), gEdit->text().toInt(), bEdit->text().toInt()); }

public slots:
    void setColor(const QColor& color);
    void setColor(int eNum);
    void setVisible(bool visible);
    void setReadOnly(bool readOnly);
    void setColorAndEditable(const int index);

signals:
    void colorEdited(const QColor& color);

private:
    QLabel *label;
    QLineEdit *rEdit;
    QLineEdit *gEdit;
    QLineEdit *bEdit;
    QSpacerItem *spacer;
};








class ComboEditLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    ComboEditLayout(QWidget *parent, const QString& text = "", const int labelWidth = SETTING_LABEL_WIDTH);

public:
    void setLabelMinimumWidth(const int width) { label->setMinimumWidth(width); }
    void setComboMaximumWidth(const int width) { combo->setMaximumWidth(width); }
    void setComboMinimumWidth(const int width) { combo->setMinimumWidth(width); }
    void insertComboItems(int index, const QStringList& texts) { combo->insertItems(index, texts); }
    int currentComboIndex() const { return combo->currentIndex(); }
    QString currentComboText() const { return combo->currentText(); }

public slots:
    void setComboCurrentIndex(const int index) { combo->setCurrentIndex(index); }
    void setVisible(bool visible);

signals:
    void currentComboIndexChanged(int index);

private:
    QLabel *label;
    QComboBox *combo;
    QSpacerItem *spacer;
};












class LineEditLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    LineEditLayout(QWidget *parent, const QString& text = "", const int labelWidth = SETTING_LABEL_WIDTH, const int editWidth = SETTING_EDIT_LWIDTH);

public:
    void setLabelMinimumWidth(const int width) { label->setMinimumWidth(width); }
    void setLineEditMaximumWidth(const int width) { lineEdit->setMaximumWidth(width); }
    void setReadOnly(const bool flag) { lineEdit->setReadOnly(flag); }
    QString lineEditText() const { return lineEdit->text(); }

public slots:
    void setLineEditText(const QString& text) { lineEdit->setText(text); }
    void setLineEditValue(const double& val) { lineEdit->setText(QString::number(val)); }
    void setLineEditDate(const QDateTime& date) { lineEdit->setText(date.toString()); }
    void setVisible(bool visible);

signals:
    void lineTextEdited(const QString& text);
    void lineValueEdited(const double& value);
    void lineDateEdited(const QDateTime& date);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *spacer;
    void lineStrToDouble(const QString& text);
    void lineStrToDate(const QString& text);
};









class SpinBoxEditLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    SpinBoxEditLayout(QWidget *parent, const QString& text = "", const int labelWidth = SETTING_LABEL_WIDTH);

public:
    void setLabelMinimumWidth(const int width) { label->setMinimumWidth(width); }
    void setSpinBoxMaximumWidth(const int width) { spinBox->setMaximumWidth(width); }
    void setSpinBoxMaxValue(const int max) { spinBox->setMaximum(max); }
    int spinBoxValue() const { return spinBox->value(); }

public slots:
    void setSpinBoxValue(const int value) { spinBox->setValue(value); }
    void setVisible(bool visible);

signals:
    void spinBoxValueChanged(const int value);

private:
    QLabel *label;
    QSpinBox *spinBox;
    QSpacerItem *spacer;
};






class CheckBoxLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    explicit CheckBoxLayout(QWidget *parent, const QString& text = "", const int labelWidth = SETTING_LABEL_WIDTH);

public:
    void setLabelMinimumWidth(const int width) { label->setMinimumWidth(width); }
    void setChecked(const bool checked) { checkBox->setChecked(checked); }
    void setVisible(const bool visible);
    bool isChecked() const { return checkBox->isChecked(); }

signals:
    void checkBoxToggled(const bool checked);

private:
    QLabel *label;
    QCheckBox *checkBox;
    QSpacerItem *spacer;
};











class PushButtonLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    PushButtonLayout(QWidget *parent, const QString& text = ""){
        button = new QPushButton(text, parent);
        addWidget(button, 0, Qt::AlignCenter);
        connect(button, &QPushButton::released, this, &PushButtonLayout::buttonReleased);
    };

public:
    void setButtonMaximumWidth(const int width) { button->setMaximumWidth(width); }
    void setButtonMinimumWidth(const int width) { button->setMinimumWidth(width); }

private:
    QPushButton *button;

signals:
    void buttonReleased();
};









class BlankSpaceLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    BlankSpaceLayout(const int width, const int height){
        spacer = new QSpacerItem(width, height, QSizePolicy::Maximum, QSizePolicy::Maximum);
        addItem(spacer);
    }

private:
    QSpacerItem *spacer;
};






class HorizontalDragBar : public QPushButton
{
    Q_OBJECT

public:
    explicit HorizontalDragBar(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPoint;

signals:
    void barDraged(const int dy);
};

class VerticalDragBar : public QPushButton
{
    Q_OBJECT

public:
    explicit VerticalDragBar(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPoint;

signals:
    void barDraged(const int dx);
};





namespace mlayout
{


class Layout3DParam : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit Layout3DParam(const QString& name, QWidget *parent, const int labelWidth = 80);

public slots:
    void setV3Value(const QVector3D& vec);
    void setQuaternionValue(const QQuaternion& qut);
    void setX(const float& val) { editX->setText(QString::number(val)); }
    void setY(const float& val) { editY->setText(QString::number(val)); }
    void setZ(const float& val) { editZ->setText(QString::number(val)); }

private:
    QLineEdit *editX;
    QLineEdit *editY;
    QLineEdit *editZ;

private slots:
    void emitXEdited();
    void emitYEdited();
    void emitZEdited();

signals:
    void xEdited(const float& val);
    void yEdited(const float& val);
    void zEdited(const float& val);
    void xyzEditedVector(const QVector3D& vec);
    void xyzEditedQuaternion(const QQuaternion& qut);
};





class Layout1DParam : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit Layout1DParam(const QString& name, QWidget *parent, const int labelWidth = 100);

public slots:
    void setValue(const float& val) { editor->setText(QString::number(val)); }

private:
    QLineEdit *editor;

private slots:
    void emitEdited() { emit edited(editor->text().toFloat()); }

signals:
    void edited(const float& val);
};



class ColorButtonLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit ColorButtonLayout(const QString& name, QWidget *parent, const int labelWidth = 100);

public:
    QColor getColor() const { return dialog->currentColor(); }

public slots:
    void setColor(const QColor& color) { dialog->setCurrentColor(color); }

private slots:
    void emitColorChanging(const QColor& color);

private:
    QPushButton *button;
    QColorDialog *dialog;

signals:
    void colorChanged(const QColor& color);
};




class DoubleSbLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit DoubleSbLayout(const QString& name, QWidget *parent, const int labelWidth);
    void setSpinBoxMaxValue(const double max) { spinBox->setMaximum(max); }
    void setSpinBoxMinValue(const double min) { spinBox->setMinimum(min); }
    void setTextColor(const QColor& color);
    void setBackColor(const QColor& color);
    double value() { return spinBox->value(); }

public slots:
    void setValue(const double& value) { spinBox->setValue(value); }

private:
    QDoubleSpinBox *spinBox;

signals:
    void valueChanged(const double& value);
};






class IntSbLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit IntSbLayout(const QString& name, QWidget *parent, const int labelWidth);
    void setSpinBoxMaxValue(const int max) { spinBox->setMaximum(max); }
    void setSpinBoxMinValue(const int min) { spinBox->setMinimum(min); }
    int value() { return spinBox->value(); }

public slots:
    void setValue(const int value) { spinBox->setValue(value); }

private:
    QSpinBox *spinBox;

signals:
    void valueChanged(const int& value);
};






class ComboBoxLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit ComboBoxLayout(const QString& name, QWidget *parent, const int labelWidth);
    void setItems(const QStringList& list) { combo->addItems(list); }
    int currentIndex() const { return combo->currentIndex(); }

public slots:
    void setCurrentIndex(const int index) { combo->setCurrentIndex(index); }

private:
    QComboBox *combo;

signals:
    void currentIndexChanged(const int index);
};





class PushButtonLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit PushButtonLayout(const QString& name, QWidget *parent, const int labelWidth);
    void setButtonText(const QString& text) { button->setText(text); }

private:
    QPushButton *button;

signals:
    void released();
};



class CheckBoxLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit CheckBoxLayout(const QString& name, QWidget *parent, const int labelWidth);
    void setChecked(const bool checked) { checkBox->setChecked(checked); }

private:
    QCheckBox *checkBox;

signals:
    void clicked(const bool checked);
};















} // namespace mlayout

#endif // LAYOUTPARTS_H
