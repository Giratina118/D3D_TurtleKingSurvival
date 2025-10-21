#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include "_VertexData.h"
#include "_SaveLoadData.h"
#include <time.h>

class CEnemy;
class CBullet;
class Timer;

// 마우스 클릭
void MouseClickTitleScene(SHORT* mousePos);	// 타이틀씬 마우스 클릭
void MouseClickResultScene(SHORT* mousePos, CEnemy** enemyObj, CBullet** bullets, int* nowGameData, DateInfo* dateInfo); // 결과씬 마우스 클릭
void MouseClickGameScene(SHORT* mousePos, int* nowGameData, SaveData* saveData, DateInfo* dateInfo, tm* realTimeInfo, 
	SliderData* sliderInfo, BOOL* shotBullet, Timer* timer, CBullet** bullets); // 게임씬 마우스 클릭

// 마우스 이동
void MouseMoveTitleScene(SHORT* mousePos);	// 타이틀씬 마우스 이동
void MouseMoveResultScene(SHORT* mousePos);	// 결과씬 마우스 이동
void MouseMoveGameScene(HWND hWnd, SHORT* mousePos, SliderData* sliderInfo); // 게임씬 마우스 이동

// 여기부터 게임씬 세부 마우스 조작
void TurnOnOffCursor(BOOL turnOn); // 커서 on/off
void OnClickTimeAndMenuButton(SHORT* mousePos, BOOL* shotBullet, DateInfo* dateInfo); // 우상단 버튼 클릭
void MenuOnOff(); // 메뉴창 on/off 시키기

// 메뉴 내부 조작
void OnClickChangeFPS(SHORT* mousePos, Timer* timer); // fps 조절
void OnClickMenuSlider(int isOpenMenu, SHORT* mousePos, SliderData* sliderInfo);	// 메뉴 슬라이더 클릭
void OnDragMenuSlider(int isOpenMenu, SHORT* nowMousePosX, SliderData* sliderInfo);	// 메뉴 슬라이더 드래그
void SetSliderHorizontalInfo(SliderData* sliderInfo, int nowSliderNum, SHORT mousePosX, FLOAT startPosX, FLOAT endPosX); // horizontal 슬라이더 정보 저장(업데이트)
void SetSkyboxSize(SliderData* sliderInfo);											// 시야 거리 조작으로 스카이박스 크기 변경
void ToTitle(int* nowGameData, SaveData saveData[10], DateInfo dateInfo, tm* realTimeInfo);	// 타이틀로 이동

// 레벨업 카드 조작
void OnClickLevelupBonusCard(SHORT* mousePos);	// 레벨업 보너스 카드 선택
void ApplyLevelUpBonus(int selectCardNum);		// 레벨업 보너스 카드 적용

#endif