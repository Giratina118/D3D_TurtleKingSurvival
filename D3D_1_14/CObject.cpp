#include "CObject.h"
#include "_DefineData.h"

CObject::CObject()
{
	D3DXMatrixIdentity(&m_matrix);
	m_radius = 0;
	m_canCollide = FALSE;
	m_objType = OBJECT_NORMAL;
	m_fallingSpeed = GRAVITY_ACCELERATION;
}

CObject::CObject(float radius, BOOL isCollision)
{
	D3DXMatrixIdentity(&m_matrix);
	m_radius = radius;
	m_canCollide = isCollision;
	m_objType = OBJECT_NORMAL;
	m_fallingSpeed = GRAVITY_ACCELERATION;
}

CObject::CObject(D3DXMATRIX matrix, D3DXVECTOR3 length, float radius, BOOL isCollision)
{
	m_matrix = matrix;
	m_length = length;
	m_radius = radius;
	m_canCollide = isCollision;
	m_objType = OBJECT_NORMAL;
	m_fallingSpeed = GRAVITY_ACCELERATION;
}

CObject::~CObject()
{

}

// 충돌 체크
BOOL CObject::IsAABBCollision(CObject& other)
{
	D3DXVECTOR3 thisPos = GetPos();
	D3DXVECTOR3 otherPos = other.GetPos();

	D3DXVECTOR3 thisLength = GetLength() * 0.5f;
	D3DXVECTOR3 otherLength = other.GetLength() * 0.5f;

	if (fabs(thisPos.x - otherPos.x) > (thisLength.x + otherLength.x)) return false;
	if (fabs(thisPos.y - otherPos.y) > (thisLength.y + otherLength.y)) return false;
	if (fabs(thisPos.z - otherPos.z) > (thisLength.z + otherLength.z)) return false;

	return true;
}