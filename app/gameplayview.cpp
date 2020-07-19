#include "gameplayview.hpp"

GameplayView::GameplayView(QWidget* displayWidget)
                            : GraphicsView(displayWidget)
{

}

GameplayView::~GameplayView()
{

}

void GameplayView::startAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        GameObject* object = dynamic_cast<GameObject*>(*it);
        object->start();
    }
}

void GameplayView::stopAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        GameObject* object = dynamic_cast<GameObject*>(*it);
        object->stop();
    }
}

void GameplayView::activate()
{
    startAllItems();
    setGraphicsEffects(0, 0);
}

void GameplayView::deactivate()
{
    stopAllItems();
    setGraphicsEffects(0.5, 5);
}

void GameplayView::addGameObjectToScene(GameObject* object)
{
    m_scene.addItem(dynamic_cast<QGraphicsItem*>(object));
}

void GameplayView::removeAllGameObjects()
{
    m_scene.clear();
}
