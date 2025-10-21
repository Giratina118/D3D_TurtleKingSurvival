#include "_UIManager.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "Timer.h"
#include "_TransformMatrix.h"
#include "_UpdateGameProc.h"
#include "_SoundManager.h"

extern HWND  g_hwnd;
extern FLOAT buttonSize;    // ��ư�� ũ��, Ŭ�� �� ��� ��ġ(��ư)�� Ŭ���Ǿ����� �Ǻ��� ���� ���

extern LPDIRECT3DVERTEXBUFFER9 g_pVB_Array[VB_MAX];
extern CPlayer playerObj;
extern SceneState sceneState;
extern bool isBtnOnMouse[BUTTON_MAX];

int cursorShow = 1;


// Ÿ��Ʋ�� ���콺 Ŭ��
void MouseClickTitleScene(SHORT* mousePos)
{
    if (sceneState.nowSceneType != SCENE_TITLE && sceneState.nowSceneType != SCENE_SCORE)                                       // Ÿ��Ʋ�� �ƴϸ� ������
        return;

    if (mousePos[MOUSE_CLICK_XPOS] < titleSceneVertices[4].x || mousePos[MOUSE_CLICK_XPOS] > titleSceneVertices[6].x)           // ��ư Ŭ�� �ƴϸ� ������
        return;

    if (mousePos[MOUSE_CLICK_YPOS] > titleSceneVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < titleSceneVertices[6].y)           // ���� ��ư
        sceneState.nowSceneType = SCENE_GAME;
    else if (mousePos[MOUSE_CLICK_YPOS] > titleSceneVertices[8].y && mousePos[MOUSE_CLICK_YPOS] < titleSceneVertices[10].y)     // ���� ��ư
    {
        if (sceneState.nowSceneType == SCENE_TITLE)    sceneState.nowSceneType = SCENE_SCORE;
        else                                            sceneState.nowSceneType = SCENE_TITLE;
    }
    else if (mousePos[MOUSE_CLICK_YPOS] > titleSceneVertices[12].y && mousePos[MOUSE_CLICK_YPOS] < titleSceneVertices[14].y)    // ���� ��ư
        DestroyWindow(g_hwnd);
}

// ����� ���콺 Ŭ��
void MouseClickResultScene(SHORT* mousePos, CEnemy** enemyObj, CBullet** bullets, int* nowGameData, DateInfo* dateInfo)
{
    if (sceneState.nowSceneType != SCENE_RESULT) // ����� �ƴϸ� ������
        return;

    if (mousePos[MOUSE_CLICK_XPOS] < resultSceneVertices[4].x || mousePos[MOUSE_CLICK_XPOS] > resultSceneVertices[6].x || 
        mousePos[MOUSE_CLICK_YPOS] < resultSceneVertices[4].y || mousePos[MOUSE_CLICK_YPOS] > resultSceneVertices[6].y)
        return; // ��������(Ÿ��Ʋ��) ��ư �������� �� if�� �������� ���

    nowGameData[NOWGAME_SCORE] = nowGameData[NOWGAME_KILLCOUNT] = 0;
    *dateInfo = { 0.0f, 1, 1, { 0, 0, 0.1f } };

    playerObj.SettingInfo();
    playerObj.TakeDamage(0);
    for (int enemyCount = 0; enemyCount < ENEMY_MAX; enemyCount++)      // �� ���� delete
    {
        if (enemyObj[enemyCount] != NULL)
        {
            delete enemyObj[enemyCount];
            enemyObj[enemyCount] = NULL;
        }
    }
    for (int bulletCount = 0; bulletCount < BULLET_MAX; bulletCount++)  // �Ѿ� delete
    {
        if (bullets[bulletCount] != NULL)
        {
            delete bullets[bulletCount];
            bullets[bulletCount] = NULL;
        }
    }
    sceneState.nowSceneType = SCENE_TITLE;
}

