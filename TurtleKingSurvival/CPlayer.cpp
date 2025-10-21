#include "CPlayer.h"
#include "_TransformMatrix.h"
#include "_UpdateGameProc.h"
#include "_Init.h"
#include "CBullet.h"
#include "_UIManager.h"
#include <stdio.h>


extern LPDIRECT3DVERTEXBUFFER9* g_pVB_Array;

CPlayer::CPlayer()
{
	D3DXMATRIX iMatrix;
	D3DXMatrixIdentity(&iMatrix);
	m_matrix = iMatrix;

	m_radius = 1.0f;
	m_canCollide = TRUE;
	m_length = { 1.0f, 2.0f, 1.0f };
	m_objType = OBJECT_PLAYER;
	m_fallingSpeed = GRAVITY_ACCELERATION;

	SettingInfo();
}

CPlayer::CPlayer(D3DXMATRIX matrix, D3DXVECTOR3 length, float radius)
{
	m_matrix = matrix;
	m_radius = radius;
	m_canCollide = TRUE;
	m_length = length;
	m_objType = OBJECT_PLAYER;
	m_fallingSpeed = GRAVITY_ACCELERATION;

	SettingInfo();
}

CPlayer::~CPlayer()
{

}

// 특수 레벨업 보너스 카드 세팅
void CPlayer::SettingLevelUpBonusSpecial()
{
	m_levelupBonusNum[0] = BULLET_SPREAD_UP;
	m_levelupBonusNum[1] = BULLET_BURST_UP;
	m_levelupBonusNum[2] = BULLET_SIZE_UP;
}


void CPlayer::SettingInfo()
{
	m_matrix = D3DXMATRIX(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 3, 0, 1);

	m_hpNow = m_hpMax = 100;
	m_attackDamage = 20;
	m_moveSpeed = 5.0f;
	m_alive = TRUE;
	m_attackDelay = 1.0f;
	m_attackDelayCount = 0.0f;

	m_nowExp = 0;
	m_level = 1;
	m_levelUpExp = m_level * 2.0f;
	m_hpRecoverRate = 10;
	m_hpRecoverDelay = 6.0f;
	m_hpRecoverDelayCount = 0.0f;
	m_expBonusRate = 1.0f;
	m_attackSpreadLevel = 1;
	m_attackBurstLevel = 1;
	m_bullstSizeLevel = 1;

	m_levelupBonusNum[0] = 0;
	m_levelupBonusNum[1] = 0;
	m_levelupBonusNum[2] = 0;
	m_isJumping = FALSE;

	playerHpExpBarVertices[13].x = playerHpExpBarVertices[14].x = PLAYERHPMIN + (float)m_nowExp / (float)m_levelUpExp * (PLAYERHPMAX - PLAYERHPMIN);
}

// 경험치 획득
void CPlayer::TakeExp(int exp, SceneState* sceneState)
{
	m_nowExp += exp * m_expBonusRate;
	sceneState->tempMouseCrossFocusMode = sceneState->mouseCrossFocusMode;
	sceneState->tempRotateFreeze = sceneState->rotateFreeze;

	if (m_levelUpExp <= m_nowExp)
	{
		if (m_level % 5 == 4 && m_level < 101)	SettingLevelUpBonusSpecial();
		else									RandChoiceLevelUpBonus();
		SetCursorPos(WIDTH_WINDOW / 2, HEIGHT_WINDOW / 4);

		m_nowExp -= m_levelUpExp;
		m_level++;
		m_levelUpExp = m_level * 2.0f;
		sceneState->onLevelUpScreen = TRUE;
		sceneState->mouseCrossFocusMode = FALSE;
		sceneState->rotateFreeze = TRUE;

		TurnOnOffCursor(TRUE);
	}

	FLOAT nowExpXPos = PLAYERHPMIN + (float)m_nowExp / (float)m_levelUpExp * (PLAYERHPMAX - PLAYERHPMIN);
	if (nowExpXPos > PLAYERHPMAX)
		nowExpXPos = PLAYERHPMAX;
	playerHpExpBarVertices[13].x = playerHpExpBarVertices[14].x = nowExpXPos;
}

