#include "_Init.h"              // 정점, 인덱스, 배열 초기화
#include "_TransformMatrix.h"   // 객체 이동, 회전
#include "_Render.h"            // 그리기
#include "_UIManager.h"         // UI 동작
#include "_CleanUp.h"           // 객체 해제
#include "_UpdateGameProc.h"    // 게임 진행 업데이트
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "_SoundManager.h"

#pragma warning(disable : 4996)

//d3d9.lib, d3dx9.lib

//                                               // 이제 해야할거
// ui 꾸미기,  폰트 예쁜걸로 넣기
// 범위 지정할 때 형식 통일하기
// 동영상 촬영

// 
// 코드 정리, 최적화, 주석달기     transformMatrix까지 했음


HWND                    g_hwnd = NULL;
LPDIRECT3D9             g_pD3D = NULL;                              // D3D 디바이스를 생성할 D3D 객체 변수
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;                        // 렌더링에 사용될 D3D 디바이스

LPDIRECT3DVERTEXBUFFER9 g_pVB_Array[VB_MAX] = { NULL, };            // 정점 버퍼 모아놓은 배열     enum VertexBufferArrayTypeEnum
LPDIRECT3DINDEXBUFFER9  g_pIB_Array[IB_MAX] = { NULL, };            // 인덱스 버퍼 모아놓은 배열   enum IndexBufferArrayTypeEnum
LPDIRECT3DTEXTURE9      g_pTEXTURE_Array[TEXTURE_MAX] = { NULL, };  // 텍스처 모아놓은 배열        enum TextureArrayTypeEnum

CPlayer playerObj(D3DXMATRIX( 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 3, 0, 1 ), D3DXVECTOR3( 1, 2.5f, 1 ), 1);   // 플레이어(카메라 시점) 오브젝트
CEnemy* enemyObj[ENEMY_MAX];            // 적 오브젝트 (현재 상한 32개)
CBullet* bullets[BULLET_MAX];           // 총알 (현재 상한 512개)

CObject groundObj[GROUND_X * GROUND_Z]; // 땅(바닥) 오브젝트
CObject wallObj[WALL_COUNT];            // 벽 오브젝트
CObject treeObj[TREE_COUNT];            // 나무(빌보드) 오브젝트
CObject obstacleObj[OBSTACLE_COUNT];    // 장애물 오브젝트
CObject* landformObj[OBJECT_LANDFORM_MAX] = { groundObj, wallObj, treeObj, obstacleObj };   // 지형지물 오브젝트들 모아서 관리

Timer timer;                                        // 타이머
DateInfo dateInfo{ 0.0f, 1, 1, { 0, 0, 0.1f } };    // 시각, 월, 일, 태양벡터

SliderData sliderInfo[SLIDER_MAX];                  // 슬라이더

// 현재 화면, 메뉴, fps, 도움말, 레벨업 창 상태, 마우스 십자모드(기본, temp), 마우스 회전 모드(기본, temp), 키보드 단축키(enum ShortcutKeyTypeEnum)
SceneState sceneState = { SCENE_TITLE, 0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, {FALSE, TRUE, TRUE, TRUE, FALSE, FALSE} };
int nowGameData[NOWGAME_MAX];
bool isBtnOnMouse[BUTTON_MAX] = { FALSE, };

SaveData saveData[10];      // 최고점수, 킬 수, 생존 달, 생존 일, 이름
struct tm* realTimeInfo;    // 시간 정보(게임 내 X, 현실 시간)
BOOL shotBullet = TRUE;     // 총알을 쏠 수 있는지 여부

IXAudio2* pXAudio2;
IXAudio2MasteringVoice* pMasteringVoice;    // 마스터 보이스, 1개, 소스 보이스를 정리해서 출력
IXAudio2SourceVoice* pSourceVoice[10];      // bgm이나 효과음, 같은 효과음을 여러번 울리려면 그만큼 만들어야 한다
WaveData waveData[2];

