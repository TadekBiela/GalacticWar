
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


#include "playercontroller.hpp"
#include "animationeffectmodel.hpp"
#include "soundeffectmodel.hpp"

PlayerController::PlayerController(ControlPlane* controller,
                                   GameplayView* view)
    : m_controller(controller),
      m_model(nullptr)
{
    connect(this, SIGNAL(addPlayerToScene(GameObject*)), view, SLOT(addGameObjectToScene(GameObject*)));
}

PlayerController::~PlayerController()
{

}

void PlayerController::create()
{
    m_model = new PlayerModel;

    connect(
        m_model, SIGNAL(addHealthPoints(int)),
        this, SLOT(addHealth(int))
    );
    connect(
        m_model, SIGNAL(subtractHealthPoints(int)),
        this, SLOT(subtractHealth(int))
    );
    connect(
        m_controller, SIGNAL(startFire()),
        m_model, SLOT(startFire())
    );
    connect(
        m_controller, SIGNAL(stopFire()),
        m_model, SLOT(stopFire())
    );
    connect(
        m_controller, SIGNAL(changeMovePosition(QPointF)),
        m_model, SLOT(changeMovePosition(QPointF))
    );
    connect(
        m_controller, SIGNAL(stopMoveOnAxeX()),
        m_model, SLOT(stopMoveOnAxeX())
    );
    connect(
        m_controller, SIGNAL(stopMoveOnAxeY()),
        m_model, SLOT(stopMoveOnAxeY())
    );
    connect(
        m_model, SIGNAL(getCurrentPosition(QPointF)),
        m_controller, SLOT(setMovePosition(QPointF))
    );

    m_model->setFocus();
    m_model->start();
    emit addPlayerToScene(m_model);
}

void PlayerController::destroy()
{
    QPointF destroyedPlayerPosition = m_model->getCenterPosition();
    AnimationEffectModel* explosionAnim = new AnimationEffectModel("explosion",
                                                                   destroyedPlayerPosition,
                                                                   def::animationFrameWidth,
                                                                   def::animationFrameHeight);
    explosionAnim->play();
    SoundEffectModel* explosionSound = new SoundEffectModel("explosion");
    explosionSound->play();

    delete m_model;
    m_model = nullptr;
}

void PlayerController::changePlayerAtribute(special_type reward)
{
    m_model->changeAtribute(reward);
}

void PlayerController::addHealth(int healthPoints)
{
    emit addHealthPoints(healthPoints);
}

void PlayerController::subtractHealth(int healthPoints)
{
    emit subtractHealthPoints(healthPoints);
}
