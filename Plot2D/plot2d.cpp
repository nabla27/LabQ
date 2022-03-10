#include "plot2d.h"

Plot2D::Plot2D(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(getRectFromScreenRatio(screen()->size(), 0.5f, 0.5f));

    initializeMenuBar();
}

Plot2D::~Plot2D()
{
}

void Plot2D::initializeMenuBar()
{
    if(!menuBar()) delete menuBar();

    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = new QMenu("File", menuBar);
    menuBar->addMenu(fileMenu);

    QMenu *widgetMenu = new QMenu("Widget", menuBar);
    menuBar->addMenu(widgetMenu);

    setMenuBar(menuBar);
}

