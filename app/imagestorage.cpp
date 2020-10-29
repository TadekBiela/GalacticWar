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
