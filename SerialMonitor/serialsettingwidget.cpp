#include "serialsettingwidget.h"

SerialSettingWidget::SerialSettingWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    baudRateCombo = new ComboEditLayout(this, "Baud rate");
    dataBitsCombo = new ComboEditLayout(this, "Data bits");
    parityCheckCombo = new ComboEditLayout(this, "Parity bits");
    stopBitsCombo = new ComboEditLayout(this, "Stop bits");
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(layout);
    layout->addLayout(baudRateCombo);
    layout->addLayout(dataBitsCombo);
    layout->addLayout(parityCheckCombo);
    layout->addLayout(stopBitsCombo);
    layout->addItem(spacer);

    baudRateCombo->insertComboItems(0, QStringList() << "1200" << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" << "115200");
    dataBitsCombo->insertComboItems(0, QStringList() << "5-bit" << "6-bit" << "7-bit" << "8-bit");
    parityCheckCombo->insertComboItems(0, QStringList() << "No" << "Even" << "Odd" << "Space" << "Mark");
    stopBitsCombo->insertComboItems(0, QStringList() << "1" << "1.5" << "2");
}

QSerialPort::BaudRate SerialSettingWidget::getBaudRateSetting() const
{
    return QSerialPort::BaudRate(pow(2, baudRateCombo->currentComboIndex()) * 1200);
}

QSerialPort::DataBits SerialSettingWidget::getDataBitsSetting() const
{
    return QSerialPort::DataBits(dataBitsCombo->currentComboIndex() + 5);
}

QSerialPort::Parity SerialSettingWidget::getParityCheckSetting() const
{
    const int index = parityCheckCombo->currentComboIndex();
    if(index == 0)
        return QSerialPort::Parity(0);
    else
        return QSerialPort::Parity(index + 1);
}

QSerialPort::StopBits SerialSettingWidget::getStopBitsSetting() const
{
    const int index = stopBitsCombo->currentComboIndex();
    if(index == 0) return QSerialPort::StopBits(1);
    else if(index == 1) return QSerialPort::StopBits(3);
    else if(index == 2) return QSerialPort::StopBits(2);

    return QSerialPort::StopBits(1);
}






















