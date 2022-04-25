#include "property_animation_setting.h"

PropertyAnimationSettingLayout::PropertyAnimationSettingLayout(PropertyAnimation *animation, QWidget *parent, const QString& propertyName, const int labelWidth)
    : QVBoxLayout()
{
    animation->setStartValue(0); //設定していないとInvalid. そのままだとsetCurrentTime()ではアニメーションが反映されないため、初期化する.

    mlayout::DoubleSbLayout *startValue = new mlayout::DoubleSbLayout("Start " + propertyName, parent, labelWidth);
    mlayout::DoubleSbLayout *endValue = new mlayout::DoubleSbLayout("End " + propertyName, parent, labelWidth);
    mlayout::IntSbLayout *duration = new mlayout::IntSbLayout("Duration", parent, labelWidth);
    mlayout::IntSbLayout *loopCount = new mlayout::IntSbLayout("Loop count", parent, labelWidth);

    addLayout(startValue);
    addLayout(endValue);
    addLayout(duration);
    addLayout(loopCount);

    startValue->setSpinBoxMaxValue(100000);
    startValue->setSpinBoxMinValue(0.00);
    endValue->setSpinBoxMaxValue(100000);
    endValue->setSpinBoxMinValue(0.00);
    duration->setSpinBoxMaxValue(100000);
    duration->setSpinBoxMinValue(1);
    loopCount->setSpinBoxMinValue(-1);

    startValue->setValue(animation->startValue().toFloat());
    endValue->setValue(animation->endValue().toFloat());
    duration->setValue(animation->duration());
    loopCount->setValue(animation->loopCount());

    connect(startValue, &mlayout::DoubleSbLayout::valueChanged, animation, &PropertyAnimation::setStartValue);
    connect(endValue, &mlayout::DoubleSbLayout::valueChanged, animation, &PropertyAnimation::setEndValue);
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
    {
        /* もし再生が終了して停止していた場合、
         * 現在時刻とプロパティの値を初期化する。現在時刻だけを0に戻しても、プロパティの値は終了時点の値のままである。*/
        animation->setCurrentTime(0);
        animation->setProperty(animation->propertyName(), animation->startValue());
        animation->start();
    }
    else if(animation->state() == QAbstractAnimation::State::Paused)
        animation->resume();
    else
        animation->pause();
}

/* 再生中、アニメーションを最初の状態に戻す。アニメーションが再生中の場合にのみ、propertyは初期値に設定される。
 * アニメーションが終了した後にsetCurrentTime(0)を行ってもpropertyは初期値に戻らない。*/
void PropertyControllerLayout::resetAnimation()
{
    animation->setCurrentTime(0);
    if(animation->state() == QAbstractAnimation::State::Running)
        animation->pause();
}










