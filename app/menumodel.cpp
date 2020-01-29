#include "menumodel.hpp"

MenuModel::MenuModel(IFileManager *fileManager)
                      : m_fileManager(fileManager)
{

}

MenuModel::~MenuModel()
{

}

void MenuModel::addRecordToHighScore(PlayerScore newPlayerScore)
{
    m_highScore.insert(m_highScore.constBegin(),
                       newPlayerScore.first,
                       newPlayerScore.second);

    emit updateHighScore(m_highScore.end(), m_highScore.size());
}

void MenuModel::saveHighScore()
{
    QString dataToSave;
    for(PlayerScoreMapIterator it = m_highScore.begin(); it != m_highScore.end(); it++)
    {
        dataToSave += QString::number(it.key()) + "\n" + it.value() + "\n";
    }
    m_fileManager->saveFile("hs.txt", dataToSave);
}

void MenuModel::loadHighScore()
{
    QString     data     = m_fileManager->loadFile("hs.txt");
    QStringList dataList = data.split("\n", QString::SplitBehavior::SkipEmptyParts);
    for(int i = 0; i < dataList.size() - 1; i += 2)
    {
        m_highScore.insert(dataList.at(i).toInt(), dataList.at(i + 1));
    }
    if(m_highScore.size() != 0)
    {
        emit updateHighScore(m_highScore.end(), m_highScore.size());
    }
}
