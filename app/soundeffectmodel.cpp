#include "soundeffectmodel.hpp"

SoundEffectModel::SoundEffectModel(QMediaPlayer* player)
{
    m_player = player;
    m_player->setVolume(50);
    connect(&m_destroyTimer, SIGNAL(timeout()), this, SLOT(destroy()));
    m_destroyTimer.setInterval(static_cast<int>(m_player->duration()));
    m_remainingDestroyTime = m_destroyTimer.interval();
    m_player->play();
    m_destroyTimer.start();
}

SoundEffectModel::~SoundEffectModel()
{

}

void SoundEffectModel::start()
{

}

void SoundEffectModel::stop()
{

}

void SoundEffectModel::destroy()
{
    delete this;
}
