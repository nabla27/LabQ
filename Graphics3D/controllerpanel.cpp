#include "controllerpanel.h"

ControllerPanel::ControllerPanel(QWidget *parent)
    : QWidget(parent)
    , animationGroup(new ParallelAnimationGroup(this))
    , playAnimationButton(new QPushButton("Play", this))
    , resetAnimationButton(new QPushButton("Reset", this))
    , currentDurationSpin(new QSpinBox(this))
    , durationSlider(new QSlider(Qt::Orientation::Horizontal, this))
    , totalDurationEdit(new QLineEdit(QString::number(0), this))
    , loopAnimationButton(new QPushButton("no loop", this))
{
    setFixedHeight(30);

    QHBoxLayout *hLayout = new QHBoxLayout(this);

    setLayout(hLayout);
    hLayout->addWidget(playAnimationButton);
    hLayout->addWidget(resetAnimationButton);
    hLayout->addWidget(currentDurationSpin);
    hLayout->addWidget(durationSlider);
    hLayout->addWidget(totalDurationEdit);
    hLayout->addWidget(loopAnimationButton);

    hLayout->setContentsMargins(0, 0, 0, 0);
    currentDurationSpin->setMinimum(0);
    totalDurationEdit->setReadOnly(true);
    durationSlider->setMinimum(0);
    durationSlider->setMaximum(0);

    connect(playAnimationButton, &QPushButton::released, this, &ControllerPanel::playAnimation);
    connect(resetAnimationButton, &QPushButton::released, this, &ControllerPanel::resetAnimation);
    connect(animationGroup, &ParallelAnimationGroup::currentTimeUpdated, currentDurationSpin, &QSpinBox::setValue);
    connect(currentDurationSpin, &QSpinBox::valueChanged, this, &ControllerPanel::setCurrentTime);
    connect(durationSlider, &QSlider::valueChanged, this, &ControllerPanel::setCurrentTime);
    connect(animationGroup, &ParallelAnimationGroup::currentTimeUpdated, durationSlider, &QSlider::setValue);
    connect(loopAnimationButton, &QPushButton::released, this, &ControllerPanel::changeAnimationLoop);
}

void ControllerPanel::addAnimation(SequentialAnimationGroup *animation)
{
    animationGroup->addAnimation(animation);
    connect(animation, &SequentialAnimationGroup::totalDurationChanged, this, &ControllerPanel::setTotalDurationEdit);
}

void ControllerPanel::playAnimation()
{
    switch(animationGroup->state())
    {
    case QAbstractAnimation::State::Stopped:
        animationGroup->start(); break;
    case QAbstractAnimation::State::Running:
        animationGroup->pause(); break;
    case QAbstractAnimation::State::Paused:
        animationGroup->resume(); break;
    }
}

void ControllerPanel::setTotalDurationEdit(const int)
{
    /* アニメーションのループ数が-1の無限ループのとき、totalDuration()は-1を返す。
     * 1ループあたりのdurationを得たいので、無限ループに設定されている場合は
     * 一度1ループに設定してからtotalDuration()を呼び出す。 */
    int totalDuration = 0;
    if(animationGroup->loopCount() == -1)
    {
        animationGroup->setLoopCount(1);
        totalDuration = animationGroup->totalDuration();
        animationGroup->setLoopCount(-1);
    }
    else
        totalDuration = animationGroup->totalDuration();

    totalDurationEdit->setText(QString::number(totalDuration));
    currentDurationSpin->setMaximum(totalDuration);
    durationSlider->setMaximum(totalDuration);
}

void ControllerPanel::resetAnimation()
{
    if(animationGroup->state() == QAbstractAnimation::State::Running)
        animationGroup->pause();
    animationGroup->setCurrentTime(0);
}

void ControllerPanel::setCurrentTime(const int msecs)
{
    switch(animationGroup->state())
    {
    /* state状態がstoppedだと、スライドバーを動かしてもanimationのcurrentTimeと
     * currentValueが設定されてもanimationのcontrollerが実行されない。*/
    case QAbstractAnimation::State::Stopped:
        animationGroup->start();
        animationGroup->pause();
        break;
    /* sliderでループをまたぐ時に、以下のPausedとRunningの処理が必要
     * これがなければ、loopモードでスライダーを使ってループをまたいだ後、スライダーで
     * オブジェクトを動かせなくなる。*/
    case QAbstractAnimation::State::Paused:
        //これがないと、ループをまたいだとき、スライダーによる操作が効かなくなる
        animationGroup->resume(); break;
    case QAbstractAnimation::State::Running:
        //これがないと、ループをまたいだとき、animationが再生され、自動で動くようになってしまう
        animationGroup->pause(); break;
    default:
        break;
    }

    animationGroup->setCurrentTime(msecs);
}

void ControllerPanel::changeAnimationLoop()
{
    if(animationGroup->loopCount() == -1)
    {
        animationGroup->setLoopCount(1);
        loopAnimationButton->setText("no loop");
    }
    else
    {
        animationGroup->setLoopCount(-1);
        loopAnimationButton->setText("loop");
    }
}
