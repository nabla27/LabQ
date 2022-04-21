#ifndef ANIMATION_SETTING_WIDGET_H
#define ANIMATION_SETTING_WIDGET_H

#include <QWidget>
#include <QSequentialAnimationGroup>
#include <QPauseAnimation>
#include <Qt3DCore/QTransform>
#include <QMenu>
#include "animation/orbitcontroller.h"
#include "layoutparts.h"


class AnimationSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationSettingWidget(Qt3DCore::QTransform *transform, QWidget *parent = nullptr);
    void changeVisible() { setVisible(!isVisible()); }
    SequentialAnimationGroup* animation() const { return sequensAnimation; }

private slots:
    void requestOrbitAnimation();
    void requestPauseAnimation();

private:
    QVBoxLayout *vLayout;
    Qt3DCore::QTransform *transform;
    SequentialAnimationGroup *sequensAnimation;

signals:

};





class PauseAnimationSettingWidget : public QGroupBox
{
    Q_OBJECT
public:
    PauseAnimationSettingWidget(PauseAnimation *animation, QWidget *parent);
};

#endif // ANIMATION_SETTING_WIDGET_H