// ���Ӿ� ���콺 Ŭ��
void MouseClickGameScene(SHORT* mousePos, int* nowGameData, SaveData* saveData, DateInfo* dateInfo, tm* realTimeInfo, SliderData* sliderInfo, BOOL* shotBullet, Timer* timer, CBullet** bullets)
{
    if (sceneState.nowSceneType != SCENE_GAME) // ���Ӿ� �ƴϸ� ������
        return;

    // �޴����� �÷��̾� ���� / ���� ��ȯ
    if (sceneState.isOpenMenu && mousePos[MOUSE_CLICK_XPOS] > menuVertices[4].x && mousePos[MOUSE_CLICK_XPOS] < menuVertices[5].x)
    {
        if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[6].y)       sceneState.isOpenMenu = 1;
        else if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[8].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[10].y) sceneState.isOpenMenu = 2;
        sceneState.clickSetFPS = FALSE;
    }

    // �޴����� Ÿ��Ʋ�� ������ ��ư
    if (sceneState.isOpenMenu == 2 && mousePos[MOUSE_CLICK_XPOS] > menuVertices[12].x && mousePos[MOUSE_CLICK_XPOS] < menuVertices[14].x && 
        mousePos[MOUSE_CLICK_YPOS] > menuVertices[12].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[14].y)
        ToTitle(nowGameData, saveData, *dateInfo, realTimeInfo);

    if (!sceneState.clickSetFPS)
        OnClickMenuSlider(sceneState.isOpenMenu, mousePos, sliderInfo); // �޴� - ���� �����̴� Ŭ��
    OnClickTimeAndMenuButton(mousePos, shotBullet, dateInfo); // ���� ��ư Ŭ�� (�ð� ����, �޴�)
    OnClickLevelupBonusCard(mousePos); // ������ Ŭ��
    OnClickChangeFPS(mousePos, timer); // FPS ����

    if (shotBullet && !sceneState.isOpenMenu && !sceneState.onLevelUpScreen && playerObj.OverAttackDelay())
        playerObj.Attack(bullets); // �Ѿ� �߻�
}


// Ÿ��Ʋ�� ���콺 �̵�
void MouseMoveTitleScene(SHORT* mousePos)
{
    if (sceneState.nowSceneType != SCENE_TITLE) // Ÿ��Ʋ�� �ƴϸ� ������
        return;

    // ���콺�� ��ư ���� ������ �ø��� ��ư�� ���� ������� ���ϵ���
    if (mousePos[MOUSE_DRAG_YPOS] > titleSceneVertices[4].y && mousePos[MOUSE_DRAG_YPOS] < titleSceneVertices[6].y &&
        mousePos[MOUSE_DRAG_XPOS] > titleSceneVertices[4].x && mousePos[MOUSE_DRAG_XPOS] < titleSceneVertices[6].x)     // ���� ��ư
        isBtnOnMouse[BUTTON_PLAY] = TRUE;
    else if (isBtnOnMouse[BUTTON_PLAY])     isBtnOnMouse[BUTTON_PLAY] = FALSE;

    if (mousePos[MOUSE_DRAG_YPOS] > titleSceneVertices[8].y && mousePos[MOUSE_DRAG_YPOS] < titleSceneVertices[10].y &&
        mousePos[MOUSE_DRAG_XPOS] > titleSceneVertices[8].x && mousePos[MOUSE_DRAG_XPOS] < titleSceneVertices[10].x)    // ���� ��ư
        isBtnOnMouse[BUTTON_SCORE] = TRUE;
    else if (isBtnOnMouse[BUTTON_SCORE])    isBtnOnMouse[BUTTON_SCORE] = FALSE;

    if (mousePos[MOUSE_DRAG_YPOS] > titleSceneVertices[12].y && mousePos[MOUSE_DRAG_YPOS] < titleSceneVertices[14].y &&
        mousePos[MOUSE_DRAG_XPOS] > titleSceneVertices[12].x && mousePos[MOUSE_DRAG_XPOS] < titleSceneVertices[14].x)   // ���� ��ư
        isBtnOnMouse[BUTTON_END] = TRUE;
    else if (isBtnOnMouse[BUTTON_END])      isBtnOnMouse[BUTTON_END] = FALSE;
}

// ����� ���콺 �̵�
void MouseMoveResultScene(SHORT* mousePos)
{
    if (sceneState.nowSceneType != SCENE_RESULT) // ����� �ƴϸ� ������
        return;

    // ���콺�� ��ư ���� ������ �ø��� ��ư�� ���� ������� ���ϵ���
    if (mousePos[MOUSE_DRAG_XPOS] > resultSceneVertices[4].x && mousePos[MOUSE_DRAG_XPOS] < resultSceneVertices[6].x &&
        mousePos[MOUSE_DRAG_YPOS] > resultSceneVertices[4].y && mousePos[MOUSE_DRAG_YPOS] < resultSceneVertices[6].y)   // �������� ��ư
        isBtnOnMouse[BUTTON_TONEXT] = TRUE;
    else if (isBtnOnMouse[BUTTON_TONEXT])   isBtnOnMouse[BUTTON_TONEXT] = FALSE;
}

