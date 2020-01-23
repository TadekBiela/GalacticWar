#include "generalview.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"
#include "soundstorage.hpp"
#include <QString>
#include <QGraphicsEffect>

GeneralView::GeneralView()
                         : m_scene(0, 0, def::sceneWight, def::sceneHeight, this),
                           m_view(&m_scene, this),
                           m_title("GALACTIC WAR", this),
                           m_author("Created by TED", this),
                           m_pause("PAUSE", this),
                           m_player("", this),
                           m_score("0", this),
                           m_startButton("START GAME", this),
                           m_highScoreButton("HIGH SCORE", this),
                           m_quitButton("QUIT", this),
                           m_backToMenuButton("BACK", this),
                           m_backToMenuButton2("BACK", this),
                           m_saveAfterGameOver("SAVE", this),
                           m_continueButton("CONTINUE", this),
                           m_highScoreList(this),
                           m_healthGraphics(this),
                           m_healthBar(this),
                           m_levelGraphics(this),
                           m_levelText(this),
                           m_scoreGraphics(this),
                           m_scoreBar(this)
{
    setFixedSize(QSize(def::windowWight, def::windowHeight));
    m_view.setGeometry(1, 1, def::sceneWight + 2, def::sceneHeight + 2);

    int defaultButtonWight  = 200;
    int defaultButtonHeight = 50;
    int buttonBetweenOffset = 15;
    int startButtonSection  = def::sceneHeight / 4 + 50;
    int buttonOffsetX       = (def::sceneWight / 2) - (defaultButtonWight / 2);
    int buttonoffsetY       = defaultButtonHeight + buttonBetweenOffset;

    QFont   bigFont("Arial", 40, 3);
    QFont   normalFont("Arial", 30, 3);
    QFont   smallFont("Arial", 15, 3);
    QString style("border: 1px solid white; color: #FFFFFF");

    //Menu setup
    m_title.setFont(normalFont);
    m_title.setAlignment(Qt::AlignCenter);
    m_title.setGeometry((def::sceneWight / 2) - 200, def::sceneHeight / 8, 400, 100);
    m_title.setStyleSheet(style);
    m_startButton.setGeometry(    buttonOffsetX, startButtonSection,                     defaultButtonWight, defaultButtonHeight);
    m_highScoreButton.setGeometry(buttonOffsetX, startButtonSection + buttonoffsetY,     defaultButtonWight, defaultButtonHeight);
    m_quitButton.setGeometry(     buttonOffsetX, startButtonSection + buttonoffsetY * 2, defaultButtonWight, defaultButtonHeight);
    m_author.setGeometry(def::sceneWight - 100, def::sceneHeight - 30, 100, 30);

    //Highscore setup
    m_highScoreList.setStyleSheet(QString("border-style: solid; border-width: 2px; border-radius: 5px; border-color: #FFFFFF; color: #FFFFFF; background-color: transparent;"));
    m_highScoreList.addItem("Player\t\t\tScore");
    m_highScoreList.setGeometry(def::sceneWight / 2 - 150,
                                m_title.pos().y() + m_title.size().height() + 30,
                                300,
                                300);
    m_backToMenuButton.setGeometry(buttonOffsetX,
                                   m_highScoreList.pos().y() + m_highScoreList.size().height() + 30,
                                   defaultButtonWight,
                                   defaultButtonHeight);

    //Pause setup
    m_pause.setFont(bigFont);
    m_pause.setAlignment(Qt::AlignCenter);
    m_pause.setStyleSheet(style);
    m_pause.setGeometry(def::sceneWight / 2 - 200,
                        def::sceneHeight / 3,
                        400,
                        100);
    m_continueButton.setGeometry(buttonOffsetX - 125,
                                 m_highScoreList.pos().y() + m_highScoreList.size().height() + 30,
                                 defaultButtonWight,
                                 defaultButtonHeight);

    //Gameover setup
    m_score.setFont(bigFont);
    m_score.setAlignment(Qt::AlignCenter);
    m_score.setStyleSheet(style);
    m_score.setGeometry(def::sceneWight / 2 - 200,
                        def::sceneHeight / 4,
                        400,
                        100);
    m_player.setFont(smallFont);
    m_player.setAlignment(Qt::AlignCenter);
    m_player.setStyleSheet(QString("border-style: solid; border-width: 2px; border-radius: 5px; border-color: #FFFFFF; color: #FFFFFF; background-color: transparent;"));
    m_player.setGeometry(def::sceneWight / 2 - 150,
                         m_score.pos().y() + m_score.size().height() + 50,
                         300,
                         50);
    m_backToMenuButton2.setGeometry(buttonOffsetX + 125,
                                    m_highScoreList.pos().y() + m_highScoreList.size().height() + 30,
                                    defaultButtonWight,
                                    defaultButtonHeight);
    m_saveAfterGameOver.setGeometry(buttonOffsetX - 125,
                                    m_highScoreList.pos().y() + m_highScoreList.size().height() + 30,
                                    defaultButtonWight,
                                    defaultButtonHeight);

    //HealthView setup
    m_healthGraphics.setCursor(QCursor(Qt::CrossCursor));
    m_healthGraphics.setFocusProxy(&m_view);
    m_healthGraphics.setStyleSheet(style);
    m_healthGraphics.setGeometry(10,
                                 def::sceneHeight - 50,
                                 220,
                                 40);
    m_healthBar.setGeometry(m_healthGraphics.pos().x() + 8,
                            m_healthGraphics.pos().y() + 8 ,
                            m_healthGraphics.size().width()  - 16,
                            m_healthGraphics.size().height() - 16);
    m_healthBar.setCursor(QCursor(Qt::CrossCursor));
    m_healthBar.setFocusProxy(&m_view);
    m_healthBar.setTextVisible(false);
    m_healthBar.setStyleSheet(QString("QProgressBar::chunk { background-color: #DE0101; }"));

    //LevelView setup
    m_levelGraphics.setCursor(QCursor(Qt::CrossCursor));
    m_levelGraphics.setFocusProxy(&m_view);
    m_levelGraphics.setStyleSheet(style);
    m_levelGraphics.setGeometry(def::sceneWight / 2 - 40,
                                def::sceneHeight - 90,
                                80,
                                80);
    m_levelText.setCursor(QCursor(Qt::CrossCursor));
    m_levelText.setFocusProxy(&m_view);
    m_levelText.setFont(normalFont);
    m_levelText.setAlignment(Qt::AlignCenter);
    m_levelText.setStyleSheet(style);
    m_levelText.setNum(1);
    m_levelText.setGeometry(m_levelGraphics.pos().x() + 8,
                            m_levelGraphics.pos().y() + 8 ,
                            m_levelGraphics.size().width()  - 16,
                            m_levelGraphics.size().height() - 16);

    //ScoreView setup
    m_scoreGraphics.setCursor(QCursor(Qt::CrossCursor));
    m_scoreGraphics.setFocusProxy(&m_view);
    m_scoreGraphics.setStyleSheet(style);
    m_scoreGraphics.setGeometry(def::sceneWight - 230,
                                def::sceneHeight - 50,
                                220,
                                40);
    m_scoreBar.setGeometry(m_scoreGraphics.pos().x() + 8,
                           m_scoreGraphics.pos().y() + 8 ,
                           m_scoreGraphics.size().width()  - 16,
                           m_scoreGraphics.size().height() - 16);
    m_scoreBar.setCursor(QCursor(Qt::CrossCursor));
    m_scoreBar.setFocusProxy(&m_view);
    m_scoreBar.setTextVisible(false);
    m_scoreBar.setStyleSheet(QString("QProgressBar::chunk { background-color: #FCCD10; }"));

    connect(&m_startButton,       SIGNAL(clicked()), this, SLOT(start()));
    connect(&m_highScoreButton,   SIGNAL(clicked()), this, SLOT(highScore()));
    connect(&m_quitButton,        SIGNAL(clicked()), this, SLOT(quitGame()));
    connect(&m_backToMenuButton,  SIGNAL(clicked()), this, SLOT(menu()));
    connect(&m_backToMenuButton2, SIGNAL(clicked()), this, SLOT(abort()));
    connect(&m_saveAfterGameOver, SIGNAL(clicked()), this, SLOT(savePlayerScore()));
    connect(&m_continueButton,    SIGNAL(clicked()), this, SLOT(continueButtonClicked()));
    connect(&m_view, SIGNAL(mousePressed(QMouseEvent*)),  this, SLOT(mousePressEvent(QMouseEvent*)));
    connect(&m_view, SIGNAL(mouseReleased(QMouseEvent*)), this, SLOT(mouseReleaseEvent(QMouseEvent*)));
    connect(&m_view, SIGNAL(mouseMoved(QMouseEvent*)),    this, SLOT(mouseMoveEvent(QMouseEvent*)));
    menu();
}

