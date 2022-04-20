#include "property_animation_setting.h"

PropertyAnimationSettingLayout::PropertyAnimationSettingLayout(QPropertyAnimation *animation, QWidget *parent, const QString& propertyName, const int labelWidth)
    : QVBoxLayout()
{
    mlayout::DoubleSbLayout *startAngle = new mlayout::DoubleSbLayout("Start " + propertyName, parent, labelWidth);
    mlayout::DoubleSbLayout *endAngle = new mlayout::DoubleSbLayout("End " + propertyName, parent, labelWidth);
    mlayout::IntSbLayout *duration = new mlayout::IntSbLayout("Duration", parent, labelWidth);
    mlayout::IntSbLayout *loopCount = new mlayout::IntSbLayout("Loop count", parent, labelWidth);

    addLayout(startAngle);
    addLayout(endAngle);
    addLayout(duration);
    addLayout(loopCount);

    startAngle->setSpinBoxMaxValue(100000);
    startAngle->setSpinBoxMinValue(0.00);
    endAngle->setSpinBoxMaxValue(100000);
    endAngle->setSpinBoxMinValue(0.00);
    duration->setSpinBoxMaxValue(100000);
    duration->setSpinBoxMinValue(1);
    loopCount->setSpinBoxMinValue(-1);

    startAngle->setValue(animation->startValue().toFloat());
    endAngle->setValue(animation->endValue().toFloat());
    duration->setValue(animation->duration());
    loopCount->setValue(animation->loopCount());

    connect(startAngle, &mlayout::DoubleSbLayout::valueChanged, animation, &QPropertyAnimation::setStartValue);
    connect(endAngle, &mlayout::DoubleSbLayout::valueChanged, animation, &QPropertyAnimation::setEndValue);
    connect(duration, &mlayout::IntSbLayout::valueChanged, animation, &QPropertyAnimation::setDuration);
    connect(loopCount, &mlayout::IntSbLayout::valueChanged, animation, &QPropertyAnimation::setLoopCount);
}







PropertyControllerLayout::PropertyControllerLayout(QPropertyAnimation *animation, QWidget *parent)
    : QHBoxLayout()
    , animation(animation)
{
    QSpinBox *indexSpin = new QSpinBox(parent);
    QPushButton *playButton = new QPushButton(parent);
    QPushButton *resetButton = new QPushButton(parent);

    addWidget(indexSpin);
    addWidget(playButton);
    addWidget(resetButton);

    connect(playButton, &QPushButton::released, this, &PropertyControllerLayout::playAnimation);
    connect(resetButton, &QPushButton::released, this, &PropertyControllerLayout::resetAnimation);
    connect(animation, &QPropertyAnimation::finished, this, &PropertyControllerLayout::resetCurrentProperty);
}

void PropertyControllerLayout::playAnimation()
{
    qDebug() << animation->state();
    if(animation->state() == QAbstractAnimation::State::Stopped)
        animation->start();
    else if(animation->state() == QAbstractAnimation::State::Paused)
        animation->resume();
    else
        animation->pause();
}

void PropertyControllerLayout::resetAnimation()
{
    qDebug() << animation->currentTime();
    qDebug() << animation->currentValue();
    animation->setCurrentTime(0);
    animation->pause();
}

void PropertyControllerLayout::resetCurrentProperty()
{
    animation->setCurrentTime(0);
    QVariant end = animation->endValue();
    animation->setEndValue(animation->startValue());
    animation->setEndValue(end);
    qDebug() << animation->state();
}










