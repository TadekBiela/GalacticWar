#ifndef SOUNDEFFECTMODEL_HPP
#define SOUNDEFFECTMODEL_HPP

#include "gameobject.hpp"
#include <QMediaPlayer>
#include <QTimer>

class SoundEffectModel : public GameObject
{
    Q_OBJECT
public:
    SoundEffectModel(QMediaPlayer* player);
    virtual ~SoundEffectModel();

public slots:
    void start();
    void stop();
    void destroy();

protected:
    QMediaPlayer* m_player;
    QTimer        m_destroyTimer;
    int           m_remainingDestroyTime;
};

#endif // SOUNDEFFECTMODEL_HPP
