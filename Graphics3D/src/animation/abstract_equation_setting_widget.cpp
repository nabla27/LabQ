#include "abstract_equation_setting_widget.h"

static const int value_display_width = 90;
static const int label_width_param = 20;
static const int label_width_option = 70;

AbstractEquationSettingWidget::AbstractEquationSettingWidget(const QStringList& initList,
                                                             const QStringList& parameter,
                                                             QWidget *parent)
    : QWidget(parent)
    , equationDisplay(new QLabel(this))
    , initWidget(new QWidget(this))
    , parameterWidget(new QWidget(this))
    , optionWidget(new QWidget(this))
    , algorithm(new mlayout::ComboBoxLayout("Algorithm", this, label_width_option))
    , startTimeSpin(new mlayout::DoubleSbLayout("Start", this, label_width_option))
    , endTimeSpin(new mlayout::DoubleSbLayout("End", this, label_width_option))
    , stepTimeSpin(new mlayout::DoubleSbLayout("Step", this, label_width_option))
    , progressBar(new QProgressBar(this))
    , calculateButton(new QPushButton("Calculate", this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    QVBoxLayout *parameterLayout = new QVBoxLayout;
    QSpacerItem *parameterSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(mainLayout);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    topLayout->addWidget(equationDisplay);
    bottomLayout->addLayout(parameterLayout);
    bottomLayout->addWidget(optionWidget);
    parameterLayout->addWidget(initWidget);
    parameterLayout->addWidget(parameterWidget);
    parameterLayout->addItem(parameterSpacer);

    equationDisplay->setFrameShape(QFrame::Shape::Box);
    equationDisplay->setMargin(10);
    startTimeSpin->setSpinBoxMinValue(0.00);
    startTimeSpin->setSpinBoxMaxValue(10000.00);
    endTimeSpin->setSpinBoxMinValue(0.00);
    endTimeSpin->setSpinBoxMaxValue(10000.00);
    stepTimeSpin->setSpinBoxMinValue(0.00);
    progressBar->setMinimum(0);
    progressBar->setTextVisible(false);

    createInitWidget(initList);
    createParameterWidget(parameter);
    createOptionWidget();
}

void AbstractEquationSettingWidget::setEquationPixmap(const QPixmap &pixmap)
{
    equationDisplay->setPixmap(pixmap);
}

void AbstractEquationSettingWidget::createInitWidget(const QStringList &initList)
{
    const qsizetype initCount = initList.count();
    QVBoxLayout *vLayout = new QVBoxLayout(initWidget);
    initWidget->setLayout(vLayout);
    initDisplay.resize(initCount);

    for(qsizetype i = 0; i < initCount; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout;
        QLabel *label = new QLabel(initList.at(i), initWidget);
        QLineEdit *edit = new QLineEdit(initWidget);
        initDisplay[i] = new FormulaExpLineEdit(initWidget, edit);

        hLayout->addWidget(label);
        hLayout->addWidget(edit);
        hLayout->addWidget(initDisplay.at(i));

        label->setFixedWidth(label_width_param);
        initDisplay[i]->setFixedWidth(value_display_width);
        initDisplay[i]->setReadOnly(true);
        vLayout->addLayout(hLayout);

        connect(edit, &QLineEdit::editingFinished, this, &AbstractEquationSettingWidget::initProgressBar);
    }

    initWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
}

void AbstractEquationSettingWidget::createParameterWidget(const QStringList &parameter)
{
    const qsizetype paramCount = parameter.count();
    QVBoxLayout *vLayout = new QVBoxLayout(parameterWidget);
    parameterWidget->setLayout(vLayout);
    paramDisplay.resize(paramCount);

    for(qsizetype i = 0; i < paramCount; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout;
        QLabel *label = new QLabel(parameter.at(i), parameterWidget);
        QLineEdit *edit = new QLineEdit(parameterWidget);
        paramDisplay[i] = new FormulaExpLineEdit(parameterWidget, edit);

        hLayout->addWidget(label);
        hLayout->addWidget(edit);
        hLayout->addWidget(paramDisplay.at(i));

        label->setFixedWidth(label_width_param);
        paramDisplay[i]->setFixedWidth(value_display_width);
        paramDisplay[i]->setReadOnly(true);
        vLayout->addLayout(hLayout);

        connect(edit, &QLineEdit::editingFinished, this, &AbstractEquationSettingWidget::initProgressBar);
    }

    parameterWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
}

void AbstractEquationSettingWidget::createOptionWidget()
{
    QVBoxLayout *vLayout = new QVBoxLayout(optionWidget);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QHBoxLayout *hLayout = new QHBoxLayout;
    optionWidget->setLayout(vLayout);

    vLayout->addLayout(algorithm);
    vLayout->addLayout(startTimeSpin);
    vLayout->addLayout(endTimeSpin);
    vLayout->addLayout(stepTimeSpin);
    vLayout->addItem(spacer);
    vLayout->addLayout(hLayout);
    hLayout->addWidget(progressBar);
    hLayout->addWidget(calculateButton);

    /* 変更されたらprogreeBarをリセット */
    connect(algorithm, &mlayout::ComboBoxLayout::currentIndexChanged, this, &AbstractEquationSettingWidget::initProgressBar);
    connect(startTimeSpin, &mlayout::DoubleSbLayout::valueChanged, this, &AbstractEquationSettingWidget::initProgressBar);
    connect(endTimeSpin, &mlayout::DoubleSbLayout::valueChanged, this, &AbstractEquationSettingWidget::initProgressBar);
    connect(stepTimeSpin, &mlayout::DoubleSbLayout::valueChanged, this, &AbstractEquationSettingWidget::initProgressBar);

    connect(calculateButton, &QPushButton::released, this, &AbstractEquationSettingWidget::emitParameter);
}

void AbstractEquationSettingWidget::emitParameter()
{
    const qsizetype initCount = initDisplay.count();
    const qsizetype paramCount = paramDisplay.count();

    equation::EquationParameter p;
    p.initValue.resize(initCount);
    p.paramValue.resize(paramCount);

    for(qsizetype i = 0; i < initCount; ++i)
        p.initValue[i] = initDisplay.at(i)->text().toDouble();
    for(qsizetype i = 0; i < paramCount; ++i)
        p.paramValue[i] = paramDisplay.at(i)->text().toDouble();

    p.algorithmType = algorithm->currentIndex();
    p.startT = startTimeSpin->value();
    p.endT = endTimeSpin->value();
    p.step = stepTimeSpin->value();

    /* 無効なパラメータの場合 */
    if(p.startT > p.endT)
    {
        endTimeSpin->setTextColor(Qt::red);
        return;
    }
    if(p.step > p.endT - p.startT || p.step == 0)
    {
        stepTimeSpin->setTextColor(Qt::red);
        return;
    }


    endTimeSpin->setTextColor(Qt::black);
    stepTimeSpin->setTextColor(Qt::black);

    emit calculatationRequested(p);
}








FormulaExpLineEdit::FormulaExpLineEdit(QWidget *parent, QLineEdit *edit)
    : QLineEdit(parent)
    , edit(edit)
{
    connect(edit, &QLineEdit::editingFinished, this, &FormulaExpLineEdit::applyFormulaExp);
    setReadOnly(true);
}

void FormulaExpLineEdit::applyFormulaExp()
{
    const QString exp = edit->text();
    if(exp.isEmpty()) return;

    FormulaExp formula(exp);
    setText(QString::number(formula.calculate()));
}






