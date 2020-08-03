#ifndef ANIMATIONPLANEVIEW_HPP
#define ANIMATIONPLANEVIEW_HPP

#include "graphicsview.hpp"
#include <QWidget>

class AnimationEffectModel;

class AnimationPlaneView : public GraphicsView
{
    Q_OBJECT
public:
    AnimationPlaneView(QWidget* displayWidget);
    virtual ~AnimationPlaneView();
    virtual void startAllItems() override;
    virtual void stopAllItems()  override;

public slots:
    void activate()   override;
    void deactivate() override;
    void addEffectToScene(AnimationEffectModel* object);
};

extern AnimationPlaneView* g_animationPlaneView;

#endif // ANIMATIONPLANEVIEW_HPP
