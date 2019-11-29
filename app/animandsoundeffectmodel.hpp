#ifndef ANIMANDSOUNDEFFECTMODEL_HPP
#define ANIMANDSOUNDEFFECTMODEL_HPP

#include "gameobject.hpp"
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>

class AnimAndSoundEffectModel : public GameObject
{
    Q_OBJECT
public:
    AnimAndSoundEffectModel();
    virtual ~AnimAndSoundEffectModel();
    QPixmap getAnimationFrame();

public slots:
    void start();
    void stop();
    void animation();
    void destroy();

protected:
    void animSetup(QString animPath, QPointF animPos);
    void soundSetup(QString soundPath);

    QImage       m_image;
    bool         m_isAnimEnabled;
    int          m_animationFrameIdx;
    QTimer       m_animationTimer;
    bool         m_isSoundEnabled;
    QMediaPlayer m_sound;
    QTimer       m_destroyTimer;
    int          m_remainigDestroyTime;
};

#endif // ANIMANDSOUNDEFFECTMODEL_HPP
