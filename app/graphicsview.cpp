#include "definitions.hpp"
#include "graphicsview.hpp"
#include "gameobject.hpp"
#include <QGraphicsEffect>

GraphicsView::GraphicsView(QWidget *displayWidget)
    : QGraphicsView(displayWidget),
      m_scene(0, 0, def::sceneWidth, def::sceneHeight, this)
{
    m_scene.setBackgroundBrush(QBrush(Qt::transparent));
    this->setScene(&m_scene);
    this->setStyleSheet("background: transparent;");
    this->setBackgroundBrush(QBrush(Qt::transparent));
    this->setGeometry(1, 1, def::sceneWidth + 2, def::sceneHeight + 2);
    this->show();
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::setGraphicsEffects(qreal opacity, qreal blurRadius)
{
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(opacity);
    setGraphicsEffect(opacityEffect);
    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(blurRadius);
    setGraphicsEffect(blurEffect);
}
