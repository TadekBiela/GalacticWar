#ifndef SCORECONTROLLER_HPP
#define SCORECONTROLLER_HPP

#include "scoremodel.hpp"
#include "scoreview.hpp"
#include "rewardtypes.hpp"
#include "irandomgenerator.hpp"
#include <QObject>

class ScoreController : public QObject
{
    Q_OBJECT
public:
    ScoreController(ScoreModel*       model,
                    ScoreView*        view,
                    IRandomGenerator* generator);
    virtual ~ScoreController();

signals:
    void get();
    void updateScore(int score);
    void addPoints(int points);
    void maxScorePerLevelAchieved();

public slots:
    void getScore();
    void update(int score);
    void addScorePoints(coin_type coin);
    void maxPerLevelAchieved();

protected:
    IRandomGenerator* m_generator;
};

#endif // SCORECONTROLLER_HPP
