#include "AudioManager.h"

void AudioManager::Init() {
    InitAudioDevice();

    musicTracks.push_back(LoadMusicStream("res/audio/BGM/Danganronpa!.mp3"));   // 0
    musicTracks.push_back(LoadMusicStream("res/audio/BGM/BeautifulDeath.mp3")); // 1
}

void AudioManager::PlaySFX(SoundID id) {
    if ((int)id >= 0 && (int)id < sounds.size()) {
        PlaySound(sounds[id]);
    }
}

void AudioManager::PlayBGM(MusicID id) {
    int index = (int)id;
    if (index >= 0 && index < musicTracks.size()) {
        if (isMusicPlaying) StopMusicStream(musicTracks[currentMusicIndex]);
        
        currentMusicIndex = index;
        PlayMusicStream(musicTracks[index]);
        isMusicPlaying = true;
    }
}

void AudioManager::Update() {
    if (isMusicPlaying) {
        UpdateMusicStream(musicTracks[currentMusicIndex]);
    }
}

void AudioManager::StopBGM() {
    if (isMusicPlaying) {
        StopMusicStream(musicTracks[currentMusicIndex]);
        isMusicPlaying = false;
    }
}

void AudioManager::Shutdown() {
    for (auto& s : sounds) UnloadSound(s);
    for (auto& m : musicTracks) UnloadMusicStream(m);
    CloseAudioDevice();
}