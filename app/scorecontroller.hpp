#ifndef SCORECONTROLLER_HPP
#define SCORECONTROLLER_HPP

#include "scoremodel.hpp"
#include "scoreview.hpp"
#include "rewardtypes.hpp"
#include <QObject>

class ScoreController : public QObject
{
    Q_OBJECT
public:
    ScoreController(ScoreModel* model,
                    ScoreView*  view);
    virtual ~ScoreController();

signals:
    void get();
    void updateScore(int score);
    void addPoints(int points);
    void maxScorePerLevelAchived();

public slots:
    void getScore();
    void update(int score);
    void addScorePoints(coin_type coin);
    void maxPerLevelAchived();
};

#endif // SCORECONTROLLER_HPP
