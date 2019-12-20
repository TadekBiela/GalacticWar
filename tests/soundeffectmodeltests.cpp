#include <gtest/gtest.h>
#include "../app/soundeffectmodel.hpp"
#include <QSignalSpy>

class SoundEffectModelTest : public SoundEffectModel
{
public:
    SoundEffectModelTest(QString soundName)
                     : SoundEffectModel(soundName){}
    virtual ~SoundEffectModelTest() {}

    const QSoundEffect* getSound() const { return m_sound; }
};

class SoundEffectModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_soundStorage = new SoundStorage;
    }
    void TearDown()
    {
        delete g_soundStorage;
    }
};

TEST_F(SoundEffectModelTestsClass, SoundEffectModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    SoundEffectModelTest* soundEffectModel = new SoundEffectModelTest("default_bullet");
    const QSoundEffect* resultSound = soundEffectModel->getSound();

    EXPECT_EQ(resultSound->isPlaying(), true);
}
