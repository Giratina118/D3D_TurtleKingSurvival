#ifndef __CENEMY_H__
#define __CENEMY_H__

#include "CCharacter.h"
#include "Timer.h"

class CPlayer;
class CBullet;

enum EnemyType
{
	ENEMY_TYPE1,
	ENEMY_TYPE2,
	ENEMY_TYPE3,

	ENEMY_TYPE_MAX
};

class CEnemy : public CCharacter
{
public:
	CEnemy();
	CEnemy(int enemyType, DateInfo dateInfo);
	~CEnemy();

	void SettingCEnmyCommonInfo();
	D3DXMATRIX GetHpBarMatrix();
	int GetEXP() { return m_canGetExp; }
	BOOL GetAlive() { return m_alive; }
	int GetEnemyType() { return m_enemyType; }

	void Attack(Timer timer, CPlayer* player, CBullet** bullets, DateInfo dateInfo);		// ����
	void Move(Timer timer, CPlayer* player, DateInfo dateInfo);								// �̵�
	void UpdateEnemy(Timer timer, CPlayer* player, CBullet** bullets, DateInfo dateInfo);	// ����, �̵�
	void TakeDamageFromPlayer() { m_isChasing = TRUE; }		// �÷��̾�� ���� ������ ���� ����

private:
	FLOAT m_chaseRange;			// ���� ����
	BOOL m_isChasing;			// ���� ������
	FLOAT m_attackRange;		// ���� ����
	BOOL m_isAttacking;			// ���� ������
	LPDIRECT3DVERTEXBUFFER9 g_pVB_HPBar; // ü�� ������
	D3DXVECTOR3 m_v3Muzzle;		// �ѱ�

	D3DXVECTOR3 m_rendMovePos;	// ���� ���� ��ġ
	FLOAT m_randMoveDelay;		// ���� �̵� ������
	FLOAT m_randMoveDelayCount;	// ���� �̵� ������ ī��Ʈ

	int m_canGetExp;			// ���� �� �ִ� ����ġ
	int m_enemyType;			// �� ����
};

#endif