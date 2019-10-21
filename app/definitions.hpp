#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

namespace def
{
    const int    defaultBulletSpeed     = 10;
    const int    animationFrameDuration = 5;
    const int    moveVectorLength       = 10;
    const double pi                     = 3.14159265;
    const double radianConversionFactor = pi / 180;
    const int    maxAnimationFrames     = 5;
    const int    maxAnimationFrameIdx   = 4;
    const int    animationFrameWight    = 50;
    const int    animationFrameHeight   = 50;
    const int    maxNumOfLevel          = 10;
    const int    maxWeaponLevel         = 5;
    const int    minEnemySpawnTimeDelay = 100;
    const int    maxEnemySpawnTimeDelay = 500;
    const int    percentDistTabSize     = 100;

    //Player default configuration
    const int maxPlayerHealth             = 1000;
    const int defaultPlayerMoveTimeDelay  = 15;

    //Reward default configuration
    const int maxNumOfSpecialRewards         = 5;
    const int maxTier                        = 6;
    const int minRewardPosOffset             = -10;
    const int maxRewardPosOffset             = 10;
    const int defaultRewardDestroyTimeDelay  = 1000;
    const int minPointsForBronzeCoin         = 10;
    const int maxPointsForBronzeCoin         = 30;
    const int minPointsForSilverCoin         = 50;
    const int maxPointsForSilverCoin         = 100;
    const int minPointsForGoldCoin           = 150;
    const int maxPointsForGoldCoin           = 300;

    //Scene size
    const int sceneWight  = 600;
    const int sceneHeight = 800;
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
