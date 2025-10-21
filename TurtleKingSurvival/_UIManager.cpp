#include "_UIManager.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "Timer.h"
#include "_TransformMatrix.h"
#include "_UpdateGameProc.h"
#include "_SoundManager.h"

extern HWND  g_hwnd;
extern FLOAT buttonSize;    // 버튼들 크기, 클릭 시 어느 위치(버튼)가 클릭되었느니 판별을 위해 사용

extern LPDIRECT3DVERTEXBUFFER9 g_pVB_Array[VB_MAX];
extern CPlayer playerObj;
extern SceneState sceneState;
extern bool isBtnOnMouse[BUTTON_MAX];

int cursorShow = 1;


// 타이틀씬 마우스 클릭
void MouseClickTitleScene(SHORT* mousePos)
{
    if (sceneState.nowSceneType != SCENE_TITLE && sceneState.nowSceneType != SCENE_SCORE)                                       // 타이틀씬 아니면 나가기
        return;

    if (mousePos[MOUSE_CLICK_XPOS] < titleSceneVertices[4].x || mousePos[MOUSE_CLICK_XPOS] > titleSceneVertices[6].x)           // 버튼 클릭 아니면 나가기
        return;

    if (mousePos[MOUSE_CLICK_YPOS] > titleSceneVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < titleSceneVertices[6].y)           // 시작 버튼
        sceneState.nowSceneType = SCENE_GAME;
    else if (mousePos[MOUSE_CLICK_YPOS] > titleSceneVertices[8].y && mousePos[MOUSE_CLICK_YPOS] < titleSceneVertices[10].y)     // 점수 버튼
    {
        if (sceneState.nowSceneType == SCENE_TITLE)    sceneState.nowSceneType = SCENE_SCORE;
        else                                            sceneState.nowSceneType = SCENE_TITLE;
    }
    else if (mousePos[MOUSE_CLICK_YPOS] > titleSceneVertices[12].y && mousePos[MOUSE_CLICK_YPOS] < titleSceneVertices[14].y)    // 종료 버튼
        DestroyWindow(g_hwnd);
}

// 결과씬 마우스 클릭
void MouseClickResultScene(SHORT* mousePos, CEnemy** enemyObj, CBullet** bullets, int* nowGameData, DateInfo* dateInfo)
{
    if (sceneState.nowSceneType != SCENE_RESULT) // 결과씬 아니면 나가기
        return;

    if (mousePos[MOUSE_CLICK_XPOS] < resultSceneVertices[4].x || mousePos[MOUSE_CLICK_XPOS] > resultSceneVertices[6].x || 
        mousePos[MOUSE_CLICK_YPOS] < resultSceneVertices[4].y || mousePos[MOUSE_CLICK_YPOS] > resultSceneVertices[6].y)
        return; // 다음으로(타이틀로) 버튼 누를때만 이 if문 다음으로 통과

    nowGameData[NOWGAME_SCORE] = nowGameData[NOWGAME_KILLCOUNT] = 0;
    *dateInfo = { 0.0f, 1, 1, { 0, 0, 0.1f } };

    playerObj.SettingInfo();
    playerObj.TakeDamage(0);
    for (int enemyCount = 0; enemyCount < ENEMY_MAX; enemyCount++)      // 적 유닛 delete
    {
        if (enemyObj[enemyCount] != NULL)
        {
            delete enemyObj[enemyCount];
            enemyObj[enemyCount] = NULL;
        }
    }
    for (int bulletCount = 0; bulletCount < BULLET_MAX; bulletCount++)  // 총알 delete
    {
        if (bullets[bulletCount] != NULL)
        {
            delete bullets[bulletCount];
            bullets[bulletCount] = NULL;
        }
    }
    sceneState.nowSceneType = SCENE_TITLE;
}

