#include "_SoundManager.h"
#include <iostream>

extern IXAudio2* pXAudio2;
extern IXAudio2MasteringVoice* pMasteringVoice;    // 마스터 보이스, 1개, 소스 보이스를 정리해서 출력
extern IXAudio2SourceVoice* pSourceVoice[10];      // bgm이나 효과음, 같은 효과음을 여러번 울리려면 그만큼 만들어야 한다
extern WaveData waveData[2];

// xAudio 초기화
void InitSound()
{
    // com 초기화
    HRESULT result;
    result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(result))
        return;

    // xaudio2 초기화
    result = XAudio2Create(&pXAudio2);
    if (FAILED(result))
        return;

    result = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
    if (FAILED(result))
        return;
}

// wave 파일 받기
bool LoadWaveFile(char* wFilePath, WaveData* outData)
{
    // wave 파일 전체가 하나의 범용 컨테이너인 RIFF 형태
    // wave 파일 포맷도 RIFF청크로 되어있다, 청크: 데이터 뭉치
    // fmt 청크: 음원 데이터에 대한 정보가 담겨있다
    // data 청크: 실제 음원 데이터가 담겨있다
    // 청크들은 식별자를 이용해 접근할 수 있다 ("WAVE", "fmt ", "data")


    // 내용물이 들어있는 것이 오면, 일단 해제한다
    // (그러지 않으면 원래 내용물의 사운드 버퍼가 있을 경우 메모리 누수됨)
    if (outData) free(outData->m_soundBuffer);
    else         return false;  // nullptr가 오면 리턴

    HMMIO mmioHandle = nullptr;
    MMCKINFO chunkInfo{};       // 청크 정보
    MMCKINFO riffChunkInfo{};   // RIFF 청크 정보

    mmioHandle = mmioOpen(wFilePath, nullptr, MMIO_READ); // WAV 파일 열기(멀티미디어 i/o파일 열기)
    if (!mmioHandle) return false; // Wav파일 열시 실패 시 종료


    // RIFF 청크에 접근하기 위해서 fccType에 wavw 설정
    riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E'); // .fccType: 어떤 종류의 데이터인지, mmioFOURCC: 4개 문자를 4문자 코드로 만들기
    if (mmioDescend(mmioHandle,	&riffChunkInfo,	nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) // RIFF 청크에 접근
    {   // mmioDescend: mmioOpen으로 연 RIFF 파일의 청크
        // MMIO 핸들, 청크 정보 취득, 부모 청크, 취득한 정보 종류
        mmioClose(mmioHandle, MMIO_FHOPEN); // Riff 청크 접근 실패 시 파일을 닫는다
        return false;
    }

    // 진입 청크를 fmt로 설정
    chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) // fmt 청크 접근
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // fmt 청크 접근 실패 시 파일을 닫는다
        return false;
    }

    // fmt 데이터 가져오기
    DWORD readSize = mmioRead(mmioHandle, (HPSTR)&outData->m_wavFormat, chunkInfo.cksize);
    if (readSize != chunkInfo.cksize)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // 버퍼 크기가 일치하지 않는 경우 파일을 닫는다
        return false;
    }

    // 포맷 체크
    if (outData->m_wavFormat.wFormatTag != WAVE_FORMAT_PCM)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // Wave 포맷 오류 시 파일을 닫는다
        return false;
    }

    // fmt 청크 탈출
    if (mmioAscend(mmioHandle, &chunkInfo, 0) != MMSYSERR_NOERROR)  // mmioAscend: 해당 청크를 빠져나온다.
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // fmt 청크 탈출 실패 시 파일을 닫는다
        return false;
    }

    // data 청크 접근
    chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // data 청크 접근 실패 시 파일을 닫는다
        return false;
    }
    
    outData->m_size = chunkInfo.cksize; // 크기 저장

    // data 청크 가져오기
    outData->m_soundBuffer = new char[chunkInfo.cksize];
    readSize = mmioRead(mmioHandle, (HPSTR)outData->m_soundBuffer, chunkInfo.cksize);
    if (readSize != chunkInfo.cksize)
    {
        mmioClose(mmioHandle, MMIO_FHOPEN); // data 청크 읽기 실패 시 파일을 닫는다.
        delete[] outData->m_soundBuffer;
        return false;
    }

    // 파일 닫기
    mmioClose(mmioHandle, MMIO_FHOPEN);

    return true;
}

// 재생 함수 생성
bool PlayWaveSound(char* fileName, WaveData* outData, bool loop, int soundNum)
{
    if (!LoadWaveFile(fileName, outData)) //Wave 파일 가져오기 실패 시 종료
        return false;

    WAVEFORMATEX waveFormat{};
    memcpy(&waveFormat, &outData->m_wavFormat, sizeof(outData->m_wavFormat)); // 음악 포맷 설정

    // 샘플 당 버퍼 크기 산출
    waveFormat.wBitsPerSample = outData->m_wavFormat.nBlockAlign * 8 / outData->m_wavFormat.nChannels;

    // SourceVoice 생성
    HRESULT result = pXAudio2->CreateSourceVoice(&pSourceVoice[soundNum], (WAVEFORMATEX*)&waveFormat);
    if (FAILED(result)) // SourceVoice 생성 실패 시 파일을 닫는다.
        return false;

    // 음악 데이터를 SourceVoice에 넘긴다
    XAUDIO2_BUFFER xAudio2Buffer{};
    xAudio2Buffer.pAudioData = (BYTE*)outData->m_soundBuffer;
    xAudio2Buffer.Flags = XAUDIO2_END_OF_STREAM;
    xAudio2Buffer.AudioBytes = outData->m_size;
    xAudio2Buffer.LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0; // 루프 할지 말지 결정
    pSourceVoice[soundNum]->SubmitSourceBuffer(&xAudio2Buffer);

    pSourceVoice[soundNum]->Start(0); // SourceVoice 실행
    return true;
}

// 소리 재생
void SoundPlay(char* soundFilePath, float volumeSize, int soundNum)
{
    // 소리 재생 함수가 성공적으로 음원을 로드하고 재생할 수 있는지 확인
    if (PlayWaveSound(soundFilePath, &waveData[soundNum], !soundNum, soundNum))
    {
        pSourceVoice[soundNum]->SetVolume(volumeSize);  // 소리 볼륨 설정

        bool isRunning = true;  // 음원이 실행 중인지 확인

        XAUDIO2_VOICE_STATE state;                  // 음원의 상태를 확인하는 변수
        pSourceVoice[soundNum]->GetState(&state);   // 소스 보이스 상태 확인

        // 음원 재생이 끝났으면 보이스를 정리하고 멈춤
        if (state.BuffersQueued == 0)
        {
            pSourceVoice[soundNum]->Stop(0);        // 보이스 멈추기
            pSourceVoice[soundNum]->DestroyVoice(); // 보이스 해제
        }
    }
}

// 볼륨 조절
void SetVolume(float volumeSize, int soundNum)
{
    if (pSourceVoice[soundNum] != NULL)
        pSourceVoice[soundNum]->SetVolume(volumeSize);
}