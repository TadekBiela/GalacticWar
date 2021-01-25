
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


#include "levelcontroller.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "soundeffectmodel.hpp"

LevelController::LevelController(QWidget*      displayWidget,
                                 ControlPlane* controller)
    : m_displayWidget(displayWidget),
      m_controller(controller),
      m_model(nullptr),
      m_view(nullptr)
{

}

LevelController::~LevelController()
{
    if(m_model)
    {
        delete m_model;
    }
    if(m_view)
    {
        delete m_view;
    }
}

void LevelController::create()
{
    m_model = new LevelModel();
    m_view  = new LabelView(m_displayWidget,
                            m_controller,
                           "levelView");
    m_view->setPosition(def::levelGraphicsCenterPositionX,
                        def::levelGraphicsCenterPositionY);
    m_view->set(1);
    m_view->show();
    emit changeEnemyConfig(m_model->getCurrentConfig());
}

void LevelController::destroy()
{
    delete m_model;
    m_model = nullptr;
    delete m_view;
    m_view = nullptr;
}

void LevelController::show()
{
    m_view->show();
}

void LevelController::hide()
{
    m_view->hide();
}

void LevelController::nextLevel()
{
    QPointF position(def::halfSceneWidth,
                     def::halfSceneHeight - def::halfSceneHeight / 4);
    AnimationEffectModel* levelUpAnim = new AnimationEffectModel("level_up",
                                                                 position,
                                                                 def::animationLevelUpFrameWidth,
                                                                 def::animationLevelUpFrameHeight,
                                                                 def::animationLevelUpNumOfFrames);
    levelUpAnim->play();
    SoundEffectModel* levelUp = new SoundEffectModel("level_up");
    levelUp->play();
    m_model->next();
    m_view->set(m_model->getCurrentLevel());
    emit changeEnemyConfig(m_model->getCurrentConfig());
}