// ���Ӿ� ���콺 �̵�
void MouseMoveGameScene(HWND hWnd, SHORT* mousePos, SliderData* sliderInfo)
{
    if (sceneState.nowSceneType != SCENE_GAME) // ���Ӿ� �ƴϸ� ������
        return;

    if (sceneState.isOpenMenu || sceneState.onLevelUpScreen || GetCursor() != LoadCursor(NULL, IDC_ARROW))
        SetCursor(LoadCursor(NULL, IDC_ARROW));

    if (sceneState.isOpenMenu && mousePos[MOUSE_DRAG_XPOS] > menuVertices[12].x && mousePos[MOUSE_DRAG_YPOS] > menuVertices[12].y &&
        mousePos[MOUSE_DRAG_XPOS] < menuVertices[14].x && mousePos[MOUSE_DRAG_YPOS] < menuVertices[14].y)
        isBtnOnMouse[BUTTON_TOTITLE] = TRUE;
    else if (isBtnOnMouse[BUTTON_TOTITLE])
        isBtnOnMouse[BUTTON_TOTITLE] = FALSE;

    if (sceneState.isOpenMenu && !sceneState.clickSetFPS)   OnDragMenuSlider(sceneState.isOpenMenu, &mousePos[MOUSE_DRAG_XPOS], sliderInfo);    // �޴� - ���� �����̴� �巡��
    else if (!sceneState.rotateFreeze)                      CameraTransform(mousePos, sliderInfo[SLIDER_CAMERAROTATESPEED].value, &playerObj);  // ���콺�� �÷��̾� �̵�, ȸ��

    if (sceneState.mouseCrossFocusMode && !sceneState.isOpenMenu) // ���콺�� ������ �߾����� �̵�
    {
        POINT ptCenter = { WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2 };
        ClientToScreen(hWnd, &ptCenter);
        SetCursorPos(ptCenter.x, ptCenter.y);

        mousePos[MOUSE_CLICK_XPOS] = (SHORT)(WIDTH_WINDOW / 2.0f);
        mousePos[MOUSE_CLICK_YPOS] = (SHORT)(HEIGHT_WINDOW / 2.0f);
    }
}


// ���콺 Ŀ�� on/off
void TurnOnOffCursor(BOOL turnOn)
{
    if (turnOn)                 // Ŀ���� ���̰� �� ��
    {
        if (cursorShow <= 0)    // Ŀ���� �̹� ���̰� ���� ������
        {
            ShowCursor(TRUE);   // Ŀ�� ���̰�
            cursorShow++;
        }
    }
    else                        // Ŀ���� ����� �� ��
    {
        if (cursorShow > 0)     // Ŀ���� �̹� ������ ���� ������
        {
            ShowCursor(FALSE);  // Ŀ�� �����
            cursorShow--;
        }
    }
}

// ���� ��ư�� Ŭ��
void OnClickTimeAndMenuButton(SHORT* mousePos, BOOL* shotBullet, DateInfo* dateInfo)
{
    if (mousePos[MOUSE_CLICK_YPOS] > gameSceneVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < gameSceneVertices[7].y)
    {
        if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[4].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[5].x)         // �ð� ����/���
        {
            sceneState.clickKey[KEY_TIMESTOP] = !sceneState.clickKey[KEY_TIMESTOP];
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[8].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[9].x)    // ���� �ð���
        {
            dateInfo->clock = ((int)dateInfo->clock + 3) / 3 * 3;
            UpdateSunPosition(dateInfo);
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[12].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[13].x)  // ���� ��
        {
            dateInfo->day++;
            UpdateSunPosition(dateInfo);
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[16].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[17].x)  // ���� ��
        {
            dateInfo->month++;
            UpdateSunPosition(dateInfo);
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[20].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[21].x)  // �޴�
        {
            sceneState.clickSetFPS = FALSE;
            *shotBullet = FALSE;
            MenuOnOff();
        }
    }
}

