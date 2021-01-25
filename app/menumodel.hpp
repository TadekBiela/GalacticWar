
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


#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "ifilemanager.hpp"
#include "settings.hpp"
#include <QVector>
#include <QPair>

typedef QPair<QString, int> PlayerScore;
typedef QVector<PlayerScore> PlayerScoreTable;
typedef QVector<PlayerScore>::iterator PlayerScoreIterator;

class MenuModel
{
public:
    MenuModel(IFileManager* fileManager = nullptr);
    ~MenuModel();
    void addRecordToHighscore(PlayerScore newPlayerScore);
    void saveHighscoreToFile();
    void loadHighscoreFromFile();
    PlayerScoreIterator getHighscoreBeginIterator();
    PlayerScoreIterator getHighscoreEndIterator();
    int getHighscoreSize() const;
    void setSettings(Settings newSettings);
    Settings getSettings() const;
    void saveSettingsToFile() const;
    void loadSettingsFromFile();

protected:
    PlayerScoreTable m_highscore;
    IFileManager* m_fileManager;
    Settings m_settings;
};

#endif // MENUMODEL_HPP