// 게임씬 마우스 클릭
void MouseClickGameScene(SHORT* mousePos, int* nowGameData, SaveData* saveData, DateInfo* dateInfo, tm* realTimeInfo, SliderData* sliderInfo, BOOL* shotBullet, Timer* timer, CBullet** bullets)
{
    if (sceneState.nowSceneType != SCENE_GAME) // 게임씬 아니면 나가기
        return;

    // 메뉴에서 플레이어 정보 / 설정 변환
    if (sceneState.isOpenMenu && mousePos[MOUSE_CLICK_XPOS] > menuVertices[4].x && mousePos[MOUSE_CLICK_XPOS] < menuVertices[5].x)
    {
        if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[6].y)       sceneState.isOpenMenu = 1;
        else if (mousePos[MOUSE_CLICK_YPOS] > menuVertices[8].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[10].y) sceneState.isOpenMenu = 2;
        sceneState.clickSetFPS = FALSE;
    }

    // 메뉴에서 타이틀로 나가기 버튼
    if (sceneState.isOpenMenu == 2 && mousePos[MOUSE_CLICK_XPOS] > menuVertices[12].x && mousePos[MOUSE_CLICK_XPOS] < menuVertices[14].x && 
        mousePos[MOUSE_CLICK_YPOS] > menuVertices[12].y && mousePos[MOUSE_CLICK_YPOS] < menuVertices[14].y)
        ToTitle(nowGameData, saveData, *dateInfo, realTimeInfo);

    if (!sceneState.clickSetFPS)
        OnClickMenuSlider(sceneState.isOpenMenu, mousePos, sliderInfo); // 메뉴 - 설정 슬라이더 클릭
    OnClickTimeAndMenuButton(mousePos, shotBullet, dateInfo); // 우상단 버튼 클릭 (시간 변경, 메뉴)
    OnClickLevelupBonusCard(mousePos); // 레벨업 클릭
    OnClickChangeFPS(mousePos, timer); // FPS 변경

    if (shotBullet && !sceneState.isOpenMenu && !sceneState.onLevelUpScreen && playerObj.OverAttackDelay())
        playerObj.Attack(bullets); // 총알 발사
}


// 타이틀씬 마우스 이동
void MouseMoveTitleScene(SHORT* mousePos)
{
    if (sceneState.nowSceneType != SCENE_TITLE) // 타이틀씬 아니면 나가기
        return;

    // 마우스를 버튼 위에 가져다 올리면 버튼이 눌린 모습으로 변하도록
    if (mousePos[MOUSE_DRAG_YPOS] > titleSceneVertices[4].y && mousePos[MOUSE_DRAG_YPOS] < titleSceneVertices[6].y &&
        mousePos[MOUSE_DRAG_XPOS] > titleSceneVertices[4].x && mousePos[MOUSE_DRAG_XPOS] < titleSceneVertices[6].x)     // 시작 버튼
        isBtnOnMouse[BUTTON_PLAY] = TRUE;
    else if (isBtnOnMouse[BUTTON_PLAY])     isBtnOnMouse[BUTTON_PLAY] = FALSE;

    if (mousePos[MOUSE_DRAG_YPOS] > titleSceneVertices[8].y && mousePos[MOUSE_DRAG_YPOS] < titleSceneVertices[10].y &&
        mousePos[MOUSE_DRAG_XPOS] > titleSceneVertices[8].x && mousePos[MOUSE_DRAG_XPOS] < titleSceneVertices[10].x)    // 점수 버튼
        isBtnOnMouse[BUTTON_SCORE] = TRUE;
    else if (isBtnOnMouse[BUTTON_SCORE])    isBtnOnMouse[BUTTON_SCORE] = FALSE;

    if (mousePos[MOUSE_DRAG_YPOS] > titleSceneVertices[12].y && mousePos[MOUSE_DRAG_YPOS] < titleSceneVertices[14].y &&
        mousePos[MOUSE_DRAG_XPOS] > titleSceneVertices[12].x && mousePos[MOUSE_DRAG_XPOS] < titleSceneVertices[14].x)   // 종료 버튼
        isBtnOnMouse[BUTTON_END] = TRUE;
    else if (isBtnOnMouse[BUTTON_END])      isBtnOnMouse[BUTTON_END] = FALSE;
}

