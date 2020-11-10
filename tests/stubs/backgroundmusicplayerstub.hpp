#ifndef BACKGROUNDMUSICPLAYERSTUB_HPP
#define BACKGROUNDMUSICPLAYERSTUB_HPP

#include <gmock/gmock.h>
#include "../app/ibackgroundmusicplayer.hpp"
#include "../app/settings.hpp"

using namespace testing;

class BackgroundMusicPlayerStub : public IBackgroundMusicPlayer
{
public:
    BackgroundMusicPlayerStub() {};
    virtual ~BackgroundMusicPlayerStub() {};

    MOCK_METHOD(void, play, (), ());
    MOCK_METHOD(void, pause, (), ());
    MOCK_METHOD(void, switchToMenuMusic, (), ());
    MOCK_METHOD(void, switchToGameMusic, (), ());
    MOCK_METHOD(void, applyNewSettings, (Settings), ());
};

#endif //BACKGROUNDMUSICPLAYERSTUB_HPP
