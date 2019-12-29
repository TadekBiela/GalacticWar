#ifndef ISOUNDSTORAGE_HPP
#define ISOUNDSTORAGE_HPP

#include <QString>
#include <QSoundEffect>

class ISoundStorage
{
public:
    ISoundStorage() {};
    virtual ~ISoundStorage() {};
    virtual QSoundEffect* getSound(QString name) = 0;
};

extern ISoundStorage* g_soundStorage;

#endif // ISOUNDSTORAGE_HPP
