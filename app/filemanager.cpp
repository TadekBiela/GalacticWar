
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


#include "filemanager.hpp"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

void FileManager::saveFile(const QString fileName, const QString data)
{
    QString path = QCoreApplication::applicationDirPath() + QString("/") + fileName;
    QFile   file(path);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << data;
        file.close();
    }
}

QString FileManager::loadFile(const QString fileName)
{
    QString data;
    QString path = QCoreApplication::applicationDirPath() + QString("/") + fileName;
    QFile   file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        data = in.readAll();
        file.close();
    }
    return data;
}
