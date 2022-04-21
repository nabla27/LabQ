#ifndef PROPERTY_ANIMATION_SETTING_H
#define PROPERTY_ANIMATION_SETTING_H

#include <QPropertyAnimation>
#include "layoutparts.h"


class PropertyAnimationSettingLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    PropertyAnimationSettingLayout(QPropertyAnimation *animation,
                                   QWidget *parent,
                                   const QString& propertyName,
                                   const int labelWidth);
};





class PropertyControllerLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    PropertyControllerLayout(QPropertyAnimation *animation, QWidget *parent);

private:
    void playAnimation();
    void resetAnimation();

private:
    QPropertyAnimation *animation;

signals:
    void indexChanged(const int index);
};






#endif // PROPERTY_ANIMATION_SETTING_H
