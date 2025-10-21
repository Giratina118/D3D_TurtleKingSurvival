#ifndef __INIT_H__
#define __INIT_H__

#include "_VertexData.h"
#include "Timer.h"

class CObject;
class CEnemy;
class CBullet;

HRESULT InitD3D(HWND hWnd, LPDIRECT3D9* g_pD3D);		// D3D �ʱ�ȭ
HRESULT InitVB(LPDIRECT3DVERTEXBUFFER9* g_pVB_Array);	// ���� ���� �ʱ�ȭ(��ü)
HRESULT InitIB(LPDIRECT3DINDEXBUFFER9*  g_pIB_Array);	// �ε��� ���� �ʱ�ȭ
void _SetVB(UINT verticesSize, CUSTOMVERTEX* vertices, LPDIRECT3DVERTEXBUFFER9* pVB);	// ���� ���� �ʱ�ȭ(����)
void _SetIB(UINT indicesSize, CUSTOMINDEX_LIST* indices, LPDIRECT3DINDEXBUFFER9* pIB);	// �ε��� ���� �ʱ�ȭ(����)

void InitMatrixTranslation(CObject** landformObj);										// ��ü�� �迭(��ġ) �ʱ�ȭ
void InitSlider(SliderData* sliderInfo);												// �����̴� ��ü �ʱ�ȭ
void _SetSlider(SliderData* sliderInfo, int sliderNum, FLOAT startXPos, FLOAT endXPos);	// �����̴� ���� �ʱ�ȭ
void InitGame(CObject** landformObj, SliderData* sliderInfo, CEnemy** enemyObj, CBullet** bullets, SHORT* mousePos);	// ������Ʈ�� �ʱ�ȭ

#endif