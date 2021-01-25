
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


#ifndef BARVIEW_HPP
#define BARVIEW_HPP

#include "controlplane.hpp"
#include "iinterfaceview.hpp"
#include <QProgressBar>
#include <QString>
#include <QWidget>

class BarView : public IInterfaceView
{
public:
    BarView(QWidget*      displayWidget,
            ControlPlane* controller,
            QString       graphicsName,
            QString       barColorInHex);
    virtual ~BarView();
    void setPosition(int x, int y) override;
    void set(int value) override;
    void show() override;
    void hide() override;
    void invertAppearance();

private:
    QProgressBar m_valueBar;
};

#endif // BARVIEW_HPP
