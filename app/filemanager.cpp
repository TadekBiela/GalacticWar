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
