#include "definitions.hpp"
#include "filemanager.hpp"
#include "menumodel.hpp"
#include <QStringList>
#include <QVariant>
#include <algorithm>

MenuModel::MenuModel(
    IFileManager* fileManager
) :
    m_highscore()
{
    if(nullptr == fileManager) {
        m_fileManager = new FileManager();
    }
    else {
        m_fileManager = fileManager;
    }

    m_settings.musicEnabled = true;
    m_settings.musicVolume = 50;
    m_settings.soundsEnabled = true;
    m_settings.soundsVolume = 0.5;
    m_settings.controlMode = control_mode::mouse;
}

MenuModel::~MenuModel() {
    delete m_fileManager;
}

void MenuModel::addRecordToHighscore(
    PlayerScore newPlayerScore
) {
    m_highscore.push_back(
        newPlayerScore
    );

    std::sort(
        m_highscore.begin(),
        m_highscore.end(),
        [](const PlayerScore& a, const PlayerScore& b)->bool {
            if(a.second > b.second) {
                return true;
            }
            else if (a.second == b.second) {
                return (a.first < b.first);
            }
            else {
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

int MenuModel::getHighscoreSize() const {
    return m_highscore.size();
}

void MenuModel::setSettings(Settings newSettings) {
    m_settings = newSettings;
}

Settings MenuModel::getSettings() const {
    return m_settings;
}

void MenuModel::saveSettingsToFile() const {
    QString dataToSave;

    dataToSave += "[Music]\n";
    dataToSave += "music enabled: " + QVariant(m_settings.musicEnabled).toString() + "\n";
    dataToSave += "music volume: " + QString::number(m_settings.musicVolume) + "\n\n";
    dataToSave += "[Sounds]\n";
    dataToSave += "sounds enabled: " + QVariant(m_settings.soundsEnabled).toString() + "\n";
    dataToSave += "sounds volume: " + QString::number(m_settings.soundsVolume) + "\n\n";
    dataToSave += "[Control]\n";
    QString controlModeStr = (m_settings.controlMode == control_mode::mouse) ?
        "mouse" :
        "keyboard";
    dataToSave += "control mode: " + controlModeStr + "\n";

    m_fileManager->saveFile("settings.txt", dataToSave);
}

void MenuModel::loadSettingsFromFile() {
    QString data = m_fileManager->loadFile("settings.txt");
    QStringList dataList = data.split("\n", QString::SplitBehavior::SkipEmptyParts);

    if(not dataList.isEmpty()) {
        const int settingValueOffset = 1;

        int musicEnabledIdx = 1;
        auto musicEnabledLineList = dataList.at(musicEnabledIdx).split(": ");
        auto musicEnabledStr = musicEnabledLineList.at(settingValueOffset);
        m_settings.musicEnabled = QVariant(musicEnabledStr).toBool();

        int musicVolumeIdx = musicEnabledIdx + 1;
        auto musicVolumeLineList = dataList.at(musicVolumeIdx).split(": ");
        auto musicVolumeStr = musicVolumeLineList.at(settingValueOffset);
        m_settings.musicVolume = QVariant(musicVolumeStr).toInt();

        int soundsEnabledIdx = musicVolumeIdx + 2;
        auto soundsEnabledLineList = dataList.at(soundsEnabledIdx).split(": ");
        auto soundsEnabledStr = soundsEnabledLineList.at(settingValueOffset);
        m_settings.soundsEnabled = QVariant(soundsEnabledStr).toBool();

        int soundsVolumeIdx = soundsEnabledIdx + 1;
        auto soundsVolumeLineList = dataList.at(soundsVolumeIdx).split(": ");
        auto soundsVolumeStr = soundsVolumeLineList.at(settingValueOffset);
        m_settings.soundsVolume = QVariant(soundsVolumeStr).toFloat();

        int controlModeIdx = soundsVolumeIdx + 2;
        auto controlModeLineList = dataList.at(controlModeIdx).split(": ");
        auto controlModeStr = controlModeLineList.at(settingValueOffset);
        m_settings.controlMode = (controlModeStr == "mouse") ?
            control_mode::mouse :
            control_mode::keyboard;
    }
}

