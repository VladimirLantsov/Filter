#ifndef OUTPUT_IMAGE_H
#define OUTPUT_IMAGE_H

#include <QtWidgets>

class DisplayImage : public QLabel
{
    Q_OBJECT

private:    
    QImage originalImage;
    QImage resultImage;

    int pixelSize;

    void changePixels(int x, int y, int pixelWidth, int pixelHeight);

    bool pixelsAtTheEdges(int xLimit, int yLimit, int imageWidth, int imageHeight);

protected:
    void paintEvent(QPaintEvent*);

public:
    DisplayImage(int pixelation, QImage image = QImage(), QWidget* parent = 0);

    void setImage(const QImage image);

    QImage getResultImage() const;

private slots:
    void setNewValuePixelation(int value);
};

#endif // OUTPUT_IMAGE_H
