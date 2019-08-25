#include "randomgeneratorstub.hpp"

void RandomGeneratorStub::setRandomGeneratorFakeResult(int number)
{
    m_randomgeneratorfakeResult = number;
}

int RandomGeneratorStub::getRandomGeneratorFakeResult()
{
    return m_randomgeneratorfakeResult;
}

int RandomGeneratorStub::bounded(int lowest, int highest)
{
    return getRandomGeneratorFakeResult();
}
