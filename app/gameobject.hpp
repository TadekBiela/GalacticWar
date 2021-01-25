
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


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
    enemy_turret  = 4,
    reward        = 5
};

class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject(game_object_type type);
    virtual ~GameObject() {}
    game_object_type getType() const;
    void setCenterPosition(qreal x, qreal y);
    void setCenterPosition(QPointF position);
    QPointF getCenterPosition() const;

public slots:
    virtual void start() = 0;
    virtual void stop()  = 0;

private:
    game_object_type m_type;
};

#endif // GAMEOBJECT_HPP
