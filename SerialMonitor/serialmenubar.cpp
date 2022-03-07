#include "serialmenubar.h"

ToolMenu::ToolMenu(const QString& title, QWidget *parent)
    : QMenu(title, parent)
{
    selectPort = new QMenu("Select port", this);
    addMenu(selectPort);
    connect(this, &ToolMenu::aboutToShow, this, &ToolMenu::addPortSelection);
}

void ToolMenu::addPortSelection()
{
    selectPort->clear();
    foreach(const QSerialPortInfo& info, QSerialPortInfo::availablePorts())
    {
        QMenu *portName = new QMenu(info.portName(), selectPort);
        QAction *portInfo = new QAction(info.description(), portName);
        selectPort->addMenu(portName);
        portName->addAction(portInfo);
        auto informSelectedPort = [this, info]() { emit portSelected(info); };
        connect(portInfo, &QAction::triggered, informSelectedPort);
    }
}





SettingMenu::SettingMenu(const QString& title, QWidget *parent)
    : QAction(title, parent)
{

}





PortOpeMenu::PortOpeMenu(const QString& title, QWidget *parent)
    : QMenu(title, parent)
{
    QAction *open = new QAction("Open", this);
    addAction(open);
    connect(open, &QAction::triggered, this, &PortOpeMenu::portOpenSelected);

    QAction *close = new QAction("Close", this);
    addAction(close);
    connect(close, &QAction::triggered, this, &PortOpeMenu::portCloseSelected);
}























