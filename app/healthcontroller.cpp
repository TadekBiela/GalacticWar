
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


#include "healthcontroller.hpp"
#include "definitions.hpp"

HealthController::HealthController(QWidget*      displayWidget,
                                   ControlPlane* controller)
    : m_displayWidget(displayWidget),
      m_controller(controller),
      m_model(nullptr),
      m_view(nullptr)
{

}

HealthController::~HealthController()
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

void HealthController::create()
{
    m_model = new HealthModel();
    m_view  = new BarView(m_displayWidget,
                          m_controller,
                          "healthView",
                          def::darkRedHex);
    m_view->setPosition(def::healthGraphicsCenterPositionX,
                        def::healthGraphicsCenterPositionY);
    m_view->set(m_model->getCurrentHealthInPercent());
    m_view->show();
}

void HealthController::destroy()
{
    delete m_model;
    m_model = nullptr;
    delete m_view;
    m_view = nullptr;
}

void HealthController::show()
{
    m_view->show();
}

void HealthController::hide()
{
    m_view->hide();
}

void HealthController::addHealthPoints(int healthPoints)
{
    m_model->add(healthPoints);
    m_view->set(m_model->getCurrentHealthInPercent());
}

void HealthController::subtractHealthPoints(int healthPoints)
{
    Health_Status status = m_model->subtract(healthPoints);
    if(Health_Status_No_More == status)
    {
        m_view->set(0);
        emit noHealth();
        return;
    }
    m_view->set(m_model->getCurrentHealthInPercent());
}
