#ifndef SCOREMODEL_HPP
#define SCOREMODEL_HPP

#include "definitions.hpp"
#include <QObject>

class ScoreModel : public QObject
{
    Q_OBJECT
public:
    ScoreModel();

signals:
    void updateScoreView(int newValue);
    void maxScorePerLevelAchieved();

public slots:
    void addScorePoints(int value);

protected:
    int m_currentTresholdIdx;
    int m_totalScore;

    static const int s_scoreTresholds[def::maxNumOfLevel];
};

#endif // SCOREMODEL_HPP
