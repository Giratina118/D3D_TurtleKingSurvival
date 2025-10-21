#ifndef __TIMER_H__
#define __TIMER_H__

#include "_DefineData.h"

class Timer
{
public:
	void Init(int fps);
	BOOL Update();

	float GetDeltaTime() { return deltaTimeStack; }
	int GetFPS() { return framesPerSecond; }
	void SetFPS(int fps);

private:
	LARGE_INTEGER frequency; // �ʴ� Ÿ�̸Ӱ� �� ƽ�� ����ϴ���(���ļ�)
	LARGE_INTEGER lastCount; // ����� ƽ ��

	float deltaTime;
	float deltaTimeStack;
	int framesPerSecond;
	float secondsPerFrame;
};

void UpdateSunPosition(DateInfo* dateInfo);										// �¾�(�𷺼ų� ����Ʈ) ���� ������Ʈ
BOOL UpdateDateInfo(DateInfo* dateInfo, FLOAT* enemyCreateDelay, int* score);	// ��¥ ���� ������Ʈ

#endif