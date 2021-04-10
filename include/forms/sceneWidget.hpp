#pragma once

#include <forms/exports.hpp>

#include <QWidget>
#include <QGraphicsView>

namespace sackofcheese {
    class Node;

    class QTNODEEDITORFORMS_EXPORT SceneWidget : public QGraphicsView {
        Q_OBJECT;

    public:
        SceneWidget(QWidget* parent = nullptr);
        ~SceneWidget();

        void itemMoved();

    public slots:
        void shuffle();
        void zoomIn();
        void zoomOut();

    protected:
        void keyPressEvent(QKeyEvent* event) override;
        void timerEvent(QTimerEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;
        void drawBackground(QPainter* painter, const QRectF& rect) override;

        void scaleView(qreal scaleFactor);

    private:
        int timerId = 0;
        Node* centerNode;
    };

}