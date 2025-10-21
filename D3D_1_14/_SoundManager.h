#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include<xaudio2.h>
#include<mmsystem.h>
#include <string>
#pragma comment(lib,"Xaudio2.lib")
#pragma comment (lib, "winmm.lib")

// wave 구조체
struct WaveData
{
    WAVEFORMATEX m_wavFormat;
    char* m_soundBuffer;
    DWORD m_size;

    ~WaveData() { free(m_soundBuffer); }
};

void InitSound();    // xAudio 초기화
bool LoadWaveFile(char* wFilePath, WaveData* outData);              // wave 파일 받기
bool PlayWaveSound(char* fileName, WaveData* outData, bool loop, int soundNum); // 재생 함수 생성
void SoundPlay(char* soundFilePath, float volume, int soundNum);    // 소리 재생
void SetVolume(float volumeSize, int soundNum); // 볼륨 조절

#endif