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

	void UpdateSprite(Timer timer);	// 스프라이트 업데이트

private:
	CUSTOMVERTEX* m_spriteVertices;	// 스프라이트 정점
	D3DXMATRIX m_matrix;			// 스프라이트 행렬
	FLOAT m_lifeTime;				// 생존 시간
	FLOAT m_lifeTimeCount;			// 생존 시간 카운트
	int m_maxSprite;				// 스프라이트 수(2d 애니메이션)
	int m_nowSpriteCount;			// 현재 어떤 스프라이트를 재생하고 있는지
	BOOL m_isPlaySprite;			// 스프라이트를 재생했는지
	BOOL m_isLoop;					// 반복 재생 여부
};

#endif