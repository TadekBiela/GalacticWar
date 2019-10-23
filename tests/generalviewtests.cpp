#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/generalview.hpp"
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QEvent>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QSignalSpy>
#include <QString>

Q_DECLARE_METATYPE(PlayerScore)

class GeneralViewTests : public GeneralView
{
public:
    GeneralViewTests() {}
    virtual ~GeneralViewTests() {}

    const QGraphicsScene& getScene()                   { return m_scene; }
    const QLabel&         getTitle()                   { return m_title; }
    const QLabel&         getAuthor()                  { return m_author; }
    const QLabel&         getPause()                   { return m_pause; }
    const QLabel&         getPlayer()                  { return m_player; }
    const QLabel&         getScore()                   { return m_score; }
    const QPushButton&    getStartButton()             { return m_startButton; }
    const QPushButton&    getHighScoreButton()         { return m_highScoreButton; }
    const QPushButton&    getQuitButton()              { return m_quitButton; }
    const QPushButton&    getBackToMenuButton()        { return m_backToMenuButton; }
    const QPushButton&    getSaveAfterGameOverButton() { return m_saveAfterGameOver; }
    const QListWidget&    getHighScoreList()           { return m_highScoreList; }
    void setPlayer(QString player)  { m_player.setText(player); }
    void setScore(int score)        { m_score.setText(QString::number(score)); }
};

class GeneralViewTestsClass : public testing::Test
{
};

TEST_F(GeneralViewTestsClass, Menu_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;

    generalView.menu();
    const QLabel&      resultTitle                   = generalView.getTitle();
    const QLabel&      resultAuthor                  = generalView.getAuthor();
    const QLabel&      resultPause                   = generalView.getPause();
    const QLabel&      resultPlayer                  = generalView.getPlayer();
    const QLabel&      resultScore                   = generalView.getScore();
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   true);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             true);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         true);
    EXPECT_EQ(resultQuitButton.isVisible(),              true);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
}

TEST_F(GeneralViewTestsClass, Start_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    QSignalSpy       signalStart(&generalView, &GeneralViewTests::startGame);
    signalStart.wait(utdef::minSignalTimeDelay);

    generalView.start();
    const QLabel&      resultTitle                   = generalView.getTitle();
    const QLabel&      resultAuthor                  = generalView.getAuthor();
    const QLabel&      resultPause                   = generalView.getPause();
    const QLabel&      resultPlayer                  = generalView.getPlayer();
    const QLabel&      resultScore                   = generalView.getScore();
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();
    int                resultSignalStartCount        = signalStart.count();

    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  false);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
    EXPECT_EQ(resultSignalStartCount,                    1);
}

TEST_F(GeneralViewTestsClass, Pause_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    QSignalSpy       signalPause(&generalView, &GeneralViewTests::pauseGame);
    signalPause.wait(utdef::minSignalTimeDelay);

    generalView.pause();
    const QLabel&      resultTitle                   = generalView.getTitle();
    const QLabel&      resultAuthor                  = generalView.getAuthor();
    const QLabel&      resultPause                   = generalView.getPause();
    const QLabel&      resultPlayer                  = generalView.getPlayer();
    const QLabel&      resultScore                   = generalView.getScore();
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();
    int                resultSignalPauseCount        = signalPause.count();

    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  false);
    EXPECT_EQ(resultPause.isVisible(),                   true);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
    EXPECT_EQ(resultSignalPauseCount,                    1);
}

TEST_F(GeneralViewTestsClass, GameOver_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;

    generalView.gameOver(100);
    const QLabel&      resultTitle                   = generalView.getTitle();
    const QLabel&      resultAuthor                  = generalView.getAuthor();
    const QLabel&      resultPause                   = generalView.getPause();
    const QLabel&      resultPlayer                  = generalView.getPlayer();
    const QLabel&      resultScore                   = generalView.getScore();
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultScore.text(),                        QString("100"));
    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  true);
    EXPECT_EQ(resultScore.isVisible(),                   true);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        true);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), true);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
}

TEST_F(GeneralViewTestsClass, HighScore_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;

    generalView.highScore();
    const QLabel&      resultTitle                   = generalView.getTitle();
    const QLabel&      resultAuthor                  = generalView.getAuthor();
    const QLabel&      resultPause                   = generalView.getPause();
    const QLabel&      resultPlayer                  = generalView.getPlayer();
    const QLabel&      resultScore                   = generalView.getScore();
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   true);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        true);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           true);
}

