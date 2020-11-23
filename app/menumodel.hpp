#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "ifilemanager.hpp"
#include "settings.hpp"
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
    void setSettings(Settings newSettings);
    Settings getSettings() const;
    void saveSettingsToFile() const;
    void loadSettingsFromFile();

protected:
    PlayerScoreTable m_highscore;
    IFileManager* m_fileManager;
    Settings m_settings;
};

#endif // MENUMODEL_HPP
