#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP

#include "controlplane.hpp"
#include "gameobject.hpp"
#include "gameplayview.hpp"
#include "playermodel.hpp"
#include "rewardtypes.hpp"
#include <QObject>

class PlayerController : public QObject
{
    Q_OBJECT
public:
    PlayerController(ControlPlane* controller,
                     GameplayView* view);
    virtual ~PlayerController();

signals:
    void addPlayerToScene(GameObject* player);
    void addHealthPoints(int healthPoints);
    void subtractHealthPoints(int healthPoints);

public slots:
    void create();
    void destroy();
    void changePlayerAtribute(special_type reward);
    void addHealth(int healthPoints);
    void subtractHealth(int healthPoints);

protected:
    ControlPlane* m_controller;
    PlayerModel*  m_model;
};

#endif // PLAYERCONTROLLER_HPP
