#ifndef ABSTRACT_EQUATION_SETTING_WIDGET_H
#define ABSTRACT_EQUATION_SETTING_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QProgressBar>
#include "layoutparts.h"
#include "../numeric/equation.h"


class FormulaExpLineEdit;

class AbstractEquationSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractEquationSettingWidget(const QStringList& initList,
                                           const QStringList& parameter,
                                           QWidget *parent = nullptr);

public:
    void setEquationPixmap(const QPixmap& pixmap);
    void setAlgorithmList(const QStringList& list) { algorithm->setItems(list); }

public slots:
    void setProgressCount(const int max) { progressBar->setMaximum(max); }
    void setCurrentProgress(const int value) { progressBar->setValue(value); }

private:
    void createInitWidget(const QStringList& initList);
    void createParameterWidget(const QStringList& parameter);
    void createOptionWidget();
    void emitParameter();

private slots:
    void initProgressBar() { progressBar->setValue(0); }

private:
    QLabel *equationDisplay;
    QWidget *initWidget;
    QWidget *parameterWidget;
    QWidget *optionWidget;

    QList<FormulaExpLineEdit*> initDisplay;
    QList<FormulaExpLineEdit*> paramDisplay;
    mlayout::ComboBoxLayout *algorithm;
    mlayout::DoubleSbLayout *startTimeSpin;
    mlayout::DoubleSbLayout *endTimeSpin;
    mlayout::DoubleSbLayout *stepTimeSpin;
    QProgressBar *progressBar;

    QPushButton *calculateButton;

signals:
    void calculatationRequested(const equation::EquationParameter& param);
};






class FormulaExpLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    FormulaExpLineEdit(QWidget *parent, QLineEdit *edit);

private slots:
    void applyFormulaExp();

private:
    QLineEdit *edit;
};









#endif // ABSTRACT_EQUATION_SETTING_WIDGET_H
