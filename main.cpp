#include <QLayout>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>

#include <functional>
#include <cmath>
#include <qwt_series_data.h>
#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <QApplication>
#include <qwt_point_data.h>

#include "Compass.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Create the widgets required,
    QWidget *mainWindow = new QWidget;

    mainWindow->setWindowTitle("Wind Speed");
    // Slider(0, 360)
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360);

    // SpinBox(0, 360)
    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 360);

    QLabel *windSpeedLbl = new QLabel("0");
    windSpeedLbl->setAlignment(Qt::AlignHCenter);
    windSpeedLbl->setStyleSheet("font-size: 18px; color: blue");

    // Push button for starting the Animation
    QPushButton *buttonF = new QPushButton("Animate - Forward");
    QPushButton *buttonB = new QPushButton("Animate - Backward");

    // Wind direction compass
    Compass *compass = new Compass;

    // Property Animation
    QPropertyAnimation *animation = new QPropertyAnimation(slider, "value");
    animation->setDuration(3600);

    // Lambda for starting the animation
    auto animationHandler = [&](int min, int max){
        animation->setStartValue(min);
        animation->setEndValue(max);
        animation->start();
    };

    // connect Slider, SpinBox and Label together
    // Slider -> SpinBox
    QObject::connect(slider, &QSlider::valueChanged, spinBox,
                     static_cast<void (QSpinBox::*)(int)>(&QSpinBox::setValue));

    // SpinBox -> Slider
    QObject::connect(spinBox, static_cast< void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     slider, &QSlider::setValue);

    // Slider -> Label
    QObject::connect(slider, &QSlider::valueChanged,
                     [=](int val){ windSpeedLbl->setText(QString::number(val)); });

    // Slider -> Compass
    QObject::connect(slider, &QSlider::valueChanged, compass, &Compass::setValue);

    // Start forward animation upon button click
    QObject::connect(buttonF, &QPushButton::clicked, std::bind(animationHandler, 0, 360));

    // Start backward animation upon button click
    QObject::connect(buttonB, &QPushButton::clicked, std::bind(animationHandler, 360, 0));
    
    int rowSpan = 7;

    // Create a GridLayout for all the widget
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(compass, 0, 0, rowSpan, 1);
    mainLayout->addWidget(windSpeedLbl, rowSpan+1, 0, 1, 1);
    mainLayout->addWidget(spinBox, rowSpan+2, 0, 1, 1);
    mainLayout->addWidget(slider, rowSpan+3, 0, 1, 1);
    mainLayout->addWidget(buttonF, rowSpan+4, 0, 1, 1);
    mainLayout->addWidget(buttonB, rowSpan+5, 0, 1, 1);

    // Add the layout to main window
    mainWindow->setLayout(mainLayout);

    // Set windows size to fixed size of given rectangle
    mainWindow->setGeometry(QRect(100, 100, 290, 435));
    mainWindow->show();

  return app.exec();
}
