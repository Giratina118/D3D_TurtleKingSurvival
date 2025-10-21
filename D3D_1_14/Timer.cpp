#include "Timer.h"

void Timer::Init(int fps)
{
    QueryPerformanceCounter(&lastCount); // ����� ƽ ��
    QueryPerformanceFrequency(&frequency); // �ʴ� Ÿ�̸Ӱ� �� ƽ�� ����ϴ���(���ļ�)
    SetFPS(fps);
}

BOOL Timer::Update()
{
	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);

    // �� �����ӿ��� ����� ƽ ��(���� ƽ�� ���� ƽ�� ��)�� ���ļ��� ���� �� �ʰ� ����ߴ��� üũ
	deltaTime = static_cast<float>(currentCount.QuadPart - 
        lastCount.QuadPart) / static_cast<float>(frequency.QuadPart);
	lastCount = currentCount;

    // fps�� ���߱� ���� deltaTime�� �������� ��ǥ fps�� �����.
    // ��ǥ fps�� daltaTimeStack���� ��������.
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

// �ð��� ���� �¾�(�𷺼ų� ����Ʈ)
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

// ��¥ ���� ������Ʈ
BOOL UpdateDateInfo(DateInfo* dateInfo, FLOAT* enemyCreateDelay, int* score)
{
    //int dayofMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // ���� �÷���Ÿ�� ������ ���� �� ���� 10�Ϸ� ����
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