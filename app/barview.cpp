
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


#include "barview.hpp"
#include "definitions.hpp"

BarView::BarView(QWidget*      displayWidget,
                 ControlPlane* controller,
                 QString       graphicsName,
                 QString       barColorInHex)
    : IInterfaceView(displayWidget,
                     controller,
                     graphicsName),
      m_valueBar(displayWidget)
{
    m_valueBar.setGeometry(def::valueBarPositionOffsetX,
                           def::valueBarPositionOffsetY,
                           m_graphics.width() - def::valueBarSizeOffsetX,
                           m_graphics.height()- def::valueBarSizeOffsetY);
    m_valueBar.setValue(0);
    m_valueBar.setTextVisible(false);
    m_valueBar.setStyleSheet("QProgressBar {"
                             "     border-radius:    2px;"
                             "     background-color: transparent; }"
                             "QProgressBar::chunk { "
                             "     border-radius:    2px;"
                             "     background-color: " +
                             QString(barColorInHex) +
                             "; }"
                             "QProgressBar::sub-line {"
                             "     background-color: transparent; }");
    m_valueBar.stackUnder(&m_graphics);
}

BarView::~BarView()
{

}

void BarView::setPosition(int x, int y)
{
    IInterfaceView::setPosition(x, y);
    m_valueBar.setGeometry(m_graphics.x() + def::valueBarPositionOffsetX,
                           m_graphics.y() + def::valueBarPositionOffsetY,
                           m_valueBar.width(),
                           m_valueBar.height());
}

void BarView::set(int value)
{
    m_valueBar.setValue(value);
}

void BarView::show()
{
    m_graphics.show();
    m_valueBar.show();
}

void BarView::hide()
{
    m_graphics.hide();
    m_valueBar.hide();
}

void BarView::invertAppearance()
{
    bool currnetApperance = m_valueBar.invertedAppearance();
    m_valueBar.setInvertedAppearance(!currnetApperance);
}
