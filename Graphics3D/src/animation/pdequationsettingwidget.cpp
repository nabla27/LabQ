#include "pdequationsettingwidget.h"
#include "utility.h"

PDEquationSettingWidget::PDEquationSettingWidget(QWidget *parent)
    : QWidget(parent)
    , eqCombo(new QComboBox(this))
    , imgLabel(new QLabel(this))
    , conditionLayout(new QVBoxLayout)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    //QHBoxLayout *hLayout = new QHBoxLayout;
    //QPushButton *button = new QPushButton("Set", this);
    QLabel *param = new QLabel("Parameter", this);
    QLabel *condition = new QLabel("Condition", this);
    QHBoxLayout *conditionPanel = new QHBoxLayout;
    QPushButton *addConditionButton = new QPushButton("+", this);
    QPushButton *removeConditionButton = new QPushButton("-", this);
    //QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *conditionPanelSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    //vLayout->addLayout(hLayout);
    //hLayout->addWidget(eqCombo);
    //hLayout->addWidget(button);
    //hLayout->addItem(topSpacer);
    vLayout->addWidget(eqCombo);
    vLayout->addWidget(imgLabel);
    vLayout->addWidget(param);

    paramLabel.resize(paramMaxCount);
    paramEdit.resize(paramMaxCount);
    paramResult.resize(paramMaxCount);

    const int label_width = 70;
    const int label_width_param = 10;
    const int editor_width = 200;
    const int result_width = 150;
    const int button_width = 30;

    for(int i = 0; i < paramMaxCount; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout;
        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
        paramLabel[i] = new QLabel(this);
        paramEdit[i] = new QLineEdit(this);
        paramResult[i] = new FormulaExpLineEdit(this, paramEdit[i]);

        hLayout->addWidget(paramLabel.at(i));
        hLayout->addWidget(paramEdit.at(i));
        hLayout->addWidget(paramResult.at(i));
        hLayout->addItem(spacer);
        vLayout->addLayout(hLayout);

        paramLabel[i]->setFixedWidth(label_width_param);
        paramEdit[i]->setFixedWidth(editor_width);
        paramResult[i]->setFixedWidth(result_width);
    }

    vLayout->addLayout(conditionPanel);
    conditionPanel->addWidget(condition);
    conditionPanel->addWidget(addConditionButton);
    conditionPanel->addWidget(removeConditionButton);
    conditionPanel->addItem(conditionPanelSpacer);
    vLayout->addLayout(conditionLayout);
    vLayout->addItem(spacer);

    vLayout->setSpacing(9);
    eqCombo->addItems(enumToStrings(PDE::WaveEquation));
    eqCombo->setCurrentIndex(0);
    eqCombo->setFixedWidth(300);
    param->setFixedWidth(label_width);
    condition->setFixedWidth(label_width);
    addConditionButton->setFixedWidth(button_width);
    removeConditionButton->setFixedWidth(button_width);

    changeEq(0);

    connect(eqCombo, &QComboBox::currentIndexChanged, this, &PDEquationSettingWidget::changeEq);
    //connect(button, &QPushButton::released, this, &PDEquationSettingWidget::readSetting);
    connect(addConditionButton, &QPushButton::released, this, &PDEquationSettingWidget::addInitialization);
    connect(removeConditionButton, &QPushButton::released, this, &PDEquationSettingWidget::removeInitialization);
}

void PDEquationSettingWidget::changeEq(const int index)
{
    const int paramCount = eqInfo.at(index).count() - 1;

    imgLabel->setPixmap(QPixmap(eqInfo.at(index).at(0)));

    for(int i = 0; i < paramCount; ++i)
    {
        paramLabel.at(i)->setText(eqInfo.at(index).at(i + 1));
        paramEdit.at(i)->setText("");
        paramResult.at(i)->setText("");
    }
    for(int j = paramCount; j < paramMaxCount; ++j)
    {
        paramLabel.at(j)->setVisible(false);
        paramEdit.at(j)->setVisible(false);
        paramResult.at(j)->setVisible(false);
    }

    emit equationChanged(enumToString(PDE(index)));
}

void PDEquationSettingWidget::addInitialization()
{
    ConditionWidget *condition = new ConditionWidget(this);
    conditionLayout->addWidget(condition);
    conditionList.append(condition);
}

