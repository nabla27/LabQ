#include "serialviewtab.h"

SerialViewTab::SerialViewTab(QWidget *parent)
    : QTabWidget(parent)
{
    initializeContextMenu();
}

void SerialViewTab::initializeContextMenu()
{
    if(contextMenu) delete contextMenu;

    contextMenu = new QMenu(this);

    QMenu *addTabMenu = new QMenu("Add tab", contextMenu);
    contextMenu->addMenu(addTabMenu);

    QAction *addTextBrowser = new QAction("Add TextBrowser", addTabMenu);
    addTabMenu->addAction(addTextBrowser);
    connect(addTextBrowser, &QAction::triggered, this, &SerialViewTab::addTextBrowserSelected);

    QAction *addGraph2d = new QAction("Add Graph1d", addTabMenu);
    addTabMenu->addAction(addGraph2d);
    connect(addGraph2d, &QAction::triggered, this, &SerialViewTab::addGraph2dSelected);



}

//右クリックのみ拾われる
void SerialViewTab::mousePressEvent(QMouseEvent *event)
{
    if(tabBar()->underMouse())
    {
        contextMenu->exec(mapToGlobal(event->pos()));
    }
}
