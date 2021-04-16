#pragma once

#include <QGraphicsItem>

namespace sackofcheese {

    class Node;

    class ConnectionMaker final {
    public:
        ~ConnectionMaker();

        void startMakingConnection(Node* src);
        void finishMakingConnection(Node* dest);
        void reset();
        bool active() const;

    private:
        Node* m_src = nullptr;
        Node* m_dst = nullptr;
    };

    class NodeConnectionZone : public QGraphicsItem {
    public:
        NodeConnectionZone(ConnectionMaker * connector, QGraphicsItem* parent = nullptr);

        enum { Type = UserType + 102 };
        int type() const override { return Type; }

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    private:
        ConnectionMaker* mConnector = nullptr;
    };

}