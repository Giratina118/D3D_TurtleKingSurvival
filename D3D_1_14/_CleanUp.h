#ifndef __CLEANUP_H__
#define __CLEANUP_H__

#include <d3d9.h>
#include <d3dx9.h>

class CBullet;
class CEnemy;

VOID Cleanup(LPDIRECT3D9* g_pD3D, LPDIRECT3DDEVICE9* g_pd3dDevice, LPDIRECT3DVERTEXBUFFER9* g_pVB_Array, LPDIRECT3DINDEXBUFFER9* g_pIB_Array, LPDIRECT3DTEXTURE9* g_pTEXTURE_Array, CBullet** bullets, CEnemy** enemyObj);		// °´Ã¼ Á¦°Å

#endif