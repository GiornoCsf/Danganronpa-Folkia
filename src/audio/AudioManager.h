#pragma once

#include <raylib.h>
#include <vector>

enum SoundID {
    SFX_SELECT,
    SFX_CURSOR
};

enum MusicID {
    BGM_TITLE,
    BGM_FREE_ROAM,
    BGM_BEAUTIFUL_DAYS,
    BGM_INVESTIGATION
};

class AudioManager {
public:
    static void Init();      
    static void Update();    
    static void Shutdown();

    static void PlaySFX(SoundID id);
    static void PlayBGM(MusicID id);
    static void StopBGM();

private:
    static inline std::vector<Sound> sounds;
    static inline std::vector<Music> musicTracks;
    static inline int currentMusicIndex = -1;
    static inline bool isMusicPlaying = false;
};