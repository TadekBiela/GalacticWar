#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodel.hpp"
#include "../app/animationeffectmodel.hpp"
#include "../app/bulletmodel.hpp"
#include "../app/playermodel.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QGraphicsScene>
#include <QSignalSpy>

class EnemyModelTest : public EnemyModel
{
public:
    EnemyModelTest(int     level,
                   QPointF position,
                   int     health,
                   int     damage,
                   int     moveTimeDelay,
                   int     fireTimeDelay)
                    : EnemyModel(level,
                                 position,
                                 health,
                                 damage,
                                 moveTimeDelay,
                                 fireTimeDelay)
    {
        //Simple graphic needed to tests
        QPixmap map(QSize(def::animationFrameWight, def::animationFrameHeight));
        map.fill(Qt::red);
        setPixmap(map);
    }
    virtual ~EnemyModelTest() {}

    int           getLevel()             const { return m_level; }
    QPointF       getPosition()          const { return pos(); }
    int           getHealth()            const { return m_health; }
    int           getDamage()            const { return m_damage; }
    int           getDirection()         const { return m_direction; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getFireTimer()         const { return m_fireTimer; }
    const QTimer& getMoveTimer()         const { return m_moveTimer; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }

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
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(EnemyModelTestsClass, EnemyModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    int           resultLevel             = enemyModel.getLevel();
    QPointF       resultPosition          = enemyModel.getPosition();
    int           resultHealth            = enemyModel.getHealth();
    int           resultDamage            = enemyModel.getDamage();
    int           resultDirection         = enemyModel.getDirection();
    int           resultAnimationFrameIdx = enemyModel.getAnimationFrameIdx();
    const QTimer& resultMoveTimer         = enemyModel.getMoveTimer();
    const QTimer& resultFireTimer         = enemyModel.getFireTimer();
    const QTimer& resultAnimTimer         = enemyModel.getAnimationTimer();

    EXPECT_EQ(resultLevel,                        1);
    EXPECT_EQ(resultHealth,                      30);
    EXPECT_EQ(resultDamage,                      15);
    EXPECT_EQ(resultDirection,                    0);
    EXPECT_EQ(resultAnimationFrameIdx,            0);
    EXPECT_EQ(resultMoveTimer.isActive(),       false);
    EXPECT_EQ(resultFireTimer.isActive(),       false);
    EXPECT_EQ(resultAnimTimer.isActive(),       false);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(),  20);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  10);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(), 100);
    EXPECT_FLOAT_EQ(resultPosition.x(),         -28);
    EXPECT_FLOAT_EQ(resultPosition.y(),         -23);
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithPlayerBulletEnemyShouldHitButNotDestroy_IsEqual)
{
    QGraphicsScene* scene  = new QGraphicsScene;
    BulletModel*    bullet = new BulletModel(bullet_type::playerDefaultBullet, QPointF(100, 100), 50, 5, 50);
    EnemyModelTest* enemy  = new EnemyModelTest(1, QPointF(100, 100), 300, 15, 20, 10);
    QSignalSpy      signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(bullet);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth          = enemy->getHealth();
    int resultSignalCount     = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(resultHealth,          250);
    EXPECT_EQ(resultSignalCount,       0);
    EXPECT_EQ(startNumOfSceneItems,    2);
    EXPECT_EQ(resultNumOfSceneItems,   1);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithPlayerBulletEnemyShouldHitCreateAnimationAndDestroy_IsEqual)
{
    QGraphicsScene* scene  = new QGraphicsScene;
    BulletModel*    bullet = new BulletModel(bullet_type::playerDefaultBullet, QPointF(100, 100), 50, 5, 50);
    EnemyModelTest* enemy  = new EnemyModelTest(1, QPointF(100, 100), 30, 15, 20, 10);
    QSignalSpy      signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(bullet);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int  resultHealth          = enemy->getHealth();
    int  resultSignalCount     = signalDestroy.count();
    auto resultSignal          = signalDestroy.takeFirst();
    int  resultNumOfSceneItems = scene->items().size();
    auto resultAnimEffect      = scene->items().at(0);

    EXPECT_EQ(resultHealth,                  0);
    EXPECT_EQ(resultSignalCount,             1);
    EXPECT_EQ(resultSignal.at(0).toPointF(), QPointF(100, 100));
    EXPECT_EQ(resultSignal.at(1).toInt(),    1);
    EXPECT_EQ(startNumOfSceneItems,          2);
    EXPECT_EQ(resultNumOfSceneItems,         1);
    EXPECT_EQ(typeid(*resultAnimEffect),     typeid(AnimationEffectModel));
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithPlayerBulletsEnemyShouldHitCreateAnimationDestroyAndHaveOneMoreCollision_IsEqual)
{
    QGraphicsScene* scene   = new QGraphicsScene;
    BulletModel*    bullet1 = new BulletModel(bullet_type::playerDefaultBullet, QPointF(100, 100), 100, 5, 50);
    BulletModel*    bullet2 = new BulletModel(bullet_type::playerDefaultBullet, QPointF(100, 100), 100, 5, 50);
    BulletModel*    bullet3 = new BulletModel(bullet_type::playerDefaultBullet, QPointF(100, 100), 100, 5, 50);
    EnemyModelTest* enemy   = new EnemyModelTest(1, QPointF(100, 100), 200, 15, 20, 10);
    QSignalSpy      signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(bullet1);
    scene->addItem(bullet2);
    scene->addItem(bullet3);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int  resultSignalCount     = signalDestroy.count();
    auto resultSignal          = signalDestroy.takeFirst();
    int  resultNumOfSceneItems = scene->items().size();
    auto resultAnimEffect      = scene->items().at(0);

    EXPECT_EQ(resultSignalCount,             1);
    EXPECT_EQ(resultSignal.at(0).toPointF(), QPointF(100, 100));
    EXPECT_EQ(resultSignal.at(1).toInt(),    1);
    EXPECT_EQ(startNumOfSceneItems,          4);
    EXPECT_EQ(resultNumOfSceneItems,         1);
    EXPECT_EQ(typeid(*resultAnimEffect),     typeid(AnimationEffectModel));
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithEnemyBulletEnemyDoNothing_IsEqual)
{
    QGraphicsScene* scene  = new QGraphicsScene;
    BulletModel*    bullet = new BulletModel(bullet_type::enemyBullet, QPointF(100, 100), 50, 5, 50);
    EnemyModelTest* enemy  = new EnemyModelTest(1, QPointF(100, 100), 300, 15, 20, 10);
    QSignalSpy      signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(bullet);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth          = enemy->getHealth();
    int resultSignalCount     = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(resultHealth,          300);
    EXPECT_EQ(resultSignalCount,       0);
    EXPECT_EQ(startNumOfSceneItems,    2);
    EXPECT_EQ(resultNumOfSceneItems,   2);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithCoinRewardEnemyDoNothing_IsEqual)
{
    QGraphicsScene*  scene = new QGraphicsScene;
    RewardCoinModel* coin  = new RewardCoinModel(coin_type::bronze);
    EnemyModelTest*  enemy = new EnemyModelTest(1, QPointF(100, 100), 300, 15, 20, 10);
    QSignalSpy       signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(coin);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth          = enemy->getHealth();
    int resultSignalCount     = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(resultHealth,          300);
    EXPECT_EQ(resultSignalCount,       0);
    EXPECT_EQ(startNumOfSceneItems,    2);
    EXPECT_EQ(resultNumOfSceneItems,   2);
    delete scene;
}

