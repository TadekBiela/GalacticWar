
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


#ifndef ENEMYCONTROLLER_HPP
#define ENEMYCONTROLLER_HPP

#include "definitions.hpp"
#include "enemyconfiguration.hpp"
#include "gameobject.hpp"
#include "gameplayview.hpp"
#include "irandomgenerator.hpp"
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QTimer>

class EnemyController : public QObject
{
    Q_OBJECT
public:
    EnemyController(
        GameplayView* view
    );
    virtual ~EnemyController();

signals:
    void addEnemyToScene(
        GameObject* enemy
    );
    void enemyDestroyed(
        QPointF position,
        int enemyLevel
    );

public slots:
    void changeEnemyConfig(
        EnemyConfiguration newEnemyConfig
    );
    void destroyed(
        QPointF position,
        int enemyLevel
    );
    void startSpawning();
    void stopSpawning();

protected slots:
    void spawnEnemy();

protected:
    int m_enemyPercentDistributionTab[def::percentDistTabSize];
    int m_minEnemySpawnTimeDelay;
    int m_maxEnemySpawnTimeDelay;
    QTimer m_enemySpawnTimer;
    int m_remainigSpawnTime;
    IRandomGenerator* m_generator;
};

#endif // ENEMYCONTROLLER_HPP
