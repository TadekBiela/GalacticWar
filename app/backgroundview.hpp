#ifndef BACKGROUNDVIEW_HPP
#define BACKGROUNDVIEW_HPP

#include "animationplaneview.hpp"
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

class BackgroundView : public AnimationPlaneView
{
    Q_OBJECT
public:
    BackgroundView(QWidget* displayWidget);
    virtual ~BackgroundView();
    void setGraphicsEffects(qreal opacity, qreal blurRadius) override;
    void activate()   override;
    void deactivate() override;
    void setBackgroundTimeDelay(int delay);

private slots:
    void backgroundAnimation();

private:
    QTimer  m_backgroundAnimTimer;
    QPixmap m_backgroundGraphics;
    int     m_backgroundGraphicsPosOffset;
    QLabel  m_backgroundLabelWindow;
};

#endif // BACKGROUNDVIEW_HPP
