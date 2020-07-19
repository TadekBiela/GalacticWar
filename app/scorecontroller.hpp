#ifndef SCORECONTROLLER_HPP
#define SCORECONTROLLER_HPP

#include "barview.hpp"
#include "irandomgenerator.hpp"
#include "scoremodel.hpp"
#include "rewardtypes.hpp"
#include <QObject>

class ScoreController : public QObject
{
    Q_OBJECT
public:
    ScoreController(QWidget* displayWidget);
    virtual ~ScoreController();

signals:
    void maxScorePerLevelAchieved();
    void totalScore(int total);

public slots:
    void create();
    void destroy();
    void show();
    void hide();
    void addScorePointsBasedOnCoinType(coin_type coin);
    void emitTotalScoreAndDestroy();

protected:
    QWidget*          m_displayWidget;
    IRandomGenerator* m_generator;
    ScoreModel*       m_model;
    BarView*          m_view;
};

#endif // SCORECONTROLLER_HPP
