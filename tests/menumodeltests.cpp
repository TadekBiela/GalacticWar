#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/menumodel.hpp"
#include "../app/ifilemanager.hpp"
#include "utdefinitions.hpp"
#include "stubs/filemanagerstub.hpp"
#include "mocks/filemanagermock.hpp"

class MenuModelTest : public MenuModel
{
public:
    MenuModelTest(IFileManager* fileManager)
        : MenuModel(fileManager)
    {}
    virtual ~MenuModelTest() {}

    const PlayerScoreTable& getHighscore() const { return m_highscore; }
    void setHighscore(const PlayerScoreTable& newHighscore) { m_highscore = newHighscore; }
};

class MenuModelTestsClass : public testing::Test
{
};

TEST_F(MenuModelTestsClass, AddRecordToHighscore_AddOneNewRecordCheckIfHighScoreMapHaveIt_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Bob", 1000} };
    PlayerScore      newRecord("Bob", 1000);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest    menuModel(fileManager);

    menuModel.addRecordToHighscore(newRecord);
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_AddTwoNewRecordsCheckOrderByScore_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Bob", 1000}, {"Andy", 900} };
    PlayerScore      newRecord1("Bob", 1000);
    PlayerScore      newRecord2("Andy", 900);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest    menuModel(fileManager);

    menuModel.addRecordToHighscore(newRecord1);
    menuModel.addRecordToHighscore(newRecord2);
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_AddThreeNewRecordsCheckOrderByScore_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Ed", 1200}, {"Bob", 1000}, {"Andy", 900} };
    PlayerScore      newRecord1("Bob", 1000);
    PlayerScore      newRecord2("Andy", 900);
    PlayerScore      newRecord3("Ed", 1200);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest    menuModel(fileManager);

    menuModel.addRecordToHighscore(newRecord1);
    menuModel.addRecordToHighscore(newRecord2);
    menuModel.addRecordToHighscore(newRecord3);
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_AddThreeNewRecordsWithTheSamePlayerNameCheckOrderByScore_IsEqual)
{
    PlayerScoreTable expectedHighscore  = { {"Bob", 1200}, {"Bob", 1000}, {"Bob", 900} };
    PlayerScore      newRecord1("Bob", 1000);
    PlayerScore      newRecord2("Bob", 900);
    PlayerScore      newRecord3("Bob", 1200);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest    menuModel(fileManager);
 
    menuModel.addRecordToHighscore(newRecord1);
    menuModel.addRecordToHighscore(newRecord2);
    menuModel.addRecordToHighscore(newRecord3);
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_AddThreeNewRecordsWithTheSameScoreNameCheckOrderIsByName_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Andy", 1000}, {"Bob", 1000}, {"Ed", 1000} };
    PlayerScore      newRecord1("Bob", 1000);
    PlayerScore      newRecord2("Andy", 1000);
    PlayerScore      newRecord3("Ed", 1000);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest    menuModel(fileManager);

    menuModel.addRecordToHighscore(newRecord1);
    menuModel.addRecordToHighscore(newRecord2);
    menuModel.addRecordToHighscore(newRecord3);
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_CurrentHighscoreSizeIsMaxNumOfRecordsMinus1_ShouldAddNewRecord)
{
    PlayerScore newRecord("testNew", 101);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest menuModel(fileManager);
    PlayerScoreTable filledHighScore;
    for(int i = 0; i < (def::maxNumOfHighScoreRecords - 1); i++) {
        filledHighScore.push_back(
            PlayerScore(
                "test",
                (10 * i)
            )
        );
    }
    menuModel.setHighscore(filledHighScore);

    menuModel.addRecordToHighscore(newRecord);

    auto resultHighscore = menuModel.getHighscore();
    EXPECT_EQ(def::maxNumOfHighScoreRecords, resultHighscore.size()); 
    EXPECT_EQ(8, resultHighscore.indexOf(newRecord));
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_CurrentHighscoreSizeIsMaxNumOfRecordsAndNewRecordHasScoreHigherThanLastInHightscore_ShouldAddNewRecordAndRemoveLast)
{
    PlayerScore newRecord("testNew", 101);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest menuModel(fileManager);
    PlayerScoreTable filledHighScore;
    for(int i = 0; i < (def::maxNumOfHighScoreRecords); i++) {
        filledHighScore.push_back(
            PlayerScore(
                "test",
                (10 * i)
            )
        );
    }
    menuModel.setHighscore(filledHighScore);

    menuModel.addRecordToHighscore(newRecord);

    auto resultHighscore = menuModel.getHighscore();
    EXPECT_EQ(def::maxNumOfHighScoreRecords, resultHighscore.size()); 
    EXPECT_EQ(9, resultHighscore.indexOf(newRecord));
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_CurrentHighscoreSizeIsMaxNumOfRecordsAndNewRecordHasScoreLowerThanLastInHightscore_ShouldNotAddNewRecord)
{
    PlayerScore newRecord("testNew", 0);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest menuModel(fileManager);
    PlayerScoreTable filledHighScore;
    for(int i = 0; i < (def::maxNumOfHighScoreRecords); i++) {
        filledHighScore.push_back(
            PlayerScore(
                "test",
                (10 + (10 * i))
            )
        );
    }
    menuModel.setHighscore(filledHighScore);

    menuModel.addRecordToHighscore(newRecord);

    auto resultHighscore = menuModel.getHighscore();
    EXPECT_EQ(def::maxNumOfHighScoreRecords, resultHighscore.size()); 
    EXPECT_EQ(-1, resultHighscore.indexOf(newRecord));
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_CurrentHighscoreSizeIsMaxNumOfRecordsAndNewRecordHasScoreSameAsLastInHightscoreButNameIsFurtherInAlphabet_ShouldNotAddNewRecord)
{
    PlayerScore newRecord("testNew", 0);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest menuModel(fileManager);
    PlayerScoreTable filledHighScore;
    for(int i = 0; i < (def::maxNumOfHighScoreRecords); i++) {
        filledHighScore.push_back(
            PlayerScore(
                "test",
                (10 * i)
            )
        );
    }
    menuModel.setHighscore(filledHighScore);

    menuModel.addRecordToHighscore(newRecord);

    auto resultHighscore = menuModel.getHighscore();
    EXPECT_EQ(def::maxNumOfHighScoreRecords, resultHighscore.size()); 
    EXPECT_EQ(-1, resultHighscore.indexOf(newRecord));
}

