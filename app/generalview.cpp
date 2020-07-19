#include "generalview.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"
#include "soundstorage.hpp"
#include <QString>
#include <QGraphicsEffect>
#include <QHeaderView>
#include <QScrollBar>

GeneralView::GeneralView()
                         : m_scene(0, 0, def::sceneWight, def::sceneHeight, this)
{
    setFixedSize(QSize(def::windowWight, def::windowHeight));
//    m_view.setGeometry(0, 0, def::sceneWight + 2, def::sceneHeight + 2);
//    m_view.setFixedSize(def::sceneWight + 2, def::sceneHeight + 2);

    m_arrowCursorMap.convertFromImage(*g_imageStorage->getImage("arrow_cursor"));
    m_crossCursorMap.convertFromImage(*g_imageStorage->getImage("cross_cursor"));

    QCursor arrowCursor(m_arrowCursorMap, 0, 0);
    setCursor(arrowCursor);
}

GeneralView::~GeneralView()
{

}

void GeneralView::start()
{
    QCursor crossCursor(m_crossCursorMap, 15, 15);
    setCursor(crossCursor);
    m_scene.clear();
    m_isGamePaused = false;
    emit startGame();
}

void GeneralView::pauseGame()
{
    QCursor arrowCursor(m_arrowCursorMap, 0, 0);
    setCursor(arrowCursor);
    m_isGamePaused = true;
}

void GeneralView::continueGame()
{
    QCursor crossCursor(m_crossCursorMap, 15, 15);
    setCursor(crossCursor);
    m_isGamePaused = false;
}


void GeneralView::abort()
{
    m_scene.clear();
    emit abortGame();
}

void GeneralView::gameOver(int score)
{
    m_scene.clear();
    QCursor arrowCursor(m_arrowCursorMap, 0, 0);
    setCursor(arrowCursor);
    m_isGamePaused = false;
}

void GeneralView::quitGame()
{
    emit exitGame();
}

void GeneralView::show()
{
    QWidget::show();
    resize(def::windowWight, def::windowHeight);
}
