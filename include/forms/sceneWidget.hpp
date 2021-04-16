#pragma once

#include <forms/exports.hpp>

#include <QWidget>
#include <QGraphicsView>

namespace sackofcheese {
    class Node;
    class ConnectionMaker;

    class QTNODEEDITORFORMS_EXPORT SceneWidget : public QGraphicsView {
        Q_OBJECT;

        void addNewNode(QPointF pt);
        int timerId = 0;
        std::unique_ptr<ConnectionMaker> mConnector = nullptr;

    public:
        SceneWidget(QWidget* parent = nullptr);
        ~SceneWidget();

        void itemMoved();

        void addItem(QGraphicsItem* n);

        ConnectionMaker* getConnector() const;

    public slots:
        void zoomIn();
        void zoomOut();

    protected:
        void keyPressEvent(QKeyEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;
        void drawBackground(QPainter* painter, const QRectF& rect) override;

        void scaleView(qreal scaleFactor);

        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;

        void resizeEvent(QResizeEvent* event) override;
    };
}