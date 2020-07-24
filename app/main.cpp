#include "animationplaneview.hpp"
#include "backgroundcontroller.hpp"
#include "controlplane.hpp"
#include "enemycontroller.hpp"
#include "filemanager.hpp"
#include "gameplayview.hpp"
#include "healthcontroller.hpp"
#include "imagestorage.hpp"
#include "levelcontroller.hpp"
#include "menucontroller.hpp"
#include "playercontroller.hpp"
#include "rewardcontroller.hpp"
#include "scorecontroller.hpp"
#include "soundstorage.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow mainWindow;
    g_imageStorage       = new ImageStorage;
    g_soundStorage       = new SoundStorage;
    g_animationPlaneView = new AnimationPlaneView(&mainWindow);

    QFontDatabase::addApplicationFont(a.applicationDirPath() + "/fonts/joystix monospace.ttf");
    a.setFont(QFont("joystix monospace"));

    //Controller
    ControlPlane controller(&mainWindow);

    //View
    GameplayView gameplayView(&mainWindow);

    //Controllers
    EnemyController  enemyController(&gameplayView);
    HealthController healthController(&mainWindow);
    LevelController  levelController(&mainWindow);
    MenuController   menuController(&mainWindow,
                                    &controller,
                                    &gameplayView,
                                    g_animationPlaneView);
    PlayerController playerController(&controller,
                                      &gameplayView);
    RewardController rewardController(&gameplayView);
    ScoreController  scoreController(&mainWindow);
    BackgroundView   backgroundController(&mainWindow);

    //Controller connections
    QObject::connect(&enemyController,  SIGNAL(enemyDestroyed(QPointF, int)),
                     &rewardController, SLOT(spawnRewards(QPointF, int)));
    QObject::connect(&levelController,  SIGNAL(changeEnemyConfiguration(EnemyConfiguration)),
                     &enemyController,  SLOT(changeEnemyConfiguration(EnemyConfiguration)));
    QObject::connect(&menuController,   SIGNAL(resetLevel()),
                     &levelController,  SLOT(resetLevel()));
    QObject::connect(&menuController,   SIGNAL(resetScore()),
                     &scoreController,  SLOT(resetScore()));
    QObject::connect(&menuController,   SIGNAL(createNewPlayer()),
                     &playerController, SLOT(createNewPlayer()));
    QObject::connect(&menuController,   SIGNAL(activateEnemySpawning()),
                     &enemyController,  SLOT(startSpawning()));
    QObject::connect(&menuController,   SIGNAL(deactivateEnemySpawning()),
                     &enemyController,  SLOT(stopSpawning()));
    QObject::connect(&menuController,   SIGNAL(getScore()),
                     &scoreController,  SLOT(getScore()));
    QObject::connect(&menuController,   SIGNAL(abortPlayer()),
                     &playerController, SLOT(abortPlayer()));
    QObject::connect(&playerController, SIGNAL(playerDefeated()),
                     &menuController,   SLOT(gameOver()));
    QObject::connect(&rewardController, SIGNAL(rewardCoinCollected(coin_type)),
                     &scoreController,  SLOT(addScorePoints(coin_type)));
    QObject::connect(&rewardController, SIGNAL(rewardSpecialCollected(special_type)),
                     &playerController, SLOT(changePlayerAtribute(special_type)));
    QObject::connect(&scoreController,  SIGNAL(maxScorePerLevelAchieved()),
                     &levelController,  SLOT(nextLevel()));
    QObject::connect(&scoreController,  SIGNAL(updateScore(int)),
                     &menuController,   SLOT(updateScore(int)));

    mainWindow.show();
	return a.exec();
}

