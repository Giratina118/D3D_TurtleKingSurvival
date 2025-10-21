#ifndef __CPALYER_H__
#define __CPALYER_H__

#include "CCharacter.h"
#include "Timer.h"

class CBullet;

enum LevelUpBonus
{
	HP_MAX_UP = 0,
	HP_RECOVER_UP,
	MOVE_SPEED_UP,
	ATTACK_DAMAGE_UP,
	ATTACK_SPEED_UP,
	GET_EXP_UP,

	LEVELUP_BONUS_MAX,

	BULLET_SPREAD_UP,
	BULLET_BURST_UP,
	BULLET_SIZE_UP,

	LEVELUP_BONUS_SPECIAL_MAX
};

class CPlayer : public CCharacter
{
public:
	CPlayer();
	CPlayer(D3DXMATRIX matrix, D3DXVECTOR3 length, float radius);
	~CPlayer();

	int GetLevel() { return m_level; }
	int* GetLevelUpBonusNum() { return m_levelupBonusNum; }
	int GetHpRecoveryRate() { return m_hpRecoverRate; }
	FLOAT GetHpRecoveryDelay() { return m_hpRecoverDelay; }
	FLOAT GetMoveSpeed() { return m_moveSpeed; }
	int GetAttackDamage() { return m_attackDamage; }
	FLOAT GetAttackDelay() { return m_attackDelay; }
	FLOAT GetExpBonusRate() { return m_expBonusRate; }
	int GetNowExp() { return (int)m_nowExp; }
	int GetLevelUpExp() { return (int)m_levelUpExp; }
	int GetAttackSpreadLevel() { return m_attackSpreadLevel; }
	int GetAttackBurstLevel() { return m_attackBurstLevel; }
	int GetBulletSizeLevel() { return m_bullstSizeLevel; }
	BOOL GetIsJumping() { return m_isJumping; }
	void SetIsJumping(BOOL isJumping) { m_isJumping = isJumping; }

	void SettingLevelUpBonusSpecial();				// 특수 레벨업 보너스 카드 세팅
	void SettingInfo();								// 플레이어 기본 정보 세팅
	void TakeExp(int exp, SceneState* sceneState);	// 경험치 획득
	void Attack(CBullet** bullets);					// 공격
	void TakeDamage(int damage);					// 공격 받음
	void UpdatePlayer(Timer timer);					// 업데이트 (공격, 체력 회복 딜레이)
	void RandChoiceLevelUpBonus();					// 레벨업 보너스 카드 화면에 나올 3개 랜덤 선택
	void ClickLevelUpBonus(int clickNum);			// 레벨업 보너스 카드 클릭

private:
	FLOAT m_nowExp;					// 현재 경험치
	FLOAT m_levelUpExp;				// 다음 레벨 레벨업 경험치
	int m_level;					// 레벨
	int m_hpRecoverRate;			// 자연 회복량
	FLOAT m_hpRecoverDelay;			// 자연 회복 딜레이
	FLOAT m_hpRecoverDelayCount;	// 자연 회복 딜레이 카운터
	int m_levelupBonusNum[3];		// 레벨업 보너스 카드 3개
	FLOAT m_expBonusRate;			// 경험치 보너스
	int m_attackSpreadLevel;		// 분사 레벨
	int m_attackBurstLevel;			// 연사 레벨
	int m_bullstSizeLevel;			// 총알 크기 레벨
	BOOL m_isJumping;				// 이중 점프 방지
};

#endif