#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/menumodel.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(PlayerScoreMap::Iterator)

class MenuModelTests : public MenuModel
{
public:
    const PlayerScoreMap& getHighScore() const { return m_highScore; }
};

class MenuModelTestsClass : public testing::Test
{
};

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddOneNewRecordCheckIfHighScoreMapHaveItAndUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMap::Iterator>();
    PlayerScore    newRecord(1000, "Bob");
    MenuModelTests menuModel;
    auto           expectedIterator = menuModel.getHighScore().begin();
    QSignalSpy     signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord       = resultHighScore.contains(newRecord.first, newRecord.second);
    auto resultFindInerator      = resultHighScore.find(newRecord.first, newRecord.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeFirst();
    auto resultPlayerScoreMapIt  = qvariant_cast<PlayerScoreMap::Iterator>(resultSignalUpdate.at(0));

    EXPECT_EQ(resultSize,               1);
    EXPECT_EQ(resultIsNewRecord,        true);
    EXPECT_EQ(resultFindInerator,       expectedIterator);
    EXPECT_EQ(resultSignalUpdateCount,  1);
    EXPECT_EQ(resultSignalUpdate.at(1), 1);
    EXPECT_EQ(resultPlayerScoreMapIt,   expectedIterator);
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddTwoNewRecordsCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMap::Iterator>();
    PlayerScore    newRecord1(1000, "Bob");
    PlayerScore    newRecord2( 900, "Andy");
    MenuModelTests menuModel;
    auto           expectedIterator = menuModel.getHighScore().begin();
    QSignalSpy     signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    auto resultFindInerator      = resultHighScore.find(newRecord1.first, newRecord1.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeFirst();
    auto resultPlayerScoreMapIt  = qvariant_cast<PlayerScoreMap::Iterator>(resultSignalUpdate.at(0));

    EXPECT_EQ(resultSize,               2);
    EXPECT_EQ(resultIsNewRecord1,       true);
    EXPECT_EQ(resultIsNewRecord2,       true);
    EXPECT_EQ(resultFindInerator,       expectedIterator);
    EXPECT_EQ(resultSignalUpdateCount,  1);
    EXPECT_EQ(resultSignalUpdate.at(1), 2);
    EXPECT_EQ(resultPlayerScoreMapIt,   expectedIterator);
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddThreeNewRecordsCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMap::Iterator>();
    PlayerScore    newRecord1(1000, "Bob");
    PlayerScore    newRecord2( 900, "Andy");
    PlayerScore    newRecord3(1200, "Ed");
    MenuModelTests menuModel;
    auto           expectedIterator = menuModel.getHighScore().begin();
    QSignalSpy     signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    menuModel.addRecordToHighScore(newRecord3);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    bool resultIsNewRecord3      = resultHighScore.contains(newRecord3.first, newRecord3.second);
    auto resultFindInerator1     = resultHighScore.find(newRecord1.first, newRecord1.second);
    auto resultFindInerator2     = resultHighScore.find(newRecord2.first, newRecord2.second);
    auto resultFindInerator3     = resultHighScore.find(newRecord3.first, newRecord3.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeFirst();
    auto resultPlayerScoreMapIt  = qvariant_cast<PlayerScoreMap::Iterator>(resultSignalUpdate.at(0));

    EXPECT_EQ(resultSize,               3);
    EXPECT_EQ(resultIsNewRecord1,       true);
    EXPECT_EQ(resultIsNewRecord2,       true);
    EXPECT_EQ(resultIsNewRecord3,       true);
    EXPECT_EQ(resultFindInerator1,      expectedIterator + 1);
    EXPECT_EQ(resultFindInerator2,      expectedIterator + 2);
    EXPECT_EQ(resultFindInerator3,      expectedIterator);
    EXPECT_EQ(resultSignalUpdateCount,  1);
    EXPECT_EQ(resultSignalUpdate.at(1), 3);
    EXPECT_EQ(resultPlayerScoreMapIt,   expectedIterator);
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddThreeNewRecordsWithTheSamePlayerNameCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMap::Iterator>();
    PlayerScore    newRecord1(1000, "Bob");
    PlayerScore    newRecord2( 900, "Bob");
    PlayerScore    newRecord3(1200, "Bob");
    MenuModelTests menuModel;
    auto           expectedIterator = menuModel.getHighScore().begin();
    QSignalSpy     signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    menuModel.addRecordToHighScore(newRecord3);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    bool resultIsNewRecord3      = resultHighScore.contains(newRecord3.first, newRecord3.second);
    auto resultFindInerator1     = resultHighScore.find(newRecord1.first, newRecord1.second);
    auto resultFindInerator2     = resultHighScore.find(newRecord2.first, newRecord2.second);
    auto resultFindInerator3     = resultHighScore.find(newRecord3.first, newRecord3.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeFirst();
    auto resultPlayerScoreMapIt  = qvariant_cast<PlayerScoreMap::Iterator>(resultSignalUpdate.at(0));

    EXPECT_EQ(resultSize,               3);
    EXPECT_EQ(resultIsNewRecord1,       true);
    EXPECT_EQ(resultIsNewRecord2,       true);
    EXPECT_EQ(resultIsNewRecord3,       true);
    EXPECT_EQ(resultFindInerator1,      expectedIterator + 1);
    EXPECT_EQ(resultFindInerator2,      expectedIterator + 2);
    EXPECT_EQ(resultFindInerator3,      expectedIterator);
    EXPECT_EQ(resultSignalUpdateCount,  1);
    EXPECT_EQ(resultSignalUpdate.at(1), 3);
    EXPECT_EQ(resultPlayerScoreMapIt,   expectedIterator);
}

TEST_F(MenuModelTestsClass, AddRecordToHighScore_AddThreeNewRecordsWithTheSameScoreNameCheckOrderByScoreAndIfUpdateSignalWasSent_IsEqual)
{
    qRegisterMetaType<PlayerScoreMap::Iterator>();
    PlayerScore    newRecord1(1000, "Bob");
    PlayerScore    newRecord2(1000, "Andy");
    PlayerScore    newRecord3(1000, "Ed");
    MenuModelTests menuModel;
    auto           expectedIterator = menuModel.getHighScore().begin();
    QSignalSpy     signalUpdate(&menuModel, &MenuModelTests::updateHighScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    menuModel.addRecordToHighScore(newRecord1);
    menuModel.addRecordToHighScore(newRecord2);
    menuModel.addRecordToHighScore(newRecord3);
    auto resultHighScore         = menuModel.getHighScore();
    int  resultSize              = resultHighScore.size();
    bool resultIsNewRecord1      = resultHighScore.contains(newRecord1.first, newRecord1.second);
    bool resultIsNewRecord2      = resultHighScore.contains(newRecord2.first, newRecord2.second);
    bool resultIsNewRecord3      = resultHighScore.contains(newRecord3.first, newRecord3.second);
    auto resultFindInerator1     = resultHighScore.find(newRecord1.first, newRecord1.second);
    auto resultFindInerator2     = resultHighScore.find(newRecord2.first, newRecord2.second);
    auto resultFindInerator3     = resultHighScore.find(newRecord3.first, newRecord3.second);
    int  resultSignalUpdateCount = signalUpdate.count();
    auto resultSignalUpdate      = signalUpdate.takeFirst();
    auto resultPlayerScoreMapIt  = qvariant_cast<PlayerScoreMap::Iterator>(resultSignalUpdate.at(0));

    EXPECT_EQ(resultSize,               3);
    EXPECT_EQ(resultIsNewRecord1,       true);
    EXPECT_EQ(resultIsNewRecord2,       true);
    EXPECT_EQ(resultIsNewRecord3,       true);
    EXPECT_EQ(resultFindInerator1,      expectedIterator + 1);
    EXPECT_EQ(resultFindInerator2,      expectedIterator);
    EXPECT_EQ(resultFindInerator3,      expectedIterator + 3);
    EXPECT_EQ(resultSignalUpdateCount,  1);
    EXPECT_EQ(resultSignalUpdate.at(1), 3);
    EXPECT_EQ(resultPlayerScoreMapIt,   expectedIterator);
}
