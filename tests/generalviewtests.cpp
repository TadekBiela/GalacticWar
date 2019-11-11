#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/generalview.hpp"
#include "../app/graphicsview.hpp"
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QSignalSpy>
#include <QString>
#include <QProgressBar>
#include <QKeyEvent>

Q_DECLARE_METATYPE(PlayerScore)

class GeneralViewTests : public GeneralView
{
public:
    GeneralViewTests() {}
    virtual ~GeneralViewTests() {}

    const QGraphicsScene& getScene()                   { return m_scene; }
    const GraphicsView&   getView()                    { return m_view; }
    const QLabel&         getTitle()                   { return m_title; }
    const QLabel&         getAuthor()                  { return m_author; }
    const QLabel&         getPause()                   { return m_pause; }
    const QLineEdit&      getPlayer()                  { return m_player; }
    const QLabel&         getScore()                   { return m_score; }
    const QPushButton&    getStartButton()             { return m_startButton; }
    const QPushButton&    getHighScoreButton()         { return m_highScoreButton; }
    const QPushButton&    getQuitButton()              { return m_quitButton; }
    const QPushButton&    getBackToMenuButton()        { return m_backToMenuButton; }
    const QPushButton&    getBackToMenuButton2()       { return m_backToMenuButton2; }
    const QPushButton&    getSaveAfterGameOverButton() { return m_saveAfterGameOver; }
    const QListWidget&    getHighScoreList()           { return m_highScoreList; }
    const QLabel&         getHealthGraphics()          { return m_healthGraphics; }
    const QProgressBar&   getHealthBar()               { return m_healthBar; }
    const QLabel&         getLevelGraphics()           { return m_levelGraphics; }
    const QLabel&         getLevelText()               { return m_levelText; }
    const QLabel&         getScoreGraphics()           { return m_scoreGraphics; }
    const QProgressBar&   getScoreBar()                { return m_scoreBar; }
    void addItemToScene(QGraphicsItem* item) { m_scene.addItem(item); }
    void setPlayer(QString player)  { m_player.setText(player); }
    void setScore(int score)        { m_score.setText(QString::number(score)); }
};

class GeneralViewTestsClass : public testing::Test
{
};

TEST_F(GeneralViewTestsClass, Menu_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    generalView.show();

    generalView.menu();
    const GraphicsView& resultView                    = generalView.getView();
    const QLabel&       resultTitle                   = generalView.getTitle();
    const QLabel&       resultAuthor                  = generalView.getAuthor();
    const QLabel&       resultPause                   = generalView.getPause();
    const QLineEdit&    resultPlayer                  = generalView.getPlayer();
    const QLabel&       resultScore                   = generalView.getScore();
    const QPushButton&  resultStartButton             = generalView.getStartButton();
    const QPushButton&  resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton&  resultQuitButton              = generalView.getQuitButton();
    const QPushButton&  resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton&  resultBackToMenuButton2       = generalView.getBackToMenuButton2();
    const QPushButton&  resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget&  resultHighScoreList           = generalView.getHighScoreList();
    const QLabel&       resultHealthGraphics          = generalView.getHealthGraphics();
    const QProgressBar& resultHealthBar               = generalView.getHealthBar();
    const QLabel&       resultLevelGraphics           = generalView.getLevelGraphics();
    const QLabel&       resultLevelText               = generalView.getLevelText();
    const QLabel&       resultScoreGraphics           = generalView.getScoreGraphics();
    const QProgressBar& resultScoreBar                = generalView.getScoreBar();

    EXPECT_EQ(resultView.isVisible(),                    false);
    EXPECT_EQ(resultTitle.isVisible(),                   true);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             true);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         true);
    EXPECT_EQ(resultQuitButton.isVisible(),              true);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultBackToMenuButton2.isVisible(),       false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
    EXPECT_EQ(resultHealthGraphics.isVisible(),          false);
    EXPECT_EQ(resultHealthBar.isVisible(),               false);
    EXPECT_EQ(resultLevelGraphics.isVisible(),           false);
    EXPECT_EQ(resultLevelText.isVisible(),               false);
    EXPECT_EQ(resultScoreGraphics.isVisible(),           false);
    EXPECT_EQ(resultScoreBar.isVisible(),                false);
}

