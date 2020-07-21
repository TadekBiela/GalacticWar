#include <gtest/gtest.h>
#include "../app/menumodel.hpp"
#include "../app/ifilemanager.hpp"
#include "utdefinitions.hpp"
#include "stubs/filemanagerstub.hpp"
#include "mocks/filemanagermock.hpp"

class MenuModelTest : public MenuModel
{
public:
    MenuModelTest() {}
    virtual ~MenuModelTest() {}

    const PlayerScoreTable& getHighscore() const { return m_highscore; }
    void setHighscore(const PlayerScoreTable& newHighscore) { m_highscore = newHighscore; }
    void changeFileManager(IFileManager* fileManager)
    {
        delete m_fileManager;
        m_fileManager = fileManager;
    }
};

class MenuModelTestsClass : public testing::Test
{
};

TEST_F(MenuModelTestsClass, AddRecordToHighscore_AddOneNewRecordCheckIfHighScoreMapHaveIt_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Bob", 1000} };
    PlayerScore      newRecord("Bob", 1000);
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

    menuModel.addRecordToHighscore(newRecord1);
    menuModel.addRecordToHighscore(newRecord2);
    menuModel.addRecordToHighscore(newRecord3);
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, SaveHighscoreToFile_CheckCorrectWorking_IsEqual)
{
    PlayerScoreTable highScore           = { {"Andy", 1000},{"Bob", 1000}, {"Ed", 1000} };
    QString          expectedFileContent = "Andy\n1000\nBob\n1000\nEd\n1000\n";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);
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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);
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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);
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
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

    menuModel.loadHighscoreFromFile();
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, LoadHighscoreFromFile_OneRecordInFileCheckCorrectWorking_IsEqual)
{
    PlayerScoreTable expectedHighscore = { {"Fred", 1300} };
    FileManagerMock* fileManager       = new FileManagerMock();
    fileManager->setFileContent(QString("Fred\n1300\n"));
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

    menuModel.loadHighscoreFromFile();
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}

TEST_F(MenuModelTestsClass, LoadHighscoreFromFile_ZeroRecordsInFileCheckCorrectWorking_IsEqual)
{
    PlayerScoreTable expectedHighscore = {};
    FileManagerMock* fileManager       = new FileManagerMock();
    fileManager->setFileContent(QString(""));
    MenuModelTest    menuModel;
    menuModel.changeFileManager(fileManager);

    menuModel.loadHighscoreFromFile();
    auto resultHighscore = menuModel.getHighscore();

    EXPECT_EQ(resultHighscore, expectedHighscore);
}
