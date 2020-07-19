#include "animationplaneview.hpp"

AnimationPlaneView::AnimationPlaneView(QWidget* displayWidget)
                                        : GraphicsView(displayWidget)
{

}

AnimationPlaneView::~AnimationPlaneView()
{

}

void AnimationPlaneView::startAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        AnimationEffectModel* effect = dynamic_cast<AnimationEffectModel*>(*it);
        effect->start();
    }
}

void AnimationPlaneView::stopAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        AnimationEffectModel* effect = dynamic_cast<AnimationEffectModel*>(*it);
        effect->stop();
    }
}

void AnimationPlaneView::activate()
{
    startAllItems();
    setGraphicsEffects(0, 0);
}

void AnimationPlaneView::deactivate()
{
    stopAllItems();
    setGraphicsEffects(0.4, 4);
}

void AnimationPlaneView::addEffectToScene(AnimationEffectModel* object)
{
    m_scene.addItem(dynamic_cast<QGraphicsItem*>(object));
}
