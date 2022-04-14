#include "plot3d.h"

Plot3D::Plot3D(QWidget *parent)
    : QMainWindow{parent}
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.5, 0.5));

    initializeLayout();
    initializeMenuBar();
}

void Plot3D::initializeMenuBar()
{
    if(menuBar()) delete menuBar();

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *test = new QMenu("test", menuBar);
    menuBar->addMenu(test);
}

void Plot3D::initializeLayout()
{
    if(centralWidget()) delete centralWidget();

    setCentralWidget(new QWidget(this));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    centralWidget()->setLayout(mainLayout);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    //centralWidget()->setContentsMargins(0, 0, 0, 0);
    //leftLayout->setContentsMargins(0, 0, 0, 0);

    cpanel = new ControllerPanel(centralWidget());
    //graph = new Q3DSurface;
    //container = QWidget::createWindowContainer(graph);
    //settingPanel = new SettingPanel(centralWidget());
    settingWidget = new SettingWidget(centralWidget());
    //container->setContentsMargins(0, 0, 0, 0);
    //ploter = new Graph3D(graph, this);

    leftLayout->addWidget(cpanel);
    leftLayout->addWidget(container);
    //rightLayout->addWidget(settingPanel);
    rightLayout->addWidget(settingWidget);

    //connect(settingWidget, &SettingWidget::readCsvStaticDataRequested, ploter, &Graph3D::readCsvStaticData);
}

