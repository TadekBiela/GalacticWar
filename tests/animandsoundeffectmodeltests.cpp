#include <gtest/gtest.h>
#include "../app/animandsoundeffectmodel.hpp"
#include "../app/definitions.hpp"
#include <QPointF>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QCoreApplication>
#include <QGraphicsItem>

class AnimAndSoundEffectModelTest : public AnimAndSoundEffectModel
{
public:
    AnimAndSoundEffectModelTest()
                                : AnimAndSoundEffectModel(){}
    virtual ~AnimAndSoundEffectModelTest() {}

    void setAnimation()
    {
        m_isAnimEnabled = true;
        m_animationTimer.setInterval(def::animationFrameDuration * def::maxAnimationFrames);
    }
    void setSound()
    {
        m_isSoundEnabled = true;
        m_sound.setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/sounds/explosion.wav"));
    }
    void runAnimation()
    {
        m_animationTimer.start();
    }
    void runSound()
    {
        m_sound.play();
    }

    QPointF             getPosition()       const { return QGraphicsItem::pos(); }
    bool                getIsAnimEnabled()  const { return m_isAnimEnabled; }
    int                 getAnimFramIdx()    const { return m_animationFrameIdx; }
    const QTimer&       getAnimTimer()      const { return m_animationTimer; }
    bool                getIsSoundEnabled() const { return m_isSoundEnabled; }
    const QMediaPlayer& getSound()          const { return m_sound; }
    const QTimer&       getDestroyTimer()   const { return m_destroyTimer; }
};

class AnimAndSoundEffectModelTestsClass : public testing::Test
{
};

TEST_F(AnimAndSoundEffectModelTestsClass, AnimAndSoundEffectModel_NoAnimationAndNoSoundCheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    const int expectedDefaultDestroyTimer = def::animationFrameDuration * def::maxAnimationFrames;

    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    QPointF             resultPosition       = animAndSoundEffectModel.getPosition();
    bool                resultIsAnimEnabled  = animAndSoundEffectModel.getIsAnimEnabled();
    int                 resultAnimFramIdx    = animAndSoundEffectModel.getAnimFramIdx();
    const QTimer&       resultAnimTimer      = animAndSoundEffectModel.getAnimTimer();
    bool                resultIsSoundEnabled = animAndSoundEffectModel.getIsSoundEnabled();
    const QMediaPlayer& resultSound          = animAndSoundEffectModel.getSound();
    const QTimer&       resultDestroyTimer   = animAndSoundEffectModel.getDestroyTimer();

    EXPECT_EQ(resultIsAnimEnabled,                 false);
    EXPECT_EQ(resultAnimFramIdx,                   0);
    EXPECT_EQ(resultAnimTimer.isActive(),          false);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_EQ(resultIsSoundEnabled,                false);
    EXPECT_EQ(resultSound.state(),                 QMediaPlayer::StoppedState);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), expectedDefaultDestroyTimer);
    EXPECT_FLOAT_EQ(resultPosition.x(),            0);
    EXPECT_FLOAT_EQ(resultPosition.y(),            0);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Start_AnimationAndSoundAreSetupCheckIfAllTimersAndMediaPlayerWillBeActive_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setAnimation();
    animAndSoundEffectModel.setSound();

    animAndSoundEffectModel.start();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    true);
    EXPECT_EQ(resultDestroyTimer.isActive(), true);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::PlayingState);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Start_OnlyAnimationIsSetupCheckIfAllTimersWillBeActive_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setAnimation();

    animAndSoundEffectModel.start();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    true);
    EXPECT_EQ(resultDestroyTimer.isActive(), true);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::StoppedState);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Start_OnlySoundIsSetupCheckIfDestroyTimerAndMediaPlayerWillBeActive_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setSound();

    animAndSoundEffectModel.start();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    false);
    EXPECT_EQ(resultDestroyTimer.isActive(), true);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::PlayingState);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Stop_AnimationAndSoundAreSetupCheckIfAllTimersAndMediaPlayerWillBePaused_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setAnimation();
    animAndSoundEffectModel.runAnimation();
    animAndSoundEffectModel.setSound();
    animAndSoundEffectModel.runSound();

    animAndSoundEffectModel.stop();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    false);
    EXPECT_EQ(resultDestroyTimer.isActive(), false);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::StoppedState);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Stop_OnlyAnimationIsSetupCheckIfAllTimersWillBePaused_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setAnimation();
    animAndSoundEffectModel.runAnimation();

    animAndSoundEffectModel.stop();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    false);
    EXPECT_EQ(resultDestroyTimer.isActive(), false);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::StoppedState);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Stop_OnlySoundIsSetupCheckIfDestroyTimerAndMediaPlayerWillBePaused_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setSound();
    animAndSoundEffectModel.runSound();

    animAndSoundEffectModel.stop();
    const QTimer&       resultAnimTimer    = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound        = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultAnimTimer.isActive(),    false);
    EXPECT_EQ(resultDestroyTimer.isActive(), false);
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::StoppedState);
}
