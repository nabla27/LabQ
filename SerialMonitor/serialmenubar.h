#ifndef SERIALMENUBAR_H
#define SERIALMENUBAR_H
#include <QMenu>
#include <QEvent>
#include <QtSerialPort/QSerialPortInfo>

class ToolMenu : public QMenu
{
    Q_OBJECT

public:
    ToolMenu(const QString& title, QWidget *parent);

private slots:
    void addPortSelection();

private:
    QMenu *selectPort;

signals:
    void portSelected(const QSerialPortInfo& info);
};




class SettingMenu : public QAction
{
    Q_OBJECT

public:
    SettingMenu(const QString& title, QWidget *parent);
};



class PortOpeMenu : public QMenu
{
    Q_OBJECT

public:
    PortOpeMenu(const QString& title, QWidget *parent);

signals:
    void portOpenSelected();
    void portCloseSelected();
};





















#endif // SERIALMENUBAR_H
