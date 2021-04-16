#include <forms/node.hpp>

#include <forms/edge.hpp>
#include <forms/sceneWidget.hpp>

#include "nodeConnection.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

namespace {
    static const int kWidth = 100;
    static const int kHeight = 75;
    static const int kSelectionZonePadding = 25;
    static const int kSelectionZoneWidth = kWidth + kSelectionZonePadding;
    static const int kSelectionZoneHeight = kHeight + kSelectionZonePadding;
    static const int kPadding = 3;
}

namespace sackofcheese {

    Node::Node(SceneWidget* graphWidget)
        : graph(graphWidget) {
        setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setCacheMode(DeviceCoordinateCache);
        setAcceptHoverEvents(true);

        new NodeConnectionZone(this);
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

    void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
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