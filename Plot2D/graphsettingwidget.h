#ifndef GRAPHSETTINGWIDGET_H
#define GRAPHSETTINGWIDGET_H

#include <QStackedWidget>
#include <QScrollArea>
#include "layoutparts.h"
#include "graph2d.h"
#include "utility.h"

class HorizontalAxisSetting;

class GraphSettingWidget : public QStackedWidget
{
    Q_OBJECT

public:
    GraphSettingWidget(QWidget *parent);

public:
    HorizontalAxisSetting *horizontalAxisSetting;
};




class AxisCommonSetting : public QWidget
{
    Q_OBJECT

public:
    AxisCommonSetting(QWidget *parent, Graph2D::AxisType type);

private:
    LineEditLayout *rangeMin;
    LineEditLayout *rangeMax;
    CheckBoxLayout *titleVisible;
    LineEditLayout *axisTitle;
    SpinBoxEditLayout *axisTitleSize;
    CheckBoxLayout *gridVisible;
    ComboEditLayout *gridColor;
    RGBEditLayout *gridColorCustom;
    CheckBoxLayout *labelVisible;
    LineEditLayout *labelAngle;
    SpinBoxEditLayout *labelSize;
    ComboEditLayout *labelColor;
    RGBEditLayout *labelColorCustom;
    CheckBoxLayout *axisVisible;
    ComboEditLayout *axisColor;
    RGBEditLayout *axisColorCustom;
    CheckBoxLayout *reverse;
};




class HorizontalAxisSetting : public QScrollArea
{
    Q_OBJECT

public:
    HorizontalAxisSetting(QWidget *parent);

private:
    ComboEditLayout *axisType;
    ComboEditLayout *axisAlign;
    PushButtonLayout *addButton;
    ComboEditLayout *axisCombo;
    QStackedWidget *settingStack;
};

#endif // GRAPHSETTINGWIDGET_H
