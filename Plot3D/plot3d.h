#ifndef PLOT3D_H
#define PLOT3D_H
#include <QMainWindow>
#include <QMenuBar>
#include <Qt3DExtras/Qt3DWindow>
#include "graph3d.h"
#include "settingwidget.h"
#include "controllerpanel.h"
#include "settingpanel.h"
#include "utility.h"

class Plot3D : public QMainWindow
{
    Q_OBJECT
public:
    explicit Plot3D(QWidget *parent = nullptr);

private:
    void initializeMenuBar();
    void initializeLayout();

private:
    //Q3DSurface *graph = nullptr;
    //Graph3D *ploter = nullptr;
    QWidget *container = nullptr;
    ControllerPanel *cpanel = nullptr;
    SettingPanel *settingPanel = nullptr;
    SettingWidget *settingWidget = nullptr;

signals:

};

#endif // PLOT3D_H
