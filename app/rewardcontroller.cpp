#include "rewardcontroller.hpp"
#include "rewardcoinmodel.hpp"
#include "rewardspecialmodel.hpp"

const int RewardController::s_minCoinsInTier[def::maxTier] = { 1, 1, 2, 2, 3, 3 };
const int RewardController::s_maxCoinsInTier[def::maxTier] = { 3, 4, 5, 5, 5, 6 };
const int RewardController::s_coinTypeInTier[def::maxTier][10] =
  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 1, 1, 1, 2 },
    { 0, 0, 1, 1, 1, 1, 1, 2, 2, 2 },
    { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
    { 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 } };
const int RewardController::s_specialChanceInTier[def::maxTier] = { 0, 2, 3, 4, 6, 10 };

RewardController::RewardController(GeneralView*      view,
                                   IRandomGenerator* generator)
                                    : m_generator(generator)
{
    connect(this, SIGNAL(addRewardToScene(QGraphicsItem*)),
            view, SLOT(addGameObject(QGraphicsItem*)));
}

RewardController::~RewardController()
{

}

void RewardController::spawnRewards(QPointF position, int tier)
{
    int rewardTierIdx = tier - 1;
    int numOfCoins    = m_generator->bounded(s_minCoinsInTier[rewardTierIdx],
                                             s_maxCoinsInTier[rewardTierIdx]);
    for (int i = 0; i < numOfCoins; i++)
    {
        coin_type type = static_cast<coin_type>(s_coinTypeInTier[rewardTierIdx][m_generator->bounded(0, 9)]);

        RewardCoinModel* coin = new RewardCoinModel(type);

        int xOffset = m_generator->bounded(def::minRewardPosOffset, def::maxRewardPosOffset);
        int yOffset = m_generator->bounded(def::minRewardPosOffset, def::maxRewardPosOffset);
        coin->setPos(position.x() + xOffset - coin->pixmap().size().width()  / 2,
                     position.y() + yOffset - coin->pixmap().size().height() / 2);

        connect(coin, SIGNAL(collected(coin_type)),
                this, SLOT(coinCollected(coin_type)));
        emit addRewardToScene(coin);
    }

    int specialChanse = m_generator->bounded(1, 100);

    if(specialChanse <= s_specialChanceInTier[rewardTierIdx])
    {
        special_type type = static_cast<special_type>(m_generator->bounded(1, def::maxNumOfSpecialRewards));

        RewardSpecialModel* special = new RewardSpecialModel(type);
        special->setPos(position.x() - special->pixmap().size().width()  / 2,
                        position.y() - special->pixmap().size().height() / 2);

        connect(special, SIGNAL(collected(special_type)),
                this,    SLOT(specialCollected(special_type)));
        emit addRewardToScene(special);
    }
}

void RewardController::coinCollected(coin_type coin)
{
    emit rewardCoinCollected(coin);
}

void RewardController::specialCollected(special_type special)
{
    emit rewardSpecialCollected(special);
}
