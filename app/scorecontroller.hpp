#ifndef SCORECONTROLLER_HPP
#define SCORECONTROLLER_HPP

#include "generalview.hpp"
#include "scoremodel.hpp"
#include "rewardtypes.hpp"
#include "irandomgenerator.hpp"
#include <QObject>

class ScoreController : public QObject
{
    Q_OBJECT
public:
    ScoreController(ScoreModel*       model,
                    GeneralView*      view,
                    IRandomGenerator* generator);
    virtual ~ScoreController();

signals:
    void reset();
    void get();
    void updateScore(int score);
    void addPoints(int points);
    void maxScorePerLevelAchieved();

public slots:
    void resetScore();
    void getScore();
    void update(int score);
    void addScorePoints(coin_type coin);
    void maxPerLevelAchieved();

protected:
    IRandomGenerator* m_generator;
};

#endif // SCORECONTROLLER_HPP