TEST_F(EnemyModelTestsClass, CheckCollisions_CollisionWithSpecialRewardEnemyDoNothing_IsEqual)
{
    QGraphicsScene*     scene   = new QGraphicsScene;
    RewardSpecialModel* special = new RewardSpecialModel(special_type::health);
    EnemyModelTest*     enemy   = new EnemyModelTest(1, QPointF(100, 100), 300, 15, 20, 10);
    QSignalSpy          signalDestroy(enemy, &EnemyModelTest::destroyed);
    scene->addItem(special);
    scene->addItem(enemy);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemy->checkCollisions();
    int resultHealth          = enemy->getHealth();
    int resultSignalCount     = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(resultHealth,          300);
    EXPECT_EQ(resultSignalCount,       0);
    EXPECT_EQ(startNumOfSceneItems,    2);
    EXPECT_EQ(resultNumOfSceneItems,   2);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsLessThanHealth_IsEqual)
{
    QGraphicsScene* scene      = new QGraphicsScene;
    EnemyModelTest* enemyModel = new EnemyModelTest(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy      signalDestroy(enemyModel, &EnemyModelTest::destroyed);
    scene->addItem(enemyModel);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel->hit(13);
    int resultHealth          = enemyModel->getHealth();
    int resultSignalCount     = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(resultHealth,          17);
    EXPECT_EQ(resultSignalCount,      0);
    EXPECT_EQ(startNumOfSceneItems,   1);
    EXPECT_EQ(resultNumOfSceneItems,  1);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsEqualThanHealth_IsEqual)
{
    QGraphicsScene* scene      = new QGraphicsScene;
    EnemyModelTest* enemyModel = new EnemyModelTest(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy      signalDestroy(enemyModel, &EnemyModelTest::destroyed);
    scene->addItem(enemyModel);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel->hit(30);
    int  resultHealth          = enemyModel->getHealth();
    int  resultSignalCount     = signalDestroy.count();
    auto resultSignal          = signalDestroy.takeFirst();
    int  resultNumOfSceneItems = scene->items().size();
    auto resultAnimEffect      = scene->items().at(0);

    EXPECT_EQ(resultHealth,                  0);
    EXPECT_EQ(resultSignalCount,             1);
    EXPECT_EQ(resultSignal.at(0).toPointF(), QPointF(2, 7));
    EXPECT_EQ(resultSignal.at(1).toInt(),    1);
    EXPECT_EQ(startNumOfSceneItems,          1);
    EXPECT_EQ(resultNumOfSceneItems,         1);
    EXPECT_EQ(typeid(*resultAnimEffect),     typeid(AnimationEffectModel));
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsMoreThanHealth_IsEqual)
{
    QGraphicsScene* scene      = new QGraphicsScene;
    EnemyModelTest* enemyModel = new EnemyModelTest(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy      signalDestroy(enemyModel, &EnemyModelTest::destroyed);
    scene->addItem(enemyModel);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel->hit(43);
    int  resultHealth          = enemyModel->getHealth();
    int  resultSignalCount     = signalDestroy.count();
    auto resultSignal          = signalDestroy.takeFirst();
    int  resultNumOfSceneItems = scene->items().size();
    auto resultAnimEffect      = scene->items().at(0);

    EXPECT_EQ(resultHealth,                  0);
    EXPECT_EQ(resultSignalCount,             1);
    EXPECT_EQ(resultSignal.at(0).toPointF(), QPointF(2, 7));
    EXPECT_EQ(resultSignal.at(1).toInt(),    1);
    EXPECT_EQ(startNumOfSceneItems,          1);
    EXPECT_EQ(resultNumOfSceneItems,         1);
    EXPECT_EQ(typeid(*resultAnimEffect),     typeid(AnimationEffectModel));
    delete scene;
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsZeroThanHealth_IsEqual)
{
    QGraphicsScene* scene      = new QGraphicsScene;
    EnemyModelTest* enemyModel = new EnemyModelTest(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy      signalDestroy(enemyModel, &EnemyModelTest::destroyed);
    scene->addItem(enemyModel);
    int startNumOfSceneItems = scene->items().size();
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel->hit(0);
    int resultHealth          = enemyModel->getHealth();
    int resultSignalCount     = signalDestroy.count();
    int resultNumOfSceneItems = scene->items().size();

    EXPECT_EQ(resultHealth,          30);
    EXPECT_EQ(resultSignalCount,      0);
    EXPECT_EQ(startNumOfSceneItems,   1);
    EXPECT_EQ(resultNumOfSceneItems,  1);
    delete scene;
}

TEST_F(EnemyModelTestsClass, Start_CheckIfAllTimersWillBeActive_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);

    enemyModel.start();
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();

    EXPECT_EQ(resultFireTimer.isActive(), true);
    EXPECT_EQ(resultMoveTimer.isActive(), true);
    EXPECT_EQ(resultAnimTimer.isActive(), true);
}

TEST_F(EnemyModelTestsClass, Stop_CheckIfAllTimersWillBeNotActive_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);

    enemyModel.stop();
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();

    EXPECT_EQ(resultFireTimer.isActive(), false);
    EXPECT_EQ(resultMoveTimer.isActive(), false);
    EXPECT_EQ(resultAnimTimer.isActive(), false);
}

TEST_F(EnemyModelTestsClass, Animation_CheckIfAnimationFrameIdxWasIncreasedBy1_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);

    enemyModel.animation();
    int resultAnimationFrameIdx = enemyModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimationFrameIdx, 1);
}

TEST_F(EnemyModelTestsClass, Animation_AnimationFrameIdxPointsToLastFrameCheckIfResetTo0_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);

    enemyModel.animation();
    enemyModel.animation();
    enemyModel.animation();
    int resultAnimationFrameIdx = enemyModel.getAnimationFrameIdx();
    enemyModel.animation();
    enemyModel.animation();
    int resultAnimationFrameIdxReset = enemyModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimationFrameIdx,      3);
    EXPECT_EQ(resultAnimationFrameIdxReset, 0);
}
