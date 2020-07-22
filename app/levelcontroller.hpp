#ifndef LEVELCONTROLLER_HPP
#define LEVELCONTROLLER_HPP

#include "enemyconfiguration.hpp"
#include "labelview.hpp"
#include "levelmodel.hpp"
#include <QObject>
#include <QWidget>

class LevelController : public QObject
{
    Q_OBJECT
public:
    LevelController(QWidget* displayWidget);
    virtual ~LevelController();

signals:
    void changeEnemyConfig(EnemyConfiguration enemyConfig);

public slots:
    void create();
    void distroy();
    void show();
    void hide();
    void nextLevel();

protected:
    QWidget*    m_displayWidget;
    LevelModel* m_model;
    LabelView*    m_view;
};

#endif // LEVELCONTROLLER_HPP
