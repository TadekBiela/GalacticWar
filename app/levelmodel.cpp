#include "levelmodel.hpp"

const EnemyConfiguration LevelModel::s_enemyLevelConfigurations[def::maxNumOfLevel] =
    { { 73, 25,  2,  0,  0,  0 }, //Each EnemyConfig members sum should be equal 100
      { 47, 38, 15,  0,  0,  0 },
      { 25, 25, 35, 15,  0,  0 },
      { 10, 15, 60, 15,  0,  0 },
      {  5, 10, 40, 35, 10,  0 },
      {  5, 10, 20, 35, 20, 10 },
      {  5, 10, 10, 25, 40, 10 },
      {  5,  7,  8, 15, 45, 20 },
      {  2,  5,  8, 10, 45, 30 },
      {  2,  5,  5,  8, 30, 50 } };

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
