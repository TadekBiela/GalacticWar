
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


#include "imagestorage.hpp"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <algorithm>

ImageStorage::ImageStorage()
{
    m_imageStorage.insert("default", new QImage());

    QDir directory(QCoreApplication::applicationDirPath() + "/images/");
    QStringList sounds = directory.entryList(
        QStringList() << "*.png" << "*.PNG",
        QDir::Files
    );
    std::for_each(
        sounds.begin(),
        sounds.end(),
        [this](QString filename) {
            QString name = filename;
            name.remove(name.size() - 4, 4);
            QImage* image = new QImage(
                QCoreApplication::applicationDirPath() + "/images/" + filename
            );

            this->m_imageStorage.insert(name, image);
        }
    );
}

ImageStorage::~ImageStorage() {
    std::for_each(
        m_imageStorage.cbegin(),
        m_imageStorage.cend(),
        [](QImage* image) {
            delete image;
        }
    );
}

QImage* ImageStorage::getImage(QString name) {
    auto it = m_imageStorage.find(name);
    if(m_imageStorage.end()  == it) {
        qDebug() << "Missing image: " << name;
        return *m_imageStorage.find("default");
    }

    return it.value();
}
