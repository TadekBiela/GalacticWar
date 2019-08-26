#ifndef LEVELMODEL_HPP
#define LEVELMODEL_HPP

#include "definitions.hpp"
#include "enemyconfiguration.hpp"
#include <QObject>

class LevelModel : public QObject
{
    Q_OBJECT
public:
    explicit LevelModel();
    ~LevelModel();

signals:
    void updateLevelView(int value);
    void changeEnemyModelConfiguration(EnemyConfiguration newEnemyConfiguration);

public slots:
    void nextLevel();

protected:
    int                             m_currentLevel = 0;
    static const EnemyConfiguration s_enemyLevelConfigurations[def::maxNumOfLevel];
};

#endif // LEVELMODEL_HPP
