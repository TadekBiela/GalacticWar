#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

namespace def
{
    const int    defaultBulletSpeed        = 20;
    const int    animationFrameDuration    = 100;
    const int    moveVectorLength          = 10;
    const double pi                        = 3.14159265;
    const double radianConversionFactor    = pi / 180;
    const int    maxAnimationFrames        = 10;
    const int    maxAnimationFrameIdx      = 9;
    const int    animationFrameWight       = 64;
    const int    animationFrameHeight      = 64;
    const int    animationSmallFrameWight  = 32;
    const int    animationSmallFrameHeight = 32;
    const int    animationBigFrameWight    = 200;
    const int    animationBigFrameHeight   = 30;
    const int    maxNumOfLevel             = 10;
    const int    maxWeaponTypes            = 3;
    const int    maxWeaponLevel            = 5;
    const int    minEnemySpawnTimeDelay    = 1000;
    const int    maxEnemySpawnTimeDelay    = 5000;
    const int    percentDistTabSize        = 100;
    const int    collisionDamageFactor     = 300;

    //Player default configuration
    const int maxPlayerHealth             = 2000;
    const int defaultPlayerMoveTimeDelay  = 20;

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
    const int windowWight     = 602;
    const int windowHeight    = 802;

    //Scene size
    const int sceneWight      = 600;
    const int sceneHeight     = 800;
    const int halfSceneWight  = sceneWight  / 2;
    const int halfSceneHeight = sceneHeight / 2;

    //Buttons
    const int buttonWight  = 50;
    const int buttonHeight = 150;

    //Defalut directions
    const int up    = 0;
    const int down  = 180;
    const int right = 90;
    const int left  = 270;
}

#endif // DEFINITIONS_HPP
