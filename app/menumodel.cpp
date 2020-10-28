#include "definitions.hpp"
#include "filemanager.hpp"
#include "menumodel.hpp"
#include <algorithm>

MenuModel::MenuModel()
    : m_highscore(),
      m_fileManager(new FileManager)
{

}

MenuModel::~MenuModel()
{
    delete m_fileManager;
}

void MenuModel::addRecordToHighscore(PlayerScore newPlayerScore)
{
    m_highscore.push_back(newPlayerScore);
    std::sort(m_highscore.begin(), m_highscore.end(),
              [](const PlayerScore& a, const PlayerScore& b)->bool
                {
                    if(a.second > b.second) //If score a is higher return true
                    {
                        return true;
                    }
                    else if (a.second == b.second)
                    {
                        return (a.first < b.first); //If score is equal check player name alphabetical order
                    }
                    else
                    {
                        return false;
                    }
                }
    );
    while(def::maxNumOfHighScoreRecords < m_highscore.size()) {
        m_highscore.pop_back();
    }
}

void MenuModel::saveHighscoreToFile()
{
    QString dataToSave;
    for(PlayerScoreIterator it = m_highscore.begin(); it != m_highscore.end(); it++)
    {
        dataToSave += it->first + "\n" + QString::number(it->second) + "\n";
    }
    m_fileManager->saveFile("hs.txt", dataToSave);
}

void MenuModel::loadHighscoreFromFile()
{
    QString     data     = m_fileManager->loadFile("hs.txt");
    QStringList dataList = data.split("\n", QString::SplitBehavior::SkipEmptyParts);
    for(int i = 0; i < dataList.size() - 1; i += 2)
    {
        PlayerScore record(dataList.at(i), dataList.at(i + 1).toInt());
        m_highscore.push_back(record);
    }
}

PlayerScoreIterator MenuModel::getHighscoreBeginIterator()
{
    return m_highscore.begin();
}

PlayerScoreIterator MenuModel::getHighscoreEndIterator()
{
    return m_highscore.end();
}
