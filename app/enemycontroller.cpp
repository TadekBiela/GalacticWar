#include "enemycontroller.hpp"
#include "enemymodeltype1.hpp"

EnemyController::EnemyController(GeneralView*      view,
                                 IRandomGenerator* generator) :
                                 m_generator(generator)
{
    EnemyConfiguration setupConfig = { 100, 0, 0, 0, 0, 0 };
    changeEnemyConfiguration(setupConfig);

    connect(&m_enemySpawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    m_enemySpawnTimer.setInterval(def::minEnemySpawnTimeDelay);
    m_enemySpawnTimer.start();
}

EnemyController::~EnemyController()
{

}

void EnemyController::changeEnemyConfiguration(EnemyConfiguration newConfiguration)
{
    int offset = 0;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType1; i++)
        m_enemyPercentDistributionTab[i + offset] = 1;
    offset += newConfiguration.proportionOfEnemyType1;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType2; i++)
        m_enemyPercentDistributionTab[i + offset] = 2;
    offset += newConfiguration.proportionOfEnemyType2;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType3; i++)
        m_enemyPercentDistributionTab[i + offset] = 3;
    offset += newConfiguration.proportionOfEnemyType3;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType4; i++)
        m_enemyPercentDistributionTab[i + offset] = 4;
    offset += newConfiguration.proportionOfEnemyType4;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType5; i++)
        m_enemyPercentDistributionTab[i + offset] = 5;
    offset += newConfiguration.proportionOfEnemyType5;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType6; i++)
        m_enemyPercentDistributionTab[i + offset] = 6;
}

void EnemyController::destroyed(QPointF position, int enemyLevel)
{
    emit enemyDestroyed(position, enemyLevel);
}

void EnemyController::spawnEnemy()
{
    EnemyModel* enemy;
    int enemyTypeIdx = m_generator->bounded(0, def::percentDistTabSize - 1);
    int enemyType    = m_enemyPercentDistributionTab[enemyTypeIdx];
    QPointF enemyPosition(m_generator->bounded(0, def::sceneWight - def::animationFrameWight),
                          -def::animationFrameHeight);
    switch (enemyType)
    {
        case 1:
            enemy = new EnemyModelType1(enemyPosition, m_generator);
            break;
    }
    emit addEnemyToScene(enemy);
}
