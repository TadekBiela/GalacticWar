#ifndef GENERALVIEW_HPP
#define GENERALVIEW_HPP

#include "menumodel.hpp"
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QMouseEvent>
#include <QPointF>

class GeneralView : public QMainWindow
{
    Q_OBJECT
public:
    GeneralView();
    ~GeneralView();

signals:
    void mousePressed();
    void mouseReleased();
    void mouseMoved(QPointF newPosition);
    void save(PlayerScore newPlayerScore);

public slots:
    void menu();
    void startGame();
    void pause();
    void gameOver();
    void highScore();
    void addGameObject(QGraphicsItem* newObject);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void savePlayerScore();
    void updateHighScoreList(PlayerScoreMapIterator iterator, int size);

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
    QListWidget m_highScoreList;     // HighScore
};

#endif // GENERALVIEW_HPP
