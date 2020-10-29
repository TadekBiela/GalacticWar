#include "menucontroller.hpp"
#include "animationeffectmodel.hpp"
#include "animationplaneview.hpp"
#include "definitions.hpp"
#include "soundeffectmodel.hpp"
#include <QMainWindow>

MenuController::MenuController(
    QWidget* displayWidget,
    ControlPlane* controller,
    GameplayView* gameplayView,
    AnimationPlaneView* animationView,
    IFileManager* fileManager
) :
    m_model(fileManager),
    m_view(displayWidget)
{
    connect(&m_view, SIGNAL(startClicked()),
            this,    SLOT(startGame()));
    connect(&m_view, SIGNAL(continueClicked()),
            this,    SLOT(continueGame()));
    connect(&m_view, SIGNAL(abortClicked()),
            this,    SLOT(abortGame()));
    connect(&m_view, SIGNAL(quitClicked()),
            this,    SLOT(exitGame()));
    connect(&m_view, SIGNAL(saveClicked()),
            this,    SLOT(saveScore()));

    connect(controller, SIGNAL(mouseLeaveWindow()),
            this,       SLOT(pauseGame()));
    connect(controller, SIGNAL(escKeyPressed()),
            this,       SLOT(pauseGame()));
    connect(this,       SIGNAL(gameStarted()),
            controller, SLOT(activate()));
    connect(this,       SIGNAL(gamePaused()),
            controller, SLOT(deactivate()));
    connect(this,       SIGNAL(gameContinued()),
            controller, SLOT(activate()));
    connect(this,       SIGNAL(gameOver()),
            controller, SLOT(deactivate()));

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
    m_view.updateHighscore(m_model.getHighscoreBeginIterator(),
                           m_model.getHighscoreEndIterator());
}

MenuController::~MenuController()
{

}

void MenuController::startGame()
{
    emit gameStarted();
    m_view.hideAllMenu();
}

void MenuController::pauseGame()
{
    emit gamePaused();
    m_view.showPauseMenu();
}

void MenuController::continueGame()
{
    emit gameContinued();
    m_view.hideAllMenu();
}

void MenuController::abortGame()
{
    emit gameAborted();
    m_view.showMainMenu();
}

void MenuController::updateScore(int totalScore)
{
    m_view.setGameoverScoreLabel(totalScore);
}

void MenuController::saveScore()
{
    QString playerName = m_view.getPlayerNameFromField();
    if(not playerName.isEmpty()) {
        int totalScore = m_view.getScoreFromLabel();
        PlayerScore scoreRecordToSave(
            playerName,
            totalScore);
        m_model.addRecordToHighscore(
            scoreRecordToSave
        );

        m_model.saveHighscoreToFile();

        m_view.updateHighscore(
            m_model.getHighscoreBeginIterator(),
            m_model.getHighscoreEndIterator()
        );
    }

    m_view.showMainMenu();
}

void MenuController::endGame()
{
    SoundEffectModel* gameOverSound = new SoundEffectModel("game_over");
    gameOverSound->play();
    emit gameOver();
    m_view.showGameoverMenu();
}

void MenuController::exitGame()
{
    delete g_soundStorage;
    delete g_imageStorage;
    delete g_animationPlaneView;

    emit gameExit();
}
