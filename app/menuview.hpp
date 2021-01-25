
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


#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <QButtonGroup>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QSlider>
#include <QString>
#include <QTableWidget>
#include <QWidget>
#include "label.hpp"
#include "menumodel.hpp"
#include "pushbutton.hpp"
#include "settings.hpp"

class MenuView : public QObject
{
    Q_OBJECT
public:
    explicit MenuView(QWidget* displayWidget);
    virtual ~MenuView();
    void    updateHighscore(PlayerScoreIterator highscoreBegin,
                            PlayerScoreIterator highscoreEnd);
    QString getPlayerNameFromField();
    int     getScoreFromLabel();
    void setPlayerNameField(QString);
    void    setGameoverScoreLabel(int scoreValue);
    void setSettingsView(Settings settings);

signals:
    void startClicked();
    void continueClicked();
    void cancelClicked();
    void quitClicked();
    void saveClicked();
    void saveSettingsClicked(Settings newSettings);

public slots:
    void hideAllMenu();
    void showMainMenu();
    void showHighscoreMenu();
    void showSettingsMenu();
    void showPauseMenu();
    void showPauseSettingsMenu();
    void showGameoverMenu();
    void startGame();
    void continueGame();
    void cancelGame();
    void quitGame();
    void saveScore();
    void saveSettingsInMenu();
    void saveSettingsOnPause();

protected:
    //Main
    Label        m_mainTitleLabel;
    PushButton   m_mainStartButton;
    PushButton   m_mainHighscoreButton;
    PushButton m_mainSettingsButton;
    PushButton   m_mainQuitButton;
    //Highscore
    Label        m_highscoreTitleLabel;
    QTableWidget m_highscoreTable;
    PushButton   m_highscoreBackToMenu;
    //Settings
    Label m_settingsTitleLabel;
    QLabel m_settingsMusicLabel;
    QCheckBox m_settingsMusicCheckBox;
    QSlider m_settingsMusicSlider;
    QLabel m_settingsSoundsLabel;
    QCheckBox m_settingsSoundsCheckBox;
    QSlider m_settingsSoundsSlider;
    QLabel m_settingsControlLabel;
    QButtonGroup m_settingsControlButtonGroup;
    QCheckBox m_settingsControlMouseCheckBox;
    QCheckBox m_settingsControlKeyboardCheckBox;
    PushButton m_settingsSaveButton;
    PushButton m_settingsBackToMenuButton;
    PushButton m_settingsPauseSaveButton;
    PushButton m_settingsPauseBackToMenuButton;
    //Pause
    Label        m_pauseTitleLabel;
    PushButton   m_pauseCancelButton;
    PushButton   m_pauseContinueButton;
    PushButton m_pauseSettingsButton;
    //Gameover
    Label        m_gameoverTitleLabel;
    Label        m_gameoverScoreLabel;
    QLineEdit    m_gameoverPlayerNameField;
    PushButton   m_gameoverSaveScoreButton;
    PushButton   m_gameoverBackToMenuButton;
    //Author
    Label        m_authorLabel;

private:
    void setupHighscoreTableStyle();
    void saveSettings();
};

#endif // MENUVIEW_HPP
