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

	void SettingLevelUpBonusSpecial();				// Ư�� ������ ���ʽ� ī�� ����
	void SettingInfo();								// �÷��̾� �⺻ ���� ����
	void TakeExp(int exp, SceneState* sceneState);	// ����ġ ȹ��
	void Attack(CBullet** bullets);					// ����
	void TakeDamage(int damage);					// ���� ����
	void UpdatePlayer(Timer timer);					// ������Ʈ (����, ü�� ȸ�� ������)
	void RandChoiceLevelUpBonus();					// ������ ���ʽ� ī�� ȭ�鿡 ���� 3�� ���� ����
	void ClickLevelUpBonus(int clickNum);			// ������ ���ʽ� ī�� Ŭ��

private:
	FLOAT m_nowExp;					// ���� ����ġ
	FLOAT m_levelUpExp;				// ���� ���� ������ ����ġ
	int m_level;					// ����
	int m_hpRecoverRate;			// �ڿ� ȸ����
	FLOAT m_hpRecoverDelay;			// �ڿ� ȸ�� ������
	FLOAT m_hpRecoverDelayCount;	// �ڿ� ȸ�� ������ ī����
	int m_levelupBonusNum[3];		// ������ ���ʽ� ī�� 3��
	FLOAT m_expBonusRate;			// ����ġ ���ʽ�
	int m_attackSpreadLevel;		// �л� ����
	int m_attackBurstLevel;			// ���� ����
	int m_bullstSizeLevel;			// �Ѿ� ũ�� ����
	BOOL m_isJumping;				// ���� ���� ����
};

#endif