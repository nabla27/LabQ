#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H
#include <QMainWindow>
#include <QScreen>
#include <QVBoxLayout>
#include <QTabWidget>
#include "utility.h"
#include "scene3d.h"
#include "contorollerpanel.h"
#include "scenemanager.h"
#include "componentmanager.h"

class Graphics3D : public QMainWindow
{
    Q_OBJECT
public:
    explicit Graphics3D(QWidget *parent = nullptr);

private:
    void initializeLayout();

private:
    ContorollerPanel *contorollerPanel = nullptr;
    Scene3D *scene3d = nullptr;
    QWidget *scene3dWidget = nullptr;
    QTabWidget *managerWidget = nullptr;
    SceneManager *sceneManager = nullptr;
    ComponentManager *componentManager = nullptr;

signals:

};

#endif // GRAPHICS3D_H
