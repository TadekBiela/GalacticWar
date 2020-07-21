#ifndef RANDOMGENERATORSTUB_HPP
#define RANDOMGENERATORSTUB_HPP

#include <gmock/gmock.h>
#include "../app/irandomgenerator.hpp"

using namespace testing;

class RandomGeneratorStub : public IRandomGenerator
{
public:
    RandomGeneratorStub() {}
    virtual ~RandomGeneratorStub() {}

    MOCK_METHOD((int), bounded, (int, int), (override));
};

#endif // RANDOMGENERATORSTUB_HPP
