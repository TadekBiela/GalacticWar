#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "ifilemanager.hpp"
#include <QString>

class FileManager : public IFileManager
{
public:
    FileManager();
    virtual ~FileManager();
    void    saveFile(const QString fileName, const QString data);
    QString loadFile(const QString fileName);
};

#endif // FILEMANAGER_HPP
