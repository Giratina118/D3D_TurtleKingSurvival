#ifndef __UPDATEGAMEPROC_H__
#define __UPDATEGAMEPROC_H__

#include "Timer.h"

class CPlayer;
class CEnemy;
class CBullet;

void FlowTime(SceneState* sceneState, DateInfo* dateInfo, Timer timer, int* score, CPlayer* playerObj); // �ð� �帧
void CreateBullet(CBullet* bullets[BULLET_MAX], D3DXMATRIX matrix, D3DXVECTOR3 bulletPos, D3DXVECTOR3 bulletDir, int bulletSizeLevel, int bulletDamage, int shooter); // �Ѿ� ����
void UpdateBulletProc(CBullet** bullets, Timer timer); // �Ѿ� ������Ʈ
void CreateEnemy(CEnemy** enemyObj, DateInfo dateInfo, int* nowGameData, int killCountTemp); // �� ����
void UpdateEnemyProc(CEnemy** enemyObj, CPlayer* playerObj, CBullet** bullets, Timer timer, SceneState* sceneState, int* nowGameData, DateInfo dateInfo); // �� ������Ʈ

void __KeyProc(Timer timer, CPlayer* playerObj); // Ű �Է�
void ClickShortCutKey(HWND hWnd, WPARAM wParam, SceneState* sceneState, CPlayer* playerObj); // ����Ű
void CameraTransform(SHORT* mousePos, FLOAT mouseSensivity, CPlayer* playerObj); // ���콺�� ���� �̵�

#endif