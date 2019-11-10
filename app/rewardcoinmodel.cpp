#include "rewardcoinmodel.hpp"
#include "definitions.hpp"
#include <QCoreApplication>

RewardCoinModel::RewardCoinModel(coin_type type)
                                  : m_type(type)
{
    QString fileName;
    switch (m_type)
    {
        case bronze:
            fileName = "coin1.jpg";
            break;
        case silver:
            fileName = "coin2.jpg";
            break;
        case gold:
            fileName = "coin3.jpg";
            break;
    }

    m_image = QImage(QCoreApplication::applicationDirPath() + "/images/" + fileName);
    setPixmap(getAnimationFrame());
}

RewardCoinModel::~RewardCoinModel()
{

}

void RewardCoinModel::collect()
{
    emit collected(m_type);
    destroy();
}
