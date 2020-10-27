#ifndef ENEMYCONFIGURATION_HPP
#define ENEMYCONFIGURATION_HPP

// Each EnemyConfig members sum should be equal 100
struct EnemyConfiguration
{
    int minEnemySpawnTimeDelay;
    int maxEnemySpawnTimeDelay;

    int proportionOfEnemyType1;
    int proportionOfEnemyType2;
    int proportionOfEnemyType3;
    int proportionOfEnemyType4;
    int proportionOfEnemyType5;
    int proportionOfEnemyType6;
};

#endif // ENEMYCONFIGURATION_HPP
