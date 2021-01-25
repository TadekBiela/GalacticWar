
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


#ifndef ISOUNDSTORAGE_HPP
#define ISOUNDSTORAGE_HPP

#include <QObject>
#include <QString>
#include <QSoundEffect>

struct Settings;

class ISoundStorage : public QObject
{
    Q_OBJECT
public:
    ISoundStorage() {};
    virtual ~ISoundStorage() {};
    virtual QSoundEffect* getSound(QString name) = 0;

public slots:
    virtual void applyNewSettings(Settings newSettings) = 0;
};

extern ISoundStorage* g_soundStorage;

#endif // ISOUNDSTORAGE_HPP
