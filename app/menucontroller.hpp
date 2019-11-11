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
    virtual ~MenuController();

signals:
    void pauseGame();
    void continueGame();
    void saveHighScore();
    void resetLevel();
    void resetScore();
    void createNewPlayer();
    void activateEnemySpawning();
    void deactivateEnemySpawning();
    void getScore();
    void playerDefeated(int score);

public slots:
    void startGame();
    void escPressed();
    void updateScore(int score);
    void gameOver();

protected:
    bool m_isGamePaused;
};

#endif // MENUCONTROLLER_HPP
