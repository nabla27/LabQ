#include "controllerpanel.h"

ControllerPanel::ControllerPanel(QWidget *parent)
    : QWidget{parent}, playIcon(QPixmap(":/icon/icon_play.png")), stopIcon(QPixmap(":/icon/icon_stop.png"))
{
    const int fixedHeight = 24;

    setMaximumHeight(30);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QHBoxLayout *layout = new QHBoxLayout;
    setLayout(layout);

    playButton = new QPushButton(playIcon, "", this);
    timeEditor = new QLineEdit("20.00", this);
    timeSlider = new QSlider(Qt::Orientation::Horizontal, this);
    fpsSpinBox = new QSpinBox(this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layout->addWidget(playButton);
    layout->addWidget(timeEditor);
    layout->addWidget(timeSlider);
    layout->addWidget(fpsSpinBox);
    layout->addItem(spacer);

    layout->setContentsMargins(0, 0, 0, 0);

    playButton->setFixedSize(fixedHeight, fixedHeight);
    playButton->setIconSize(QSize(fixedHeight, fixedHeight));

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    setPalette(palette);
    setAutoFillBackground(true);

    QColor colorPlayButtonNormal(Qt::black);
    QColor colorPlayButtonHover(Qt::gray);
    playButton->setStyleSheet(QString("QPushButton {background-color: %1;}"
                                      "QPushButton:hover {background-color: %2;}").arg(colorPlayButtonNormal.name(),
                                                                                       colorPlayButtonHover.name()));

    QColor colorTimeSlider(Qt::green);
    timeSlider->setStyleSheet(QString("QSlider::handle:horizontal {background-color: %1;}").arg(colorTimeSlider.name()));

    connect(playButton, &QPushButton::released, this, &ControllerPanel::changePlayIcon);
}

void ControllerPanel::changePlayIcon()
{
    isPlaying = !isPlaying;

    if(isPlaying)
        playButton->setIcon(stopIcon);
    else
        playButton->setIcon(playIcon);
}































