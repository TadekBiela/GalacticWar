#ifndef HEALTHCONTROLLER_HPP
#define HEALTHCONTROLLER_HPP

#include "barview.hpp"
#include "controlplane.hpp"
#include "healthmodel.hpp"
#include <QObject>
#include <QWidget>

class HealthController : public QObject
{
    Q_OBJECT
public:
    HealthController(QWidget*      displayWidget,
                     ControlPlane* controller);
    virtual ~HealthController();

signals:
    void noHealth();

public slots:
    void create();
    void destroy();
    void show();
    void hide();
    void addHealthPoints(int healthPoints);
    void subtractHealthPoints(int healthPoints);

protected:
    QWidget*      m_displayWidget;
    ControlPlane* m_controller;
    HealthModel*  m_model;
    BarView*      m_view;

};

#endif // HEALTHCONTROLLER_HPP
