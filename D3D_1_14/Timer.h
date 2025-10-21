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
	LARGE_INTEGER frequency; // 초당 타이머가 몇 틱을 기록하는지(주파수)
	LARGE_INTEGER lastCount; // 경과된 틱 수

	float deltaTime;
	float deltaTimeStack;
	int framesPerSecond;
	float secondsPerFrame;
};

void UpdateSunPosition(DateInfo* dateInfo);										// 태양(디렉셔널 라이트) 정보 업데이트
BOOL UpdateDateInfo(DateInfo* dateInfo, FLOAT* enemyCreateDelay, int* score);	// 날짜 정보 업데이트

#endif