GeneralView::~GeneralView()
{

}

void GeneralView::menu()
{
    m_title.setVisible(true);
    m_author.setVisible(true);
    m_pause.setVisible(false);
    m_player.setVisible(false);
    m_score.setVisible(false);
    m_startButton.setVisible(true);
    m_highScoreButton.setVisible(true);
    m_quitButton.setVisible(true);
    m_backToMenuButton.setVisible(false);
    m_backToMenuButton2.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_continueButton.setVisible(false);
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);
    m_healthGraphics.setVisible(false);
    m_healthBar.setVisible(false);
    m_levelGraphics.setVisible(false);
    m_levelText.setVisible(false);
    m_scoreGraphics.setVisible(false);
    m_scoreBar.setVisible(false);
}

void GeneralView::start()
{
    m_title.setVisible(false);
    m_author.setVisible(false);
    m_pause.setVisible(false);
    m_player.setVisible(false);
    m_score.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(false);
    m_backToMenuButton2.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_continueButton.setVisible(false);
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);
    m_healthGraphics.setVisible(true);
    m_healthBar.setVisible(true);
    m_levelGraphics.setVisible(true);
    m_levelText.setVisible(true);
    m_scoreGraphics.setVisible(true);
    m_scoreBar.setVisible(true);

    m_view.setCursor(QCursor(Qt::CrossCursor));
    m_view.setGraphicsEffects(0, 0);
    m_scene.clear();
    emit startGame();
}

