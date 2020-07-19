#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/animationeffectmodel.hpp"
#include "../app/definitions.hpp"
#include <QGraphicsScene>

//class AnimationEffectModelTest : public AnimationEffectModel
//{
//public:
//    AnimationEffectModelTest(QString animationName,
//                             QPointF position,
//                             int     animationFrameWidth,
//                             int     animationFrameHeight,
//                             int     numOfFrames)
//                              : AnimationEffectModel(animationName,
//                                                     position,
//                                                     animationFrameWidth,
//                                                     animationFrameHeight,
//                                                     numOfFrames)
//    {}
//    virtual ~AnimationEffectModelTest() {}

//    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
//    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
//    void setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }
//};

//class AnimationEffectModelTestsClass : public testing::Test
//{
//public:
//    void SetUp()
//    {
//        g_imageStorage = new ImageStorage;
//    }
//    void TearDown()
//    {
//        delete g_imageStorage;
//    }
//};

//TEST_F(AnimationEffectModelTestsClass, AnimationEffectModel_CheckCorrectModelBuilding_IsEqual)
//{
//    QGraphicsScene*           scene              = new QGraphicsScene();
//    AnimationEffectModelTest* animation          = new AnimationEffectModelTest(scene,
//                                                                                "explosion",
//                                                                                QPointF(50, 50),
//                                                                                def::animationFrameWight,
//                                                                                def::animationFrameHeight,
//                                                                                def::maxAnimationFrames);
//    int                       resultAnimFrameIdx = animation->getAnimationFrameIdx();
//    const QTimer&             resultAnimTimer    = animation->getAnimationTimer();

//    EXPECT_EQ(resultAnimFrameIdx,         0);
//    EXPECT_EQ(resultAnimTimer.isActive(), true);
//    EXPECT_EQ(resultAnimTimer.interval(), def::animationFrameDuration);
//    delete scene;
//}

//TEST_F(AnimationEffectModelTestsClass, Animation_CheckIfAnimationFrameIdxWasIncreasedBy1_IsEqual)
//{
//    QGraphicsScene*           scene     = new QGraphicsScene();
//    AnimationEffectModelTest* animation = new AnimationEffectModelTest(scene,
//                                                                       "explosion",
//                                                                       QPointF(50, 50),
//                                                                       def::animationFrameWight,
//                                                                       def::animationFrameHeight,
//                                                                       def::maxAnimationFrames);

//    animation->animation();
//    int resultAnimFrameIdx = animation->getAnimationFrameIdx();

//    EXPECT_EQ(resultAnimFrameIdx, 1);
//    delete scene;
//}

//TEST_F(AnimationEffectModelTestsClass, Animation_AnimationFrameIdxPointsToLastFrameCheckIfEffectWillBeDeleted_IsEqual)
//{
//    QGraphicsScene*           scene     = new QGraphicsScene();
//    AnimationEffectModelTest* animation = new AnimationEffectModelTest(scene,
//                                                                       "explosion",
//                                                                       QPointF(50, 50),
//                                                                       def::animationFrameWight,
//                                                                       def::animationFrameHeight,
//                                                                       def::maxAnimationFrames);
//    animation->setAnimationFrameIdx(def::maxAnimationFrameIdx);

//    animation->animation();

//    EXPECT_DEATH(animation->animation(), ".*");
//    delete scene;
//}