// �޴�â on/off ��Ű��
void MenuOnOff()
{
    sceneState.isOpenMenu = !(sceneState.isOpenMenu);

    if (sceneState.isOpenMenu)  // �޴� on
    {
        sceneState.tempMouseCrossFocusMode = sceneState.mouseCrossFocusMode;
        sceneState.tempRotateFreeze = sceneState.rotateFreeze;
        sceneState.mouseCrossFocusMode = FALSE;
        sceneState.rotateFreeze = TRUE;

        TurnOnOffCursor(TRUE);
    }
    else                        // �޴� off
    {
        sceneState.mouseCrossFocusMode = sceneState.tempMouseCrossFocusMode;
        sceneState.rotateFreeze = sceneState.tempRotateFreeze;

        TurnOnOffCursor(!sceneState.mouseCrossFocusMode);
    }
}


// fps ���� Ŭ��
void OnClickChangeFPS(SHORT* mousePos, Timer* timer)
{
    // FPS ����
    if (mousePos[MOUSE_CLICK_XPOS] > menuVertices[16].x && mousePos[MOUSE_CLICK_XPOS] < menuVertices[18].x && 
        mousePos[MOUSE_CLICK_YPOS] > menuVertices[16].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[18].y)
        sceneState.clickSetFPS = TRUE;
    else if (sceneState.clickSetFPS && mousePos[MOUSE_CLICK_XPOS] > menuVertices[20].x && mousePos[MOUSE_CLICK_XPOS] < menuVertices[21].x && 
        mousePos[MOUSE_CLICK_YPOS] > menuVertices[16].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[39].y)
    {
        if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[20].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[23].y)         timer->SetFPS(30);
        else if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[24].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[27].y)    timer->SetFPS(45);
        else if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[28].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[31].y)    timer->SetFPS(60);
        else if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[32].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[35].y)    timer->SetFPS(90);
        else if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[36].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[39].y)    timer->SetFPS(120);
        sceneState.clickSetFPS = FALSE;
    }
    else
        sceneState.clickSetFPS = FALSE;
}

// �޴� �����̴� Ŭ��
void OnClickMenuSlider(int isOpenMenu, SHORT* mousePos, SliderData* sliderInfo)
{
    if (isOpenMenu != 2 || mousePos[MOUSE_CLICK_XPOS] < MENU_SLIDER_START || mousePos[MOUSE_CLICK_XPOS] > MENU_SLIDER_END)
        return;
    
    int nowSliderNum = -1;  // ��� �����̴��� �����ߴ���
    if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[0].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[3].y)           nowSliderNum = SLIDER_FIELDOFVIEW;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[20].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[23].y)    nowSliderNum = SLIDER_VIEWFAR;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[40].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[43].y)    nowSliderNum = SLIDER_CAMERAROTATESPEED;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[60].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[63].y)    nowSliderNum = SLIDER_BGM;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[80].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[83].y)    nowSliderNum = SLIDER_SE;

    if (nowSliderNum == -1)
        return;

    SetSliderHorizontalInfo(sliderInfo, nowSliderNum, mousePos[MOUSE_CLICK_XPOS], MENU_SLIDER_START, MENU_SLIDER_END); // �����̴� ����, ������ ������Ʈ

    if (nowSliderNum == SLIDER_VIEWFAR)     SetSkyboxSize(sliderInfo);                          // �þ� ���� �����̴� ���� �� ��ī�̹ڽ� ũ�� ����
    else if (nowSliderNum == SLIDER_BGM)    SetVolume(sliderInfo[SLIDER_BGM].value, 0);         // �����̵� ���� �� ����� ũ�� ����
    else if (nowSliderNum == SLIDER_SE)     SetVolume(0.5f * sliderInfo[SLIDER_SE].value, 1);   // �����̵� ���� �� ȿ���� ũ�� ����
}

