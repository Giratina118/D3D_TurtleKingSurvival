#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "_VertexData.h"
#include "Timer.h"

class CSprite
{
public:
	CSprite();
	CSprite(CUSTOMVERTEX* spriteVertices, D3DXMATRIX matrix, FLOAT lifeTime, int maxSprite, BOOL isLoop);
	~CSprite();

	D3DXMATRIX* GetMatrix() { return &m_matrix; }
	BOOL GetIsPlaySprite() { return m_isPlaySprite; }
	int GetNowTextureCount() { return m_nowSpriteCount; }
	void SetPlaySprite() { m_isPlaySprite = TRUE; }

	void UpdateSprite(Timer timer);	// ��������Ʈ ������Ʈ

private:
	CUSTOMVERTEX* m_spriteVertices;	// ��������Ʈ ����
	D3DXMATRIX m_matrix;			// ��������Ʈ ���
	FLOAT m_lifeTime;				// ���� �ð�
	FLOAT m_lifeTimeCount;			// ���� �ð� ī��Ʈ
	int m_maxSprite;				// ��������Ʈ ��(2d �ִϸ��̼�)
	int m_nowSpriteCount;			// ���� � ��������Ʈ�� ����ϰ� �ִ���
	BOOL m_isPlaySprite;			// ��������Ʈ�� ����ߴ���
	BOOL m_isLoop;					// �ݺ� ��� ����
};

#endif