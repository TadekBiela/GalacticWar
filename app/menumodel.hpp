#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "ifilemanager.hpp"
#include <QVector>
#include <QPair>

typedef QPair<QString, int>            PlayerScore;
typedef QVector<PlayerScore>           PlayerScoreTable;
typedef QVector<PlayerScore>::iterator PlayerScoreIterator;

class MenuModel
{
public:
    MenuModel();
    ~MenuModel();
    void addRecordToHighscore(PlayerScore newPlayerScore);
    void saveHighscoreToFile();
    void loadHighscoreFromFile();
    PlayerScoreIterator getHighscoreBeginIterator();
    PlayerScoreIterator getHighscoreEndIterator();

protected:
     PlayerScoreTable m_highscore;
     IFileManager*    m_fileManager;
};

#endif // MENUMODEL_HPP
