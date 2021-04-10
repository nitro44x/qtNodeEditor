#include <QApplication>

#include <forms/mainWindow.hpp>
#include <forms/sceneWidget.hpp>

int main(int argc, char**argv) {

    QApplication app(argc, argv);

    auto scene = new sackofcheese::SceneWidget();
    sackofcheese::MainWindow win;
    win.setCentralWidget(scene);
    win.show();

    return app.exec();
}