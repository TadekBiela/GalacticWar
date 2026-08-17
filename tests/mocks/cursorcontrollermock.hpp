#include "../app/cursorcontroller.hpp"
#include <QPoint>
#include <gmock/gmock.h>

class CursorControllerMock : public CursorController
{
public:
    MOCK_METHOD(void, setCursorPosition, (const QPoint& position), (override));
};
