#ifndef RANDOMGENERATORFAKE_HPP
#define RANDOMGENERATORFAKE_HPP

#include "../app/irandomgenerator.hpp"

class RandomGeneratorStub : public IRandomGenerator
{
public:
    virtual ~RandomGeneratorStub() {}
    void setRandomGeneratorFakeResult(int number)
    {
        m_randomgeneratorfakeResult = number;
    }
    int bounded(int lowest, int highest)
    {
        return m_randomgeneratorfakeResult;
    }

private:
    int m_randomgeneratorfakeResult;
};

#endif // RANDOMGENERATORFAKE_HPP
