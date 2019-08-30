#ifndef FILEMANAGIERSTUB_HPP
#define FILEMANAGIERSTUB_HPP

#include "../../app/ifilemanager.hpp"

class FileManagerStub : public IFileManager
{
public:
    void saveFile(const QString data) {}
    QString loadFile(const QString fileName) {}
};

#endif // FILEMANAGIERSTUB_HPP
