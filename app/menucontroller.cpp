#include "menucontroller.hpp"

MenuController::MenuController(GeneralView* view,
                               MenuModel*   model)
                                : m_isGamePaused(false)
{
    connect(view,  SIGNAL(save(PlayerScore)),
            model, SLOT(addRecordToHighScore(PlayerScore)));
    connect(model, SIGNAL(updateHighScore(PlayerScoreMapIterator, int)),
            view,  SLOT(updateHighScoreList(PlayerScoreMapIterator, int)));
    connect(this,  SIGNAL(playerDefeated(int)),
            view,  SLOT(gameOver(int)));
    connect(view,  SIGNAL(startGame()),
            this,  SLOT(startGame()));
    connect(view,  SIGNAL(escPressed()),
            this,  SLOT(escPressed()));
    connect(this,  SIGNAL(pauseGame()),
            view,  SLOT(pauseGame()));
    connect(this,  SIGNAL(continueGame()),
            view,  SLOT(continueGame()));
}

MenuController::~MenuController()
{

}

void MenuController::startGame()
{
    emit resetLevel();
    emit resetScore();
    emit createNewPlayer();
    emit activateEnemySpawning();
}

void MenuController::escPressed()
{
    if(m_isGamePaused == false)
    {
        emit deactivateEnemySpawning();
        emit pauseGame();
        m_isGamePaused = true;
    }
    else
    {
        emit activateEnemySpawning();
        emit continueGame();
        m_isGamePaused = false;
    }
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
