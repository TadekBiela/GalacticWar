#ifndef FILEMANAGIERSTUB_HPP
#define FILEMANAGIERSTUB_HPP

#include "../../app/ifilemanager.hpp"

class FileManagerStub : public IFileManager
{
public:
    void saveFile(const QString data) {}
    void loadFile(QMultiHash<int, QString>::iterator highScoreIterator, int size) {}
};

#endif // FILEMANAGIERSTUB_HPP
