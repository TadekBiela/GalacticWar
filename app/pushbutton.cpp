
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


#include "pushbutton.hpp"
#include "soundeffectmodel.hpp"
#include "definitions.hpp"

PushButton::PushButton(const QString& text, QWidget* parent)
    : QPushButton (text, parent)
{
    QString style("border-style: solid; border-width: 2px; border-radius: 5px; border-color: #FFFFFF; color: #FFFFFF; background-color: transparent; font-size: 20px;");
    setStyleSheet(style);
    setGeometry(0, 0, def::buttonWidth, def::buttonHeight);
}

void PushButton::setPosition(int x, int y)
{
    setGeometry(x, y, this->width(), this->height());
}

void PushButton::enterEvent(QEvent* event)
{
    SoundEffectModel* click = new SoundEffectModel("button_select");
    click->play();
    QPushButton::enterEvent(event);
}

void PushButton::mouseReleaseEvent(QMouseEvent* event)
{
    SoundEffectModel* click = new SoundEffectModel("button_click");
    click->play();
    QPushButton::mouseReleaseEvent(event);
}
