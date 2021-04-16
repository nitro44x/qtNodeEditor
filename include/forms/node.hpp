#pragma once

#include <forms/exports.hpp>

#include <QGraphicsItem>
#include <QVector>

namespace sackofcheese {

    class Edge;
    class SceneWidget;
    class ConnectionMaker;

    class QTNODEEDITORFORMS_EXPORT Node : public QGraphicsItem {

    public:
        Node(SceneWidget* graphWidget);
        Node(SceneWidget* graphWidget, ConnectionMaker * connector);

        void addEdge(Edge* edge);
        QVector<Edge*> edges() const;

        enum { Type = UserType + 100 };
        int type() const override { return Type; }

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        QVector<QPointF> connectionPoints() const;

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;


    private:
        QVector<Edge*> edgeList;
        QPointF newPos;
        SceneWidget* graph;
        ConnectionMaker* mConnector;
    };

}