TEST_F(GeneralViewTestsClass, AddGameObject_AddPlayerModelCheckIfWillAddedCorrect_IsEqual)
{
    PlayerModel*     player = new PlayerModel;
    GeneralViewTests generalView;

    generalView.addGameObject(player);
    const QGraphicsScene& resultScene      = generalView.getScene();
    auto                  resultSceneItems = resultScene.items();
    PlayerModel*          resultPlayer     = dynamic_cast<PlayerModel*>(resultSceneItems.at(0));

    EXPECT_EQ(resultSceneItems.size(),   1);
    EXPECT_EQ(resultPlayer->getHealth(), def::maxPlayerHealth);
}

TEST_F(GeneralViewTestsClass, AddGameObject_AddEnemyModelType1CheckIfWillAddedCorrect_IsEqual)
{
    RandomGeneratorStub* generator = new RandomGeneratorStub;
    EnemyModelType1*     enemy     = new EnemyModelType1(QPointF(0,0), generator);
    GeneralViewTests     generalView;

    generalView.addGameObject(enemy);
    const QGraphicsScene& resultScene      = generalView.getScene();
    auto                  resultSceneItems = resultScene.items();
    EnemyModelType1*      resultEnemy      = dynamic_cast<EnemyModelType1*>(resultSceneItems.at(0));

    EXPECT_EQ(resultSceneItems.size(), 1);
    EXPECT_EQ(resultEnemy->getLevel(), 1);
    delete generator;
}

TEST_F(GeneralViewTestsClass, AddGameObject_AddRewardCoinModelCheckIfWillAddedCorrect_IsEqual)
{
    RewardCoinModel* coin = new RewardCoinModel(coin_type::gold);
    GeneralViewTests generalView;

    generalView.addGameObject(coin);
    const QGraphicsScene& resultScene      = generalView.getScene();
    auto                  resultSceneItems = resultScene.items();
    RewardCoinModel*      resultCoin       = dynamic_cast<RewardCoinModel*>(resultSceneItems.at(0));

    EXPECT_EQ(resultSceneItems.size(), 1);
    EXPECT_EQ(resultCoin->getType(),   coin_type::gold);
}

TEST_F(GeneralViewTestsClass, AddGameObject_AddRewardSpecialModelCheckIfWillAddedCorrect_IsEqual)
{
    RewardSpecialModel* special = new RewardSpecialModel(special_type::weaponBlue);
    GeneralViewTests    generalView;

    generalView.addGameObject(special);
    const QGraphicsScene& resultScene      = generalView.getScene();
    auto                  resultSceneItems = resultScene.items();
    RewardSpecialModel*   resultspecial    = dynamic_cast<RewardSpecialModel*>(resultSceneItems.at(0));

    EXPECT_EQ(resultSceneItems.size(),  1);
    EXPECT_EQ(resultspecial->getType(), special_type::weaponBlue);
}

TEST_F(GeneralViewTestsClass, MousePressEvent_CheckIfSignalWillBeSend_IsEqual)
{
    QMouseEvent      event(QEvent::MouseButtonPress,
                           QPointF(0, 0),
                           Qt::LeftButton,
                           Qt::LeftButton,
                           Qt::NoModifier);
    GeneralViewTests generalView;
    QSignalSpy       signalPressed(&generalView, &GeneralViewTests::mousePressed);
    signalPressed.wait(utdef::minSignalTimeDelay);

    generalView.mousePressEvent(&event);
    int resultSignalPressedCount = signalPressed.count();

    EXPECT_EQ(resultSignalPressedCount, 1);
}

TEST_F(GeneralViewTestsClass, MouseReleaseEvent_CheckIfSignalWillBeSend_IsEqual)
{
    QMouseEvent      event(QEvent::MouseButtonRelease,
                           QPointF(0, 0),
                           Qt::LeftButton,
                           Qt::LeftButton,
                           Qt::NoModifier);
    GeneralViewTests generalView;
    QSignalSpy       signalReleased(&generalView, &GeneralViewTests::mouseReleased);
    signalReleased.wait(utdef::minSignalTimeDelay);

    generalView.mouseReleaseEvent(&event);
    int resultSignalReleasedCount = signalReleased.count();

    EXPECT_EQ(resultSignalReleasedCount, 1);
}

