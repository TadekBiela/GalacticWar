#include "menucontroller.hpp"

MenuController::MenuController(GeneralView* view,
                               MenuModel*   model)
{

}

void MenuController::startGame()
{
    emit activateEnemySpawning();
    emit activatePlayer();
}

void MenuController::gameOver()
{

}

void MenuController::save(PlayerScore newPlayerScore)
{

}

void MenuController::updateHighScore(PlayerScoreMapIterator highScoreIterator)
{

}
