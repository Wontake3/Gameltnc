#include "music.h"
#include "exception.h"

Music::Music() : gMusic{nullptr} {}

Music::Music(const std::string& path) :Music()
{
    gMusic = Mix_LoadMUS(path.c_str());
    if (gMusic == nullptr) {
        logErrorAndExit("Could not load music! SDL_mixer Error: ", Mix_GetError());
    }
}

Music::~Music()
{
    if (gMusic != nullptr) {
        Mix_FreeMusic( gMusic );
    }
}

void Music::play()
{
    if (gMusic != nullptr) {
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }
}

void Music::pause()
{
    if (Mix_PlayingMusic() == 1) {
        Mix_PauseMusic();
    }
}

void Music::stop()
{
    pause();
    Mix_RewindMusic();
}

Sound::Sound() : gChunk{nullptr} {}

Sound::Sound(const std::string& path)
    : Sound()
{
    gChunk = Mix_LoadWAV(path.c_str());
    if (gChunk == nullptr) {
        logErrorAndExit("Could not load sound! SDL_mixer Error: ", Mix_GetError());
    }
}

Sound::~Sound()
{
    if (gChunk != nullptr) {
        Mix_FreeChunk(gChunk);
    }
}

void Sound::play()
{
    if (gChunk != nullptr) {
        Mix_PlayChannel( -1, gChunk, 0 );
    }
}

void Sound::setVolume(int volume)
{
    if (gChunk != nullptr) {
        Mix_VolumeChunk(gChunk, volume);
    }
}
