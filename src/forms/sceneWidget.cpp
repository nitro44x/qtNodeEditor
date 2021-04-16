#include <forms/sceneWidget.hpp>

#include <forms/node.hpp>
#include <forms/edge.hpp>

#include "nodeConnection.hpp"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMouseEvent>

namespace sackofcheese {

    SceneWidget::SceneWidget(QWidget* parent) : QGraphicsView(parent), mConnector(std::make_unique<ConnectionMaker>()) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        setScene(scene);
        setCacheMode(CacheBackground);
        setViewportUpdateMode(BoundingRectViewportUpdate);
        setRenderHint(QPainter::Antialiasing);
        setTransformationAnchor(AnchorUnderMouse);
    }

    SceneWidget::~SceneWidget() = default;

    void SceneWidget::itemMoved() {}

    void SceneWidget::addItem(QGraphicsItem* n) {
        scene()->addItem(n);
    }

    ConnectionMaker* SceneWidget::getConnector() const {
        return mConnector.get();
    }

    void SceneWidget::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
        }
    }

#if QT_CONFIG(wheelevent)
    void SceneWidget::wheelEvent(QWheelEvent* event) {
        scaleView(pow(2., -event->angleDelta().y() / 240.0));
    }
#endif

    void SceneWidget::drawBackground(QPainter* painter, const QRectF& rect) {
        QRectF sceneRect = this->sceneRect();
        painter->setPen(Qt::lightGray);
        painter->drawRect(sceneRect);
    }

    void SceneWidget::scaleView(qreal scaleFactor) {
        qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
        if (factor < 0.07 || factor > 100)
            return;

        scale(scaleFactor, scaleFactor);
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
            addNewNode(mapToScene(event->pos()));
            break;
        default:
            QGraphicsView::mouseReleaseEvent(event);
        }
    }

    void SceneWidget::resizeEvent(QResizeEvent* event) {
        auto const height = event->size().height();
        auto const width = event->size().width();
        scene()->setSceneRect(-width / 2.0, -height / 2.0, width, height);
    }

    void SceneWidget::addNewNode(QPointF pt) {
        Node* node = new Node(this);
        scene()->addItem(node);
        node->setPos(pt.x(), pt.y());
    }
}