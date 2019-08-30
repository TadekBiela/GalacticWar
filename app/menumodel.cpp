#include "menumodel.hpp"

MenuModel::MenuModel(IFileManager *fileManager) : m_fileManager(fileManager)
{

}

MenuModel::~MenuModel()
{

}

void MenuModel::addRecordToHighScore(PlayerScore newPlayerScore)
{
    m_highScore.insert(newPlayerScore.first, newPlayerScore.second);
    emit updateHighScore(m_highScore.begin(), m_highScore.size());
}

void MenuModel::saveHighScore()
{
    QString dataToSave;
    for(PlayerScoreMapIterator it = m_highScore.begin(); it != m_highScore.end(); it++)
    {
        dataToSave += QString::number(it.key()) + " " + it.value() + " ";
    }
    m_fileManager->saveFile(dataToSave);
}

void MenuModel::loadHighScore()
{

}
