#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "animationplaneview.hpp"
#include "controlplane.hpp"
#include "menumodel.hpp"
#include "menuview.hpp"
#include "gameplayview.hpp"
#include "ibackgroundmusicplayer.hpp"
#include <QObject>

class MenuController : public QObject
{
    Q_OBJECT
public:
    MenuController(
        QWidget* displayWidget,
        ControlPlane* controller,
        GameplayView* gameplayView,
        AnimationPlaneView* animationView,
        IBackgroundMusicPlayer* backgroundMusicPlayer,
        IFileManager* fileManager = nullptr
    );
    virtual ~MenuController();

signals:
    void gameStarted();
    void gamePaused();
    void gameContinued();
    void gameAborted();
    void gameOver();
    void gameExit();

public slots:
    void startGame();
    void pauseGame();
    void continueGame();
    void abortGame();
    void updateScore(int totalScore);
    void saveScore();
    void endGame();
    void exitGame();

protected:
    MenuModel m_model;
    MenuView m_view;
};

#endif // MENUCONTROLLER_HPP