TEST_F(GeneralViewTestsClass, Start_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    generalView.show();
    QSignalSpy       signalStart(&generalView, &GeneralViewTests::startGame);
    signalStart.wait(utdef::minSignalTimeDelay);

    generalView.start();
    const GraphicsView& resultView                    = generalView.getView();
    const QLabel&       resultTitle                   = generalView.getTitle();
    const QLabel&       resultAuthor                  = generalView.getAuthor();
    const QLabel&       resultPause                   = generalView.getPause();
    const QLineEdit&    resultPlayer                  = generalView.getPlayer();
    const QLabel&       resultScore                   = generalView.getScore();
    const QPushButton&  resultStartButton             = generalView.getStartButton();
    const QPushButton&  resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton&  resultQuitButton              = generalView.getQuitButton();
    const QPushButton&  resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton&  resultBackToMenuButton2       = generalView.getBackToMenuButton2();
    const QPushButton&  resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget&  resultHighScoreList           = generalView.getHighScoreList();
    const QLabel&       resultHealthGraphics          = generalView.getHealthGraphics();
    const QProgressBar& resultHealthBar               = generalView.getHealthBar();
    const QLabel&       resultLevelGraphics           = generalView.getLevelGraphics();
    const QLabel&       resultLevelText               = generalView.getLevelText();
    const QLabel&       resultScoreGraphics           = generalView.getScoreGraphics();
    const QProgressBar& resultScoreBar                = generalView.getScoreBar();
    int                 resultSignalStartCount        = signalStart.count();

    EXPECT_EQ(resultView.isVisible(),                    true);
    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  false);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultBackToMenuButton2.isVisible(),       false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
    EXPECT_EQ(resultHealthGraphics.isVisible(),          true);
    EXPECT_EQ(resultHealthBar.isVisible(),               true);
    EXPECT_EQ(resultLevelGraphics.isVisible(),           true);
    EXPECT_EQ(resultLevelText.isVisible(),               true);
    EXPECT_EQ(resultScoreGraphics.isVisible(),           true);
    EXPECT_EQ(resultScoreBar.isVisible(),                true);
    EXPECT_EQ(resultSignalStartCount,                    1);
}

TEST_F(GeneralViewTestsClass, Pause_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    generalView.show();

    generalView.pause();
    const GraphicsView& resultView                    = generalView.getView();
    const QLabel&       resultTitle                   = generalView.getTitle();
    const QLabel&       resultAuthor                  = generalView.getAuthor();
    const QLabel&       resultPause                   = generalView.getPause();
    const QLineEdit&    resultPlayer                  = generalView.getPlayer();
    const QLabel&       resultScore                   = generalView.getScore();
    const QPushButton&  resultStartButton             = generalView.getStartButton();
    const QPushButton&  resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton&  resultQuitButton              = generalView.getQuitButton();
    const QPushButton&  resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton&  resultBackToMenuButton2       = generalView.getBackToMenuButton2();
    const QPushButton&  resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget&  resultHighScoreList           = generalView.getHighScoreList();
    const QLabel&       resultHealthGraphics          = generalView.getHealthGraphics();
    const QProgressBar& resultHealthBar               = generalView.getHealthBar();
    const QLabel&       resultLevelGraphics           = generalView.getLevelGraphics();
    const QLabel&       resultLevelText               = generalView.getLevelText();
    const QLabel&       resultScoreGraphics           = generalView.getScoreGraphics();
    const QProgressBar& resultScoreBar                = generalView.getScoreBar();

    EXPECT_EQ(resultView.isVisible(),                    true);
    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  false);
    EXPECT_EQ(resultPause.isVisible(),                   true);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
    EXPECT_EQ(resultHealthGraphics.isVisible(),          false);
    EXPECT_EQ(resultHealthBar.isVisible(),               false);
    EXPECT_EQ(resultLevelGraphics.isVisible(),           false);
    EXPECT_EQ(resultLevelText.isVisible(),               false);
    EXPECT_EQ(resultScoreGraphics.isVisible(),           false);
    EXPECT_EQ(resultScoreBar.isVisible(),                false);
}

