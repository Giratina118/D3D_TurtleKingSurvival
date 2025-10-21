#include "_Init.h"
#include "CEnemy.h"
#include "CObject.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice; // 렌더링에 사용될 D3D 디바이스

// Direct3D 초기화
HRESULT InitD3D(HWND hWnd, LPDIRECT3D9* g_pD3D)
{
    // 디바이스를 생성하기위한 D3D객체 생성
    if (NULL == (*g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;                // 디바이스 생성을 위한 구조체
    ZeroMemory(&d3dpp, sizeof(d3dpp));          // 구조체 비우기       
    d3dpp.Windowed = TRUE;                      // 창모드
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // 가장 효율적인 presentarion을 선택할 수 있게 하는 swap 효과
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;    // 현재의 바탕화면 모드에 맞춰 후면 버퍼를 생성
    d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

    // 실제 디바이스를 생성하는 함수.
    if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
        return E_FAIL;

    return S_OK;
}

// 정점 버퍼 초기화
HRESULT InitVB(LPDIRECT3DVERTEXBUFFER9* g_pVB_Array)
{
    _SetVB(sizeof(cubeVertices),        cubeVertices,       &g_pVB_Array[VB_CUBE]);         // 큐브(벽, 장애물)
    _SetVB(sizeof(groundVertices),      groundVertices,     &g_pVB_Array[VB_GRASS]);        // 땅(바닥)
    _SetVB(sizeof(bliboardVertices),    bliboardVertices,   &g_pVB_Array[VB_BILBOARD]);     // 빌보드(나무, 구름)
    _SetVB(sizeof(skyBoxVertices),      skyBoxVertices,     &g_pVB_Array[VB_SKYBOX]);       // 스카이박스
    _SetVB(sizeof(enemy1Vertices),      enemy1Vertices,     &g_pVB_Array[VB_ENEMY1]);       // 적1
    _SetVB(sizeof(enemyHpBarVertices),  enemyHpBarVertices, &g_pVB_Array[VB_ENEMYHPBAR]);   // 빌보드(적 체력바)
    _SetVB(sizeof(spriteVertices),    spriteVertices,   &g_pVB_Array[VB_BULLETFIRE]);   // 총알 파티클(불꽃)
    _SetVB(sizeof(bulletVertices),      bulletVertices,     &g_pVB_Array[VB_BULLET]);       // 총알

    return S_OK;
}

// 인덱스 버퍼 초기화
HRESULT InitIB(LPDIRECT3DINDEXBUFFER9* g_pIB_Array)
{
    _SetIB(sizeof(cubeIndices),   cubeIndices,   &g_pIB_Array[IB_CUBE]);    // 큐브(벽, 장애물)
    _SetIB(sizeof(enemy1Indices), enemy1Indices, &g_pIB_Array[IB_ENEMY1]);  // 적1
    _SetIB(sizeof(bulletIndices), bulletIndices, &g_pIB_Array[IB_BULLET]);  // 총알

    return S_OK;
}

// 정점 버퍼 초기화(개별 과정)
void _SetVB(UINT verticesSize, CUSTOMVERTEX* vertices, LPDIRECT3DVERTEXBUFFER9* pVB)
{
    VOID* pVertices;
    g_pd3dDevice->CreateVertexBuffer(verticesSize, 0, CUSTOMVERTEX::FVF, D3DPOOL_DEFAULT, pVB, NULL);
    (*pVB)->Lock(0, verticesSize, (void**)&pVertices, 0);   // Lock(lock할 시작점, 크기, 버퍼의 주소, 0)
    memcpy(pVertices, vertices, verticesSize);              // 버퍼에 값을 넣는다
    (*pVB)->Unlock();
}

// 인덱스 버퍼 초기화(개별 과정)
void _SetIB(UINT indicesSize, CUSTOMINDEX_LIST* indices, LPDIRECT3DINDEXBUFFER9* pIB)
{
    VOID* pIndices;
    g_pd3dDevice->CreateIndexBuffer(indicesSize, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, pIB, NULL);
    (*pIB)->Lock(0, indicesSize, (void**)&pIndices, 0);
    memcpy(pIndices, indices, indicesSize);
    (*pIB)->Unlock();
}


// 환경 오브젝트들 초기화
void InitMatrixTranslation(CObject** landformObj)
{
    // 땅(잔디)
    for (int groundX = 0; groundX < GROUND_X; groundX++)
    {
        for (int groundZ = 0; groundZ < GROUND_Z; groundZ++)
        {
            D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_GROUND][groundX * GROUND_Z + groundZ].GetMatrix(), GROUND_RADIUS * (groundX * 2 - GROUND_X + 1), -2.0f, GROUND_RADIUS * (groundZ * 2 - GROUND_Z + 1));
            landformObj[OBJECT_LANDFORM_GROUND][groundX * GROUND_Z + groundZ].SetRadius(GROUND_RADIUS);
            landformObj[OBJECT_LANDFORM_GROUND][groundX * GROUND_Z + groundZ].SetLength(D3DXVECTOR3(GROUND_RADIUS * 2.0f, 0.5f, GROUND_RADIUS * 2.0f));
        }
    }

    // 벽
    for (int wallCount = 0; wallCount < GROUND_X; wallCount++)
    {
        D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_WALL][wallCount].GetMatrix(), GROUND_RADIUS * (wallCount * 2 - GROUND_X + 1), GROUND_RADIUS - 2.0f, (GROUND_Z + 1) * GROUND_RADIUS);
        D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_WALL][wallCount + GROUND_X].GetMatrix(), GROUND_RADIUS * (wallCount * 2 - GROUND_X + 1), GROUND_RADIUS - 2.0f, -(GROUND_Z + 1) * GROUND_RADIUS);
    }
    for (int wallCount = 0; wallCount < GROUND_Z + 2; wallCount++)
    {
        D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_WALL][GROUND_X * 2 + wallCount].GetMatrix(), -(GROUND_X + 1) * GROUND_RADIUS, GROUND_RADIUS - 2.0f, GROUND_RADIUS * (wallCount * 2 - GROUND_Z - 1));
        D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_WALL][GROUND_X * 2 + wallCount + GROUND_Z + 2].GetMatrix(), (GROUND_X + 1) * GROUND_RADIUS, GROUND_RADIUS - 2.0f, GROUND_RADIUS * (wallCount * 2 - GROUND_Z - 1));
    }
    for (int wallCount = 0; wallCount < WALL_COUNT; wallCount++)
    {
        landformObj[OBJECT_LANDFORM_WALL][wallCount].SetRadius(GROUND_RADIUS * 1.7f);
        landformObj[OBJECT_LANDFORM_WALL][wallCount].SetLength(D3DXVECTOR3(GROUND_RADIUS * 2.0f, GROUND_RADIUS * 2.0f, GROUND_RADIUS * 2.0f));
    }

    // 나무
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][0].GetMatrix(), 5.0f, 1.9f, 20.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][1].GetMatrix(), 15.0f, 1.9f, 15.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][2].GetMatrix(), 20.0f, 1.9f, 10.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][3].GetMatrix(), 10.0f, 1.9f, -10.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][4].GetMatrix(), 20.0f, 1.9f, -20.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][5].GetMatrix(), -5.0f, 1.9f, -25.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][6].GetMatrix(), -15.0f, 1.9f, -15.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][7].GetMatrix(), -20.0f, 1.9f, -10.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][8].GetMatrix(), -25.0f, 1.9f, 15.0f);
    D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_TREE][9].GetMatrix(), -10.0f, 1.9f, 25.0f);
    for (int treeCount = 0; treeCount < TREE_COUNT; treeCount++)
    {
        landformObj[OBJECT_LANDFORM_TREE][treeCount].SetRadius(1.5f);
        landformObj[OBJECT_LANDFORM_TREE][treeCount].SetLength(D3DXVECTOR3(0.05f, 3.0f, 0.05f));
    }
}

