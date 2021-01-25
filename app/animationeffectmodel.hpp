
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


#ifndef ANIMATIONEFFECTMODEL_HPP
#define ANIMATIONEFFECTMODEL_HPP

#include "animationplaneview.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QPointF>
#include <QImage>
#include <QTimer>

class AnimationEffectModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimationEffectModel(QString         animationName,
                         QPointF         position,
                         int             animationFrameWidth,
                         int             animationFrameHeight,
                         int             numOfFrames = def::maxAnimationFrames,
                         QGraphicsScene* targetScene = g_animationPlaneView->scene());
    virtual ~AnimationEffectModel();
    virtual void play();

public slots:
    virtual void start();
    virtual void stop();

protected slots:
    void animation();
    void destroy();

protected:
    QImage* m_image;
    int     m_animationFrameIdx;
    QTimer  m_animationTimer;
    int     m_animationFrameWidth;
    int     m_animationFrameHeight;
    int     m_numOfFrames;
};

#endif // ANIMATIONEFFECTMODEL_HPP