void PDEquationSettingWidget::removeInitialization()
{
    if(conditionList.count() == 0) return;

    ConditionWidget *condition = conditionList.takeLast();
    conditionLayout->removeWidget(condition);

    const QRect rect = condition->geometry();

    delete condition;

    /* 削除した分、ウィンドウサイズを縮小する
     * ひとwidget分の空白が空いてしまう。以下のように繰り返すと2回に一回は適当にリサイズされる*/
    setMaximumHeight(rect.y());
    setMaximumHeight(height());
    setMaximumHeight(rect.y());
}

//void PDEquationSettingWidget::readSetting()
//{
//    const qsizetype conditionCount = conditionList.count();
//    QList<equation::InitWithFormulaExpCondition::Range> ranges(conditionCount);
//    QStringList explist(conditionCount);
//
//    for(qsizetype i = 0; i < conditionCount; ++i)
//    {
//        const QString xMin = conditionList.at(i)->xMin();
//        const QString xMax = conditionList.at(i)->xMax();
//        const QString zMin = conditionList.at(i)->zMin();
//        const QString zMax = conditionList.at(i)->zMax();
//
//        if(!xMin.isEmpty())
//            ranges[i].xl = { xMin.toFloat(), true };
//        if(!xMax.isEmpty())
//            ranges[i].xr = { xMax.toFloat(), true };
//        if(!zMin.isEmpty())
//            ranges[i].zl = { zMin.toFloat(), true };
//        if(!zMax.isEmpty())
//            ranges[i].zr = { zMax.toFloat(), true };
//
//        explist[i] = conditionList.at(i)->formulaExp();
//    }
//
//    QList<float> parameterList(paramResult.count());
//    for(const FormulaExpLineEdit* param : paramResult)
//        parameterList << param->text().toFloat();
//
//    emit set(ranges, explist, eqCombo->currentIndex(), parameterList);
//}

QList<equation::InitWithFormulaExpCondition::Range> PDEquationSettingWidget::ranges() const
{
    const qsizetype conditionCount = conditionList.count();
    QList<equation::InitWithFormulaExpCondition::Range> ranges(conditionCount);

    for(qsizetype i = 0; i < conditionCount; ++i)
    {
        const QString xMin = conditionList.at(i)->xMin();
        const QString xMax = conditionList.at(i)->xMax();
        const QString zMin = conditionList.at(i)->zMin();
        const QString zMax = conditionList.at(i)->zMax();

        if(!xMin.isEmpty())
            ranges[i].xl = { xMin.toFloat(), true };
        if(!xMax.isEmpty())
            ranges[i].xr = { xMax.toFloat(), true };
        if(!zMin.isEmpty())
            ranges[i].zl = { zMin.toFloat(), true };
        if(!zMax.isEmpty())
            ranges[i].zr = { zMax.toFloat(), true };
    }

    return ranges;
}

QStringList PDEquationSettingWidget::conditionFormula() const
{
    QStringList explist;

    for(ConditionWidget *w : conditionList)
        explist << w->formulaExp();

    return explist;
}

QList<float> PDEquationSettingWidget::parameter() const
{
    QList<float> parameterList;

    for(const FormulaExpLineEdit* param : paramResult)
        parameterList << param->text().toFloat();

    return parameterList;
}













ConditionWidget::ConditionWidget(QWidget *parent)
    : QWidget(parent)
    , xmin(new QLineEdit(this))
    , xmax(new QLineEdit(this))
    , zmin(new QLineEdit(this))
    , zmax(new QLineEdit(this))
    , formula(new QLineEdit(this))
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QLabel *xrange = new QLabel("≦ X ≦", parent);
    QLabel *zrange = new QLabel("≦ Z ≦", parent);

    setLayout(hLayout);
    hLayout->addWidget(xmin);
    hLayout->addWidget(xrange);
    hLayout->addWidget(xmax);
    hLayout->addWidget(zmin);
    hLayout->addWidget(zrange);
    hLayout->addWidget(zmax);
    hLayout->addWidget(formula);

    const int editor_width = 50;

    xmin->setFixedWidth(editor_width);
    xmax->setFixedWidth(editor_width);
    zmin->setFixedWidth(editor_width);
    zmax->setFixedWidth(editor_width);

    xmin->setAlignment(Qt::AlignmentFlag::AlignRight);
    zmin->setAlignment(Qt::AlignmentFlag::AlignRight);

    hLayout->setContentsMargins(0, 0, 0, 0);
}








