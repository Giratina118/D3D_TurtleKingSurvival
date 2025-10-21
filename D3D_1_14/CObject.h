#ifndef __COBJECT_H__
#define __COBJECT_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

enum ObjType
{
	OBJECT_NORMAL,
	OBJECT_CHARACTER,
	OBJECT_PLAYER,
	OBJECT_ENEMY,
	OBJECT_BULLET,

	OBJECT_MAX
};

class CObject
{
public:
	CObject();
	CObject(float radius, BOOL isCollision);
	CObject(D3DXMATRIX matrix, D3DXVECTOR3 length, float radius, BOOL isCollision);
	~CObject();

	D3DXMATRIX* GetMatrix() { return &m_matrix; }
	FLOAT GetRadius() { return m_radius; }
	BOOL GetIsCollision() { return m_canCollide; }
	D3DXVECTOR3 GetPos() { return { m_matrix._41, m_matrix._42, m_matrix._43 }; }
	D3DXVECTOR3 GetFront() { return { m_matrix._31, m_matrix._32, m_matrix._33 }; }
	D3DXVECTOR3 GetLength() { return m_length; }
	int GetObjType() { return m_objType; }
	FLOAT GetFallingSpeed() { return m_fallingSpeed; }
		
	void SetMatrix(D3DXMATRIX mtrix) { m_matrix = mtrix; }
	void SetRadius(FLOAT radius) { m_radius = radius; }
	void SetLength(D3DXVECTOR3 length) { m_length = length; }
	void SetFallingSpeed(FLOAT fallingSpeed) { m_fallingSpeed = fallingSpeed; }
	
	BOOL IsAABBCollision(CObject& other);	// 충돌 채크

protected:
	D3DXMATRIX m_matrix;	// 위치 행렬
	FLOAT m_radius;			// 반지름
	BOOL m_canCollide;		// 충돌 가능한 물체인지 여부
	D3DXVECTOR3 m_length;	// 물체의 xyz축 길이
	int m_objType;			// 물체 유형
	FLOAT m_fallingSpeed;	// 낙하 속도
};

#endif