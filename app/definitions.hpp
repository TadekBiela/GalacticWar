#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <QString>

namespace def
{
    const int    animationFrameDuration          = 100;
    const int    animationFrameWight             = 64;
    const int    animationFrameHeight            = 64;
    const int    animationSmallFrameWight        = 32;
    const int    animationSmallFrameHeight       = 32;
    const int    animationBigFrameWight          = 200;
    const int    animationBigFrameHeight         = 30;
    const int    collisionDamageFactor           = 300;
    const int    defaultBulletSpeed              = 20;
    const int    shortBackgroundAnimTimeDelay    = 5;
    const int    defaultBackgroundAnimTimeDelay  = 10;
    const int    healthRewardValue               = 100;
    const int    maxAnimationFrames              = 10;
    const int    maxAnimationFrameIdx            = 9;
    const int    maxNumOfLevel                   = 10;
    const int    maxWeaponTypes                  = 3;
    const int    maxWeaponLevel                  = 5;
    const int    minEnemySpawnTimeDelay          = 1000;
    const int    maxEnemySpawnTimeDelay          = 5000;
    const int    minBackgroundItemSpawnTimeDelay = 3000;
    const int    maxBackgroundItemSpawnTimeDelay = 10000;
    const int    moveVectorLength                = 10;
    const int    percentDistTabSize              = 100;
    const double pi                              = 3.14159265;
    const double radianConversionFactor          = pi / 180;
    const int    valueBarPositionOffsetX         = 15;
    const int    valueBarPositionOffsetY         = 5;
    const int    valueBarSizeOffsetX             = 30;
    const int    valueBarSizeOffsetY             = 14;
    const int    valueLabelPositionOffset        = 5;
    const int    valueLabelSizeOffset            = 10;

    //Player default configuration
    const int maxPlayerHealth            = 2000;
    const int defaultPlayerMoveTimeDelay = 20;
    const int defaultPlayerFireTimeDelay = 100;

    //Reward default configuration
    const int maxNumOfSpecialRewards         = 4;
    const int maxTier                        = 6;
    const int minRewardPosOffset             = -30;
    const int maxRewardPosOffset             = 30;
    const int defaultRewardDestroyTimeDelay  = 5000;
    const int minPointsForBronzeCoin         = 10;
    const int maxPointsForBronzeCoin         = 30;
    const int minPointsForSilverCoin         = 50;
    const int maxPointsForSilverCoin         = 100;
    const int minPointsForGoldCoin           = 150;
    const int maxPointsForGoldCoin           = 300;

    //Window size
    const int windowWight     = 604;
    const int windowHeight    = 804;

    //Scene size
    const int sceneWight      = 600;
    const int sceneHeight     = 800;
    const int halfSceneWight  = sceneWight  / 2;
    const int halfSceneHeight = sceneHeight / 2;

    //Labels
    const int labelWidth                  = 500;
    const int labelHeight                 = 100;
    const int labelPositionX              = halfSceneWight - (labelWidth / 2);
    const int labelPositionY              = (halfSceneHeight / 3) - (labelHeight / 2);
    const int gameoverScoreLabelPositionX = halfSceneWight    - (labelWidth  / 2);
    const int gameoverScoreLabelPositionY = (sceneHeight / 3) - (labelHeight / 2);
    const int authorLabelWidth            = 150;
    const int authorLabelHeight           = 15;
    const int authorLabelPositionX        = sceneWight  - authorLabelWidth;
    const int authorLabelPositionY        = sceneHeight - authorLabelHeight;

    //Tabels
    const int highscoreTableWight     = 500;
    const int highscoreTableHeight    = 400;
    const int highscoreTablePositionX = halfSceneWight - (highscoreTableWight / 2);
    const int highscoreTablePositionY = labelPositionY + labelHeight + 30;

    //EditLines
    const int gameoverPlayerNameFieldWidth     = 300;
    const int gameoverPlayerNameFieldHeight    = 50;
    const int gameoverPlayerNameFieldPositionX = halfSceneWight - (gameoverPlayerNameFieldWidth / 2);
    const int gameoverPlayerNameFieldPositionY = gameoverScoreLabelPositionY
                                               + labelHeight + 25;

    //Buttons
    const int buttonWight  = 200;
    const int buttonHeight = 50;
    const int centerButtonPositionX         = halfSceneWight - (buttonWight / 2);
    const int startButtonPositionY          = labelPositionY + labelHeight + 100;
    const int highscoreButtonPositionY      = startButtonPositionY     + buttonHeight + 25;
    const int quitButtonPositionY           = highscoreButtonPositionY + buttonHeight + 25;
    const int highscoreBackButtonPositionY  = highscoreTablePositionY  + highscoreTableHeight + 25;
    const int pauseAbortButtonPositionX     = halfSceneWight + 25;
    const int pauseContinueButtonPositionX  = halfSceneWight - buttonWight - 25;
    const int pauseBottomButtonPositionY    = halfSceneHeight;
    const int gameoverSaveButtonPositionX   = pauseAbortButtonPositionX;
    const int gameoverBackButtonPositionX   = pauseContinueButtonPositionX;
    const int gameoverBottomButtonPositionY = gameoverPlayerNameFieldPositionY
                                            + gameoverPlayerNameFieldHeight + 100;
    //Interface
    const int healthGraphicsCenterPositionX = 130;
    const int healthGraphicsCenterPositionY = sceneHeight - 45;
    const int scoreGraphicsCenterPositionX  = sceneWight  - 130;
    const int scoreGraphicsCenterPositionY  = healthGraphicsCenterPositionY;
    const int levelGraphicsCenterPositionX  = halfSceneWight;
    const int levelGraphicsCenterPositionY  = sceneHeight - 45;

    //Defalut directions
    const int up    = 0;
    const int down  = 180;
    const int right = 90;
    const int left  = 270;

    //Texts
    const QString authorTitle = "Created by TED";
    const QString backText = "BACK";
    const QString continueText = "CONTINUE";
    const QString gameTitle = "GALACTIC WAR";
    const QString gameoverText = "GAME OVER";
    const QString highscoreText = "HIGH SCORE";
    const QString pauseText = "PAUSE";
    const QString startgameText = "START GAME";
    const QString saveText = "SAVE";
    const QString quitText = "QUIT";

    //Colors
    const QString darkRedHex    = "#DE0101";
    const QString darkYellowHex = "#FCCD10";
}

#endif // DEFINITIONS_HPP
