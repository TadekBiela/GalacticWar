#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include "irandomgenerator.hpp"
#include <QRandomGenerator>

class RandomGenerator : public IRandomGenerator
{
public:
    RandomGenerator();
    virtual ~RandomGenerator();
    int bounded(int lowest, int highest);

protected:
    QRandomGenerator* generator;
};

#endif // RANDOMGENERATOR_HPP
