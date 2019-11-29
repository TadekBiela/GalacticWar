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
    void animationSetup(QString animationName, QPointF position);
    void soundSetup(QString soundName);

public slots:
    void start();
    void stop();
    void animation();
    void destroy();

protected:
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
