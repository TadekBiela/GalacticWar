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

