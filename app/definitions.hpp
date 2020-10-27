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
    const int    animationLevelUpFrameWight      = 200;
    const int    animationLevelUpFrameHeight     = 27;
    const int    animationLevelUpNumOfFrames     = 11;
    const int    collisionDamageFactor           = 300;
    const int    defaultBulletSpeed              = 15;
    const int    shortBackgroundAnimTimeDelay    = 5;
    const int    defaultBackgroundAnimTimeDelay  = 10;
    const int    healthRewardValue               = 100;
    const int    maxAnimationFrames              = 10;
    const int    maxAnimationFrameIdx            = 9;
    const int    minBackgroundDirectionRange     = 135;
    const int    maxBackgroundDirectionRange     = 225;
    const int    maxNumOfLevel                   = 10;
    const int    maxWeaponTypes                  = 3;
    const int    maxWeaponLevel                  = 5;
    const int    minEnemySpawnTimeDelay          = 1000;
    const int    maxEnemySpawnTimeDelay          = 5000;
    const int    minBackgroundItemSpawnTimeDelay = 3000;
    const int    maxBackgroundItemSpawnTimeDelay = 10000;
    const int    moveVectorLength                = 5;
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
    const int defaultPlayerMoveTimeDelay = 15;
    const int defaultPlayerFireTimeDelay = 100;

    //Enemies
    const int enemy1Level = 1;
    const int enemy1MaxHealthPoints = 30;
    const int enemy1BaseDamage = 10;
    const int enemy1MoveTimeDelay = 40;
    const int enemy1FireTimeDelay = 1000;
    const int enemy1RightMoveDirection = 170;
    const int enemy1DownMoveDirection = 180;
    const int enemy1LeftMoveDirection = 190;
    const int enemy1FireBulletOffset = 28;

    const int enemy2Level = 2;
    const int enemy2MaxHealthPoints = 40;
    const int enemy2BaseDamage = 5;
    const int enemy2MoveTimeDelay = 30;
    const int enemy2FireTimeDelay = 300;
    const int enemy2MinDirectionRange = 135;
    const int enemy2MaxDirectionRange = 225;
    const int enemy2XCoordinateOffset = 50;
    const int enemy2FireBulletOffset = 28;

    const int enemy3Level = 3;
    const int enemy3MaxHealthPoints = 100;
    const int enemy3BaseDamage = 8;
    const int enemy3MoveTimeDelay = 20;
    const int enemy3FireTimeDelay = 200;
    const int enemy3MoveSlowFactor = 25;
    const int enemy3RotateLeftSideMinBorder = 60;
    const int enemy3RotateLeftSideMaxBorder = 180;
    const int enemy3RotateRightSideMinBorder = 180;
    const int enemy3RotateRightSideMaxBorder = 300;
    const int enemy3FireSideOffset = 14;
    const int enemy3BulletSpeed = (def::defaultBulletSpeed - 5);
    const int enemy3RotateAngle = 3;
    const int enemy3MinMoveSlowFactor = 3;

    const int enemy4Level = 4;
    const int enemy4MaxHealthPoints = 120;
    const int enemy4BaseDamage = 20;
    const int enemy4MoveTimeDelay = 50;
    const int enemy4FireTimeDelay = 500;
    const int enemy4SpeedupFireTimeDelay = 250;
    const int enemy4BulletSpeed = def::defaultBulletSpeed - 6;
    const int enemy4BulletYCoordinateOffsetInPx = 12;
    const int enemy4JumpTimeDelay =
        (animationFrameDuration * maxAnimationFrames)
        / enemy4MoveTimeDelay;
    const int enemy4JumpMoveOffsetInPx = 5;

    const int enemy5Level = 5;
    const int enemy5MaxHealthPoints = 500;
    const int enemy5BaseDamage = 10;
    const int enemy5MoveTimeDelay = 70;
    const int enemy5FireTimeDelay = 1500;
    const int enemy5AnimationFrameWight = (animationFrameWight * 2);
    const int enemy5AnimationFrameHeight = animationFrameHeight;
    const int enemy5StartXCoordinate = def::animationFrameWight + 10;
    const int enemy5StartYCoordinate = -enemy5AnimationFrameHeight + 5;
    const int enemy5YCoordinateOffsetInPx = 1;
    const int enemy5ChangeMoveSideTimeDelay = 70;
    const int enemy5XCoordinateOffsetInPx = 2;
    const int enemy5SmallWeaponDamage = 30;
    const int enemy5SmallWeaponXOffset = 42;
    const int enemy5SmallWeaponBulletMoveTimeDelay = def::defaultBulletSpeed + 5;
    const int enemy5MediumWeaponDamage = 40;
    const int enemy5MediumWeaponXOffset = 32;
    const int enemy5MediumWeaponBulletMoveTimeDelay = def::defaultBulletSpeed + 8;
    const int enemy5BigWeaponDamage = 60;
    const int enemy5BigWeaponYOffset = def::enemy5AnimationFrameHeight / 2;
    const int enemy5BigWeaponBulletMoveTimeDelay = def::defaultBulletSpeed + 12;

    const int enemy6Level = 6;
    const int enemy6MaxHealthPoints = 2000;
    const int enemy6BaseDamage = 0;
    const int enemy6MoveTimeDelay = 100;
    const int enemy6FireTimeDelay = 1000;
    const int enemy6AnimationFrameWidth = 64;
    const int enemy6AnimationFrameHeight = 256;
    const int enemy6StartXCoordinateOffset = 112;
    const int enemy6MinStartYCoordinate = -48;
    const int enemy6MaxStartYCoordinate = 68;
    const int enemy6MinRotationDegrees = 65;
    const int enemy6MaxRotationDegrees = 80;
    const int enemy6MinRotationTimeDelay = 250;
    const int enemy6MaxRotationTimeDelay = 290;


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

    const int maxDegree = 360;

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
