#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/enemymodel.hpp"
#include "../app/bulletmodel.hpp"
#include "../app/playermodel.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QGraphicsScene>
#include <QSignalSpy>

class EnemyModelTest : public EnemyModel
{
public:
    EnemyModelTest(int level,
                   int health,
                   int damage,
                   int moveTimeDelay,
                   int fireTimeDelay)
    : EnemyModel(level,
                 health,
                 damage,
                 moveTimeDelay,
                 fireTimeDelay)
    {
        //Simple graphic needed to tests
        QPixmap map(QSize(def::animationFrameWidth, def::animationFrameHeight));
        map.fill(Qt::red);
        setPixmap(map);
        setPos(QPointF(100, 100));
    }
    virtual ~EnemyModelTest() {}
    void animation() { EnemyModel::animation(); }
    void checkCollisions() { EnemyModel::checkCollisions(); }
    void hit(int points) { EnemyModel::hit(points); }

    int getLevel() const { return m_level; }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
    int getDirection() const { return m_direction; }
    int getAnimationFrameXIdx() const { return m_animationFrameXIdx; }
    const QTimer& getFireTimer() const { return m_fireTimer; }
    const QTimer& getMoveTimer() const { return m_moveTimer; }
    const QTimer& getAnimationTimer() const { return m_animationTimer; }
    void setImage(QImage* image) { m_image = image; }

public slots: //dummy implementation - slots not tested in this class
    void fire(){}
    void move(){}
};

class EnemyModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
        m_displayWidget = new QWidget;
        g_animationPlaneView = new AnimationPlaneView(m_displayWidget);
    }
    void TearDown()
    {
        delete g_animationPlaneView;
        delete m_displayWidget;
        delete g_imageStorage;
        delete g_soundStorage;
    }

private:
    QWidget* m_displayWidget;
};

