#ifndef __TRANSFORMMATRIX_H__
#define __TRANSFORMMATRIX_H__

#include "_DefineData.h"
#include "CObject.h"

class CPlayer;
class CEnemy;
class CBullet;

BOOL TranslateObject(CObject* object, int moveDir, float moveSpeed);				// �̵�(���� üũ)
D3DXMATRIX GetTransformMatrix(D3DXMATRIX* object, int moveDir, float moveSpeed);	// �̵� ����
CObject* CollisionCheckIndex(CObject* object, CObject nextObj, int xyz, FLOAT* gravityMoveDown);										// �浹 üũ ����
CObject* CollisionCheck(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown);	// �浹 üũ (������)
CObject* CollisionCheckOne(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown);	// �浹 üũ (����)

void RotationObject(D3DXMATRIX* object, int xyz, float rotSpeed, BOOL isPlayer);	// ȸ��
void RotationLookAt(CObject* object, D3DXVECTOR3 targetPos);						// ȸ�� (Ư�� Ÿ�� ��������)
void _JumpProcess(CObject* object);						// ����
void _Gravity(CPlayer* object, CEnemy** enemyObj);		// �߷�

#endif