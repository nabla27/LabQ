#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <QScrollArea>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenu>
#include <Qt3DCore/QEntity>
#include "itemsettingwidget/basic_mesh_setting_widget.h"
#include "itemsettingwidget/basic_shape_setting_widget.h"

#include <QTreeWidget>
#include <QStandardItemModel>

class ObjectTree;


class ComponentManager : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentManager(QWidget *parent = nullptr);

private:
    void initializeAddObjectMenu();

private slots:
    void requestBasicShape(Qt3DRender::QGeometryRenderer *mesh, QWidget *meshWidget);
    void requestBasicShapeTorus();
    void requestBasicShapePlane();

private:
    QPushButton *addObjectButton;
    QMenu *addObjectMenu;
    ObjectTree *objectTree;
    QStackedWidget *stackedWidget;

signals:
    void objectAdded(Qt3DCore::QEntity *entity);
    void animationAdded(SequentialAnimationGroup *animation);
};








class ObjectTree : public QTreeWidget
{
    Q_OBJECT
public:
    ObjectTree(QWidget *parent);

private:
    void emitClick(QTreeWidgetItem *item, int column);
    void emitSelectedObject(QTreeWidgetItem *item, int column);

signals:
    void objectSelected(QWidget *widget);
};


class ObjectTreeItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    ObjectTreeItem(ObjectTreeItem *item, QWidget *settingWidget);
    ObjectTreeItem(ObjectTree *tree, QWidget *settingWidget);

public:
    QWidget *const settingWidget() const { return _settingWidget; }

private:
    QWidget *_settingWidget;

signals:
    void clickedCheckState0(const bool checked);
};










#endif // COMPONENTMANAGER_H
