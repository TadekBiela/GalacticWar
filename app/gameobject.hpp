#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject();
    virtual const QPointF getPosition() const { return QGraphicsPixmapItem::pos(); }
};

#endif // GAMEOBJECT_HPP
