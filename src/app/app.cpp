#include <QApplication>

#include <forms/mainWindow.hpp>
#include <forms/sceneWidget.hpp>
#include <forms/node.hpp>
#include <forms/edge.hpp>

namespace sackofcheese {
    void initData(SceneWidget* scene) {
        Node* node1 = new Node(scene);
        Node* node2 = new Node(scene);
        Node* node3 = new Node(scene);
        Node* node4 = new Node(scene);
        Node* node5 = new Node(scene);
        Node* node6 = new Node(scene);
        Node* node7 = new Node(scene);
        Node* node8 = new Node(scene);
        Node* node9 = new Node(scene);
        scene->addItem(node1);
        scene->addItem(node2);
        scene->addItem(node3);
        scene->addItem(node4);
        scene->addItem(node5);
        scene->addItem(node6);
        scene->addItem(node7);
        scene->addItem(node8);
        scene->addItem(node9);
        scene->addItem(new Edge(node1, node2));
        scene->addItem(new Edge(node2, node3));
        scene->addItem(new Edge(node2, node5));
        scene->addItem(new Edge(node3, node6));
        scene->addItem(new Edge(node4, node1));
        scene->addItem(new Edge(node4, node5));
        scene->addItem(new Edge(node5, node6));
        scene->addItem(new Edge(node5, node8));
        scene->addItem(new Edge(node6, node9));
        scene->addItem(new Edge(node7, node4));
        scene->addItem(new Edge(node8, node7));
        scene->addItem(new Edge(node9, node8));

        node1->setPos(-50, -50);
        node2->setPos(0, -50);
        node3->setPos(50, -50);
        node4->setPos(-50, 0);
        node5->setPos(0, 0);
        node6->setPos(50, 0);
        node7->setPos(-50, 50);
        node8->setPos(0, 50);
        node9->setPos(50, 50);

        scene->setCenterItem(node5);
    }
}

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    auto scene = new sackofcheese::SceneWidget();
    sackofcheese::initData(scene);
    sackofcheese::MainWindow win;
    win.setCentralWidget(scene);
    win.show();

    return app.exec();
}