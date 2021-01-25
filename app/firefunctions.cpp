
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


#include "firefunctions.hpp"
#include "functions.hpp"
#include "bulletmodel.hpp"

void defaultFireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    BulletModel* bullet = new BulletModel("bullet_default",
                                          game_object_type::player_bullet,
                                          startPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);
}

void redLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    startPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          game_object_type::player_bullet,
                                          startPosition,
                                          baseDamage,
                                          def::up,
                                          30,
                                          0.65);
    scene->addItem(bullet);
}

void redLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    QPointF bulletPosition = startPosition;
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);
}

void redLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    QPointF bulletPosition = startPosition;
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 10);
    bulletPosition2.setY(startPosition.y() + 20);
    BulletModel* bullet2 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 3,
                                           def::up + 5,
                                           30,
                                           0.4);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 10);
    bulletPosition3.setY(startPosition.y() + 20);
    BulletModel* bullet3 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 3,
                                           def::up - 5,
                                           30,
                                           0.4);
    scene->addItem(bullet3);
}

void redLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    QPointF bulletPosition = startPosition;
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 10);
    bulletPosition2.setY(startPosition.y() + 20);
    BulletModel* bullet2 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 3,
                                           def::up + 4,
                                           30,
                                           0.45);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 10);
    bulletPosition3.setY(startPosition.y() + 20);
    BulletModel* bullet3 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 3,
                                           def::up - 4,
                                           30,
                                           0.45);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() + 14);
    bulletPosition4.setY(startPosition.y() + 24);
    BulletModel* bullet4 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition4,
                                           baseDamage / 4,
                                           def::up + 8,
                                           30,
                                           0.30);
    scene->addItem(bullet4);

    QPointF bulletPosition5 = startPosition;
    bulletPosition5.setX(startPosition.x() - 14);
    bulletPosition5.setY(startPosition.y() + 24);
    BulletModel* bullet5 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition5,
                                           baseDamage / 4,
                                           def::up - 8,
                                           30,
                                           0.30);
    scene->addItem(bullet5);
}

void redLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    QPointF bulletPosition = startPosition;
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 10);
    bulletPosition2.setY(startPosition.y() + 20);
    BulletModel* bullet2 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 2,
                                           def::up + 5,
                                           30,
                                           0.6);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 10);
    bulletPosition3.setY(startPosition.y() + 20);
    BulletModel* bullet3 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 2,
                                           def::up - 5,
                                           30,
                                           0.6);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() + 14);
    bulletPosition4.setY(startPosition.y() + 24);
    BulletModel* bullet4 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition4,
                                           baseDamage / 2.5,
                                           def::up + 10,
                                           30,
                                           0.45);
    scene->addItem(bullet4);

    QPointF bulletPosition5 = startPosition;
    bulletPosition5.setX(startPosition.x() - 14);
    bulletPosition5.setY(startPosition.y() + 24);
    BulletModel* bullet5 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition5,
                                           baseDamage / 2.5,
                                           def::up - 10,
                                           30,
                                           0.45);
    scene->addItem(bullet5);

    QPointF bulletPosition6 = startPosition;
    bulletPosition6.setX(startPosition.x() + 14);
    bulletPosition6.setY(startPosition.y() + 24);
    BulletModel* bullet6 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition6,
                                           baseDamage / 3,
                                           def::up + 15,
                                           30,
                                           0.35);
    scene->addItem(bullet6);

    QPointF bulletPosition7 = startPosition;
    bulletPosition7.setX(startPosition.x() - 14);
    bulletPosition7.setY(startPosition.y() + 24);
    BulletModel* bullet7 = new BulletModel("bullet_red",
                                           game_object_type::player_bullet,
                                           bulletPosition7,
                                           baseDamage / 3,
                                           def::up - 15,
                                           30,
                                           0.35);
    scene->addItem(bullet7);
}

void yellowLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static int fireSide = 1;
    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() - 10 * fireSide);
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_yellow",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage / 2,
                                          def::up - 15 * fireSide,
                                          def::defaultBulletSpeed,
                                          0.75);
    scene->addItem(bullet);
    fireSide *= -1;
}

void yellowLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    int   damage[3]    = { baseDamage / 3, baseDamage, baseDamage / 3 };
    int   direction[3] = {   def::up - 15,    def::up,   def::up + 15 };
    int   positionX[3] = {            -15,          0,             15 };
    float scale[3]     = {           0.65,          1,           0.65 };
    static int fireSide = 0;
    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() + positionX[fireSide]);
    bulletPosition.setY(startPosition.y() + 10);
    BulletModel* bullet = new BulletModel("bullet_yellow",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          damage[fireSide],
                                          direction[fireSide],
                                          def::defaultBulletSpeed,
                                          scale[fireSide]);
    scene->addItem(bullet);
    fireSide++;
    fireSide = fireSide % 3;
}

void yellowLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    int   damage[3]    = { baseDamage / 2, baseDamage, baseDamage / 2 };
    int   direction[3] = {   def::up - 15,    def::up,   def::up + 15 };
    int   positionX[3] = {            -15,          0,             15 };
    float scale[3]     = {           0.65,          1,           0.65 };
    static int fireSide = 0;
    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() + positionX[fireSide]);
    bulletPosition.setY(startPosition.y() + 10);
    BulletModel* bullet = new BulletModel("bullet_yellow",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          damage[fireSide],
                                          direction[fireSide],
                                          def::defaultBulletSpeed,
                                          scale[fireSide]);
    scene->addItem(bullet);
    fireSide++;
    fireSide = fireSide % 3;

    static int fireSide2 = 1;
    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireSide2);
    bulletPosition2.setY(startPosition.y() + 30);
    BulletModel* bullet2 = new BulletModel("bullet_yellow",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 4,
                                           def::left * fireSide2,
                                           def::defaultBulletSpeed,
                                           0.5);
    scene->addItem(bullet2);
    fireSide2 *= -1;
}

void yellowLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    int   damage[3]    = { baseDamage / 2, baseDamage, baseDamage / 2 };
    int   direction[3] = {   def::up - 15,    def::up,   def::up + 15 };
    int   positionX[3] = {            -15,          0,             15 };
    float scale[3]     = {           0.65,          1,           0.65 };
    static int fireSide = 0;
    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() + positionX[fireSide]);
    bulletPosition.setY(startPosition.y() + 10);
    BulletModel* bullet = new BulletModel("bullet_yellow",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          damage[fireSide],
                                          direction[fireSide],
                                          def::defaultBulletSpeed,
                                          scale[fireSide]);
    scene->addItem(bullet);
    fireSide++;
    fireSide = fireSide % 3;

    static int fireSide2 = 1;
    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireSide2);
    bulletPosition2.setY(startPosition.y() + 30);
    BulletModel* bullet2 = new BulletModel("bullet_yellow",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 3,
                                           def::left * fireSide2,
                                           def::defaultBulletSpeed,
                                           0.65);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() + 20 * fireSide2);
    bulletPosition3.setY(startPosition.y() + 50);
    BulletModel* bullet3 = new BulletModel("bullet_yellow",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 3,
                                           def::down - 30 * fireSide2,
                                           def::defaultBulletSpeed,
                                           0.65);
    scene->addItem(bullet3);
    fireSide2 *= -1;
}

void yellowLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    int sideFactor[3] = { -30, 0, 30 };
    static int fireSide = 0;
    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() + sideFactor[fireSide]);
    bulletPosition.setY(startPosition.y() + 10);
    BulletModel* bullet = new BulletModel("bullet_yellow",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage / 2,
                                          def::up + sideFactor[fireSide],
                                          def::defaultBulletSpeed,
                                          0.75);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 20);
    bulletPosition2.setY(startPosition.y() + 30 + sideFactor[fireSide]);
    BulletModel* bullet2 = new BulletModel("bullet_yellow",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 2,
                                           def::right + sideFactor[fireSide],
                                           def::defaultBulletSpeed,
                                           0.75);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() + sideFactor[fireSide] * -1);
    bulletPosition3.setY(startPosition.y() + 50);
    BulletModel* bullet3 = new BulletModel("bullet_yellow",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 2,
                                           def::down + sideFactor[fireSide],
                                           def::defaultBulletSpeed,
                                           0.75);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() - 20);
    bulletPosition4.setY(startPosition.y() + 30 + sideFactor[fireSide] * -1);
    BulletModel* bullet4 = new BulletModel("bullet_yellow",
                                           game_object_type::player_bullet,
                                           bulletPosition4,
                                           baseDamage / 2,
                                           def::left + sideFactor[fireSide],
                                           def::defaultBulletSpeed,
                                           0.75);
    scene->addItem(bullet4);

    fireSide++;
    fireSide = fireSide % 3;
}

void blueLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static int fireLeft = 1;
    startPosition.setX(startPosition.x() - 12 * fireLeft);
    startPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_blue",
                                          game_object_type::player_bullet,
                                          startPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);
    fireLeft *= -1;
}

void blueLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static bool fireUp = true;
    static int fireLeft = 1;

    if(fireUp)
    {
        QPointF bulletPosition = startPosition;
        BulletModel* bullet = new BulletModel("bullet_blue",
                                              game_object_type::player_bullet,
                                              bulletPosition,
                                              baseDamage,
                                              def::up,
                                              def::defaultBulletSpeed);
        scene->addItem(bullet);
    }

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 30);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 1.2,
                                           def::up - 30 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet2);
    fireLeft *= -1;
    fireUp = !fireUp;
}

void blueLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static int fireLeft = 1;

    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() - 12 * fireLeft);
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_blue",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 25);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 1.2,
                                           def::up - 30 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet2);
    fireLeft *= -1;
}

void blueLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static int fireLeft = 1;

    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() - 12 * fireLeft);
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_blue",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 25);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 1.2,
                                           def::up - 30 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 25 * fireLeft);
    bulletPosition3.setY(startPosition.y() + 30);
    BulletModel* bullet3 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 2,
                                           def::up - 45 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet3);
    fireLeft *= -1;
}

void blueLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static int fireLeft = 1;

    QPointF bulletPosition = startPosition;
    bulletPosition.setX(startPosition.x() - 12 * fireLeft);
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_blue",
                                          game_object_type::player_bullet,
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 25);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition2,
                                           baseDamage / 1.2,
                                           def::up - 45 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 25 * fireLeft);
    bulletPosition3.setY(startPosition.y() + 30);
    BulletModel* bullet3 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition3,
                                           baseDamage / 2,
                                           def::up - 75 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() - 25 * fireLeft);
    bulletPosition4.setY(startPosition.y() + 45);
    BulletModel* bullet4 = new BulletModel("bullet_blue",
                                           game_object_type::player_bullet,
                                           bulletPosition4,
                                           baseDamage / 2,
                                           def::up + 90 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet4);
    fireLeft *= -1;
}

