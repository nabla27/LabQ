#ifndef SERIALVIEWTAB_H
#define SERIALVIEWTAB_H

#include <QTabWidget>
#include <QWidget>
#include <QDebug>
#include <QMenu>
#include <QMouseEvent>
#include <QTabBar>

class SerialViewTab : public QTabWidget
{
    Q_OBJECT

public:
    SerialViewTab(QWidget *parent);
    void initializeContextMenu();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QMenu *contextMenu = nullptr;

signals:
    void addTextBrowserSelected();
    void addGraph2dSelected();
};

#endif // SERIALVIEWTAB_H
