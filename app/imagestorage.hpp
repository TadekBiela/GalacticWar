#ifndef IMAGESTORAGE_HPP
#define IMAGESTORAGE_HPP

#include "iimagestorage.hpp"
#include <QString>
#include <QImage>
#include <QHash>

class ImageStorage : public IImageStorage
{
public:
    ImageStorage();
    virtual ~ImageStorage();
    virtual QImage* getImage(QString name);

protected:
    QHash<QString, QImage*> m_imageStorage;
};

#endif // IMAGESTORAGE_HPP
