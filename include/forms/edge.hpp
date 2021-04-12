#pragma once

#include <forms/exports.hpp>

#include <QGraphicsItem>

namespace sackofcheese {
    class Node;

    class QTNODEEDITORFORMS_EXPORT Edge : public QGraphicsItem {
    public:
        Edge(Node* sourceNode, Node* destNode);

        Node* sourceNode() const;
        Node* destNode() const;

        void updateEndpoints();

        enum { Type = UserType + 200 };
        int type() const override { return Type; }

    protected:
        QRectF boundingRect() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    private:
        Node* source;
        Node* dest;

        QPointF sourcePoint;
        QPointF destPoint;
        qreal arrowSize = 10;
    };
}