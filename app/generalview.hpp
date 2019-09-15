#ifndef GENERALVIEW_HPP
#define GENERALVIEW_HPP

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>

class GeneralView : public QMainWindow
{
    Q_OBJECT
public:
    GeneralView();
    ~GeneralView()

public slots:
    void menu();
    void startGame();
    void pause();
    void gameOver();
    void highScore();
    void addGameObject(QGraphicsItem *newObject);

protected:
    QGraphicsScene m_scene;

    QLabel      m_title;             // Menu
    QLabel      m_author;            // Menu
    QLabel      m_pause;             // Menu
    QPushButton m_startButton;       // Menu
    QPushButton m_highScoreButton;   // Menu
    QPushButton m_quitButton;        // Menu
    QPushButton m_backToMenuButton;  // HighScore
    QPushButton m_saveAfterGameOver; // GameOver
};

#endif // GENERALVIEW_HPP
