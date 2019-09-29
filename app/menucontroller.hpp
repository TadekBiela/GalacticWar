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
    void saveHighScore();
    void activateEnemySpawning();
    void deactivateEnemySpawning();
    void activatePlayer();
    void deactivatePlayer();
    void playerDefeated();

public slots:
    void startGame();
    void stopGame();
    void gameOver();
};

#endif // MENUCONTROLLER_HPP
