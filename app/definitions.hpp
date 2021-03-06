
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <QString>

namespace def
{
    const int    animationFrameDuration          = 100;
    const int    animationFrameWidth             = 64;
    const int    animationFrameHeight            = 64;
    const int    animationSmallFrameWidth        = 32;
    const int    animationSmallFrameHeight       = 32;
    const int    animationLevelUpFrameWidth      = 200;
    const int    animationLevelUpFrameHeight     = 27;
    const int    animationLevelUpNumOfFrames     = 11;
    const int    collisionDamageFactor           = 300;
    const int    defaultBulletSpeed              = 15;
    const int    shortBackgroundAnimTimeDelay    = 5;
    const int    defaultBackgroundAnimTimeDelay  = 15;
    const int    healthRewardValue               = 100;
    const int    maxAnimationFrames              = 10;
    const int    maxAnimationFrameIdx            = 9;
    const int    minBackgroundDirectionRange     = 135;
    const int    maxBackgroundDirectionRange     = 225;
    const int maxNumOfHighScoreRecords = 20;
    const int    maxNumOfLevel                   = 10;
    const int    maxWeaponTypes                  = 3;
    const int    maxWeaponLevel                  = 5;
    const int    maxWeaponLevelIdx               = 4;
    const int    minEnemySpawnTimeDelay          = 1000;
    const int    maxEnemySpawnTimeDelay          = 5000;
    const int minEnemySpawnTimeDelayDecreaseFactor = 100;
    const int maxEnemySpawnTimeDelayDecreaseFactor = 300;
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
    const int enemy3BulletSpeed = (defaultBulletSpeed - 5);
    const int enemy3RotateAngle = 3;
    const int enemy3MinMoveSlowFactor = 3;

    const int enemy4Level = 4;
    const int enemy4MaxHealthPoints = 220;
    const int enemy4BaseDamage = 20;
    const int enemy4MoveTimeDelay = 50;
    const int enemy4FireTimeDelay = 500;
    const int enemy4SpeedupFireTimeDelay = 250;
    const int enemy4BulletSpeed = defaultBulletSpeed - 6;
    const int enemy4BulletYCoordinateOffsetInPx = 12;
    const int enemy4JumpTimeDelay =
        (animationFrameDuration * maxAnimationFrames)
        / enemy4MoveTimeDelay;
    const int enemy4JumpMoveOffsetInPx = 5;
    const int enemy4MoveYCoordinateOffset = 8;

    const int enemy5Level = 5;
    const int enemy5MaxHealthPoints = 1100;
    const int enemy5BaseDamage = 10;
    const int enemy5MoveTimeDelay = 30;
    const int enemy5FireTimeDelay = 1000;
    const int enemy5AnimationFrameWidth = (animationFrameWidth * 2);
    const int enemy5AnimationFrameHeight = animationFrameHeight;
    const int enemy5StartXCoordinate = animationFrameWidth + 10;
    const int enemy5StartYCoordinate = -enemy5AnimationFrameHeight + 5;
    const int enemy5YCoordinateOffsetInPx = 1;
    const int enemy5ChangeMoveSideTimeDelay = 70;
    const int enemy5XCoordinateOffsetInPx = 2;
    const int enemy5SmallWeaponDamage = 30;
    const int enemy5SmallWeaponXOffset = 42;
    const int enemy5SmallWeaponBulletMoveTimeDelay = defaultBulletSpeed + 5;
    const int enemy5MediumWeaponDamage = 40;
    const int enemy5MediumWeaponXOffset = 32;
    const int enemy5MediumWeaponBulletMoveTimeDelay = defaultBulletSpeed + 8;
    const int enemy5BigWeaponDamage = 60;
    const int enemy5BigWeaponYOffset = enemy5AnimationFrameHeight / 2;
    const int enemy5BigWeaponBulletMoveTimeDelay = defaultBulletSpeed + 12;

