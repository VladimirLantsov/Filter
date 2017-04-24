#include "OutputImage.h"

//=============================================================================

DisplayImage::DisplayImage(int pixelation, QImage image,
                                              QWidget* parent) : QLabel(parent)
{
    originalImage = image;
    setNewValuePixelation(pixelation);
}

//=============================================================================

void DisplayImage::changePixels(int x, int y, int pixelWidth, int pixelHeight)
{
    const QRgb color = resultImage.pixel(x, y);

    for(int i = y; i < (y + pixelHeight); ++i)
    {
        for(int j = x; j < (x + pixelWidth); ++j)
            resultImage.setPixel(j, i, color);
    }
}

//=============================================================================

bool DisplayImage::pixelsAtTheEdges(int xLimit, int yLimit, int imageWidth,
                                                               int imageHeight)
{
    if(xLimit < imageWidth)
    {
        int pixelWidth = imageWidth - xLimit;

        for(int y = 0; y < yLimit; y += pixelWidth)
            changePixels(xLimit, y, pixelWidth, pixelSize);
    }

    if(yLimit < imageHeight)
    {
        int pixelHeight = imageHeight - yLimit;

        for(int x = 0; x < xLimit; x += pixelHeight)
            changePixels(x, yLimit, pixelSize, pixelHeight);
    }

    if((xLimit < imageWidth) && (yLimit < imageHeight))
        return true;

    return false;
}

//=============================================================================

void DisplayImage::paintEvent(QPaintEvent*)
{
    if(originalImage.isNull())
    {
        resultImage = QImage(size(), QImage::Format_ARGB32_Premultiplied);

        QPainter painter(&resultImage);
        painter.setFont(QFont("Times", 30, QFont::Light));

        painter.setBrush(Qt::black);
        painter.drawRect(QRect(0, 0, width(), height()));

        painter.setPen(Qt::blue);
        painter.drawText(rect(), Qt::AlignCenter | Qt::TextWordWrap,
                                   "Specify the path to the image, please :)");
        painter.end();
    }
    else
        resultImage = originalImage;

    int imageWidth = resultImage.width();
    int imageHeight = resultImage.height();

    int xLimit = imageWidth % pixelSize ? imageWidth - pixelSize : imageWidth;
    int yLimit = imageHeight % pixelSize ? imageHeight - pixelSize : imageHeight;

    for(int y = 0; y < yLimit; y += pixelSize)
    {
        for(int x = 0; x < xLimit; x += pixelSize)
            changePixels(x, y, pixelSize, pixelSize);
    }

    if(pixelsAtTheEdges(xLimit, yLimit, imageWidth, imageHeight))
        changePixels(xLimit, yLimit, imageWidth - xLimit, imageHeight - yLimit);

    QPainter painter(this);
    painter.drawImage(rect(), resultImage);
    painter.end();
}

//=============================================================================

void DisplayImage::setImage(const QImage image)
{
    originalImage = image;
    update();
}

//=============================================================================

QImage DisplayImage::getResultImage() const
{
    return resultImage;
}

//=============================================================================

void DisplayImage::setNewValuePixelation(int value)
{    
    pixelSize = value;
    update();
}

//=============================================================================
