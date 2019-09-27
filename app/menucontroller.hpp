#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "generalview.hpp"
#include "menumodel.hpp"
#include <QObject>

class MenuController : public QObject
{
    Q_OBJECT
public:
    MenuController(GeneralView* view,
                   MenuModel*   model);

signals:
    void addRecordToHighScore(PlayerScore newRecord);
    void saveHighScore();
    void activateEnemySpawning();
    void deactivateEnemySpawning();
    void activatePlayer();
    void deactivatePlayer();

public slots:
    void startGame();
    void stopGame();
    void save(PlayerScore newPlayerScore);
    void updateHighScore(PlayerScoreMapIterator highScoreIterator);
};

#endif // MENUCONTROLLER_HPP
