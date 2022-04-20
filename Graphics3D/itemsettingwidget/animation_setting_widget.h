#ifndef ANIMATION_SETTING_WIDGET_H
#define ANIMATION_SETTING_WIDGET_H

#include <QWidget>
#include <QSequentialAnimationGroup>
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

private slots:
    void requestOrbitAnimation();

private:
    QVBoxLayout *vLayout;
    Qt3DCore::QTransform *transform;
    QSequentialAnimationGroup *sequensAnimation;

signals:

};

#endif // ANIMATION_SETTING_WIDGET_H
