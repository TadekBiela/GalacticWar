
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


#include "backgroundmusicplayer.hpp"
#include <QApplication>
#include <QString>
#include <QUrl>

BackgroundMusicPlayer::BackgroundMusicPlayer() {
    QString baseMediaPath = QCoreApplication::applicationDirPath() + QString("/music/");

    m_menuPlaylist.addMedia(QUrl::fromLocalFile(baseMediaPath + QString("menu1.wav")));
    m_menuPlaylist.setPlaybackMode(QMediaPlaylist::Loop);

    m_gamePlaylist.addMedia(QUrl::fromLocalFile(baseMediaPath + QString("game1.wav")));
    m_gamePlaylist.addMedia(QUrl::fromLocalFile(baseMediaPath + QString("game2.wav")));
    m_gamePlaylist.addMedia(QUrl::fromLocalFile(baseMediaPath + QString("game3.wav")));
    m_gamePlaylist.setPlaybackMode(QMediaPlaylist::Loop);

    m_mediaPlayer.setPlaylist(&m_menuPlaylist);
    this->play();
}

BackgroundMusicPlayer::~BackgroundMusicPlayer() {

}

void BackgroundMusicPlayer::applyNewSettings(Settings newSettings) {
    m_mediaPlayer.setMuted(!newSettings.musicEnabled);
    m_mediaPlayer.setVolume(newSettings.musicVolume);
}

void BackgroundMusicPlayer::play() {
    m_mediaPlayer.play();
}

void BackgroundMusicPlayer::pause() {
    m_mediaPlayer.pause();
}

void BackgroundMusicPlayer::switchToMenuMusic() {
    m_mediaPlayer.setPlaylist(&m_menuPlaylist);
    this->play();
}

void BackgroundMusicPlayer::switchToGameMusic() {
    m_mediaPlayer.setPlaylist(&m_gamePlaylist);
    this->play();
}

