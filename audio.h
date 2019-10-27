//------------------------------------------------------------------------------
#ifndef AUDIO_H
#define AUDIO_H
#include <AL/al.h>
#include <AL/alc.h>
//------------------------------------------------------------------------------
#define BUFFERS 10

#define ATT_SOUND 0
#define AXE_SOUND 1
#define BOW_SOUND 2
#define CLICK_SOUND 3
#define DIE_SOUND 4
#define DIE2_SOUND 5
#define HIT_SOUND 6
#define STEP_SOUND 7
#define SWORD_SOUND 8
#define WHIP_SOUND 9
//------------------------------------------------------------------------------
#define SOURCES 13

#define PLAY_CLICK 0
#define PLAY_HIT 1
#define PLAY_ATT 2
#define PLAY_AXE 3
#define PLAY_BOW 4
#define PLAY_DIE 5
#define PLAY_DIE2 6
#define PLAY_STEP 7
#define PLAY_STEP2 8
#define PLAY_STEP3 9
#define PLAY_STEP4 10
#define PLAY_SWORD 11
#define PLAY_WHIP 12
//------------------------------------------------------------------------------

class Audio {
public:
    static ALuint Buffers[BUFFERS];
    static ALboolean Init();
    static ALuint sources[SOURCES];
    static void Play(int sc);
    static void Stop(int sc);
    static void Unload();

private:
    static ALboolean LoadBuffer(const char* fileName, int ind);
    static ALboolean CreateSources();
    static ALboolean LoadAudio();
    static void SetListenerValues();
    static ALboolean Source(int ind, int buff, float pitch, float gain, ALboolean loop);
};
//------------------------------------------------------------------------------     
#endif
