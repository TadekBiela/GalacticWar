#ifndef BACKGROUNDMUSICPLAYER_HPP
#define BACKGROUNDMUSICPLAYER_HPP

#include "ibackgroundmusicplayer.hpp"
#include "settings.hpp"
#include <QMediaPlayer>
#include <QMediaPlaylist>

class BackgroundMusicPlayer : public IBackgroundMusicPlayer
{
    Q_OBJECT
public:
    BackgroundMusicPlayer();
    virtual ~BackgroundMusicPlayer();

public slots:
    void play();
    void pause();
    void switchToMenuMusic();
    void switchToGameMusic();
    void applyNewSettings(Settings newSettings);

protected:
    QMediaPlayer m_mediaPlayer;
    QMediaPlaylist m_menuPlaylist;
    QMediaPlaylist m_gamePlaylist;
};

#endif //BACKGROUNDMUSICPLAYER_HPP
