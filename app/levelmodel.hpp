#ifndef LEVELMODEL_HPP
#define LEVELMODEL_HPP

#include "definitions.hpp"
#include "enemyconfiguration.hpp"

class LevelModel
{
public:
    LevelModel();
    ~LevelModel();
    void next();
    int getCurrentLevel();
    EnemyConfiguration getCurrentConfig();

protected:
    int m_currentLevel;

    static const EnemyConfiguration s_enemyLevelConfigurations[def::maxNumOfLevel];
};

#endif // LEVELMODEL_HPP
