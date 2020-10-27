#include "randomgenerator.hpp"

RandomGenerator::RandomGenerator()
{
    generator = QRandomGenerator::system();
}

RandomGenerator::~RandomGenerator()
{

}

int RandomGenerator::bounded(int lowest, int highest)
{
    return generator->bounded(lowest, highest + 1);
}
