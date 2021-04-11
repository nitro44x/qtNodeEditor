#include <forms/sceneWidget.hpp>

#include <forms/node.hpp>
#include <forms/edge.hpp>

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMouseEvent>

namespace sackofcheese {

    SceneWidget::SceneWidget(QWidget* parent) : QGraphicsView(parent), centerNode(nullptr) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        scene->setSceneRect(-200, -200, 400, 400);
        setScene(scene);
        setCacheMode(CacheBackground);
        setViewportUpdateMode(BoundingRectViewportUpdate);
        setRenderHint(QPainter::Antialiasing);
        setTransformationAnchor(AnchorUnderMouse);
        //scale(qreal(0.8), qreal(0.8));
        //setMinimumSize(400, 400);
        //setWindowTitle(tr("Elastic Nodes"));

    }

    SceneWidget::~SceneWidget() = default;

    void SceneWidget::itemMoved() {
        if (!timerId)
            timerId = startTimer(1000 / 25);
    }

    void SceneWidget::addItem(QGraphicsItem* n) {
        scene()->addItem(n);
    }

    void SceneWidget::setCenterItem(Node* n) {
        centerNode = n;
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

        QRectF sceneRect = this->sceneRect();

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

    void SceneWidget::mousePressEvent(QMouseEvent* event) {
        QGraphicsView::mousePressEvent(event);
    }

    void SceneWidget::mouseReleaseEvent(QMouseEvent* event) {
        switch (event->button()) {
        case Qt::RightButton:
            addItem(mapToScene(event->pos()));
            break;
        default:
            QGraphicsView::mouseReleaseEvent(event);
        }
    }

    void SceneWidget::addItem(QPointF pt) {
        Node* node = new Node(this);
        scene()->addItem(node);
        scene()->addItem(new Edge(node, centerNode));
        node->setPos(pt.x(), pt.y());
    }
}