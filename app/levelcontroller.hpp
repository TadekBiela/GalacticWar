#ifndef LEVELCONTROLLER_HPP
#define LEVELCONTROLLER_HPP

#include "enemyconfiguration.hpp"
#include "levelmodel.hpp"
#include "generalview.hpp"
#include <QObject>

class LevelController : public QObject
{
    Q_OBJECT
public:
    LevelController(LevelModel*  model,
                    GeneralView* view);
    virtual ~LevelController();

signals:
    void reset();
    void next();
    void changeEnemyConfiguration(EnemyConfiguration newEnemyConfiguration);

public slots:
    void resetLevel();
    void nextLevel();
    void change(EnemyConfiguration newEnemyConfiguration);
};

#endif // LEVELCONTROLLER_HPP
