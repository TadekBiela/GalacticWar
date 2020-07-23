#include "menucontroller.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "soundeffectmodel.hpp"

MenuController::MenuController(QWidget*            displayWidget,
                               ControlPlane*       controller,
                               GameplayView*       gameplayView,
                               AnimationPlaneView* animationView)
                                : m_isGameStarted(false),
                                  m_isGamePaused(false),
                                  m_model(),
                                  m_view(displayWidget)
{
    connect(&m_view, SIGNAL(startClicked()),
            this,   SLOT(startGame()));
    connect(&m_view, SIGNAL(continueClicked()),
            this,   SLOT(continueGame()));
    connect(&m_view, SIGNAL(abortClicked()),
            this,   SLOT(abortGame()));
    connect(&m_view, SIGNAL(quitClicked()),
            this,   SLOT(exitGame()));

    connect(controller, SIGNAL(mouseLeaveWindow()),
            this,       SLOT(pauseGame()));
    connect(controller, SIGNAL(escKeyPressed()),
            this,       SLOT(pauseGame()));

    connect(this,         SIGNAL(gamePaused()),
            gameplayView, SLOT(deactivate()));
    connect(this,         SIGNAL(gameContinued()),
            gameplayView, SLOT(activate()));
    connect(this,         SIGNAL(gameAborted()),
            gameplayView, SLOT(removeAllGameObjects()));

    connect(this,          SIGNAL(gamePaused()),
            animationView, SLOT(deactivate()));
    connect(this,          SIGNAL(gameContinued()),
            animationView, SLOT(activate()));
    connect(this,          SIGNAL(gameAborted()),
            animationView, SLOT(activate()));

    m_model.loadHighscoreFromFile();
}

MenuController::~MenuController()
{

}

void MenuController::startGame()
{
    m_isGameStarted = true;
    emit gameStarted();
}

void MenuController::pauseGame()
{
    if(m_isGameStarted && (not m_isGamePaused))
    {
        m_isGamePaused = true;
        emit gamePaused();
    }
}

void MenuController::continueGame()
{
    m_isGamePaused = false;
    emit gameContinued();
}

void MenuController::abortGame()
{
    m_isGameStarted = false;
    m_isGamePaused  = false;
    emit gameAborted();
}

void MenuController::updateScore(int totalScore)
{
    m_view.setGameoverScoreLabel(totalScore);
}

void MenuController::saveScore()
{
    QString     playerName = m_view.getPlayerNameFromField();
    int         totalScore = m_view.getScoreFromLabel();
    PlayerScore scoreRecordToSave(playerName, totalScore);

    m_model.addRecordToHighscore(scoreRecordToSave);
    m_model.saveHighscoreToFile();

    m_view.updateHighscore(m_model.getHighscoreBeginIterator(),
                           m_model.getHighscoreEndIterator());
}

void MenuController::endGame()
{
    QPointF position(def::halfSceneWight,
                     def::halfSceneHeight - def::halfSceneHeight / 4);
    AnimationEffectModel* gameOverAnim = new AnimationEffectModel("game_over",
                                                                  position,
                                                                  def::animationBigFrameWight,
                                                                  def::animationBigFrameHeight,
                                                                  20);
    gameOverAnim->play();
    SoundEffectModel* gameOverSound = new SoundEffectModel("game_over");
    connect(gameOverSound, SIGNAL(end()), this, SLOT(showScore()));
    gameOverSound->play();
    m_isGameStarted = false;
    emit gameOver();
}

void MenuController::exitGame()
{
    delete g_soundStorage;
    delete g_imageStorage;
}
