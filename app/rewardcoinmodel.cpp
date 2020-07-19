#include "rewardcoinmodel.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include "soundeffectmodel.hpp"

RewardCoinModel::RewardCoinModel(coin_type type)
                                  : m_type(type)
{
    QString animationName;
    switch (m_type)
    {
        case bronze:
            animationName = "coin1";
            break;
        case silver:
            animationName = "coin2";
            break;
        case gold:
            animationName = "coin3";
            break;
    }

    m_image = g_imageStorage->getImage(animationName);
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                m_image->height(),
                                m_image->height()));
}

RewardCoinModel::~RewardCoinModel()
{

}

void RewardCoinModel::collect()
{
    emit collected(m_type);
    SoundEffectModel* collect = new SoundEffectModel("collect_coin");
    QPointF position = pos();
    position.setX(position.x() + def::animationSmallFrameWight  / 2);
    position.setY(position.y() + def::animationSmallFrameHeight / 2);
//    AnimationEffectModel* collectAnim = new AnimationEffectModel("collect_reward",
//                                                                 position,
//                                                                 def::animationSmallFrameWight,
//                                                                 def::animationSmallFrameHeight);
    collect->play();
//    collectAnim->play();
    destroy();
}
