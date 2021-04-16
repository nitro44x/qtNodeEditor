#pragma once

#include <QGraphicsItem>

namespace sackofcheese {

    class NodeConnectionZone : public QGraphicsItem {

    public:
        NodeConnectionZone(QGraphicsItem* parent = nullptr);

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
    };

}