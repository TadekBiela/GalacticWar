#include "graphicsview.hpp"
#include "gameobject.hpp"
#include <QGraphicsEffect>

GraphicsView::GraphicsView()
{

}

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
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

void GraphicsView::startAllItems()
{
    QGraphicsScene* scene = this->scene();
    auto items = scene->items();

    for (auto it = items.begin(); it != items.end(); it++)
    {
        GameObject* object = dynamic_cast<GameObject*>(*it);
        object->start();
    }
}

void GraphicsView::stopAllItems()
{
    QGraphicsScene* scene = this->scene();
    auto items = scene->items();

    for(auto i = 0; i != items.size(); i++)
    {
        GameObject* object = static_cast<GameObject*>(items[i]);
        object->stop();
    }
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
