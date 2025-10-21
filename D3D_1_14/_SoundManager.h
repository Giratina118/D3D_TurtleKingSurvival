#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include<xaudio2.h>
#include<mmsystem.h>
#include <string>
#pragma comment(lib,"Xaudio2.lib")
#pragma comment (lib, "winmm.lib")

// wave ����ü
struct WaveData
{
    WAVEFORMATEX m_wavFormat;
    char* m_soundBuffer;
    DWORD m_size;

    ~WaveData() { free(m_soundBuffer); }
};

void InitSound();    // xAudio �ʱ�ȭ
bool LoadWaveFile(char* wFilePath, WaveData* outData);              // wave ���� �ޱ�
bool PlayWaveSound(char* fileName, WaveData* outData, bool loop, int soundNum); // ��� �Լ� ����
void SoundPlay(char* soundFilePath, float volume, int soundNum);    // �Ҹ� ���
void SetVolume(float volumeSize, int soundNum); // ���� ����

#endif