// 공격
void CPlayer::Attack(CBullet** bullets)
{
	D3DXMATRIX tm_tmep;
	D3DXVECTOR3 v3_tempDir;

	for (int i = 1; i <= m_attackBurstLevel; i++)
	{
		tm_tmep = m_matrix;
		RotationObject(&tm_tmep, Y_MINUS_ROT, (m_attackSpreadLevel + 1) * 5.0f, FALSE);

		for (int spreadBullet = 0; spreadBullet < m_attackSpreadLevel; spreadBullet++)
		{
			RotationObject(&tm_tmep, Y_PLUS_ROT, 10, TRUE);
			v3_tempDir = { tm_tmep._31, tm_tmep._32, tm_tmep._33 };
			CreateBullet(bullets, m_matrix, { 0, 0, 0 }, v3_tempDir * (1.0f + i * 0.2f), m_bullstSizeLevel, m_attackDamage * (1.0f + 0.1f * m_bullstSizeLevel), m_objType);
		}
	}
}

// 공격 받음
void CPlayer::TakeDamage(int damage)
{
	CCharacter::TakeDamage(damage);

	FLOAT nowHpXPos = PLAYERHPMIN + GetNowHpRate() * (PLAYERHPMAX - PLAYERHPMIN);
	playerHpExpBarVertices[5].x = playerHpExpBarVertices[6].x = nowHpXPos;
}

// 업데이트
void CPlayer::UpdatePlayer(Timer timer)
{
	m_attackDelayCount += timer.GetDeltaTime();
	m_hpRecoverDelayCount += timer.GetDeltaTime();

	if (m_hpRecoverDelayCount > m_hpRecoverDelay)
	{
		m_hpRecoverDelayCount -= m_hpRecoverDelay;
		if (m_hpNow + m_hpRecoverRate > m_hpMax)	TakeDamage(m_hpNow - m_hpMax);
		else										TakeDamage(-m_hpRecoverRate);
	}
}

// 레벨업 보너스 카드 화면에 나올 3개 랜덤 선택
void CPlayer::RandChoiceLevelUpBonus()
{
	m_levelupBonusNum[0] = m_levelupBonusNum[1] = m_levelupBonusNum[2] = rand() % LEVELUP_BONUS_MAX;

	while (m_levelupBonusNum[0] == m_levelupBonusNum[1])
		m_levelupBonusNum[1] = rand() % LEVELUP_BONUS_MAX;

	while (m_levelupBonusNum[0] == m_levelupBonusNum[2] || m_levelupBonusNum[1] == m_levelupBonusNum[2])
		m_levelupBonusNum[2] = rand() % LEVELUP_BONUS_MAX;
}

// 레벨업 보너스 카드 클릭
void CPlayer::ClickLevelUpBonus(int clickNum)
{
	switch (m_levelupBonusNum[clickNum])
	{
	case HP_MAX_UP:
		m_hpMax += 20;
		break;

	case HP_RECOVER_UP:
		m_hpRecoverRate += 2;
		m_hpRecoverDelay *= 0.95f;
		break;

	case MOVE_SPEED_UP:
		m_moveSpeed += 0.2f;
		break;

	case ATTACK_DAMAGE_UP:
		m_attackDamage += 2;
		break;

	case ATTACK_SPEED_UP:
		m_attackDelay *= 0.95f;
		break;

	case GET_EXP_UP:
		m_expBonusRate += 0.1f;
		break;

	case BULLET_SPREAD_UP:
		m_attackSpreadLevel++;
		break;

	case BULLET_BURST_UP:
		m_attackBurstLevel++;
		break;

	case BULLET_SIZE_UP:
		m_bullstSizeLevel++;
		break;

	default:
		break;
	}

	m_hpNow = m_hpMax;
	TakeDamage(0);
}