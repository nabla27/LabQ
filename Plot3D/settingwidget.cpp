#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget{parent}
{
    const int buttonFixWidth = 25;
    setFixedWidth(250);

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *panelLayout = new QHBoxLayout;
    settingStacked = new QStackedWidget(this);

    setLayout(layout);
    layout->addLayout(panelLayout);
    layout->addWidget(settingStacked);

    expandButton = new QPushButton(this);
    itemCombo = new QComboBox(this);
    addButton = new QPushButton(this);

    panelLayout->addWidget(expandButton);
    panelLayout->addWidget(itemCombo);
    panelLayout->addWidget(addButton);

    settingStacked->setFrameShape(QFrame::Box);

    layout->setContentsMargins(0, 0, 0, 0);
    panelLayout->setContentsMargins(0, 4, 0, 2);
    expandButton->setFixedWidth(buttonFixWidth);
    addButton->setFixedWidth(buttonFixWidth);

    initializeAddtionMenu();
}

void SettingWidget::initializeAddtionMenu()
{
    if(additionMenu) delete additionMenu;

    additionMenu = new QMenu(this);

    QAction *staticCsvAct = new QAction("static csv", additionMenu);
    additionMenu->addAction(staticCsvAct);
    connect(staticCsvAct, &QAction::triggered, this, &SettingWidget::readCsvStaticDataRequested);

    connect(addButton, &QPushButton::released, [this]()
    {
        const int posX = addButton->pos().x();
        const int posY = addButton->pos().y() + addButton->rect().height();
        additionMenu->exec(mapToGlobal(QPoint(posX, posY)));
    });
}

void SettingWidget::addStaticSurfaceWidget(QSurface3DSeries *series)
{

}
