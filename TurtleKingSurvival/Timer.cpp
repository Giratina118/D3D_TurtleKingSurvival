#include "Timer.h"

void Timer::Init(int fps)
{
    QueryPerformanceCounter(&lastCount); // 경과된 틱 수
    QueryPerformanceFrequency(&frequency); // 초당 타이머가 몇 틱을 기록하는지(주파수)
    SetFPS(fps);
}

BOOL Timer::Update()
{
	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);

    // 한 프레임에서 경과된 틱 수(이전 틱과 현재 틱의 차)를 주파수로 나눠 몇 초가 경과했는지 체크
	deltaTime = static_cast<float>(currentCount.QuadPart - 
        lastCount.QuadPart) / static_cast<float>(frequency.QuadPart);
	lastCount = currentCount;

    // fps를 맞추기 위해 deltaTime을 누적시켜 목표 fps를 맞춘다.
    // 목표 fps는 daltaTimeStack에서 맞춰진다.
    if (deltaTimeStack > secondsPerFrame)   deltaTimeStack = 0.0f;
    deltaTimeStack += deltaTime;

    if (deltaTimeStack < secondsPerFrame)   return FALSE;
    else                                    return TRUE;
}

void Timer::SetFPS(int fps)
{
    framesPerSecond = fps;
    secondsPerFrame = 1.0f / fps;
}

// 시간에 따른 태양(디렉셔널 라이트)
void UpdateSunPosition(DateInfo* dateInfo)
{
    float sunHeight = fabs(6.5f - dateInfo->month);

    FLOAT sunX = -sin(dateInfo->clock * (PI / 180.0f) * 15.0f);
    FLOAT sunY = cos(dateInfo->clock * (PI / 180.0f) * 15.0f) - (8.0f - sunHeight) / 10.0f;
    FLOAT sunZ = cos(dateInfo->clock * (PI / 180.0f) * 15.0f) * sunHeight / 7.0f;

    dateInfo->sunDirection.x = sunX;
    dateInfo->sunDirection.y = sunY;
    dateInfo->sunDirection.z = sunZ;
}

// 날짜 정보 업데이트
BOOL UpdateDateInfo(DateInfo* dateInfo, FLOAT* enemyCreateDelay, int* score)
{
    //int dayofMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // 게임 플레이타임 조절을 위해 한 달을 10일로 설정
    if (dateInfo->clock > 24.0f)
    {
        *score += 200 * dateInfo->month + 20 * dateInfo->day;
        *enemyCreateDelay -= 0.1f;
        dateInfo->clock -= 24.0f;
        dateInfo->day++;
    }
    if (dateInfo->day > 10 /*dayofMonth[dateInfo->month]*/ )
    {
        *score += 500 * dateInfo->month;
        *enemyCreateDelay *= 5.0f * powf(0.9f, dateInfo->month);
        dateInfo->day = 1;
        dateInfo->month++;
    }
    if (dateInfo->month > 12)
    {
        *score += 10000;
        dateInfo->month = 1;
        return TRUE;
    }
    return FALSE;
}