
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


#include "label.hpp"
#include "definitions.hpp"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

Label::Label(const QString& text, QWidget* parent)
    : QLabel (text, parent)
{
    QString style("border: 0px; color: #FFFFFF; font-size: 45px;");
    QLabel::setStyleSheet(style);
    QLabel::setGeometry(0, 0, def::labelWidth, def::labelHeight);
    QLabel::setAlignment(Qt::AlignCenter);
}

void Label::setPosition(int x, int y)
{
    QLabel::setGeometry(x, y, this->width(), this->height());
}

void Label::setSize(int width, int height)
{
    QLabel::setGeometry(this->x(), this->y(), width, height);
}

void Label::setAlignment(Qt::AlignmentFlag alignment)
{
    QLabel::setAlignment(alignment);
}

void Label::setFontSizeInPx(int fontSize)
{
    QString     currStyle     = this->styleSheet();
    QStringList currStyleList = currStyle.split(QString(";"));
    QString     newFontSize   = "font-size: " + QString::number(fontSize) + "px";

    currStyleList.replaceInStrings(QRegExp("font-size: \\d+px"), newFontSize);

    QString newStyle = currStyleList.join(QString(";"));

    this->setStyleSheet(newStyle);
}

void Label::setText(QString text)
{
    QLabel::setText(text);
}

QString Label::getText()
{
    return QLabel::text();
}

void Label::show()
{
    QLabel::show();
}

void Label::hide()
{
    QLabel::hide();
}
