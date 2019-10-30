#include "graphicsview.hpp"

GraphicsView::GraphicsView()
{

}

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
                            : QGraphicsView(scene, parent)
{
    setMouseTracking(true);
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    emit mousePressed(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseReleased(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoved(event);
}