void redExtraBeamFireFunc(
    QGraphicsScene* scene,
    QPointF startPosition,
    int baseDamage
) {
    QPointF bullet1Position = startPosition;
    bullet1Position.ry() += 20;
    BulletModel* bullet1 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet1Position,
        baseDamage,
        def::up,
        30
    );
    scene->addItem(bullet1);

    QPointF bullet2Position = startPosition;
    bullet2Position.ry() -= 20;
    BulletModel* bullet2 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet2Position,
        baseDamage,
        def::down,
        30
    );
    scene->addItem(bullet2);

    QPointF bullet3Position = startPosition;
    bullet3Position.rx() += 20;
    BulletModel* bullet3 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet3Position,
        baseDamage,
        def::right,
        30
    );
    scene->addItem(bullet3);

    QPointF bullet4Position = startPosition;
    bullet4Position.rx() -= 20;
    BulletModel* bullet4 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet4Position,
        baseDamage,
        def::left,
        30
    );
    scene->addItem(bullet4);

    QPointF bullet5Position = startPosition;
    bullet5Position.rx() -= 10;
    bullet5Position.ry() -= 10;
    BulletModel* bullet5 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet5Position,
        baseDamage / 2,
        def::up - 45,
        30,
        0.5
    );
    scene->addItem(bullet5);

    QPointF bullet6Position = startPosition;
    bullet6Position.rx() += 10;
    bullet6Position.ry() -= 10;
    BulletModel* bullet6 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet6Position,
        baseDamage / 2,
        def::up + 45,
        30,
        0.5
    );
    scene->addItem(bullet6);

    QPointF bullet7Position = startPosition;
    bullet7Position.rx() -= 10;
    bullet7Position.ry() += 10;
    BulletModel* bullet7 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet7Position,
        baseDamage / 2,
        def::down + 45,
        30,
        0.5
    );
    scene->addItem(bullet7);

    QPointF bullet8Position = startPosition;
    bullet8Position.rx() -= 10;
    bullet8Position.ry() -= 10;
    BulletModel* bullet8 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet8Position,
        baseDamage / 2,
        def::down - 45,
        30,
        0.5
    );
    scene->addItem(bullet8);

    QPointF bullet9Position = startPosition;
    bullet9Position.rx() += 5;
    bullet9Position.ry() -= 15;
    BulletModel* bullet9 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet9Position,
        baseDamage / 3,
        def::up + 22,
        30,
        0.25
    );
    scene->addItem(bullet9);

    QPointF bullet10Position = startPosition;
    bullet10Position.rx() += 15;
    bullet10Position.ry() -= 5;
    BulletModel* bullet10 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet10Position,
        baseDamage / 3,
        def::up + 69,
        30,
        0.25
    );
    scene->addItem(bullet10);

    QPointF bullet11Position = startPosition;
    bullet11Position.rx() -= 5;
    bullet11Position.ry() -= 15;
    BulletModel* bullet11 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet11Position,
        baseDamage / 3,
        def::up - 22,
        30,
        0.25
    );
    scene->addItem(bullet11);

    QPointF bullet12Position = startPosition;
    bullet12Position.rx() -= 15;
    bullet12Position.ry() -= 5;
    BulletModel* bullet12 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet12Position,
        baseDamage / 3,
        def::up - 69,
        30,
        0.25
    );
    scene->addItem(bullet12);

    QPointF bullet13Position = startPosition;
    bullet13Position.rx() += 5;
    bullet13Position.ry() += 15;
    BulletModel* bullet13 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet13Position,
        baseDamage / 3,
        def::down - 22,
        30,
        0.25
    );
    scene->addItem(bullet13);

    QPointF bullet14Position = startPosition;
    bullet14Position.rx() += 15;
    bullet14Position.ry() += 5;
    BulletModel* bullet14 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet14Position,
        baseDamage / 3,
        def::down - 69,
        30,
        0.25
    );
    scene->addItem(bullet14);

    QPointF bullet15Position = startPosition;
    bullet15Position.rx() -= 5;
    bullet15Position.ry() += 15;
    BulletModel* bullet15 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet15Position,
        baseDamage / 3,
        def::down + 22,
        30,
        0.25
    );
    scene->addItem(bullet15);

    QPointF bullet16Position = startPosition;
    bullet16Position.rx() -= 15;
    bullet16Position.ry() += 5;
    BulletModel* bullet16 = new BulletModel(
        "bullet_red",
        game_object_type::player_bullet,
        bullet16Position,
        baseDamage / 3,
        def::down + 69,
        30,
        0.25
    );
    scene->addItem(bullet16);
}

void yellowExtraBeamFireFunc(
    QGraphicsScene* scene,
    QPointF startPosition,
    int baseDamage
) {
    QPointF bullet1Position = startPosition;
    bullet1Position.rx() += 10;
    bullet1Position.ry() -= 20;
    BulletModel* bullet1 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet1Position,
        baseDamage * 2,
        def::up,
        def::defaultBulletSpeed,
        1.2
    );
    scene->addItem(bullet1);

    QPointF bullet2Position = startPosition;
    bullet2Position.rx() -= 10;
    bullet2Position.ry() -= 20;
    BulletModel* bullet2 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet2Position,
        baseDamage * 2,
        def::up,
        def::defaultBulletSpeed,
        1.2
    );
    scene->addItem(bullet2);

    QPointF bullet3Position = startPosition;
    bullet3Position.rx() += 15;
    bullet3Position.ry() -= 15;
    BulletModel* bullet3 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet3Position,
        baseDamage * 1.8,
        def::up + 5,
        def::defaultBulletSpeed
    );
    scene->addItem(bullet3);

    QPointF bullet4Position = startPosition;
    bullet4Position.rx() -= 15;
    bullet4Position.ry() -= 15;
    BulletModel* bullet4 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet4Position,
        baseDamage * 1.8,
        def::up - 5,
        def::defaultBulletSpeed
    );
    scene->addItem(bullet4);

    QPointF bullet5Position = startPosition;
    bullet5Position.rx() += 30;
    bullet5Position.ry() -= 5;
    BulletModel* bullet5 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet5Position,
        baseDamage * 1.5,
        def::up + 10,
        def::defaultBulletSpeed,
        0.8
    );
    scene->addItem(bullet5);

    QPointF bullet6Position = startPosition;
    bullet6Position.rx() -= 30;
    bullet6Position.ry() -= 5;
    BulletModel* bullet6 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet6Position,
        baseDamage * 1.5,
        def::up - 10,
        def::defaultBulletSpeed,
        0.8
    );
    scene->addItem(bullet6);

    QPointF bullet7Position = startPosition;
    bullet7Position.rx() += 35;
    BulletModel* bullet7 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet7Position,
        baseDamage * 1.2,
        def::up + 15,
        def::defaultBulletSpeed,
        0.6
    );
    scene->addItem(bullet7);

    QPointF bullet8Position = startPosition;
    bullet8Position.rx() -= 35;
    BulletModel* bullet8 = new BulletModel(
        "bullet_yellow",
        game_object_type::player_bullet,
        bullet8Position,
        baseDamage * 1.2,
        def::up - 15,
        def::defaultBulletSpeed,
        0.6
    );
    scene->addItem(bullet8);
}

