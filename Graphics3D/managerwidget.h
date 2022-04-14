#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H
#include <QTabWidget>

class ManagerWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ManagerWidget(QWidget *parent = nullptr);

private:
    QTabWidget *tabWidget;

signals:

};

#endif // MANAGERWIDGET_H
