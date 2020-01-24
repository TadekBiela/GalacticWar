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
    void abortPlayer();
    void activateEnemySpawning();
    void deactivateEnemySpawning();
    void getScore();
    void playerDefeated(int score);

public slots:
    void startGame();
    void startSpawningEnemies();
    void showScore();
    void mouseLeaveWindow();
    void escPressed();
    void updateScore(int score);
    void abortGame();
    void gameOver();

protected:
    bool         m_isGameStarted;
    bool         m_isGamePaused;
    GeneralView* m_view;
};

#endif // MENUCONTROLLER_HPP
