#ifndef BACKGROUNDCONTROLLER_HPP
#define BACKGROUNDCONTROLLER_HPP

#include "animationeffectmodel.hpp"
#include "backgroundview.hpp"
#include "irandomgenerator.hpp"
#include <QObject>
#include <QTimer>
#include <QWidget>

class BackgroundController : public QObject
{
    Q_OBJECT
public:
    BackgroundController(QWidget* displayWidget);
    virtual ~BackgroundController();

signals:
    void addEffectToScene(AnimationEffectModel* effect);

public slots:
    void activate();
    void deactivate();

private slots:
    void spawnItem();

private:
    IRandomGenerator* m_generator;
    BackgroundView    m_view;
    QTimer            m_itemsSpawnTimer;
};

#endif // BACKGROUNDCONTROLLER_HPP
