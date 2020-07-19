#ifndef GAMEPLAYVIEW_HPP
#define GAMEPLAYVIEW_HPP

#include "gameobject.hpp"
#include "graphicsview.hpp"

class GameplayView : public GraphicsView
{
    Q_OBJECT
public:
    GameplayView(QWidget* displayWidget);
    virtual ~GameplayView();
    void startAllItems() override;
    void stopAllItems() override;

public slots:
    void activate() override;
    void deactivate() override;
    void addGameObjectToScene(GameObject* object);
    void removeAllGameObjects();
};

#endif // GAMEPLAYVIEW_HPP
