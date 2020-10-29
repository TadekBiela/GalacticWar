#ifndef FILEMANAGIERSTUB_HPP
#define FILEMANAGIERSTUB_HPP

#include "../../app/ifilemanager.hpp"

class FileManagerStub : public IFileManager
{
public:
    FileManagerStub() {}
    virtual ~FileManagerStub() {}
    void    saveFile(const QString fileName, const QString data) {}
    QString loadFile(const QString fileName) {
        return QString();
    }
};

#endif // FILEMANAGIERSTUB_HPP
