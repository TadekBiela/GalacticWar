#ifndef SOUNDEFFECTMODEL_HPP
#define SOUNDEFFECTMODEL_HPP

#include "soundstorage.hpp"
#include <QObject>
#include <QSoundEffect>
#include <QTimer>

class SoundEffectModel : public QObject
{
    Q_OBJECT
public:
    SoundEffectModel(QString soundName);
    virtual ~SoundEffectModel();

public slots:
    void destroy();

protected:
    QSoundEffect* m_sound;
};

#endif // SOUNDEFFECTMODEL_HPP
