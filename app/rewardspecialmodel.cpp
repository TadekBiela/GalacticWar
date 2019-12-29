#include "rewardspecialmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "soundeffectmodel.hpp"
#include <QCoreApplication>

RewardSpecialModel::RewardSpecialModel(special_type type)
                                        : m_type(type)
{
    QString fileName;
    switch (m_type)
    {
        case health:
            fileName = "health.jpg";
            break;
        case weaponRed:
            fileName = "red.jpg";
            break;
        case weaponYellow:
            fileName = "yellow.jpg";
            break;
        case weaponBlue:
            fileName = "blue.jpg";
            break;
    }

    m_image = QImage(QCoreApplication::applicationDirPath() + "/images/" + fileName);
    setPixmap(getAnimationFrame(m_image, m_animationFrameIdx));
}

RewardSpecialModel::~RewardSpecialModel()
{

}

void RewardSpecialModel::collect()
{
    emit collected(m_type);
    SoundEffectModel* collect = new SoundEffectModel("collect_special");
    destroy();
}