TEST_F(EnemyModelTestsClass, EnemyModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    EnemyModelTest enemy(1, 30, 15, 20, 10);
    int resultLevel = enemy.getLevel();
    int resultHealth = enemy.getHealth();
    int resultDamage = enemy.getDamage();
    int resultDirection = enemy.getDirection();
    int resultAnimationFrameXIdx = enemy.getAnimationFrameXIdx();
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    const QTimer& resultFireTimer = enemy.getFireTimer();
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();

    EXPECT_EQ(1, resultLevel);
    EXPECT_EQ(30, resultHealth);
    EXPECT_EQ(15, resultDamage);
    EXPECT_EQ(0, resultDirection);
    EXPECT_EQ(0, resultAnimationFrameXIdx);
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(20, resultMoveTimer.interval());
    EXPECT_FLOAT_EQ(10, resultFireTimer.interval());
    EXPECT_FLOAT_EQ(100, resultAnimTimer.interval());
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithPlayerBulletEnemyShouldHitButNotDestroy_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               300,
                                               15,
                                               20,
                                               10);
    BulletModel* bullet = new BulletModel("bullet_default",
                                          game_object_type::player_bullet,
                                          enemy->pos(),
                                          50,
                                          5,
                                          50);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(enemy);
    scene->addItem(bullet);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(250, resultHealth);
    EXPECT_EQ(0, resultSignalCount);
    EXPECT_EQ(2, startNumOfSceneItems);
    EXPECT_EQ(1, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithPlayerBulletEnemyShouldHitAndDestroy_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               30,
                                               15,
                                               20,
                                               10);
    BulletModel* bullet = new BulletModel("bullet_default",
                                          game_object_type::player_bullet,
                                          enemy->pos(),
                                          50,
                                          5,
                                          50);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(enemy);
    scene->addItem(bullet);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);
    QPointF expectedEnemyDestroyedPosition(enemy->getCenterPosition());

    enemy->checkCollisions();
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    auto resultSignal = signalDestroy.takeFirst();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(0, resultHealth);
    EXPECT_EQ(1, resultSignalCount);
    EXPECT_EQ(expectedEnemyDestroyedPosition.x(), resultSignal.at(0).toPointF().x());
    EXPECT_EQ(expectedEnemyDestroyedPosition.y(), resultSignal.at(0).toPointF().y());
    EXPECT_EQ(1, resultSignal.at(1).toInt());
    EXPECT_EQ(2, startNumOfSceneItems);
    EXPECT_EQ(0, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithPlayerBulletsEnemyShouldHitDestroyAndHaveOneMoreCollision_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               200,
                                               15,
                                               20,
                                               10);
    BulletModel* bullet1 = new BulletModel("bullet_default",
                                           game_object_type::player_bullet,
                                           enemy->pos(),
                                           100,
                                           5,
                                           50);
    BulletModel* bullet2 = new BulletModel("bullet_default",
                                           game_object_type::player_bullet,
                                           enemy->pos(),
                                           100,
                                           5,
                                           50);
    BulletModel* bullet3 = new BulletModel("bullet_default",
                                           game_object_type::player_bullet,
                                           enemy->pos(),
                                           100,
                                           5,
                                           50);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(bullet1);
    scene->addItem(bullet2);
    scene->addItem(bullet3);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);
    QPointF expectedEnemyDestroyedPosition(enemy->getCenterPosition());

    enemy->checkCollisions();
    int resultSignalCount = signalDestroy.count();
    auto resultSignal = signalDestroy.takeFirst();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(1, resultSignalCount);
    EXPECT_EQ(expectedEnemyDestroyedPosition.x(), resultSignal.at(0).toPointF().x());
    EXPECT_EQ(expectedEnemyDestroyedPosition.y(), resultSignal.at(0).toPointF().y());
    EXPECT_EQ(1, resultSignal.at(1).toInt());
    EXPECT_EQ(4, startNumOfSceneItems);
    EXPECT_EQ(0, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithEnemyBulletEnemyDoNothing_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               300,
                                               15,
                                               20,
                                               10);
    BulletModel* bullet = new BulletModel("bullet_enemy",
                                          game_object_type::enemy_bullet,
                                          enemy->pos(),
                                          50,
                                          5,
                                          50);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(bullet);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(300, resultHealth);
    EXPECT_EQ(0, resultSignalCount);
    EXPECT_EQ(2, startNumOfSceneItems);
    EXPECT_EQ(2, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithCoinRewardEnemyDoNothing_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               300,
                                               15,
                                               20,
                                               10);
    RewardCoinModel* coin = new RewardCoinModel(coin_type::bronze);
    coin->setPos(enemy->pos());
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(coin);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(300, resultHealth);
    EXPECT_EQ(0, resultSignalCount);
    EXPECT_EQ(2, startNumOfSceneItems);
    EXPECT_EQ(2, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithSpecialRewardEnemyDoNothing_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               300,
                                               15,
                                               20,
                                               10);
    RewardSpecialModel* special = new RewardSpecialModel(special_type::health);
    special->setPos(enemy->pos());
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(special);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(300, resultHealth);
    EXPECT_EQ(0, resultSignalCount);
    EXPECT_EQ(2, startNumOfSceneItems);
    EXPECT_EQ(2, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsLessThanHealth_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               30,
                                               15,
                                               20,
                                               10);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->hit(13);
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(17, resultHealth);
    EXPECT_EQ(0, resultSignalCount);
    EXPECT_EQ(1, startNumOfSceneItems);
    EXPECT_EQ(1, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsEqualThanHealth_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               30,
                                               15,
                                               20,
                                               10);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);
    QPointF expectedEnemyDestroyedPosition(enemy->getCenterPosition());

    enemy->hit(30);
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    auto resultSignal = signalDestroy.takeFirst();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(0, resultHealth);
    EXPECT_EQ(1, resultSignalCount);
    EXPECT_EQ(expectedEnemyDestroyedPosition.x(), resultSignal.at(0).toPointF().x());
    EXPECT_EQ(expectedEnemyDestroyedPosition.y(), resultSignal.at(0).toPointF().y());
    EXPECT_EQ(1, resultSignal.at(1).toInt());
    EXPECT_EQ(1, startNumOfSceneItems);
    EXPECT_EQ(0, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsMoreThanHealth_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               30,
                                               15,
                                               20,
                                               10);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);
    QPointF expectedEnemyDestroyedPosition(enemy->getCenterPosition());

    enemy->hit(43);
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    auto resultSignal = signalDestroy.takeFirst();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(0, resultHealth);
    EXPECT_EQ(1, resultSignalCount);
    EXPECT_EQ(expectedEnemyDestroyedPosition.x(), resultSignal.at(0).toPointF().x());
    EXPECT_EQ(expectedEnemyDestroyedPosition.y(), resultSignal.at(0).toPointF().y());
    EXPECT_EQ(1, resultSignal.at(1).toInt());
    EXPECT_EQ(1, startNumOfSceneItems);
    EXPECT_EQ(0, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsZeroThanHealth_IsEqual)
{
    QGraphicsScene* scene = new QGraphicsScene;
    EnemyModelTest* enemy = new EnemyModelTest(1,
                                               30,
                                               15,
                                               20,
                                               10);
    QSignalSpy signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->hit(0);
    int resultHealth = enemy->getHealth();
    int resultSignalCount = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(30, resultHealth);
    EXPECT_EQ(0, resultSignalCount);
    EXPECT_EQ(1, startNumOfSceneItems);
    EXPECT_EQ(1, resultNumOfSceneItems);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Start_CheckIfAllTimersWillBeActive_IsEqual)
{
    EnemyModelTest enemy(1,
                         30,
                         15,
                         20,
                         10);

    enemy.start();
    const QTimer& resultFireTimer = enemy.getFireTimer();
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();

    EXPECT_TRUE(resultFireTimer.isActive());
    EXPECT_TRUE(resultMoveTimer.isActive());
    EXPECT_TRUE(resultAnimTimer.isActive());
}

