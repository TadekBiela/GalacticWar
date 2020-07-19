#ifndef GENERALVIEW_HPP
#define GENERALVIEW_HPP

#include "menumodel.hpp"
#include "graphicsview.hpp"
#include "pushbutton.hpp"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QMouseEvent>
#include <QPointF>
#include <QProgressBar>
#include <QKeyEvent>

class GeneralView : public QWidget
{
    Q_OBJECT
public:
    GeneralView();
    virtual ~GeneralView();
    QGraphicsScene* getScene() { return &m_scene; }

signals:
    void startGame();
    void abortGame();
    void exitGame();

public slots:
    void start();
    void pauseGame();
    void continueGame();
    void abort();
    void gameOver(int score);
    void quitGame();
    void show();

protected:
    QGraphicsScene m_scene;

    bool m_isGamePaused = false;
    QPixmap m_arrowCursorMap;
    QPixmap m_crossCursorMap;
};

#endif // GENERALVIEW_HPP
