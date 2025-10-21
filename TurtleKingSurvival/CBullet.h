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

	BOOL IsLifeTimeOver();					// �����ð� �� �Ǹ� ��� ó��
	void UpdateBulletState(Timer timer);	// �Ѿ� ������Ʈ (�̵�, �浹üũ, ������, �Ҹ�)

private:
	FLOAT m_speed;				// �Ѿ� �ӵ�
	D3DXVECTOR3 m_direction;	// �Ѿ� ����
	ID3DXMesh* m_mesh;			// �Ѿ� �޽�
	FLOAT m_lifeTime;			// �Ѿ� ���� �ð�
	int m_damage;				// �Ѿ� ������
	int m_shooter;				// �Ѿ� ��� ��ü ���� 
	CSprite m_fire;				// �Ҳ� ȿ��
};

#endif