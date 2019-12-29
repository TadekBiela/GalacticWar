#include "imagestorage.hpp"
#include <QCoreApplication>
#include <QDir>
#include <QStringList>
#include <algorithm>

ImageStorage::ImageStorage()
{
    QDir directory(QCoreApplication::applicationDirPath() + "/images/");
    QStringList sounds = directory.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    std::for_each(sounds.begin(), sounds.end(), [this](QString filename)
    {
        QString name = filename;
        name.remove(name.size() - 4, 4);
        QImage* image = new QImage(QCoreApplication::applicationDirPath() + "/images/" + filename);
        this->m_imageStorage.insert(name, image);
    });
}

ImageStorage::~ImageStorage()
{
    std::for_each(m_imageStorage.cbegin(), m_imageStorage.cend(), [](QImage* image)
    {
        delete image;
    });
}

QImage* ImageStorage::getImage(QString name)
{
    return *m_imageStorage.find(name);
}
