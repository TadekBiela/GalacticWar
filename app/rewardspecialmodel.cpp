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
            m_soundName   = "collect_health";
            break;
        case weaponRed:
            animationName = "weapon_red";
            m_soundName   = "collect_weapon";
            break;
        case weaponYellow:
            animationName = "weapon_yellow";
            m_soundName   = "collect_weapon";
            break;
        case weaponBlue:
            animationName = "weapon_blue";
            m_soundName   = "collect_weapon";
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
    SoundEffectModel* collect = new SoundEffectModel(m_soundName);
    QPointF position = pos();
    position.setX(position.x() + def::animationSmallFrameWight  / 2);
    position.setY(position.y() + def::animationSmallFrameHeight / 2);
    AnimationEffectModel* collectAnim = new AnimationEffectModel(this->scene(),
                                                                 "collect_reward",
                                                                 position);
    destroy();
}
