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

    const QMediaPlayer* getPlayer()               const { return m_player; }
    const QTimer&       getDestroyTimer()         const { return m_destroyTimer; }
    int                 getRemainingDestroyTime() const { return m_remainingDestroyTime; }
};

class SoundEffectModelTestsClass : public testing::Test
{
};

TEST_F(SoundEffectModelTestsClass, SoundEffectModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    QMediaContent sound(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/sounds/explosion.wav"));
    QMediaPlayer* player = new QMediaPlayer();
    player->setMedia(sound);
    bool status = QTest::qWaitFor([&]() {
            return player->mediaStatus() == QMediaPlayer::LoadedMedia;
        }, 3000);

    SoundEffectModelTest SoundEffectModel(player);
    const QMediaPlayer* resultPlayer               = SoundEffectModel.getPlayer();
    const QTimer&       resultDestroyTimer         = SoundEffectModel.getDestroyTimer();
    int                 resultRemainingDestroyTime = SoundEffectModel.getRemainingDestroyTime();

    ASSERT_TRUE(status);
    EXPECT_EQ(resultPlayer->state(),               QMediaPlayer::PlayingState);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), 2775);
    EXPECT_EQ(resultRemainingDestroyTime,          2775);
    delete player;
}
