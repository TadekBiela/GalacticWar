#include "firefunctions.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"

void defaultFireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    BulletModel* bullet = new BulletModel("bullet_default",
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
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 10);
    bulletPosition2.setY(startPosition.y() + 20);
    BulletModel* bullet2 = new BulletModel("bullet_red",
                                           bulletPosition2,
                                           baseDamage / 4,
                                           def::up + 5,
                                           30,
                                           0.25);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 10);
    bulletPosition3.setY(startPosition.y() + 20);
    BulletModel* bullet3 = new BulletModel("bullet_red",
                                           bulletPosition3,
                                           baseDamage / 4,
                                           def::up - 5,
                                           30,
                                           0.25);
    scene->addItem(bullet3);
}

void redLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    QPointF bulletPosition = startPosition;
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 10);
    bulletPosition2.setY(startPosition.y() + 20);
    BulletModel* bullet2 = new BulletModel("bullet_red",
                                           bulletPosition2,
                                           baseDamage / 3,
                                           def::up + 4,
                                           30,
                                           0.35);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 10);
    bulletPosition3.setY(startPosition.y() + 20);
    BulletModel* bullet3 = new BulletModel("bullet_red",
                                           bulletPosition3,
                                           baseDamage / 3,
                                           def::up - 4,
                                           30,
                                           0.35);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() + 14);
    bulletPosition4.setY(startPosition.y() + 24);
    BulletModel* bullet4 = new BulletModel("bullet_red",
                                           bulletPosition4,
                                           baseDamage / 4,
                                           def::up + 8,
                                           30,
                                           0.25);
    scene->addItem(bullet4);

    QPointF bulletPosition5 = startPosition;
    bulletPosition5.setX(startPosition.x() - 14);
    bulletPosition5.setY(startPosition.y() + 24);
    BulletModel* bullet5 = new BulletModel("bullet_red",
                                           bulletPosition5,
                                           baseDamage / 4,
                                           def::up - 8,
                                           30,
                                           0.25);
    scene->addItem(bullet5);
}

void redLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    QPointF bulletPosition = startPosition;
    bulletPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_red",
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          30);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() + 10);
    bulletPosition2.setY(startPosition.y() + 20);
    BulletModel* bullet2 = new BulletModel("bullet_red",
                                           bulletPosition2,
                                           baseDamage / 2,
                                           def::up + 5,
                                           30,
                                           0.5);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 10);
    bulletPosition3.setY(startPosition.y() + 20);
    BulletModel* bullet3 = new BulletModel("bullet_red",
                                           bulletPosition3,
                                           baseDamage / 2,
                                           def::up - 5,
                                           30,
                                           0.5);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() + 14);
    bulletPosition4.setY(startPosition.y() + 24);
    BulletModel* bullet4 = new BulletModel("bullet_red",
                                           bulletPosition4,
                                           baseDamage / 3,
                                           def::up + 10,
                                           30,
                                           0.35);
    scene->addItem(bullet4);

    QPointF bulletPosition5 = startPosition;
    bulletPosition5.setX(startPosition.x() - 14);
    bulletPosition5.setY(startPosition.y() + 24);
    BulletModel* bullet5 = new BulletModel("bullet_red",
                                           bulletPosition5,
                                           baseDamage / 3,
                                           def::up - 10,
                                           30,
                                           0.35);
    scene->addItem(bullet5);

    QPointF bulletPosition6 = startPosition;
    bulletPosition6.setX(startPosition.x() + 14);
    bulletPosition6.setY(startPosition.y() + 24);
    BulletModel* bullet6 = new BulletModel("bullet_red",
                                           bulletPosition6,
                                           baseDamage / 4,
                                           def::up + 15,
                                           30,
                                           0.25);
    scene->addItem(bullet6);

    QPointF bulletPosition7 = startPosition;
    bulletPosition7.setX(startPosition.x() - 14);
    bulletPosition7.setY(startPosition.y() + 24);
    BulletModel* bullet7 = new BulletModel("bullet_red",
                                           bulletPosition7,
                                           baseDamage / 4,
                                           def::up - 15,
                                           30,
                                           0.25);
    scene->addItem(bullet7);
}

void yellowLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void blueLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    static int fireLeft = 1;
    startPosition.setX(startPosition.x() - 12 * fireLeft);
    startPosition.setY(startPosition.y() + 20);
    BulletModel* bullet = new BulletModel("bullet_blue",
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
                                           bulletPosition2,
                                           baseDamage / 2,
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
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 25);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           bulletPosition2,
                                           baseDamage / 2,
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
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 25);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           bulletPosition2,
                                           baseDamage / 2,
                                           def::up - 30 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 25 * fireLeft);
    bulletPosition3.setY(startPosition.y() + 30);
    BulletModel* bullet3 = new BulletModel("bullet_blue",
                                           bulletPosition3,
                                           baseDamage / 3,
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
                                          bulletPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);

    QPointF bulletPosition2 = startPosition;
    bulletPosition2.setX(startPosition.x() - 20 * fireLeft);
    bulletPosition2.setY(startPosition.y() + 25);
    BulletModel* bullet2 = new BulletModel("bullet_blue",
                                           bulletPosition2,
                                           baseDamage / 2,
                                           def::up - 45 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet2);

    QPointF bulletPosition3 = startPosition;
    bulletPosition3.setX(startPosition.x() - 25 * fireLeft);
    bulletPosition3.setY(startPosition.y() + 30);
    BulletModel* bullet3 = new BulletModel("bullet_blue",
                                           bulletPosition3,
                                           baseDamage / 3,
                                           def::up - 75 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet3);

    QPointF bulletPosition4 = startPosition;
    bulletPosition4.setX(startPosition.x() - 25 * fireLeft);
    bulletPosition4.setY(startPosition.y() + 45);
    BulletModel* bullet4 = new BulletModel("bullet_blue",
                                           bulletPosition4,
                                           baseDamage / 4,
                                           def::up + 90 * fireLeft,
                                           def::defaultBulletSpeed);
    scene->addItem(bullet4);
    fireLeft *= -1;
}
