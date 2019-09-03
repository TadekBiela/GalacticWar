#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

namespace def
{
    const int    defaultBulletSpeed     = 10;
    const int    animationFrameDuration = 5;
    const int    moveVectorLength       = 10;
    const double pi                     = 3.14159265;
    const double radianConversionFactor = pi / 180;
    const int    maxFrameIdx            = 5;
    const int    maxNumOfLevel          = 10;

    //Player default configuration
    const int defaultPlayerDamage         = 1;
    const int defaultPlayerMoveTimeDelay  = 15;
    const int defaultPlayerFireTimeDelay  = 10;

    //Scene size
    const int sceneWight  = 600;
    const int sceneHeight = 800;
    const int halfSceneWight  = sceneWight  / 2;
    const int halfSceneHeight = sceneHeight / 2;

    //Defalut directions
    const int up    = 0;
    const int down  = 180;
    const int right = 90;
    const int left  = 270;
}

#endif // DEFINITIONS_HPP
