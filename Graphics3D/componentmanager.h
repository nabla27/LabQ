#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenu>
#include <Qt3DCore/QEntity>
#include "itemsettingwidget/torussettingwidget.h"

class ComponentManager : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentManager(QWidget *parent = nullptr);

private:
    void initializeAddComponentMenu();

private slots:
    void requestBasicShapeTorus();

private:
    QPushButton *addComponentButton;
    QMenu *addComponentMenu;
    QStackedWidget *stackedWidget;

signals:
    void componentAdded(Qt3DCore::QEntity *entity);
};

#endif // COMPONENTMANAGER_H
