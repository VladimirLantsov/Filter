#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OutputImage.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    DisplayImage* displayImage;

    QSlider* pixelSizeSlider;
    QLabel* currentPixelSizeLabel;
    QPushButton* saveButton;

    QString imageName;

public:
    MainWindow(QWidget* parent = 0);

private slots:
    void saveImage();
};

#endif // MAINWINDOW_H
