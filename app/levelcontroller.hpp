#ifndef LEVELCONTROLLER_HPP
#define LEVELCONTROLLER_HPP

#include "controlplane.hpp"
#include "enemyconfiguration.hpp"
#include "labelview.hpp"
#include "levelmodel.hpp"
#include <QObject>
#include <QWidget>

class LevelController : public QObject
{
    Q_OBJECT
public:
    LevelController(QWidget*      displayWidget,
                    ControlPlane* controller);
    virtual ~LevelController();

signals:
    void changeEnemyConfig(EnemyConfiguration enemyConfig);

public slots:
    void create();
    void destroy();
    void show();
    void hide();
    void nextLevel();

protected:
    QWidget*      m_displayWidget;
    ControlPlane* m_controller;
    LevelModel*   m_model;
    LabelView*    m_view;
};

#endif // LEVELCONTROLLER_HPP
