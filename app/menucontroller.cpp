
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


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
    IBackgroundMusicPlayer* backgroundMusicPlayer,
    ISoundStorage* soundStorage,
    IFileManager* fileManager
) :
    m_model(fileManager),
    m_view(displayWidget)
{
    connect(&m_view, SIGNAL(startClicked()),
            this,    SLOT(startGame()));
    connect(&m_view, SIGNAL(continueClicked()),
            this,    SLOT(continueGame()));
    connect(&m_view, SIGNAL(cancelClicked()),
            this,    SLOT(cancelGame()));
    connect(&m_view, SIGNAL(quitClicked()),
            this,    SLOT(exitGame()));
    connect(&m_view, SIGNAL(saveClicked()),
            this,    SLOT(saveScore()));
    connect(&m_view, SIGNAL(saveSettingsClicked(Settings)),
            this,    SLOT(saveSettings(Settings)));

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
    connect(this,       SIGNAL(settingsChanged(Settings)),
            controller, SLOT(applyNewSettings(Settings)));

    connect(this,         SIGNAL(gamePaused()),
            gameplayView, SLOT(deactivate()));
    connect(this,         SIGNAL(gameContinued()),
            gameplayView, SLOT(activate()));
    connect(this,         SIGNAL(gameCanceled()),
            gameplayView, SLOT(removeAllGameObjects()));

    connect(this,          SIGNAL(gamePaused()),
            animationView, SLOT(deactivate()));
    connect(this,          SIGNAL(gameContinued()),
            animationView, SLOT(activate()));
    connect(this,          SIGNAL(gameCanceled()),
            animationView, SLOT(activate()));

    connect(
        this, SIGNAL(gameStarted()),
        backgroundMusicPlayer, SLOT(switchToGameMusic())
    );
    connect(
        this, SIGNAL(gamePaused()),
        backgroundMusicPlayer, SLOT(pause())
    );
    connect(
        this, SIGNAL(gameContinued()),
        backgroundMusicPlayer, SLOT(play())
    );
    connect(
        this, SIGNAL(gameCanceled()),
        backgroundMusicPlayer, SLOT(switchToMenuMusic())
    );
    connect(
        this, SIGNAL(gameOver()),
        backgroundMusicPlayer, SLOT(switchToMenuMusic())
    );
    connect(
        this, SIGNAL(settingsChanged(Settings)),
        backgroundMusicPlayer, SLOT(applyNewSettings(Settings))
    );

    connect(
        this, SIGNAL(settingsChanged(Settings)),
        soundStorage, SLOT(applyNewSettings(Settings))
    );

    m_model.loadHighscoreFromFile();
    m_model.loadSettingsFromFile();

    m_view.updateHighscore(m_model.getHighscoreBeginIterator(),
                           m_model.getHighscoreEndIterator());
    m_view.setSettingsView(m_model.getSettings());

    emit settingsChanged(m_model.getSettings());
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

void MenuController::cancelGame()
{
    emit gameCanceled();
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
}

void MenuController::saveSettings(Settings newSettings) {
    m_model.setSettings(newSettings);
    m_model.saveSettingsToFile();

    emit settingsChanged(m_model.getSettings());
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
