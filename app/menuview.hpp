#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <QLineEdit>
#include <QObject>
#include <QString>
#include <QTableWidget>
#include <QWidget>
#include "label.hpp"
#include "menumodel.hpp"
#include "pushbutton.hpp"

class MenuView : public QObject
{
    Q_OBJECT
public:
    explicit MenuView(QWidget* displayWidget);
    virtual ~MenuView();
    void    updateHighscore(PlayerScoreIterator highscoreBegin,
                            PlayerScoreIterator highscoreEnd);
    QString getPlayerNameFromField();
    int     getScoreFromLabel();
    void setPlayerNameField(QString);
    void    setGameoverScoreLabel(int scoreValue);

signals:
    void startClicked();
    void continueClicked();
    void cancelClicked();
    void quitClicked();
    void saveClicked();

public slots:
    void hideAllMenu();
    void showMainMenu();
    void showHighscoreMenu();
    void showPauseMenu();
    void showGameoverMenu();
    void startGame();
    void continueGame();
    void cancelGame();
    void quitGame();
    void saveScore();

protected:
    Label        m_mainTitleLabel;
    PushButton   m_mainStartButton;
    PushButton   m_mainHighscoreButton;
    PushButton   m_mainQuitButton;
    Label        m_highscoreTitleLabel;
    QTableWidget m_highscoreTable;
    PushButton   m_highscoreBackToMenu;
    Label        m_pauseTitleLabel;
    PushButton   m_pauseCancelButton;
    PushButton   m_pauseContinueButton;
    Label        m_gameoverTitleLabel;
    Label        m_gameoverScoreLabel;
    QLineEdit    m_gameoverPlayerNameField;
    PushButton   m_gameoverSaveScoreButton;
    PushButton   m_gameoverBackToMenuButton;
    Label        m_authorLabel;

private:
    void setupHighscoreTableStyle();
};

#endif // MENUVIEW_HPP
