#ifndef GRID_MESH_SETTING_WIDGET_H
#define GRID_MESH_SETTING_WIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QThread>
#include "../custommesh/surfacegridgeometry.h"
#include "../animation/animation.h"
#include "../numeric/equation.h"
#include "../numeric/pde.h"
#include "../numeric/wave.h"
#include "../animation/dynamicsurfacecontroller.h"
#include "../animation/pdequationsettingwidget.h"
#include "layoutparts.h"

class SurfaceGridMeshSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SurfaceGridMeshSettingWidget(SurfaceGridMesh *mesh);
    ~SurfaceGridMeshSettingWidget();

    SequentialAnimationGroup* animation() const { return animationGroup; }

private slots:
    void setInitState();
    void requestCalculate(const QVector<float>& init);
    void handlePostCalculation();

private:
    SurfaceGridMesh *mesh;

    SequentialAnimationGroup *animationGroup;
    PauseAnimation *pauseAnimation;
    PropertyAnimation *propertyAnimation;
    DynamicSurfaceController *controller;

    mlayout::PushButtonLayout *equationButton;
    mlayout::IntSbLayout *gridRow;
    mlayout::IntSbLayout *gridCol;
    mlayout::DoubleSbLayout *gridStride;

    mlayout::DoubleSbLayout *startTime;
    mlayout::DoubleSbLayout *deltaTime;
    mlayout::IntSbLayout *stepCount;

    QStackedWidget *stackedWidget;
    QPushButton *button;
    QProgressBar *progressBar;

    PDEquationSettingWidget *equationSettingWidget;

    QThread calculationThread;

signals:
    void initializationRequested(const QList<equation::InitWithFormulaExpCondition::Range>& range,
                                 const QStringList& condition,
                                 const qsizetype row,
                                 const qsizetype col,
                                 const float dx);
    void calculationRequested();

};


#endif // GRID_MESH_SETTING_WIDGET_H
