#include "barview.hpp"
#include "definitions.hpp"

BarView::BarView(QWidget*      displayWidget,
                 ControlPlane* controller,
                 QString       graphicsName,
                 QString       barColorInHex)
    : IInterfaceView(displayWidget,
                     controller,
                     graphicsName),
      m_valueBar(displayWidget)
{
    m_valueBar.setGeometry(def::valueBarPositionOffsetX,
                           def::valueBarPositionOffsetY,
                           m_graphics.width() - def::valueBarSizeOffsetX,
                           m_graphics.height()- def::valueBarSizeOffsetY);
    m_valueBar.setValue(0);
    m_valueBar.setTextVisible(false);
    m_valueBar.setStyleSheet("QProgressBar {"
                             "     border-radius:    2px;"
                             "     background-color: transparent; }"
                             "QProgressBar::chunk { "
                             "     border-radius:    2px;"
                             "     background-color: " +
                             QString(barColorInHex) +
                             "; }"
                             "QProgressBar::sub-line {"
                             "     background-color: transparent; }");
    m_valueBar.stackUnder(&m_graphics);
}

BarView::~BarView()
{

}

void BarView::setPosition(int x, int y)
{
    IInterfaceView::setPosition(x, y);
    m_valueBar.setGeometry(m_graphics.x() + def::valueBarPositionOffsetX,
                           m_graphics.y() + def::valueBarPositionOffsetY,
                           m_valueBar.width(),
                           m_valueBar.height());
}

void BarView::set(int value)
{
    m_valueBar.setValue(value);
}

void BarView::show()
{
    m_graphics.show();
    m_valueBar.show();
}

void BarView::hide()
{
    m_graphics.hide();
    m_valueBar.hide();
}

void BarView::invertAppearance()
{
    bool currnetApperance = m_valueBar.invertedAppearance();
    m_valueBar.setInvertedAppearance(!currnetApperance);
}