// �޴� �����̴� �巡��
void OnDragMenuSlider(int isOpenMenu, SHORT* nowMousePosX, SliderData* sliderInfo)
{
    int nowSliderNum = -1; // ��� �����̴��� �����ߴ���
    if (sliderInfo[SLIDER_FIELDOFVIEW].onDragHandle)            nowSliderNum = SLIDER_FIELDOFVIEW;
    else if (sliderInfo[SLIDER_VIEWFAR].onDragHandle)           nowSliderNum = SLIDER_VIEWFAR;
    else if (sliderInfo[SLIDER_CAMERAROTATESPEED].onDragHandle) nowSliderNum = SLIDER_CAMERAROTATESPEED;
    else if (sliderInfo[SLIDER_BGM].onDragHandle)               nowSliderNum = SLIDER_BGM;
    else if (sliderInfo[SLIDER_SE].onDragHandle)                nowSliderNum = SLIDER_SE;

    if (nowSliderNum == -1)
        return;

    if (*nowMousePosX < MENU_SLIDER_START)      *nowMousePosX = MENU_SLIDER_START;  // �������� �����̴� ������ �� �Ѿ��
    else if (*nowMousePosX > MENU_SLIDER_END)   *nowMousePosX = MENU_SLIDER_END;

    SetSliderHorizontalInfo(sliderInfo, nowSliderNum, *nowMousePosX, MENU_SLIDER_START, MENU_SLIDER_END); // �����̴� ����, ������ ������Ʈ

    if (nowSliderNum == SLIDER_VIEWFAR)     SetSkyboxSize(sliderInfo);                          // �þ� ���� �����̴� ���� �� ��ī�̹ڽ� ũ�� ����
    else if (nowSliderNum == SLIDER_BGM)    SetVolume(sliderInfo[SLIDER_BGM].value, 0);         // �����̵� ���� �� ����� ũ�� ����
    else if (nowSliderNum == SLIDER_SE)     SetVolume(0.5f * sliderInfo[SLIDER_SE].value, 1);   // �����̵� ���� �� ȿ���� ũ�� ����
}

// horizontal �����̴� ���� ����(������Ʈ)
void SetSliderHorizontalInfo(SliderData* sliderInfo, int nowSliderNum, SHORT mousePosX, FLOAT startPosX, FLOAT endPosX)
{
    sliderInfo[nowSliderNum].clickXPos = mousePosX;
    sliderInfo[nowSliderNum].value = (mousePosX - startPosX) / (endPosX - startPosX);
    sliderInfo[nowSliderNum].onDragHandle = TRUE;

    int sliderVerticesNum = nowSliderNum * 20;  // ������ ������Ʈ, �� �� ���׶� �κ��� �߾ӱ����� �ν��ϵ��� (+-WIDTH_WINDOW / 10.0f * 0.175f)
    menuSliderVertices[13 + sliderVerticesNum].x = menuSliderVertices[14 + sliderVerticesNum].x = sliderInfo[nowSliderNum].clickXPos;
    menuSliderVertices[16 + sliderVerticesNum].x = menuSliderVertices[19 + sliderVerticesNum].x = sliderInfo[nowSliderNum].clickXPos - WIDTH_WINDOW / 10.0f * 0.175f;
    menuSliderVertices[17 + sliderVerticesNum].x = menuSliderVertices[18 + sliderVerticesNum].x = sliderInfo[nowSliderNum].clickXPos + WIDTH_WINDOW / 10.0f * 0.175f;
}

