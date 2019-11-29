#include <gtest/gtest.h>
#include "../app/animandsoundeffectmodel.hpp"
#include "../app/definitions.hpp"
#include <QPointF>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QCoreApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>

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
    int setAnimFramIdx(int animFrameIdx) { m_animationFrameIdx = animFrameIdx; }

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

TEST_F(AnimAndSoundEffectModelTestsClass, AnimationSetup_CheckCorrectWorking_IsEqual)
{
    const int expectedDestroyTimer = def::animationFrameDuration * def::maxAnimationFrames;

    AnimAndSoundEffectModelTest animAndSoundEffectModel;

    animAndSoundEffectModel.animationSetup("explosion", QPointF(200, 300));
    bool                resultIsAnimEnabled  = animAndSoundEffectModel.getIsAnimEnabled();
    bool                resultIsSoundEnabled = animAndSoundEffectModel.getIsSoundEnabled();
    const QTimer&       resultAnimTimer      = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer   = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound          = animAndSoundEffectModel.getSound();
    QPointF             resultPosition       = animAndSoundEffectModel.getPosition();

    EXPECT_EQ(resultIsAnimEnabled,                 true);
    EXPECT_EQ(resultIsSoundEnabled,                false);
    EXPECT_EQ(resultAnimTimer.isActive(),          false);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_EQ(resultSound.state(),                 QMediaPlayer::StoppedState);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), expectedDestroyTimer);
    EXPECT_FLOAT_EQ(resultPosition.x(),            170);
    EXPECT_FLOAT_EQ(resultPosition.y(),            270);
}

TEST_F(AnimAndSoundEffectModelTestsClass, SoundSetup_CheckCorrectWorking_IsEqual)
{
    const int expectedDestroyTimer = 2000;

    AnimAndSoundEffectModelTest animAndSoundEffectModel;

    animAndSoundEffectModel.soundSetup("explosion");
    bool                resultIsAnimEnabled  = animAndSoundEffectModel.getIsAnimEnabled();
    bool                resultIsSoundEnabled = animAndSoundEffectModel.getIsSoundEnabled();
    const QTimer&       resultAnimTimer      = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer   = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound          = animAndSoundEffectModel.getSound();

    EXPECT_EQ(resultIsAnimEnabled,                 false);
    EXPECT_EQ(resultIsSoundEnabled,                true);
    EXPECT_EQ(resultAnimTimer.isActive(),          false);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_EQ(resultSound.state(),                 QMediaPlayer::StoppedState);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    0);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), expectedDestroyTimer);
}

TEST_F(AnimAndSoundEffectModelTestsClass, AnimationAndSoundSetup_SoundIsLongerThanAnimationCheckCorrectWorking_IsEqual)
{
    const int expectedDestroyTimer = 2000;

    AnimAndSoundEffectModelTest animAndSoundEffectModel;

    animAndSoundEffectModel.animationSetup("explosion", QPointF(200, 300));
    animAndSoundEffectModel.soundSetup("explosion");
    bool                resultIsAnimEnabled  = animAndSoundEffectModel.getIsAnimEnabled();
    bool                resultIsSoundEnabled = animAndSoundEffectModel.getIsSoundEnabled();
    const QTimer&       resultAnimTimer      = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer   = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound          = animAndSoundEffectModel.getSound();
    QPointF             resultPosition       = animAndSoundEffectModel.getPosition();

    EXPECT_EQ(resultIsAnimEnabled,                 true);
    EXPECT_EQ(resultIsSoundEnabled,                true);
    EXPECT_EQ(resultAnimTimer.isActive(),          false);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_EQ(resultSound.state(),                 QMediaPlayer::StoppedState);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), expectedDestroyTimer);
    EXPECT_FLOAT_EQ(resultPosition.x(),            170);
    EXPECT_FLOAT_EQ(resultPosition.y(),            270);
}

