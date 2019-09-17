#include "generalview.hpp"
#include "definitions.hpp"

GeneralView::GeneralView() :
                         m_scene(0, 0, def::sceneWight, def::sceneHeight),
                         m_title("GALACTIC WAR"),
                         m_author("Created by TED"),
                         m_startButton("MENU"),
                         m_highScoreButton("HIGH SCORE"),
                         m_quitButton("QUIT"),
                         m_backToMenuButton("BACK"),
                         m_saveAfterGameOver("SAVE")
{
    menu();
}

GeneralView::~GeneralView()
{

}

void GeneralView::menu()
{
    m_title.setVisible(true);
    m_author.setVisible(true);
    m_pause.setVisible(false);
    m_startButton.setVisible(true);
    m_highScoreButton.setVisible(true);
    m_quitButton.setVisible(true);
    m_backToMenuButton.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_highScoreList.setVisible(false);
}

void GeneralView::startGame()
{
    m_title.setVisible(false);
    m_author.setVisible(false);
    m_pause.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_highScoreList.setVisible(false);
}

void GeneralView::pause()
{
    m_title.setVisible(false);
    m_author.setVisible(false);
    m_pause.setVisible(true);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_highScoreList.setVisible(false);
}

void GeneralView::gameOver()
{
    m_title.setVisible(false);
    m_author.setVisible(true);
    m_pause.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(true);
    m_saveAfterGameOver.setVisible(true);
    m_highScoreList.setVisible(false);
}

void GeneralView::highScore()
{
    m_title.setVisible(true);
    m_author.setVisible(true);
    m_pause.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(true);
    m_saveAfterGameOver.setVisible(false);
    m_highScoreList.setVisible(true);
}

void GeneralView::addGameObject(QGraphicsItem* newObject)
{
    m_scene.addItem(newObject);
}
