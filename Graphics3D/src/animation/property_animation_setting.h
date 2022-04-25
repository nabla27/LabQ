#ifndef PROPERTY_ANIMATION_SETTING_H
#define PROPERTY_ANIMATION_SETTING_H

#include "layoutparts.h"
#include "animation.h"

class PropertyAnimationSettingLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    PropertyAnimationSettingLayout(PropertyAnimation *animation,
                                   QWidget *parent,
                                   const QString& propertyName,
                                   const int labelWidth);
};





class PropertyControllerLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    PropertyControllerLayout(PropertyAnimation *animation, QWidget *parent);

private:
    void playAnimation();
    void resetAnimation();

private:
    PropertyAnimation *animation;

signals:
    void indexChanged(const int index);
};






#endif // PROPERTY_ANIMATION_SETTING_H
