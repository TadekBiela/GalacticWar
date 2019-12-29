#ifndef IMAGESTORAGESTUB_HPP
#define IMAGESTORAGESTUB_HPP

#include "../../app/iimagestorage.hpp"

class ImageStorageStub : public IImageStorage
{
public:
    ImageStorageStub() {}
    virtual ~ImageStorageStub() {}
    virtual QImage* getImage(QString name)
    {
        return &dummyImage;
    }
private:
    QImage dummyImage;
};

#endif // IMAGESTORAGESTUB_HPP
