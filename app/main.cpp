#include "enemycontroller.hpp"
#include "filemanager.hpp"
#include "generalview.hpp"
#include "levelcontroller.hpp"
#include "levelmodel.hpp"
#include "menucontroller.hpp"
#include "menumodel.hpp"
#include "playercontroller.hpp"
#include "randomgenerator.hpp"
#include "rewardcontroller.hpp"
#include "scorecontroller.hpp"
#include "scoremodel.hpp"
#include "soundstorage.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_soundStorage = new SoundStorage;

    FileManager     fileManager;
    RandomGenerator randomGenerator;

    //Model
    LevelModel levelModel;
    MenuModel  menuModel(&fileManager);
    ScoreModel scoreModel;

    //View
    GeneralView generalView;

    //Controller
    EnemyController  enemyController(&generalView, &randomGenerator);
    LevelController  levelController(&levelModel, &generalView);
    MenuController   menuController(&generalView, &menuModel);
    PlayerController playerController(&generalView);
    RewardController rewardController(&generalView, &randomGenerator);
    ScoreController  scoreController(&scoreModel, &generalView, &randomGenerator);

    //Connections MVC
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

    generalView.show();
	return a.exec();
}

