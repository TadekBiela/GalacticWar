
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


#include "iinterfaceview.hpp"
#include "imagestorage.hpp"

IInterfaceView::IInterfaceView(QWidget*      displayWidget,
                               ControlPlane* controller,
                               QString       graphicsName)
    : m_graphics(displayWidget)
{
    QImage* image = g_imageStorage->getImage(graphicsName);
    QPixmap map;
    map.convertFromImage(image->copy(0,
                                     0,
                                     image->width(),
                                     image->height()));
    m_graphics.setPixmap(map);
    m_graphics.setGeometry(0,
                           0,
                           image->width(),
                           image->height());
    m_graphics.stackUnder(controller);
}

IInterfaceView::~IInterfaceView()
{

}

void IInterfaceView::setPosition(int x, int y)
{
    m_graphics.setGeometry(x - (m_graphics.width()  / 2),
                           y - (m_graphics.height() / 2),
                           m_graphics.width(),
                           m_graphics.height());
}
