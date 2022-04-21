#include "property_animation_setting.h"

PropertyAnimationSettingLayout::PropertyAnimationSettingLayout(PropertyAnimation *animation, QWidget *parent, const QString& propertyName, const int labelWidth)
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

    connect(startAngle, &mlayout::DoubleSbLayout::valueChanged, animation, &PropertyAnimation::setStartValue);
    connect(endAngle, &mlayout::DoubleSbLayout::valueChanged, animation, &PropertyAnimation::setEndValue);
    connect(duration, &mlayout::IntSbLayout::valueChanged, animation, &PropertyAnimation::setDuration);
    connect(loopCount, &mlayout::IntSbLayout::valueChanged, animation, &PropertyAnimation::setLoopCount);
}







PropertyControllerLayout::PropertyControllerLayout(PropertyAnimation *animation, QWidget *parent)
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
}

void PropertyControllerLayout::playAnimation()
{
    if(animation->state() == QAbstractAnimation::State::Stopped)
        animation->start();
    else if(animation->state() == QAbstractAnimation::State::Paused)
        animation->resume();
    else
        animation->pause();
}

/* 再生中、アニメーションを最初の状態に戻す。アニメーションが再生中の場合にのみ、propertyは初期値に設定される。
 * アニメーションが終了した後にsetCurrentTime(0)を行ってもpropertyは初期値に戻らない。
 * よって、アニメーションが終了した際の初期化は別の場所で行う。 */
void PropertyControllerLayout::resetAnimation()
{
    animation->setCurrentTime(0);
    if(animation->state() == QAbstractAnimation::State::Running)
        animation->pause();
}










