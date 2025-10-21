#ifndef __SAVELOADDATA_H__
#define __SAVELOADDATA_H__

#include "_DefineData.h"

// 점수 기록
struct SaveData
{
    int score;          // 점수
    int killCount;      // 킬 카운트
    int aliveTime[2];   // 생존 시간(게임 내 시간 기준)
    int realTime[5];    // 점수 기록 시간(현실 시간 기준) (년, 월, 일, 시, 분)
};

void SaveFile(int fps, SaveData saveData[10], SliderData sliderInfo[SLIDER_MAX]);                    // 파일 저장하기
void LoadFile(int* fps, int* bestScore, SaveData saveData[10], SliderData sliderInfo[SLIDER_MAX]);   // 파일 불러오기

#endif