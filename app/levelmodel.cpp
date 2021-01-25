
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


#include "levelmodel.hpp"

//Each EnemyConfig members sum should be equal 100
const EnemyConfiguration LevelModel::s_enemyLevelConfigurations[def::maxNumOfLevel] = {
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 1),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 1),
    73,
    25,
    2,
    0,
    0,
    0
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 2),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 2),
    47,
    38,
    15,
    0,
    0,
    0
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 3),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 3),
    5,
    25,
    35,
    15,
    0,
    0
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 4),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 4),
    0,
    15,
    60,
    15,
    0,
    0
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 5),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 5),
    5,
    10,
    40,
    35,
    10,
    0
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 6),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 6),
    5,
    10,
    20,
    35,
    20,
    10
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 7),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 7),
    5,
    10,
    10,
    25,
    40,
    10
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 8),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 8),
    5,
    7,
    8,
    15,
    45,
    20
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 9),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 9),
    2,
    5,
    8,
    10,
    45,
    30
  },
  {
    def::minEnemySpawnTimeDelay - (def::minEnemySpawnTimeDelayDecreaseFactor * 10),
    def::maxEnemySpawnTimeDelay - (def::maxEnemySpawnTimeDelayDecreaseFactor * 10),
    2,
    5,
    5,
    8,
    30,
    50
  }
};

LevelModel::LevelModel()
    : m_currentLevel(1)
{

}

LevelModel::~LevelModel()
{

}

void LevelModel::next()
{
    if(m_currentLevel < def::maxNumOfLevel)
    {
        m_currentLevel++;
    }
}

int LevelModel::getCurrentLevel()
{
    return m_currentLevel;
}

EnemyConfiguration LevelModel::getCurrentConfig()
{
    return s_enemyLevelConfigurations[m_currentLevel - 1];
}
