#ifndef __INIT_H__
#define __INIT_H__

#include "_VertexData.h"
#include "Timer.h"

class CObject;
class CEnemy;
class CBullet;

HRESULT InitD3D(HWND hWnd, LPDIRECT3D9* g_pD3D);		// D3D 초기화
HRESULT InitVB(LPDIRECT3DVERTEXBUFFER9* g_pVB_Array);	// 정점 버퍼 초기화(전체)
HRESULT InitIB(LPDIRECT3DINDEXBUFFER9*  g_pIB_Array);	// 인덱스 버퍼 초기화
void _SetVB(UINT verticesSize, CUSTOMVERTEX* vertices, LPDIRECT3DVERTEXBUFFER9* pVB);	// 정점 버퍼 초기화(개별)
void _SetIB(UINT indicesSize, CUSTOMINDEX_LIST* indices, LPDIRECT3DINDEXBUFFER9* pIB);	// 인덱스 버퍼 초기화(개별)

void InitMatrixTranslation(CObject** landformObj);										// 객체들 배열(위치) 초기화
void InitSlider(SliderData* sliderInfo);												// 슬라이더 전체 초기화
void _SetSlider(SliderData* sliderInfo, int sliderNum, FLOAT startXPos, FLOAT endXPos);	// 슬라이더 개별 초기화
void InitGame(CObject** landformObj, SliderData* sliderInfo, CEnemy** enemyObj, CBullet** bullets, SHORT* mousePos);	// 오브젝트들 초기화

#endif