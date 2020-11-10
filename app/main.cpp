#include "animationplaneview.hpp"
#include "backgroundcontroller.hpp"
#include "backgroundmusicplayer.hpp"
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
    QFontDatabase::addApplicationFont(a.applicationDirPath() + "/fonts/joystix monospace.ttf");
    a.setFont(QFont("joystix monospace"));

    //Main window setup
    QMainWindow mainWindow;
    mainWindow.setFixedSize(QSize(def::windowWight, def::windowHeight));
    mainWindow.show();

    //Media storages setup
    g_imageStorage = new ImageStorage;
    g_soundStorage = new SoundStorage;

    //Create view layer in correct order
    //Background layer
    BackgroundController backgroundController(&mainWindow);

    //Gameplay layer
    GameplayView gameplayView(&mainWindow);

    //Animation layer
    g_animationPlaneView = new AnimationPlaneView(&mainWindow);

    //Controller layer
    ControlPlane controller(&mainWindow);

    //Background music
    BackgroundMusicPlayer backgroundMusicPlayer;

    //HUD interface layer
    HealthController healthController(&mainWindow,
                                      &controller);
    LevelController  levelController(&mainWindow,
                                     &controller);
    ScoreController  scoreController(&mainWindow,
                                     &controller);

    //Rest of controllers
    EnemyController  enemyController(&gameplayView);
    MenuController menuController(
        &mainWindow,
        &controller,
        &gameplayView,
        g_animationPlaneView,
        &backgroundMusicPlayer,
        g_soundStorage
    );
    PlayerController playerController(&controller,
                                      &gameplayView);
    RewardController rewardController(&gameplayView);

    //Controller connections
    QObject::connect(&menuController,       SIGNAL(gameStarted()),  //Game started
                     &healthController,     SLOT(create()));
    QObject::connect(&menuController,       SIGNAL(gameStarted()),
                     &levelController,      SLOT(create()));
    QObject::connect(&menuController,       SIGNAL(gameStarted()),
                     &scoreController,      SLOT(create()));
    QObject::connect(&menuController,       SIGNAL(gameStarted()),
                     &playerController,     SLOT(create()));
    QObject::connect(&menuController,       SIGNAL(gameStarted()),
                     &enemyController,      SLOT(startSpawning()));
    QObject::connect(&menuController,       SIGNAL(gameStarted()),
                     &backgroundController, SLOT(increaseBackgroundSpeed()));
    QObject::connect(&menuController,       SIGNAL(gamePaused()),   //Game paused
                     &healthController,     SLOT(hide()));
    QObject::connect(&menuController,       SIGNAL(gamePaused()),
                     &levelController,      SLOT(hide()));
    QObject::connect(&menuController,       SIGNAL(gamePaused()),
                     &scoreController,      SLOT(hide()));
    QObject::connect(&menuController,       SIGNAL(gamePaused()),
                     &enemyController,      SLOT(stopSpawning()));
    QObject::connect(&menuController,       SIGNAL(gamePaused()),
                     &backgroundController, SLOT(deactivate()));
    QObject::connect(&menuController,       SIGNAL(gameContinued()), //Game continued
                     &healthController,     SLOT(show()));
    QObject::connect(&menuController,       SIGNAL(gameContinued()),
                     &levelController,      SLOT(show()));
    QObject::connect(&menuController,       SIGNAL(gameContinued()),
                     &scoreController,      SLOT(show()));
    QObject::connect(&menuController,       SIGNAL(gameContinued()),
                     &enemyController,      SLOT(startSpawning()));
    QObject::connect(&menuController,       SIGNAL(gameContinued()),
                     &backgroundController, SLOT(activate()));
    QObject::connect(&menuController,       SIGNAL(gameCanceled()),  //Game canceled
                     &healthController,     SLOT(destroy()));
    QObject::connect(&menuController,       SIGNAL(gameCanceled()),
                     &levelController,      SLOT(destroy()));
    QObject::connect(&menuController,       SIGNAL(gameCanceled()),
                     &scoreController,      SLOT(destroy()));
    QObject::connect(&menuController,       SIGNAL(gameCanceled()),
                     &enemyController,      SLOT(stopSpawning()));
    QObject::connect(&menuController,       SIGNAL(gameCanceled()),
                     &backgroundController, SLOT(resetToDefault()));
    QObject::connect(&menuController,       SIGNAL(gameOver()),     //Game over
                     &healthController,     SLOT(destroy()));
    QObject::connect(&menuController,       SIGNAL(gameOver()),
                     &levelController,      SLOT(destroy()));
    QObject::connect(&menuController,       SIGNAL(gameOver()),
                     &scoreController,      SLOT(emitTotalScoreAndDestroy()));
    QObject::connect(&menuController,       SIGNAL(gameOver()),
                     &enemyController,      SLOT(stopSpawning()));
    QObject::connect(&menuController,       SIGNAL(gameOver()),
                     &playerController,     SLOT(destroy()));
    QObject::connect(&menuController,       SIGNAL(gameOver()),
                     &backgroundController, SLOT(decreaseBackgroundSpeed()));
    QObject::connect(&scoreController,      SIGNAL(totalScore(int)),                //Total score
                     &menuController,       SLOT(updateScore(int)));
    QObject::connect(&enemyController,      SIGNAL(enemyDestroyed(QPointF, int)),   //Spawn rewards
                     &rewardController,     SLOT(spawnRewards(QPointF, int)));
    QObject::connect(&rewardController,     SIGNAL(rewardCoinCollected(coin_type)), //Collect rewards
                     &scoreController,      SLOT(addScorePointsBasedOnCoinType(coin_type)));
    QObject::connect(&rewardController,     SIGNAL(rewardSpecialCollected(special_type)),
                     &playerController,     SLOT(changePlayerAtribute(special_type)));
    QObject::connect(&scoreController,      SIGNAL(maxScorePerLevelAchieved()),     //Next level
                     &levelController,      SLOT(nextLevel()));
    QObject::connect(&levelController,      SIGNAL(changeEnemyConfig(EnemyConfiguration)),
                     &enemyController,      SLOT(changeEnemyConfig(EnemyConfiguration)));
    QObject::connect(&playerController,     SIGNAL(addHealthPoints(int)),           //Health points
                     &healthController,     SLOT(addHealthPoints(int)));
    QObject::connect(&playerController,     SIGNAL(subtractHealthPoints(int)),
                     &healthController,     SLOT(subtractHealthPoints(int)));
    QObject::connect(&healthController,     SIGNAL(noHealth()),
                     &menuController,       SLOT(endGame()));
    QObject::connect(&menuController,       SIGNAL(gameExit()),                     //Exit game
                     &mainWindow,           SLOT(close()));

    mainWindow.resize(QSize(def::windowWight, def::windowHeight));
	return a.exec();
}

