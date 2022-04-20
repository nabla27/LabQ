#include "animation_setting_widget.h"

AnimationSettingWidget::AnimationSettingWidget(Qt3DCore::QTransform *transform, QWidget *parent)
    : QWidget(parent)
    , vLayout(new QVBoxLayout)
    , transform(transform)
    , sequensAnimation(new QSequentialAnimationGroup(transform))
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

    addAnimationButton->setMenu(animationMenu);
    animationMenu->addAction(addOrbitAnimation);

    connect(addOrbitAnimation, &QAction::triggered, this, &AnimationSettingWidget::requestOrbitAnimation);
}

void AnimationSettingWidget::requestOrbitAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(transform);
    OrbitAnimationSettingWidget *widget = new OrbitAnimationSettingWidget(animation, transform, this);

    vLayout->insertWidget(sequensAnimation->animationCount() + 1, widget);
    sequensAnimation->addAnimation(animation);
}






