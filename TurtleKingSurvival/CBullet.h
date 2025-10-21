#ifndef __CBULLET_H__
#define __CBULLET_H__

#include "CObject.h"
#include "CSprite.h"

class CBullet : public CObject
{
public:
	CBullet();
	CBullet(D3DXMATRIX matrix, D3DXVECTOR3 pos, D3DXVECTOR3 dir, int size, FLOAT bulletSpeed, int damage, int shooter);
	~CBullet();

	ID3DXMesh** GetMesh() { return &m_mesh; }
	CSprite GetFireSprite() { return m_fire; }
	int GetShooterType() { return m_shooter; }
	void SetLifeTimeOver() { m_lifeTime = 0.0f; }

	BOOL IsLifeTimeOver();					// 생존시간 다 되면 사망 처리
	void UpdateBulletState(Timer timer);	// 총알 업데이트 (이동, 충돌체크, 데미지, 소멸)

private:
	FLOAT m_speed;				// 총알 속도
	D3DXVECTOR3 m_direction;	// 총알 방향
	ID3DXMesh* m_mesh;			// 총알 메쉬
	FLOAT m_lifeTime;			// 총알 생존 시간
	int m_damage;				// 총알 데미지
	int m_shooter;				// 총알 쏘는 객체 유형 
	CSprite m_fire;				// 불꽃 효과
};

#endif