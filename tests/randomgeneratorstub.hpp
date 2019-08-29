#ifndef RANDOMGENERATORFAKE_HPP
#define RANDOMGENERATORFAKE_HPP

#include "../app/irandomgenerator.hpp"

class RandomGeneratorStub : public IRandomGenerator
{
public:
    virtual ~RandomGeneratorStub() {}
    void setRandomGeneratorFakeResult(int number);
    int  getRandomGeneratorFakeResult();
    int  bounded(int lowest, int highest);

private:
    int m_randomgeneratorfakeResult;
};

#endif // RANDOMGENERATORFAKE_HPP
