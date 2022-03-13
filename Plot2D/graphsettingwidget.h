#ifndef GRAPHSETTINGWIDGET_H
#define GRAPHSETTINGWIDGET_H

#include <QStackedWidget>
#include <QScrollArea>
#include "layoutparts.h"
#include "graph2d.h"
#include "utility.h"

class AxisSetting;
class GeneralSetting;
class SeriesSetting;

class GraphSettingWidget : public QStackedWidget
{
    Q_OBJECT

public:
    GraphSettingWidget(QWidget *parent);

public:
    GeneralSetting *generalSetting;
    AxisSetting *axisSetting;
    SeriesSetting *seriesSetting;
};




class AxisCommonSetting : public QWidget
{
    Q_OBJECT

public:
    AxisCommonSetting(QWidget *parent, QAbstractAxis *const axis);

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

signals:
    void rangeMinSet(const double& min);
    void rangeMaxSet(const double& max);
    void titleVisibleChanged(const bool visible);
    void titleSet(const QString& title);
    void titleSizeSet(const int ps);
    void gridVisibleChanged(const bool visible);
    void gridColorSet(const QColor& color);
    void labelVisibleChanged(const bool visible);
    void labelAngleSet(const double& angle);
    void labelSizeSet(const int ps);
    void labelColorSet(const QColor& color);
    void axisVisibleChanged(const bool visible);
    void axisColorSet(const QColor& color);
    void reverseChanged(const bool reverse);
};

class AxisSetting : public QScrollArea
{
    Q_OBJECT

public:
    AxisSetting(QWidget *parent);

private slots:
    void createNewAxis();

private:
    ComboEditLayout *axisType;
    ComboEditLayout *axisAlign;
    PushButtonLayout *addButton;
    ComboEditLayout *axisCombo;
    QComboBox *axisIndex;
    QStackedWidget *settingStack;

signals:
    void axisCreated(QAbstractAxis *axis, const Graph2D::AxisAlign align);
};



class GeneralSetting : public QScrollArea
{
    Q_OBJECT

public:
    GeneralSetting(QWidget *parent);

private:
    LineEditLayout *pointX;
    LineEditLayout *pointY;
    QLineEdit *marginLeft;
    QLineEdit *marginRight;
    QLineEdit *marginBottom;
    QLineEdit *marginTop;
    LineEditLayout *graphTitle;
    SpinBoxEditLayout *graphTitleSize;
    ComboEditLayout *graphTheme;

signals:
    void marginLeftSet(const QString& lw);
    void marginRightSet(const QString& rw);
    void marginBottomSet(const QString& bh);
    void marginTopSet(const QString& th);
    void graphTitleSet(const QString& title);
    void graphTitleSizeSet(const int ps);
    void graphThemeSet(const int index);
};



class SeriesSetting : public QScrollArea
{
    Q_OBJECT

public:
    SeriesSetting(QWidget *parent);

public slots:
    void addSeries(QAbstractSeries *series);

private:
    QComboBox *seriesCombo;
    QStackedWidget *stackWidget;
};




































#endif // GRAPHSETTINGWIDGET_H
