#include "pushbutton.hpp"
#include "soundeffectmodel.hpp"

PushButton::PushButton(const QString& text, QWidget* parent)
                        : QPushButton (text, parent)
{
    QString style("border-style: solid; border-width: 2px; border-radius: 5px; border-color: #FFFFFF; color: #FFFFFF; background-color: transparent; font-size: 20px;");
    setStyleSheet(style);
}

void PushButton::enterEvent(QEvent* event)
{
    SoundEffectModel* click = new SoundEffectModel("button_select");
    QPushButton::enterEvent(event);
}

void PushButton::mouseReleaseEvent(QMouseEvent* event)
{
    SoundEffectModel* click = new SoundEffectModel("button_click");
    QPushButton::mouseReleaseEvent(event);
}
