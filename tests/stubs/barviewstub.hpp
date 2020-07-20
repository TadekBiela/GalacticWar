#ifndef BARVIEWSTUB_HPP
#define BARVIEWSTUB_HPP

#include <gmock/gmock.h>
#include "../app/barview.hpp"
#include "../app/definitions.hpp"

using namespace testing;

class BarViewStub : public BarView
{
public:
    BarViewStub(QWidget* displayWidget)
        : BarView(displayWidget,
                  QString("healthView"),
                  QString(def::darkRedHex)){}
    virtual ~BarViewStub() {}

    MOCK_METHOD(void, set, (int), ());
};

#endif // BARVIEWSTUB_HPP