    const int enemy6Level = 6;
    const int enemy6MaxHealthPoints = 2000;
    const int enemy6BaseDamage = 0;
    const int enemy6MoveTimeDelay = 90;
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
    const int enemyTurretDoubleCannonDamage = 20;
    const int enemyTurretDoubleCannonFrontStartDirection = 0;
    const int enemyTurretDoubleCannonBackStartDirection = 180;
    const int enemyTurretDoubleCannonFireTimeDelay = 500;
    const int enemyTurretDoubleCannonRotateTimeDelay = 100;
    const int enemyTurretTripleCannonDamage = 30;
    const int enemyTurretTripleCannonMiddleStartDirection = 45;
    const int enemyTurretTripleCannonFireTimeDelay = 300;
    const int enemyTurretTripleCannonRotateTimeDelay = 80;
    const int enemyTurretFrontYCoordinateOffset = 34;
    const int enemyTurretMiddleYCoordinateOffset = 18;
    const int enemyTurretBackYCoordinateOffset = 60;
    const int enemyTurretRotationDegreeRange = 90;
    const int enemyTurretPixmapCenterPointHightOffset = 3;
    const int enemyTurretTripleCannonMaxFireCannonOffsets = 3;

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
    const int windowWidth     = 604;
    const int windowHeight    = 804;

    //Scene size
    const int sceneWidth      = 600;
    const int sceneHeight     = 800;
    const int halfSceneWidth  = sceneWidth  / 2;
    const int halfSceneHeight = sceneHeight / 2;

    //Labels
    const int labelWidth                  = 500;
    const int labelHeight                 = 100;
    const int labelPositionX              = halfSceneWidth - (labelWidth / 2);
    const int labelPositionY              = (halfSceneHeight / 3) - (labelHeight / 2);
    const int gameoverScoreLabelPositionX = halfSceneWidth    - (labelWidth  / 2);
    const int gameoverScoreLabelPositionY = (sceneHeight / 3) - (labelHeight / 2);
    const int authorLabelWidth            = 150;
    const int authorLabelHeight           = 15;
    const int authorLabelPositionX        = sceneWidth  - authorLabelWidth;
    const int authorLabelPositionY        = sceneHeight - authorLabelHeight;

    //Tabels
    const int highscoreTableWidth     = 500;
    const int highscoreTableHeight    = 400;
    const int highscoreTablePositionX = halfSceneWidth - (highscoreTableWidth / 2);
    const int highscoreTablePositionY = labelPositionY + labelHeight + 30;

    //EditLines
    const int gameoverPlayerNameFieldWidth     = 300;
    const int gameoverPlayerNameFieldHeight    = 50;
    const int gameoverPlayerNameFieldPositionX = halfSceneWidth - (gameoverPlayerNameFieldWidth / 2);
    const int gameoverPlayerNameFieldPositionY = gameoverScoreLabelPositionY
                                               + labelHeight + 25;
    //Checkbox
    const int settingsMusicOnOffWidth = 50;
    const int settingsMusicOnOffHeight = 200;
    const int settingsMusicOnOffPoxitionX = halfSceneWidth;
    const int settingsMusicOnOffPoxitionY = labelPositionY + 100;

    //Buttons
    const int buttonWidth  = 200;
    const int buttonHeight = 50;
    const int buttonBetweenDistance = 25;
    const int centerButtonPositionX = halfSceneWidth - (buttonWidth / 2);
    const int startButtonPositionY = labelPositionY + labelHeight + 100;
    const int highscoreButtonPositionY = startButtonPositionY     + buttonHeight + buttonBetweenDistance;
    const int settingsButtonPositionY = highscoreButtonPositionY + buttonHeight + buttonBetweenDistance;
    const int quitButtonPositionY = settingsButtonPositionY + buttonHeight + buttonBetweenDistance;
    const int highscoreBackButtonPositionY = highscoreTablePositionY  + highscoreTableHeight + buttonBetweenDistance;
    const int settingsBackToMenuButtonPositionX = halfSceneWidth - buttonWidth - buttonBetweenDistance;
    const int settingsMainButtonPositionY = sceneHeight - buttonHeight - 100;
    const int settingsSaveButtonPositionX = halfSceneWidth + buttonBetweenDistance;
    const int pauseCancelButtonPositionX = halfSceneWidth - buttonWidth - buttonBetweenDistance;
    const int pauseContinueButtonPositionX  = halfSceneWidth + buttonBetweenDistance;
    const int pauseBottomButtonPositionY    = halfSceneHeight;
    const int pauseSettingsButtonPositionX = halfSceneWidth - (buttonWidth / 2);
    const int pauseSettingsButtonPositionY = pauseBottomButtonPositionY + buttonHeight + buttonBetweenDistance;
    const int gameoverSaveButtonPositionX   = pauseContinueButtonPositionX;
    const int gameoverBackButtonPositionX   = pauseCancelButtonPositionX;
    const int gameoverBottomButtonPositionY = gameoverPlayerNameFieldPositionY
                                            + gameoverPlayerNameFieldHeight + 100;

