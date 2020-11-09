#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QSlider>
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
    void saveSettingsClicked();

public slots:
    void hideAllMenu();
    void showMainMenu();
    void showHighscoreMenu();
    void showSettingsMenu();
    void showPauseMenu();
    void showGameoverMenu();
    void startGame();
    void continueGame();
    void cancelGame();
    void quitGame();
    void saveScore();
    void saveSettings();

protected:
    //Main
    Label        m_mainTitleLabel;
    PushButton   m_mainStartButton;
    PushButton   m_mainHighscoreButton;
    PushButton m_mainSettingsButton;
    PushButton   m_mainQuitButton;
    //Highscore
    Label        m_highscoreTitleLabel;
    QTableWidget m_highscoreTable;
    PushButton   m_highscoreBackToMenu;
    //Settings
    Label m_settingsTitleLabel;
    QLabel m_settingsMusicLabel;
    QCheckBox m_settingsMusicCheckBox;
    QSlider m_settingsMusicSlider;
    QLabel m_settingsSoundsLabel;
    QCheckBox m_settingsSoundsCheckBox;
    QSlider m_settingsSoundsSlider;
    QLabel m_settingsControlLabel;
    QCheckBox m_settingsControlMouseCheckBox;
    QCheckBox m_settingsControlKeyboardCheckBox;
    PushButton m_settingsSaveButton;
    PushButton m_settingsBackToMenuButton;
    //Pause
    Label        m_pauseTitleLabel;
    PushButton   m_pauseCancelButton;
    PushButton   m_pauseContinueButton;
    //Gameover
    Label        m_gameoverTitleLabel;
    Label        m_gameoverScoreLabel;
    QLineEdit    m_gameoverPlayerNameField;
    PushButton   m_gameoverSaveScoreButton;
    PushButton   m_gameoverBackToMenuButton;
    //Author
    Label        m_authorLabel;

private:
    void setupHighscoreTableStyle();
};

#endif // MENUVIEW_HPP
