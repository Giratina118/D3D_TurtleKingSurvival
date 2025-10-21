#include "_UpdateGameProc.h"
#include "_UIManager.h"
#include "_TransformMatrix.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "_SoundManager.h"

FLOAT enemyCreateTimer = 0.0f;          // 적 생성 타이머(타이머가 딜레이만큼 차오르면 적 생성)
FLOAT enemyCreateDelay = 5.0f;          // 적 생성 딜레이
int nowBulletMakingArrayNumber = 0;     // 총알 생성(몇 번째 배열로 들어가는지)
extern SliderData sliderInfo[SLIDER_MAX];

// 시간 흐름
void FlowTime(SceneState* sceneState, DateInfo* dateInfo, Timer timer, int* score, CPlayer* playerObj)
{
    if (!sceneState->clickKey[KEY_TIMESTOP])                    // 타이머 업데이트
    {
        dateInfo->clock += timer.GetDeltaTime();
        enemyCreateTimer += timer.GetDeltaTime();
        if (UpdateDateInfo(dateInfo, &enemyCreateDelay, score)) // 날짜 정보 업데이트
            playerObj->TakeDamage(10000);
        UpdateSunPosition(dateInfo);                            // 시간, 태양 위치 업데이트
    }
}

// 총알 생성
void CreateBullet(CBullet* bullets[BULLET_MAX], D3DXMATRIX matrix, D3DXVECTOR3 bulletPos, D3DXVECTOR3 bulletDir, int bulletSizeLevel, int bulletDamage, int shooter)
{
    if (bullets[nowBulletMakingArrayNumber] == NULL)
        bullets[nowBulletMakingArrayNumber] = new CBullet(matrix, bulletPos, bulletDir, bulletSizeLevel, 20.0f, bulletDamage, shooter);

    nowBulletMakingArrayNumber++;
    if (nowBulletMakingArrayNumber == BULLET_MAX)   nowBulletMakingArrayNumber = 0;

    SoundPlay("Sound\\gun_fire.wav", 0.5f * sliderInfo[SLIDER_SE].value, 1); // 총소리
}

// 총알 업데이트
void UpdateBulletProc(CBullet** bullets, Timer timer)
{
    for (int bulletCount = 0; bulletCount < BULLET_MAX; bulletCount++)
    {
        if (bullets[bulletCount] == NULL)
            continue;

        if (bullets[bulletCount]->IsLifeTimeOver()) // 총알 제거
        {
            delete bullets[bulletCount];
            bullets[bulletCount] = NULL;
        }
        else
            bullets[bulletCount]->UpdateBulletState(timer);
    }
}

// 적 생성
void CreateEnemy(CEnemy** enemyObj, DateInfo dateInfo, int* nowGameData, int killCountTemp)
{
    if (nowGameData[NOWGAME_NOWENEMYCOUNT] == 0)
        enemyCreateTimer += enemyCreateDelay * 1.5f;

    if (nowGameData[NOWGAME_KILLCOUNT] > killCountTemp)
        enemyCreateTimer += enemyCreateDelay * 0.5f;

    if (enemyCreateTimer < enemyCreateDelay)
        return;

    enemyCreateTimer -= enemyCreateDelay;

    for (int enemyNum = 0; enemyNum < ENEMY_MAX; enemyNum++)
    {
        if (enemyObj[enemyNum] != NULL)
            continue;

        int enemyType = rand() % 3;

        enemyObj[enemyNum] = new CEnemy(enemyType, dateInfo);
        nowGameData[NOWGAME_NOWENEMYCOUNT]++;
        break;
    }
}

