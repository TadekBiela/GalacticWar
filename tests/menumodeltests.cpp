#include <gtest/gtest.h>
#include "../app/menumodel.hpp"
#include "../app/ifilemanager.hpp"
#include "utdefinitions.hpp"
#include "stubs/filemanagerstub.hpp"
#include "mocks/filemanagermock.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(PlayerScoreMapIterator)

class MenuModelTests : public MenuModel
{
public:
    MenuModelTests(IFileManager* fileManager) : MenuModel(fileManager) {}
    const PlayerScoreMap& getHighScore() const { return m_highScore; }
    void setHighScore(const PlayerScoreMap& newHighScore) { m_highScore = newHighScore; }
};

class MenuModelTestsClass : public testing::Test
{
};

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddOneNewRecordCheckIfHighScoreMapHaveItAndUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMapIterator>();
    PlayerScoreMap   expectedHighScore       = { {1000, "Bob"} };
    auto             expectedFirstParamType  = QVariant::fromValue(PlayerScoreMapIterator()).type();
    auto             expectedSecondParamType = QVariant::Int;
    PlayerScore      newRecord(1000, "Bob");
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTests   menuModel(fileManager);
    QSignalSpy       signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord       = resultHighScore.contains(newRecord.first, newRecord.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeLast();

    EXPECT_EQ(resultSize,                       1);
    EXPECT_EQ(resultIsNewRecord,                true);
    EXPECT_EQ(resultHighScore,                  expectedHighScore);
    EXPECT_EQ(resultSignalUpdateCount,          1);
    EXPECT_EQ(resultSignalUpdate.at(0).type(),  expectedFirstParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).type(),  expectedSecondParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).toInt(), 1);
    delete fileManager;
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddTwoNewRecordsCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMapIterator>();
    PlayerScoreMap   expectedHighScore       = { {1000, "Bob"}, {900, "Andy"} };
    auto             expectedFirstParamType  = QVariant::fromValue(PlayerScoreMapIterator()).type();
    auto             expectedSecondParamType = QVariant::Int;
    PlayerScore      newRecord1(1000, "Bob");
    PlayerScore      newRecord2( 900, "Andy");
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTests   menuModel(fileManager);
    QSignalSpy       signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeLast();

    EXPECT_EQ(resultSize,                       2);
    EXPECT_EQ(resultIsNewRecord1,               true);
    EXPECT_EQ(resultIsNewRecord2,               true);
    EXPECT_EQ(resultHighScore,                  expectedHighScore);
    EXPECT_EQ(resultSignalUpdateCount,          2);
    EXPECT_EQ(resultSignalUpdate.at(0).type(),  expectedFirstParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).type(),  expectedSecondParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).toInt(), 2);
    delete fileManager;
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddThreeNewRecordsCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMapIterator>();
    PlayerScoreMap   expectedHighScore       = { {1200, "Ed"}, {1000, "Bob"}, {900, "Andy"} };
    auto             expectedFirstParamType  = QVariant::fromValue(PlayerScoreMapIterator()).type();
    auto             expectedSecondParamType = QVariant::Int;
    PlayerScore      newRecord1(1000, "Bob");
    PlayerScore      newRecord2( 900, "Andy");
    PlayerScore      newRecord3(1200, "Ed");
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTests   menuModel(fileManager);
    QSignalSpy       signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    menuModel.addRecordToHighScore(newRecord3);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    bool resultIsNewRecord3      = resultHighScore.contains(newRecord3.first, newRecord3.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeLast();

    EXPECT_EQ(resultSize,                       3);
    EXPECT_EQ(resultIsNewRecord1,               true);
    EXPECT_EQ(resultIsNewRecord2,               true);
    EXPECT_EQ(resultIsNewRecord3,               true);
    EXPECT_EQ(resultHighScore,                  expectedHighScore);
    EXPECT_EQ(resultSignalUpdateCount,          3);
    EXPECT_EQ(resultSignalUpdate.at(0).type(),  expectedFirstParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).type(),  expectedSecondParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).toInt(), 3);
    delete fileManager;
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddThreeNewRecordsWithTheSamePlayerNameCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMapIterator>();
    PlayerScoreMap   expectedHighScore       = { {1200, "Bob"}, {1000, "Bob"}, {900, "Bob"} };
    auto             expectedFirstParamType  = QVariant::fromValue(PlayerScoreMapIterator()).type();
    auto             expectedSecondParamType = QVariant::Int;
    PlayerScore      newRecord1(1000, "Bob");
    PlayerScore      newRecord2( 900, "Bob");
    PlayerScore      newRecord3(1200, "Bob");
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTests   menuModel(fileManager);
    QSignalSpy       signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    menuModel.addRecordToHighScore(newRecord3);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    bool resultIsNewRecord3      = resultHighScore.contains(newRecord3.first, newRecord3.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeLast();

    EXPECT_EQ(resultSize,                       3);
    EXPECT_EQ(resultIsNewRecord1,               true);
    EXPECT_EQ(resultIsNewRecord2,               true);
    EXPECT_EQ(resultIsNewRecord3,               true);
    EXPECT_EQ(resultHighScore,                  expectedHighScore);
    EXPECT_EQ(resultSignalUpdateCount,          3);
    EXPECT_EQ(resultSignalUpdate.at(0).type(),  expectedFirstParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).type(),  expectedSecondParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).toInt(), 3);
    delete fileManager;
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddThreeNewRecordsWithTheSameScoreNameCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMapIterator>();
    PlayerScoreMap   expectedHighScore       = { {1000, "Andy"}, {1000, "Bob"}, {1000, "Ed"} };
    auto             expectedFirstParamType  = QVariant::fromValue(PlayerScoreMapIterator()).type();
    auto             expectedSecondParamType = QVariant::Int;
    PlayerScore      newRecord1(1000, "Bob");
    PlayerScore      newRecord2(1000, "Andy");
    PlayerScore      newRecord3(1000, "Ed");
    FileManagerStub* fileManager = new FileManagerStub();
    MenuModelTests   menuModel(fileManager);
    QSignalSpy       signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    menuModel.addRecordToHighScore(newRecord3);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    bool resultIsNewRecord3      = resultHighScore.contains(newRecord3.first, newRecord3.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeLast();

    EXPECT_EQ(resultSize,                       3);
    EXPECT_EQ(resultIsNewRecord1,               true);
    EXPECT_EQ(resultIsNewRecord2,               true);
    EXPECT_EQ(resultIsNewRecord3,               true);
    EXPECT_EQ(resultHighScore,                  expectedHighScore);
    EXPECT_EQ(resultSignalUpdateCount,          3);
    EXPECT_EQ(resultSignalUpdate.at(0).type(),  expectedFirstParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).type(),  expectedSecondParamType);
    EXPECT_EQ(resultSignalUpdate.at(1).toInt(), 3);
    delete fileManager;
}

