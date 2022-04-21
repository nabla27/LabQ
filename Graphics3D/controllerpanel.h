#ifndef CONTROLLERPANEL_H
#define CONTROLLERPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>

#include "itemsettingwidget/animation_setting_widget.h"

class ControllerPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControllerPanel(QWidget *parent = nullptr);
    void addAnimation(SequentialAnimationGroup *animation);

private:
    ParallelAnimationGroup *animationGroup;
    QPushButton *playAnimationButton;
    QPushButton *resetAnimationButton;
    QSpinBox *currentDurationSpin;
    QSlider *durationSlider;
    QLineEdit *totalDurationEdit;

private slots:
    void playAnimation();
    void resetAnimation();
    void setTotalDurationEdit(const int duration);
    void setCurrentTime(const int msecs);

signals:

};

#endif // CONTROLLERPANEL_H
