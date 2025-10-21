#ifndef __VERTEXDATA_H__
#define __VERTEXDATA_H__

#include "_DefineData.h"

// 2D UI
struct SCREEN_VERTEX
{
    FLOAT x, y, z, w;
    DWORD color;
    FLOAT u, v;
    static DWORD FVF;
};
extern SCREEN_VERTEX titleSceneVertices[];      // Ÿ��Ʋ�� ����
extern SCREEN_VERTEX resultSceneVertices[];     // ����� ����
extern SCREEN_VERTEX gameSceneVertices[];       // ���Ӿ� ����
extern SCREEN_VERTEX menuVertices[];            // �޴� UI ����
extern SCREEN_VERTEX menuSliderVertices[];      // �����̴� ����
extern SCREEN_VERTEX playerHpExpBarVertices[];  // �÷��̾� ü�¹�, ����ġ�� 
extern SCREEN_VERTEX levelUpScreenVertices[];   // ������ â ����

// 3D Object
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;     // ���� ����
    FLOAT u, v;
    static DWORD FVF;
};

struct CUSTOMINDEX_LIST
{
    WORD	v0, v1, v2;
};

struct CUSTOMINDEX_FAN
{
    WORD	v0, v1, v2, v3;
};

extern CUSTOMVERTEX cubeVertices[CUBE_VERTEX_COUNT];    // ť�� ����(��, ��ֹ�)
extern CUSTOMINDEX_LIST cubeIndices[12];        // ť�� �ε���

extern CUSTOMVERTEX groundVertices[4];          // ��(�ܵ�) ����
extern CUSTOMVERTEX bliboardVertices[8];        // ������(����, ����) ����
extern CUSTOMVERTEX enemyHpBarVertices[8];      // ������(�� ü�¹�) ����
extern CUSTOMVERTEX spriteVertices[80];

extern CUSTOMVERTEX skyBoxVertices[24];         // ��ī�̹ڽ� ����

extern CUSTOMVERTEX enemy1Vertices[4 * 41];     // ��1 ����,   �� �鿡 ���� 4��
extern CUSTOMINDEX_LIST enemy1Indices[2 * 41];  // ��1 �ε���, �� �鿡 ����(�ﰢ��) 2�� 

extern CUSTOMVERTEX bulletVertices[12];         // �Ѿ� ����
extern CUSTOMINDEX_LIST bulletIndices[20];      // ��1 �ε���, �� �鿡 ����(�ﰢ��) 2��

#endif
