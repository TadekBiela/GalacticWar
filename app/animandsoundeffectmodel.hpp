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
    AnimAndSoundEffectModel(bool    isAnim    = false,
                            QString animPath  = "",
                            QPointF animPos   = QPointF(0,0),
                            bool    isSound   = false,
                            QString soundPath = "");
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
    int          m_animationFrameIdx;
    QTimer       m_animationTimer;
    QMediaPlayer m_sound;
    QTimer       m_destroyTimer;
};

#endif // ANIMANDSOUNDEFFECTMODEL_HPP