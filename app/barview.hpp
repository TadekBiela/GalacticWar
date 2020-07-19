#ifndef BARVIEW_HPP
#define BARVIEW_HPP

#include "iinterfaceview.hpp"
#include <QProgressBar>
#include <QString>
#include <QWidget>

class BarView : public IInterfaceView
{
public:
    BarView(QWidget* displayWidget,
            QString  graphicsName,
            QString  barColorInHex);
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
