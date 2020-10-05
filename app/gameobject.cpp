#include "gameobject.hpp"

GameObject::GameObject(game_object_type type)
    : m_type(type)
{

}

game_object_type GameObject::getType() const
{
    return m_type;
}

void GameObject::setCenterPosition(qreal x, qreal y)
{
    QPointF centerPosition(x - (pixmap().width() / 2),
                           y - (pixmap().height() / 2));
    setPos(centerPosition);
}

void GameObject::setCenterPosition(QPointF position)
{
    setCenterPosition(position.x(), position.y());
}

QPointF GameObject::getCenterPosition() const
{
    QPointF centerPosition = pos();
    centerPosition.setX(centerPosition.x() + (pixmap().width() / 2));
    centerPosition.setY(centerPosition.y() + (pixmap().height() / 2));
    return centerPosition;
}
