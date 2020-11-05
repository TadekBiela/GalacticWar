#include "menuview.hpp"
#include "definitions.hpp"
#include <QString>
#include <QHeaderView>

MenuView::MenuView(QWidget* displayWidget)
    : m_mainTitleLabel(def::gameTitle, displayWidget),
      m_mainStartButton(def::startgameText, displayWidget),
      m_mainHighscoreButton(def::highscoreText, displayWidget),
      m_mainQuitButton(def::quitText, displayWidget),
      m_highscoreTitleLabel(def::highscoreText, displayWidget),
      m_highscoreTable(displayWidget),
      m_highscoreBackToMenu(def::backText, displayWidget),
      m_pauseTitleLabel(def::pauseText, displayWidget),
      m_pauseCancelButton(def::cancelText, displayWidget),
      m_pauseContinueButton(def::continueText, displayWidget),
      m_gameoverTitleLabel(def::gameoverText, displayWidget),
      m_gameoverScoreLabel("", displayWidget),
      m_gameoverPlayerNameField("", displayWidget),
      m_gameoverSaveScoreButton(def::saveText, displayWidget),
      m_gameoverBackToMenuButton(def::backText, displayWidget),
      m_authorLabel(def::authorTitle, displayWidget)
{
    //Init main menu
    m_mainTitleLabel.setPosition(def::labelPositionX,
                                 def::labelPositionY);
    m_mainStartButton.setPosition(def::centerButtonPositionX,
                                  def::startButtonPositionY);
    m_mainHighscoreButton.setPosition(def::centerButtonPositionX,
                                      def::highscoreButtonPositionY);
    m_mainQuitButton.setPosition(def::centerButtonPositionX,
                                 def::quitButtonPositionY);

    //Init highscore menu
    m_highscoreTitleLabel.setPosition(def::labelPositionX,
                                      def::labelPositionY);
    m_highscoreTable.setGeometry(def::highscoreTablePositionX,
                                 def::highscoreTablePositionY,
                                 def::highscoreTableWight,
                                 def::highscoreTableHeight);
    setupHighscoreTableStyle();
    m_highscoreBackToMenu.setPosition(def::centerButtonPositionX,
                                      def::highscoreBackButtonPositionY);


    //Init pause menu
    m_pauseTitleLabel.setPosition(def::labelPositionX,
                                  def::labelPositionY);
    m_pauseCancelButton.setPosition(def::pauseCancelButtonPositionX,
                                   def::pauseBottomButtonPositionY);
    m_pauseContinueButton.setPosition(def::pauseContinueButtonPositionX,
                                      def::pauseBottomButtonPositionY);

    //Init gameover menu
    m_gameoverTitleLabel.setPosition(def::labelPositionX,
                                     def::labelPositionY);
    m_gameoverScoreLabel.setPosition(def::gameoverScoreLabelPositionX,
                                     def::gameoverScoreLabelPositionY);
    m_gameoverPlayerNameField.setStyleSheet(QString("border-style:     solid;"
                                                    "border-width:     2px;"
                                                    "border-radius:    5px;"
                                                    "border-color:     #FFFFFF;"
                                                    "color:            #FFFFFF;"
                                                    "background-color: transparent;"
                                                    "font-size:        30px"));
    m_gameoverPlayerNameField.setGeometry(def::gameoverPlayerNameFieldPositionX,
                                          def::gameoverPlayerNameFieldPositionY,
                                          def::gameoverPlayerNameFieldWidth,
                                          def::gameoverPlayerNameFieldHeight);
    m_gameoverPlayerNameField.setAlignment(Qt::AlignCenter);
    m_gameoverSaveScoreButton.setPosition(def::gameoverSaveButtonPositionX,
                                          def::gameoverBottomButtonPositionY);
    m_gameoverBackToMenuButton.setPosition(def::gameoverBackButtonPositionX,
                                           def::gameoverBottomButtonPositionY);


    //Init author label
    m_authorLabel.setSize(def::authorLabelWidth,
                          def::authorLabelHeight);
    m_authorLabel.setPosition(def::authorLabelPositionX,
                              def::authorLabelPositionY);
    m_authorLabel.setAlignment(Qt::AlignRight);
    m_authorLabel.setFontSizeInPx(8);

    connect(&m_mainStartButton,          SIGNAL(clicked()), this, SLOT(startGame()));
    connect(&m_mainHighscoreButton,      SIGNAL(clicked()), this, SLOT(showHighscoreMenu()));
    connect(&m_mainQuitButton,           SIGNAL(clicked()), this, SLOT(quitGame()));
    connect(&m_highscoreBackToMenu,      SIGNAL(clicked()), this, SLOT(showMainMenu()));
    connect(&m_pauseContinueButton,      SIGNAL(clicked()), this, SLOT(continueGame()));
    connect(&m_pauseCancelButton,        SIGNAL(clicked()), this, SLOT(cancelGame()));
    connect(&m_gameoverSaveScoreButton,  SIGNAL(clicked()), this, SLOT(saveScore()));
    connect(&m_gameoverBackToMenuButton, SIGNAL(clicked()), this, SLOT(showMainMenu()));

    showMainMenu();
}

MenuView::~MenuView()
{

}

