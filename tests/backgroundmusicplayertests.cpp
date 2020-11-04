#include <gtest/gtest.h>
#include "../app/backgroundmusicplayer.hpp"
#include <QSignalSpy>

class BackgroundMusicPlayerTest : public BackgroundMusicPlayer
{
public:
    BackgroundMusicPlayerTest() {}
    virtual ~BackgroundMusicPlayerTest() {}

    const QMediaPlayer& getMediaPlayer() const {
        return m_mediaPlayer;
    }
    const QMediaPlaylist& getMenuPlaylist() const {
        return m_menuPlaylist;
    }
    const QMediaPlaylist& getGamePlaylist() const {
        return m_gamePlaylist;
    }
};

class BackgroundMusicPlayerTestsClass : public testing::Test
{
};

TEST_F(BackgroundMusicPlayerTestsClass, Constructor_LoadAllMusic_ShouldLoadMenuAndGamePlaylistsAndStartPlayMenuPlaylist)
{
    BackgroundMusicPlayerTest musicPlayer;

    const QMediaPlayer& resultMediaPlayer = musicPlayer.getMediaPlayer();
    const QMediaPlaylist& resultMenuPlaylist = musicPlayer.getMenuPlaylist();
    EXPECT_EQ(&resultMenuPlaylist, resultMediaPlayer.playlist());
    EXPECT_EQ(QMediaPlayer::PlayingState, resultMediaPlayer.state());
    EXPECT_EQ(1, resultMenuPlaylist.mediaCount());
    EXPECT_EQ(QMediaPlaylist::Loop, resultMenuPlaylist.playbackMode());
    const QMediaPlaylist& resultGamePlaylist = musicPlayer.getGamePlaylist();
    EXPECT_EQ(3, resultGamePlaylist.mediaCount());
    EXPECT_EQ(QMediaPlaylist::Loop, resultGamePlaylist.playbackMode());
}

TEST_F(BackgroundMusicPlayerTestsClass, Play_MusicIsPaused_ShouldPlayMusic)
{
    BackgroundMusicPlayerTest musicPlayer;
    musicPlayer.pause();

    musicPlayer.play();

    const QMediaPlayer& resultMediaPlayer = musicPlayer.getMediaPlayer();
    EXPECT_EQ(QMediaPlayer::PlayingState, resultMediaPlayer.state());
}

TEST_F(BackgroundMusicPlayerTestsClass, Pause_MusicIsPalaing_ShouldPauseMusic)
{
    BackgroundMusicPlayerTest musicPlayer;

    musicPlayer.pause();

    const QMediaPlayer& resultMediaPlayer = musicPlayer.getMediaPlayer();
    EXPECT_EQ(QMediaPlayer::PausedState, resultMediaPlayer.state());
}

TEST_F(BackgroundMusicPlayerTestsClass, SwitchToGameMusic_CurrentMusicIsMenu_ShouldChangeToGameMusic)
{
    BackgroundMusicPlayerTest musicPlayer;

    musicPlayer.switchToGameMusic();

    const QMediaPlayer& resultMediaPlayer = musicPlayer.getMediaPlayer();
    EXPECT_EQ(QMediaPlayer::PlayingState, resultMediaPlayer.state());
    const QMediaPlaylist& resultGamePlaylist = musicPlayer.getGamePlaylist();
    EXPECT_EQ(&resultGamePlaylist, resultMediaPlayer.playlist());
}

TEST_F(BackgroundMusicPlayerTestsClass, SwitchToMenuMusic_CurrentMusicIsGame_ShouldChangeToMenuMusic)
{
    BackgroundMusicPlayerTest musicPlayer;
    musicPlayer.switchToGameMusic();

    musicPlayer.switchToMenuMusic();

    const QMediaPlayer& resultMediaPlayer = musicPlayer.getMediaPlayer();
    EXPECT_EQ(QMediaPlayer::PlayingState, resultMediaPlayer.state());
    const QMediaPlaylist& resultMenuPlaylist = musicPlayer.getMenuPlaylist();
    EXPECT_EQ(&resultMenuPlaylist, resultMediaPlayer.playlist());
}

