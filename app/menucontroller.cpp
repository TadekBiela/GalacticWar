#include "menucontroller.hpp"

MenuController::MenuController(GeneralView* view,
                               MenuModel*   model)
{
    connect(view,  SIGNAL(save(PlayerScore)),
            model, SLOT(addRecordToHighScore(PlayerScore)));
    connect(model, SIGNAL(updateHighScore(PlayerScoreMapIterator, int)),
            view,  SLOT(updateHighScoreList(PlayerScoreMapIterator, int)));
}

void MenuController::startGame()
{
    emit activateEnemySpawning();
    emit activatePlayer();
}

void MenuController::stopGame()
{
    emit deactivateEnemySpawning();
    emit deactivatePlayer();
}

void MenuController::gameOver()
{

}
