#ifndef LEVELMODEL_HPP
#define LEVELMODEL_HPP

#include "definitions.hpp"
#include "enemyconfiguration.hpp"
#include <QObject>

class LevelModel : public QObject
{
    Q_OBJECT
public:
    LevelModel();
    virtual ~LevelModel();

signals:
    void update(int value);
    void change(EnemyConfiguration newEnemyConfiguration);

public slots:
    void next();
    void reset();

protected:
    int m_currentLevel = 1;

    static const EnemyConfiguration s_enemyLevelConfigurations[def::maxNumOfLevel];
};

#endif // LEVELMODEL_HPP