void blueExtraBeamFireFunc(
    QGraphicsScene* scene,
    QPointF startPosition,
    int baseDamage
) {
    QPointF bullet1Position = startPosition;
    bullet1Position.rx() -= 15;
    bullet1Position.ry() -= 15;
    BulletModel* bullet1 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet1Position,
        baseDamage * 4,
        def::up - 45,
        def::defaultBulletSpeed - 10,
        2
    );
    scene->addItem(bullet1);

    QPointF bullet2Position = startPosition;
    bullet2Position.rx() += 15;
    bullet2Position.ry() -= 15;
    BulletModel* bullet2 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet2Position,
        baseDamage * 4,
        def::up + 45,
        def::defaultBulletSpeed - 10,
        2
    );
    scene->addItem(bullet2);

    QPointF bullet3Position = startPosition;
    bullet3Position.rx() -= 15;
    bullet3Position.ry() += 15;
    BulletModel* bullet3 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet3Position,
        baseDamage * 4,
        def::down + 45,
        def::defaultBulletSpeed - 10,
        2
    );
    scene->addItem(bullet3);

    QPointF bullet4Position = startPosition;
    bullet4Position.rx() += 15;
    bullet4Position.ry() += 15;
    BulletModel* bullet4 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet4Position,
        baseDamage * 4,
        def::down - 45,
        def::defaultBulletSpeed - 10,
        2
    );
    scene->addItem(bullet4);

    QPointF bullet5Position = startPosition;
    bullet5Position.rx() -= 10;
    bullet5Position.ry() -= 10;
    BulletModel* bullet5 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet5Position,
        baseDamage * 3,
        def::up - 35,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet5);

    QPointF bullet6Position = startPosition;
    bullet6Position.rx() -= 20;
    bullet6Position.ry() -= 20;
    BulletModel* bullet6 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet6Position,
        baseDamage * 3,
        def::up - 55,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet6);

    QPointF bullet7Position = startPosition;
    bullet7Position.rx() += 10;
    bullet7Position.ry() -= 10;
    BulletModel* bullet7 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet7Position,
        baseDamage * 3,
        def::up + 35,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet7);

    QPointF bullet8Position = startPosition;
    bullet8Position.rx() += 20;
    bullet8Position.ry() -= 20;
    BulletModel* bullet8 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet8Position,
        baseDamage * 3,
        def::up + 55,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet8);

    QPointF bullet9Position = startPosition;
    bullet9Position.rx() -= 10;
    bullet9Position.ry() += 10;
    BulletModel* bullet9 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet9Position,
        baseDamage * 3,
        def::down + 35,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet9);

    QPointF bullet10Position = startPosition;
    bullet10Position.rx() -= 20;
    bullet10Position.ry() += 20;
    BulletModel* bullet10 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet10Position,
        baseDamage * 3,
        def::down + 55,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet10);

    QPointF bullet11Position = startPosition;
    bullet11Position.rx() += 10;
    bullet11Position.ry() += 10;
    BulletModel* bullet11 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet11Position,
        baseDamage * 3,
        def::down - 35,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet11);

    QPointF bullet12Position = startPosition;
    bullet12Position.rx() += 20;
    bullet12Position.ry() += 20;
    BulletModel* bullet12 = new BulletModel(
        "bullet_blue",
        game_object_type::player_bullet,
        bullet12Position,
        baseDamage * 3,
        def::down - 55,
        def::defaultBulletSpeed - 10,
        1.5
    );
    scene->addItem(bullet12);
}

fire extraBeamAttack[def::maxWeaponTypes] {
    &redExtraBeamFireFunc,
    &yellowExtraBeamFireFunc,
    &blueExtraBeamFireFunc
};

