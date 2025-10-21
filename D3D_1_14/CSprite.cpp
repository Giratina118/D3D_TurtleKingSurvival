#include "CSprite.h"

CSprite::CSprite()
{
	m_spriteVertices = NULL;
	m_matrix = { };
	m_lifeTime = 0.0f;
	m_lifeTimeCount = 0.0f;
	m_maxSprite = 0;
	m_nowSpriteCount = 0;
	m_isPlaySprite = FALSE;
	m_isLoop = FALSE;
}

CSprite::CSprite(CUSTOMVERTEX* spriteVertices, D3DXMATRIX matrix, FLOAT lifeTime, int maxSprite, BOOL isLoop)
{
	m_spriteVertices = spriteVertices;
	m_matrix = matrix;
	m_lifeTime = lifeTime;
	m_lifeTimeCount = 0.0f;
	m_maxSprite = maxSprite;
	m_nowSpriteCount = 0;
	m_isPlaySprite = FALSE;
	m_isLoop = isLoop;
}

CSprite::~CSprite()
{

}

void CSprite::UpdateSprite(Timer timer)
{
	m_lifeTimeCount += timer.GetDeltaTime();
	if (m_lifeTime < m_lifeTimeCount)
	{
		if (m_isLoop) m_lifeTimeCount = 0.0f;
		else		  m_isPlaySprite = FALSE;
	}
	else if (m_lifeTimeCount / m_lifeTime > 1.0f * m_nowSpriteCount / m_maxSprite)
		m_nowSpriteCount++;
}