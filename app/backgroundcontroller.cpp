
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


#include "backgroundcontroller.hpp"
#include "backgroundeffectmodel.hpp"
#include "definitions.hpp"
#include "randomgenerator.hpp"

BackgroundController::BackgroundController(QWidget* displayWidget)
    : m_generator(new RandomGenerator),
      m_view(displayWidget),
      m_itemsSpawnTimer()
{
    connect(&m_itemsSpawnTimer, SIGNAL(timeout()),
            this,               SLOT(spawnItem()));

    int itemSpawnTimeDelay = m_generator->bounded(def::minBackgroundItemSpawnTimeDelay,
                                                  def::maxBackgroundItemSpawnTimeDelay);
    m_itemsSpawnTimer.setInterval(itemSpawnTimeDelay);
    m_itemsSpawnTimer.start();
}

BackgroundController::~BackgroundController()
{
    delete m_generator;
}

void BackgroundController::activate()
{
    m_view.activate();
    m_itemsSpawnTimer.start();
}

void BackgroundController::deactivate()
{
    m_view.deactivate();
    m_itemsSpawnTimer.stop();
}

void BackgroundController::increaseBackgroundSpeed()
{
    m_view.setBackgroundTimeDelay(def::shortBackgroundAnimTimeDelay);
}

void BackgroundController::decreaseBackgroundSpeed()
{
    m_view.setBackgroundTimeDelay(def::defaultBackgroundAnimTimeDelay);
}

void BackgroundController::resetToDefault()
{
    m_view.activate();
    m_view.setBackgroundTimeDelay(def::defaultBackgroundAnimTimeDelay);
}

void BackgroundController::spawnItem()
{
    background_effect type = static_cast<background_effect>(
                m_generator->bounded(background_effect::first_element,
                                     background_effect::last_element));
    const int sceneBorderOffset = 10;
    int startPositionX = m_generator->bounded(-sceneBorderOffset,
                                              def::sceneWidth + sceneBorderOffset);
    int startPositionY = -sceneBorderOffset;
    QPointF startPosition(startPositionX, startPositionY);
    int moveDirection = 0;
    if(startPositionX <= def::halfSceneWidth) {
        moveDirection = m_generator->bounded(def::minBackgroundDirectionRange,
                                             def::down);
    }
    else{
        moveDirection = m_generator->bounded(def::down,
                                             def::maxBackgroundDirectionRange);
    }
    BackgroundEffectModel* newBgEffect = new BackgroundEffectModel(type,
                                                                   startPosition,
                                                                   moveDirection,
                                                                   m_view.scene());
    newBgEffect->play();
}
