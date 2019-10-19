#include "rewardcontroller.hpp"

RewardController::RewardController(GeneralView*      view,
                                   IRandomGenerator* generator)
                                    : m_generator(generator)
{

}

RewardController::~RewardController()
{

}

void RewardController::spawnRewards(QPointF position, int tier)
{

}

void RewardController::coinCollected(coin_type coin)
{
    emit rewardCoinCollected(coin);
}

void RewardController::specialCollected(special_type special)
{
    emit rewardSpecialCollected(special);
}
