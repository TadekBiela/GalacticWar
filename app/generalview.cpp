#include "generalview.hpp"
#include "definitions.hpp"
#include <QString>

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
                           m_highScoreList(this)
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
    QString style("border: 1px solid black");

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
    m_player.setStyleSheet(style);
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

    connect(&m_startButton,       SIGNAL(clicked()), this, SLOT(start()));
    connect(&m_highScoreButton,   SIGNAL(clicked()), this, SLOT(highScore()));
    connect(&m_quitButton,        SIGNAL(clicked()), this, SLOT(close()));
    connect(&m_backToMenuButton,  SIGNAL(clicked()), this, SLOT(menu()));
    connect(&m_backToMenuButton2, SIGNAL(clicked()), this, SLOT(menu()));
    connect(&m_saveAfterGameOver, SIGNAL(clicked()), this, SLOT(savePlayerScore()));

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
    m_highScoreList.setVisible(false);
    m_view.setVisible(false);
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
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);

    emit startGame();
}

void GeneralView::pause()
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
    m_backToMenuButton2.setVisible(false);
    m_saveAfterGameOver.setVisible(false);
    m_highScoreList.setVisible(false);
    m_view.setVisible(true);

    emit pauseGame();
}

void GeneralView::gameOver(int score)
{
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
    m_highScoreList.setVisible(false);
    m_view.setVisible(false);
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
    m_highScoreList.setVisible(true);
    m_view.setVisible(false);
}

void GeneralView::addGameObject(QGraphicsItem* newObject)
{
    m_scene.addItem(newObject);
}

void GeneralView::mousePressEvent(QMouseEvent* event)
{
    emit mousePressed();
}

void GeneralView::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseReleased();
}

void GeneralView::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoved(event->localPos());
}

void GeneralView::savePlayerScore()
{
    PlayerScore newPlayerScore;
    newPlayerScore.first  = m_score.text().toInt();
    newPlayerScore.second = m_player.text();

    emit save(newPlayerScore);
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
