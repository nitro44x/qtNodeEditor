#pragma once

#include <QGraphicsItem>
#include <QVector>

namespace sackofcheese {

    class Edge;
    class SceneWidget;

    class Node : public QGraphicsItem {

    public:
        Node(SceneWidget* graphWidget);

        void addEdge(Edge* edge);
        QVector<Edge*> edges() const;

        enum { Type = UserType + 1 };
        int type() const override { return Type; }

        void calculateForces();
        bool advancePosition();

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        void equilibrate();
        void lockPosition();

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    private:
        QVector<Edge*> edgeList;
        QPointF newPos;
        SceneWidget* graph;
        double vTol = 100;
    };
}