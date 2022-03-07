#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextBrowser>
#include <QDebug>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QScreen>
#include <QComboBox>
#include <QThread>
#include "utility.h"
#include "serialmenubar.h"
#include "serialsettingwidget.h"
#include "serialplot1d.h"
#include "serialviewtab.h"
#include "serialtextbrowser.h"

class SerialMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialMonitor(QWidget *parent = nullptr);

private slots:
    void initializeMenuBar();
    void initializeLayout();
    void setPort(const QSerialPortInfo& info);
    void openPort();
    void closePort();
    void addTextBrowserTab();
    void addGraph1dTab();

private:
    QMetaObject::Connection serialBrowserConnection;
    QMetaObject::Connection serialGraph1dConnection;

private:
    QSerialPort *serialPort;
    SerialSettingWidget *settingWidget;
    PortOpeMenu *portOpeMenu;

    SerialViewTab *tab;
    SerialTextBrowser *browser = nullptr;
    SerialPlot1D *graph1D = nullptr;

signals:

};

#endif // SERIALMONITOR_H
