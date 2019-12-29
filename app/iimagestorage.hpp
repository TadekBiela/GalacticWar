#ifndef IIMAGESTORAGE_HPP
#define IIMAGESTORAGE_HPP

#include <QString>
#include <QImage>

class IImageStorage
{
public:
    IImageStorage() {};
    virtual ~IImageStorage() {};
    virtual QImage* getImage(QString name) = 0;
};

extern IImageStorage* g_imageStorage;

#endif // IIMAGESTORAGE_HPP
