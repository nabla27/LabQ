#ifndef POSITION_TIME_CONTROLLER_H
#define POSITION_TIME_CONTROLLER_H

#include <QObject>
#include <Qt3DCore/QTransform>
#include <QGroupBox>
#include "../numeric/equation.h"
#include "layoutparts.h"
#include "../animation/animation.h"
#include "../animation/property_animation_setting.h"
#include "../animation/abstract_equation_setting_widget.h"

class PositionTimeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float time READ time WRITE setTime NOTIFY timeChanged)

public:
    explicit PositionTimeController(QObject *parent = nullptr);

    void setTarget(Qt3DCore::QTransform *target);
    void setTime(const float time);
    void setObserver(equation::PositionObserver *observer) { _observer = observer; }

    Qt3DCore::QTransform *target() const { return _target; }
    float time() const { return _time; }

private:
    Qt3DCore::QTransform *_target;
    float _time;
    equation::PositionObserver *_observer;

signals:
    void targetChanged();
    void timeChanged();
};








class PositionTimeAnimationSettingWidget : public QGroupBox
{
    Q_OBJECT
public:
    PositionTimeAnimationSettingWidget(PropertyAnimation *animation,
                                       Qt3DCore::QTransform *transform,
                                       AbstractEquationSettingWidget *settingWidget,
                                       QWidget *parent);
public slots:
    void emitRequestCalculatation(const equation::EquationParameter& p);

private:
    AbstractEquationSettingWidget *settingWidget;
    PositionTimeController *controller;
    PropertyAnimation *animation;
    equation::PositionObserver *observer;

signals:
    void calculationRequested(const equation::EquationParameter& p, equation::PositionObserver *observer);
};



#endif // POSITION_TIME_CONTROLLER_H
