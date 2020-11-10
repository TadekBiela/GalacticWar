#ifndef ISOUNDSTORAGE_HPP
#define ISOUNDSTORAGE_HPP

#include <QObject>
#include <QString>
#include <QSoundEffect>

struct Settings;

class ISoundStorage : public QObject
{
    Q_OBJECT
public:
    ISoundStorage() {};
    virtual ~ISoundStorage() {};
    virtual QSoundEffect* getSound(QString name) = 0;

public slots:
    virtual void applyNewSettings(Settings newSettings) = 0;
};

extern ISoundStorage* g_soundStorage;

#endif // ISOUNDSTORAGE_HPP
