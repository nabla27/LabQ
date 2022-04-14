#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H
#include <QWidget>
#include <QMenu>

#include <QSurface3DSeries>
#include <QSurfaceDataProxy>
#include <QSurfaceDataArray>
#include <QSurfaceDataRow>

#include <QFileDialog>
#include <QFile>

#include "layoutparts.h"

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);

private:
    void initializeAddtionMenu();

private:
    void addStaticSurfaceWidget(QSurface3DSeries *series);

private:
    QPushButton *expandButton;
    QComboBox *itemCombo;
    QPushButton *addButton;
    QStackedWidget *settingStacked;
    QMenu *additionMenu = nullptr;

signals:
    void readCsvStaticDataRequested();
};

#endif // SETTINGWIDGET_H
