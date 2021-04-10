#include <QApplication>

#include "mainWindow.hpp"

int main(int argc, char**argv) {

    QApplication app(argc, argv);

    sackofcheese::MainWindow win;
    win.show();

    return app.exec();
}