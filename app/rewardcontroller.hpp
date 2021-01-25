
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


#ifndef REWARDCONTROLLER_HPP
#define REWARDCONTROLLER_HPP

#include "definitions.hpp"
#include "gameobject.hpp"
#include "gameplayview.hpp"
#include "irandomgenerator.hpp"
#include "rewardtypes.hpp"
#include <QObject>
#include <QGraphicsItem>
#include "QPointF"

class RewardController : public QObject
{
    Q_OBJECT
public:
    RewardController(GameplayView* view);
    virtual ~RewardController();

signals:
    void addRewardToScene(GameObject* reward);
    void rewardCoinCollected(coin_type coin);
    void rewardSpecialCollected(special_type special);

public slots:
    void spawnRewards(QPointF position, int tier);
    void coinCollected(coin_type coin);
    void specialCollected(special_type special);

protected:
    IRandomGenerator* m_generator;

    static const int s_minCoinsInTier[def::maxTier];
    static const int s_maxCoinsInTier[def::maxTier];
    static const int s_coinTypeInTier[def::maxTier][10];
    static const int s_specialChanceInTier[def::maxTier];
};

#endif // REWARDCONTROLLER_HPP
