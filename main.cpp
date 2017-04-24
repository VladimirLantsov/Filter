#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(400, 400);
    mainWindow.setWindowTitle("Pixelation");
    mainWindow.show();

    return app.exec();
}
