#include <gtest/gtest.h>
#include "../app/generalview.hpp"
#include "../app/definitions.hpp"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class GeneralViewTests : public GeneralView
{
public:
    const QLabel&      getTitle()                   { return m_title; }
    const QLabel&      getAuthor()                  { return m_author; }
    const QLabel&      getPause()                   { return m_pause; }
    const QPushButton& getStartButton()             { return m_startButton; }
    const QPushButton& getHighScoreButton()         { return m_highScoreButton; }
    const QPushButton& getQuitButton()              { return m_quitButton; }
    const QPushButton& getBackToMenuButton()        { return m_backToMenuButton; }
    const QPushButton& getSaveAfterGameOverButton() { return m_saveAfterGameOver; }
    const QListWidget& getHighScoreList()           { return m_highScoreList; }
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
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   true);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
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
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  false);
    EXPECT_EQ(resultPause.isVisible(),                   false);
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
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  false);
    EXPECT_EQ(resultPause.isVisible(),                   true);
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

    generalView.gameOver();
    const QLabel&      resultTitle                   = generalView.getTitle();
    const QLabel&      resultAuthor                  = generalView.getAuthor();
    const QLabel&      resultPause                   = generalView.getPause();
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   false);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
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
    const QPushButton& resultStartButton             = generalView.getStartButton();
    const QPushButton& resultHighScoreButton         = generalView.getHighScoreButton();
    const QPushButton& resultQuitButton              = generalView.getQuitButton();
    const QPushButton& resultBackToMenuButton        = generalView.getBackToMenuButton();
    const QPushButton& resultSaveAfterGameOverButton = generalView.getSaveAfterGameOverButton();
    const QListWidget& resultHighScoreList           = generalView.getHighScoreList();

    EXPECT_EQ(resultTitle.isVisible(),                   true);
    EXPECT_EQ(resultAuthor.isVisible(),                  true);
    EXPECT_EQ(resultPause.isVisible(),                   false);
    EXPECT_EQ(resultStartButton.isVisible(),             false);
    EXPECT_EQ(resultHighScoreButton.isVisible(),         false);
    EXPECT_EQ(resultQuitButton.isVisible(),              false);
    EXPECT_EQ(resultBackToMenuButton.isVisible(),        true);
    EXPECT_EQ(resultSaveAfterGameOverButton.isVisible(), false);
    EXPECT_EQ(resultHighScoreList.isVisible(),           true);
}
