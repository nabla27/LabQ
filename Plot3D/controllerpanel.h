#ifndef CONTROLLERPANEL_H
#define CONTROLLERPANEL_H
#include <QWidget>

#include <QIcon>
#include <QPixmap>

#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QSpinBox>
#include <QSpacerItem>

class ControllerPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControllerPanel(QWidget *parent = nullptr);

private slots:
    void changePlayIcon();

private:
    QPushButton *playButton;
    QLineEdit *timeEditor;
    QSlider *timeSlider;
    QSpinBox *fpsSpinBox;
    bool isPlaying = false;
    QIcon playIcon;
    QIcon stopIcon;

signals:

};

#endif // CONTROLLERPANEL_H
