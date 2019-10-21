#include "levelview.hpp"

LevelView::LevelView()
{
    m_levelLabel.setNum(1);
}

LevelView::~LevelView()
{

}

void LevelView::update(int value)
{
    m_levelLabel.setNum(value);
}
