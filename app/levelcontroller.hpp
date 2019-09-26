#ifndef LEVELCONTROLLER_HPP
#define LEVELCONTROLLER_HPP

#include "enemyconfiguration.hpp"
#include <QObject>

class LevelController : public QObject
{
    Q_OBJECT
public:
    LevelController();

signals:
    void nextLevelInModel();
    void updateLevelInView(int value);
    void changeEnemyConfiguration(EnemyConfiguration newEnemyConfiguration);

public slots:
    void nextLevel();
    void updateLevelView(int value);
    void changeEnemyConfig(EnemyConfiguration newEnemyConfiguration);
};

#endif // LEVELCONTROLLER_HPP
