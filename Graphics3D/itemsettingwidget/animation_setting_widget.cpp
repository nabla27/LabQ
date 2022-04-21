#include "animation_setting_widget.h"

static const int label_width = 100;

AnimationSettingWidget::AnimationSettingWidget(Qt3DCore::QTransform *transform, QWidget *parent)
    : QWidget(parent)
    , vLayout(new QVBoxLayout)
    , transform(transform)
    , sequensAnimation(new SequentialAnimationGroup(transform))
{
    QHBoxLayout *addAnimationLayout = new QHBoxLayout;
    QLabel *addAnimationLabel = new QLabel("Add animation", this);
    QPushButton *addAnimationButton = new QPushButton("Type", this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(addAnimationLayout);
    addAnimationLayout->addWidget(addAnimationLabel);
    addAnimationLayout->addWidget(addAnimationButton);
    vLayout->addItem(spacer);

    addAnimationLabel->setFixedWidth(100);
    addAnimationButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    vLayout->setContentsMargins(0, 0, 0, 0);


    /* アニメーションの追加メニュー */

    QMenu *animationMenu = new QMenu(addAnimationButton);
    QAction *addOrbitAnimation = new QAction("Orbit", animationMenu);
    QAction *addPauseAnimation = new QAction("Pause", animationMenu);

    addAnimationButton->setMenu(animationMenu);
    animationMenu->addAction(addOrbitAnimation);
    animationMenu->addAction(addPauseAnimation);

    connect(addOrbitAnimation, &QAction::triggered, this, &AnimationSettingWidget::requestOrbitAnimation);
    connect(addPauseAnimation, &QAction::triggered, this, &AnimationSettingWidget::requestPauseAnimation);
}

void AnimationSettingWidget::requestOrbitAnimation()
{
    PropertyAnimation *animation = new PropertyAnimation(transform);
    OrbitAnimationSettingWidget *widget = new OrbitAnimationSettingWidget(animation, transform, this);

    vLayout->insertWidget(sequensAnimation->animationCount() + 1, widget);
    sequensAnimation->addAnimation(animation);;
}

void AnimationSettingWidget::requestPauseAnimation()
{
    PauseAnimation *animation = new PauseAnimation(0, this);
    sequensAnimation->addAnimation(animation);
    PauseAnimationSettingWidget *widget = new PauseAnimationSettingWidget(animation, this);

    vLayout->insertWidget(sequensAnimation->animationCount(), widget);
}








PauseAnimationSettingWidget::PauseAnimationSettingWidget(PauseAnimation *animation, QWidget *parent)
    : QGroupBox(parent)
{
    setTitle("Pause");

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    mlayout::IntSbLayout *duration = new mlayout::IntSbLayout("Duration", this, label_width);

    setLayout(vLayout);
    vLayout->addLayout(duration);

    duration->setSpinBoxMinValue(0);
    duration->setSpinBoxMaxValue(100000);
    duration->setValue(animation->duration());

    connect(duration, &mlayout::IntSbLayout::valueChanged, animation, &PauseAnimation::setDuration);
}



