#include <gtest/gtest.h>
#include "../app/soundeffectmodel.hpp"
#include <QMediaContent>
#include <QUrl>
#include <QCoreApplication>
#include <QTest>

class SoundEffectModelTest : public SoundEffectModel
{
public:
    SoundEffectModelTest(QMediaPlayer* player)
                     : SoundEffectModel(player){}
    virtual ~SoundEffectModelTest() {}
    void stopTestFunc()
    {
        m_remainingDestroyTime = m_destroyTimer.remainingTime();
        m_destroyTimer.stop();
        m_player->pause();
    }

    const QMediaPlayer* getPlayer()               const { return m_player; }
    const QTimer&       getDestroyTimer()         const { return m_destroyTimer; }
    int                 getRemainingDestroyTime() const { return m_remainingDestroyTime; }
};

class SoundEffectModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        QMediaContent sound(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/sounds/explosion.wav"));
        mediaPlayer = new QMediaPlayer();
        mediaPlayer->setMedia(sound);
        bool status = QTest::qWaitFor([&]() {
                return mediaPlayer->mediaStatus() == QMediaPlayer::LoadedMedia;
            }, 1000);
        ASSERT_TRUE(status);
    }
    void TearDown()
    {
        delete mediaPlayer;
    }

    QMediaPlayer* mediaPlayer;
};

TEST_F(SoundEffectModelTestsClass, SoundEffectModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{

    SoundEffectModelTest soundEffectModel(mediaPlayer);
    const QMediaPlayer* resultPlayer               = soundEffectModel.getPlayer();
    const QTimer&       resultDestroyTimer         = soundEffectModel.getDestroyTimer();
    int                 resultRemainingDestroyTime = soundEffectModel.getRemainingDestroyTime();

    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), 2775);
    EXPECT_EQ(resultRemainingDestroyTime,          2775);
}

TEST_F(SoundEffectModelTestsClass, Start_CheckIfDestroyTimerWillBeActiveWithCorrectTime_IsEqual)
{
    SoundEffectModelTest soundEffectModel(mediaPlayer);
    QTest::qWait(1000);
    soundEffectModel.stopTestFunc();

    soundEffectModel.start();
    const QMediaPlayer* resultPlayer       = soundEffectModel.getPlayer();
    const QTimer&       resultDestroyTimer = soundEffectModel.getDestroyTimer();

    EXPECT_EQ(resultPlayer->state(),           QMediaPlayer::PlayingState);
    EXPECT_EQ(resultDestroyTimer.isActive(),   true);
    EXPECT_NEAR(resultDestroyTimer.interval(), 1775, 5);
}

TEST_F(SoundEffectModelTestsClass, Stop_CheckIfDestroyTimerAndMediaPlayerWillBeStopped_IsEqual)
{
    SoundEffectModelTest soundEffectModel(mediaPlayer);
    QTest::qWait(1000);

    soundEffectModel.stop();
    const QMediaPlayer* resultPlayer               = soundEffectModel.getPlayer();
    const QTimer&       resultDestroyTimer         = soundEffectModel.getDestroyTimer();
    int                 resultRemainingDestroyTime = soundEffectModel.getRemainingDestroyTime();

    EXPECT_EQ(resultPlayer->state(),           QMediaPlayer::PausedState);
    EXPECT_EQ(resultDestroyTimer.isActive(),   false);
    EXPECT_NEAR(resultDestroyTimer.interval(), 2775, 5);
    EXPECT_NEAR(resultRemainingDestroyTime,    1775, 5);
}

TEST_F(SoundEffectModelTestsClass, Destroy_CheckIfEffectWillBeDeleted_IsEqual)
{
    SoundEffectModelTest* soundEffectModel = new SoundEffectModelTest(mediaPlayer);

    soundEffectModel->destroy();

    ASSERT_DEATH(soundEffectModel->start(), ".*");
}
