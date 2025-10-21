#ifndef __UPDATEGAMEPROC_H__
#define __UPDATEGAMEPROC_H__

#include "Timer.h"

class CPlayer;
class CEnemy;
class CBullet;

void FlowTime(SceneState* sceneState, DateInfo* dateInfo, Timer timer, int* score, CPlayer* playerObj); // 시간 흐름
void CreateBullet(CBullet* bullets[BULLET_MAX], D3DXMATRIX matrix, D3DXVECTOR3 bulletPos, D3DXVECTOR3 bulletDir, int bulletSizeLevel, int bulletDamage, int shooter); // 총알 생성
void UpdateBulletProc(CBullet** bullets, Timer timer); // 총알 업데이트
void CreateEnemy(CEnemy** enemyObj, DateInfo dateInfo, int* nowGameData, int killCountTemp); // 적 생성
void UpdateEnemyProc(CEnemy** enemyObj, CPlayer* playerObj, CBullet** bullets, Timer timer, SceneState* sceneState, int* nowGameData, DateInfo dateInfo); // 적 업데이트

void __KeyProc(Timer timer, CPlayer* playerObj); // 키 입력
void ClickShortCutKey(HWND hWnd, WPARAM wParam, SceneState* sceneState, CPlayer* playerObj); // 단축키
void CameraTransform(SHORT* mousePos, FLOAT mouseSensivity, CPlayer* playerObj); // 마우스로 시점 이동

#endif