TEST_F(EnemyModelTestsClass, Stop_CheckIfAllTimersWillBeNotActive_IsEqual)
{
    EnemyModelTest enemy(1,
                         30,
                         15,
                         20,
                         10);

    enemy.stop();
    const QTimer& resultFireTimer = enemy.getFireTimer();
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();

    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FALSE(resultAnimTimer.isActive());
}

TEST_F(EnemyModelTestsClass, Animation_CheckIfAnimationFrameXIdxWasIncreasedBy1_IsEqual)
{
    QImage dumpImage;
    EnemyModelTest enemy(1,
                         30,
                         15,
                         20,
                         10);
    enemy.setImage(&dumpImage);

    enemy.animation();
    int resultAnimationFrameXIdx = enemy.getAnimationFrameXIdx();

    EXPECT_EQ(1, resultAnimationFrameXIdx);
}

TEST_F(EnemyModelTestsClass, Animation_AnimationFrameXIdxPointsToLastFrameCheckIfResetTo0_IsEqual)
{
    QImage dumpImage;
    EnemyModelTest enemy(1,
                         30,
                         15,
                         20,
                         10);
    enemy.setImage(&dumpImage);

    enemy.animation();
    enemy.animation();
    enemy.animation();
    int resultAnimationFrameXIdx = enemy.getAnimationFrameXIdx();
    enemy.animation();
    enemy.animation();
    enemy.animation();
    enemy.animation();
    enemy.animation();
    enemy.animation();
    enemy.animation();
    int resultAnimationFrameXIdxReset = enemy.getAnimationFrameXIdx();

    EXPECT_EQ(3, resultAnimationFrameXIdx);
    EXPECT_EQ(0, resultAnimationFrameXIdxReset);
}
