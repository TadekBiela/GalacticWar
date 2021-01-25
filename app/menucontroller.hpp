
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


#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "animationplaneview.hpp"
#include "controlplane.hpp"
#include "menumodel.hpp"
#include "menuview.hpp"
#include "gameplayview.hpp"
#include "ibackgroundmusicplayer.hpp"
#include "isoundstorage.hpp"
#include "settings.hpp"
#include <QObject>

class MenuController : public QObject
{
    Q_OBJECT
public:
    MenuController(
        QWidget* displayWidget,
        ControlPlane* controller,
        GameplayView* gameplayView,
        AnimationPlaneView* animationView,
        IBackgroundMusicPlayer* backgroundMusicPlayer,
        ISoundStorage* soundStorage,
        IFileManager* fileManager = nullptr
    );
    virtual ~MenuController();

signals:
    void gameStarted();
    void gamePaused();
    void gameContinued();
    void gameCanceled();
    void gameOver();
    void gameExit();
    void settingsChanged(Settings newSettings);

public slots:
    void startGame();
    void pauseGame();
    void continueGame();
    void cancelGame();
    void updateScore(int totalScore);
    void saveScore();
    void saveSettings(Settings newSettings);
    void endGame();
    void exitGame();

protected:
    MenuModel m_model;
    MenuView m_view;
};

#endif // MENUCONTROLLER_HPP
