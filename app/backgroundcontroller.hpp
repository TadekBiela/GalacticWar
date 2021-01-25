
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


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

public slots:
    void activate();
    void deactivate();
    void increaseBackgroundSpeed();
    void decreaseBackgroundSpeed();
    void resetToDefault();

private slots:
    void spawnItem();

private:
    IRandomGenerator* m_generator;
    BackgroundView    m_view;
    QTimer            m_itemsSpawnTimer;
};

#endif // BACKGROUNDCONTROLLER_HPP
