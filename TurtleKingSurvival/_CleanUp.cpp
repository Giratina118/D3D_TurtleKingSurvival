#include "_CleanUp.h"
#include "CBullet.h"
#include "CEnemy.h"
#include <xaudio2.h>

extern IXAudio2* pXAudio2;
extern IXAudio2MasteringVoice* pMasteringVoice;
extern IXAudio2SourceVoice* pSourceVoice[10];

// 객체 제거
VOID Cleanup(LPDIRECT3D9* g_pD3D, LPDIRECT3DDEVICE9* g_pd3dDevice, LPDIRECT3DVERTEXBUFFER9* g_pVB_Array, LPDIRECT3DINDEXBUFFER9* g_pIB_Array, LPDIRECT3DTEXTURE9* g_pTEXTURE_Array, CBullet** bullets, CEnemy** enemyObj)
{
    // 해제 순서: 해제시 반드시 생성 순서의 역순으로 해제

    // 사운드 관련 해제
    for (int i = 0; i < 10; i++)
        if (pSourceVoice[i] != NULL) pSourceVoice[i]->DestroyVoice();
    if (pMasteringVoice != NULL)     pMasteringVoice->DestroyVoice();
    if (pXAudio2 != NULL)            pXAudio2->Release();
    CoUninitialize();

    for (int i = 0; i < ENEMY_MAX; i++)     if (enemyObj[i] != NULL)    delete enemyObj[i];
    for (int i = 0; i < BULLET_MAX; i++)    if (bullets[i] != NULL)     delete bullets[i];

    for (int i = TEXTURE_MAX - 1; i > -1; i--)  if (g_pTEXTURE_Array[i] != NULL)    g_pTEXTURE_Array[i]->Release();
    for (int i = IB_MAX - 1; i > -1; i--)       if (g_pIB_Array[i] != NULL)         g_pIB_Array[i]->Release();
    for (int i = VB_MAX - 1; i > -1; i--)       if (g_pVB_Array[i] != NULL)         g_pVB_Array[i]->Release();

    if (*g_pd3dDevice != NULL)  (*g_pd3dDevice)->Release();
    if (*g_pD3D != NULL)        (*g_pD3D)->Release();
}