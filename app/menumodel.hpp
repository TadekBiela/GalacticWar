#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "ifilemanager.hpp"
#include <QVector>
#include <QPair>

typedef QPair<QString, int> PlayerScore;
typedef QVector<PlayerScore> PlayerScoreTable;
typedef QVector<PlayerScore>::iterator PlayerScoreIterator;

class MenuModel
{
public:
    MenuModel(IFileManager* fileManager = nullptr);
    ~MenuModel();
    void addRecordToHighscore(PlayerScore newPlayerScore);
    void saveHighscoreToFile();
    void loadHighscoreFromFile();
    PlayerScoreIterator getHighscoreBeginIterator();
    PlayerScoreIterator getHighscoreEndIterator();
    int getHighscoreSize() const;

protected:
    PlayerScoreTable m_highscore;
    IFileManager* m_fileManager;
};

#endif // MENUMODEL_HPP