// �þ� �Ÿ� �������� ��ī�̹ڽ� ũ�� ����
void SetSkyboxSize(SliderData* sliderInfo)
{
    VOID* pVertices;
    g_pVB_Array[VB_SKYBOX]->Lock(0, sizeof(skyBoxVertices), (void**)&pVertices, 0); // Lock(lock�� ������, ũ��, ������ �ּ�, 0)

    D3DXVECTOR3 v3SkyBox = D3DXVECTOR3{ 1, 1, 1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[0].position = skyBoxVertices[10].position = skyBoxVertices[17].position = v3SkyBox;

    v3SkyBox = D3DXVECTOR3{ 1, 1, -1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[1].position = skyBoxVertices[9].position = skyBoxVertices[20].position = v3SkyBox;

    v3SkyBox = D3DXVECTOR3{ 1, -1, 1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[3].position = skyBoxVertices[13].position = skyBoxVertices[18].position = v3SkyBox;

    v3SkyBox = D3DXVECTOR3{ 1, -1, -1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[2].position = skyBoxVertices[14].position = skyBoxVertices[23].position = v3SkyBox;


    v3SkyBox = D3DXVECTOR3{ -1, 1, 1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[5].position = skyBoxVertices[11].position = skyBoxVertices[16].position = v3SkyBox;

    v3SkyBox = D3DXVECTOR3{ -1, 1, -1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[4].position = skyBoxVertices[8].position = skyBoxVertices[21].position = v3SkyBox;

    v3SkyBox = D3DXVECTOR3{ -1, -1, 1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[6].position = skyBoxVertices[12].position = skyBoxVertices[19].position = v3SkyBox;

    v3SkyBox = D3DXVECTOR3{ -1, -1, -1 } *(FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value) * 0.7f;
    skyBoxVertices[7].position = skyBoxVertices[15].position = skyBoxVertices[22].position = v3SkyBox;

    memcpy(pVertices, skyBoxVertices, sizeof(skyBoxVertices));
    g_pVB_Array[VB_SKYBOX]->Unlock();
}

// Ÿ��Ʋ�� �̵� (���� ���(����) ���� �� ���� ��Ȳ �ʱ�ȭ)
void ToTitle(int* nowGameData, SaveData saveData[10], DateInfo dateInfo, tm* realTimeInfo)
{
    nowGameData[NOWGAME_RANKING] = 10;
    if (nowGameData[NOWGAME_SCORE] > saveData[9].score)
        for (int rank = 0; rank < 10; rank++)
            if (nowGameData[NOWGAME_SCORE] > saveData[rank].score) { nowGameData[NOWGAME_RANKING] = rank; break; }

    if (nowGameData[NOWGAME_RANKING] < 10)
    {
        resultSceneVertices[8].y = resultSceneVertices[9].y = HEIGHT_WINDOW / 10.0f * (2.0f + nowGameData[NOWGAME_RANKING] * 0.6f);
        resultSceneVertices[10].y = resultSceneVertices[11].y = HEIGHT_WINDOW / 10.0f * (2.6f + nowGameData[NOWGAME_RANKING] * 0.6f);

        for (int rank = 8; rank >= nowGameData[NOWGAME_RANKING]; rank--)
            saveData[rank + 1] = saveData[rank];
        saveData[nowGameData[NOWGAME_RANKING]] = { nowGameData[NOWGAME_SCORE], nowGameData[NOWGAME_KILLCOUNT], {dateInfo.month, dateInfo.day}, {realTimeInfo->tm_year + 1900, realTimeInfo->tm_mon + 1, realTimeInfo->tm_mday, realTimeInfo->tm_hour, realTimeInfo->tm_min } };
        nowGameData[NOWGAME_BESTSCORE] = saveData[0].score;
    }

    TurnOnOffCursor(TRUE);

    sceneState = { SCENE_RESULT, 0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, {FALSE, TRUE, TRUE, TRUE, FALSE, FALSE} };
}


// ������ ���ʽ� ī�� ����
void OnClickLevelupBonusCard(SHORT* mousePos)
{
    if (sceneState.onLevelUpScreen && mousePos[MOUSE_CLICK_YPOS] > levelUpScreenVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < levelUpScreenVertices[7].y)
    {
        if (mousePos[MOUSE_CLICK_XPOS] > levelUpScreenVertices[4].x && mousePos[MOUSE_CLICK_XPOS] < levelUpScreenVertices[5].x && !(playerObj.GetLevel() % 5 == 0 && playerObj.GetAttackSpreadLevel() >= SPREADLEVELMAX && playerObj.GetLevel() < 101))
            ApplyLevelUpBonus(0);
        else if (mousePos[MOUSE_CLICK_XPOS] > levelUpScreenVertices[8].x && mousePos[MOUSE_CLICK_XPOS] < levelUpScreenVertices[9].x && !(playerObj.GetLevel() % 5 == 0 && playerObj.GetAttackBurstLevel() >= BURSTLEVELMAX && playerObj.GetLevel() < 101))
            ApplyLevelUpBonus(1);
        else if (mousePos[MOUSE_CLICK_XPOS] > levelUpScreenVertices[12].x && mousePos[MOUSE_CLICK_XPOS] < levelUpScreenVertices[13].x && !(playerObj.GetLevel() % 5 == 0 && playerObj.GetBulletSizeLevel() >= BULLETSIZELEVELMAX && playerObj.GetLevel() < 101))
            ApplyLevelUpBonus(2);
    }
}

// ������ ���ʽ� ī�� ����
void ApplyLevelUpBonus(int selectCardNum)
{
    playerObj.ClickLevelUpBonus(selectCardNum);
    sceneState.onLevelUpScreen = FALSE;
    sceneState.mouseCrossFocusMode = sceneState.tempMouseCrossFocusMode;
    sceneState.rotateFreeze = sceneState.tempRotateFreeze;

    TurnOnOffCursor(!sceneState.mouseCrossFocusMode);
}