TEST_F(MenuModelTestsClass, AddRecordToHighscore_CurrentHighscoreSizeIsMaxNumOfRecordsAndNewRecordHasScoreSameAsLastInHightscoreButNameIsPriorInAlphabet_ShouldAddNewRecordAndRemoveLastOld)
{
    PlayerScore newRecord("testNew", 0);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest menuModel(fileManager);
    PlayerScoreTable filledHighScore;
    for(int i = 0; i < (def::maxNumOfHighScoreRecords); i++) {
        filledHighScore.push_back(
            PlayerScore(
                "testVintage:D",
                (10 * i)
            )
        );
    }
    menuModel.setHighscore(filledHighScore);

    menuModel.addRecordToHighscore(newRecord);

    auto resultHighscore = menuModel.getHighscore();
    EXPECT_EQ(def::maxNumOfHighScoreRecords, resultHighscore.size()); 
    EXPECT_EQ(19, resultHighscore.indexOf(newRecord));
}

TEST_F(MenuModelTestsClass, SaveHighscoreToFile_CheckCorrectWorking_IsEqual)
{
    PlayerScoreTable highScore           = { {"Andy", 1000},{"Bob", 1000}, {"Ed", 1000} };
    QString          expectedFileContent = "Andy\n1000\nBob\n1000\nEd\n1000\n";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTest    menuModel(fileManager);
    menuModel.setHighscore(highScore);

    menuModel.saveHighscoreToFile();
    QString resultFileContent = fileManager->getFileContent();

    EXPECT_EQ(resultFileContent.toStdString(), expectedFileContent.toStdString());
}

