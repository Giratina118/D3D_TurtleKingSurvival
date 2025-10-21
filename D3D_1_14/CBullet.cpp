#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "_TransformMatrix.h"

CBullet::CBullet()
{
	m_radius = 0.0f;
	m_canCollide = TRUE;
	m_length = { 0.2f, 0.2f, 0.2f };
	m_objType = OBJECT_BULLET;

	m_speed = 0.01f;
	m_mesh = 0;
	m_lifeTime = 3.0f;
	m_damage = 20;
	m_shooter = 0;
}

CBullet::CBullet(D3DXMATRIX matrix, D3DXVECTOR3 muzzle, D3DXVECTOR3 dir, int size, FLOAT bulletSpeed, int damage, int shooter)
{
	D3DXMatrixIdentity(&m_matrix);
	D3DXMatrixScaling(&m_matrix, 1.0f * size, 1.0f * size, 1.0f * size);
	m_matrix._41 = matrix._41;
	m_matrix._42 = matrix._42 + muzzle.y;
	m_matrix._43 = matrix._43;

	m_radius = 0.1f * size;
	m_canCollide = TRUE;
	m_length = { m_radius * 2.0f, m_radius * 2.0f, m_radius * 2.0f };
	m_objType = OBJECT_BULLET;

	m_speed = bulletSpeed;
	m_direction = dir;
	m_mesh = 0;
	m_lifeTime = 3.0f;
	m_damage = damage;
	m_shooter = shooter;
	CSprite fire = { spriteVertices, m_matrix, 0.3f, 20, FALSE };
	m_fire = fire;
}

CBullet::~CBullet()
{
	if (m_mesh != NULL)
		m_mesh->Release();
}

BOOL CBullet::IsLifeTimeOver()
{
	if (m_lifeTime < 0.0f)	return TRUE;
	else					return FALSE;
}

// 총알 업데이트 (이동, 충돌체크, 데미지, 소멸)
void CBullet::UpdateBulletState(Timer timer)
{
	if (!m_fire.GetIsPlaySprite())
	{
		// 이동
		FLOAT bulletSpeed = m_speed * timer.GetDeltaTime();
		D3DXMATRIX transformMatrix;
		D3DXMatrixTranslation(&transformMatrix, m_direction.x * bulletSpeed, m_direction.y * bulletSpeed, m_direction.z * bulletSpeed);
		D3DXMatrixMultiply(&m_matrix, &m_matrix, &transformMatrix);

		// 접촉 체크
		FLOAT gravityMoveDown = 0.0f;
		CObject* collisionObj = CollisionCheckIndex(this, *this, -1, &gravityMoveDown);

		if (collisionObj != NULL)	// 접촉 시 데미지
		{
			m_fire.SetPlaySprite(); // 불꽃 스프라이트 재생
			m_canCollide = FALSE;
			if (collisionObj->GetObjType() == OBJECT_ENEMY && m_shooter != OBJECT_ENEMY) // 총알과 적 접촉 시 데미지
				static_cast<CEnemy*>(collisionObj)->TakeDamage(m_damage);
			else if (collisionObj->GetObjType() == OBJECT_PLAYER && m_shooter != OBJECT_PLAYER) // 총알과 플레이어 접촉 시 데미지
				static_cast<CPlayer*>(collisionObj)->TakeDamage(m_damage);
		}

		m_lifeTime -= timer.GetDeltaTime();
	}
	else // 불꽃 스프라이트 재생
	{
		m_fire.UpdateSprite(timer);
		if (!m_fire.GetIsPlaySprite())
			m_lifeTime = -1.0f;
	}
}