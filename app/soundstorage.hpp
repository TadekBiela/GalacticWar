#ifndef SOUNDSTORAGE_HPP
#define SOUNDSTORAGE_HPP

#include "isoundstorage.hpp"
#include "settings.hpp"
#include <QString>
#include <QSoundEffect>
#include <QHash>

class SoundStorage : public ISoundStorage
{
    Q_OBJECT
public:
    SoundStorage();
    virtual ~SoundStorage();
    virtual QSoundEffect* getSound(QString name);

public slots:
    void applyNewSettings(Settings newSettings);

protected:
    QHash<QString, QSoundEffect*> m_soundStorage;
};

#endif // SOUNDSTORAGE_HPP
