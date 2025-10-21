#include "_UpdateGameProc.h"
#include "_UIManager.h"
#include "_TransformMatrix.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "_SoundManager.h"

FLOAT enemyCreateTimer = 0.0f;          // �� ���� Ÿ�̸�(Ÿ�̸Ӱ� �����̸�ŭ �������� �� ����)
FLOAT enemyCreateDelay = 5.0f;          // �� ���� ������
int nowBulletMakingArrayNumber = 0;     // �Ѿ� ����(�� ��° �迭�� ������)
extern SliderData sliderInfo[SLIDER_MAX];

// �ð� �帧
void FlowTime(SceneState* sceneState, DateInfo* dateInfo, Timer timer, int* score, CPlayer* playerObj)
{
    if (!sceneState->clickKey[KEY_TIMESTOP])                    // Ÿ�̸� ������Ʈ
    {
        dateInfo->clock += timer.GetDeltaTime();
        enemyCreateTimer += timer.GetDeltaTime();
        if (UpdateDateInfo(dateInfo, &enemyCreateDelay, score)) // ��¥ ���� ������Ʈ
            playerObj->TakeDamage(10000);
        UpdateSunPosition(dateInfo);                            // �ð�, �¾� ��ġ ������Ʈ
    }
}

// �Ѿ� ����
void CreateBullet(CBullet* bullets[BULLET_MAX], D3DXMATRIX matrix, D3DXVECTOR3 bulletPos, D3DXVECTOR3 bulletDir, int bulletSizeLevel, int bulletDamage, int shooter)
{
    if (bullets[nowBulletMakingArrayNumber] == NULL)
        bullets[nowBulletMakingArrayNumber] = new CBullet(matrix, bulletPos, bulletDir, bulletSizeLevel, 20.0f, bulletDamage, shooter);

    nowBulletMakingArrayNumber++;
    if (nowBulletMakingArrayNumber == BULLET_MAX)   nowBulletMakingArrayNumber = 0;

    SoundPlay("Sound\\gun_fire.wav", 0.5f * sliderInfo[SLIDER_SE].value, 1); // �ѼҸ�
}

// �Ѿ� ������Ʈ
void UpdateBulletProc(CBullet** bullets, Timer timer)
{
    for (int bulletCount = 0; bulletCount < BULLET_MAX; bulletCount++)
    {
        if (bullets[bulletCount] == NULL)
            continue;

        if (bullets[bulletCount]->IsLifeTimeOver()) // �Ѿ� ����
        {
            delete bullets[bulletCount];
            bullets[bulletCount] = NULL;
        }
        else
            bullets[bulletCount]->UpdateBulletState(timer);
    }
}

// �� ����
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

// �� ������Ʈ
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


// Ű �Է�
void __KeyProc(Timer timer, CPlayer* playerObj)
{
    FLOAT playerSpeed = 5.0f * timer.GetDeltaTime();
    // camera, player
    if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)    TranslateObject(playerObj, MOVE_RIGHT, playerSpeed);
    if (GetKeyState(VK_LEFT) & 0x80  || GetKeyState('A') & 0x80)    TranslateObject(playerObj, MOVE_LEFT, playerSpeed);
    if (GetKeyState(VK_UP) & 0x80    || GetKeyState('W') & 0x80)    TranslateObject(playerObj, MOVE_FRONT, playerSpeed);
    if (GetKeyState(VK_DOWN) & 0x80  || GetKeyState('S') & 0x80)    TranslateObject(playerObj, MOVE_BACK, playerSpeed);
}

bool cullingOn = true; // ����ü �ø� �����ֱ�� �׽�Ʈ ����

// Ű���� ����Ű
void ClickShortCutKey(HWND hWnd, WPARAM wParam, SceneState* sceneState, CPlayer* playerObj)
{
    if (sceneState->nowSceneType != SCENE_GAME)
        return;

    if (wParam == VK_SPACE && !playerObj->GetIsJumping()) _JumpProcess(playerObj); // �����̽��ٷ� ����

    switch (wParam) // ����Ű
    {
    case '1':       // ī�޶� ž�� ��ȯ
    case '2':       // ����(pointLight) on/off
    case '3':       // ������(spotLight) on/off
    case '4':       // �¾�(directionalLight) on/off
        sceneState->clickKey[wParam - 49] = !sceneState->clickKey[wParam - 49];
        break;

    case VK_F1:     // ���� on/off
        sceneState->openHelp = !sceneState->openHelp;
        break;

    case VK_TAB:    // ���콺 ���� ��� on/off
        sceneState->mouseCrossFocusMode = !sceneState->mouseCrossFocusMode;
        sceneState->tempMouseCrossFocusMode = sceneState->mouseCrossFocusMode;

        TurnOnOffCursor(!sceneState->mouseCrossFocusMode);
        break;

    case VK_ESCAPE: // �޴� on/off
        MenuOnOff();
        break;

    case 'Q':
        DestroyWindow(hWnd);

    case '5':
        playerObj->TakeExp(1000, sceneState);
        break;

    case '6': // ����ü �ø� �׽�Ʈ��
        cullingOn = !cullingOn;
    }
}

// ī�޶� ���콺 �̵�
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