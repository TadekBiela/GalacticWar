#include "iinterfaceview.hpp"
#include "imagestorage.hpp"

IInterfaceView::IInterfaceView(QWidget*      displayWidget,
                               ControlPlane* controller,
                               QString       graphicsName)
    : m_graphics(displayWidget)
{
    QImage* image = g_imageStorage->getImage(graphicsName);
    QPixmap map;
    map.convertFromImage(image->copy(0,
                                     0,
                                     image->width(),
                                     image->height()));
    m_graphics.setPixmap(map);
    m_graphics.setGeometry(0,
                           0,
                           image->width(),
                           image->height());
    m_graphics.stackUnder(controller);
}

IInterfaceView::~IInterfaceView()
{

}

void IInterfaceView::setPosition(int x, int y)
{
    m_graphics.setGeometry(x - (m_graphics.width()  / 2),
                           y - (m_graphics.height() / 2),
                           m_graphics.width(),
                           m_graphics.height());
}