// 결과씬 마우스 이동
void MouseMoveResultScene(SHORT* mousePos)
{
    if (sceneState.nowSceneType != SCENE_RESULT) // 결과씬 아니면 나가기
        return;

    // 마우스를 버튼 위에 가져다 올리면 버튼이 눌린 모습으로 변하도록
    if (mousePos[MOUSE_DRAG_XPOS] > resultSceneVertices[4].x && mousePos[MOUSE_DRAG_XPOS] < resultSceneVertices[6].x &&
        mousePos[MOUSE_DRAG_YPOS] > resultSceneVertices[4].y && mousePos[MOUSE_DRAG_YPOS] < resultSceneVertices[6].y)   // 다음으로 버튼
        isBtnOnMouse[BUTTON_TONEXT] = TRUE;
    else if (isBtnOnMouse[BUTTON_TONEXT])   isBtnOnMouse[BUTTON_TONEXT] = FALSE;
}

// 게임씬 마우스 이동
void MouseMoveGameScene(HWND hWnd, SHORT* mousePos, SliderData* sliderInfo)
{
    if (sceneState.nowSceneType != SCENE_GAME) // 게임씬 아니면 나가기
        return;

    if (sceneState.isOpenMenu || sceneState.onLevelUpScreen || GetCursor() != LoadCursor(NULL, IDC_ARROW))
        SetCursor(LoadCursor(NULL, IDC_ARROW));

    if (sceneState.isOpenMenu && mousePos[MOUSE_DRAG_XPOS] > menuVertices[12].x && mousePos[MOUSE_DRAG_YPOS] > menuVertices[12].y &&
        mousePos[MOUSE_DRAG_XPOS] < menuVertices[14].x && mousePos[MOUSE_DRAG_YPOS] < menuVertices[14].y)
        isBtnOnMouse[BUTTON_TOTITLE] = TRUE;
    else if (isBtnOnMouse[BUTTON_TOTITLE])
        isBtnOnMouse[BUTTON_TOTITLE] = FALSE;

    if (sceneState.isOpenMenu && !sceneState.clickSetFPS)   OnDragMenuSlider(sceneState.isOpenMenu, &mousePos[MOUSE_DRAG_XPOS], sliderInfo);    // 메뉴 - 설정 슬라이더 드래그
    else if (!sceneState.rotateFreeze)                      CameraTransform(mousePos, sliderInfo[SLIDER_CAMERAROTATESPEED].value, &playerObj);  // 마우스로 플레이어 이동, 회전

    if (sceneState.mouseCrossFocusMode && !sceneState.isOpenMenu) // 마우스를 윈도우 중앙으로 이동
    {
        POINT ptCenter = { WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2 };
        ClientToScreen(hWnd, &ptCenter);
        SetCursorPos(ptCenter.x, ptCenter.y);

        mousePos[MOUSE_CLICK_XPOS] = (SHORT)(WIDTH_WINDOW / 2.0f);
        mousePos[MOUSE_CLICK_YPOS] = (SHORT)(HEIGHT_WINDOW / 2.0f);
    }
}


// 마우스 커서 on/off
void TurnOnOffCursor(BOOL turnOn)
{
    if (turnOn)                 // 커서를 보이게 할 때
    {
        if (cursorShow <= 0)    // 커서가 이미 보이고 있지 않으면
        {
            ShowCursor(TRUE);   // 커서 보이게
            cursorShow++;
        }
    }
    else                        // 커서를 숨기게 할 때
    {
        if (cursorShow > 0)     // 커서가 이미 숨겨져 있지 않으면
        {
            ShowCursor(FALSE);  // 커서 숨기기
            cursorShow--;
        }
    }
}