TEST_F(GeneralViewTestsClass, GameOver_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    generalView.show();

    generalView.gameOver(100);
    const GraphicsView& resultView                    = generalView.getView();
    const QLabel&       resultTitle                   = generalView.getTitle();
    const QLabel&       resultAuthor                  = generalView.getAuthor();
    const QLabel&       resultPause                   = generalView.getPause();
    const QLineEdit&    resultPlayer                  = generalView.getPlayer();
    const QLabel&       resultScore                   = generalView.getScore();
    const QPushButton&  resultStartButton             = generalView.getStartButton();
    const QPushButton&  resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton&  resultQuitButton              = generalView.getQuitButton();
    const QPushButton&  resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton&  resultBackToMenuButton2       = generalView.getBackToMenuButton2();
    const QPushButton&  resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget&  resultHighScoreList           = generalView.getHighScoreList();
    const QLabel&       resultHealthGraphics          = generalView.getHealthGraphics();
    const QProgressBar& resultHealthBar               = generalView.getHealthBar();
    const QLabel&       resultLevelGraphics           = generalView.getLevelGraphics();
    const QLabel&       resultLevelText               = generalView.getLevelText();
    const QLabel&       resultScoreGraphics           = generalView.getScoreGraphics();
    const QProgressBar& resultScoreBar                = generalView.getScoreBar();

    EXPECT_EQ(resultScore.text(),                        QString("100"));
    EXPECT_EQ(resultView.isVisible(),                    false);
    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  true);
    EXPECT_EQ(resultScore.isVisible(),                   true);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        false);
    EXPECT_EQ(resultBackToMenuButton2.isVisible(),       true);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), true);
    EXPECT_EQ(resultHighScoreList.isVisible(),           false);
    EXPECT_EQ(resultHealthGraphics.isVisible(),          false);
    EXPECT_EQ(resultHealthBar.isVisible(),               false);
    EXPECT_EQ(resultLevelGraphics.isVisible(),           false);
    EXPECT_EQ(resultLevelText.isVisible(),               false);
    EXPECT_EQ(resultScoreGraphics.isVisible(),           false);
    EXPECT_EQ(resultScoreBar.isVisible(),                false);
}

TEST_F(GeneralViewTestsClass, GameOver_AllGameObjectsShouldBeRemovedFromScene_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);
    EnemyModelType1* enemyModel = new EnemyModelType1(QPointF(2, 7), randomGenerator);
    RewardCoinModel* rewardCoinModel = new RewardCoinModel(coin_type::bronze);
    GeneralViewTests generalView;
    generalView.show();
    generalView.addItemToScene(enemyModel);
    generalView.addItemToScene(rewardCoinModel);
    const QGraphicsScene& scene = generalView.getScene();
    int numOfSceneItemsShouldBeTwo = scene.items().size();

    generalView.gameOver(100);
    int resultNumOfSceneItems = scene.items().size();

    EXPECT_EQ(numOfSceneItemsShouldBeTwo, 2);
    EXPECT_EQ(resultNumOfSceneItems,      0);
}

TEST_F(GeneralViewTestsClass, HighScore_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;
    generalView.show();

    generalView.highScore();
    const GraphicsView& resultView                    = generalView.getView();
    const QLabel&       resultTitle                   = generalView.getTitle();
    const QLabel&       resultAuthor                  = generalView.getAuthor();
    const QLabel&       resultPause                   = generalView.getPause();
    const QLineEdit&    resultPlayer                  = generalView.getPlayer();
    const QLabel&       resultScore                   = generalView.getScore();
    const QPushButton&  resultStartButton             = generalView.getStartButton();
    const QPushButton&  resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton&  resultQuitButton              = generalView.getQuitButton();
    const QPushButton&  resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton&  resultBackToMenuButton2       = generalView.getBackToMenuButton2();
    const QPushButton&  resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget&  resultHighScoreList           = generalView.getHighScoreList();
    const QLabel&       resultHealthGraphics          = generalView.getHealthGraphics();
    const QProgressBar& resultHealthBar               = generalView.getHealthBar();
    const QLabel&       resultLevelGraphics           = generalView.getLevelGraphics();
    const QLabel&       resultLevelText               = generalView.getLevelText();
    const QLabel&       resultScoreGraphics           = generalView.getScoreGraphics();
    const QProgressBar& resultScoreBar                = generalView.getScoreBar();

    EXPECT_EQ(resultView.isVisible(),                    false);
    EXPECT_EQ(resultTitle.isVisible(),                   true);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultPlayer.isVisible(),                  false);
    EXPECT_EQ(resultScore.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        true);
    EXPECT_EQ(resultBackToMenuButton2.isVisible(),       false);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           true);
    EXPECT_EQ(resultHealthGraphics.isVisible(),          false);
    EXPECT_EQ(resultHealthBar.isVisible(),               false);
    EXPECT_EQ(resultLevelGraphics.isVisible(),           false);
    EXPECT_EQ(resultLevelText.isVisible(),               false);
    EXPECT_EQ(resultScoreGraphics.isVisible(),           false);
    EXPECT_EQ(resultScoreBar.isVisible(),                false);
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

