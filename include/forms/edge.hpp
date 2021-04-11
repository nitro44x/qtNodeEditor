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

        void adjust();

        enum { Type = UserType + 2 };
        int type() const override { return Type; }

    protected:
        QRectF boundingRect() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    private:
        Node* source, * dest;

        QPointF sourcePoint;
        QPointF destPoint;
        qreal arrowSize = 10;
    };
}