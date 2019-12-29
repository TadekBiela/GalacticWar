#include "soundstorage.hpp"
#include <QCoreApplication>
#include <QDir>
#include <QStringList>
#include <algorithm>

SoundStorage::SoundStorage()
{
    QDir directory(QCoreApplication::applicationDirPath() + "/sounds/");
    QStringList sounds = directory.entryList(QStringList() << "*.wav" << "*.WAV", QDir::Files);
    std::for_each(sounds.begin(), sounds.end(), [this](QString filename)
    {
        QString name = filename;
        name.remove(name.size() - 4, 4);
        QSoundEffect* sound = new QSoundEffect;
        sound->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/sounds/" + filename));
        this->m_soundStorage.insert(name, sound);
    });
}

SoundStorage::~SoundStorage()
{
    std::for_each(m_soundStorage.cbegin(), m_soundStorage.cend(), [](QSoundEffect* sound)
    {
        delete sound;
    });
}

QSoundEffect* SoundStorage::getSound(QString name)
{
    return *m_soundStorage.find(name);
}
