#ifndef SOUNDSTORAGE_HPP
#define SOUNDSTORAGE_HPP

#include <QString>
#include <QSoundEffect>
#include <QHash>

class SoundStorage
{
public:
    SoundStorage();
    virtual ~SoundStorage();
    QSoundEffect* getSound(QString name);

protected:
    QHash<QString, QSoundEffect*> m_soundStorage;
};

extern SoundStorage* g_soundStorage;

#endif // SOUNDSTORAGE_HPP
