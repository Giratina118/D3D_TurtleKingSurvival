#include "_SaveLoadData.h"
#include <iostream>
#pragma warning(disable : 4996)

// 파일 저장하기
void SaveFile(int fps, SaveData saveData[10], SliderData sliderInfo[SLIDER_MAX])
{
    FILE* fout;
    fout = fopen("Save\\saveData.bin", "wb");
    fprintf(fout, "%d %f %f %f %f %f ", fps, sliderInfo[0].value, sliderInfo[1].value, sliderInfo[2].value, sliderInfo[3].value, sliderInfo[4].value);
    for (int i = 0; i < 10; i++)
        fprintf(fout, "%d %d %d %d %d %d %d %d %d ", saveData[i].score, saveData[i].killCount, saveData[i].aliveTime[0], 
            saveData[i].aliveTime[1], saveData[i].realTime[0], saveData[i].realTime[1], saveData[i].realTime[2], saveData[i].realTime[3], saveData[i].realTime[4]);
    fclose(fout);
}

// 파일 불러오기
void LoadFile(int* fps, int* bestScore, SaveData saveData[10], SliderData sliderInfo[SLIDER_MAX])
{
    FILE* fin;
    fin = fopen("Save\\saveData.bin", "rb");
    if (fin != NULL)	// 저장된 파일이 있을 경우
    {
        fscanf_s(fin, "%d %f %f %f %f %f ", fps, &sliderInfo[0].value, &sliderInfo[1].value, &sliderInfo[2].value, &sliderInfo[3].value, &sliderInfo[4].value);
        for (int i = 0; i < 10; i++)
            fscanf_s(fin, "%d %d %d %d %d %d %d %d %d ", &saveData[i].score, &saveData[i].killCount, &saveData[i].aliveTime[0], &saveData[i].aliveTime[1], 
                &saveData[i].realTime[0], &saveData[i].realTime[1], &saveData[i].realTime[2], &saveData[i].realTime[3], &saveData[i].realTime[4]);
        *bestScore = saveData[0].score;
        fclose(fin);
    }
    else                // 저장된 파일이 없을 경우
    {
        *bestScore = 0;
        sliderInfo[0].value = sliderInfo[1].value = sliderInfo[2].value = 0.5f;
        for (int i = 0; i < 10; i++)
            saveData[i] = { 0, 0, {0, 0}, {0, 0, 0, 0, 0} };
    }
}