#ifndef __SAVELOADDATA_H__
#define __SAVELOADDATA_H__

#include "_DefineData.h"

// ���� ���
struct SaveData
{
    int score;          // ����
    int killCount;      // ų ī��Ʈ
    int aliveTime[2];   // ���� �ð�(���� �� �ð� ����)
    int realTime[5];    // ���� ��� �ð�(���� �ð� ����) (��, ��, ��, ��, ��)
};

void SaveFile(int fps, SaveData saveData[10], SliderData sliderInfo[SLIDER_MAX]);                    // ���� �����ϱ�
void LoadFile(int* fps, int* bestScore, SaveData saveData[10], SliderData sliderInfo[SLIDER_MAX]);   // ���� �ҷ�����

#endif