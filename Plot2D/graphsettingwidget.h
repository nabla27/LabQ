#ifndef GRAPHSETTINGWIDGET_H
#define GRAPHSETTINGWIDGET_H

#include <QStackedWidget>
#include <QScrollArea>
#include <QGraphicsScene>
#include "layoutparts.h"
#include "graph2d.h"
#include "utility.h"
#include "graphicsitem.h"

class AxisSetting;
class GeneralSetting;
class LegendSetting;
class SeriesSetting;
class GraphicsItemSetting;

class GraphSettingWidget : public QStackedWidget
{
    Q_OBJECT

public:
    GraphSettingWidget(QWidget *parent, Graph2D *graph);

public:
    GeneralSetting *generalSetting;
    LegendSetting *legendSetting;
    AxisSetting *axisSetting;
    SeriesSetting *seriesSetting;
    GraphicsItemSetting *graphicsItemSetting;
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
    PushButtonLayout *removeAxis;

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
    void removeAxisFromListRequested(QAbstractAxis *axis);
};

class AxisSetting : public QScrollArea
{
    Q_OBJECT

public:
    AxisSetting(QWidget *parent);
    QAbstractItemModel* getAxisListModel() const { return axisIndex->model(); }

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
    void removeAxisRequested(QAbstractAxis *axis);
};



class GeneralSetting : public QScrollArea
{
    Q_OBJECT

public:
    GeneralSetting(QWidget *parent, Graph2D *graph);

private:
    LineEditLayout *pointX;
    LineEditLayout *pointY;
};




class LegendSetting : public QScrollArea
{
    Q_OBJECT

public:
    LegendSetting(QWidget *parent, QLegend *legend);

private:
    CheckBoxLayout *visible;
    CheckBoxLayout *backgroundVisible;
    CheckBoxLayout *interactive;
    CheckBoxLayout *reverseMarker;
    CheckBoxLayout *showToolTip;
    ComboEditLayout *alignment;
    ComboEditLayout *markerShape;
    SpinBoxEditLayout *fontSize;
    ComboEditLayout *color;
    RGBEditLayout *colorCustom;
    ComboEditLayout *borderColor;
    RGBEditLayout *borderColorCustom;
    ComboEditLayout *labelColor;
    RGBEditLayout *labelColorCustom;
};






class AxisAttachingList : public QHBoxLayout
{
    Q_OBJECT

public:
    AxisAttachingList(QAbstractItemModel *model, QWidget *parent = nullptr);

private slots:
    void changeCheckBoxIndex(const int index);
    void removeStateList(const QModelIndex& parent, int first, int last);
    void changeState(const bool checked);
    void addStateListIndex();

private:
    QComboBox *axisComboList;
    QCheckBox *attach;
    QList<bool> stateList;

signals:
    void axisAttachedStateChanged(const int index, const bool attached);
};


class SeriesSetting : public QScrollArea
{
    Q_OBJECT

public:
    SeriesSetting(QWidget *parent);

public slots:
    void addSeries(QAbstractSeries *series, const QString& name);
    void setAxisListModel(QAbstractItemModel *model) { axisListModel = model; }
    void addAxisToList(QAbstractAxis *axis, const Graph2D::AxisAlign) { axisList.append(axis); }
    void removeAxisFromList(QAbstractAxis *axis) { axisList.removeAt(axisList.indexOf(axis)); }

private:
    QComboBox *seriesCombo;
    QStackedWidget *stackWidget;
    QAbstractItemModel *axisListModel = nullptr;
    QList<QAbstractAxis*> axisList;

signals:
    void removeSeriesRequested(QAbstractSeries *series);
};







class GraphicsItemSetting : public QScrollArea
{
    Q_OBJECT

public:
    GraphicsItemSetting(QWidget *parent);

public slots:
    void addTextItemSettingWidget(GraphicsTextItem *textItem);
    void addLineItemSettingWidget(GraphicsLineItem *lineItem);
    void addRectItemSettingWidget(GraphicsRectItem *rectItem);
    void addEllipseItemSettingWidget(GraphicsEllipseItem *ellipseItem);
    void addPolygonItemSettingWidget(GraphicsPolygonItem *polygonItem);
    void addPixmapItemSettingWidget(GraphicsPixmapItem *pixmapItem);

private:
    void removeWidgetWithObject(QGraphicsItem *item);

private:
    QComboBox *itemCombo;
    QStackedWidget *settingStack;
    qsizetype itemCount = 0;
};



































#endif // GRAPHSETTINGWIDGET_H
