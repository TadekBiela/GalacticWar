#ifndef SCOREMODEL_HPP
#define SCOREMODEL_HPP

#include "definitions.hpp"
#include <QObject>

class ScoreModel : public QObject
{
    Q_OBJECT
public:
    ScoreModel();
    virtual ~ScoreModel();

signals:
    void update(int score);
    void updateView(int value);
    void maxPerLevelAchieved();

public slots:
    void reset();
    void get();
    void addPoints(int points);

protected:
    int m_currentTresholdIdx;
    int m_totalScore;

    static const int s_scoreTresholds[def::maxNumOfLevel];
};

#endif // SCOREMODEL_HPP
