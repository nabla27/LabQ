#include "position_time_controller.h"

static const int label_width = 100;

PositionTimeController::PositionTimeController(QObject *parent)
    : QObject(parent)
    , _target(nullptr)
    , _time(0)
    , _observer(nullptr)
{
}

void PositionTimeController::setTarget(Qt3DCore::QTransform *target)
{
    if(_target == target) return;

    _target = target;
    emit targetChanged();
}

void PositionTimeController::setTime(const float time)
{
    if(_time == time) return;

    _time = time;

    const std::array<double, 4> vec = _observer->data->at(static_cast<qsizetype>(_time));
    _target->setTranslation(QVector3D(vec.at(1), vec.at(2), vec.at(3)));


    emit timeChanged();
}









PositionTimeAnimationSettingWidget::PositionTimeAnimationSettingWidget(PropertyAnimation *animation,
                                                                       Qt3DCore::QTransform *transform,
                                                                       AbstractEquationSettingWidget *settingWidget,
                                                                       QWidget *parent)
    : QGroupBox(parent)
    , settingWidget(settingWidget)
    , controller(new PositionTimeController(transform))
    , animation(animation)
    , observer(new equation::PositionObserver)
{
    controller->setTarget(transform);
    controller->setObserver(observer);
    animation->setTargetObject(controller);
    animation->setPropertyName("time");

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    PropertyControllerLayout *cLayout = new PropertyControllerLayout(animation, this);
    mlayout::PushButtonLayout *showSettingButton = new mlayout::PushButtonLayout("", this, label_width);
    mlayout::IntSbLayout *duration = new mlayout::IntSbLayout("Duration", this, label_width);
    mlayout::IntSbLayout *loopCount = new mlayout::IntSbLayout("Loop count", this, label_width);

    setLayout(vLayout);
    vLayout->addLayout(cLayout);
    vLayout->addLayout(showSettingButton);
    vLayout->addLayout(duration);
    vLayout->addLayout(loopCount);

    duration->setSpinBoxMinValue(1);
    duration->setSpinBoxMaxValue(100000);
    duration->setValue(animation->duration());
    loopCount->setSpinBoxMinValue(-1);
    loopCount->setValue(animation->loopCount());

    connect(showSettingButton, &mlayout::PushButtonLayout::released, settingWidget, &QWidget::show);
    connect(duration, &mlayout::IntSbLayout::valueChanged, animation, &PropertyAnimation::setDuration);
    connect(loopCount, &mlayout::IntSbLayout::valueChanged, animation, &PropertyAnimation::setLoopCount);
    connect(settingWidget, &AbstractEquationSettingWidget::calculatationRequested, this, &PositionTimeAnimationSettingWidget::emitRequestCalculatation);
    connect(observer, &equation::PositionObserver::dataSizeChanged, settingWidget, &AbstractEquationSettingWidget::setProgressCount);
    connect(observer, &equation::PositionObserver::inProgress, settingWidget, &AbstractEquationSettingWidget::setCurrentProgress);
}

void PositionTimeAnimationSettingWidget::emitRequestCalculatation(const equation::EquationParameter& p)
{
    observer->setDataSize((p.endT - p.startT) / p.step + 1);
    observer->count = 0;

    animation->setStartValue(float(0));
    animation->setEndValue(float(observer->data->size() - 1));

    emit calculationRequested(p, observer);
}









