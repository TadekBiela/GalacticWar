#include "pushbutton.hpp"
#include "soundeffectmodel.hpp"

PushButton::PushButton(const QString& text, QWidget* parent)
                        : QPushButton (text, parent)
{

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
