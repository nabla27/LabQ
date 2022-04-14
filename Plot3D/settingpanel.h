#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QComboBox>

class SettingPanel : public QWidget
{
    Q_OBJECT
public:
    explicit SettingPanel(QWidget *parent = nullptr);

private:
    QPushButton *expandButton;
    QComboBox *combo;
    QPushButton *addButton;

signals:

};

#endif // SETTINGPANEL_H
