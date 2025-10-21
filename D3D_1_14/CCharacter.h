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

	BOOL OverAttackDelay();			// ���� ������ üũ(���� ������ ��������)
	void Move();					// �̵�
	void Attack();					// ����
	void TakeDamage(int damage);	// ���� ������ ���
	void Die() { m_alive = FALSE; }	// ��� ó��

protected:
	int m_hpNow;				// ���� ä��
	int m_hpMax;				// �ִ� ü��
	int m_attackDamage;			// ���ݷ�
	FLOAT m_moveSpeed;			// �̵� �ӵ�
	FLOAT m_attackDelay;		// ���� ������
	FLOAT m_attackDelayCount;	// ���� ������ ī����
	BOOL m_alive;				// ���� ����
};

#endif