TEST_F(AnimAndSoundEffectModelTestsClass, AnimationAndSoundSetup_SoundIsShortedThanAnimationCheckCorrectWorking_IsEqual)
{
    const int expectedDestroyTimer = def::animationFrameDuration * def::maxAnimationFrames;;

    AnimAndSoundEffectModelTest animAndSoundEffectModel;

    animAndSoundEffectModel.animationSetup("explosion", QPointF(200, 300));
    animAndSoundEffectModel.soundSetup("default_bullet");
    bool                resultIsAnimEnabled  = animAndSoundEffectModel.getIsAnimEnabled();
    bool                resultIsSoundEnabled = animAndSoundEffectModel.getIsSoundEnabled();
    const QTimer&       resultAnimTimer      = animAndSoundEffectModel.getAnimTimer();
    const QTimer&       resultDestroyTimer   = animAndSoundEffectModel.getDestroyTimer();
    const QMediaPlayer& resultSound          = animAndSoundEffectModel.getSound();
    QPointF             resultPosition       = animAndSoundEffectModel.getPosition();

    EXPECT_EQ(resultIsAnimEnabled,                 true);
    EXPECT_EQ(resultIsSoundEnabled,                true);
    EXPECT_EQ(resultAnimTimer.isActive(),          false);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_EQ(resultSound.state(),                 QMediaPlayer::StoppedState);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), expectedDestroyTimer);
    EXPECT_FLOAT_EQ(resultPosition.x(),            170);
    EXPECT_FLOAT_EQ(resultPosition.y(),            270);
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
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::PausedState);
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
    EXPECT_EQ(resultSound.state(),           QMediaPlayer::PausedState);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Animation_AnimationFrameIdxIs0CheckIfWillBeIncreased_IsOne)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;

    animAndSoundEffectModel.animation();
    int resultAnimFrameIdx = animAndSoundEffectModel.getAnimFramIdx();

    EXPECT_EQ(resultAnimFrameIdx, 1);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Animation_AnimationFrameIdxIsMaxCheckIfWillBeResetTo0_IsZero)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setAnimFramIdx(def::maxAnimationFrameIdx);

    animAndSoundEffectModel.animation();
    int resultAnimFrameIdx = animAndSoundEffectModel.getAnimFramIdx();

    EXPECT_EQ(resultAnimFrameIdx, 0);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Animation_AnimationFrameIdxIsMaxMinusOneCheckIfWillBeSetToMax_IsEqual)
{
    AnimAndSoundEffectModelTest animAndSoundEffectModel;
    animAndSoundEffectModel.setAnimFramIdx(def::maxAnimationFrameIdx - 1);

    animAndSoundEffectModel.animation();
    int resultAnimFrameIdx = animAndSoundEffectModel.getAnimFramIdx();

    EXPECT_EQ(resultAnimFrameIdx, def::maxAnimationFrameIdx);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Destory_EffectIsAddedToSceneChechIfWillBeRemovedFromSceneAndDeleted_IsEqual)
{
    QGraphicsScene scene;
    AnimAndSoundEffectModelTest* animAndSoundEffectModel = new AnimAndSoundEffectModelTest;
    animAndSoundEffectModel->setAnimFramIdx(def::maxAnimationFrameIdx - 1);
    scene.addItem(animAndSoundEffectModel);

    animAndSoundEffectModel->destroy();
    int resultNumOfSceneItems = scene.items().size();

    EXPECT_EQ(resultNumOfSceneItems, 0);
}

TEST_F(AnimAndSoundEffectModelTestsClass, Destory_EffectIsNotAddedToSceneChechIfWillBeCorrectlyDeleted_IsEqual)
{
    AnimAndSoundEffectModelTest* animAndSoundEffectModel = new AnimAndSoundEffectModelTest;
    animAndSoundEffectModel->setAnimFramIdx(def::maxAnimationFrameIdx - 1);

    ASSERT_EXIT((animAndSoundEffectModel->destroy(),exit(0)),::testing::ExitedWithCode(0),".*");
}