// 적 업데이트
void UpdateEnemyProc(CEnemy** enemyObj, CPlayer* playerObj, CBullet** bullets, Timer timer, SceneState* sceneState, int* nowGameData, DateInfo dateInfo)
{
    for (int enemyNum = 0; enemyNum < ENEMY_MAX; enemyNum++)
    {
        if (enemyObj[enemyNum] == NULL)
            continue;

        if (!enemyObj[enemyNum]->GetAlive())
        {
            nowGameData[NOWGAME_SCORE] += enemyObj[enemyNum]->GetScore();
            playerObj->TakeExp(enemyObj[enemyNum]->GetEXP(), sceneState);

            delete enemyObj[enemyNum];
            enemyObj[enemyNum] = NULL;
            nowGameData[NOWGAME_KILLCOUNT]++;
            nowGameData[NOWGAME_NOWENEMYCOUNT]--;
            continue;
        }

        enemyObj[enemyNum]->UpdateEnemy(timer, playerObj, bullets, dateInfo);
    }
}


// 키 입력
void __KeyProc(Timer timer, CPlayer* playerObj)
{
    FLOAT playerSpeed = 5.0f * timer.GetDeltaTime();
    // camera, player
    if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)    TranslateObject(playerObj, MOVE_RIGHT, playerSpeed);
    if (GetKeyState(VK_LEFT) & 0x80  || GetKeyState('A') & 0x80)    TranslateObject(playerObj, MOVE_LEFT, playerSpeed);
    if (GetKeyState(VK_UP) & 0x80    || GetKeyState('W') & 0x80)    TranslateObject(playerObj, MOVE_FRONT, playerSpeed);
    if (GetKeyState(VK_DOWN) & 0x80  || GetKeyState('S') & 0x80)    TranslateObject(playerObj, MOVE_BACK, playerSpeed);
}

bool cullingOn = true; // 절두체 컬링 보여주기용 테스트 변수

// 키보드 단축키
void ClickShortCutKey(HWND hWnd, WPARAM wParam, SceneState* sceneState, CPlayer* playerObj)
{
    if (sceneState->nowSceneType != SCENE_GAME)
        return;

    if (wParam == VK_SPACE && !playerObj->GetIsJumping()) _JumpProcess(playerObj); // 스페이스바로 점프

    switch (wParam) // 단축키
    {
    case '1':       // 카메라 탑뷰 전환
    case '2':       // 램프(pointLight) on/off
    case '3':       // 손전등(spotLight) on/off
    case '4':       // 태양(directionalLight) on/off
        sceneState->clickKey[wParam - 49] = !sceneState->clickKey[wParam - 49];
        break;

    case VK_F1:     // 도움말 on/off
        sceneState->openHelp = !sceneState->openHelp;
        break;

    case VK_TAB:    // 마우스 조준 모드 on/off
        sceneState->mouseCrossFocusMode = !sceneState->mouseCrossFocusMode;
        sceneState->tempMouseCrossFocusMode = sceneState->mouseCrossFocusMode;

        TurnOnOffCursor(!sceneState->mouseCrossFocusMode);
        break;

    case VK_ESCAPE: // 메뉴 on/off
        MenuOnOff();
        break;

    case 'Q':
        DestroyWindow(hWnd);

    case '5':
        playerObj->TakeExp(1000, sceneState);
        break;

    case '6': // 절두체 컬링 테스트용
        cullingOn = !cullingOn;
    }
}

// 카메라 마우스 이동
void CameraTransform(SHORT* mousePos, FLOAT mouseSensivity, CPlayer* playerObj)
{
    float cameraMoveSpeed = 0.025f;
    float cameraRotateSpeed = 0.1f + 0.2f * mouseSensivity;

    int mouseMoveX = mousePos[MOUSE_DRAG_XPOS] - mousePos[MOUSE_CLICK_XPOS];
    int mouseMoveY = mousePos[MOUSE_DRAG_YPOS] - mousePos[MOUSE_CLICK_YPOS];

    if (mouseMoveX != 0)    RotationObject(playerObj->GetMatrix(), Y_PLUS_ROT, mouseMoveX * cameraRotateSpeed, TRUE);

    mousePos[MOUSE_CLICK_XPOS] = mousePos[MOUSE_DRAG_XPOS];
    mousePos[MOUSE_CLICK_YPOS] = mousePos[MOUSE_DRAG_YPOS];
}