
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
