#include <QApplication>

#include <forms/mainWindow.hpp>
#include <forms/sceneWidget.hpp>
#include <forms/node.hpp>
#include <forms/edge.hpp>

struct SampleSetup {
    static void tutorialInit(sackofcheese::SceneWidget* scene) {
        sackofcheese::Node* node1 = new sackofcheese::Node(scene);
        sackofcheese::Node* node2 = new sackofcheese::Node(scene);
        sackofcheese::Node* node3 = new sackofcheese::Node(scene);
        sackofcheese::Node* node4 = new sackofcheese::Node(scene);
        sackofcheese::Node* node5 = new sackofcheese::Node(scene);
        sackofcheese::Node* node6 = new sackofcheese::Node(scene);
        sackofcheese::Node* node7 = new sackofcheese::Node(scene);
        sackofcheese::Node* node8 = new sackofcheese::Node(scene);
        sackofcheese::Node* node9 = new sackofcheese::Node(scene);
        scene->addItem(node1);
        scene->addItem(node2);
        scene->addItem(node3);
        scene->addItem(node4);
        scene->addItem(node5);
        scene->addItem(node6);
        scene->addItem(node7);
        scene->addItem(node8);
        scene->addItem(node9);
        scene->addItem(new sackofcheese::Edge(node1, node2));
        scene->addItem(new sackofcheese::Edge(node2, node3));
        scene->addItem(new sackofcheese::Edge(node2, node5));
        scene->addItem(new sackofcheese::Edge(node3, node6));
        scene->addItem(new sackofcheese::Edge(node4, node1));
        scene->addItem(new sackofcheese::Edge(node4, node5));
        scene->addItem(new sackofcheese::Edge(node5, node6));
        scene->addItem(new sackofcheese::Edge(node5, node8));
        scene->addItem(new sackofcheese::Edge(node6, node9));
        scene->addItem(new sackofcheese::Edge(node7, node4));
        scene->addItem(new sackofcheese::Edge(node8, node7));
        scene->addItem(new sackofcheese::Edge(node9, node8));

        node1->setPos(-50, -50);
        node2->setPos(0, -50);
        node3->setPos(50, -50);
        node4->setPos(-50, 0);
        node5->setPos(0, 0);
        node6->setPos(50, 0);
        node7->setPos(-50, 50);
        node8->setPos(0, 50);
        node9->setPos(50, 50);
    }

    static void singleNode(sackofcheese::SceneWidget* scene) {
        sackofcheese::Node* n = new sackofcheese::Node(scene);
        scene->addItem(n);
        n->setPos(0, 0);
    }

    static void empty(sackofcheese::SceneWidget* ) { }
};

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    auto scene = new sackofcheese::SceneWidget();
    //SampleSetup::tutorialInit(scene);
    //SampleSetup::singleNode(scene);
    SampleSetup::empty(scene);
    sackofcheese::MainWindow win;
    win.setCentralWidget(scene);
    win.show();

    return app.exec();
}