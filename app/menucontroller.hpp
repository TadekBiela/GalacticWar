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

public slots:
    void startGame();
    void gameOver();
    void highScore();
    void back();
    void save(PlayerScore newPlayerScore);
    void updateHighScore(PlayerScoreMapIterator highScoreIterator);
    void quit();
};

#endif // MENUCONTROLLER_HPP
