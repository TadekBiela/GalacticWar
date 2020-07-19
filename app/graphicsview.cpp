#include "graphicsview.hpp"
#include "gameobject.hpp"
#include <QGraphicsEffect>

GraphicsView::GraphicsView(QWidget *displayWidget)
                            : QGraphicsView(displayWidget),
                              m_scene(displayWidget)
{
    QGraphicsView::setScene(&m_scene);
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
