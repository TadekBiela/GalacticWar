#include "rewardspecialmodel.hpp"
#include "definitions.hpp"
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
    setPixmap(getAnimationFrame());
}

RewardSpecialModel::~RewardSpecialModel()
{

}

void RewardSpecialModel::collect()
{
    emit collected(m_type);
    destroy();
}
