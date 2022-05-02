#include "grid_mesh_setting_widget.h"

#include "../animation/property_animation_setting.h"
#include "../numeric/pde.h"
#include "../numeric/wave.h"
#include "utility.h"

static const int label_width = 100;

SurfaceGridMeshSettingWidget::SurfaceGridMeshSettingWidget(SurfaceGridMesh *mesh)
    : QWidget(nullptr)
    , mesh(mesh)
    , animationGroup(new SequentialAnimationGroup(this))
    , pauseAnimation(new PauseAnimation(0, this))
    , propertyAnimation(new PropertyAnimation(this))
    , controller(new DynamicSurfaceController(this))

    , equationButton(new mlayout::PushButtonLayout("", this, label_width))
    , gridRow(new mlayout::IntSbLayout("Grid row", this, label_width))
    , gridCol(new mlayout::IntSbLayout("Grid col", this, label_width))
    , gridStride(new mlayout::DoubleSbLayout("Grid stride", this, label_width))

    , startTime(new mlayout::DoubleSbLayout("Start time", this, label_width))
    , deltaTime(new mlayout::DoubleSbLayout("Delta time", this, label_width))
    , stepCount(new mlayout::IntSbLayout("Step count", this, label_width))

    , stackedWidget(new QStackedWidget(this))
    , button(new QPushButton("Calculate", this))
    , progressBar(new QProgressBar(this))

    , equationSettingWidget(new PDEquationSettingWidget(nullptr))
{
    setObjectName("Surface grid");

    animationGroup->addAnimation(pauseAnimation);
    animationGroup->addAnimation(propertyAnimation);

    controller->setTarget(mesh);
    propertyAnimation->setTargetObject(controller);
    propertyAnimation->setPropertyName("step");

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    PropertyControllerLayout *pLayout = new PropertyControllerLayout(propertyAnimation, this);
    mlayout::IntSbLayout *delayAnimation = new mlayout::IntSbLayout("Delay animation", this, label_width);
    mlayout::IntSbLayout *duration = new mlayout::IntSbLayout("Duration", this, label_width);
    QHBoxLayout *hLayout = new QHBoxLayout;
    QSpacerItem *spacer = new QSpacerItem(label_width, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

    setLayout(vLayout);
    vLayout->addLayout(pLayout);
    vLayout->addLayout(equationButton);
    vLayout->addLayout(gridRow);
    vLayout->addLayout(gridCol);
    vLayout->addLayout(gridStride);
    vLayout->addLayout(startTime);
    vLayout->addLayout(deltaTime);
    vLayout->addLayout(stepCount);
    vLayout->addLayout(delayAnimation);
    vLayout->addLayout(duration);
    vLayout->addLayout(hLayout);
    hLayout->addItem(spacer);
    hLayout->addWidget(stackedWidget);
    stackedWidget->addWidget(button);
    stackedWidget->addWidget(progressBar);

    equationButton->setButtonText(enumToString(PDEquationSettingWidget::PDE(0)));
    gridRow->setSpinBoxMaxValue(100000);
    gridCol->setSpinBoxMaxValue(100000);
    gridStride->setSpinBoxMaxValue(100000);
    startTime->setSpinBoxMaxValue(100000);
    stepCount->setSpinBoxMaxValue(100000);
    duration->setSpinBoxMaxValue(1000000);
    progressBar->setMinimum(0);
    progressBar->setTextVisible(false);

    calculationThread.start();

    connect(equationSettingWidget, &PDEquationSettingWidget::equationChanged, equationButton, &mlayout::PushButtonLayout::setButtonText);
    connect(equationButton, &mlayout::PushButtonLayout::released, equationSettingWidget, &PDEquationSettingWidget::show);
    connect(duration, &mlayout::IntSbLayout::valueChanged, propertyAnimation, &PropertyAnimation::setDuration);
    connect(button, &QPushButton::released, this, &SurfaceGridMeshSettingWidget::setInitState);
}

SurfaceGridMeshSettingWidget::~SurfaceGridMeshSettingWidget()
{
    calculationThread.quit();
    calculationThread.wait();
    delete equationSettingWidget;
}

void SurfaceGridMeshSettingWidget::setInitState()
{
    equation::InitWithFormulaExpCondition *initializer = new equation::InitWithFormulaExpCondition(nullptr);
    connect(this, &SurfaceGridMeshSettingWidget::initializationRequested, initializer, &equation::InitWithFormulaExpCondition::calculate);
    connect(initializer, &equation::InitWithFormulaExpCondition::calculated, this, &SurfaceGridMeshSettingWidget::requestCalculate);
    connect(initializer, &equation::InitWithFormulaExpCondition::calculated, initializer, &equation::InitWithFormulaExpCondition::deleteLater);

    initializer->moveToThread(&calculationThread);

    const qsizetype row = gridRow->value();
    const qsizetype col = gridCol->value();
    const float dx = gridStride->value();

    emit initializationRequested(equationSettingWidget->ranges(),
                                 equationSettingWidget->conditionFormula(),
                                 row, col, dx);
}

void SurfaceGridMeshSettingWidget::requestCalculate(const QVector<float>& init)
{
    const qsizetype row = gridRow->value();
    const qsizetype col = gridCol->value();
    const float gridStride = this->gridStride->value();
    const float startT = startTime->value();
    const float deltaT = deltaTime->value();
    const qsizetype count = stepCount->value();

    progressBar->setMaximum(count);
    stackedWidget->setCurrentWidget(progressBar);
    controller->setStateCount(count);
    propertyAnimation->setEndValue(qMin(propertyAnimation->endValue().toLongLong(), count - 1));

    equation::WaveEquation *waveEquation = new equation::WaveEquation(nullptr);

    waveEquation->setConstantValue(equationSettingWidget->parameter());
    waveEquation->setDeltaTime(deltaT);
    waveEquation->setGridWidth(gridStride);
    waveEquation->setStartTime(startT);
    waveEquation->setStepCount(count);
    waveEquation->setInitializeState(init, row, col);

    waveEquation->moveToThread(&calculationThread);

    connect(this, &SurfaceGridMeshSettingWidget::calculationRequested, waveEquation, &equation::WaveEquation::calculate);
    connect(waveEquation, &equation::WaveEquation::stepChanged, progressBar, &QProgressBar::setValue);
    connect(waveEquation, &equation::WaveEquation::stateChanged, controller, &DynamicSurfaceController::receiveData);
    connect(waveEquation, &equation::WaveEquation::finished, waveEquation, &equation::WaveEquation::deleteLater);
    connect(waveEquation, &equation::WaveEquation::finished, this, &SurfaceGridMeshSettingWidget::handlePostCalculation);

    emit calculationRequested();
}

void SurfaceGridMeshSettingWidget::handlePostCalculation()
{
    mesh->setStride(gridStride->value());
    mesh->setInitState(gridRow->value(), gridCol->value(), controller->firstState());

    propertyAnimation->setStartValue(0);
    propertyAnimation->setEndValue(stepCount->value() - 1);

    stackedWidget->setCurrentWidget(button);
}