TEST_F(GeneralViewTestsClass, MouseMoveEvent_CheckIfSignalWillBeSend_IsEqual)
{
    const QPointF    expectedPosition(100, 400);
    QMouseEvent      event(QEvent::MouseMove,
                           expectedPosition,
                           Qt::LeftButton,
                           Qt::LeftButton,
                           Qt::NoModifier);
    GeneralViewTests generalView;
    QSignalSpy       signalMoved(&generalView, &GeneralViewTests::mouseMoved);
    signalMoved.wait(utdef::minSignalTimeDelay);

    generalView.mouseMoveEvent(&event);
    int resultSignalMovedCount = signalMoved.count();
    QPointF resultPosition = signalMoved.takeFirst().at(0).toPointF();

    EXPECT_EQ(resultSignalMovedCount,   1);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(GeneralViewTestsClass, SavePlayerScore_CheckIfSignalWillBeSendWithCorrectPlayerScore_IsEqual)
{
    qRegisterMetaType<PlayerScore>();
    int     expectedPlayerScoreValue = 1250;
    QString expectedPlayerName("Eddy");
    GeneralViewTests generalView;
    generalView.setScore(expectedPlayerScoreValue);
    generalView.setPlayer(expectedPlayerName);
    QSignalSpy signalSave(&generalView, &GeneralViewTests::save);
    signalSave.wait(utdef::minSignalTimeDelay);

    generalView.savePlayerScore();
    int  resultSignalMovedCount = signalSave.count();
    auto resultPlayerScore      = qvariant_cast<PlayerScore>(signalSave.takeFirst().at(0));

    EXPECT_EQ(resultSignalMovedCount,   1);
    EXPECT_EQ(resultPlayerScore.first,  expectedPlayerScoreValue);
    EXPECT_EQ(resultPlayerScore.second, expectedPlayerName);
}

TEST_F(GeneralViewTestsClass, UpdateHighScoreList_SizeOfListIs0ListShouldHaveOnlyTitles_IsEqual)
{
    PlayerScoreMap         input;
    PlayerScoreMapIterator iterator = input.end();
    GeneralViewTests generalView;

    generalView.updateHighScoreList(iterator, input.size());
    const QListWidget&     resultHighScoreList = generalView.getHighScoreList();
    const QListWidgetItem* resultListItem0     = resultHighScoreList.item(0);

    EXPECT_EQ(resultHighScoreList.count(),           1);
    EXPECT_EQ(resultListItem0->text().toStdString(), "Player\t\t\tScore");
}

TEST_F(GeneralViewTestsClass, UpdateHighScoreList_SizeOfListIs1ListShouldHaveTitlesAndOneRecord_IsEqual)
{
    PlayerScoreMap input;
    input.insert(100, "Andy");
    PlayerScoreMapIterator iterator = input.end();
    GeneralViewTests generalView;

    generalView.updateHighScoreList(iterator, input.size());
    const QListWidget&     resultHighScoreList = generalView.getHighScoreList();
    const QListWidgetItem* resultListItem0     = resultHighScoreList.item(0);
    const QListWidgetItem* resultListItem1     = resultHighScoreList.item(1);

    EXPECT_EQ(resultHighScoreList.count(),           2);
    EXPECT_EQ(resultListItem0->text().toStdString(), "Player\t\t\tScore");
    EXPECT_EQ(resultListItem1->text().toStdString(), "Andy\t\t\t100");
}

TEST_F(GeneralViewTestsClass, UpdateHighScoreList_SizeOfListIs5ListShouldHaveTitlesAnd5Records_IsEqual)
{
    PlayerScoreMap input;
    input.insert(500, "Andy");
    input.insert(400, "Mendy");
    input.insert(100, "Andy");
    input.insert(50,  "Bob");
    input.insert(0,   "Mendy");
    PlayerScoreMapIterator iterator = input.end();
    GeneralViewTests generalView;

    generalView.updateHighScoreList(iterator, input.size());
    const QListWidget&     resultHighScoreList = generalView.getHighScoreList();
    const QListWidgetItem* resultListItem0     = resultHighScoreList.item(0);
    const QListWidgetItem* resultListItem1     = resultHighScoreList.item(1);
    const QListWidgetItem* resultListItem2     = resultHighScoreList.item(2);
    const QListWidgetItem* resultListItem3     = resultHighScoreList.item(3);
    const QListWidgetItem* resultListItem4     = resultHighScoreList.item(4);
    const QListWidgetItem* resultListItem5     = resultHighScoreList.item(5);

    EXPECT_EQ(resultHighScoreList.count(),           6);
    EXPECT_EQ(resultListItem0->text().toStdString(), "Player\t\t\tScore");
    EXPECT_EQ(resultListItem1->text().toStdString(), "Andy\t\t\t500");
    EXPECT_EQ(resultListItem2->text().toStdString(), "Mendy\t\t\t400");
    EXPECT_EQ(resultListItem3->text().toStdString(), "Andy\t\t\t100");
    EXPECT_EQ(resultListItem4->text().toStdString(), "Bob\t\t\t50");
    EXPECT_EQ(resultListItem5->text().toStdString(), "Mendy\t\t\t0");
}
