#ifndef IMAGESTORAGESTUB_HPP
#define IMAGESTORAGESTUB_HPP

#include "../../app/iimagestorage.hpp"

class ImageStorageStub : public IImageStorage
{
public:
    ImageStorageStub()
                     : dummyImage(60, 60, QImage::Format::Format_RGB32)
    {}
    virtual ~ImageStorageStub() {}

    virtual QImage* getImage(QString name)
    {
        dummyImage.fill(QColor(Qt::black));
        return &dummyImage;
    }

    void setDummyImageSize(int width, int height)
    {
        dummyImage = QImage(width, height, QImage::Format::Format_RGB32);
    }

private:
    QImage dummyImage;
};

#endif // IMAGESTORAGESTUB_HPP
