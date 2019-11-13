#include "graphicsview.hpp"
#include <QGraphicsEffect>

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

void GraphicsView::setGraphicsEffects(qreal opacity, qreal blurRadius)
{
    QGraphicsOpacityEffect* op = new QGraphicsOpacityEffect();
    op->setOpacity(opacity);
    setGraphicsEffect(op);
    QGraphicsBlurEffect* bl = new QGraphicsBlurEffect();
    bl->setBlurRadius(blurRadius);
    setGraphicsEffect(bl);
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
