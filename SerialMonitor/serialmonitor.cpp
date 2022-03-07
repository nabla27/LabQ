#include "serialmonitor.h"

SerialMonitor::SerialMonitor(QWidget *parent)
    : QMainWindow{parent}
{
    serialPort = new QSerialPort(this);
    settingWidget = new SerialSettingWidget(nullptr); settingWidget->hide();

    initializeMenuBar();
    initializeLayout();
    addTextBrowserTab();

    setGeometry(getRectFromScreenRatio(screen()->size(), 0.3f, 0.4f));
}

void SerialMonitor::initializeMenuBar()
{
    if(menuBar()) delete menuBar();

    QMenuBar *menuBar = new QMenuBar(this);

    ToolMenu *toolMenu = new ToolMenu("Tool", menuBar);
    menuBar->addMenu(toolMenu);
    connect(toolMenu, &ToolMenu::portSelected, this, &SerialMonitor::setPort);

    SettingMenu *portSettingMenu = new SettingMenu("Port", menuBar);
    menuBar->addAction(portSettingMenu);
    connect(portSettingMenu, &QAction::triggered, settingWidget, &SerialSettingWidget::show);

    portOpeMenu = new PortOpeMenu("", menuBar);
    menuBar->addMenu(portOpeMenu);
    connect(portOpeMenu, &PortOpeMenu::portOpenSelected, this, &SerialMonitor::openPort);
    connect(portOpeMenu, &PortOpeMenu::portCloseSelected, this, &SerialMonitor::closePort);

    setMenuBar(menuBar);
}

void SerialMonitor::initializeLayout()
{
    if(centralWidget()) delete centralWidget();

    setCentralWidget(new QWidget(this));

    QVBoxLayout *layout = new QVBoxLayout(centralWidget());
    tab = new SerialViewTab(centralWidget());

    centralWidget()->setLayout(layout);
    layout->addWidget(tab);

    layout->setContentsMargins(0, 0, 0, 0);

    connect(tab, &SerialViewTab::addTextBrowserSelected, this, &SerialMonitor::addTextBrowserTab);
    connect(tab, &SerialViewTab::addGraph2dSelected, this, &SerialMonitor::addGraph1dTab);
}

void SerialMonitor::setPort(const QSerialPortInfo& info)
{
    serialPort->setPort(info);
    portOpeMenu->setTitle(info.portName());
}

void SerialMonitor::openPort()
{
    serialPort->setBaudRate(settingWidget->getBaudRateSetting());
    serialPort->setDataBits(settingWidget->getDataBitsSetting());
    serialPort->setParity(settingWidget->getParityCheckSetting());
    serialPort->setStopBits(settingWidget->getStopBitsSetting());

    if(serialPort->open(QIODevice::ReadOnly))
    {

    }
    else
    {
        //開けなかった通知処理
    }
}

void SerialMonitor::closePort()
{
    serialPort->close();
}

void SerialMonitor::addTextBrowserTab()
{
    if(browser){
        tab->setCurrentWidget(browser);
        return;
    }

    browser = new SerialTextBrowser(tab);
    tab->addTab(browser, "TextBrowser");
}

void SerialMonitor::addGraph1dTab()
{
    if(graph1D){
        tab->setCurrentWidget(graph1D);
        return;
    }

    graph1D = new SerialPlot1D(serialPort, nullptr);
    tab->addTab(graph1D, "Graph1D");
}




































