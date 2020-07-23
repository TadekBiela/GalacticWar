#ifndef BACKGROUNDVIEW_HPP
#define BACKGROUNDVIEW_HPP

#include "animationplaneview.hpp"
#include <QPixmap>
#include <QTimer>
#include <QWidget>

class BackgroundView : public AnimationPlaneView
{
    Q_OBJECT
public:
    BackgroundView(QWidget* displayWidget);
    virtual ~BackgroundView();
    void activate() override;
    void deactivate() override;

private slots:
    void backgroundAnimation();

private:
    int                 m_backgroundAnimTimeDelay;
    QTimer              m_backgroundAnimTimer;
    QGraphicsPixmapItem m_backgroundGraphics;
    int                 m_backgroundGraphicsPosOffset;
};

#endif // BACKGROUNDVIEW_HPP
