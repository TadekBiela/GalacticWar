#ifndef SOUNDEFFECTMODEL_HPP
#define SOUNDEFFECTMODEL_HPP

#include "soundstorage.hpp"
#include <QObject>
#include <QSoundEffect>

class SoundEffectModel : public QObject
{
    Q_OBJECT
public:
    SoundEffectModel(QString soundName);
    virtual ~SoundEffectModel();

signals:
    void end();

public slots:
    void destroy();

protected:
    QSoundEffect* m_sound;
};

#endif // SOUNDEFFECTMODEL_HPP
