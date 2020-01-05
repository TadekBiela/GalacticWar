#ifndef GENERALVIEW_HPP
#define GENERALVIEW_HPP

#include "menumodel.hpp"
#include "graphicsview.hpp"
#include "pushbutton.hpp"
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMouseEvent>
#include <QPointF>
#include <QProgressBar>
#include <QKeyEvent>

class GeneralView : public QMainWindow
{
    Q_OBJECT
public:
    GeneralView();
    virtual ~GeneralView();
    QGraphicsScene* getScene() { return &m_scene; }

signals:
    void startGame();
    void abortGame();
    void mousePressed();
    void mouseReleased();
    void mouseMoved(QPointF newPosition);
    void escPressed();
    void save(PlayerScore newPlayerScore);

public slots:
    void menu();
    void start();
    void pauseGame();
    void continueGame();
    void abort();
    void gameOver(int score);
    void highScore();
    void quitGame();
    void addGameObject(QGraphicsItem* newObject);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void continueButtonClicked();
    void savePlayerScore();
    void updateHighScoreList(PlayerScoreMapIterator iterator, int size);

    //HealthView section
    void updateHealth(int value);

    //LevelView section
    void updateLevel(int value);

    //ScoreView section
    void updateScore(int value);

protected:
    QGraphicsScene m_scene;
    GraphicsView   m_view;

    QLabel      m_title;             // Menu
    QLabel      m_author;            // Menu
    QLabel      m_pause;             // Menu
    QLineEdit   m_player;            // GameOver
    QLabel      m_score;             // GameOver
    PushButton  m_startButton;       // Menu
    PushButton  m_highScoreButton;   // Menu
    PushButton  m_quitButton;        // Menu
    PushButton  m_backToMenuButton;  // HighScore
    PushButton  m_backToMenuButton2; // GameOver & Pause
    PushButton  m_saveAfterGameOver; // GameOver
    PushButton  m_continueButton;    // Pause
    QListWidget m_highScoreList;     // HighScore

    //HealthView section
    QLabel       m_healthGraphics;
    QProgressBar m_healthBar;

    //LevelView section
    QLabel m_levelGraphics;
    QLabel m_levelText;

    //ScoreView section
    QLabel       m_scoreGraphics;
    QProgressBar m_scoreBar;
};

#endif // GENERALVIEW_HPP
