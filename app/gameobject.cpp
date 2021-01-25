
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
