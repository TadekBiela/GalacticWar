#ifndef SOUNDSTORAGESTUB_HPP
#define SOUNDSTORAGESTUB_HPP

#include "../../app/isoundstorage.hpp"
#include "../../app/settings.hpp"

class SoundStorageStub : public ISoundStorage
{
public:
    SoundStorageStub() {}
    virtual ~SoundStorageStub() {}
    virtual QSoundEffect* getSound(QString name)
    {
        return &dummySound;
    }
public slots:
    void applyNewSettings(Settings newSettings) {}

private:
    QSoundEffect dummySound;
};

#endif // SOUNDSTORAGESTUB_HPP
