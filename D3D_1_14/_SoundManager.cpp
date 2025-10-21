#include "_SoundManager.h"
#include <iostream>

extern IXAudio2* pXAudio2;
extern IXAudio2MasteringVoice* pMasteringVoice;    // ������ ���̽�, 1��, �ҽ� ���̽��� �����ؼ� ���
extern IXAudio2SourceVoice* pSourceVoice[10];      // bgm�̳� ȿ����, ���� ȿ������ ������ �︮���� �׸�ŭ ������ �Ѵ�
extern WaveData waveData[2];

// xAudio �ʱ�ȭ
void InitSound()
{
    // com �ʱ�ȭ
    HRESULT result;
    result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(result))
        return;

    // xaudio2 �ʱ�ȭ
    result = XAudio2Create(&pXAudio2);
    if (FAILED(result))
        return;

    result = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
    if (FAILED(result))
        return;
}

// wave ���� �ޱ�
bool LoadWaveFile(char* wFilePath, WaveData* outData)
{
    // wave ���� ��ü�� �ϳ��� ���� �����̳��� RIFF ����
    // wave ���� ���˵� RIFFûũ�� �Ǿ��ִ�, ûũ: ������ ��ġ
    // fmt ûũ: ���� �����Ϳ� ���� ������ ����ִ�
    // data ûũ: ���� ���� �����Ͱ� ����ִ�
    // ûũ���� �ĺ��ڸ� �̿��� ������ �� �ִ� ("WAVE", "fmt ", "data")


    // ���빰�� ����ִ� ���� ����, �ϴ� �����Ѵ�
    // (�׷��� ������ ���� ���빰�� ���� ���۰� ���� ��� �޸� ������)
    if (outData) free(outData->m_soundBuffer);
    else         return false;  // nullptr�� ���� ����

    HMMIO mmioHandle = nullptr;
    MMCKINFO chunkInfo{};       // ûũ ����
    MMCKINFO riffChunkInfo{};   // RIFF ûũ ����

    mmioHandle = mmioOpen(wFilePath, nullptr, MMIO_READ); // WAV ���� ����(��Ƽ�̵�� i/o���� ����)
    if (!mmioHandle) return false; // Wav���� ���� ���� �� ����


    // RIFF ûũ�� �����ϱ� ���ؼ� fccType�� wavw ����
    riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E'); // .fccType: � ������ ����������, mmioFOURCC: 4�� ���ڸ� 4���� �ڵ�� �����
    if (mmioDescend(mmioHandle,	&riffChunkInfo,	nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) // RIFF ûũ�� ����
    {   // mmioDescend: mmioOpen���� �� RIFF ������ ûũ
        // MMIO �ڵ�, ûũ ���� ���, �θ� ûũ, ����� ���� ����
        mmioClose(mmioHandle, MMIO_FHOPEN); // Riff ûũ ���� ���� �� ������ �ݴ´�
        return false;
    }

    // ���� ûũ�� fmt�� ����
    chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) // fmt ûũ ����
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // fmt ûũ ���� ���� �� ������ �ݴ´�
        return false;
    }

    // fmt ������ ��������
    DWORD readSize = mmioRead(mmioHandle, (HPSTR)&outData->m_wavFormat, chunkInfo.cksize);
    if (readSize != chunkInfo.cksize)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // ���� ũ�Ⱑ ��ġ���� �ʴ� ��� ������ �ݴ´�
        return false;
    }

    // ���� üũ
    if (outData->m_wavFormat.wFormatTag != WAVE_FORMAT_PCM)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // Wave ���� ���� �� ������ �ݴ´�
        return false;
    }

    // fmt ûũ Ż��
    if (mmioAscend(mmioHandle, &chunkInfo, 0) != MMSYSERR_NOERROR)  // mmioAscend: �ش� ûũ�� �������´�.
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // fmt ûũ Ż�� ���� �� ������ �ݴ´�
        return false;
    }

    // data ûũ ����
    chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // data ûũ ���� ���� �� ������ �ݴ´�
        return false;
    }
    
    outData->m_size = chunkInfo.cksize; // ũ�� ����

    // data ûũ ��������
    outData->m_soundBuffer = new char[chunkInfo.cksize];
    readSize = mmioRead(mmioHandle, (HPSTR)outData->m_soundBuffer, chunkInfo.cksize);
    if (readSize != chunkInfo.cksize)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // data ûũ �б� ���� �� ������ �ݴ´�.
        delete[] outData->m_soundBuffer;
        return false;
    }

    // ���� �ݱ�
    mmioClose(mmioHandle, MMIO_FHOPEN);

    return true;
}

// ��� �Լ� ����
bool PlayWaveSound(char* fileName, WaveData* outData, bool loop, int soundNum)
{
    if (!LoadWaveFile(fileName, outData)) //Wave ���� �������� ���� �� ����
        return false;

    WAVEFORMATEX waveFormat{};
    memcpy(&waveFormat, &outData->m_wavFormat, sizeof(outData->m_wavFormat)); // ���� ���� ����

    // ���� �� ���� ũ�� ����
    waveFormat.wBitsPerSample = outData->m_wavFormat.nBlockAlign * 8 / outData->m_wavFormat.nChannels;

    // SourceVoice ����
    HRESULT result = pXAudio2->CreateSourceVoice(&pSourceVoice[soundNum], (WAVEFORMATEX*)&waveFormat);
    if (FAILED(result)) // SourceVoice ���� ���� �� ������ �ݴ´�.
        return false;

    // ���� �����͸� SourceVoice�� �ѱ��
    XAUDIO2_BUFFER xAudio2Buffer{};
    xAudio2Buffer.pAudioData = (BYTE*)outData->m_soundBuffer;
    xAudio2Buffer.Flags = XAUDIO2_END_OF_STREAM;
    xAudio2Buffer.AudioBytes = outData->m_size;
    xAudio2Buffer.LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0; // ���� ���� ���� ����
    pSourceVoice[soundNum]->SubmitSourceBuffer(&xAudio2Buffer);

    pSourceVoice[soundNum]->Start(0); // SourceVoice ����
    return true;
}

// �Ҹ� ���
void SoundPlay(char* soundFilePath, float volumeSize, int soundNum)
{
    // �Ҹ� ��� �Լ��� ���������� ������ �ε��ϰ� ����� �� �ִ��� Ȯ��
    if (PlayWaveSound(soundFilePath, &waveData[soundNum], !soundNum, soundNum))
    {
        pSourceVoice[soundNum]->SetVolume(volumeSize);  // �Ҹ� ���� ����

        bool isRunning = true;  // ������ ���� ������ Ȯ��

        XAUDIO2_VOICE_STATE state;                  // ������ ���¸� Ȯ���ϴ� ����
        pSourceVoice[soundNum]->GetState(&state);   // �ҽ� ���̽� ���� Ȯ��

        // ���� ����� �������� ���̽��� �����ϰ� ����
        if (state.BuffersQueued == 0)
        {
            pSourceVoice[soundNum]->Stop(0);        // ���̽� ���߱�
            pSourceVoice[soundNum]->DestroyVoice(); // ���̽� ����
        }
    }
}

// ���� ����
void SetVolume(float volumeSize, int soundNum)
{
    if (pSourceVoice[soundNum] != NULL)
        pSourceVoice[soundNum]->SetVolume(volumeSize);
}