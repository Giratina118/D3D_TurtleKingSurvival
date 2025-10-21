#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include "_VertexData.h"
#include "_SaveLoadData.h"
#include <time.h>

class CEnemy;
class CBullet;
class Timer;

// ���콺 Ŭ��
void MouseClickTitleScene(SHORT* mousePos);	// Ÿ��Ʋ�� ���콺 Ŭ��
void MouseClickResultScene(SHORT* mousePos, CEnemy** enemyObj, CBullet** bullets, int* nowGameData, DateInfo* dateInfo); // ����� ���콺 Ŭ��
void MouseClickGameScene(SHORT* mousePos, int* nowGameData, SaveData* saveData, DateInfo* dateInfo, tm* realTimeInfo, 
	SliderData* sliderInfo, BOOL* shotBullet, Timer* timer, CBullet** bullets); // ���Ӿ� ���콺 Ŭ��

// ���콺 �̵�
void MouseMoveTitleScene(SHORT* mousePos);	// Ÿ��Ʋ�� ���콺 �̵�
void MouseMoveResultScene(SHORT* mousePos);	// ����� ���콺 �̵�
void MouseMoveGameScene(HWND hWnd, SHORT* mousePos, SliderData* sliderInfo); // ���Ӿ� ���콺 �̵�

// ������� ���Ӿ� ���� ���콺 ����
void TurnOnOffCursor(BOOL turnOn); // Ŀ�� on/off
void OnClickTimeAndMenuButton(SHORT* mousePos, BOOL* shotBullet, DateInfo* dateInfo); // ���� ��ư Ŭ��
void MenuOnOff(); // �޴�â on/off ��Ű��

// �޴� ���� ����
void OnClickChangeFPS(SHORT* mousePos, Timer* timer); // fps ����
void OnClickMenuSlider(int isOpenMenu, SHORT* mousePos, SliderData* sliderInfo);	// �޴� �����̴� Ŭ��
void OnDragMenuSlider(int isOpenMenu, SHORT* nowMousePosX, SliderData* sliderInfo);	// �޴� �����̴� �巡��
void SetSliderHorizontalInfo(SliderData* sliderInfo, int nowSliderNum, SHORT mousePosX, FLOAT startPosX, FLOAT endPosX); // horizontal �����̴� ���� ����(������Ʈ)
void SetSkyboxSize(SliderData* sliderInfo);											// �þ� �Ÿ� �������� ��ī�̹ڽ� ũ�� ����
void ToTitle(int* nowGameData, SaveData saveData[10], DateInfo dateInfo, tm* realTimeInfo);	// Ÿ��Ʋ�� �̵�

// ������ ī�� ����
void OnClickLevelupBonusCard(SHORT* mousePos);	// ������ ���ʽ� ī�� ����
void ApplyLevelUpBonus(int selectCardNum);		// ������ ���ʽ� ī�� ����

#endif