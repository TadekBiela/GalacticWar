#ifndef PUSHBUTTON_HPP
#define PUSHBUTTON_HPP

#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    PushButton(const QString& text, QWidget* parent = nullptr);
    virtual ~PushButton() {}

protected:
    virtual void enterEvent(QEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
};

#endif // PUSHBUTTON_HPP