// 슬라이더 전체 초기화
void InitSlider(SliderData* sliderInfo)
{
    _SetSlider(sliderInfo, SLIDER_FIELDOFVIEW,       MENU_SLIDER_START, MENU_SLIDER_END);   // 시야각 슬라이더
    _SetSlider(sliderInfo, SLIDER_VIEWFAR,           MENU_SLIDER_START, MENU_SLIDER_END);   // 시야범위 슬라이더
    _SetSlider(sliderInfo, SLIDER_CAMERAROTATESPEED, MENU_SLIDER_START, MENU_SLIDER_END);   // 마우스 회전 감도 슬라이더
    _SetSlider(sliderInfo, SLIDER_BGM,               MENU_SLIDER_START, MENU_SLIDER_END);   // 배경음 볼륨
    _SetSlider(sliderInfo, SLIDER_SE,                MENU_SLIDER_START, MENU_SLIDER_END);   // 효과음 볼륨
}

// 슬라이더 개별 초기화
void _SetSlider(SliderData* sliderInfo, int sliderNum, FLOAT startXPos, FLOAT endXPos)
{
    sliderInfo[sliderNum] = { startXPos + (endXPos - startXPos) * sliderInfo[sliderNum].value, sliderInfo[sliderNum].value, FALSE };    // 슬라이더 정보 입력
    int verticesNum = sliderNum * 20;
    menuSliderVertices[13 + verticesNum].x = menuSliderVertices[14 + verticesNum].x = sliderInfo[sliderNum].clickXPos;                  // 슬라이더 좌표 지정
    menuSliderVertices[16 + verticesNum].x = menuSliderVertices[19 + verticesNum].x = sliderInfo[sliderNum].clickXPos - WIDTH_WINDOW / 10.0f * 0.175f;
    menuSliderVertices[17 + verticesNum].x = menuSliderVertices[18 + verticesNum].x = sliderInfo[sliderNum].clickXPos + WIDTH_WINDOW / 10.0f * 0.175f;
}

// 오브젝트들 초기화
void InitGame(CObject** landformObj, SliderData* sliderInfo, CEnemy** enemyObj, CBullet** bullets, SHORT* mousePos)
{
    InitMatrixTranslation(landformObj);         // 오브젝트 행렬 초기화
    InitSlider(sliderInfo);                     // 슬라이더 초기화

    for (int i = 0; i < 24; i++)            skyBoxVertices[i].position *= (FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f; // 스카이박스 초기화
    for (int i = 0; i < BULLET_MAX; i++)    bullets[i] = NULL;  // 총알 초기화
    for (int i = 0; i < ENEMY_MAX; i++)     enemyObj[i] = NULL; // 적 초기화

    SetCursor(LoadCursor(NULL, IDC_ARROW));                     // 마우스 커서 정보 초기화
    SetCursorPos(WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2);
    mousePos[MOUSE_CLICK_XPOS] = (SHORT)(WIDTH_WINDOW / 2.0f);
    mousePos[MOUSE_CLICK_YPOS] = (SHORT)(HEIGHT_WINDOW / 2.0f);
}