int bgmVolumeSize = 0.5f, seVolumeSize = 0.5f;


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static SHORT mousePos[4] = {0, }; // 마우스 클릭 시 좌표(x, y), // 마우스 드래그 시 좌표(x, y)

    switch (msg)
    {
    case WM_CREATE:
    {
        srand((unsigned int)time(NULL));
        int FPS = 60;
        LoadFile(&FPS, &nowGameData[NOWGAME_BESTSCORE], saveData, sliderInfo);  // 파일 로드
        timer.Init(FPS);                                                        // 타이머 초기화
        InitGame(landformObj, sliderInfo, enemyObj, bullets, mousePos);         // 오브젝트들, 마우스 초기화

        InitSound();                                                            // 사운드 관련 초기화
        SoundPlay("Sound\\bgm.wav", sliderInfo[SLIDER_BGM].value, 0);           // 배경음악 재생
        break;
    }
    case WM_LBUTTONDOWN:
        mousePos[MOUSE_CLICK_XPOS] = LOWORD(lParam);
        mousePos[MOUSE_CLICK_YPOS] = HIWORD(lParam);
        SetCapture(hWnd);

        MouseClickTitleScene(mousePos); // 타이틀 화면 클릭
        MouseClickResultScene(mousePos, enemyObj, bullets, nowGameData, &dateInfo); // 결과 화면 클릭
        MouseClickGameScene(mousePos, nowGameData, saveData, &dateInfo, realTimeInfo, sliderInfo, &shotBullet, &timer, bullets); // 게임 화면 클릭
        break;

    case WM_RBUTTONDOWN:
        if (sceneState.nowSceneType != SCENE_GAME)  break;
        mousePos[MOUSE_CLICK_XPOS] = LOWORD(lParam);
        mousePos[MOUSE_CLICK_YPOS] = HIWORD(lParam);
        sceneState.rotateFreeze = !sceneState.rotateFreeze;
        SetCapture(hWnd);
        break;

    case WM_MOUSEMOVE:
        mousePos[MOUSE_DRAG_XPOS] = LOWORD(lParam);
        mousePos[MOUSE_DRAG_YPOS] = HIWORD(lParam);

        MouseMoveTitleScene(mousePos);                  // 타이틀씬 마우스 이동
        MouseMoveResultScene(mousePos);                 // 결과씬 마우스 이동
        MouseMoveGameScene(hWnd, mousePos, sliderInfo); // 게임씬 마우스 이동
        break;

    case WM_LBUTTONUP:
        if (sceneState.nowSceneType == SCENE_GAME) // 슬라이더 드래그 하고 뗄 때 슬라이더 핸들 위치 지정
            for (int sliderDrag = 0; sliderDrag < SLIDER_MAX; sliderDrag++) sliderInfo[sliderDrag].onDragHandle = FALSE;
        ReleaseCapture();
        break;

    case WM_RBUTTONUP:
        ReleaseCapture();
        break;

    case WM_KEYDOWN:
        ClickShortCutKey(hWnd, wParam, &sceneState, &playerObj); // 키보드 단축키
        break;

    case WM_DESTROY:
        SaveFile(timer.GetFPS(), saveData, sliderInfo); // 파일 저장
        Cleanup(&g_pD3D, &g_pd3dDevice, g_pVB_Array, g_pIB_Array, g_pTEXTURE_Array, bullets, enemyObj);
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        ValidateRect(hWnd, NULL);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "D3D_Project_MH", NULL };
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow("D3D_Project_MH", "D3D Project MH",
        WS_OVERLAPPEDWINDOW, 0, 0, WIDTH_WINDOW, HEIGHT_WINDOW,
        GetDesktopWindow(), NULL, wc.hInstance, NULL);
    g_hwnd = hWnd;

    if (SUCCEEDED(InitD3D(hWnd, &g_pD3D)) && SUCCEEDED(InitVB(g_pVB_Array)) && SUCCEEDED(InitIB(g_pIB_Array)))
    {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        time_t realTime;
        realTime = time(NULL);
        realTimeInfo = localtime(&realTime);

        // 텍스처 파일 경로
        char texturePath[TEXTURE_MAX][64] = {
        "Images\\tree.png", "Images\\grass.png", "Images\\wall.png",
        "Images\\skyBoxRight.png", "Images\\skyBoxLeft.png", "Images\\skyBoxTop.png", "Images\\skyBoxBottom.png", "Images\\skyBoxFront.png", "Images\\skyBoxBack.png",
        "Images\\UI\\playButton.png", "Images\\UI\\rightChevron1.png", "Images\\UI\\rightChevron2.png", "Images\\UI\\rightChevron3.png", "Images\\UI\\menuButton.png",
        "Images\\UI\\buttonBlue.png", "Images\\UI\\buttonRed.png", "Images\\UI\\sliderHandle.png", "Images\\UI\\sliderHorizontal_blue.png", "Images\\UI\\sliderHorizontal_gray.png",
        "Images\\UI\\hpBarGreen.png", "Images\\UI\\hpBarRed.png", "Images\\UI\\expBarBlue.png", "Images\\UI\\expBarGray.png", "Images\\fire.png", "Images\\UI\\crossLine.png",
        "Images\\turtle.png", "Images\\bulletColor.png", "Images\\UI\\outlineRect.png", "Images\\UI\\MenuBG.png", "Images\\UI\\MenuBtn.png", "Images\\UI\\LvUp_BG_Brown.png", 
        "Images\\UI\\LvUp_BG_White.png", "Images\\UI\\buttonBrown.png", "Images\\UI\\buttonBrownLight.png", "Images\\UI\\buttonBlue_onMouse.png", "Images\\UI\\buttonRed_onMouse.png"};

        for (int textureNum = 0; textureNum < TEXTURE_MAX; textureNum++)
            D3DXCreateTextureFromFile(g_pd3dDevice, texturePath[textureNum], &g_pTEXTURE_Array[textureNum]);

        // 폰트
        int fontSize = 0;
        LPD3DXFONT font;
        TEXTMETRICA pTextMetrics;

        if (WIDTH_WINDOW > HEIGHT_WINDOW)   fontSize = HEIGHT_WINDOW / 40;
        else                                fontSize = WIDTH_WINDOW / 40;
        D3DXCreateFont(g_pd3dDevice, fontSize, 0, FW_MEDIUM, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Batang", &font);
        // Malgun Gothic, Gulim, Dotum, Batang, Gungsuh

        font->GetTextMetricsA(&pTextMetrics);

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                DispatchMessage(&msg);
            }
            else
            {
                if (!timer.Update()) continue;

                if (sceneState.nowSceneType != SCENE_GAME || sceneState.isOpenMenu || sceneState.onLevelUpScreen) // 메뉴 열려있으면 시간 멈춤
                {
                    Render(landformObj, bullets, sliderInfo, font, pTextMetrics, dateInfo, sceneState); // 그리기
                    continue;
                }

                FlowTime(&sceneState, &dateInfo, timer, &nowGameData[NOWGAME_SCORE], &playerObj); // 시간 흐름

                __KeyProc(timer, &playerObj);       // 키 입력
                if (GetKeyState(VK_LBUTTON) & 0x80 && shotBullet && !sceneState.isOpenMenu && !sceneState.onLevelUpScreen && playerObj.OverAttackDelay())
                    playerObj.Attack(bullets);      // 플레이어 공격
                playerObj.UpdatePlayer(timer);      // 플레이어 업데이트
                playerObj.TakeExp(0, &sceneState);  // 잔여 경험치 처리

                UpdateBulletProc(bullets, timer);   // 총알 업데이트
                
                int killCountTemp = nowGameData[NOWGAME_KILLCOUNT];
                UpdateEnemyProc(enemyObj, &playerObj, bullets, timer, &sceneState, nowGameData, dateInfo); // 적 업데이트
                CreateEnemy(enemyObj, dateInfo, nowGameData, killCountTemp); // 적 생산

                _Gravity(&playerObj, enemyObj);     // 중력 적용

                if (playerObj.GetHpNow() < 1)       // 게임 오버 판정, 결과 저장
                    ToTitle(nowGameData, saveData, dateInfo, realTimeInfo);

                Render(landformObj, bullets, sliderInfo, font, pTextMetrics, dateInfo, sceneState); // 그리기
            }
        }
        font->Release();
    }

    UnregisterClass("D3D_Project_MH", wc.hInstance);
    return 0;
}