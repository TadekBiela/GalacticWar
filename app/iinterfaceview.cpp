#include "iinterfaceview.hpp"
#include "imagestorage.hpp"

IInterfaceView::IInterfaceView(QWidget* displayWidget,
                               QString graphicsName)
                                : m_graphics(displayWidget)
{
    QImage* image = g_imageStorage->getImage(graphicsName);
    QPixmap map;
    map.convertFromImage(image->copy(0,
                                     0,
                                     image->width(),
                                     image->height()));
    m_graphics.setPixmap(map);
    m_graphics.setGeometry(0, 0, image->width(), image->height());
}

IInterfaceView::~IInterfaceView()
{

}

void IInterfaceView::setPosition(int x, int y)
{
    m_graphics.setGeometry(x,
                           y,
                           m_graphics.width(),
                           m_graphics.height());
}
