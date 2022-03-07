#ifndef SERIALSETTINGWIDGET_H
#define SERIALSETTINGWIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include "layoutparts.h"


class SerialSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialSettingWidget(QWidget *parent = nullptr);
    QSerialPort::BaudRate getBaudRateSetting() const;
    QSerialPort::DataBits getDataBitsSetting() const;
    QSerialPort::Parity getParityCheckSetting() const;
    QSerialPort::StopBits getStopBitsSetting() const;

protected:
    void closeEvent(QCloseEvent*) override { this->hide(); }

private:
    ComboEditLayout *baudRateCombo;
    ComboEditLayout *dataBitsCombo;
    ComboEditLayout *parityCheckCombo;
    ComboEditLayout *stopBitsCombo;

signals:

};

#endif // SERIALSETTINGWIDGET_H
