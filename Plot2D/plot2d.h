#ifndef PLOT2D_H
#define PLOT2D_H

#include <QMainWindow>
#include <QMenuBar>
#include <QScreen>
#include "utility.h"

class Plot2D : public QMainWindow
{
    Q_OBJECT

public:
    Plot2D(QWidget *parent = nullptr);
    ~Plot2D();

private:
    void initializeMenuBar();
};
#endif // PLOT2D_H
