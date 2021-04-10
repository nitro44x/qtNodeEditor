#include <forms/sceneWidget.hpp>

#include "node.hpp"
#include "edge.hpp"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

namespace sackofcheese {

    SceneWidget::SceneWidget(QWidget* parent) : QGraphicsView(parent) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        //scene->setSceneRect(-200, -200, 400, 400);
        setScene(scene);
        setCacheMode(CacheBackground);
        setViewportUpdateMode(BoundingRectViewportUpdate);
        setRenderHint(QPainter::Antialiasing);
        setTransformationAnchor(AnchorUnderMouse);
        //scale(qreal(0.8), qreal(0.8));
        //setMinimumSize(400, 400);
        //setWindowTitle(tr("Elastic Nodes"));

        Node* node1 = new Node(this);
        Node* node2 = new Node(this);
        Node* node3 = new Node(this);
        Node* node4 = new Node(this);
        centerNode = new Node(this);
        Node* node6 = new Node(this);
        Node* node7 = new Node(this);
        Node* node8 = new Node(this);
        Node* node9 = new Node(this);
        scene->addItem(node1);
        scene->addItem(node2);
        scene->addItem(node3);
        scene->addItem(node4);
        scene->addItem(centerNode);
        scene->addItem(node6);
        scene->addItem(node7);
        scene->addItem(node8);
        scene->addItem(node9);
        scene->addItem(new Edge(node1, node2));
        scene->addItem(new Edge(node2, node3));
        scene->addItem(new Edge(node2, centerNode));
        scene->addItem(new Edge(node3, node6));
        scene->addItem(new Edge(node4, node1));
        scene->addItem(new Edge(node4, centerNode));
        scene->addItem(new Edge(centerNode, node6));
        scene->addItem(new Edge(centerNode, node8));
        scene->addItem(new Edge(node6, node9));
        scene->addItem(new Edge(node7, node4));
        scene->addItem(new Edge(node8, node7));
        scene->addItem(new Edge(node9, node8));

        node1->setPos(-50, -50);
        node2->setPos(0, -50);
        node3->setPos(50, -50);
        node4->setPos(-50, 0);
        centerNode->setPos(0, 0);
        node6->setPos(50, 0);
        node7->setPos(-50, 50);
        node8->setPos(0, 50);
        node9->setPos(50, 50);
    }

    SceneWidget::~SceneWidget() = default;

    void SceneWidget::itemMoved() {
        if (!timerId)
            timerId = startTimer(1000 / 25);
    }

    void SceneWidget::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_Space:
        {
            QVector<Node*> nodes;
            const QList<QGraphicsItem*> items = scene()->items();
            for (QGraphicsItem* item : items) {
                if (Node* node = qgraphicsitem_cast<Node*>(item))
                    nodes << node;
            }

            for (Node* node : qAsConst(nodes))
                node->equilibrate();
            itemMoved();
            break;
        }
        case Qt::Key_Enter:
            shuffle();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
        }
    }

    void SceneWidget::timerEvent(QTimerEvent* event) {
        Q_UNUSED(event);

        QVector<Node*> nodes;
        const QList<QGraphicsItem*> items = scene()->items();
        for (QGraphicsItem* item : items) {
            if (Node* node = qgraphicsitem_cast<Node*>(item))
                nodes << node;
        }

        for (Node* node : qAsConst(nodes))
            node->calculateForces();

        bool itemsMoved = false;
        for (Node* node : qAsConst(nodes)) {
            if (node->advancePosition())
                itemsMoved = true;
        }

        if (!itemsMoved) {
            killTimer(timerId);
            timerId = 0;
            setSceneRect(scene()->itemsBoundingRect());
            for (Node* node : qAsConst(nodes))
                node->lockPosition();
        }
    }

#if QT_CONFIG(wheelevent)
    void SceneWidget::wheelEvent(QWheelEvent* event) {
        scaleView(pow(2., -event->angleDelta().y() / 240.0));
    }
#endif

    void SceneWidget::drawBackground(QPainter* painter, const QRectF& rect) {
        Q_UNUSED(rect);

        // Shadow
        QRectF sceneRect = this->sceneRect();

        // Fill
        QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::lightGray);
        painter->fillRect(rect.intersected(sceneRect), gradient);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(sceneRect);
    }

    void SceneWidget::scaleView(qreal scaleFactor) {
        qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
        if (factor < 0.07 || factor > 100)
            return;

        scale(scaleFactor, scaleFactor);
    }

    void SceneWidget::shuffle() {
        const QList<QGraphicsItem*> items = scene()->items();
        for (QGraphicsItem* item : items) {
            if (qgraphicsitem_cast<Node*>(item))
                item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
        }
    }

    void SceneWidget::zoomIn() {
        scaleView(qreal(1.2));
    }

    void SceneWidget::zoomOut() {
        scaleView(1 / qreal(1.2));
    }
}