    //Settings menu
    //Labels
    const int settingsLabelWidth = 400;
    const int settingsLabelHeight = 100;
    const int settingsLabelPositionX = halfSceneWidth - (settingsLabelWidth / 2);
    const int settingsMusicLabelPositionY = labelPositionY + settingsLabelHeight + buttonBetweenDistance;
    const int settingsSoundsLabelPositionY = settingsMusicLabelPositionY + settingsLabelHeight + buttonBetweenDistance;
    const int settingsControlLabelPositionY = settingsSoundsLabelPositionY + settingsLabelHeight + buttonBetweenDistance;
    //Check boxs
    const int settingsCheckBoxWidth = 30;
    const int settingsCheckBoxHeight = settingsCheckBoxWidth;
    const int settingsCheckBoxPositionX = settingsLabelPositionX + settingsLabelWidth - settingsCheckBoxWidth - 10;
    const int settingsMusicCheckBoxPositionY = settingsMusicLabelPositionY + 10;
    const int settingsSoundsCheckBoxPositionY = settingsSoundsLabelPositionY + 10;
    const int settingsControlCheckBoxWidth = 165;
    const int settingsControlCheckBoxHeight = 40;
    const int settingsControlMouseCheckBoxPositionX = settingsLabelPositionX + 20;
    const int settingsControlKeyboardCheckBoxPositionX = settingsLabelPositionX + settingsLabelWidth - settingsControlCheckBoxWidth - 20;
    const int settingsControlCheckBoxPositionY = settingsControlLabelPositionY + 45;
    //Sliders
    const int settingsSliderWidth = settingsLabelWidth - 30;
    const int settingsSliderHeight = 20;
    const int settingsSliderPositionX = settingsLabelPositionX + 15;
    const int settingsMusicSliderPositionY = settingsMusicLabelPositionY + 60;
    const int settingsSoundsSliderPositionY = settingsSoundsLabelPositionY + 60;
    const int settingsSlidersMinValue = 0;
    const int settingsSlidersMaxValue = 100;

    //Interface
    const int healthGraphicsCenterPositionX = 130;
    const int healthGraphicsCenterPositionY = sceneHeight - 45;
    const int scoreGraphicsCenterPositionX  = sceneWidth  - 130;
    const int scoreGraphicsCenterPositionY  = healthGraphicsCenterPositionY;
    const int levelGraphicsCenterPositionX  = halfSceneWidth;
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
    const QString cancelText = "CANCEL";
    const QString continueText = "CONTINUE";
    const QString gameTitle = "GALACTIC WAR";
    const QString gameoverText = "GAME OVER";
    const QString highscoreText = "HIGH SCORE";
    const QString pauseText = "PAUSE";
    const QString startgameText = "START GAME";
    const QString saveText = "SAVE";
    const QString quitText = "QUIT";
    const QString settingsText = "SETTINGS";
    const QString settingsMusicText = "MUSIC";
    const QString settingsSoundsText = "SOUNDS";
    const QString settingsControlText = "CONTROL";
    const QString settingsMouseText = "MOUSE";
    const QString settingsKeyboardText = "KEYBOARD";

    //Colors
    const QString darkRedHex    = "#DE0101";
    const QString darkYellowHex = "#FCCD10";
}

#endif // DEFINITIONS_HPP
