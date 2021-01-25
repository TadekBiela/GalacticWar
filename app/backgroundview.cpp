
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


#include "backgroundview.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsEffect>

BackgroundView::BackgroundView(QWidget* displayWidget)
    : AnimationPlaneView(displayWidget),
      m_backgroundAnimTimer(),
      m_backgroundGraphics(),
      m_backgroundGraphicsPosOffset(0),
      m_backgroundLabelWindow(displayWidget)
{
    this->setBackgroundBrush(QBrush(Qt::transparent));
    m_scene.setBackgroundBrush(QBrush(Qt::transparent));

    QImage* backgroundImage = g_imageStorage->getImage("background");
    m_backgroundGraphics.convertFromImage(*backgroundImage);
    m_backgroundLabelWindow.setGeometry(1,
                                        1,
                                        def::sceneWidth,
                                        def::sceneHeight);
    m_backgroundLabelWindow.stackUnder(this);
    m_backgroundLabelWindow.show();

    connect(&m_backgroundAnimTimer, SIGNAL(timeout()),
            this, SLOT(backgroundAnimation()));
    m_backgroundAnimTimer.setInterval(def::defaultBackgroundAnimTimeDelay);
    m_backgroundAnimTimer.start();
}

BackgroundView::~BackgroundView()
{

}

void BackgroundView::setGraphicsEffects(qreal opacity, qreal blurRadius)
{
    GraphicsView::setGraphicsEffects(opacity, blurRadius);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(opacity);
    m_backgroundLabelWindow.setGraphicsEffect(opacityEffect);
    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(blurRadius);
    m_backgroundLabelWindow.setGraphicsEffect(blurEffect);
}

void BackgroundView::activate()
{
    startAllItems();
    m_backgroundAnimTimer.start();
    setGraphicsEffects(0, 0);
}

void BackgroundView::deactivate()
{
    stopAllItems();
    m_backgroundAnimTimer.stop();
    setGraphicsEffects(0.6, 6);
}

void BackgroundView::setBackgroundTimeDelay(int delay)
{
    m_backgroundAnimTimer.setInterval(delay);
}

void BackgroundView::backgroundAnimation()
{
    int endBackgroundPositionOffsetValue = m_backgroundGraphics.height() - def::sceneHeight;
    if(endBackgroundPositionOffsetValue < m_backgroundGraphicsPosOffset)
    {
        m_backgroundGraphicsPosOffset = 0;
    }

    int startBackgroundGraphicsPositionY = m_backgroundGraphics.height() - def::sceneHeight;
    m_backgroundLabelWindow.setPixmap(
                m_backgroundGraphics.copy(0,
                startBackgroundGraphicsPositionY - m_backgroundGraphicsPosOffset,
                def::sceneWidth,
                def::sceneHeight));
    m_backgroundGraphicsPosOffset+=2;
}
