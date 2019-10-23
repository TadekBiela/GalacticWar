#ifndef FILEMANAGIERMOCK_HPP
#define FILEMANAGIERMOCK_HPP

#include "../../app/ifilemanager.hpp"

class FileManagerMock : public IFileManager
{
public:
    FileManagerMock() {}
    virtual ~FileManagerMock() {}
    void    saveFile(const QString fileName, const QString data) { m_fileContent = data; }
    QString loadFile(const QString fileName) { return m_fileContent; }
    QString getFileContent() const { return m_fileContent; }
    void    setFileContent(const QString data) { m_fileContent = data; }

private:
    QString m_fileContent;
};

#endif // FILEMANAGIERMOCK_HPP
