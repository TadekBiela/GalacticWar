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
    LevelController(LevelModel* model,
                    LevelView*  view);
    virtual ~LevelController();

signals:
    void next();
    void changeEnemyConfiguration(EnemyConfiguration newEnemyConfiguration);

public slots:
    void nextLevel();
    void change(EnemyConfiguration newEnemyConfiguration);
};

#endif // LEVELCONTROLLER_HPP
