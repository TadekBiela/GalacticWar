#pragma once

#include <QPoint>

class CursorController
{
public:
    virtual ~CursorController() = default;

    virtual void setCursorPosition(const QPoint& position);
};
