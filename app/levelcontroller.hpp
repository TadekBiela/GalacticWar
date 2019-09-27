#ifndef LEVELCONTROLLER_HPP
#define LEVELCONTROLLER_HPP

#include "enemyconfiguration.hpp"
#include "levelmodel.hpp"
#include "levelview.hpp"
#include <QObject>

class LevelController : public QObject
{
    Q_OBJECT
public:
    LevelController(LevelModel* levelModel,
                    LevelView*  levelView);

signals:
    void nextLevelInModel();
    void changeEnemyConfiguration(EnemyConfiguration newEnemyConfiguration);

public slots:
    void nextLevel();
    void changeEnemyConfig(EnemyConfiguration newEnemyConfiguration);
};

#endif // LEVELCONTROLLER_HPP
