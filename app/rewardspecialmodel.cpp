#include "rewardspecialmodel.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "soundeffectmodel.hpp"
#include "imagestorage.hpp"

RewardSpecialModel::RewardSpecialModel(special_type type)
                                        : m_type(type)
{
    QString animationName;
    switch (m_type)
    {
        case health:
            animationName = "health";
            break;
        case weaponRed:
            animationName = "weapon_red";
            break;
        case weaponYellow:
            animationName = "weapon_yellow";
            break;
        case weaponBlue:
            animationName = "weapon_blue";
            break;
    }

    m_image = g_imageStorage->getImage(animationName);
    setPixmap(getAnimationFrame(m_image, m_animationFrameIdx));
}

RewardSpecialModel::~RewardSpecialModel()
{

}

void RewardSpecialModel::collect()
{
    emit collected(m_type);
    SoundEffectModel* collect = new SoundEffectModel("collect_special");
    QPointF position = pos();
    position.setX(position.x() + def::animationSmallFrameWight  / 2);
    position.setY(position.y() + def::animationSmallFrameHeight / 2);
    AnimationEffectModel* collectAnim = new AnimationEffectModel(this->scene(),
                                                                 "collect_reward",
                                                                 position);
    destroy();
}
