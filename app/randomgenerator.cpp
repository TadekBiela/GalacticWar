#include "randomgenerator.hpp"

RandomGenerator::RandomGenerator()
{

}

RandomGenerator::~RandomGenerator()
{

}

int RandomGenerator::bounded(int lowest, int highest)
{
    return generator.bounded(lowest, highest + 1);
}
