#include "CCharacter.h"
#include "CEnemy.h"

CCharacter::CCharacter()
{

}

CCharacter::~CCharacter()
{

}

// ���� ������
BOOL CCharacter::OverAttackDelay()
{
	if (m_attackDelayCount > m_attackDelay)
	{
		m_attackDelayCount = 0.0f;
		return TRUE;
	}
	return FALSE;
}

void CCharacter::Move()
{

}

void CCharacter::Attack()
{

}

// ���� ������ ���
void CCharacter::TakeDamage(int damage)
{
	m_hpNow -= damage;

	if (m_hpNow <= 0)
		Die();
	else if (m_objType == OBJECT_ENEMY)
		static_cast<CEnemy*>(this)->TakeDamageFromPlayer();
}