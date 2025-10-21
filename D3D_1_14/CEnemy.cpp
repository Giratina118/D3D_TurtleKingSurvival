#include "CEnemy.h"
#include "_TransformMatrix.h"
#include "_UpdateGameProc.h"
#include "CBullet.h"
#include "CPlayer.h"

CEnemy::CEnemy()
{
	m_radius = 1.0f;
	m_length = { 1.0f, 2.0f, 2.0f };

	m_hpNow = m_hpMax = 100;
	m_attackDamage = 10;
	m_moveSpeed = 3.0f;

	m_attackRange = 5.0f;
	m_attackDelay = 5.0f;
	m_chaseRange = 8.0f;
	m_v3Muzzle = { 0.0f, 0.5f, 0.9f };
	m_canGetExp = 1;

	SettingCEnmyCommonInfo();
}

CEnemy::CEnemy(int enemyType, DateInfo dateInfo)
{
	m_enemyType = enemyType;
	switch (m_enemyType)	// 적 랜덤으로 한 종류 소환
	{
	case ENEMY_TYPE1:		// 기본
		m_radius = 1.0f;
		m_length = { 1.0f, 1.75f, 2.0f };

		m_hpNow = m_hpMax = dateInfo.month * 100 + dateInfo.day * 5 - 5;
		m_attackDamage = 5 + dateInfo.month * 5 + dateInfo.day / 5 * 2;
		m_moveSpeed = 3.0f + dateInfo.month * 0.3f;

		m_attackRange = 6.0f;
		m_attackDelay = 2.1f - dateInfo.month * 0.1f;
		m_chaseRange = 9.0f;
		m_v3Muzzle = { 0.0f, 0.5f, 0.95f };
		m_canGetExp = 3 + dateInfo.month;
		break;

	case ENEMY_TYPE2:		// 이속, 공속 ↓,  사거리, 공격력 ↑
		m_radius = 1.0f;
		m_length = { 1.0f, 1.75f, 2.0f };

		m_hpNow = m_hpMax = dateInfo.month * 150 + dateInfo.day * 7 - 5;
		m_attackDamage = 8 + dateInfo.month * 8 + dateInfo.day / 2;
		m_moveSpeed = 2.0f + dateInfo.month * 0.2f;

		m_attackRange = 7.0f;
		m_attackDelay = 4.2f - dateInfo.month * 0.2f;
		m_chaseRange = 8.0f;
		m_v3Muzzle = { 0.0f, 0.5f, 0.95f };
		m_canGetExp = 4 + dateInfo.month * 1.34f;
		break;

	case ENEMY_TYPE3:		// 사거리, 공격력 ↓,  이속, 공속 ↑
		m_radius = 1.0f;
		m_length = { 1.0f, 1.75f, 2.0f };

		m_hpNow = m_hpMax = dateInfo.month * 70 + dateInfo.day * 3 - 5;
		m_attackDamage = 3 + dateInfo.month * 3 + dateInfo.day / 5;
		m_moveSpeed = 4.0f + dateInfo.month * 0.5f;

		m_attackRange = 5.0f;
		m_attackDelay = 1.1f - dateInfo.month * 0.055f;
		m_chaseRange = 12.0f;
		m_v3Muzzle = { 0.0f, 0.5f, 0.95f };
		m_canGetExp = 5 + dateInfo.month * 1.5f;
		break;

	default:
		m_radius = 1.0f;
		m_length = { 1.0f, 1.75f, 2.0f };

		m_hpNow = m_hpMax = 100;
		m_attackDamage = 10;
		m_moveSpeed = 3.0f;

		m_attackRange = 5.0f;
		m_attackDelay = 1.0f;
		m_chaseRange = 8.0f;
		m_v3Muzzle = { 0.0f, 0.5f, 0.95f };
		m_canGetExp = 1;
		break;
	}

	SettingCEnmyCommonInfo();
}

CEnemy::~CEnemy()
{

}

