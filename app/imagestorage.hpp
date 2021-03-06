
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
