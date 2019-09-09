#ifndef SCOREMODEL_HPP
#define SCOREMODEL_HPP

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
    int m_currentScorePerLevel;
    int m_totalScore;
};

#endif // SCOREMODEL_HPP
