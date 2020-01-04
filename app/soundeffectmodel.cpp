#include "soundeffectmodel.hpp"

SoundEffectModel::SoundEffectModel(QString soundName)
{
    QSoundEffect* sound = g_soundStorage->getSound(soundName);
    m_sound = sound;
    m_sound->setVolume(50);
    connect(m_sound, SIGNAL(playingChanged()), this, SLOT(destroy()));
    m_sound->play();
}

SoundEffectModel::~SoundEffectModel()
{

}

void SoundEffectModel::destroy()
{
    if(m_sound->isPlaying() == false)
    {
        emit end();
        delete this;
    }
}
