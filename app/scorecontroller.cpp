
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


#include "scorecontroller.hpp"
#include "randomgenerator.hpp"

ScoreController::ScoreController(QWidget*      displayWidget,
                                 ControlPlane* controller)
    : m_displayWidget(displayWidget),
      m_controller(controller),
      m_generator(new RandomGenerator()),
      m_model(nullptr),
      m_view(nullptr)
{

}

ScoreController::~ScoreController()
{
    delete m_generator;
    if(m_model)
    {
        delete m_model;
    }
    if(m_view)
    {
        delete m_view;
    }
}

void ScoreController::create()
{
    m_model = new ScoreModel();
    m_view  = new BarView(m_displayWidget,
                          m_controller,
                          "scoreView",
                          def::darkYellowHex);
    m_view->setPosition(def::scoreGraphicsCenterPositionX,
                        def::scoreGraphicsCenterPositionY);
    m_view->invertAppearance();
    m_view->show();
}

void ScoreController::destroy()
{
    delete m_model;
    m_model = nullptr;
    delete m_view;
    m_view = nullptr;
}

void ScoreController::show()
{
    m_view->show();
}

void ScoreController::hide()
{
    m_view->hide();
}

void ScoreController::addScorePointsBasedOnCoinType(coin_type coin)
{
    int points = 0;
    switch (coin)
    {
        case bronze:
            points = m_generator->bounded(def::minPointsForBronzeCoin,
                                          def::maxPointsForBronzeCoin);
            break;
        case silver:
            points = m_generator->bounded(def::minPointsForSilverCoin,
                                          def::maxPointsForSilverCoin);
            break;
        case gold:
            points = m_generator->bounded(def::minPointsForGoldCoin,
                                          def::maxPointsForGoldCoin);
            break;
    }
    Score_Per_Level status = m_model->add(points);
    if(Score_Per_Level_Next == status)
    {
        emit maxScorePerLevelAchieved();
    }
    m_view->set(m_model->getCurrentScoreInPercent());
}

void ScoreController::emitTotalScoreAndDestroy()
{
    emit totalScore(m_model->getTotalScore());
    destroy();
}
