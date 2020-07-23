#include "backgroundview.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"

BackgroundView::BackgroundView(QWidget* displayWidget)
    : AnimationPlaneView(displayWidget),
      m_backgroundAnimTimeDelay(def::defaultBackgroundAnimTimeDelay),
      m_backgroundAnimTimer(),
      m_backgroundGraphics(),
      m_backgroundGraphicsPosOffset(0)
{
    QImage* backgroundImage = g_imageStorage->getImage("background");
    QPixmap backgroundPixmap;
    backgroundPixmap.convertFromImage(*backgroundImage);
    m_backgroundGraphics.setPixmap(backgroundPixmap);
    m_backgroundGraphics.setPos(0, 0 - m_backgroundGraphics.pixmap().height() + def::sceneHeight);

    this->setBackgroundBrush(QBrush(Qt::black));
    m_scene.setBackgroundBrush(QBrush(Qt::black));
    m_scene.addItem(dynamic_cast<QGraphicsItem*>(&m_backgroundGraphics));

    connect(&m_backgroundAnimTimer, SIGNAL(timeout()),
            this, SLOT(backgroundAnimation()));
    m_backgroundAnimTimer.setInterval(m_backgroundAnimTimeDelay);
    m_backgroundAnimTimer.start();
}

BackgroundView::~BackgroundView()
{

}

void BackgroundView::activate()
{
    AnimationPlaneView::activate();
    m_backgroundAnimTimer.start();
}

void BackgroundView::deactivate()
{
    AnimationPlaneView::deactivate();
    m_backgroundAnimTimer.stop();
}

void BackgroundView::backgroundAnimation()
{
    int endBackgroundGraphicsPositionY = m_backgroundGraphics.pixmap().height() - def::sceneHeight;
    if(endBackgroundGraphicsPositionY <= m_backgroundGraphicsPosOffset)
    {
        m_backgroundGraphicsPosOffset = 0;
    }

    int startBackgroundGraphicsPositionY = 0 - m_backgroundGraphics.pixmap().height() + def::sceneHeight;
    m_backgroundGraphics.setPos(0, startBackgroundGraphicsPositionY + m_backgroundGraphicsPosOffset);
    m_backgroundGraphicsPosOffset++;
}
