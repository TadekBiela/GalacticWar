#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/generalview.hpp"
#include "../app/definitions.hpp"
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
    const QLabel&      getTitle()                   { return m_title; }
    const QLabel&      getAuthor()                  { return m_author; }
    const QLabel&      getPause()                   { return m_pause; }
    const QLabel&      getPlayer()                  { return m_player; }
    const QLabel&      getScore()                   { return m_score; }
    const QPushButton& getStartButton()             { return m_startButton; }
    const QPushButton& getHighScoreButton()         { return m_highScoreButton; }
    const QPushButton& getQuitButton()              { return m_quitButton; }
    const QPushButton& getBackToMenuButton()        { return m_backToMenuButton; }
    const QPushButton& getSaveAfterGameOverButton() { return m_saveAfterGameOver; }
    const QListWidget& getHighScoreList()           { return m_highScoreList; }
    void setPlayer(QString player)                  { m_player.setText(player); }
    void setScore(int score)                        { m_score.setText(QString::number(score)); }
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

TEST_F(GeneralViewTestsClass, StartGame_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;

    generalView.startGame();
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
}

TEST_F(GeneralViewTestsClass, Pause_CheckCorrectVisibleUI_IsEqual)
{
    GeneralViewTests generalView;

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