// 변수 정의 공통 부분
void CEnemy::SettingCEnmyCommonInfo()
{
	D3DXMATRIX iMatrix;
	D3DXMatrixIdentity(&iMatrix);
	m_matrix = iMatrix;

	m_matrix._41 = rand() % ((int)(GROUND_X * GROUND_RADIUS - m_radius * 3) * 2) - (GROUND_X * GROUND_RADIUS - m_radius * 3);
	m_matrix._43 = rand() % ((int)(GROUND_Z * GROUND_RADIUS - m_radius * 3) * 2) - (GROUND_Z * GROUND_RADIUS - m_radius * 3);

	m_canCollide = TRUE;
	m_objType = OBJECT_ENEMY;
	m_fallingSpeed = GRAVITY_ACCELERATION;

	m_alive = TRUE;
	m_isChasing = FALSE;
	m_isAttacking = FALSE;

	g_pVB_HPBar = NULL;
	m_attackDelayCount = 0.0f;
	m_rendMovePos = { 0.0f, 0.0f, 0.0f };
	m_rendMovePos.x = rand() % ((int)(GROUND_X * GROUND_RADIUS - m_length.x * 2) * 2) - (GROUND_X * GROUND_RADIUS - m_length.x * 2);
	m_rendMovePos.z = rand() % ((int)(GROUND_Z * GROUND_RADIUS - m_length.z * 2) * 2) - (GROUND_Z * GROUND_RADIUS - m_length.z * 2);
	m_randMoveDelay = 5.0f;
	m_randMoveDelayCount = 0.0f;

	RotationLookAt(this, m_rendMovePos);
}

// 체력 게이지 위치
D3DXMATRIX CEnemy::GetHpBarMatrix()
{
	D3DXMATRIX hpBarMatrix = m_matrix;
	hpBarMatrix._42 += m_length.y / 2;

	return hpBarMatrix;
}

// 공격
void CEnemy::Attack(Timer timer, CPlayer* player, CBullet** bullets, DateInfo dateInfo)
{
	FLOAT attDmgBonus = 1.0f;
	m_attackDelayCount += timer.GetDeltaTime();

	FLOAT distanceToPlayer = sqrtf(powf(player->GetPos().x - this->GetPos().x, 2) + powf(player->GetPos().y - this->GetPos().y, 2));
	if (m_isAttacking)
	{
		if (m_attackRange < distanceToPlayer)	m_isAttacking = FALSE;
		else if (m_attackDelayCount > m_attackDelay)
		{
			m_attackDelayCount = 0.0f;
			if (dateInfo.clock > 20 || dateInfo.clock < 4)
				attDmgBonus = 1.25f;

			CreateBullet(bullets, m_matrix, m_v3Muzzle, GetFront(), 1, m_attackDamage * attDmgBonus, m_objType);
			TranslateObject(this, MOVE_BACK, m_moveSpeed * 10.0f * timer.GetDeltaTime()); // 반동
		}
	}
	else
		if (m_attackRange > distanceToPlayer)	m_isAttacking = TRUE;
}

// 이동
void CEnemy::Move(Timer timer, CPlayer* player, DateInfo dateInfo)
{
	FLOAT distanceToPlayer = sqrtf(powf(player->GetPos().x - this->GetPos().x, 2) + powf(player->GetPos().y - this->GetPos().y, 2));
	FLOAT moveSpeedBonus = 1.0f;
	if (dateInfo.clock > 20 || dateInfo.clock < 4)
		moveSpeedBonus = 1.25f;

	if (m_isChasing) {
		if (distanceToPlayer > m_chaseRange * 1.5f) {
			m_isChasing = FALSE;
			return;
		}

		RotationLookAt(this, player->GetPos());
		if (distanceToPlayer > m_attackRange * 0.5f)
			TranslateObject(this, MOVE_FRONT, m_moveSpeed * moveSpeedBonus * timer.GetDeltaTime());
	}
	else {
		if (distanceToPlayer < m_chaseRange) {
			m_isChasing = TRUE;
			return;
		}
		
		// 랜덤좌표 이동
		m_randMoveDelayCount += timer.GetDeltaTime();

		if (m_randMoveDelay < m_randMoveDelayCount) {
			m_rendMovePos.x = rand() % ((int)(GROUND_X * GROUND_RADIUS - m_length.x * 2) * 2) - (GROUND_X * GROUND_RADIUS - m_length.x * 2);
			m_rendMovePos.z = rand() % ((int)(GROUND_Z * GROUND_RADIUS - m_length.z * 2) * 2) - (GROUND_Z * GROUND_RADIUS - m_length.z * 2);
			m_rendMovePos.y = player->GetPos().y;
			m_randMoveDelayCount = 0.0f;
			RotationLookAt(this, m_rendMovePos);
		}
		TranslateObject(this, MOVE_FRONT, m_moveSpeed * moveSpeedBonus * timer.GetDeltaTime());
	}
}

void CEnemy::UpdateEnemy(Timer timer, CPlayer* player, CBullet** bullets, DateInfo dateInfo)
{
	Move(timer, player, dateInfo);
	Attack(timer, player, bullets, dateInfo);
}