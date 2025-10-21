#ifndef __TRANSFORMMATRIX_H__
#define __TRANSFORMMATRIX_H__

#include "_DefineData.h"
#include "CObject.h"

class CPlayer;
class CEnemy;
class CBullet;

BOOL TranslateObject(CObject* object, int moveDir, float moveSpeed);				// 이동(접촉 체크)
D3DXMATRIX GetTransformMatrix(D3DXMATRIX* object, int moveDir, float moveSpeed);	// 이동 방향
CObject* CollisionCheckIndex(CObject* object, CObject nextObj, int xyz, FLOAT* gravityMoveDown);										// 충돌 체크 묶음
CObject* CollisionCheck(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown);	// 충돌 체크 (여러개)
CObject* CollisionCheckOne(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown);	// 충돌 체크 (단일)

void RotationObject(D3DXMATRIX* object, int xyz, float rotSpeed, BOOL isPlayer);	// 회전
void RotationLookAt(CObject* object, D3DXVECTOR3 targetPos);						// 회전 (특정 타깃 방향으로)
void _JumpProcess(CObject* object);						// 점프
void _Gravity(CPlayer* object, CEnemy** enemyObj);		// 중력

#endif