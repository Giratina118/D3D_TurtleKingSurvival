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
extern SCREEN_VERTEX titleSceneVertices[];      // 타이틀씬 정점
extern SCREEN_VERTEX resultSceneVertices[];     // 결과씬 정점
extern SCREEN_VERTEX gameSceneVertices[];       // 게임씬 정점
extern SCREEN_VERTEX menuVertices[];            // 메뉴 UI 정점
extern SCREEN_VERTEX menuSliderVertices[];      // 슬라이더 정점
extern SCREEN_VERTEX playerHpExpBarVertices[];  // 플레이어 체력바, 경험치바 
extern SCREEN_VERTEX levelUpScreenVertices[];   // 레벨업 창 정점

// 3D Object
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;     // 법선 벡터
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

extern CUSTOMVERTEX cubeVertices[CUBE_VERTEX_COUNT];    // 큐브 정점(벽, 장애물)
extern CUSTOMINDEX_LIST cubeIndices[12];        // 큐브 인덱스

extern CUSTOMVERTEX groundVertices[4];          // 땅(잔디) 정점
extern CUSTOMVERTEX bliboardVertices[8];        // 빌보드(나무, 구름) 정점
extern CUSTOMVERTEX enemyHpBarVertices[8];      // 빌보드(적 체력바) 정점
extern CUSTOMVERTEX spriteVertices[80];

extern CUSTOMVERTEX skyBoxVertices[24];         // 스카이박스 정점

extern CUSTOMVERTEX enemy1Vertices[4 * 41];     // 적1 정점,   한 면에 정점 4개
extern CUSTOMINDEX_LIST enemy1Indices[2 * 41];  // 적1 인덱스, 한 면에 도형(삼각형) 2개 

extern CUSTOMVERTEX bulletVertices[12];         // 총알 정점
extern CUSTOMINDEX_LIST bulletIndices[20];      // 적1 인덱스, 한 면에 도형(삼각형) 2개

#endif
