#include <forms/edge.hpp>

#include <forms/node.hpp>

#include <QPainter>
#include <QtMath>


namespace sackofcheese {

    Edge::Edge(Node* sourceNode, Node* destNode)
        : source(sourceNode), dest(destNode) {
        setAcceptedMouseButtons(Qt::NoButton);
        source->addEdge(this);
        dest->addEdge(this);
        updateEndpoints();
    }

    Node* Edge::sourceNode() const {
        return source;
    }

    Node* Edge::destNode() const {
        return dest;
    }

    void Edge::updateEndpoints() {
        if (!source || !dest)
            return;

        auto const srcConnectionPts = source->connectionPoints();
        auto const destConnectionPts = dest->connectionPoints();

        QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));

        for (auto const& srcPt : srcConnectionPts) {
            for (auto const& dstPt : destConnectionPts) {
                QLineF testLine(mapFromItem(source, srcPt), mapFromItem(dest, dstPt));
                if (testLine.length() < line.length())
                    line = testLine;
            }
        }

        prepareGeometryChange();

        sourcePoint = line.p1();
        destPoint = line.p2();
    }

    QRectF Edge::boundingRect() const {
        if (!source || !dest)
            return QRectF();

        qreal penWidth = 1;
        qreal extra = (penWidth + arrowSize) / 2.0;

        return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
            destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
    }

    void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
        if (!source || !dest)
            return;

        QLineF line(sourcePoint, destPoint);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;

        // Draw the line itself
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);

        // Draw the arrows
        double angle = std::atan2(-line.dy(), line.dx());

        QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
            cos(angle + M_PI / 3) * arrowSize);
        QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
            cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
            cos(angle - M_PI / 3) * arrowSize);
        QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
            cos(angle - M_PI + M_PI / 3) * arrowSize);

        painter->setBrush(Qt::black);
        painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
        painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    }

}