TEST_F(MenuModelTestsClass, SaveHighscoreToFile_OnlyOneRecordCheckCorrectWorking_IsEqual)
{
    PlayerScoreTable highScore           = { {"Andy", 1000} };
    QString          expectedFileContent = "Andy\n1000\n";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTest    menuModel(fileManager);
    menuModel.setHighscore(highScore);

    menuModel.saveHighscoreToFile();
    QString resultFileContent = fileManager->getFileContent();

    EXPECT_EQ(resultFileContent.toStdString(), expectedFileContent.toStdString());
}

TEST_F(MenuModelTestsClass, SaveHighscoreToFile_ZeroRecordsCheckCorrectWorking_IsEqual)
{
    PlayerScoreTable highScore           = { };
    QString          expectedFileContent = "";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTest    menuModel(fileManager);
    menuModel.setHighscore(highScore);

    menuModel.saveHighscoreToFile();
    QString resultFileContent = fileManager->getFileContent();

    EXPECT_EQ(resultFileContent.toStdString(), expectedFileContent.toStdString());
}

TEST_F(MenuModelTestsClass, LoadHighscoreFromFile_CheckCorrectWorking_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Andy", 1300}, {"Ed", 1000}, {"Bob", 1000}, {"Andy", 1000}, {"Fred", 300}};
    FileManagerMock* fileManager       = new FileManagerMock();
    fileManager->setFileContent(QString("Andy\n1300\nEd\n1000\nBob\n1000\nAndy\n1000\nFred\n300\n"));
    MenuModelTest    menuModel(fileManager);

    menuModel.loadHighscoreFromFile();
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, LoadHighscoreFromFile_OneRecordInFileCheckCorrectWorking_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Fred", 1300} };
    FileManagerMock* fileManager       = new FileManagerMock();
    fileManager->setFileContent(QString("Fred\n1300\n"));
    MenuModelTest    menuModel(fileManager);

    menuModel.loadHighscoreFromFile();
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, LoadHighscoreFromFile_ZeroRecordsInFileCheckCorrectWorking_IsEqual)
{
    PlayerScoreTable expectedHighscore = {};
    FileManagerMock* fileManager       = new FileManagerMock();
    fileManager->setFileContent(QString(""));
    MenuModelTest    menuModel(fileManager);

    menuModel.loadHighscoreFromFile();
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, saveSettingsToFile_MouseControlMode_ShouldSaveAllSettingsAndControlModeAsMouse)
{
    QString expectedSettingFileContent(
        "[Music]\n"
        "music enabled: false\n"
        "music volume: 81\n\n"
        "[Sounds]\n"
        "sounds enabled: true\n"
        "sounds volume: 0.5\n\n"
        "[Control]\n"
        "control mode: mouse\n"
    );
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModel menuModel(fileManager);
    Settings inputSettings;
    inputSettings.musicEnabled = false;
    inputSettings.musicVolume = 81;
    inputSettings.soundsEnabled = true;
    inputSettings.soundsVolume = 0.5;
    inputSettings.controlMode = control_mode::mouse;
    menuModel.setSettings(inputSettings);

    menuModel.saveSettingsToFile();

    EXPECT_EQ(expectedSettingFileContent, fileManager->getFileContent());
}

TEST_F(MenuModelTestsClass, saveSettingsToFile_KeyboardControl_ShouldSaveAllSettingsAndControlModeAsKeyboard)
{
    QString expectedSettingFileContent(
        "[Music]\n"
        "music enabled: true\n"
        "music volume: 40\n\n"
        "[Sounds]\n"
        "sounds enabled: false\n"
        "sounds volume: 0\n\n"
        "[Control]\n"
        "control mode: keyboard\n"
    );
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModel menuModel(fileManager);
    Settings inputSettings;
    inputSettings.musicEnabled = true;
    inputSettings.musicVolume = 40;
    inputSettings.soundsEnabled = false;
    inputSettings.soundsVolume = 0;
    inputSettings.controlMode = control_mode::keyboard;
    menuModel.setSettings(inputSettings);

    menuModel.saveSettingsToFile();

    EXPECT_EQ(expectedSettingFileContent, fileManager->getFileContent());
}

