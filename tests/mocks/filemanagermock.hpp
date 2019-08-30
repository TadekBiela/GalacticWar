#ifndef FILEMANAGIERMOCK_HPP
#define FILEMANAGIERMOCK_HPP

#include "../../app/ifilemanager.hpp"

class FileManagerMock : public IFileManager
{
public:
    void saveFile(const QString data) { m_fileContent = data; }
    void loadFile(QMultiHash<int, QString>::iterator highScoreIterator, int size) {}
    QString getFileContent() const { return m_fileContent; }

private:
    QString m_fileContent;
};

#endif // FILEMANAGIERMOCK_HPP
