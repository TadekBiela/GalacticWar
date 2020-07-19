#ifndef IINTERFACEVIEW_HPP
#define IINTERFACEVIEW_HPP

#include <QLabel>
#include <QString>
#include <QWidget>

class IInterfaceView
{
public:
    IInterfaceView(QWidget* displayWidget,
                   QString  graphicsName);
    ~IInterfaceView();
    virtual void setPosition(int x, int y);
    virtual void set(int value) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;

protected:
    QLabel m_graphics;
};

#endif // IINTERFACEVIEW_HPP
