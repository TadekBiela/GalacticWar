#include "generalview.hpp"
#include "definitions.hpp"

GeneralView::GeneralView() :
                         m_scene(0, 0, def::sceneWight, def::sceneHeight, this),
                         m_title("GALACTIC WAR", this),
                         m_author("Created by TED", this),
                         m_startButton("MENU", this),
                         m_highScoreButton("HIGH SCORE", this),
                         m_quitButton("QUIT", this),
                         m_backToMenuButton("BACK", this),
                         m_saveAfterGameOver("SAVE", this)
{

}

void GeneralView::menu()
{

}

void GeneralView::startGame()
{

}

void GeneralView::gameOver()
{

}

void GeneralView::highScore()
{

}

void GeneralView::addGameObject(QGraphicsItem* newObject)
{
    m_scene.addItem(newObject);
}
