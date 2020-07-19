#include "healthmodel.hpp"
#include "definitions.hpp"

HealthModel::HealthModel()
    : m_currentHealth(def::maxPlayerHealth)
{

}

HealthModel::~HealthModel()
{

}

int HealthModel::getCurrentHealthInPercent() const
{
    return m_currentHealth * 100 / def::maxPlayerHealth;
}

void HealthModel::add(int healthPoints)
{
    m_currentHealth += healthPoints;
    if(def::maxPlayerHealth < m_currentHealth)
    {
        m_currentHealth = def::maxPlayerHealth;
    }
}

Health_Status HealthModel::subtract(int healthPoints)
{
    m_currentHealth -= healthPoints;
    if(0 >= m_currentHealth)
    {
        m_currentHealth = 0;
        return Health_Status_No_More;
    }
    return Health_Status_Still_Is;
}
