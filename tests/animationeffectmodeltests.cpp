#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/animationeffectmodel.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/definitions.hpp"
#include <QGraphicsScene>

class AnimationEffectModelTest : public AnimationEffectModel
{
public:
    AnimationEffectModelTest(QString animationName,
                             QPointF position,
                             int     animationFrameWidth,
                             int     animationFrameHeight,
                             int     numOfFrames)
                              : AnimationEffectModel(animationName,
                                                     position,
                                                     animationFrameWidth,
                                                     animationFrameHeight,
                                                     numOfFrames)
    {}
    virtual ~AnimationEffectModelTest() {}
    void animation()
    {
        AnimationEffectModel::animation();
    }

    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    void setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }
};

class AnimationEffectModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage       = new ImageStorage;
        m_displayWidget      = new QWidget;
        g_animationPlaneView = new AnimationPlaneView(m_displayWidget);
    }
    void TearDown()
    {
        delete g_animationPlaneView;
        delete m_displayWidget;
        delete g_imageStorage;
    }

private:
    QWidget* m_displayWidget;
};

TEST_F(AnimationEffectModelTestsClass, AnimationEffectModel_CheckCorrectModelBuilding_IsEqual)
{
    QGraphicsScene*           scene              = new QGraphicsScene();
    AnimationEffectModelTest* animation          = new AnimationEffectModelTest("explosion",
                                                                                QPointF(50, 50),
                                                                                def::animationFrameWidth,
                                                                                def::animationFrameHeight,
                                                                                def::maxAnimationFrames);
    int                       resultAnimFrameIdx = animation->getAnimationFrameIdx();
    const QTimer&             resultAnimTimer    = animation->getAnimationTimer();

    EXPECT_EQ(resultAnimFrameIdx,         0);
    EXPECT_EQ(resultAnimTimer.isActive(), false);
    EXPECT_EQ(resultAnimTimer.interval(), def::animationFrameDuration);
    delete scene;
}

TEST_F(AnimationEffectModelTestsClass, Animation_CheckIfAnimationFrameIdxWasIncreasedBy1_IsEqual)
{
    QGraphicsScene*           scene     = new QGraphicsScene();
    AnimationEffectModelTest* animation = new AnimationEffectModelTest("explosion",
                                                                       QPointF(50, 50),
                                                                       def::animationFrameWidth,
                                                                       def::animationFrameHeight,
                                                                       def::maxAnimationFrames);

    animation->animation();
    int resultAnimFrameIdx = animation->getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 1);
    delete scene;
}

TEST_F(AnimationEffectModelTestsClass, Animation_AnimationFrameIdxPointsToLastFrameCheckIfEffectWillBeDeleted_IsEqual)
{
    QGraphicsScene*           scene     = new QGraphicsScene();
    AnimationEffectModelTest* animation = new AnimationEffectModelTest("explosion",
                                                                       QPointF(50, 50),
                                                                       def::animationFrameWidth,
                                                                       def::animationFrameHeight,
                                                                       def::maxAnimationFrames);
    animation->setAnimationFrameIdx(def::maxAnimationFrameIdx);

    animation->animation();

    EXPECT_DEATH(animation->animation(), ".*");
    delete scene;
}
