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

	void Attack(Timer timer, CPlayer* player, CBullet** bullets, DateInfo dateInfo);		// 공격
	void Move(Timer timer, CPlayer* player, DateInfo dateInfo);								// 이동
	void UpdateEnemy(Timer timer, CPlayer* player, CBullet** bullets, DateInfo dateInfo);	// 공격, 이동
	void TakeDamageFromPlayer() { m_isChasing = TRUE; }		// 플레이어에게 공격 받으면 추적 시작

private:
	FLOAT m_chaseRange;			// 추적 범위
	BOOL m_isChasing;			// 추적 중인지
	FLOAT m_attackRange;		// 공격 범위
	BOOL m_isAttacking;			// 공격 중인지
	LPDIRECT3DVERTEXBUFFER9 g_pVB_HPBar; // 체력 게이지
	D3DXVECTOR3 m_v3Muzzle;		// 총구

	D3DXVECTOR3 m_rendMovePos;	// 랜덤 생성 위치
	FLOAT m_randMoveDelay;		// 랜덤 이동 딜레이
	FLOAT m_randMoveDelayCount;	// 랜덤 이동 딜레이 카운트

	int m_canGetExp;			// 얻을 수 있는 경험치
	int m_enemyType;			// 적 유형
};

#endif