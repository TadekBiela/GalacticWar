#include "menucontroller.hpp"

MenuController::MenuController(GeneralView* view,
                               MenuModel*   model)
{
    connect(view,  SIGNAL(save(PlayerScore)),
            model, SLOT(addRecordToHighScore(PlayerScore)));
    connect(model, SIGNAL(updateHighScore(PlayerScoreMapIterator, int)),
            view,  SLOT(updateHighScoreList(PlayerScoreMapIterator, int)));
    connect(this,  SIGNAL(playerDefeated(int)),
            view,  SLOT(gameOver(int)));
    connect(view,  SIGNAL(startGame()),
            this,  SLOT(startGame()));
    connect(view,  SIGNAL(pause()),
            this,  SLOT(stopGame()));
}

MenuController::~MenuController()
{

}

void MenuController::startGame()
{
    emit activateEnemySpawning();
}

void MenuController::stopGame()
{
    emit deactivateEnemySpawning();
}

void MenuController::updateScore(int score)
{
    emit playerDefeated(score);
}

void MenuController::gameOver()
{
    emit deactivateEnemySpawning();
    emit getScore();
}
