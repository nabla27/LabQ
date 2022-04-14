#include "settingpanel.h"

SettingPanel::SettingPanel(QWidget *parent)
    : QWidget{parent}
{
    const int buttonWidth = 22;

    QHBoxLayout *layout = new QHBoxLayout;
    setLayout(layout);

    expandButton = new QPushButton(this);
    combo = new QComboBox(this);
    addButton = new QPushButton(this);

    layout->addWidget(expandButton);
    layout->addWidget(combo);
    layout->addWidget(addButton);

    expandButton->setFixedWidth(expandButton->height());
    addButton->setFixedWidth(expandButton->height());
}
