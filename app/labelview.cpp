#include "labelview.hpp"
#include "definitions.hpp"

LabelView::LabelView(QWidget* displayWidget,
                     QString  graphicsName)
                      : IInterfaceView(displayWidget,
                                       graphicsName),
                        m_valueLabel(displayWidget)
{
    m_valueLabel.setGeometry(def::valueLabelPositionOffset,
                             def::valueLabelPositionOffset,
                             m_graphics.width()  - def::valueLabelSizeOffset,
                             m_graphics.height() - def::valueLabelSizeOffset);
    m_valueLabel.setNum(0);
    m_valueLabel.setAlignment(Qt::AlignCenter);
    m_valueLabel.setStyleSheet("border-color:  transparent;"
                               "background:    transparent;"
                               "color:         white;"
                               "font-size:     25px;"
                               "margin-top:    2px;"
                               "margin-bottom: 4px;"
                               "margin-left:   2px;"
                               "margin-right:  2px;");
}

LabelView::~LabelView()
{

}

void LabelView::setPosition(int x, int y)
{
    IInterfaceView::setPosition(x, y);
    m_valueLabel.setGeometry(x + def::valueLabelPositionOffset,
                             y + def::valueLabelPositionOffset,
                             m_valueLabel.width(),
                             m_valueLabel.height());
}

void LabelView::set(int value)
{
    m_valueLabel.setNum(value);
}

void LabelView::show()
{
    m_graphics.hide();
    m_valueLabel.hide();
}

void LabelView::hide()
{
    m_graphics.hide();
    m_valueLabel.hide();
}
