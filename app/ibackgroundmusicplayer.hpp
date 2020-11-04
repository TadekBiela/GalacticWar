#ifndef IBACKGROUNDMUSICPLAYER_HPP
#define IBACKGROUNDMUSICPLAYER_HPP

#include <QObject>

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
};

#endif //IBACKGROUNDMUSICPLAYER_HPP
