#ifndef PDEQUATIONSETTINGWIDGET_H
#define PDEQUATIONSETTINGWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "abstract_equation_setting_widget.h"
#include "../numeric/pde.h"

class ConditionWidget;

class PDEquationSettingWidget : public QWidget
{
    Q_OBJECT
public:
    enum class PDE
    {
        WaveEquation
    };
    QList<QStringList> eqInfo =
    {
        { ":/equation_wave", "c" }
    };

    Q_ENUM(PDE)

public:
    explicit PDEquationSettingWidget(QWidget *parent = nullptr);

public:
    QList<equation::InitWithFormulaExpCondition::Range> ranges() const;
    QStringList conditionFormula() const;
    QList<float> parameter() const;
    PDE eqType() const { return PDE(eqCombo->currentIndex()); }


private slots:
    void changeEq(const int index);
    void addInitialization();
    void removeInitialization();
    //void emitEquationChanging(const int index);
    //void readSetting();

private:
    QComboBox *eqCombo;
    QLabel *imgLabel;
    QList<QLabel*> paramLabel;
    QList<QLineEdit*> paramEdit;
    QList<FormulaExpLineEdit*> paramResult;
    QVBoxLayout *conditionLayout;
    QList<ConditionWidget*> conditionList;

    const int paramMaxCount = 5;

signals:
    //void set(const QList<equation::InitWithFormulaExpCondition::Range>& range,
    //         const QStringList& explist,
    //         const int index,
    //         const QList<float>& parameter);
    void equationChanged(const QString& eqName);
};








class ConditionWidget : public QWidget
{
    Q_OBJECT
public:
    ConditionWidget(QWidget *prarent) ;

    QString xMin() const { return xmin->text(); }
    QString xMax() const { return xmax->text(); }
    QString zMin() const { return zmin->text(); }
    QString zMax() const { return zmax->text(); }
    QString formulaExp() const { return formula->text(); }

private:
    QLineEdit *xmin;
    QLineEdit *xmax;
    QLineEdit *zmin;
    QLineEdit *zmax;
    QLineEdit *formula;
};

#endif // PDEQUATIONSETTINGWIDGET_H
