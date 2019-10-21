#include "scoreview.hpp"

ScoreView::ScoreView()
{
    m_scoreBar.setValue(0);
}

ScoreView::~ScoreView()
{

}

void ScoreView::update(int value)
{
    m_scoreBar.setValue(value < 100 ? value : 100);
}
