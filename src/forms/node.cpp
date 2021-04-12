#include <forms/node.hpp>

#include <forms/edge.hpp>
#include <forms/sceneWidget.hpp>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

namespace {
    static const int kWidth = 100;
    static const int kHeight = 75;
    static const int kSelectionZonePadding = 5;
    static const int kPadding = 3;
}

namespace sackofcheese {

    InnerNode::InnerNode(QGraphicsItem* parent) {
        setParentItem(parent);
    }

    QRectF InnerNode::boundingRect() const {
        qreal x = -(kPadding + kWidth / 2.0);
        qreal y = -(kPadding + kHeight / 2.0);
        qreal width = kWidth + 2 * kPadding;
        qreal height = kHeight + 2 * kPadding;
        return QRectF(x, y, width, height);
    }

    QPainterPath InnerNode::shape() const {
        QPainterPath path;
        path.addEllipse(-kWidth / 2.0, -kHeight / 2.0, kWidth, kHeight);
        return path;
    }

    void InnerNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::cyan);

        if (option->state & QStyle::State_Sunken) {
            painter->setPen(QPen(Qt::black, 4, Qt::DashLine));
            painter->setBrush(Qt::magenta);
        }
        else if (option->state & QStyle::State_MouseOver) {
            painter->setPen(QPen(Qt::black, 4));
        }
        else if (option->state & QStyle::State_Selected) {
            painter->setPen(QPen(Qt::yellow, 4));
        }

        painter->drawEllipse(-kWidth / 2.0, -kHeight / 2.0, kWidth, kHeight);
    }

    QVariant InnerNode::itemChange(GraphicsItemChange change, const QVariant& value) {
        return QGraphicsItem::itemChange(change, value);
    }

    void InnerNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        // Update item state (sunken/raised)
        update();
        QGraphicsItem::mousePressEvent(event);
    }

    void InnerNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        // Update item state (sunken/raised)
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }

    void InnerNode::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
        update();
        QGraphicsItem::hoverEnterEvent(event);
    }

    void InnerNode::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
        update();
        QGraphicsItem::hoverLeaveEvent(event);
    }

    NodeConnectionZone::NodeConnectionZone(QGraphicsItem* parent) {
        setParentItem(parent);
    }

    QRectF NodeConnectionZone::boundingRect() const {
        qreal x = -(kPadding + kWidth / 2.0);
        qreal y = -(kPadding + kHeight / 2.0);
        qreal width = kWidth + 2 * kPadding;
        qreal height = kHeight + 2 * kPadding;
        return QRectF(x, y, width, height);
    }

    QPainterPath NodeConnectionZone::shape() const {
        QPainterPath path;
        path.addEllipse(-kWidth / 2.0, -kHeight / 2.0, kWidth, kHeight);
        return path;
    }

    void NodeConnectionZone::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::cyan);

        if (option->state & QStyle::State_Sunken) {
            painter->setPen(QPen(Qt::black, 4, Qt::DashLine));
            painter->setBrush(Qt::magenta);
        }
        else if (option->state & QStyle::State_MouseOver) {
            painter->setPen(QPen(Qt::black, 4));
        }
        else if (option->state & QStyle::State_Selected) {
            painter->setPen(QPen(Qt::yellow, 4));
        }

        painter->drawEllipse(-kWidth / 2.0, -kHeight / 2.0, kWidth, kHeight);
    }

    QVariant NodeConnectionZone::itemChange(GraphicsItemChange change, const QVariant& value) {
        return QGraphicsItem::itemChange(change, value);
    }

    void NodeConnectionZone::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        // Update item state (sunken/raised)
        update();
        QGraphicsItem::mousePressEvent(event);
    }

    void NodeConnectionZone::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        // Update item state (sunken/raised)
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }

    void NodeConnectionZone::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
        update();
        QGraphicsItem::hoverEnterEvent(event);
    }

    void NodeConnectionZone::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
        update();
        QGraphicsItem::hoverLeaveEvent(event);
    }



    Node::Node(SceneWidget* graphWidget)
        : graph(graphWidget) {
        setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setCacheMode(DeviceCoordinateCache);
        setZValue(-1);
        setAcceptHoverEvents(true);
    }

    void Node::addEdge(Edge* edge) {
        edgeList << edge;
        edge->updateEndpoints();
    }

    QVector<Edge*> Node::edges() const {
        return edgeList;
    }

    QRectF Node::boundingRect() const {
        qreal x = -(kPadding + kWidth / 2.0);
        qreal y = -(kPadding + kHeight / 2.0);
        qreal width = kWidth + 2 * kPadding;
        qreal height = kHeight + 2 * kPadding;
        return QRectF(x, y, width, height);
    }

    QPainterPath Node::shape() const {
        QPainterPath path;
        path.addEllipse(-kWidth / 2.0, -kHeight / 2.0, kWidth, kHeight);
        return path;
    }

    void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::cyan);

        if (option->state & QStyle::State_Sunken) {
            painter->setPen(QPen(Qt::black, 4, Qt::DashLine));
            painter->setBrush(Qt::magenta);
        }
        else if (option->state & QStyle::State_MouseOver) {
            painter->setPen(QPen(Qt::black, 4));
        }
        else if (option->state & QStyle::State_Selected) {
            painter->setPen(QPen(Qt::yellow, 4));
        }

        painter->drawEllipse(-kWidth / 2.0, -kHeight / 2.0, kWidth, kHeight);
    }

    QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value) {

        if (ItemPositionHasChanged == change) {
            for (Edge* edge : qAsConst(edgeList))
                edge->updateEndpoints();
            graph->itemMoved();
        }

        return QGraphicsItem::itemChange(change, value);
    }

    void Node::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        // Update item state (sunken/raised)
        update();
        QGraphicsItem::mousePressEvent(event);
    }

    void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        // Update item state (sunken/raised)
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }

    void Node::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
        update();
        QGraphicsItem::hoverEnterEvent(event);
    }

    void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
        update();
        QGraphicsItem::hoverLeaveEvent(event);
    }
}