// 우상단 버튼들 클릭
void OnClickTimeAndMenuButton(SHORT* mousePos, BOOL* shotBullet, DateInfo* dateInfo)
{
    if (mousePos[MOUSE_CLICK_YPOS] > gameSceneVertices[4].y && mousePos[MOUSE_CLICK_YPOS] < gameSceneVertices[7].y)
    {
        if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[4].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[5].x)         // 시간 정지/재생
        {
            sceneState.clickKey[KEY_TIMESTOP] = !sceneState.clickKey[KEY_TIMESTOP];
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[8].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[9].x)    // 다음 시간대
        {
            dateInfo->clock = ((int)dateInfo->clock + 3) / 3 * 3;
            UpdateSunPosition(dateInfo);
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[12].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[13].x)  // 다음 날
        {
            dateInfo->day++;
            UpdateSunPosition(dateInfo);
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[16].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[17].x)  // 다음 달
        {
            dateInfo->month++;
            UpdateSunPosition(dateInfo);
            *shotBullet = FALSE;
        }
        else if (mousePos[MOUSE_CLICK_XPOS] > gameSceneVertices[20].x && mousePos[MOUSE_CLICK_XPOS] < gameSceneVertices[21].x)  // 메뉴
        {
            sceneState.clickSetFPS = FALSE;
            *shotBullet = FALSE;
            MenuOnOff();
        }
    }
}

// 메뉴창 on/off 시키기
void MenuOnOff()
{
    sceneState.isOpenMenu = !(sceneState.isOpenMenu);

    if (sceneState.isOpenMenu)  // 메뉴 on
    {
        sceneState.tempMouseCrossFocusMode = sceneState.mouseCrossFocusMode;
        sceneState.tempRotateFreeze = sceneState.rotateFreeze;
        sceneState.mouseCrossFocusMode = FALSE;
        sceneState.rotateFreeze = TRUE;

        TurnOnOffCursor(TRUE);
    }
    else                        // 메뉴 off
    {
        sceneState.mouseCrossFocusMode = sceneState.tempMouseCrossFocusMode;
        sceneState.rotateFreeze = sceneState.tempRotateFreeze;

        TurnOnOffCursor(!sceneState.mouseCrossFocusMode);
    }
}


// fps 변경 클릭
void OnClickChangeFPS(SHORT* mousePos, Timer* timer)
{
    // FPS 조절
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

// 메뉴 슬라이더 클릭
void OnClickMenuSlider(int isOpenMenu, SHORT* mousePos, SliderData* sliderInfo)
{
    if (isOpenMenu != 2 || mousePos[MOUSE_CLICK_XPOS] < MENU_SLIDER_START || mousePos[MOUSE_CLICK_XPOS] > MENU_SLIDER_END)
        return;
    
    int nowSliderNum = -1;  // 어느 슬라이더를 조작했는지
    if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[0].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[3].y)           nowSliderNum = SLIDER_FIELDOFVIEW;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[20].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[23].y)    nowSliderNum = SLIDER_VIEWFAR;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[40].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[43].y)    nowSliderNum = SLIDER_CAMERAROTATESPEED;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[60].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[63].y)    nowSliderNum = SLIDER_BGM;
    else if (mousePos[MOUSE_CLICK_YPOS] > menuSliderVertices[80].y && mousePos[MOUSE_CLICK_YPOS] < menuSliderVertices[83].y)    nowSliderNum = SLIDER_SE;

    if (nowSliderNum == -1)
        return;

    SetSliderHorizontalInfo(sliderInfo, nowSliderNum, mousePos[MOUSE_CLICK_XPOS], MENU_SLIDER_START, MENU_SLIDER_END); // 슬라이더 정보, 게이지 업데이트

    if (nowSliderNum == SLIDER_VIEWFAR)     SetSkyboxSize(sliderInfo);                          // 시야 범위 슬라이더 조작 시 스카이박스 크기 변경
    else if (nowSliderNum == SLIDER_BGM)    SetVolume(sliderInfo[SLIDER_BGM].value, 0);         // 슬라이드 조작 시 배경음 크기 조절
    else if (nowSliderNum == SLIDER_SE)     SetVolume(0.5f * sliderInfo[SLIDER_SE].value, 1);   // 슬라이드 조작 시 효과음 크기 조절
}

