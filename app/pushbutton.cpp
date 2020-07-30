#include "pushbutton.hpp"
#include "soundeffectmodel.hpp"
#include "definitions.hpp"

PushButton::PushButton(const QString& text, QWidget* parent)
    : QPushButton (text, parent)
{
    QString style("border-style: solid; border-width: 2px; border-radius: 5px; border-color: #FFFFFF; color: #FFFFFF; background-color: transparent; font-size: 20px;");
    setStyleSheet(style);
    setGeometry(0, 0, def::buttonWight, def::buttonHeight);
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
