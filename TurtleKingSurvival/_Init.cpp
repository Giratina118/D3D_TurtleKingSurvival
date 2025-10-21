#include "_Init.h"
#include "CEnemy.h"
#include "CObject.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice; // �������� ���� D3D ����̽�

// Direct3D �ʱ�ȭ
HRESULT InitD3D(HWND hWnd, LPDIRECT3D9* g_pD3D)
{
    // ����̽��� �����ϱ����� D3D��ü ����
    if (NULL == (*g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;                // ����̽� ������ ���� ����ü
    ZeroMemory(&d3dpp, sizeof(d3dpp));          // ����ü ����       
    d3dpp.Windowed = TRUE;                      // â���
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // ���� ȿ������ presentarion�� ������ �� �ְ� �ϴ� swap ȿ��
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;    // ������ ����ȭ�� ��忡 ���� �ĸ� ���۸� ����
    d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

    // ���� ����̽��� �����ϴ� �Լ�.
    if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
        return E_FAIL;

    return S_OK;
}

// ���� ���� �ʱ�ȭ
HRESULT InitVB(LPDIRECT3DVERTEXBUFFER9* g_pVB_Array)
{
    _SetVB(sizeof(cubeVertices),        cubeVertices,       &g_pVB_Array[VB_CUBE]);         // ť��(��, ��ֹ�)
    _SetVB(sizeof(groundVertices),      groundVertices,     &g_pVB_Array[VB_GRASS]);        // ��(�ٴ�)
    _SetVB(sizeof(bliboardVertices),    bliboardVertices,   &g_pVB_Array[VB_BILBOARD]);     // ������(����, ����)
    _SetVB(sizeof(skyBoxVertices),      skyBoxVertices,     &g_pVB_Array[VB_SKYBOX]);       // ��ī�̹ڽ�
    _SetVB(sizeof(enemy1Vertices),      enemy1Vertices,     &g_pVB_Array[VB_ENEMY1]);       // ��1
    _SetVB(sizeof(enemyHpBarVertices),  enemyHpBarVertices, &g_pVB_Array[VB_ENEMYHPBAR]);   // ������(�� ü�¹�)
    _SetVB(sizeof(spriteVertices),    spriteVertices,   &g_pVB_Array[VB_BULLETFIRE]);   // �Ѿ� ��ƼŬ(�Ҳ�)
    _SetVB(sizeof(bulletVertices),      bulletVertices,     &g_pVB_Array[VB_BULLET]);       // �Ѿ�

    return S_OK;
}

// �ε��� ���� �ʱ�ȭ
HRESULT InitIB(LPDIRECT3DINDEXBUFFER9* g_pIB_Array)
{
    _SetIB(sizeof(cubeIndices),   cubeIndices,   &g_pIB_Array[IB_CUBE]);    // ť��(��, ��ֹ�)
    _SetIB(sizeof(enemy1Indices), enemy1Indices, &g_pIB_Array[IB_ENEMY1]);  // ��1
    _SetIB(sizeof(bulletIndices), bulletIndices, &g_pIB_Array[IB_BULLET]);  // �Ѿ�

    return S_OK;
}

// ���� ���� �ʱ�ȭ(���� ����)
void _SetVB(UINT verticesSize, CUSTOMVERTEX* vertices, LPDIRECT3DVERTEXBUFFER9* pVB)
{
    VOID* pVertices;
    g_pd3dDevice->CreateVertexBuffer(verticesSize, 0, CUSTOMVERTEX::FVF, D3DPOOL_DEFAULT, pVB, NULL);
    (*pVB)->Lock(0, verticesSize, (void**)&pVertices, 0);   // Lock(lock�� ������, ũ��, ������ �ּ�, 0)
    memcpy(pVertices, vertices, verticesSize);              // ���ۿ� ���� �ִ´�
    (*pVB)->Unlock();
}

// �ε��� ���� �ʱ�ȭ(���� ����)
void _SetIB(UINT indicesSize, CUSTOMINDEX_LIST* indices, LPDIRECT3DINDEXBUFFER9* pIB)
{
    VOID* pIndices;
    g_pd3dDevice->CreateIndexBuffer(indicesSize, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, pIB, NULL);
    (*pIB)->Lock(0, indicesSize, (void**)&pIndices, 0);
    memcpy(pIndices, indices, indicesSize);
    (*pIB)->Unlock();
}


// ȯ�� ������Ʈ�� �ʱ�ȭ
void InitMatrixTranslation(CObject** landformObj)
{
    // ��(�ܵ�)
    for (int groundX = 0; groundX < GROUND_X; groundX++)
    {
        for (int groundZ = 0; groundZ < GROUND_Z; groundZ++)
        {
            D3DXMatrixTranslation(landformObj[OBJECT_LANDFORM_GROUND][groundX * GROUND_Z + groundZ].GetMatrix(), GROUND_RADIUS * (groundX * 2 - GROUND_X + 1), -2.0f, GROUND_RADIUS * (groundZ * 2 - GROUND_Z + 1));
            landformObj[OBJECT_LANDFORM_GROUND][groundX * GROUND_Z + groundZ].SetRadius(GROUND_RADIUS);
            landformObj[OBJECT_LANDFORM_GROUND][groundX * GROUND_Z + groundZ].SetLength(D3DXVECTOR3(GROUND_RADIUS * 2.0f, 0.5f, GROUND_RADIUS * 2.0f));
        }
    }

    // ��
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

    // ����
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

// �����̴� ��ü �ʱ�ȭ
void InitSlider(SliderData* sliderInfo)
{
    _SetSlider(sliderInfo, SLIDER_FIELDOFVIEW,       MENU_SLIDER_START, MENU_SLIDER_END);   // �þ߰� �����̴�
    _SetSlider(sliderInfo, SLIDER_VIEWFAR,           MENU_SLIDER_START, MENU_SLIDER_END);   // �þ߹��� �����̴�
    _SetSlider(sliderInfo, SLIDER_CAMERAROTATESPEED, MENU_SLIDER_START, MENU_SLIDER_END);   // ���콺 ȸ�� ���� �����̴�
    _SetSlider(sliderInfo, SLIDER_BGM,               MENU_SLIDER_START, MENU_SLIDER_END);   // ����� ����
    _SetSlider(sliderInfo, SLIDER_SE,                MENU_SLIDER_START, MENU_SLIDER_END);   // ȿ���� ����
}

// �����̴� ���� �ʱ�ȭ
void _SetSlider(SliderData* sliderInfo, int sliderNum, FLOAT startXPos, FLOAT endXPos)
{
    sliderInfo[sliderNum] = { startXPos + (endXPos - startXPos) * sliderInfo[sliderNum].value, sliderInfo[sliderNum].value, FALSE };    // �����̴� ���� �Է�
    int verticesNum = sliderNum * 20;
    menuSliderVertices[13 + verticesNum].x = menuSliderVertices[14 + verticesNum].x = sliderInfo[sliderNum].clickXPos;                  // �����̴� ��ǥ ����
    menuSliderVertices[16 + verticesNum].x = menuSliderVertices[19 + verticesNum].x = sliderInfo[sliderNum].clickXPos - WIDTH_WINDOW / 10.0f * 0.175f;
    menuSliderVertices[17 + verticesNum].x = menuSliderVertices[18 + verticesNum].x = sliderInfo[sliderNum].clickXPos + WIDTH_WINDOW / 10.0f * 0.175f;
}

// ������Ʈ�� �ʱ�ȭ
void InitGame(CObject** landformObj, SliderData* sliderInfo, CEnemy** enemyObj, CBullet** bullets, SHORT* mousePos)
{
    InitMatrixTranslation(landformObj);         // ������Ʈ ��� �ʱ�ȭ
    InitSlider(sliderInfo);                     // �����̴� �ʱ�ȭ

    for (int i = 0; i < 24; i++)            skyBoxVertices[i].position *= (FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f; // ��ī�̹ڽ� �ʱ�ȭ
    for (int i = 0; i < BULLET_MAX; i++)    bullets[i] = NULL;  // �Ѿ� �ʱ�ȭ
    for (int i = 0; i < ENEMY_MAX; i++)     enemyObj[i] = NULL; // �� �ʱ�ȭ

    SetCursor(LoadCursor(NULL, IDC_ARROW));                     // ���콺 Ŀ�� ���� �ʱ�ȭ
    SetCursorPos(WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2);
    mousePos[MOUSE_CLICK_XPOS] = (SHORT)(WIDTH_WINDOW / 2.0f);
    mousePos[MOUSE_CLICK_YPOS] = (SHORT)(HEIGHT_WINDOW / 2.0f);
}