// 메뉴 슬라이더 드래그
void OnDragMenuSlider(int isOpenMenu, SHORT* nowMousePosX, SliderData* sliderInfo)
{
    int nowSliderNum = -1; // 어느 슬라이더를 조작했는지
    if (sliderInfo[SLIDER_FIELDOFVIEW].onDragHandle)            nowSliderNum = SLIDER_FIELDOFVIEW;
    else if (sliderInfo[SLIDER_VIEWFAR].onDragHandle)           nowSliderNum = SLIDER_VIEWFAR;
    else if (sliderInfo[SLIDER_CAMERAROTATESPEED].onDragHandle) nowSliderNum = SLIDER_CAMERAROTATESPEED;
    else if (sliderInfo[SLIDER_BGM].onDragHandle)               nowSliderNum = SLIDER_BGM;
    else if (sliderInfo[SLIDER_SE].onDragHandle)                nowSliderNum = SLIDER_SE;

    if (nowSliderNum == -1)
        return;

    if (*nowMousePosX < MENU_SLIDER_START)      *nowMousePosX = MENU_SLIDER_START;  // 게이지가 슬라이더 범위를 안 넘어서게
    else if (*nowMousePosX > MENU_SLIDER_END)   *nowMousePosX = MENU_SLIDER_END;

    SetSliderHorizontalInfo(sliderInfo, nowSliderNum, *nowMousePosX, MENU_SLIDER_START, MENU_SLIDER_END); // 슬라이더 정보, 게이지 업데이트

    if (nowSliderNum == SLIDER_VIEWFAR)     SetSkyboxSize(sliderInfo);                          // 시야 범위 슬라이더 조작 시 스카이박스 크기 변경
    else if (nowSliderNum == SLIDER_BGM)    SetVolume(sliderInfo[SLIDER_BGM].value, 0);         // 슬라이드 조작 시 배경음 크기 조절
    else if (nowSliderNum == SLIDER_SE)     SetVolume(0.5f * sliderInfo[SLIDER_SE].value, 1);   // 슬라이드 조작 시 효과음 크기 조절
}

// horizontal 슬라이더 정보 저장(업데이트)
void SetSliderHorizontalInfo(SliderData* sliderInfo, int nowSliderNum, SHORT mousePosX, FLOAT startPosX, FLOAT endPosX)
{
    sliderInfo[nowSliderNum].clickXPos = mousePosX;
    sliderInfo[nowSliderNum].value = (mousePosX - startPosX) / (endPosX - startPosX);
    sliderInfo[nowSliderNum].onDragHandle = TRUE;

    int sliderVerticesNum = nowSliderNum * 20;  // 게이지 업데이트, 양 끝 동그란 부분의 중앙까지만 인식하도록 (+-WIDTH_WINDOW / 10.0f * 0.175f)
    menuSliderVertices[13 + sliderVerticesNum].x = menuSliderVertices[14 + sliderVerticesNum].x = sliderInfo[nowSliderNum].clickXPos;
    menuSliderVertices[16 + sliderVerticesNum].x = menuSliderVertices[19 + sliderVerticesNum].x = sliderInfo[nowSliderNum].clickXPos - WIDTH_WINDOW / 10.0f * 0.175f;
    menuSliderVertices[17 + sliderVerticesNum].x = menuSliderVertices[18 + sliderVerticesNum].x = sliderInfo[nowSliderNum].clickXPos + WIDTH_WINDOW / 10.0f * 0.175f;
}

// 시야 거리 조작으로 스카이박스 크기 변경
void SetSkyboxSize(SliderData* sliderInfo)
{
    VOID* pVertices;
    g_pVB_Array[VB_SKYBOX]->Lock(0, sizeof(skyBoxVertices), (void**)&pVertices, 0); // Lock(lock할 시작점, 크기, 버퍼의 주소, 0)

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

// 타이틀로 이동 (게임 결과(순위) 저장 및 게임 상황 초기화)
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


// 레벨업 보너스 카드 선택
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

// 레벨업 보너스 카드 적용
void ApplyLevelUpBonus(int selectCardNum)
{
    playerObj.ClickLevelUpBonus(selectCardNum);
    sceneState.onLevelUpScreen = FALSE;
    sceneState.mouseCrossFocusMode = sceneState.tempMouseCrossFocusMode;
    sceneState.rotateFreeze = sceneState.tempRotateFreeze;

    TurnOnOffCursor(!sceneState.mouseCrossFocusMode);
}