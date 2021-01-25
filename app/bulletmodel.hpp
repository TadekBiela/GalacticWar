
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


#ifndef BULLETMODEL_HPP
#define BULLETMODEL_HPP

#include "gameobject.hpp"
#include <QPointF>
#include <QString>
#include <QTimer>

class BulletModel : public GameObject
{
    Q_OBJECT
public:
    BulletModel(QString          graphicsName,
                game_object_type type,
                QPointF          position,
                int              damage,
                int              direction,
                int              moveTimeDelay,
                float            pixmapScaleFactor = 1);
    virtual ~BulletModel();
    int getDamage() const;

public slots:
    void start();
    void stop();

protected slots:
    void move();

protected:
    int    m_damage;
    int    m_direction;
    QTimer m_moveTimer;
};

#endif //BULLETMODEL_HPP