TEST_F(MenuModelTestsClass, SaveHighScore_CheckCorrectWorking_IsEqual)
{
    PlayerScoreMap   highScore           = { {1000, "Andy"},{1000, "Bob"}, {1000, "Ed"} };
    QString          expectedFileContent = "1000 Ed 1000 Bob 1000 Andy ";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTests   menuModel(fileManager);
    menuModel.setHighScore(highScore);

    menuModel.saveHighScore();
    QString resultFileContent = fileManager->getFileContent();

    EXPECT_EQ(resultFileContent.toStdString(), expectedFileContent.toStdString());
    delete fileManager;
}

TEST_F(MenuModelTestsClass, SaveHighScore_OnlyOneRecordCheckCorrectWorking_IsEqual)
{
    PlayerScoreMap   highScore           = { {1000, "Andy"} };
    QString          expectedFileContent = "1000 Andy ";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTests   menuModel(fileManager);
    menuModel.setHighScore(highScore);

    menuModel.saveHighScore();
    QString resultFileContent = fileManager->getFileContent();

    EXPECT_EQ(resultFileContent.toStdString(), expectedFileContent.toStdString());
    delete fileManager;
}

TEST_F(MenuModelTestsClass, SaveHighScore_ZeroRecordsCheckCorrectWorking_IsEqual)
{
    PlayerScoreMap   highScore           = { };
    QString          expectedFileContent = "";
    FileManagerMock* fileManager = new FileManagerMock();
    MenuModelTests   menuModel(fileManager);
    menuModel.setHighScore(highScore);

    menuModel.saveHighScore();
    QString resultFileContent = fileManager->getFileContent();

    EXPECT_EQ(resultFileContent.toStdString(), expectedFileContent.toStdString());
    delete fileManager;
}
