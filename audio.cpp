//------------------------------------------------------------------------------
#include "audio.h"
#include <stdio.h>
#include <stdint.h>
//------------------------------------------------------------------------------
ALuint Audio::Buffers[BUFFERS];
ALuint Audio::sources[SOURCES];
//------------------------------------------------------------------------------

ALboolean Audio::Init()
{
    //init OpenAL
    ALCdevice* pDevice;
    ALCcontext* pContext;
    pDevice = alcOpenDevice(NULL);
    pContext = alcCreateContext(pDevice, NULL);
    alcMakeContextCurrent(pContext);

    if (alcGetError(pDevice) != ALC_NO_ERROR)
        return AL_FALSE;
    alGetError();

    LoadAudio();
    CreateSources();
    return AL_TRUE;
}
//------------------------------------------------------------------------------

void Audio::SetListenerValues()
{
    ALfloat ListenerPos[] = {0.0f, 0.0f, 0.0f};
    ALfloat ListenerVel[] = {0.0f, 0.0f, 0.0f};
    ALfloat ListenerOri[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}

//------------------------------------------------------------------------------

ALboolean Audio::LoadAudio()
{
    alGenBuffers(BUFFERS, Buffers);

    LoadBuffer("sounds/attack.wav", ATT_SOUND);
    LoadBuffer("sounds/axe.wav", AXE_SOUND);
    LoadBuffer("sounds/bow.wav", BOW_SOUND);
    LoadBuffer("sounds/click.wav", CLICK_SOUND);
    LoadBuffer("sounds/die.wav", DIE_SOUND);
    LoadBuffer("sounds/die2.wav", DIE2_SOUND);
    LoadBuffer("sounds/hit.wav", HIT_SOUND);
    LoadBuffer("sounds/step.wav", STEP_SOUND);
    LoadBuffer("sounds/sword.wav", SWORD_SOUND);
    LoadBuffer("sounds/whip.wav", WHIP_SOUND);
    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;
    return AL_TRUE;
}

//------------------------------------------------------------------------------

ALboolean Audio::CreateSources()
{
    alGenSources(SOURCES, sources);
    Source(PLAY_CLICK, CLICK_SOUND, 1.0f, 0.3f, AL_FALSE);
    Source(PLAY_HIT, HIT_SOUND, 1.0f, 0.4f, AL_FALSE);
    Source(PLAY_ATT, ATT_SOUND, 1.0f, 0.5f, AL_FALSE);
    Source(PLAY_AXE, AXE_SOUND, 1.0f, 0.4f, AL_FALSE);
    Source(PLAY_DIE, DIE_SOUND, 1.0f, 0.4f, AL_FALSE);
    Source(PLAY_DIE2, DIE2_SOUND, 1.0f, 0.5f, AL_FALSE);
    Source(PLAY_STEP, STEP_SOUND, 1.0f, 0.4f, AL_TRUE);
    Source(PLAY_STEP2, STEP_SOUND, 1.33f, 0.4f, AL_TRUE);
    Source(PLAY_STEP3, STEP_SOUND, 1.67f, 0.4f, AL_TRUE);
    Source(PLAY_STEP4, STEP_SOUND, 2.0f, 0.4f, AL_TRUE);
    Source(PLAY_BOW, BOW_SOUND, 1.0f, 0.4f, AL_FALSE);
    Source(PLAY_SWORD, SWORD_SOUND, 1.0f, 0.4f, AL_FALSE);
    Source(PLAY_WHIP, WHIP_SOUND, 1.0f, 0.4f, AL_FALSE);

    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;
    return AL_TRUE;
}

//------------------------------------------------------------------------------

void Audio::Play(int sc)
{
    alSourcePlay(sources[sc]);
}

//------------------------------------------------------------------------------

void Audio::Stop(int sc)
{
    alSourceStop(sources[sc]);
}

//------------------------------------------------------------------------------

void Audio::Unload()
{
    alDeleteBuffers(BUFFERS, Buffers);
    alDeleteSources(SOURCES, sources);
    //exit OpenAL
    ALCcontext* pCurContext;
    ALCdevice* pCurDevice;
    pCurContext = alcGetCurrentContext();
    pCurDevice = alcGetContextsDevice(pCurContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(pCurContext);
    alcCloseDevice(pCurDevice);
}

//------------------------------------------------------------------------------

ALboolean Audio::Source(int ind, int buff, float pitch, float gain, ALboolean loop)
{
    alSourcei(sources[ind], AL_BUFFER, Buffers[buff]);
    alSourcef(sources[ind], AL_PITCH, pitch);
    alSourcef(sources[ind], AL_GAIN, gain);
    alSourcei(sources[ind], AL_LOOPING, loop);

    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;
    return AL_TRUE;
}
//------------------------------------------------------------------------------

ALboolean Audio::LoadBuffer(const char* fileName, int ind)
{

    unsigned char *data;
    uint32_t freq;
    uint32_t size;
    uint16_t format;
    FILE* file;
    uint16_t channels;
    uint16_t samplebits;
    file = fopen(fileName, "rb");
    if (file == NULL) return AL_FALSE;
    fseek(file, 22, SEEK_SET);
    fread(&channels, sizeof(channels), 1, file);
    fread(&freq, sizeof(freq), 1, file);
    fseek(file, 34, SEEK_SET);
    fread(&samplebits, sizeof(samplebits), 1, file);
    fseek(file, 40, SEEK_SET);
    fread(&size, sizeof(size), 1, file);
    //	reading data
    data = new unsigned char[size];
    fread(data, sizeof (char), size, file);

    if (channels == 2 && samplebits == 16) format = AL_FORMAT_STEREO16;
    if (channels == 2 && samplebits == 8) format = AL_FORMAT_STEREO8;
    if (channels == 1 && samplebits == 16) format = AL_FORMAT_MONO16;
    if (channels == 1 && samplebits == 8) format = AL_FORMAT_MONO8;

    alBufferData(Buffers[ind], format, data, size, freq);
    fclose(file);
    delete [] data;
    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;
    return AL_TRUE;
}
//------------------------------------------------------------------------------

