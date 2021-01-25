
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


#ifndef REWARDMODEL_HPP
#define REWARDMODEL_HPP

#include "gameobject.hpp"
#include <QTimer>
#include <QImage>
#include <QPixmap>

class RewardModel : public GameObject
{
    Q_OBJECT
public:
    RewardModel();
    virtual ~RewardModel();
    virtual void collect() = 0;

public slots:
    virtual void start();
    virtual void stop();
    virtual void animation();
    void destroy();

protected:
    QImage* m_image;
    int     m_animationFrameIdx;
    QTimer  m_animationTimer;
    QTimer  m_destroyTimer;
};

#endif // REWARDMODEL_HPP