void MenuView::updateHighscore(const PlayerScoreIterator highscoreBegin,
                               const PlayerScoreIterator highscoreEnd)
{
    while(m_highscoreTable.rowCount() != 0)
    {
        m_highscoreTable.removeRow(0);
    }

    int tableIdx = 0;
    for(auto iterator = highscoreBegin; iterator < highscoreEnd; iterator++, tableIdx++)
    {
        QTableWidgetItem* playerName  = new QTableWidgetItem(iterator->first);
        QTableWidgetItem* playerScore = new QTableWidgetItem(QString::number(iterator->second));
        playerScore->setTextAlignment(Qt::AlignRight + Qt::AlignCenter);
        m_highscoreTable.insertRow(m_highscoreTable.rowCount());
        m_highscoreTable.setItem(tableIdx, 0, playerName);
        m_highscoreTable.setItem(tableIdx, 1, playerScore);
    }
}

QString MenuView::getPlayerNameFromField()
{
    return m_gameoverPlayerNameField.text();
}

void MenuView::setPlayerNameField(QString playerName) {
    m_gameoverPlayerNameField.setText(playerName);
}

void MenuView::setGameoverScoreLabel(int scoreValue)
{
    m_gameoverScoreLabel.setText(QString::number(scoreValue));
}

int MenuView::getScoreFromLabel()
{
    QString totalScoreInString = m_gameoverScoreLabel.getText();
    return totalScoreInString.toInt();
}

void MenuView::setupHighscoreTableStyle()
{
    m_highscoreTable.setColumnCount(2);
    m_highscoreTable.setColumnWidth(0, def::highscoreTableWight / 2 - 10);
    m_highscoreTable.setColumnWidth(1, def::highscoreTableWight / 2 - 38);
    QStringList labels = { "Player", "Score" };
    m_highscoreTable.setHorizontalHeaderLabels(labels);
    m_highscoreTable.horizontalHeader()->setSectionsClickable(false);
    m_highscoreTable.horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_highscoreTable.verticalHeader()->setSectionsClickable(false);
    m_highscoreTable.verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_highscoreTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_highscoreTable.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_highscoreTable.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_highscoreTable.setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
    m_highscoreTable.setRowCount(0);
    m_highscoreTable.setShowGrid(false);
    m_highscoreTable.setStyleSheet("QTableView {"
                                  "        border-style: solid;"
                                  "        border-width: 2px;"
                                  "        border-radius: 5px;"
                                  "        border-color: white;"
                                  "        background: transparent;"
                                  "        font-size: 16px;"
                                  "}"
                                  "QTableView::item {"
                                  "        background: transparent;"
                                  "        color: white;"
                                  "}"
                                  "QTableView QTableCornerButton::section {"
                                  "        background: transparent;"
                                  "        border-top: 0px;"
                                  "        border-right: 0px;"
                                  "        border-left: 0px;"
                                  "        border-bottom: 2px solid white;"
                                  "}"
                                  "QHeaderView {"
                                  "        background-color: transparent;"
                                  "        border-style: solid;"
                                  "        border-bottom-width: 2px;"
                                  "        border-color: white;"
                                  "}"
                                  "QHeaderView::section {"
                                  "        background-color: transparent;"
                                  "        border-style: none;"
                                  "        font-size: 18px;"
                                  "        color: white;"
                                  "}"
                                  "QHeaderView::section::vertical {"
                                  "        border-bottom-width: 0px;"
                                  "        background-color: transparent;"
                                  "}"
                                  "QHeaderView::section::horizontal {"
                                  "        background-color: transparent;"
                                  "}");
}

void MenuView::hideAllMenu()
{
    m_mainTitleLabel.hide();
    m_mainStartButton.hide();
    m_mainHighscoreButton.hide();
    m_mainQuitButton.hide();
    m_highscoreTitleLabel.hide();
    m_highscoreTable.hide();
    m_highscoreBackToMenu.hide();
    m_pauseTitleLabel.hide();
    m_pauseCancelButton.hide();
    m_pauseContinueButton.hide();
    m_gameoverTitleLabel.hide();
    m_gameoverScoreLabel.hide();
    m_gameoverPlayerNameField.hide();
    m_gameoverSaveScoreButton.hide();
    m_gameoverBackToMenuButton.hide();
    m_authorLabel.hide();
}

void MenuView::showMainMenu()
{
    hideAllMenu();
    m_mainTitleLabel.show();
    m_mainStartButton.show();
    m_mainHighscoreButton.show();
    m_mainQuitButton.show();
    m_authorLabel.show();
}

void MenuView::showHighscoreMenu()
{
    hideAllMenu();
    m_highscoreTitleLabel.show();
    m_highscoreTable.show();
    m_highscoreBackToMenu.show();
    m_authorLabel.show();
}

void MenuView::showPauseMenu()
{
    hideAllMenu();
    m_pauseTitleLabel.show();
    m_pauseCancelButton.show();
    m_pauseContinueButton.show();
    m_authorLabel.show();
}

void MenuView::showGameoverMenu()
{
    hideAllMenu();
    m_gameoverTitleLabel.show();
    m_gameoverScoreLabel.show();
    m_gameoverPlayerNameField.show();
    m_gameoverSaveScoreButton.show();
    m_gameoverBackToMenuButton.show();
    m_authorLabel.show();
}

void MenuView::startGame()
{
    emit startClicked();
}

void MenuView::continueGame()
{
    emit continueClicked();
}

void MenuView::cancelGame()
{
    emit cancelClicked();
}

void MenuView::quitGame()
{
    emit quitClicked();
}

void MenuView::saveScore()
{
    emit saveClicked();
}
