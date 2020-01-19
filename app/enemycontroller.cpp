#include "enemycontroller.hpp"
#include "enemymodeltype1.hpp"

EnemyController::EnemyController(GeneralView*      view,
                                 IRandomGenerator* generator)
                                  : m_remainigSpawnTime(def::minEnemySpawnTimeDelay),
                                    m_generator(generator)
{
    connect(this,               SIGNAL(addEnemyToScene(QGraphicsItem*)),
            view,               SLOT(addGameObject(QGraphicsItem*)));
    connect(&m_enemySpawnTimer, SIGNAL(timeout()),
            this,               SLOT(spawnEnemy()));
    m_enemySpawnTimer.setInterval(def::minEnemySpawnTimeDelay);
}

EnemyController::~EnemyController()
{

}

void EnemyController::changeEnemyConfiguration(EnemyConfiguration newConfiguration)
{
    int offset = 0;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType1; i++)
    {
        m_enemyPercentDistributionTab[i + offset] = 1;
    }
    offset += newConfiguration.proportionOfEnemyType1;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType2; i++)
    {
        m_enemyPercentDistributionTab[i + offset] = 2;
    }
    offset += newConfiguration.proportionOfEnemyType2;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType3; i++)
    {
        m_enemyPercentDistributionTab[i + offset] = 3;
    }
    offset += newConfiguration.proportionOfEnemyType3;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType4; i++)
    {
        m_enemyPercentDistributionTab[i + offset] = 4;
    }
    offset += newConfiguration.proportionOfEnemyType4;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType5; i++)
    {
        m_enemyPercentDistributionTab[i + offset] = 5;
    }
    offset += newConfiguration.proportionOfEnemyType5;
    for(int i = 0; i < newConfiguration.proportionOfEnemyType6; i++)
    {
        m_enemyPercentDistributionTab[i + offset] = 6;
    }
}

void EnemyController::destroyed(QPointF position, int enemyLevel)
{
    emit enemyDestroyed(position, enemyLevel);
}

void EnemyController::startSpawning()
{
    m_enemySpawnTimer.setInterval(m_remainigSpawnTime);
    m_enemySpawnTimer.start();
}

void EnemyController::stopSpawning()
{
    int remainingSpawnTime = m_enemySpawnTimer.remainingTime() > 0 ?
                             m_enemySpawnTimer.remainingTime() :
                             def::minEnemySpawnTimeDelay;
    m_remainigSpawnTime = remainingSpawnTime;
    m_enemySpawnTimer.stop();
}

void EnemyController::spawnEnemy()
{
    EnemyModel* enemy;
    int enemyTypeIdx = m_generator->bounded(0, def::percentDistTabSize - 1);
    int enemyType    = m_enemyPercentDistributionTab[enemyTypeIdx];
    QPointF enemyPosition(m_generator->bounded(def::animationFrameWight / 2,
                                               def::sceneWight - def::animationFrameWight),
                          -def::animationFrameHeight / 2 + 1);
    switch (enemyType)
    {
        case 1:
        default:
            enemy = new EnemyModelType1(enemyPosition, m_generator);
            connect(enemy, SIGNAL(destroyed(QPointF, int)),
                    this,  SLOT(destroyed(QPointF, int)));
            enemy->start();
            break;
    }
    emit addEnemyToScene(enemy);
    int newEnemySPawnDelay = m_generator->bounded(def::minEnemySpawnTimeDelay,
                                                  def::maxEnemySpawnTimeDelay);
    m_enemySpawnTimer.setInterval(newEnemySPawnDelay);
}