void GeneralView::pauseGame()
{
    m_title.setVisible(false);
    m_author.setVisible(false);
    m_pause.setVisible(true);
    m_player.setVisible(false);
    m_score.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(false);
    m_backToMenuButton2.setVisible(true);
    m_saveAfterGameOver.setVisible(false);
    m_continueButton.setVisible(true);
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);
    m_healthGraphics.setVisible(false);
    m_healthBar.setVisible(false);
    m_levelGraphics.setVisible(false);
    m_levelText.setVisible(false);
    m_scoreGraphics.setVisible(false);
    m_scoreBar.setVisible(false);

    m_view.setCursor(QCursor(Qt::ArrowCursor));
    m_view.setGraphicsEffects(0.5, 5);
    m_view.stopAllItems();
    m_isGamePaused = true;
}

void GeneralView::continueGame()
{
    m_title.setVisible(false);
    m_author.setVisible(false);
    m_pause.setVisible(false);
    m_player.setVisible(false);
    m_score.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(false);
    m_backToMenuButton2.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_continueButton.setVisible(false);
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);
    m_healthGraphics.setVisible(true);
    m_healthBar.setVisible(true);
    m_levelGraphics.setVisible(true);
    m_levelText.setVisible(true);
    m_scoreGraphics.setVisible(true);
    m_scoreBar.setVisible(true);

    m_view.setCursor(QCursor(Qt::CrossCursor));
    m_view.setGraphicsEffects(0, 0);
    m_view.startAllItems();
    m_isGamePaused = false;
}


void GeneralView::abort()
{
    m_scene.clear();
    emit abortGame();
    menu();
}

void GeneralView::gameOver(int score)
{
    m_scene.clear();
    m_score.setText(QString::number(score));

    m_title.setVisible(false);
    m_author.setVisible(true);
    m_pause.setVisible(false);
    m_player.setVisible(true);
    m_score.setVisible(true);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(false);
    m_backToMenuButton2.setVisible(true);
    m_saveAfterGameOver.setVisible(true);
    m_continueButton.setVisible(false);
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);
    m_healthGraphics.setVisible(false);
    m_healthBar.setVisible(false);
    m_levelGraphics.setVisible(false);
    m_levelText.setVisible(false);
    m_scoreGraphics.setVisible(false);
    m_scoreBar.setVisible(false);
}

void GeneralView::highScore()
{
    m_title.setVisible(true);
    m_author.setVisible(true);
    m_pause.setVisible(false);
    m_player.setVisible(false);
    m_score.setVisible(false);
    m_startButton.setVisible(false);
    m_highScoreButton.setVisible(false);
    m_quitButton.setVisible(false);
    m_backToMenuButton.setVisible(true);
    m_backToMenuButton2.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_continueButton.setVisible(false);
    m_highScoreList.setVisible(true);
    m_view.setVisible(true);
    m_healthGraphics.setVisible(false);
    m_healthBar.setVisible(false);
    m_levelGraphics.setVisible(false);
    m_levelText.setVisible(false);
    m_scoreGraphics.setVisible(false);
    m_scoreBar.setVisible(false);
}

void GeneralView::quitGame()
{
    delete g_soundStorage;
    delete g_imageStorage;
    close();
}

void GeneralView::addGameObject(QGraphicsItem* newObject)
{
    m_scene.addItem(newObject);
}

void GeneralView::mousePressEvent(QMouseEvent* event)
{
    if(!m_isGamePaused)
    {
        emit mousePressed();
    }
}

void GeneralView::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseReleased();
}

void GeneralView::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoved(event->localPos());
}

void GeneralView::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
        emit escPressed();
    }
}

void GeneralView::leaveEvent(QEvent *event)
{
    event->ignore();
    emit escPressed();
}

void GeneralView::enterEvent(QEvent *event)
{
    event->ignore();
    emit escPressed();
}

void GeneralView::continueButtonClicked()
{
    emit escPressed();
}

void GeneralView::savePlayerScore()
{
    PlayerScore newPlayerScore;
    newPlayerScore.first  = m_score.text().toInt();
    newPlayerScore.second = m_player.text();

    emit save(newPlayerScore);
    menu();
}

void GeneralView::updateHighScoreList(PlayerScoreMapIterator iterator, int size)
{
    m_highScoreList.clear();
    m_highScoreList.addItem("Player\t\t\tScore");
    for(int i = 0; i < size; i++)
    {
        iterator--;
        m_highScoreList.addItem(iterator.value() + "\t\t\t" + QString::number(iterator.key()));
    }
}

//HealthView section
void GeneralView::updateHealth(int value)
{
    m_healthBar.setValue(value < 100 ? value : 100);
}

//LevelView section
void GeneralView::updateLevel(int value)
{
    m_levelText.setNum(value);
}

//ScoreView section
void GeneralView::updateScore(int value)
{
    m_scoreBar.setValue(value < 100 ? value : 100);
}
