#include "menucontroller.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "soundeffectmodel.hpp"

MenuController::MenuController(GeneralView* view,
                               MenuModel*   model)
                                : m_isGameStarted(false),
                                  m_isGamePaused(false),
                                  m_view(view)
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
    m_isGameStarted = false;
    m_isGamePaused  = false;

    emit resetLevel();
    emit resetScore();
    emit createNewPlayer();

    QPointF position(def::halfSceneWight,
                     def::halfSceneHeight - def::halfSceneHeight / 4);
    AnimationEffectModel* gameOverAnim = new AnimationEffectModel(m_view->getScene(),
                                                                  "start_game",
                                                                  position,
                                                                  def::animationBigFrameWight,
                                                                  def::animationBigFrameHeight,
                                                                  40);
    SoundEffectModel* startGame = new SoundEffectModel("start_game");
    connect(startGame, SIGNAL(end()), this, SLOT(startSpawningEnemies()));
}

void MenuController::startSpawningEnemies()
{
    m_isGameStarted = true;
    emit activateEnemySpawning();
}

void MenuController::showScore()
{
    emit getScore();
}

void MenuController::escPressed()
{
    if(m_isGameStarted == true)
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
}

void MenuController::updateScore(int score)
{
    emit playerDefeated(score);
}

void MenuController::gameOver()
{
    emit deactivateEnemySpawning();

    QPointF position(def::halfSceneWight,
                     def::halfSceneHeight - def::halfSceneHeight / 4);
    AnimationEffectModel* gameOverAnim = new AnimationEffectModel(m_view->getScene(),
                                                                  "game_over",
                                                                  position,
                                                                  def::animationBigFrameWight,
                                                                  def::animationBigFrameHeight,
                                                                  20);
    SoundEffectModel* gameOver = new SoundEffectModel("game_over");
    connect(gameOver, SIGNAL(end()), this, SLOT(showScore()));
}
