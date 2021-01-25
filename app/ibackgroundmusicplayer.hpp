
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


#ifndef IBACKGROUNDMUSICPLAYER_HPP
#define IBACKGROUNDMUSICPLAYER_HPP

#include <QObject>

struct Settings;

class IBackgroundMusicPlayer : public QObject
{
    Q_OBJECT
public:
    IBackgroundMusicPlayer() {}
    virtual ~IBackgroundMusicPlayer() {}

public slots:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void switchToMenuMusic() = 0;
    virtual void switchToGameMusic() = 0;
    virtual void applyNewSettings(Settings) = 0;
};

#endif //IBACKGROUNDMUSICPLAYER_HPP
