#include "levelmodel.hpp"

const EnemyConfiguration LevelModel::s_enemyLevelConfigurations[def::maxNumOfLevel] =
    { { 75, 25,  0,  0,  0,  0 }, //Each EnemyConfig members sum should be equal 100
      { 50, 40, 10,  0,  0,  0 },
      { 25, 25, 40, 10,  0,  0 },
      { 10, 15, 60, 15,  0,  0 },
      {  0, 10, 40, 35, 10,  0 },
      {  0,  5, 20, 40, 20, 10 },
      {  0,  0, 10, 30, 50, 10 },
      {  0,  0,  5, 20, 55, 20 },
      {  0,  0,  0, 10, 50, 40 },
      {  0,  0,  0,  0, 30, 70 } };

LevelModel::LevelModel()
{

}

LevelModel::~LevelModel()
{

}

void LevelModel::nextLevel()
{
    if(++m_currentLevel <= def::maxNumOfLevel)
    {
        emit updateLevelView(m_currentLevel);
        emit changeEnemyModelConfiguration(s_enemyLevelConfigurations[m_currentLevel-1]);
    }
    else
    {
        m_currentLevel = def::maxNumOfLevel;
    }
}

void LevelModel::reset()
{
    m_currentLevel = 1;
    emit updateLevelView(m_currentLevel);
    emit changeEnemyModelConfiguration(s_enemyLevelConfigurations[m_currentLevel-1]);
}
