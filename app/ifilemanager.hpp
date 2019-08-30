#ifndef IFILEMANAGER_HPP
#define IFILEMANAGER_HPP

#include <QString>
#include <QMultiHash>

class IFileManager
{
public:
    IFileManager() {}
    virtual ~IFileManager() {}
    virtual void saveFile(const QString data) = 0;
    virtual void loadFile(QMultiHash<int, QString>::iterator highScoreIterator, int size) = 0;
};

#endif // IFILEMANAGER_HPP
