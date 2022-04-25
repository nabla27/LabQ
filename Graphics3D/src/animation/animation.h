#ifndef ANIMATION_H
#define ANIMATION_H

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QPauseAnimation>
#include <QParallelAnimationGroup>

class PropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    PropertyAnimation(QObject *parent) : QPropertyAnimation(parent) {}

public:
    void setDuration(const int& duration)
    {
        QPropertyAnimation::setDuration(duration);
        emit durationChanged(duration);
    }

signals:
    void durationChanged(const int duration);
};







class PauseAnimation : public QPauseAnimation
{
    Q_OBJECT
public:
    PauseAnimation(int msecs, QObject *parent) : QPauseAnimation(msecs, parent) {}

public:
    void setDuration(const int& duration)
    {
        QPauseAnimation::setDuration(duration);
        emit durationChanged(duration);
    }

signals:
    void durationChanged(const int duration);
};





class SequentialAnimationGroup : public QSequentialAnimationGroup
{
    Q_OBJECT
public:
    SequentialAnimationGroup(QObject *parent = nullptr)
        : QSequentialAnimationGroup(parent) {}

protected:
    void updateCurrentTime(int currentTime) override
    {
        emit currentTimeUpdated(currentTime);
        QSequentialAnimationGroup::updateCurrentTime(currentTime);
    }

public:
    void addAnimation(PropertyAnimation *animation)
    {
        QSequentialAnimationGroup::addAnimation(animation);
        connect(animation, &PropertyAnimation::durationChanged, this, &SequentialAnimationGroup::updateTotalDuration);
    }
    void addAnimation(PauseAnimation *animation)
    {
        QSequentialAnimationGroup::addAnimation(animation);
        connect(animation, &PauseAnimation::durationChanged, this, &SequentialAnimationGroup::updateTotalDuration);
    }

private:
    void updateTotalDuration()
    {
        emit totalDurationChanged(totalDuration());
    }

signals:
    void currentTimeUpdated(const int currentTime);
    void totalDurationChanged(const int totalDuration);
};






class ParallelAnimationGroup : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    ParallelAnimationGroup(QObject *parent) : QParallelAnimationGroup(parent) {}

protected:
    void updateCurrentTime(int currentTime) override
    {
        QParallelAnimationGroup::updateCurrentTime(currentTime);
        emit currentTimeUpdated(currentTime);
    }

signals:
    void currentTimeUpdated(const int currentTime);
};



















#endif ANIMATION_H
