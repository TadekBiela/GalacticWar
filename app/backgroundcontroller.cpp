#include "backgroundcontroller.hpp"
#include "backgroundeffectmodel.hpp"
#include "definitions.hpp"
#include "randomgenerator.hpp"

BackgroundController::BackgroundController(QWidget* displayWidget)
    : m_generator(new RandomGenerator),
      m_view(displayWidget),
      m_itemsSpawnTimer()
{
    connect(&m_itemsSpawnTimer, SIGNAL(timeout()),
            this,               SLOT(spawnItem()));

    int itemSpawnTimeDelay = m_generator->bounded(def::minBackgroundItemSpawnTimeDelay,
                                                  def::maxBackgroundItemSpawnTimeDelay);
    m_itemsSpawnTimer.setInterval(itemSpawnTimeDelay);
    m_itemsSpawnTimer.start();
}

BackgroundController::~BackgroundController()
{
    delete m_generator;
}

void BackgroundController::activate()
{
    m_view.activate();
    m_itemsSpawnTimer.start();
}

void BackgroundController::deactivate()
{
    m_view.deactivate();
    m_itemsSpawnTimer.stop();
}

void BackgroundController::increaseBackgroundSpeed()
{
    m_view.setBackgroundTimeDelay(def::shortBackgroundAnimTimeDelay);
}

void BackgroundController::decreaseBackgroundSpeed()
{
    m_view.setBackgroundTimeDelay(def::defaultBackgroundAnimTimeDelay);
}

void BackgroundController::resetToDefault()
{
    m_view.activate();
    m_view.setBackgroundTimeDelay(def::defaultBackgroundAnimTimeDelay);
}

void BackgroundController::spawnItem()
{
    background_effect type = static_cast<background_effect>(
                m_generator->bounded(background_effect::first_element,
                                     background_effect::last_element));
    const int sceneBorderOffset = 10;
    int startPositionX = m_generator->bounded(sceneBorderOffset,
                                              def::sceneWight  - sceneBorderOffset);
    int startPositionY = m_generator->bounded(sceneBorderOffset,
                                              def::sceneHeight - sceneBorderOffset);
    QPointF startPosition(startPositionX, startPositionY);
    int moveDirection = m_generator->bounded(0, 359);
    BackgroundEffectModel* newBgEffect = new BackgroundEffectModel(type,
                                                                   startPosition,
                                                                   moveDirection);
    newBgEffect->play();
    m_view.addEffectToScene(newBgEffect);
}
