
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


#include "soundstorage.hpp"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <algorithm>

SoundStorage::SoundStorage()
{
    m_soundStorage.insert("default", new QSoundEffect());

    QDir directory(QCoreApplication::applicationDirPath() + "/sounds/");
    QStringList sounds = directory.entryList(
        QStringList() << "*.wav" << "*.WAV",
        QDir::Files
    );
    std::for_each(
        sounds.begin(),
        sounds.end(),
        [this](QString filename) {
            QString name = filename;
            name.remove(name.size() - 4, 4);
            QSoundEffect* sound = new QSoundEffect();
            sound->setSource(
                QUrl::fromLocalFile(
                    QCoreApplication::applicationDirPath() + "/sounds/" + filename
                )
            );
            m_soundStorage.insert(name, sound);
        }
    );
}

SoundStorage::~SoundStorage() {
    std::for_each(
        m_soundStorage.cbegin(),
        m_soundStorage.cend(),
        [](QSoundEffect* sound) {
            delete sound;
        }
    );
}

QSoundEffect* SoundStorage::getSound(QString name) {
    auto it = m_soundStorage.find(name);
    if(m_soundStorage.end() == it) {
        qDebug() << "Missing sound: " << name;
        return *m_soundStorage.find("default");
    }

    return it.value();
}

void SoundStorage::applyNewSettings(Settings newSettings) {
    std::for_each(
        m_soundStorage.begin(),
        m_soundStorage.end(),
        [&newSettings](QSoundEffect* sound) {
            sound->setMuted(!newSettings.soundsEnabled);
            sound->setVolume(newSettings.soundsVolume);
        }
    );
}

