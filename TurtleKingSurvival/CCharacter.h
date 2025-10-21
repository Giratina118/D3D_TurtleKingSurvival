#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "CObject.h"

class CCharacter : public CObject
{
public:
	CCharacter();
	~CCharacter();

	int GetHpNow() { return m_hpNow; }
	int GetHpMax() { return m_hpMax; }
	FLOAT GetNowHpRate() { return (FLOAT)m_hpNow / (FLOAT)m_hpMax; }
	int GetScore() { return m_hpMax; }

	BOOL OverAttackDelay();			// 공격 딜레이 체크(공격 가능한 상태인지)
	void Move();					// 이동
	void Attack();					// 공격
	void TakeDamage(int damage);	// 받은 데미지 계산
	void Die() { m_alive = FALSE; }	// 사망 처리

protected:
	int m_hpNow;				// 현재 채력
	int m_hpMax;				// 최대 체력
	int m_attackDamage;			// 공격력
	FLOAT m_moveSpeed;			// 이동 속도
	FLOAT m_attackDelay;		// 공격 딜레이
	FLOAT m_attackDelayCount;	// 공격 딜레이 카운터
	BOOL m_alive;				// 생존 여부
};

#endif