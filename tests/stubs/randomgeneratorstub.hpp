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


class RandomSequanceGeneratorStub : public IRandomGenerator
{
public:
    RandomSequanceGeneratorStub(int sequanceLenght, int sequance[])
    {
        m_seqLenght = sequanceLenght;
        m_sequance  = sequance;
    }
    virtual ~RandomSequanceGeneratorStub() {}
    int bounded(int lowest, int highest)
    {
        int result = m_sequance[m_seqCount];
        m_seqCount = (m_seqCount + 1 < m_seqLenght) ? (m_seqCount + 1) : m_seqCount;
        return result;
    }

private:
    int  m_seqCount  = 0;
    int  m_seqLenght;
    int* m_sequance;
};

#endif // RANDOMGENERATORFAKE_HPP
