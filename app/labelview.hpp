#ifndef LABELVIEW_HPP
#define LABELVIEW_HPP

#include "controlplane.hpp"
#include "iinterfaceview.hpp"
#include <QLabel>
#include <QString>
#include <QWidget>

class LabelView : public IInterfaceView
{
public:
    LabelView(QWidget*      displayWidget,
              ControlPlane* controller,
              QString       graphicsName);
    virtual ~LabelView();
    void setPosition(int x, int y) override;
    void set(int value) override;
    void show() override;
    void hide() override;

protected:
    QLabel m_valueLabel;
};

#endif // LABELVIEW_HPP
