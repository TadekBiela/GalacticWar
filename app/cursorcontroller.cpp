#include "cursorcontroller.hpp"
#include <QCursor>

void CursorController::setCursorPosition(const QPoint& position)
{
    QCursor::setPos(position);
}
