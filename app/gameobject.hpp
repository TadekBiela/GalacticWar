#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

enum game_object_type
{
    player        = 0,
    player_bullet = 1,
    enemy         = 2,
    enemy_bullet  = 3,
    reward        = 4
};

class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject(game_object_type type);
    virtual ~GameObject() {}
    game_object_type getType() const;
    void setCenterPosition(int x, int y);
    void setCenterPosition(QPointF position);
    QPointF getCenterPosition() const;

public slots:
    virtual void start() = 0;
    virtual void stop()  = 0;

private:
    game_object_type m_type;
};

#endif // GAMEOBJECT_HPP
