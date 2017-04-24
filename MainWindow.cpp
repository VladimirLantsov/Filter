#include "MainWindow.h"

//=============================================================================

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    const int DEFAULT_PIXEL_SIZE = 12;

    imageName = "Image.jpg";

    displayImage = new DisplayImage(DEFAULT_PIXEL_SIZE, QImage(imageName));
    pixelSizeSlider = new QSlider(Qt::Horizontal);

    pixelSizeSlider->setRange(1, 100);
    pixelSizeSlider->setValue(DEFAULT_PIXEL_SIZE);

    currentPixelSizeLabel = new QLabel;
    currentPixelSizeLabel->setNum(DEFAULT_PIXEL_SIZE);

    saveButton = new QPushButton("Save");

    QHBoxLayout* pixelSizeSliderAndLabel = new QHBoxLayout;
    pixelSizeSliderAndLabel->addWidget(pixelSizeSlider);
    pixelSizeSliderAndLabel->addWidget(currentPixelSizeLabel);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(displayImage);
    layout->addLayout(pixelSizeSliderAndLabel);
    layout->addWidget(saveButton);

    layout->setStretch(0, 1);

    setLayout(layout);

    QObject::connect(pixelSizeSlider, SIGNAL(valueChanged(int)),
                               displayImage, SLOT(setNewValuePixelation(int)));

    QObject::connect(pixelSizeSlider, SIGNAL(valueChanged(int)),
                                    currentPixelSizeLabel, SLOT(setNum(int)));

    QObject::connect(saveButton, SIGNAL(clicked()), SLOT(saveImage()));
}

//=============================================================================

void MainWindow::saveImage()
{
    QString resultName = imageName;
    resultName.replace(".jpg", "_RESULT.jpg");

    if(!displayImage->getResultImage().save(resultName))
        qDebug() << "Error!";
}

//=============================================================================
