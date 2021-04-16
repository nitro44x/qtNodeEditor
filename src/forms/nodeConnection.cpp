#include "nodeConnection.hpp"

#include <forms/edge.hpp>
#include <forms/node.hpp>
#include <forms/sceneWidget.hpp>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

namespace {
    static const int kWidth = 100; //todo refactor these constants to a common place (with node.cpp)
    static const int kHeight = 75;
    static const int kSelectionZonePadding = 25;
    static const int kSelectionZoneWidth = kWidth + kSelectionZonePadding;
    static const int kSelectionZoneHeight = kHeight + kSelectionZonePadding;
    static const int kPadding = 0;
}

namespace sackofcheese {
    ConnectionMaker::~ConnectionMaker() = default;

    void ConnectionMaker::startMakingConnection(Node* src) {
        m_src = src;
    }

    void ConnectionMaker::finishMakingConnection(Node* dest) {
        m_dst = dest;
    }

    void ConnectionMaker::reset() {
        m_src = m_dst = nullptr;
    }

    bool ConnectionMaker::active() const {
        return m_src;
    }

    NodeConnectionZone::NodeConnectionZone(ConnectionMaker * connector, QGraphicsItem* parent) : mConnector(connector) {
        setFlag(ItemSendsGeometryChanges);
        setFlag(ItemStacksBehindParent);
        setCacheMode(DeviceCoordinateCache);
        setAcceptHoverEvents(true);

        setParentItem(parent);
    }

    QRectF NodeConnectionZone::boundingRect() const {
        qreal x = -(kPadding + kSelectionZoneWidth / 2.0);
        qreal y = -(kPadding + kSelectionZoneHeight / 2.0);
        qreal width = kSelectionZoneWidth + 2 * kPadding;
        qreal height = kSelectionZoneHeight + 2 * kPadding;
        return QRectF(x, y, width, height);
    }

    QPainterPath NodeConnectionZone::shape() const {
        QPainterPath path;
        qreal width = kSelectionZoneWidth + 2 * kPadding;
        qreal height = kSelectionZoneHeight + 2 * kPadding;
        path.addEllipse(-width / 2.0, -height / 2.0, width, height);
        return path;
    }

    void NodeConnectionZone::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) {

        painter->setPen(Qt::PenStyle::NoPen);
        if (option->state & QStyle::State_MouseOver) {
            painter->setBrush(Qt::gray);
        }
        else {
            painter->setBrush(Qt::lightGray);
        }

        painter->drawEllipse(-kSelectionZoneWidth / 2.0, -kSelectionZoneHeight / 2.0, kSelectionZoneWidth, kSelectionZoneHeight);
    }

    QVariant NodeConnectionZone::itemChange(GraphicsItemChange change, const QVariant& value) {
        return QGraphicsItem::itemChange(change, value);
    }

    void NodeConnectionZone::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        if(auto p = qgraphicsitem_cast<Node*>(parentItem()))
            mConnector->startMakingConnection(p);

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

}