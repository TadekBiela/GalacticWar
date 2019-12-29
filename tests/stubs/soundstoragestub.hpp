#ifndef SOUNDSTORAGESTUB_HPP
#define SOUNDSTORAGESTUB_HPP

#include "../../app/isoundstorage.hpp"

class SoundStorageStub : public ISoundStorage
{
public:
    SoundStorageStub() {}
    virtual ~SoundStorageStub() {}
    virtual QSoundEffect* getSound(QString name)
    {
        return &dummySound;
    }
private:
    QSoundEffect dummySound;
};

#endif // SOUNDSTORAGESTUB_HPP
