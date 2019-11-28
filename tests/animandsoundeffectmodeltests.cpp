#include <gtest/gtest.h>
#include "../app/animandsoundeffectmodel.hpp"
#include "../app/definitions.hpp"
#include <QPointF>
#include <QTimer>
#include <QMediaPlayer>
#include <QGraphicsItem>

class AnimAndSoundEffectModelTest : public AnimAndSoundEffectModel
{
public:
    AnimAndSoundEffectModelTest()
                                : AnimAndSoundEffectModel(){}
    virtual ~AnimAndSoundEffectModelTest() {}

    QPointF             getPosition()     const { return QGraphicsItem::pos(); }
    int                 getAnimFramIdx()  const { return m_animationFrameIdx; }
    const QTimer&       getAnimTimer()    const { return m_animationTimer; }
    const QMediaPlayer& getSound()        const { return m_sound; }
    const QTimer&       getDestroyTimer() const { return m_destroyTimer; }
};

class AnimAndSoundEffectModelTestsClass : public testing::Test
{
};

TEST_F(AnimAndSoundEffectModelTestsClass, AnimAndSoundEffectModel_NoAnimationAndNoSoundCheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    const int expectedDefaultDestroyTimer = def::animationFrameDuration * def::maxAnimationFrames;

    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    QPointF             resultPosition     = animAndSoundEffectModel.getPosition();
    int                 resultAnimFramIdx  = animAndSoundEffectModel.getAnimFramIdx();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();

    EXPECT_EQ(resultAnimFramIdx,                   0);
    EXPECT_EQ(resultAnimTimer.isActive(),          false);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_EQ(resultSound.state(),                 QMediaPlayer::StoppedState);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), expectedDefaultDestroyTimer);
    EXPECT_FLOAT_EQ(resultPosition.x(),            0);
    EXPECT_FLOAT_EQ(resultPosition.y(),            0);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Start_SoundIsSetupCheckIfAllTimersAndMediaPlayerWillBeActive_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;

    animAndSoundEffectModel.start();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    true);
    EXPECT_EQ(resultDestroyTimer.isActive(), true);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::PlayingState);
}
