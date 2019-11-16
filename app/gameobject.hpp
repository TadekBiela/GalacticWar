#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QObject>
#include <QGraphicsPixmapItem>

class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject();
    virtual ~GameObject() {}

public slots:
    virtual void start() = 0;
    virtual void stop()  = 0;
};

#endif // GAMEOBJECT_HPP
