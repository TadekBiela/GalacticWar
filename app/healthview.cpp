#include "healthview.hpp"

HealthView::HealthView()
{
    m_healthBar.setValue(0);
}

HealthView::~HealthView()
{

}

void HealthView::updateHealthView(int value)
{
    m_healthBar.setValue(value < 100 ? value : 100);
}
