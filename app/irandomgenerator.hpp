#ifndef IRANDOMGENERATOR_HPP
#define IRANDOMGENERATOR_HPP

class IRandomGenerator
{
public:
    IRandomGenerator() {}
    virtual ~IRandomGenerator() {}
    virtual int bounded(int lowest, int highest) = 0;
};

#endif // IRANDOMGENERATOR_HPP