TEST_F(MenuModelTestsClass, loadSettingsFromFile_MouseControl_ShouldLoadAllSettingsAndControlModeAsMouse)
{
    Settings expectedSettings;
    expectedSettings.musicEnabled = false;
    expectedSettings.musicVolume = 0;
    expectedSettings.soundsEnabled = true;
    expectedSettings.soundsVolume = 1;
    expectedSettings.controlMode = control_mode::mouse;
    FileManagerMock* fileManager = new FileManagerMock;
    fileManager->setFileContent(QString(
        "[Music]\n"
        "music enabled: false\n"
        "music volume: 0\n\n"
        "[Sounds]\n"
        "sounds enabled: true\n"
        "sounds volume: 1\n\n"
        "[Control]\n"
        "control mode: mouse\n"
    ));
    MenuModel menuModel(fileManager);

    menuModel.loadSettingsFromFile();

    Settings resultSettings = menuModel.getSettings();
    EXPECT_EQ(expectedSettings.musicEnabled, resultSettings.musicEnabled);
    EXPECT_EQ(expectedSettings.musicVolume, resultSettings.musicVolume);
    EXPECT_EQ(expectedSettings.soundsEnabled, resultSettings.soundsEnabled);
    EXPECT_EQ(expectedSettings.soundsVolume, resultSettings.soundsVolume);
    EXPECT_EQ(expectedSettings.controlMode, resultSettings.controlMode);
}

TEST_F(MenuModelTestsClass, loadSettingsFromFile_KeyboardControl_ShouldLoadAllSettingsAndControlModeAsKeyboard)
{
    Settings expectedSettings;
    expectedSettings.musicEnabled = true;
    expectedSettings.musicVolume = 40;
    expectedSettings.soundsEnabled = false;
    expectedSettings.soundsVolume = 0;
    expectedSettings.controlMode = control_mode::keyboard;
    FileManagerMock* fileManager = new FileManagerMock;
    fileManager->setFileContent(QString(
        "[Music]\n"
        "music enabled: true\n"
        "music volume: 40\n\n"
        "[Sounds]\n"
        "sounds enabled: false\n"
        "sounds volume: 0\n\n"
        "[Control]\n"
        "control mode: keyboard\n"
    ));
    MenuModel menuModel(fileManager);

    menuModel.loadSettingsFromFile();

    Settings resultSettings = menuModel.getSettings();
    EXPECT_EQ(expectedSettings.musicEnabled, resultSettings.musicEnabled);
    EXPECT_EQ(expectedSettings.musicVolume, resultSettings.musicVolume);
    EXPECT_EQ(expectedSettings.soundsEnabled, resultSettings.soundsEnabled);
    EXPECT_EQ(expectedSettings.soundsVolume, resultSettings.soundsVolume);
    EXPECT_EQ(expectedSettings.controlMode, resultSettings.controlMode);
}

TEST_F(MenuModelTestsClass, loadSettingsFromFile_LoadEmptyFile_ShouldDoNothing)
{
    FileManagerStub* fileManager = new FileManagerStub;
    MenuModel menuModel(fileManager);
    Settings expectedSettings = menuModel.getSettings();

    menuModel.loadSettingsFromFile();

    Settings resultSettings = menuModel.getSettings();
    EXPECT_EQ(expectedSettings.musicEnabled, resultSettings.musicEnabled);
    EXPECT_EQ(expectedSettings.musicVolume, resultSettings.musicVolume);
    EXPECT_EQ(expectedSettings.soundsEnabled, resultSettings.soundsEnabled);
    EXPECT_EQ(expectedSettings.soundsVolume, resultSettings.soundsVolume);
    EXPECT_EQ(expectedSettings.controlMode, resultSettings.controlMode);
}

