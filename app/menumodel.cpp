#include "menumodel.hpp"

MenuModel::MenuModel()
{

}

MenuModel::~MenuModel()
{

}

void MenuModel::addRecordToHighScore(PlayerScore newPlayerScore)
{
    m_highScore.insert(newPlayerScore.first, newPlayerScore.second);
    emit updateHighScore(m_highScore.begin(), m_highScore.size());
}

void MenuModel::saveHighScore()
{

}
