#ifndef SOUNDSTORAGE_HPP
#define SOUNDSTORAGE_HPP

#include "isoundstorage.hpp"
#include <QString>
#include <QSoundEffect>
#include <QHash>

class SoundStorage : public ISoundStorage
{
public:
    SoundStorage();
    virtual ~SoundStorage();
    virtual QSoundEffect* getSound(QString name);

protected:
    QHash<QString, QSoundEffect*> m_soundStorage;
};

#endif // SOUNDSTORAGE_HPP