TEST_F(GeneralViewTestsClass, KeyPressEvent_EscKeyPressedCheckIfPauseWillBeOn_IsEqual)
{
    QKeyEvent        event(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
    GeneralViewTests generalView;
    QSignalSpy       signalEsc(&generalView, &GeneralViewTests::escPressed);
    signalEsc.wait(utdef::minSignalTimeDelay);

    generalView.keyPressEvent(&event);
    int resultSignalEscCount = signalEsc.count();

    EXPECT_EQ(resultSignalEscCount, 1);
}

TEST_F(GeneralViewTestsClass, KeyPressEvent_OtherKeyPressedShouldDoNothing_IsEqual)
{
    QKeyEvent        event(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
    GeneralViewTests generalView;
    QSignalSpy       signalEsc(&generalView, &GeneralViewTests::escPressed);
    signalEsc.wait(utdef::minSignalTimeDelay);

    generalView.keyPressEvent(&event);
    int resultSignalEscCount = signalEsc.count();

    EXPECT_EQ(resultSignalEscCount, 0);
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

TEST_F(GeneralViewTestsClass, UpdateHealth_UpdateWithValue0_IsZero)
{
    GeneralViewTests generalView;

    generalView.updateHealth(0);
    const QProgressBar& resultHealthBar = generalView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 0);
}

TEST_F(GeneralViewTestsClass, UpdateHealth_UpdateWithValue30_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateHealth(30);
    const QProgressBar& resultHealthBar = generalView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 30);
}

TEST_F(GeneralViewTestsClass, UpdateHealth_UpdateWithMaxValue_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateHealth(100);
    const QProgressBar& resultHealthBar = generalView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 100);
}

TEST_F(GeneralViewTestsClass, UpdateHealth_UpdateWithMoreThanMaxValueShouldntIncreaseMoreThanMax_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateHealth(120);
    const QProgressBar& resultHealthBar = generalView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 100);
}

TEST_F(GeneralViewTestsClass, UpdateLevel_UpdateWithValue1_IsOne)
{
    GeneralViewTests generalView;

    generalView.updateLevel(1);
    const QLabel& resultLevelText = generalView.getLevelText();

    EXPECT_EQ(resultLevelText.text().toStdString(), "1");
}

TEST_F(GeneralViewTestsClass, UpdateLevel_UpdateWithValueMax_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateLevel(def::maxNumOfLevel);
    const QLabel& resultLevelText = generalView.getLevelText();

    EXPECT_EQ(resultLevelText.text().toStdString(), "10");
}

TEST_F(GeneralViewTestsClass, UpdateScore_UpdateWithValue0_IsZero)
{
    GeneralViewTests generalView;

    generalView.updateScore(0);
    const QProgressBar& resultScoreBar = generalView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 0);
}

TEST_F(GeneralViewTestsClass, UpdateScore_UpdateWithValue30_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateScore(30);
    const QProgressBar& resultScoreBar = generalView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 30);
}

TEST_F(GeneralViewTestsClass, UpdateScore_UpdateWithMaxValue_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateScore(100);
    const QProgressBar& resultScoreBar = generalView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 100);
}

TEST_F(GeneralViewTestsClass, UpdateScore_UpdateWithMoreThanMaxValueShouldntIncreaseMoreThanMax_IsEqual)
{
    GeneralViewTests generalView;

    generalView.updateScore(120);
    const QProgressBar& resultScoreBar = generalView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 100);
}
