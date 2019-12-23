#ifndef IMAGESTORAGE_HPP
#define IMAGESTORAGE_HPP

#include <QString>
#include <QImage>
#include <QHash>

class ImageStorage
{
public:
    ImageStorage();
    virtual ~ImageStorage();
    QImage* getImage(QString name);

protected:
    QHash<QString, QImage*> m_imageStorage;
};

extern ImageStorage* g_imageStorage;

#endif // IMAGESTORAGE_HPP
