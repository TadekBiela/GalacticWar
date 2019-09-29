#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP

#include "generalview.hpp"
#include "healthview.hpp"
#include "playermodel.hpp"
#include "rewardtypes.hpp"
#include <QObject>
#include <QGraphicsItem>

class PlayerController : public QObject
{
    Q_OBJECT
public:
    PlayerController(GeneralView* view,
                     HealthView*  healthView);
    ~PlayerController();

signals:
    void addPlayerToScene(QGraphicsItem* player);
    void changeAtribute(special_type reward);
    void playerDefeated();

public slots:
    void createNew();
    void activate();
    void deactivate();
    void defeated();
    void changePlayerAtribute(special_type reward);

protected:
    GeneralView* m_view;
    HealthView*  m_healthView;
    PlayerModel* m_player;
};

#endif // PLAYERCONTROLLER_HPP
